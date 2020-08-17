import sys
import numpy as np 
import pandas as pd 
import matplotlib.pyplot as plt 

stations_file = sys.argv[1]
city_file = sys.argv[2]

output_name = sys.argv[3]

stations = pd.read_json(stations_file, lines=True)
city_data = pd.read_csv(city_file)

stations['avg_tmax'] = stations['avg_tmax'].div(10)
city_data = city_data[city_data['population'].notna()]
city_data = city_data[city_data['area'].notna()]
city_data['area'] = city_data['area'].div(1000000)
city_data = city_data[city_data['area'] <= 10000]
city_data['pop_density'] = city_data['population'].div(city_data['area'])

def distance(city, stations):
    """
    Implementation for distance function inspired by: 
    http://stackoverflow.com/questions/27928/calculate-distance-between-two-latitude-longitude-points-haversine-formula/21623206
    """
    R = 6371
    dLat = np.deg2rad(city['latitude']-stations['latitude'])
    dLon = np.deg2rad(city['longitude']-stations['longitude'])
    a = np.sin(dLat/2)**2 + np.cos(np.deg2rad(stations['latitude'])) * np.cos(np.deg2rad(city['latitude'])) * np.sin(dLon/2)**2
    c = 2*np.arctan2(np.sqrt(a), np.sqrt(1-a))
    d = R * c
    return d

def best_tmax(city, stations):
    distances = distance(city, stations)
    return stations['avg_tmax'].iloc[distances.argmin()]

city_data['best_tmax'] = city_data.apply(best_tmax, stations=stations, axis=1)

plt.plot(city_data['best_tmax'], city_data['pop_density'], 'b.')
plt.title('Temperature vs Population Density')
plt.ylabel('Population Density (people/km\u00b2)')
plt.xlabel('Avg Max Temperature (\u00b0C)')
plt.savefig(output_name)