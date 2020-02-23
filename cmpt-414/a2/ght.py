import cv2
import numpy as np
import os
from matplotlib import pyplot as plt 
from scipy.ndimage.filters import sobel

os.chdir('testimages')

img = cv2.imread('block.tif')
img_med = cv2.medianBlur(img, 3)
edges = cv2.Canny(img, 50, 150, apertureSize=3)

# plt.subplot(131), plt.imshow(img)
# plt.title('Original Image'), plt.xticks([]), plt.yticks([])
# plt.subplot(132),plt.imshow(edges)
# plt.title('Edge Image'), plt.xticks([]), plt.yticks([])
# plt.subplot(133),plt.imshow(img_med)
# plt.title('Med Filt Image'), plt.xticks([]), plt.yticks([])

# plt.show()

# Model generation
ref_point = (edges.shape[0]/2, edges.shape[1]/2)
x_gradient = sobel(edges, axis=0, mode='constant')
y_gradient = sobel(edges, axis=1, mode='constant')
all_gradients = np.arctan2(y_gradient, x_gradient)*180/np.pi
print(all_gradients)

r_table = {}
# Calculate distances to boundaries from ref point
for (i, j), val in np.ndenumerate(edges):
	if val > 0:
		if len(r_table[all_gradients[i, j]]) == 0:
			r_table[all_gradients[i, j]] = []
		r_table[all_gradients[i, j]].append(ref_point[0] - i, ref_point[1] - j)

print(r_table)
# print(x_gradient)
# print(y_gradient)

r_table = []
phis = []




