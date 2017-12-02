#include <Arduino.h>
#include "FastLED.h"

class CalibrateMode{
  private:
    int count;
    int led;
    int start;
  public:
    CalibrateMode(int pCount);
    void loop(CRGB *leds);
    void init();
};
