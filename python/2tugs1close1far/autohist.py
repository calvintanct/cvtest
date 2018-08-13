import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np
import cv2


def nothing(x):
  pass

image = mpimg.imread('disparity.png')

image = image*255
image = image.astype(np.uint8)

print("This image is type")
print(image.dtype)

plt.figure(1)

# Create a histogram of image
histr = cv2.calcHist([image],[0],None,[256],[0,256])

# Display the Histogram Plot
plt.plot(histr, 'r')
plt.xlim([0,256])

# Display the original image 
plt.figure(2)
plt.imshow(image, cmap='gray')

# Set threshold for number of pixels
pixel_thresh=5000

xlist = []
for i in range(0, histr.shape[0]):
	if(histr[i]>pixel_thresh):
		xlist.append(i)

# Take last 10,5 or 2 disparity values that has more than threshold number of pixels
if (len(xlist)>10):
	xlist = xlist[-10:]
elif(len(xlist)>5):
	xlist = xlist[-5:]
else:
	xlist = xlist[-2:]

# print the candidates
print(xlist)
size = len(xlist)

# Create a disparity threshold
for i in range(size):
	diff = xlist[size-1]-xlist[i]
	if diff < 20:
		disp_threshold_min = xlist[i]
		break
		
disp_threshold_max = xlist[len(xlist)-1]

print(disp_threshold_min)
print(disp_threshold_max)

# Display the image
plt.show()