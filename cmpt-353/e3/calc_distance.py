import sys
import pandas as pd 
import numpy as np 
import matplotlib.pyplot as plt
import math
import xml.etree.ElementTree as ET
from pykalman import KalmanFilter

def output_gpx(points, output_filename):
    """
    Output a GPX file with latitude and longitude from the points DataFrame.
    """
    from xml.dom.minidom import getDOMImplementation
    def append_trkpt(pt, trkseg, doc):
        trkpt = doc.createElement('trkpt')
        trkpt.setAttribute('lat', '%.8f' % (pt['lat']))
        trkpt.setAttribute('lon', '%.8f' % (pt['lon']))
        trkseg.appendChild(trkpt)
    
    doc = getDOMImplementation().createDocument(None, 'gpx', None)
    trk = doc.createElement('trk')
    doc.documentElement.appendChild(trk)
    trkseg = doc.createElement('trkseg')
    trk.appendChild(trkseg)
    
    points.apply(append_trkpt, axis=1, trkseg=trkseg, doc=doc)
    
    with open(output_filename, 'w') as fh:
        doc.writexml(fh, indent=' ')

def get_data(file):
    parse_result = ET.parse(file)
    root = parse_result.getroot()
    latitude = []
    longitude = []
    for point in parse_result.iter('{http://www.topografix.com/GPX/1/0}trkpt'):
        latitude.append(point.attrib['lat'])
        longitude.append(point.attrib['lon'])
    lat = pd.Series(latitude, dtype='float')
    lon = pd.Series(longitude, dtype='float')
    df = pd.DataFrame({
        'lat': lat,
        'lon': lon
        })
    return df


def distance(points):
    """
    Implementation for distance function inspired by: 
    http://stackoverflow.com/questions/27928/calculate-distance-between-two-latitude-longitude-points-haversine-formula/21623206
    """
    R = 6371
    points2 = points.shift(periods=-1)
    dLat = np.deg2rad(points2['lat']-points['lat'])
    dLon = np.deg2rad(points2['lon']-points['lon'])
    a = np.sin(dLat/2)**2 + np.cos(np.deg2rad(points['lat'])) * np.cos(np.deg2rad(points2['lat'])) * np.sin(dLon/2)**2
    c = 2*np.arctan2(np.sqrt(a), np.sqrt(1-a))
    d = R * c
    return d.sum()*1000 # km to metres

def smooth(points):
    initial_state = points.iloc[0]
    observation_covariance = np.diag([0.00015, 0.00015]) ** 2 
    transition_covariance = np.diag([0.0001, 0.0001]) ** 2
    transition = [[1, 0], [0, 1]]
    kf = KalmanFilter(
        initial_state_mean=initial_state,
        initial_state_covariance=observation_covariance,
        observation_covariance=observation_covariance,
        transition_covariance=transition_covariance,
        transition_matrices=transition
        )
    kalman_smoothed, _ = kf.smooth(points)
    result = pd.DataFrame(kalman_smoothed)
    result = result.rename(columns={0: 'lat', 1: 'lon'})
    return result

def main():
    points = get_data(sys.argv[1])
    print('Unfiltered distance: %0.2f' % (distance(points),))
    
    smoothed_points = smooth(points)
    print('Filtered distance: %0.2f' % (distance(smoothed_points),))
    output_gpx(smoothed_points, 'out.gpx')


if __name__ == '__main__':
    main()