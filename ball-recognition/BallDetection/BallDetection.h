#ifndef BALLDETECTION_H
#define BALLDETECTION_H

# include <iostream>
# include <alcommon/almodule.h>

#include <boost/shared_ptr.hpp>
#include <string>


////////PFUDOR
#include <alproxies/almemoryproxy.h>
#include <alproxies/altexttospeechproxy.h>
#include <alproxies/almotionproxy.h>
#include <alproxies/alvideodeviceproxy.h>
#include <althread/almutex.h>

namespace AL
{
  class ALBroker;
}

class BallDetection : public AL::ALModule
{
public:
  BallDetection(boost::shared_ptr<AL::ALBroker> broker,
           const std::string &name);
  virtual ~BallDetection();
  virtual void init();

  // Function to create event "bwBallDetected"
  void bwBallDetection();

private:
    AL::ALMemoryProxy fMemoryProxy;
    AL::ALMotionProxy fMotionProxy;
    AL::ALVideoDeviceProxy fVideoDeviceProxy;
    boost::shared_ptr<AL::ALMutex> fCallbackMutex;
    AL::ALValue fState;

    //Write every variable used in bwBallDetecction???

    void generateMicroEventBwBallDetected(const AL::ALValue& value);
    
};
#endif // VISION_H
