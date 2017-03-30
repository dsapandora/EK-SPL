#include "vision.h"

#include <iostream>
#include <math.h>

#include <alcommon/albroker.h>
#include <alvalue/alvalue.h>
#include <alcommon/alproxy.h>
#include <qi/log.hpp>
#include <althread/alcriticalsection.h>

Vision::Vision(boost::shared_ptr<AL::ALBroker> broker, const std::string& name)
  : AL::ALModule(broker, name), fCallbackMutex(AL::ALMutex::createALMutex())
{
  setModuleDescription("Module for vision.");
  ///////////////////////////////////////////////////////////////////////////////////////
  functionName("onBallDetected", getName(), "Method called when the ball is detected.");
  BIND_METHOD(Vision::onBallDetected)
  void onBallDetected();
}

Vision::~Vision()
{
  fMemoryProxy.unsubscribeToEvent("onBallDetected", "Vision");
}

void Vision::init()
{
  try {
    fMemoryProxy = AL::ALMemoryProxy(getParentBroker());
    fMotionProxy = AL::ALMotionProxy(getParentBroker());
    fVideoDeviceProxy = AL::ALVideoDeviceProxy(getParentBroker());
    ////////////////////////////////////////////////////////////////////////////
    //Comenzaremos a hacer cambios aqui para buscar detectar pelotas

    fState = fMemoryProxy.getData("redBallDetected");
    fMemoryProxy.subscribeToEvent("redBallDetected", "Vision", "onBallDetected");
    fVideoDeviceProxy.setParam(18, 1);
  }
  catch (const AL::ALError& e) {
    qiLogError("vision.init") << e.what() << std::endl;
  }
}

void Vision::onBallDetected(){
  //qiLogInfo("vision.onBallDetected") << "Executing method on red ball detected event" << std::endl;
  AL::ALCriticalSection section(fCallbackMutex);
  headValues = fMotionProxy.getAngles("Head", true);
  /////////////////////////////////////////////////////////////////////////////////////
  fState =  fMemoryProxy.getData("redBallDetected");

  AL::ALValue value;
  

  // Variable que dice a donde mover la cabeza para centrar la pelota.
  std::vector<float> nextHeadValues(2, 0);
  nextHeadValues[0] = -(fVideoDeviceProxy.getImageInfoFromAngularInfo(1, fState[1])[0] - 0.5) + headValues[0]; 
  nextHeadValues[1] = (fVideoDeviceProxy.getImageInfoFromAngularInfo(1, fState[1])[1] - 0.5) + headValues[1];

  // Variable que calcula la distancia a la pelota, asumiendo que está en el suelo.
  float distanceToBall = 46 * tan(3.1416 / 4 - nextHeadValues[1]);

  // Variable para posición de pelota respecto a robot.
  std::vector<float> XYT(3,0);
  XYT[0] = cos(nextHeadValues[0]) * distanceToBall;
  XYT[1] = sin(nextHeadValues[0]) * distanceToBall;
  XYT[2] = nextHeadValues[0];

  // Variable para velocidad normalizada hacia la pelota respecto a robot.
  std::vector<float> uXYT(3,0);
  float norma = sqrt(XYT[0] * XYT[0] + XYT[1] * XYT[1]);
  uXYT[0] = XYT[0] / norma;
  uXYT[1] = XYT[1] / norma;
  uXYT[2] = nextHeadValues[0] / 2.09;


  value.arrayPush(distanceToBall);
  value.arrayPush(nextHeadValues);
  value.arrayPush(XYT);
  value.arrayPush(uXYT);
  value.arrayPush(fState[0]);

  generateMicroEventBallDetected(value);
}

void Vision::generateMicroEventBallDetected(const AL::ALValue& value) {
  fMemoryProxy.raiseMicroEvent("EKBallDetected", value);
}


#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;

/** @function main */
int main(int argc, char** argv)
{
  Mat src, src_gray;

  /// Read the image
  src = imread( argv[1], 1 );

  if( !src.data )
    { return -1; }

  /// Convert it to gray
  cvtColor( src, src_gray, CV_BGR2GRAY );

  /// Reduce the noise so we avoid false circle detection
  GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );

  vector<Vec3f> circles;

  /// Apply the Hough Transform to find the circles
  HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows/8, 200, 100, 0, 0 );

  /// Draw the circles detected
  for( size_t i = 0; i < circles.size(); i++ )
  {
      Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
      int radius = cvRound(circles[i][2]);
      // circle center
      circle( src, center, 3, Scalar(0,255,0), -1, 8, 0 );
      // circle outline
      circle( src, center, radius, Scalar(0,0,255), 3, 8, 0 );
   }

  /// Show your results
  namedWindow( "Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE );
  imshow( "Hough Circle Transform Demo", src );

  waitKey(0);
  return 0;
}