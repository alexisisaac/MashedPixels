#include "MathieuMode.h"
#include "hsv2rgb.h"
MathieuMode::MathieuMode( int pCount){
  count = pCount;
}
void MathieuMode::init(){
}
void MathieuMode::loop(CRGB *leds){
  //(int)(millis()*2.0f)
  fill_rainbow(leds, count, (int)(sin(millis()*0.003f)*180.0f+180.0f), 1.4);
}
