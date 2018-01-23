#!/usr/bin/python

import numpy as np
import cv2

def callback(x):
	pass

cv2.namedWindow('image')

img_index = 0
img_num = 310
img_nums = [310,386,288,289,330,346,347,365]
img_beg = "SPQR_Upper_"
img_home = "/home/egranadoo/"
img_path = img_home + "SPL/SPQR_Dataset/" + img_beg + str(img_num) + ".png"

img = cv2.imread(img_path)
im_gray = cv2.imread(img_path, cv2.IMREAD_GRAYSCALE)

ilowH = 0
ihighH = 179

ilowS = 0
ihighS = 255
ilowV = 0
ihighV = 255

# create trackbars for color change



while(True):
	frame = img
	hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

# 	# define range of blue color in HSV
	lower_black = np.array([0  ,0  , 60])
	upper_black = np.array([179,145,145])

	lower_white = np.array([0  , 0 , 116])
	upper_white = np.array([179, 87, 212])

#     # Threshold the HSV image to get only blue colors
	mask_1 = cv2.inRange(hsv, lower_black, upper_black)
	mask_2 = cv2.inRange(hsv, lower_white, upper_white)
# 	# Bitwise-AND mask and original image	
	# res_1 = cv2.bitwise_and(frame,frame, mask= mask_1)
	# res_2 = cv2.bitwise_and(frame,frame, mask= mask_2)
	kernel = np.ones((5,5), np.uint8)

	mask_1 = cv2.erode (mask_1, kernel, iterations=1)
	mask_1 = cv2.dilate(mask_1, kernel, iterations=1)
	mask_1 = cv2.erode (mask_1, kernel, iterations=1)
	mask_1 = cv2.dilate(mask_1, kernel, iterations=2)

	mask_2 = cv2.erode (mask_2, kernel, iterations=1)
	mask_2 = cv2.dilate(mask_2, kernel, iterations=1)
	mask_2 = cv2.erode (mask_2, kernel, iterations=1)
	mask_2 = cv2.dilate(mask_2, kernel, iterations=2)

	params = cv2.SimpleBlobDetector_Params()
	# params.filterByInertia = False
	params.filterByConvexity = False
	params.minThreshold = 10;    # the graylevel of images
	# params.maxThreshold = 200;
	
	# params.filterByColor = True
	# params.blobColor = 255
	
	# Filter by Area
	# params.filterByArea = True
	# params.minArea = 300
	detector = cv2.SimpleBlobDetector_create(params)

	mask_1 = cv2.bitwise_not(mask_1)
	mask_2 = cv2.bitwise_not(mask_2)
	# Detect blobs.
	keypoints_1 = detector.detect(mask_1)
	keypoints_2 = detector.detect(mask_2)

	mask_1 = cv2.bitwise_not(mask_1)
	mask_2 = cv2.bitwise_not(mask_2)

	im_with_keypoints_1 = cv2.drawKeypoints(mask_1, keypoints_1, np.array([]), (0,0,255), cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
	im_with_keypoints_2 = cv2.drawKeypoints(mask_2, keypoints_2, np.array([]), (0,0,255), cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)

	mask_3 = cv2.add(mask_1, mask_2)

	mask_3 = cv2.dilate(mask_3, kernel, iterations=2)
	mask_3 = cv2.erode (mask_3, kernel, iterations=2)
	

	mask_3 = cv2.bitwise_not(mask_3)
	# Detect blobs.
	keypoints_3 = detector.detect(mask_3)

	mask_3 = cv2.bitwise_not(mask_3)

	im_with_keypoints_3 = cv2.drawKeypoints(mask_3, keypoints_3, np.array([]), (0,0,255), cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
	frame = cv2.drawKeypoints(frame, keypoints_3, np.array([]), (0,0,255), cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
	# cv2.imshow('mask_1_orig',mask_1)

	# cv2.drawContours(mask_1, contours, -1, (0,255,0), 3)

	# res_3 = cv2.bitwise_and(mask_1, mask_2)


	cv2.imshow('frame',frame)
	# cv2.imshow('mask_1',mask_1)
	cv2.imshow('mask_1', im_with_keypoints_1)
	cv2.imshow('mask_2', im_with_keypoints_2)
	cv2.imshow('mask_3', im_with_keypoints_3)
	# cv2.imshow('mask_1_ero', mask_1_erosion)
	# cv2.imshow('mask_2',mask_2)
	# cv2.imshow('res',res_3)
	
	k = cv2.waitKey(0) & 0xFF
	print k
	if k == 27:
		break
	if k == 83 or k == 100:
		img_beg = "SPQR_Upper_"
		img_home = "/home/egranadoo/"
		img_path = img_home + "SPL/SPQR_Dataset/" + img_beg + str(img_nums[img_index]) + ".png"
		
		img = cv2.imread(img_path)
		img_index = (img_index + 1) % len(img_nums)
		print "Img", img_index, "of", len(img_nums)
	if k == 81:
		img_beg = "SPQR_Upper_"
		img_home = "/home/egranadoo/"
		img_path = img_home + "SPL/SPQR_Dataset/" + img_beg + str(img_nums[img_index]) + ".png"
		
		img = cv2.imread(img_path)
		img_index -= 1
		if img_index < 0:
			img_index = len(img_nums) - 1
		print "Img", str(img_index + 1), "of", len(img_nums)


cv2.destroyAllWindows()
    # # grab the frame
    # # ret, frame = cap.read()
    # frame = img
    # # get trackbar positions
    # ilowH = cv2.getTrackbarPos('lowH', 'image')
    # ihighH = cv2.getTrackbarPos('highH', 'image')
    # ilowS = cv2.getTrackbarPos('lowS', 'image')
    # ihighS = cv2.getTrackbarPos('highS', 'image')
    # ilowV = cv2.getTrackbarPos('lowV', 'image')
    # ihighV = cv2.getTrackbarPos('highV', 'image')

    # hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    # lower_hsv = np.array([ilowH, ilowS, ilowV])
    # higher_hsv = np.array([ihighH, ihighS, ihighV])
    # mask = cv2.inRange(hsv, lower_hsv, higher_hsv)

    # frame = cv2.bitwise_and(frame, frame, mask=mask)

    # # show thresholded image
    # cv2.imshow('image', frame)
    # k = cv2.waitKey(1000) & 0xFF # large wait time to remove freezing
    # if k == 113 or k == 27:
    #     break