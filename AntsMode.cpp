#include "AntsMode.h"


#ifdef MODE_EXPORT_NAME
const char *AntsMode::name = "Ants";
#endif

AntsMode::AntsMode(boolean pBounces, int pCount){
  count = pCount;
  bounces = pBounces;
}
void AntsMode::init(){
  for (int a=0;a<ANTS_COUNT;a++){
    ants[a].position = random(10,1000)/1000.0f;
    ants[a].speed = random(10,500)/100000.0f;
    ants[a].direction = random(0,1000)>500;
  }
}
void AntsMode::loop(CRGB *leds){
   CRGB color;
   color.setRGB(random(0,255),random(0,255),random(0,255));
   for(int whiteLed = 0; whiteLed < count; whiteLed = whiteLed + 1) {
      // Turn our current led on to white, then show the leds
      leds[whiteLed].g = constrain(9.8*leds[whiteLed].g/10.0-1, 0, 255);
      leds[whiteLed].r = constrain(9.8*leds[whiteLed].r/10.0-1, 0, 255);
      leds[whiteLed].b = constrain(9.8*leds[whiteLed].b/10.0-1, 0, 255);
   }
  for (int a=0;a<ANTS_COUNT;a++){
    ants[a].position += ants[a].speed*(ants[a].direction?1:-1);
    if(ants[a].position>1 || ants[a].position<0){
      if(bounces){
        ants[a].direction = !ants[a].direction;
      } else if(ants[a].position>1){
        ants[a].position = ants[a].position-1;
      } else {
        ants[a].position = 1+ants[a].position;
      }
    }
    CRGB *led = &leds[round(ants[a].position*count)];
    led->r = constrain(led->r+10, 0,255);
    led->b = constrain(led->b+2, 0,255);
    led->g = constrain(led->g+5, 0,255);
  }
}
