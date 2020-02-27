'''
CMPT 414 A2
Jackie Chan 301310345

Written for Python 2.7
'''

import cv2
import numpy as np
import os
from scipy import ndimage
from matplotlib import pyplot as plt

os.chdir('testimages')

def run_ght(template, test, temp_blur=1, ref_blur=3, scale=1, angles=[0], 
    low_thresholds=(30,30), high_thresholds=(70,130), num_results=3, show_steps=False):
    
    # template: template image file name
    # test: test image file name
    # temp_blur: # of times to apply median filter to template image
    # ref_blur: # of times to apply median filter to test image
    # scale: multiplicative scale to match test image
    # angles: list of angles to rotate template
    # low_thresholds: tuple of Canny low thresholds for template image and test image, respectively
    # high_thresholds: tuple of Canny high thresholds for template image and test image, respectively
    # num_results: # of top results to display for each angle in angles
    # show_steps: for debugging purposes, toggles plots showing in between steps

    output_folder = 'results'

    # Read grayscaled images
    temp_img = cv2.imread(template, 0)
    ref_img = cv2.imread(test, 0)

    # Image preparation
    temp_med = temp_img
    ref_med = ref_img
    for k in range(temp_blur):
        temp_med = cv2.medianBlur(temp_med, 3)
    for k in range(ref_blur):
        ref_med = cv2.medianBlur(ref_med, 5)

    plt.gray()
    if show_steps:
        plt.subplot(1,2,1), plt.imshow(temp_img)
        plt.title("Original temp image")
        plt.subplot(1,2,2), plt.imshow(temp_med)
        plt.title("Median filtered temp image")
        plt.show()

    # Get template edges for each angle
    temps = []
    for a in angles:
        temp_edges = cv2.Canny(temp_med, low_thresholds[0], high_thresholds[0])
        temp_edges = ndimage.rotate(temp_edges, a)
        for i in range(temp_edges.shape[0]):
            for j in range(temp_edges.shape[1]):
                # print(temp_edges[i, j])
                if temp_edges[i, j] < 100:
                    temp_edges[i, j] = 0
                else:
                    temp_edges[i, j] = 255
        if show_steps:
            plt.imshow(temp_edges, cmap='gray')
            plt.title("Temp edges with rotated " + str(a))
            plt.show()
        temps.append(temp_edges)

    # Model generation
    ref_point = (temp_edges.shape[0]/2, temp_edges.shape[1]/2)

    # Generate gradients
    all_temp_gradients = []
    for a in range(len(angles)):
        x_gradient = ndimage.filters.sobel(temps[a], axis=0, mode='constant')
        y_gradient = ndimage.filters.sobel(temps[a], axis=1, mode='constant')
        all_temp_gradients.append(np.arctan2(y_gradient, x_gradient)*360/np.pi)

    # Create r table for each rotation angle
    r_tables = []
    for a in range(len(angles)):
        r_table = {}
        temp_edges = temps[a]
        temp_gradients = all_temp_gradients[a]
        # Calculate distances to boundaries from ref point
        for i in range(temp_edges.shape[0]):
            for j in range(temp_edges.shape[1]):
                if temp_edges[i, j] != 0:
                    grad = round(temp_gradients[i, j])
                    if not grad in r_table.keys():
                        r_table[grad] = []
                    xc = ref_point[0] - i
                    yc = ref_point[1] - j
                    r_table[grad].append((xc, yc))
                    # print(grad)

        r_tables.append(r_table)
        # print(r_table.keys())


    # Fill accumulator matrix per r_table
    accumulators = []
    ref_edges = cv2.Canny(ref_med, low_thresholds[1], high_thresholds[1])
    if show_steps:
        plt.imshow(ref_edges, cmap='gray')
        plt.title("Ref image edges")
        plt.show()

    x_gradient = ndimage.filters.sobel(ref_edges, axis=0, mode='constant')
    y_gradient = ndimage.filters.sobel(ref_edges, axis=1, mode='constant')
    ref_gradients = np.arctan2(y_gradient, x_gradient)*360/np.pi

    for a in range(len(angles)):
        accum = np.zeros((ref_edges.shape[0], ref_edges.shape[1]))

        r_table = r_tables[a]
        for i in range(ref_edges.shape[0]):
            for j in range(ref_edges.shape[1]):
                grad = round(ref_gradients[i, j])
                if ref_edges[i, j] > 0 and grad in r_table.keys():
                    for ref in r_table[grad]:
                        a1, a2 = int(round(i+ref[0]*scale)), int(round(j+ref[1]*scale))
                        if a1 < accum.shape[0] and a2 < accum.shape[1]:
                            accum[a1, a2] += 1

        accumulators.append(accum)

    x_max = []
    y_max = []
    for a in range(len(angles)):
        added = 0
        accum = accumulators[a]
        maxVal = np.amax(accum)

        # Print accumulator array around peak
        x = np.where(accum == maxVal)[0]
        y = np.where(accum == maxVal)[1]
        if len(x) > 1:
            x = x[0]
            y = y[0]
        x = int(x)
        y = int(y)
        A = accum[x-10:x+10, y-10:y+10]
        print(template, test, 'Angle: ' + str(angles[a]))
        for row in A:
            for val in row:
                if val:
                    print '{:4}'.format(int(val)),
                else:
                    print '   .',
            print

        while added < num_results and maxVal >= 15:
            x = np.where(accum == maxVal)[0]
            y = np.where(accum == maxVal)[1]
            if len(x) and len(y):
                for i in range(len(x)):
                    x_max.append(x[i])
                    y_max.append(y[i])
                    added += 1
                    if added >= num_results:
                        break
            maxVal -= 1

    # plt.gray()
    plt.clf()

    fig = plt.figure(figsize=(16.0, 9.0))

    fig.add_subplot(1,3,1)
    plt.imshow(temp_img)
    plt.title('Template Image')

    fig.add_subplot(1,3,2)
    plt.imshow(accum, cmap='gray')
    plt.title('Accumulator Matrix')

    # ax = fig.add_subplot(1,2,2)
    ax = fig.add_subplot(1,3,3)
    plt.imshow(ref_img)
    plt.title('Test Image Detect')

    # Mark most likely detection spot
    for i in range(len(x_max)):
        circle = plt.Circle((y_max[i], x_max[i]), 20, color='y', fill=False)
        ax.add_patch(circle)

    if not os.path.exists(output_folder):
        os.makedirs(output_folder)
        
    result_file = template[:len(template)-4] + "_" + test[:len(test)-4] + '_result.png'
    plt.savefig(os.path.join(output_folder, result_file), bbox_inches='tight')
    # plt.show()

    plt.clf()
    fig = plt.figure(figsize=(16.0, 9.0))

    for i in range(len(angles)):
        fig.add_subplot(1,len(angles)+1,i+1)
        plt.imshow(temps[i])
        t_string = 'Template Edge Map'
        if angles[i] != 0:
            t_string += ' Rotated ' + str(angles[i]) + ' Degrees'
        plt.title(t_string)

    fig.add_subplot(1, len(angles)+1, len(angles)+1)
    plt.imshow(ref_edges)
    plt.title('Test Image Edge Map')

    edge_file = template[:len(template)-4] + "_" + test[:len(test)-4] + '_edges.png'
    plt.savefig(os.path.join(output_folder, edge_file), bbox_inches='tight')
    # plt.show()


run_ght('block.tif', 'block.tif', ref_blur=0, temp_blur=0)
run_ght('template_elephant.png', 'animals.jpg', angles=[95])
run_ght('template_bear.png', 'animals.jpg', ref_blur=1, angles=[-25, -120])
run_ght('template_elephant.png', 'animals2.jpg', scale=1.5, angles=[-20])
run_ght('template_bear.png', 'animals2.jpg', scale=1.5, angles=[-35, -100])
run_ght('template_K.png', 'letters.png', angles=[0, -8], ref_blur=0)
run_ght('template_Q.png', 'letters.png', angles=[0, 30], ref_blur=0, num_results=5)





