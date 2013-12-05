#include <Arduino.h>
#include "FastSPI_LED2.h"

class TraditionalMode{
  private:
    int count;
    
  public:
    TraditionalMode(int pCount);
    void loop(CRGB *leds);
    void init();
};
