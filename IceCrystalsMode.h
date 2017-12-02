#include <Arduino.h>
#include "FastLED.h"

#define ICE_COUNT 10                                                                                                                                                                                                                                                                                                                                                                                       

enum ice_state {
  ICE_GROWING,
  ICE_FLICKERING,
  ICE_EXPLODING, 
  ICE_SLEEPING
};

struct ice_data{
  double position;
  unsigned long start;
  unsigned long growingSpeed;
  unsigned long flickeringDuration;
  unsigned long explodingDuration;
  unsigned long wakeupTime;
  double explodingSpeed;
  ice_state state;
};

class IceCrystalsMode{
  private:
    int count;
    ice_data ice[ICE_COUNT];
    void initializeIce(int a);
  public:
    IceCrystalsMode(int pCount);
    void loop(CRGB *leds);
    void init();
#ifdef MODE_EXPORT_NAME
    static const char *name;
#endif
};
