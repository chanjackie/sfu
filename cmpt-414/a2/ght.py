import cv2
import numpy as np
import os
from matplotlib import pyplot as plt 
from scipy.ndimage.filters import sobel
from skimage.feature import canny

os.chdir('testimages')

# Read grayscaled image
img = cv2.imread('template_bear.png', 0)
ref_img = cv2.imread('block.tif', 0)
img_med = cv2.medianBlur(img, 3)
# edges = cv2.Canny(img, 50, 150, apertureSize=3)
edges = canny(img, low_threshold=50, high_threshold=150)

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
# print(all_gradients)

r_table = {}
# Calculate distances to boundaries from ref point

denum_edges = np.ndenumerate(edges)
for (i, j), val in denum_edges:
	if val > 0:
		if not all_gradients[i, j] in r_table.keys():
			r_table[all_gradients[i, j]] = []
		r_table[all_gradients[i, j]].append((ref_point[0] - i, ref_point[1] - j))

# Fill accumulator matrix
accum = np.zeros(ref_img.shape)
denum_edges = np.ndenumerate(edges)
for (i, j), val in denum_edges:
	if val > 0:
		for k in r_table[all_gradients[i, j]]:
			a1, a2 = i+k[0], j+k[1]
			if a1 < accum.shape[0] and a2 < accum.shape[1]:
				accum[a1, a2] += 1

print(accum.max())


plt.gray()

plt.subplot(1,2,1), plt.imshow(accum)
plt.title('Accumulator Matrix')

plt.subplot(1,2,2), plt.imshow(ref_img)
plt.title('Ref Image Detect')
# Mark most likely detection spot
x, y = np.where(accum == np.amax(accum))
print(x, y)
plt.scatter(y, x, marker='o', color='y')

plt.show()

# print(r_table)
# print(x_gradient)
# print(y_gradient)






