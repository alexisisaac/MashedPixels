#include <Arduino.h>
#include "FastLED.h"

class EiffelMode
{
  private:
    int count;
    boolean redSparks;
  public:
    EiffelMode(boolean pRedSparks, int pCount);
    void loop(CRGB *leds);
    void init();
};
