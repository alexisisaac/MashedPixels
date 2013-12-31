#include "IceCrystalsMode.h"


#ifdef MODE_EXPORT_NAME
const char *IceCrystalsMode::name = "IceCrystals";
#endif

IceCrystalsMode::IceCrystalsMode( int pCount){
  count = pCount;
}
void IceCrystalsMode::init(){
  for (int a=0;a<ICE_COUNT;a++){
    initializeIce(a);
    if(random(0,100)>60){
      ice[a].state = ICE_SLEEPING; 
      ice[a].wakeupTime = millis()+random(1000,2000);
    }
  }
}
void IceCrystalsMode::initializeIce(int  a){
  ice[a].position = random(10,1000)/1000.0f;
  ice[a].growingSpeed = millis()+random(500,1200);
  ice[a].flickeringDuration = ice[a].growingSpeed+random(2000,5000);
  ice[a].explodingDuration = ice[a].flickeringDuration+random(600,1800);
  ice[a].explodingSpeed = random(10,1000)/1000000.0f;
  ice[a].wakeupTime = ice[a].explodingDuration+random(200,400);
  ice[a].state = ICE_GROWING;
  ice[a].start = millis();
}
void IceCrystalsMode::loop(CRGB *leds){
  CRGB color;
  color.setRGB(random(0,255),random(0,255),random(0,255));
  for(int whiteLed = 0; whiteLed < count; whiteLed = whiteLed + 1) {
    leds[whiteLed].g = constrain(9.8*leds[whiteLed].g/10.0-1, 0, 255);
    leds[whiteLed].r = constrain(9.8*leds[whiteLed].r/10.0-1, 0, 255);
    leds[whiteLed].b = constrain(9.8*leds[whiteLed].b/10.0-1, 0, 255);
  }
  for (int a=0;a<ICE_COUNT;a++){
    CRGB *led = &leds[round(ice[a].position*count)];
    CRGB *ledr;
    CRGB *ledl;
    int r, l;
    double npr, npl;
    byte flicker = random(10,50);
    switch(ice[a].state){
      case ICE_GROWING:
        led->g = ((millis()-ice[a].start)*50)/(ice[a].growingSpeed-ice[a].start);
        led->r = ((millis()-ice[a].start)*70)/(ice[a].growingSpeed-ice[a].start);
        led->b = ((millis()-ice[a].start)*200)/(ice[a].growingSpeed-ice[a].start);
        if (millis()>ice[a].growingSpeed){
          ice[a].state = ICE_FLICKERING;
        }
        break;
      case ICE_FLICKERING: 
        led->g = flicker+50;
        led->r = flicker+70;
        led->b = flicker+200;
        if (millis()>ice[a].flickeringDuration){
          ice[a].state = ICE_EXPLODING;
        }
        break;
      case ICE_EXPLODING: 
        
        //led->b = 100-((millis()-ice[a].flickeringDuration)*100)/(ice[a].explodingDuration/10-ice[a].flickeringDuration);
        //led->r = 100-((millis()-ice[a].flickeringDuration)*100)/(ice[a].explodingDuration/10-ice[a].flickeringDuration);
        //led->g = 100-((millis()-ice[a].flickeringDuration)*100)/(ice[a].explodingDuration/10-ice[a].flickeringDuration);
        npr = ice[a].position+(ice[a].explodingSpeed*(millis()-ice[a].flickeringDuration));
        npl = ice[a].position-(ice[a].explodingSpeed*(millis()-ice[a].flickeringDuration));
        r = round(npr*count);
        l = round(npl*count);
        if(r>=0 && r<count){
          ledr = &leds[r];
          ledr->g = 0;
          ledr->r = 0;
          ledr->b = 10;
        }
        if(l>=0 && l<count){
          ledl = &leds[l];
          ledl->g = 0;
          ledl->r = 0;
          ledl->b = 10;
        }
        if (millis()>ice[a].explodingDuration){
          ice[a].state = ICE_SLEEPING;
        }
        break;
      case ICE_SLEEPING: 
        if (millis()>ice[a].wakeupTime){
          initializeIce(a);
        }
        break;
    }
  }
}

