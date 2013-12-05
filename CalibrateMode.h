#include <Arduino.h>
#include "FastSPI_LED2.h"

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
