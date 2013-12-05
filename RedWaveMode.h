#include <Arduino.h>
#include "FastSPI_LED2.h"

class RedWaveMode
{
  private:
    int count;
  public:
    RedWaveMode(int pCount);
    void loop(CRGB *leds);
    void init();
};
