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

  functionName("positionInBox", getName(), "Lugar en area");
  BIND_METHOD(Goalkeeper::positionInBox);

  functionName("leftBumperPressed", getName(), "Hace penal");
  BIND_METHOD(Goalkeeper::leftBumperPressed);

  functionName("rightBumperPressed", getName(), "Se para");
  BIND_METHOD(Goalkeeper::rightBumperPressed);
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
    dcm = new AL::DCMProxy(getParentBroker());  
    ta = 0;
    ti = dcm->getTime(0);
    offset = 10;
    naoPos[0] = 0;
    naoPos[1] = 0;
    naoPos[2] = 0; 
    uMov[0] = 0;
    uMov[1] = 0;
    thetaTrans = 0;
    flag = false;
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
  //fMemoryProxy.subscribeToMicroEvent("EKBallDetected", "Goalkeeper", "EKBallDetected", "ballDetected");
  qiLogInfo("vision.onBallDetected") << "left leftBumperPressed" << std::endl;
  fMemoryProxy.subscribeToMicroEvent("EKBallDetected", "Goalkeeper", "EKBallDetected", "positionInBox");
}

void Goalkeeper::rightBumperPressed()
{
  fMotionProxy.setStiffnesses("Head", 0.7);
  fMotionProxy.setStiffnesses("Body", 0.7);
  fPostureProxy.goToPosture("StandInit", 0.5f);
  //fMemoryProxy.subscribeToMicroEvent("EKBallDetected", "Goalkeeper", "EKBallDetected", "ballDetected");
  qiLogInfo("vision.onBallDetected") << "right rightBumperPressed" << std::endl;
  fMemoryProxy.unsubscribeToMicroEvent("EKBallDetected", "Goalkeeper");
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
  AL::ALCriticalSection section(fCallbackMutex);
  //std::cout << "Hola" << std::endl;
  

  //Fixed point behind the net, used as reference
  //float origin [2] = { 0,0 };
  //std::vector<float> origin(2,0);

  //Angulo del origen al eje de referencia del Nao
  thetaTrans = 0; //Hay que volverlo variable

  //Gets ball information relative to the robot.
  fState =  fMemoryProxy.getData("EKBallDetected");
  fMotionProxy.setAngles("Head", fState[1], 0.4);

  //Transformation of coordinates so that the position of the ball is relative to origin.
  //thetaTrans=nextHeadValues[0]?

  ball[0] = cos(thetaTrans)*(float)fState[2][0] - sin(thetaTrans)*(float)fState[2][1] + naoPos[0];
  ball[1] = sin(thetaTrans)*(float)fState[2][0] + cos(thetaTrans)*(float)fState[2][1] + naoPos[1];

  qiLogInfo("vision.onBallDetected") << "Ball 0" << ball[0] << std::endl;
  qiLogInfo("vision.onBallDetected") << "Ball 1" << ball[1] << std::endl;

  //Using a straight line to position the robot between the ball and the net.
  //Slope
  float m = (ball[1]-offset)/ball[0];
  //Aqui hay que disenar el algoritmo para determinar Y dependiendo de la distancia entre la pelota y la porteria.
  //Falta tambien calcular theta con respecto al origen.
  //Al agregar theta habria que calcular a que x,y se debe mover el robot con respecto al origen.

  newPos[1] = naoPos[1];
  newPos[0] = (naoPos[1]+offset)/m; 
  newPos[2] = atan((naoPos[1]+offset)/naoPos[0]);

  //Al agregar theta habria que calcular a que x,y se movio el robot con respecto al origen.
//  naoPos[0] = oldPos[0];
//  naoPos[1] = oldPos[1];

  
  mov[0] = newPos[0] - naoPos[0];
  mov[1] = newPos[1] - naoPos[1];
  
  movR[0] = ((mov[0]+sin(thetaTrans)*(mov[1]-naoPos[1])/cos(thetaTrans)-naoPos[1])/cos(thetaTrans))/(1+tan(thetaTrans)*tan(thetaTrans));//si no jalan, usar la transformacion de ball[0] y ball[1] pero con los valores negativos
  movR[1] = ((mov[1]-sin(thetaTrans)*(mov[0]-naoPos[0])/cos(thetaTrans)-naoPos[1])/cos(thetaTrans))/(1+tan(thetaTrans)*tan(thetaTrans));//si no jalan, usar la transformacion de ball[0] y ball[1] pero con los valores negativos
  movR[2] = newPos[2] - naoPos[2]; 

  float norma = sqrt(movR[0] * movR[0] + movR[1] * movR[1]);
  
  uMov[0] = movR[0]/norma;
  uMov[1] = movR[1]/norma;
  uMov[2] = movR[2]/2.09;


  if(abs(movR[0])<75){
    ti=ti+ta;
    ta = dcm->getTime(ti);
    if(abs(mov[0])>10){
      fMotionProxy.setWalkTargetVelocity(0,uMov[0],0,0.1); 
    }else{
      fMotionProxy.setWalkTargetVelocity(0,0,0,0);
    }

  }else{
    fMotionProxy.setWalkTargetVelocity(0,0,0,0);
  }

  
  /* else { 

    if(newPos[0]>75 && naoPos[0]<75){

      fMotionProxy.setWalkTargetVelocity(75,naoPos[1],0,0.1);

    } else {

      fMotionProxy.setWalkTargetVelocity(-75,naoPos[1],0,0.1);

    }

  }*/

    if(!flag){
      flag = true;
    }else{
      naoPos[0] = naoPos[0] ;//+ uMov[0]*ta;//uMov * TIEMPO (como chingaos lo calculamos no se)
      naoPos[1] = naoPos[1] ;//+ uMov[1]*ta;//uMov * TIEMPO (como chingaos lo calculamos no se) 
    }
//  oldPos[0] = naoPos[0];
//  oldPos[1] = naoPos[1];

  }

/*void Goalkeeper::shoot()
{
  std::string behaviorID;
  behaviorID = fFrameManagerProxy.newBehaviorFromFile("/home/nao/kick.xar", "");
  fFrameManagerProxy.completeBehavior(behaviorID);
}*/

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
