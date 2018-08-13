import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np
import cv2

imageleft = mpimg.imread('Left.png')
imageleft = imageleft*255
imageleft = imageleft.astype(np.uint8)

print("This image is type")
print(imageleft.dtype)

# Display the original image 
# plt.figure(1)
# plt.imshow(imageleft, cmap='gray')

# Define a kernel size and apply Gaussian smoothing
kernel_size = 9
blur_gray = cv2.GaussianBlur(imageleft,(kernel_size, kernel_size),0)

# Display the gaussian blur image 
plt.imshow(blur_gray, cmap='gray')

# Define our parameters for Canny and apply
low_threshold = 10
high_threshold = 80
edges3 = cv2.Canny(blur_gray, low_threshold, high_threshold)

# Morphological image
# Create a binary mask
ret, mask = cv2.threshold(edges3, 200, 255, cv2.THRESH_BINARY)

# Display mask in binary format
plt.figure(2)
plt.subplot(121)
plt.imshow(mask)

# Applied the dilation and opening morphological
kernel = np.ones((3,3),np.uint8)
dilation = cv2.dilate(mask,kernel,iterations = 1)
opening = cv2.morphologyEx(dilation, cv2.MORPH_OPEN, kernel)

# Display morphed mask in binary format
plt.subplot(122)
plt.imshow(opening)


# Second Masking
# Read Disparity Image
imagedisp = mpimg.imread('disparity.png')

imagedisp = imagedisp*255
imagedisp = imagedisp.astype(np.uint8)

# Create a disparity threshold
disp_threshold_min = 85
disp_threshold_max = 110

# mask from disparity
maskdisp = imagedisp.copy()

thresholds = ((imagedisp > disp_threshold_max) | (imagedisp < disp_threshold_min))
maskdisp[thresholds] = 0
maskdisp[~thresholds] = 255

# Display mask from disparity
plt.figure(4)
plt.imshow(maskdisp)

# Create a binary mask
ret, maskdisp = cv2.threshold(maskdisp, 200, 255, cv2.THRESH_BINARY)


print(opening.shape[0])
print(opening.shape[1])
print(maskdisp.shape[0])
print(maskdisp.shape[1])
print(opening.dtype)
print(maskdisp.dtype)
# combine two mask become one portion of mask
combination = cv2.bitwise_and(opening, maskdisp)

# Create an object from morphological closing
kernel = np.ones((100,100),np.uint8)
openingcomb = cv2.morphologyEx(combination, cv2.MORPH_CLOSE, kernel)
openingcomb = cv2.morphologyEx(openingcomb, cv2.MORPH_CLOSE, kernel)

# Display the masking combination and whole morphed object
plt.figure(3)
plt.subplot(121)
plt.imshow(combination)
plt.subplot(122)
plt.imshow(openingcomb)

# Change to uint8
combcover = openingcomb.astype(np.uint8)
print("This image is type")
print(combcover.dtype)

# Create a arrays of zeros
zeros = np.zeros((combcover.shape[0],combcover.shape[1],1), np.uint8)

# Create 'color' images from both grayscale images
imageleft_color = np.dstack((imageleft,imageleft,imageleft))
combcover_color = np.dstack((combcover,zeros,zeros))
blend = cv2.addWeighted(imageleft_color, 1, combcover_color, 0.5, 0)

# Display the mask and results of the program
plt.figure(5)
plt.subplot(121)
plt.imshow(combcover_color)
plt.subplot(122)
plt.imshow(blend)

# Show images
plt.show()