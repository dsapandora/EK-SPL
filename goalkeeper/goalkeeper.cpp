#include "goalkeeper.h"

#include <alvalue/alvalue.h>
#include <alcommon/alproxy.h>

#include <iostream>
#include <alcommon/albroker.h>
#include <althread/alcriticalsection.h>

#include <qi/log.hpp>

Goalkeeper::Goalkeeper(boost::shared_ptr<AL::ALBroker> broker,
                   const std::string& name)
  : AL::ALModule(broker, name),
  fCallbackMutex(AL::ALMutex::createALMutex())
{
  setModuleDescription("FollowBall module");

  functionName("ballDetected", getName(), "Guarda en variable");
  BIND_METHOD(Goalkeeper::ballDetected);

  functionName("leftBumperPressed", getName(), "Hace penal");
  BIND_METHOD(Goalkeeper::leftBumperPressed);
}
void Goalkeeper::caidaizq()
{
  std::string behaviorID;
  behaviorID = fFrameManagerProxy.newBehaviorFromFile("/home/nao/caida1.xar", "");
  fFrameManagerProxy.completeBehavior(behaviorID);
}

void Goalkeeper::caidader()
{
  std::string behaviorID;
  behaviorID = fFrameManagerProxy.newBehaviorFromFile("/home/nao/caida2.xar", "");
  fFrameManagerProxy.completeBehavior(behaviorID);
}

Goalkeeper::~Goalkeeper()
{
  //fMemoryProxy.unsubscribeToMicroEvent("EKBallDetected", "Goalkeeper");
  //fMemoryProxy.unsubscribeToEvent("LeftBumperPressed", "Goalkeeper");
  fPostureProxy.goToPosture("Crouch", 0.5f);
}

void Goalkeeper::init()
{
  try {
    fMemoryProxy = AL::ALMemoryProxy(getParentBroker());
    fMotionProxy = AL::ALMotionProxy(getParentBroker());
    fFrameManagerProxy = AL::ALFrameManagerProxy(getParentBroker());
    //fMemoryProxy.subscribeToMicroEvent("EKBallDetected", "Goalkeeper", "EKBallDetected", "ballDetected");
    fMemoryProxy.subscribeToEvent("LeftBumperPressed", "Goalkeeper", "LefttBumperPressed", "leftBumperPressed");
    fMotionProxy.setStiffnesses("Head", 0.7);
    fMotionProxy.setStiffnesses("Body", 0.7);
    fPostureProxy.goToPosture("StandInit", 0.5f);
  }
  catch (const AL::ALError& e) {
    qiLogError("goalkeeper.init") << e.what() << std::endl;
  }
}

void Goalkeeper::leftBumperPressed()
{
  fMotionProxy.setStiffnesses("Head", 0.7);
  fMotionProxy.setStiffnesses("Body", 0.7);
  fPostureProxy.goToPosture("StandInit", 0.5f);
  fMemoryProxy.subscribeToMicroEvent("EKBallDetected", "Goalkeeper", "EKBallDetected", "ballDetected");
}

void Goalkeeper::centerBall()
{
    if(fState.getSize() > 0)
    {
      fMotionProxy.setAngles("Head", fState[1], 0.4);
    }
}

//Method that determines the position the goalkeeper has to be in based on the position of the ball
//and the robot's position relative to a fixed point behind the net.
void Goalkeeper::positionInBox()
{

  //Fixed point behind the net, used as reference
  //float origin [2] = { 0,0 };
  //std::vector<float> origin(2,0);

  float thetaTrans = 0;

  //Gets ball information relative to the robot.
  fState =  fMemoryProxy.getData("EKBallDetected");
  //Transformation of coordinates so that the position of the ball is relative to origin.
  //thetaTrans=nextHeadValues[0]?
  float ball[2];
  ball[0] = cos(thetaTrans)*(float)fState[2][0] - sen(thetaTrans)*(float)fState[2][1] + oldX;
  ball[1] = sen(thetaTrans)*(float)fState[2][0] + cos(thetaTrans)*(float)fState[2][1] + oldY;

  //Using a straight line to position the robot between the ball and the net.
  //Slope
  m = ballY/ballX;
  //Aquí hay que diseñar el algoritmo para determinar Y dependiendo de la distancia entre la pelota y la portería.
  float newPos[2];
  newPos[0] = oldY;
  newPos[1] = oldY/m;

  naoPos[0] = oldX;
  naoPos[1] = oldY;

  float mov[2];
  mov[0] = newPos[0] - naoPos[0];
  mov[1] = newPos[1] - naoPos[1];
  float norma = sqrt(mov[0] * mov[0] + mov[1] * mov[1]);
  float uMov[2];
  uMov[0] = mov[0]/norma;
  uMov[1] = mov[1]/norma;

  //
  if(abs(newPos[0])<75){

    fMotionProxy.setWalkTargetVelocity(uMov[0],uMov[1],(float)fState[3][2],0.1);

  } else {

    if(newPos[0]>75 && naoPos[0]<75){

      fMotionProxy.setWalkTargetVelocity(75,naoPos[1],(float)fState[3][2],0.1);

    } else {

      fMotionProxy.setWalkTargetVelocity(-75,naoPos[1],(float)fState[3][2],0.1);

    }

  }

  naoPos[0] = oldX + newX;
  naoPos[1] = oldY + newY;

  oldX = newX;
  oldY = newY;

  )

}

void Goalkeeper::shoot()
{
  std::string behaviorID;
  behaviorID = fFrameManagerProxy.newBehaviorFromFile("/home/nao/kick.xar", "");
  fFrameManagerProxy.completeBehavior(behaviorID);
}

void Goalkeeper::ballDetected()
{
  AL::ALCriticalSection section(fCallbackMutex);
  fState =  fMemoryProxy.getData("EKBallDetected");


  fMotionProxy.setAngles("Head", fState[1], 0.4);
  //fMotionProxy.setWalkTargetVelocity(0, fState[2][2], 0, 0.1);

  if((float)fState[0] < 65)
  {
    std::cout << "Theta: " << (float)fState[2][2] << std::endl;
    if ((float)fState[2][2] > 0.35)
    {
      caidader();
    }
    else if((float)fState[2][2] < -0.35)
    {
      caidaizq();
    }
  }
/**
  if((float)fState[0] > 17)
  {
    fMotionProxy.setAngles("Head", fState[1], 0.4);
    //fMotionProxy.setWalkTargetVelocity(0.0,(float)fState[3][1],(float)fState[3][2],0.1);
    //std::cout << "Seconds: " << (float)fState[4][0] << std::endl;
    //std::cout << "Miccros: " << (float)fState[4][1] << std::endl;

  }
  else
  {
    if ((float)fState[2][2] > 0.3)
    {
      fMotionProxy.setWalkTargetVelocity(0, 0.4, 0, 0.1);
    }
    else if((float)fState[2][2] < -0.3)
    {
      fMotionProxy.setWalkTargetVelocity(0, -0.4, 0, 0.1);
    }
    else
**/
    //{
      //if(abs((float)fState[2][2]) < 0.08)
      //{
        //fMemoryProxy.unsubscribeToMicroEvent("EKBallDetected", "Goalkeeper");
        //fMotionProxy.moveTo(0, 0.04, 0);
        //shoot();
      //}
    //}
    //fMotionProxy.setStiffnesses("Head", 0.0);
    //fMotionProxy.setStiffnesses("Body", 0.0);

/**
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
            fMemoryProxy.unsubscribeToMicroEvent("EKBallDetected", "Goalkeeper");
            fMotionProxy.moveTo(0, 0.04, 0);
            //shoot();
          }
        }
**/
  //}
}
