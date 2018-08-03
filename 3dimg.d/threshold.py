import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np
import cv2


def nothing(x):
  pass

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

disp_threshold_min = 42
disp_threshold_max = 46

cv2.namedWindow('Thresholdbars')
cv2.createTrackbar("Distance","Thresholdbars",5,250,nothing)

while(1):
	k = cv2.waitKey(1) & 0xFF
	if k == 27:
		break
	
	number=cv2.getTrackbarPos("Distance", "Thresholdbars")
	disp_threshold_max = number + 5
	disp_threshold_min = number - 5


	mask = image.copy()
   
   	# Identify unaccepted pixels the threshold
	thresholds = ((image > disp_threshold_max) | (image < disp_threshold_min))
	mask[thresholds] = 0
	mask[~thresholds] = 255

	# Create 'color' disparity image
	results =np.dstack((image,image,image))
	results = cv2.addWeighted(results, 5, results, 0, 0)

	# Create 'color' mask image
	color_mask = np.dstack((mask,mask,mask))
	color_mask[~thresholds] = [255,0,0]

	# # Display the mask image
	# plt.figure(3)                 
	# plt.imshow(mask, cmap='gray')

	# # Display the color mask image
	# plt.figure(4)                 
	# plt.imshow(color_mask)

	# # Display the color mask image
	# plt.figure(5)                 
	# plt.imshow(results)

	cv2.imshow("color_mask", color_mask)
	# cv2.imshow("results", results)

	# Blend the red masking inside the original image
	blend = results.copy()
	blend = cv2.addWeighted(results, 1, color_mask, 1, 0)
	blend[~thresholds]= blend[~thresholds]*[1,0.5,0.5]


	# # Display the blend image
	# plt.figure(6)                 
	# plt.imshow(blend)
	cv2.imshow("blend", blend)

	# # Display the image
	# plt.show()

cv2.destroyAllWindows()