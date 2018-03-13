//Code to recognize a black and white ball in a football environment given
//certain color thresholds.

#include <iostream>
#include <math.h>

#include "opencv2/opencv.hpp"
#define PI 3.14159265

using namespace std; 
using namespace cv; 

int main(int argc, char** argv){ 

    int img_index = 0; 
    int img_num = 365; 
    int img_nums[] = {310,386,288,289,330,346,347,365}; 
    String img_beg = "SPQR_Upper_"; 
    String img_home = "/home/htellezb/"; 
    String img_path = img_home + "SPQR_Dataset/" + img_beg + to_string(img_num) + ".png"; 
    String img_path = "/home/htellezb/Pictures/bola.jpg";

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

    erode (mask_green, mask_green, kernel, p, 1);
    dilate (mask_green, mask_green, kernel, p, 1);

    dilate(mask_green, mask_green, kernel_field, p, 20);
    erode (mask_green, mask_green, kernel_field, p, 20);

    subtract(mask_1, mask_lines, mask_1);
    subtract(mask_2, mask_lines, mask_2);

    erode (mask_1, mask_1, kernel, p, 1);
    dilate(mask_1, mask_1, kernel, p, 1);
    erode (mask_2, mask_2, kernel, p, 1);
    dilate(mask_2, mask_2, kernel, p, 1);

    SimpleBlobDetector::Params params;

    params.filterByConvexity = false;
    params.minThreshold = 10; 

    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

    bitwise_not(mask_1, mask_1);
    bitwise_not(mask_2, mask_2);

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

    bitwise_not(mask_3, mask_3);

        //# Detect blobs. 
    detector->detect(mask_3, keypoints_3);
    //cout << "Keypoint size: " << keypoints_3.size() << endl;

    //Convertion from keypoint 0 (v) to points
    vector<cv::Point_<float>> points;
    vector<int> v {0};
    cv::KeyPoint::convert(keypoints_3,points,v);
    cout << "KeyPoint coordinates x: " << points.at(0).x << " y: " << points.at(0).y << endl;
    
    //Convertion from pixels to angular coordinates as explained on AlRedBallDetection->BallInfo->centerX,centerY
    //Get frame size and set center
    Size size = frame.size();
    cout << "Image size x: " << size.width << " y: " << size.height << endl;
    float cX = size.width / 2.0;
    float cY = size.height / 2.0;
    //Translation to match NAOqi coordinate system
    float keyX = -(points.at(0).x - cX);
    float keyY = points.at(0).y - cY;
    cout << "KeyPoint NAOqi coordinates x: " << keyX << " y: " << keyY << endl;
    //Pixels->angular coordniates using trigonometry for x_ang and camera's HFOV for y_ang 
    float x_rad = atan2(keyY,keyX);
    float x_ang = x_rad * 180 / PI;
    //Camera's HFOV for NAO v4.0 is 60.97°
    //DFOV 72.6°, HFOV 60.9°, VFOV 47.6°
    //Linear relation from pixels to angles.
    float y_ang = -0.095 * keyX + 30.485;
    float y_rad = y_ang * PI / 180;

    cout << "Angular (degrees) NAOqi coordinates CenterX: " << x_ang << " CenterY: " << y_ang << endl;
    cout << "Angular (radians) NAOqi coordinates CenterX: " << x_rad << " CenterY: " << y_rad << endl;

    bitwise_not(mask_3, mask_3); 
    drawKeypoints(mask_3, keypoints_3, im_with_keypoints_3, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    drawKeypoints(frame, keypoints_3, frame, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

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
