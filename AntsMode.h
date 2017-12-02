#include <Arduino.h>
#include "FastLED.h"

#define ANTS_COUNT 8
struct ant_data{
  double position;
  double speed;
  boolean direction;
};

class AntsMode{
  private:
    boolean bounces;
    int count;
    ant_data ants[ANTS_COUNT];
  public:
    AntsMode(boolean pBounces, int pCount);
    void loop(CRGB *leds);
    void init();
#ifdef MODE_EXPORT_NAME
    static const char *name;
#endif
};
