#include "BallDetection.h"

#include <iostream>
#include <math.h>

#include <alcommon/albroker.h>
#include <alvalue/alvalue.h>
#include <alcommon/alproxy.h>
#include <qi/log.hpp>
#include <althread/alcriticalsection.h>

BallDetection::BallDetection(boost::shared_ptr<AL::ALBroker> broker, const std::string& name)
: AL::ALModule(broker, name), fCallbackMutex(AL::ALMutex::createALMutex())
{
  setModuleDescription("Module for black and white ball detection.");
  ///////////////////////////////////////////////////////////////////////////////////////
  functionName("bwBallDetection", getName(), "Method to detect black and white ball.");
  BIND_METHOD(BallDetection::bwBallDetection)
  void bwBallDetection();
}

BallDetection::~BallDetection()
{
  fMemoryProxy.unsubscribeToEvent("bwBallDetection", "BallDetection");
}

void BallDetection::init()
{
  try {
    fMemoryProxy = AL::ALMemoryProxy(getParentBroker());
    fMotionProxy = AL::ALMotionProxy(getParentBroker());
    fVideoDeviceProxy = AL::ALVideoDeviceProxy(getParentBroker());
    ////////////////////////////////////////////////////////////////////////////
    //Comenzaremos a hacer cambios aqui para buscar detectar pelotas

    fState = fMemoryProxy.getData("redBallDetected");
    fMemoryProxy.subscribeToEvent("redBallDetected", "BallDetection", "bwBallDetection");
    fVideoDeviceProxy.setParam(18, 1);
  }
  catch (const AL::ALError& e) {
    qiLogError("BallDetection.init") << e.what() << std::endl;
  }
}

void BallDetection::bwBallDetection(){
  //qiLogInfo("BallDetection.bwBallDetection") << "Executing method on red ball detected event" << std::endl;
  AL::ALCriticalSection section(fCallbackMutex);
  /////////////////////////////////////////////////////////////////////////////////////
  
  //Use fState to get image from camera
  fState =  fMemoryProxy.getData("redBallDetected");

  AL::ALValue value;

  //-----------------------------------------------------------------------

  //imread should take the NAO's camera as input
  Mat img = imread(img_path);
  Mat im_gray = imread(img_path, CV_LOAD_IMAGE_GRAYSCALE); 

  Mat frame = img;
  Mat hsv; 
  cvtColor(frame, hsv, CV_BGR2HSV); 
  
  //Threshold values are determined with calibration code
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
  //cout << "Number of keypoints: " << keypoints_3.size() << endl;

  //Convertion from keypoint 0 (v serves as a mask to indicate which keypoint) to points
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

  //The values used by vision.cpp are the angular coordinates in radians
  value.arrayPush(x_rad);
  value.arrayPush(y_rad);

  //-----------------------------------------------------------------------

  generateMicroEventBwBallDetected(value);
}

void BallDetection::generateMicroEventBwBallDetected(const AL::ALValue& value) {
  fMemoryProxy.raiseMicroEvent("bwBallDetected", value);
}