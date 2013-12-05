#include <Arduino.h>
#include "FastSPI_LED2.h"

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
