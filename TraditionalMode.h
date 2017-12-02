#include <Arduino.h>
#include "FastLED.h"

class TraditionalMode{
  private:
    int count;
    
  public:
    TraditionalMode(int pCount);
    void loop(CRGB *leds);
    void init();
};
