#include "RedWaveMode.h"
RedWaveMode::RedWaveMode(int pCount){
  count = pCount;
}
void RedWaveMode::init(){
}
void RedWaveMode::loop(CRGB *leds){
   CRGB color;
   color.setRGB(random(0,255),random(0,255),random(0,255));
   int last=-100;
   for(int whiteLed = 0; whiteLed < count; whiteLed = whiteLed + 1) {
      // Turn our current led on to white, then show the leds
      double v = sin(whiteLed*0.3+millis()/1000.0)*255;
      if (v>240 && random(0,100)>90 && whiteLed-last>10){
        last = whiteLed;
        leds[whiteLed].g = 250;
        leds[whiteLed].r = 255;
        leds[whiteLed].b = 252;
        
      } else {
        leds[whiteLed].g = constrain(v, 0, 255);
        leds[whiteLed].r = 0;
        leds[whiteLed].b = 0;
      }
   }
}
