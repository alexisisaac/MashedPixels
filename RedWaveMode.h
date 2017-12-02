#include <Arduino.h>
#include "FastLED.h"

class RedWaveMode
{
  private:
    int count;
  public:
    RedWaveMode(int pCount);
    void loop(CRGB *leds);
    void init();
};
