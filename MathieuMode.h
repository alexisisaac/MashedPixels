#include <Arduino.h>
#include "FastLED.h"

class MathieuMode
{
  private:
    int count;
  public:
    MathieuMode( int pCount);
    void loop(CRGB *leds);
    void init();
};
