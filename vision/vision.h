#ifndef VISION_H
#define VISION_H

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

class Vision : public AL::ALModule
{
public:
  Vision(boost::shared_ptr<AL::ALBroker> broker,
           const std::string &name);
  virtual ~Vision();
  virtual void init();

  // Function for create event "EKBallDetected"
  void onBallDetected();

private:
    AL::ALMemoryProxy fMemoryProxy;
    AL::ALMotionProxy fMotionProxy;
    AL::ALVideoDeviceProxy fVideoDeviceProxy;
    boost::shared_ptr<AL::ALMutex> fCallbackMutex;
    AL::ALValue fState;
    std::vector<float> headValues;

    void generateMicroEventBallDetected(const AL::ALValue& value);
    
};
#endif // VISION_H
