#include "TraditionalMode.h"


TraditionalMode::TraditionalMode(int pCount){
count = pCount;
}
void TraditionalMode::init(){

}
void TraditionalMode::loop(CRGB *leds){
   byte colors[] = {
                              255,0,0,
                              0,180,0,
                              0,0,150,
                              180,150,0
                            };
  for (int a=0;a<count;a++){
    if((millis()/1000)%2==0){
    leds[a].r = colors[(a%4)*3];
    leds[a].g = colors[(a%4)*3+1];
    leds[a].b = colors[(a%4)*3+2];
    } else {
    leds[a].r = colors[(a%4)*3]/20;
    leds[a].g = colors[(a%4)*3+1]/20;
    leds[a].b = colors[(a%4)*3+2]/20;
    }
  }
}
