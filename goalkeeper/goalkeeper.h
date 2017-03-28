#ifndef GOALKEEPER_H
# define GOALKEEPER_H

# include <alcommon/almodule.h>
# include <boost/shared_ptr.hpp>
# include <alproxies/almemoryproxy.h>
# include <alproxies/almotionproxy.h>
# include <alproxies/alframemanagerproxy.h>
# include <alproxies/alrobotpostureproxy.h>

# include <iostream>
# include <alcommon/almodule.h>
# include <althread/almutex.h>

namespace AL
{
  class ALBroker;
}

class Goalkeeper : public AL::ALModule
{
public:
  Goalkeeper(boost::shared_ptr<AL::ALBroker> broker,
           const std::string &name);

  virtual ~Goalkeeper();
  virtual void init();

private:
  AL::ALMemoryProxy fMemoryProxy;
  AL::ALRobotPostureProxy fPostureProxy;
  AL::ALMotionProxy fMotionProxy;
  AL::ALFrameManagerProxy fFrameManagerProxy;
  boost::shared_ptr<AL::ALMutex> fCallbackMutex;
  AL::ALValue fState;
  float oldPos[2] = {0,10};
  //Nao's position relative to origin in cm
  float naoPos[2] = {0,10};
  float thetaTrans = 0;

  void leftBumperPressed();
  void ballDetected();
  void centerBall();
  void positionInBox();
  void shoot();
  void caidaizq();
  void caidader();

};

#endif // GOALKEEPER_H
