import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np
import cv2

image = mpimg.imread('blue.png')

image = image*255
image = image.astype(np.uint8)

print("This image is type")
print(image.dtype)

plt.figure(1)
color = ('r','g','b')
for i,col in enumerate(color):
    histr = cv2.calcHist([image],[i],None,[256],[0,256])
    # Display the Histogram Plot
    plt.plot(histr,color = col)
    plt.xlim([0,256])
    # plt.show()

# Display the original image 
plt.figure(2)
plt.imshow(image)
# plt.show()

red_threshold = 0
green_threshold = 140
blue_threshold = 0
rgb_threshold = [red_threshold, green_threshold, blue_threshold]

results = image.copy()

# Identify pixels below the threshold
thresholds = (image[:,:,0] < rgb_threshold[0]) | (image[:,:,1] < rgb_threshold[1]) | (image[:,:,2] < rgb_threshold[2])
image[thresholds] = [0,0,0]
image[~thresholds] = [255,0,0]

blend = image.copy()
blend = cv2.addWeighted(image, 1, results, 1, 0)

# Blend the red masking inside the original image
blend[~thresholds]= blend[~thresholds]*[1,0.5,0.5]

results[~thresholds]=image[~thresholds]


# Display the image
plt.figure(3)                 
plt.imshow(results)

plt.figure(4)                 
plt.imshow(blend)
plt.show()
