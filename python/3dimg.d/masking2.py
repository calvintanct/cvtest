import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np
import cv2

image = mpimg.imread('tugdisparity.png')

image = image*255
image = image.astype(np.uint8)

print("This image is type")
print(image.dtype)

plt.figure(1)


histr = cv2.calcHist([image],[0],None,[256],[0,256])
# Display the Histogram Plot
plt.plot(histr, 'r')
plt.xlim([0,256])

# Display the original image 
plt.figure(2)
plt.imshow(image, cmap='gray')

# Create a disparity threshold
disp_threshold = 44

mask = image.copy()

# Identify pixels below the threshold
thresholds = (image < disp_threshold)
mask[thresholds] = 0
mask[~thresholds] = 255

# Create 'color' disparity image
results =np.dstack((image,image,image))
results = cv2.addWeighted(results, 5, results, 0, 0)

# Create 'color' mask image
color_mask = np.dstack((mask,mask,mask))
color_mask[~thresholds] = [255,0,0]

# Display the mask image
plt.figure(3)                 
plt.imshow(mask, cmap='gray')

# Display the color mask image
plt.figure(4)                 
plt.imshow(color_mask)

# Display the color mask image
plt.figure(5)                 
plt.imshow(results)

# Blend the red masking inside the original image
blend = results.copy()
blend = cv2.addWeighted(results, 1, color_mask, 1, 0)
blend[~thresholds]= blend[~thresholds]*[1,0.5,0.5]

# Display the blend image
plt.figure(6)                 
plt.imshow(blend)

# Display the image
plt.show()
