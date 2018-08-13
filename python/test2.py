import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np
import cv2

image = mpimg.imread('blue.png')

gray = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)

kernel_size = 3
blur_gray = cv2.GaussianBlur(gray,(kernel_size, kernel_size), 0)

low_threshold = 10
high_threshold = 50
edges = cv2.Canny(blur_gray, low_threshold, high_threshold)

# Display the image

plt.figure()
plt.imshow(edges, cmap='gray')

plt.show()


plt.figure()
plt.imshow(gray, cmap='gray')

plt.show()