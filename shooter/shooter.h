#ifndef SHOOTER_H
# define SHOOTER_H

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

class Shooter : public AL::ALModule
{
public:
  Shooter(boost::shared_ptr<AL::ALBroker> broker,
           const std::string &name);

  virtual ~Shooter();
  virtual void init();

private:
  AL::ALMemoryProxy fMemoryProxy;
  AL::ALRobotPostureProxy fPostureProxy;
  AL::ALMotionProxy fMotionProxy;
  AL::ALFrameManagerProxy fFrameManagerProxy;
  boost::shared_ptr<AL::ALMutex> fCallbackMutex;
  AL::ALValue fState;

  void leftBumperPressed();
  void ballDetected();
  void centerBall();
  void walkToBall();
  void shoot();
};
#endif // SHOOTER_H
