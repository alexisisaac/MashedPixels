#include "CalibrateMode.h"


CalibrateMode::CalibrateMode(int pCount){
  count = pCount;
}
void CalibrateMode::init(){

   led=-100;
   start = millis();
}
void CalibrateMode::loop(CRGB *leds){
          Serial.println(led);
         if(led==-100){   
          start = millis();
          for (int a=0;a<count;a++){
            CRGB *led = &leds[a];
            led->r =0;
            led->g =0;
            led->b =0;
          }
         }
         if(led>=0 && led<count){
           leds[led].r = 0;
           leds[led].g = 0;
           leds[led].b = 0;
         }
         led = floor((millis()-start)/160)-4;
         Serial.println(led);
         if(led>=0 && led<count){
           switch(led%3){
             case(0):
               leds[led].r = 0;
               leds[led].g = 255;
               leds[led].b = 255;
               break;
             case(1):
               leds[led].r = 255;
               leds[led].g = 0;
               leds[led].b = 255;
               break;
             case(2):
               leds[led].r = 255;
               leds[led].g = 255;
               leds[led].b = 0;
               break;
             default:
               leds[led].r = 255;
               leds[led].g = 255;
               leds[led].b = 255;
               break;

           }
         }
         
}
