//import numpy as np 
#include "opencv2/opencv.hpp"

using namespace std; 
using namespace cv; 
//def callback(x): //	pass 
int main(int argc, char** argv){ 

    int img_index = 0; 
    int img_num = 346; 
    int img_nums[] = {310,386,288,289,330,346,347,365}; 
    String img_beg = "SPQR_Upper_"; 
    String img_home = "/home/htellezb/"; 
    String img_path = img_home + "SPQR_Dataset/" + img_beg + to_string(img_num) + ".png"; 


    Mat img = imread(img_path);
    Mat im_gray = imread(img_path, CV_LOAD_IMAGE_GRAYSCALE); 
    
    Mat frame = img;
    Mat hsv; 
    cvtColor(frame, hsv, CV_BGR2HSV); 
        //define range of blue color in HSV 
    vector<int> lower_black = {0 ,0 , 60}; 
    vector<int> upper_black = {179,145,145}; 

    vector<int> lower_white = {0 , 0 , 116}; 
    vector<int> upper_white = {179, 63, 212}; 

    vector<int> lower_green = {84 , 155, 74}; 
    vector<int> upper_green = {115, 214, 190}; 

    vector<int> lower_lines = {68, 0, 219}; 
    vector<int> upper_lines = {155, 100, 255}; 


    Mat mask_1, mask_2, mask_green, mask_lines;
        //Threshold the HSV image to get only important colors
    inRange(hsv, lower_black, upper_black, mask_1);

    inRange(hsv, lower_white, upper_white, mask_2); 

    inRange(hsv, lower_green, upper_green, mask_green); 

    inRange(hsv, lower_lines, upper_lines, mask_lines); 


        //Bitwise-AND mask and original image 
        // # res_1 = cv2.bitwise_and(frame,frame, mask= mask_1) 
        // # res_2 = cv2.bitwise_and(frame,frame, mask= mask_2) 
        // # normal kernel. TODO: maybe use a kernel to dilate green only by the sides and not up??? 


    Mat kernel = Mat::ones(5,5,CV_8U);

    //float kdata[] = {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0};
    //Mat kernel_field(5,7,CV_8U,kdata);
    //Mat kernel_field = (Mat_<double>(5,8) << 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0);
    //Mat kernel_field(5,7,CV_8U)

    //Th rectangular structuring element considers Size(columns,rows)
    //Mat kernel_field = getStructuringElement(MORPH_RECT, Size(7,5));
    Mat kernel_field = getStructuringElement(MORPH_RECT, Size(5,3));

    Point p = Point(-1,-1);

    erode (mask_1, mask_1, kernel, p, 1);
    dilate(mask_1, mask_1, kernel, p, 1); 
    erode (mask_1, mask_1, kernel, p, 1); 
    dilate(mask_1, mask_1, kernel, p, 2);

    erode (mask_2, mask_2, kernel, p, 1);
    dilate(mask_2, mask_2, kernel, p, 1);
    erode (mask_2, mask_2, kernel, p, 1);
    dilate(mask_2, mask_2, kernel, p, 2);

    //imshow("mask_green_pre",mask_green);

    erode (mask_green, mask_green, kernel, p, 1);
    dilate (mask_green, mask_green, kernel, p, 1);
    //imshow("mask_green_erdil1",mask_green);
    dilate(mask_green, mask_green, kernel_field, p, 20);
    //imshow("mask_green_dil20",mask_green);
    erode (mask_green, mask_green, kernel_field, p, 20);


        //# cv2.imshow("m1-presub",mask_1) 
        //# cv2.imshow("m2-presub",mask_2) 

    subtract(mask_1, mask_lines, mask_1);
    subtract(mask_2, mask_lines, mask_2);

        //# cv2.imshow("m1-possub",mask_1) 
        //# cv2.imshow("m2-possub",mask_2) 


    erode (mask_1, mask_1, kernel, p, 1);
    dilate(mask_1, mask_1, kernel, p, 1);
    erode (mask_2, mask_2, kernel, p, 1);
    dilate(mask_2, mask_2, kernel, p, 1);


        /*# cv2.imshow("pre-erode", mask_lines) 
        # mask_lines = cv2.dilate(mask_lines, kernel, iterations = 1) 
        # mask_lines = cv2.erode (mask_lines, kernel, iterations = 1) 
        # cv2.imshow("post-erode", mask_lines) 
        # mask_1 = cv2.bitwise_or(mask_1, mask_1, mask = mask_green) 
        # mask_2 = cv2.bitwise_or(mask_2, mask_2, mask = mask_green) */


    SimpleBlobDetector::Params params;

        //# params.filterByInertia = False 
    params.filterByConvexity = false;
    params.minThreshold = 10; 

        /*# the graylevel of images 
        # params.maxThreshold = 200; 
        # params.filterByColor = True 
        # params.blobColor = 255 
        # Fiter by Area 
        # params.filterByArea = True 
        # params.minArea = 300 
        */


    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

    bitwise_not(mask_1, mask_1);
    bitwise_not(mask_2, mask_2);

        //# Detect blobs. 

    vector<KeyPoint> keypoints_1;
    vector<KeyPoint> keypoints_2;
    vector<KeyPoint> keypoints_3;

    detector->detect(mask_1, keypoints_1);
    detector->detect(mask_2, keypoints_2);


    bitwise_not(mask_1, mask_1);
    bitwise_not(mask_2, mask_2);

    Mat im_with_keypoints_1;
    Mat im_with_keypoints_2;
    Mat im_with_keypoints_3;

    drawKeypoints(mask_1, keypoints_1, im_with_keypoints_1, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    drawKeypoints(mask_2, keypoints_2, im_with_keypoints_2, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    Mat mask_3;

    add(mask_1, mask_2, mask_3);
    bitwise_and(mask_3, mask_green, mask_3);

        //# mask_3 = cv2.dilate(mask_3, kernel, iterations=2) 
        //# mask_3 = cv2.erode (mask_3, kernel, iterations=2) 

    bitwise_not(mask_3, mask_3);

        //# Detect blobs. 
    detector->detect(mask_3, keypoints_3);

    bitwise_not(mask_3, mask_3); 
    drawKeypoints(mask_3, keypoints_3, im_with_keypoints_3, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    drawKeypoints(frame, keypoints_3, frame, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

         /*# cv2.imshow('mask_1_orig',mask_1) 
         # cv2.drawContours(mask_1, contours, -1, (0,255,0), 3) 
         # res_3 = cv2.bitwise_and(mask_1, mask_2) 
         */

        //# cv2.imshow('mask_1',mask_1) 

    imshow("mask_1", im_with_keypoints_1); 
    imshow("mask_2", im_with_keypoints_2); 
    imshow("mask_3", im_with_keypoints_3); 
    imshow("mask_green", mask_green);
    imshow("frame", frame);

    int k = waitKey(0);

    if(k=27){
        destroyAllWindows();
    }

        //# cv2.imshow('mask_1_ero', mask_1_erosion) 
        //# cv2.imshow('mask_2',mask_2) 
        //# cv2.imshow('res',res_3) 
        // k = cv2.waitKey(0) & 0xFF print k if k == 27: break if k == 83 or k == 100: img_beg = "SPQR_Upper_" 
        //         img_home = "/home/egranadoo/" 
        //         img_path = img_home + "SPL/SPQR_Dataset/" + img_beg + str(img_nums[img_index]) + ".png" 
        //         img = cv2.imread(img_path) 
        //         img_index = (img_index + 1) % len(img_nums) 
        //         print "Img", img_index, "of", len(img_nums) 
        //         if k == 81: img_beg = "SPQR_Upper_" 
        //                 img_home = "/home/egranadoo/" 
        //                 img_path = img_home + "SPL/SPQR_Dataset/" + img_beg + str(img_nums[img_index]) + ".png" 
        //                 img = cv2.imread(img_path) 
        //                 img_index -= 1 if img_index < 0: img_index = len(img_nums) - 1 
        //                         print "Img", str(img_index + 1), "of", len(img_nums)  

    return 0;
}
