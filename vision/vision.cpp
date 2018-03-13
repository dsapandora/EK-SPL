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
  // nextHeadValues[0] = -(fVideoDeviceProxy.getImageInfoFromAngularInfo(1, fState[1])[0] - 0.5) + headValues[0]; 
  // nextHeadValues[1] = (fVideoDeviceProxy.getImageInfoFromAngularInfo(1, fState[1])[1] - 0.5) + headValues[1];
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