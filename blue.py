import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np
import cv2

image = mpimg.imread('blue.png')

image = image*255
image = image.astype(np.uint8)

print("This image is type")
print(image.dtype)

#start the histogram
plt.imshow(image)
plt.show()

histSize = 256
histRange = [0, 256] # the upper boundary is exclusive
accumulate = False

color = ('r','g','b')
im_hist = cv2.calcHist([image], [0], None, [histSize], histRange)
plt.plot(im_hist,'b')
plt.xlim([0,256])
# im_hist = cv2.calcHist(image, [2], None, [histSize], histRange)
# plt.plot(im_hist,'b')
# plt.xlim([0,256])


plt.show()

# hist_h=500
# hist_w=500
# cv2.normalize(im_hist, im_hist, alpha=0, beta=hist_h, norm_type=cv2.NORM_MINMAX)

# gray = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)

# threshold=0.2
# graybw=gray>0.2


# plt.figure()
# plt.imshow(image2)
# plt.show()

# histogram=[]
# for x in gray:
# 	count = 0
# 	for color in x:
# 		print(color)
# 		if(color>100):
# 			count=count+1
# 	histogram.append(count)
# print(histogram)

# plt 

# plt.figure()
# plt.imshow(gray, cmap='gray')

# plt.show()