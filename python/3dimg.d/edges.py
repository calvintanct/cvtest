import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np
import cv2


image = mpimg.imread('Left.png')

image = image*255
image = image.astype(np.uint8)

print("This image is type")
print(image.dtype)

# Display the original image 
# plt.figure(1)
# plt.imshow(image, cmap='gray')

# Define a kernel size and apply Gaussian smoothing
kernel_size = 9
blur_gray = cv2.GaussianBlur(image,(kernel_size, kernel_size),0)

# Display the original image 
plt.subplot(221)
plt.imshow(blur_gray, cmap='gray')

# Define our parameters for Canny and apply
low_threshold = 10
high_threshold = 100
edges = cv2.Canny(blur_gray, low_threshold, high_threshold)

low_threshold = 100
high_threshold = 150
edges2 = cv2.Canny(blur_gray, low_threshold, high_threshold)

low_threshold = 10
high_threshold = 80
edges3 = cv2.Canny(blur_gray, low_threshold, high_threshold)

# Display the edges image
plt.subplot(222)
plt.imshow(edges, cmap='gray')

plt.subplot(223)
plt.imshow(edges2, cmap='gray')

plt.subplot(224)
plt.imshow(edges3, cmap='gray')

# Morphological image
ret, mask = cv2.threshold(edges3, 200, 255, cv2.THRESH_BINARY)

plt.figure(2)
plt.subplot(121)
plt.imshow(mask)
kernel = np.ones((3,3),np.uint8)
dilation = cv2.dilate(mask,kernel,iterations = 1)
opening = cv2.morphologyEx(dilation, cv2.MORPH_OPEN, kernel)
plt.subplot(122)
plt.imshow(opening)

# Show images
plt.show()