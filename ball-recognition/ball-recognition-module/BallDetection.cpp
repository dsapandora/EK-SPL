#include "BallDetection.h"

#include <iostream>
#include <math.h>

#include <alcommon/albroker.h>
#include <alvalue/alvalue.h>
#include <alcommon/alproxy.h>
#include <qi/log.hpp>

//Video related includes
#include <althread/alcriticalsection.h>
#include <alproxies/alvideodeviceproxy.h>
#include <alvision/alimage.h>
#include <alvision/alvisiondefinitions.h>
#include <alerror/alerror.h>

//Log
#include <cstdlib>  //for atexit
#include <qi/log.hpp>

//CV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"
#include <opencv2/features2d/features2d.hpp>


#define PI 3.14159265

using namespace AL;
using namespace cv;
using namespace std; 

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

    cout << "BallDetection running!" << endl;
    fMemoryProxy = AL::ALMemoryProxy(getParentBroker());
    fMotionProxy = AL::ALMotionProxy(getParentBroker());
    fVideoDeviceProxy = AL::ALVideoDeviceProxy(getParentBroker());
    ////////////////////////////////////////////////////////////////////////////
    //Comenzaremos a hacer cambios aqui para buscar detectar pelotas

    // fState = fMemoryProxy.getData("redBallDetected");
    // fMemoryProxy.subscribeToEvent("redBallDetected", "BallDetection", "bwBallDetection");
    fVideoDeviceProxy.setParam(18, 1);
    // qi::log::init();
    // atexit(qi::log::destroy);
    while(true){
      bwBallDetection();
    }
    
    //fMemoryProxy.subscribeToEvent("LeftBumperPressed", "BallDetection", "LeftBumperPressed", "bwBallDetection");
  }
  catch (const AL::ALError& e) {
    qiLogError("BallDetection.init") << e.what() << std::endl;
  }
}

void BallDetection::bwBallDetection(){
  cout << "Finally some OpenCV!" << endl;
  //qiLogInfo("BallDetection.bwBallDetection") << "Executing method on red ball detected event" << std::endl;
  AL::ALCriticalSection section(fCallbackMutex);
  /////////////////////////////////////////////////////////////////////////////////////
  
  /** Create a proxy to ALVideoDevice on the robot.*/
  //ALVideoDeviceProxy cameraProxy("169.254.35.27", 9559);

  /** Subscribe a client image requiring 320*240 and BGR colorspace.*/
  const std::string clientName = fVideoDeviceProxy.subscribe("test", kQVGA, kBGRColorSpace, 30);
  cout << "clientName set" << endl;

  /** Create an cv::Mat header to wrap into an opencv image.*/
  //cv::Mat imgHeader = cv::Mat(cv::Size(320, 240), CV_8UC3);
  cout << "imgHeader set" << endl;

  /** Create a OpenCV window to display the images. */
  // cv::namedWindow("images");

  //ALValue img = fVideoDeviceProxy.getImageLocal(clientName);
  ALImage* img = (ALImage*) fVideoDeviceProxy.getImageLocal(clientName);
  cout << "img set" << endl;

  /** Access the image buffer (6th field) and assign it to the opencv image
  //* container. */
  //imgHeader.data = (uchar*) img[6].GetBinary();
  printf("the val is: %p\n", img);
  //ALValue aux = img->toALValue();
  unsigned char* dataPointer = img->getData();
  //imgHeader.data = img->getData();
  cv::Mat imgHeader = cv::Mat(320, 240, CV_8UC3, dataPointer);
  //imgHeader.data = dataPointer;
  //imgHeader.data = (uchar*) aux[6].GetBinary();
  //cout << imgHeader.data[6]  << endl;
  cout << "access buffer" << endl;
  // qiLogInfo("BallDetection.bwBallDetection") << "Getting image" << std::endl;

  /** Tells to ALVideoDevice that it can give back the image buffer to the
    * driver. Optional after a getImageRemote but MANDATORY after a getImageLocal.*/
  //fVideoDeviceProxy.releaseImage(clientName);
  cout << "release image" << endl;

  /** Display the iplImage on screen.*/
  //   cv::imshow("images", imgHeader);

  /** Cleanup.*/
  //fVideoDeviceProxy.unsubscribe(clientName);
  cout << "unsubscribe from camera" << endl;

  AL::ALValue value;

  String img_path = "/home/nao/test.jpg";

  // //-----------------------------------------------------------------------

  // //imread should take the NAO's camera as input
  // //Mat img = imread(img_path);
  //Mat img = imgHeader;
  //Mat im_gray = imread(img_path, CV_LOAD_IMAGE_GRAYSCALE); 

  Mat frame = imgHeader;
  //Mat frame = imread(img_path);
  int theType = frame.type();
  cout << "Frame type: " << theType << endl;
  cout << "Frame set " << endl;
  //cout << "Frame size= " << frame.size() << endl;
  Mat hsv;
  cvtColor(frame, hsv, CV_BGR2HSV); 
  cout << "HSV set" << endl;
  
  //Threshold values are determined with calibration code
  vector<int> lower_black = {73 ,0 , 10}; 
  vector<int> upper_black = {147,86,115}; 

  vector<int> lower_white = {0 , 0 , 138}; 
  vector<int> upper_white = {158, 48, 255}; 

  vector<int> lower_green = {20 , 50, 34}; 
  vector<int> upper_green = {65, 197, 213}; 

  vector<int> lower_lines = {0, 4, 208};
  vector<int> upper_lines = {179, 73, 255};


  Mat mask_1, mask_2, mask_green, mask_lines;

  //Threshold the HSV image to get only important colors
  inRange(hsv, lower_black, upper_black, mask_1);

  inRange(hsv, lower_white, upper_white, mask_2); 

  inRange(hsv, lower_green, upper_green, mask_green); 

  inRange(hsv, lower_lines, upper_lines, mask_lines); 

  cout << "Masks set" << endl;

  Mat kernel = Mat::ones(5,5,CV_8U);

  //Th rectangular structuring element considers Size(columns,rows)
  //Mat kernel_field = getStructuringElement(MORPH_RECT, Size(7,5));
  Mat kernel_field = cv::getStructuringElement(MORPH_RECT, Size(5,3));

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
  
  SimpleBlobDetector detector(params);
  // cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params);

  bitwise_not(mask_1, mask_1);
  bitwise_not(mask_2, mask_2);

  vector<KeyPoint> keypoints_1;
  vector<KeyPoint> keypoints_2;
  vector<KeyPoint> keypoints_3;

  detector.detect(mask_1, keypoints_1);
  detector.detect(mask_2, keypoints_2);

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
  detector.detect(mask_3, keypoints_3);
  //cout << "Number of keypoints: " << keypoints_3.size() << endl;

  float x_rad, y_rad;

  value.arrayPush("Time");

  if(keypoints_3.size()==0){

    cout << "No keypoints detected" << endl;
    x_rad = 30 * PI / 180;
    y_rad = 20 * PI / 180;
    vector<float> val = {x_rad, y_rad}; 
    value.arrayPush(val);

  }else{
    cout << "Keypoints detected" << endl;
    //Conversion from keypoint 0 (v serves as a mask to indicate which keypoint) to points
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
    x_rad = atan2(keyY,keyX);
    float x_ang = x_rad * 180 / PI;
  //Camera's HFOV for NAO v4.0 is 60.97°
  //DFOV 72.6°, HFOV 60.9°, VFOV 47.6°
  //Linear relation from pixels to angles.
    float y_ang = -0.095 * keyX + 30.485;
    y_rad = y_ang * PI / 180;

    cout << "Angular (degrees) NAOqi coordinates CenterX: " << x_ang << " CenterY: " << y_ang << endl;
    cout << "Angular (radians) NAOqi coordinates CenterX: " << x_rad << " CenterY: " << y_rad << endl;

    vector<float> val = {x_rad, y_rad}; 
    value.arrayPush(val);

  }

  fVideoDeviceProxy.releaseImage(clientName);
  fVideoDeviceProxy.unsubscribe(clientName);

  // qiLogInfo("BallDetection.bwBallDetection") << "CenterX: " << x_rad << std::endl;
  // qiLogInfo("BallDetection.bwBallDetection") << "CenterY: " << y_rad << std::endl;

  //The values used by vision.cpp are the angular coordinates in radians

  //-----------------------------------------------------------------------

  generateMicroEventBwBallDetected(value);

}

void BallDetection::generateMicroEventBwBallDetected(const AL::ALValue& value) {
  fMemoryProxy.raiseMicroEvent("bwBallDetected", value);
}