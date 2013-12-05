#include "EiffelMode.h"
EiffelMode::EiffelMode(boolean pRedSparks, int pCount){
  count = pCount;
  redSparks = pRedSparks;
}
void EiffelMode::init(){
}
void EiffelMode::loop(CRGB *leds){
   CRGB color;
   color.setRGB(random(0,255),random(0,255),random(0,255));
   for(int whiteLed = 0; whiteLed < count; whiteLed = whiteLed + 1) {
      // Turn our current led on to white, then show the leds
      leds[whiteLed].g = constrain(4*leds[whiteLed].g/5-1, 0, 255);
      leds[whiteLed].r = constrain(4*leds[whiteLed].r/5-1, 0, 255);
      leds[whiteLed].b = constrain(4*leds[whiteLed].b/5-1, 0, 255);
      if(random(0,1000)>990){
        if(random(0,1000)>900 && redSparks){
          leds[whiteLed].g = 255;
          leds[whiteLed].r = 10+random(0,10);
           leds[whiteLed].b =leds[whiteLed].r;
        } else {
          leds[whiteLed].g = 200;
          leds[whiteLed].r = 190+random(0,10);
           leds[whiteLed].b = 20+random(0,60);
        }
      }
   }
}
