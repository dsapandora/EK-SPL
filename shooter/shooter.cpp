#include "shooter.h"

#include <alvalue/alvalue.h>
#include <alcommon/alproxy.h>

#include <iostream>
#include <alcommon/albroker.h>
#include <althread/alcriticalsection.h>

#include <qi/log.hpp>


Shooter::Shooter(boost::shared_ptr<AL::ALBroker> broker,
                   const std::string& name)
  : AL::ALModule(broker, name),
  fCallbackMutex(AL::ALMutex::createALMutex())

{
  setModuleDescription("FollowBall module");

  functionName("ballDetected", getName(), "Guarda en variable");
  BIND_METHOD(Shooter::ballDetected);

  functionName("leftBumperPressed", getName(), "Hace penal");
  BIND_METHOD(Shooter::leftBumperPressed);
}

Shooter::~Shooter()
{
  fMemoryProxy.unsubscribeToMicroEvent("EKBallDetected", "Shooter");
  fMemoryProxy.unsubscribeToEvent("LeftBumperPressed", "Shooter");
}

void Shooter::init()
{
  try {
    fMemoryProxy = AL::ALMemoryProxy(getParentBroker());
    fMotionProxy = AL::ALMotionProxy(getParentBroker());
    fFrameManagerProxy = AL::ALFrameManagerProxy(getParentBroker());
    //fMemoryProxy.subscribeToMicroEvent("EKBallDetected", "Shooter", "EKBallDetected", "ballDetected");
    fMemoryProxy.subscribeToEvent("LeftBumperPressed", "Shooter", "LefttBumperPressed", "leftBumperPressed");
    fMotionProxy.setStiffnesses("Head", 0.7);
    fMotionProxy.setStiffnesses("Body", 0.7);
    fPostureProxy.goToPosture("StandInit", 0.5f);
  }
  catch (const AL::ALError& e) {
    qiLogError("shooter.init") << e.what() << std::endl;
  }
}

void Shooter::leftBumperPressed()
{
  fMemoryProxy.subscribeToMicroEvent("EKBallDetected", "Shooter", "EKBallDetected", "ballDetected");
}

void Shooter::centerBall()
{
    if(fState.getSize() > 0)
    {
      fMotionProxy.setAngles("Head", fState[1], 0.4);
    }
}

void Shooter::walkToBall()
{


  //fMotionProxy.setWalkTargetVelocity((float)fState[3][0],(float)fState[3][1],(float)fState[3][2],0.8);
  //fMotionProxy.moveTo((float)fState[2][0]*0.01-0.15, (float)fState[2][1]*0.01+0.05, (float)fState[2][2]);
}

void Shooter::shoot()
{
  std::string behaviorID;
  behaviorID = fFrameManagerProxy.newBehaviorFromFile("/home/nao/kick.xar", "");
  fFrameManagerProxy.completeBehavior(behaviorID);
}

void Shooter::ballDetected()
{
  AL::ALCriticalSection section(fCallbackMutex);
  fState =  fMemoryProxy.getData("EKBallDetected");


  fMotionProxy.setAngles("Head", fState[1], 0.4);
    if((float)fState[0] > 17)
    {
      fMotionProxy.setWalkTargetVelocity((float)fState[3][0],(float)fState[3][1],(float)fState[3][2],0.1);
    }
    else
    {
        if ((float)fState[2][2] > 1)
        {
          fMotionProxy.setWalkTargetVelocity(0, 0, 1.0, 0.1);
        }
        else if((float)fState[2][2] < -1)
        {
          fMotionProxy.setWalkTargetVelocity(0, 0, -1.0, 0.1);
        }
        else
        {
          if(abs((float)fState[2][2]) < 0.08)
          {
            fMemoryProxy.unsubscribeToMicroEvent("EKBallDetected", "Shooter");
            fMotionProxy.moveTo(0, 0.04, 0);
            shoot();
          }
        }
    }
}