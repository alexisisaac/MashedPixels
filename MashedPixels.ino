#include "FastSPI_LED2.h"
#include <Wire.h>
#include <EEPROM.h>

#define USE_MATHIEUMODE
#define USE_EIFFELMODE
#define USE_ANTSMODE
#define USE_CALIBRATEMODE
#define USE_TRADITIONALMODE
#define USE_REDWAVEMODE
//#define USE_VIDEOMODE


//Customize here
#define DATA_PIN 2  
#define BUTTON_PIN 3
#define NUM_LEDS 100


#define SERIAL_DEBUG


#ifdef SERIAL_DEBUG
#define MODE_EXPORT_MNAME
#endif

#ifdef USE_MATHIEUMODE
#include "MathieuMode.h"
#endif
#ifdef USE_EIFFELMODE
#include "EiffelMode.h"
#endif
#ifdef USE_ANTSMODE
#include "AntsMode.h"
#endif
#ifdef USE_CALIBRATEMODE
#include "CalibrateMode.h"
#endif
#ifdef USE_TRADITIONALMODE
#include "TraditionalMode.h"
#endif
#ifdef USE_REDWAVEMODE
#include "RedWaveMode.h"
#endif



#ifdef USE_VIDEOMODE
#define FRAME_TIME 67 //milliseconds per frame
#define BITS_PER_PIXELS 24 //Bits per pixels
#define BITS_PER_PIXELS_24 //Bits per pixels
#define FRAMES_COUNT 301 //frames
#define SD_DATA
#endif

#define DATA_SIZE 300
byte *data;
//char files[13][13];

//Menu modes
enum mode_display {
#ifdef USE_MATHIEUMODE
  MODE_DISPLAY_MATHIEU,
#endif
#ifdef USE_EIFFELMODE
  MODE_DISPLAY_EIFFEL,
#endif
#ifdef USE_ANTSMODE
  MODE_DISPLAY_ANTS,
#endif
#ifdef USE_CALIBRATEMODE
  MODE_DISPLAY_CALIBRATE,
#endif
#ifdef USE_TRADITIONALMODE
  MODE_DISPLAY_TRADITIONAL,
#endif
#ifdef USE_REDWAVEMODE
  MODE_DISPLAY_REDWAVE,
#endif
#ifdef USE_VIDEOMODE
  MODE_DISPLAY_VIDEO,
#endif
};

#ifdef USE_VIDEOMODE
#ifdef SD_DATA
#include <SdFat.h>
#include <SdFatUtil.h>

// SD chip select pin
const uint8_t chipSelect = 4;
SdFat sd;
SdFile file;
char videofile[13];

//#define error(s) sd.errorHalt_P(PSTR(s))
#define error(s) void(s)
#endif
#endif
CRGB leds[NUM_LEDS+1];
unsigned long lastFrame = 0;
unsigned long startTime = 0;
boolean fr_count;
byte MAX_MODE = 0;
#ifdef USE_MATHIEUMODE
MathieuMode mat = MathieuMode( NUM_LEDS);
#endif
#ifdef USE_EIFFELMODE
EiffelMode ef = EiffelMode(false, NUM_LEDS);
#endif
#ifdef USE_ANTSMODE
AntsMode ant = AntsMode(true, NUM_LEDS);
#endif
#ifdef USE_CALIBRATEMODE
CalibrateMode cal = CalibrateMode(NUM_LEDS);
#endif
#ifdef USE_TRADITIONALMODE
TraditionalMode trad = TraditionalMode( NUM_LEDS);
#endif
#ifdef USE_REDWAVEMODE
RedWaveMode rw = RedWaveMode(NUM_LEDS);
#endif

enum mode_display mode;
boolean file_initialized = false;


void setup(){
  delay(500);
  Serial.begin(9600);
  data = (byte *)malloc(DATA_SIZE);
  Serial.println("init FastLED");
  // Uncomment one of the following lines for your leds arrangement.
  // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
   FastLED.addLeds<NEOPIXEL, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
  //** FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);
  // FastLED.addLeds<WS2801, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<SM16716, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<LPD8806, RGB>(leds, NUM_LEDS);

  // FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);

  // delay(1000);

  pinMode(BUTTON_PIN,INPUT);

#ifdef USE_MATHIEUMODE
  Serial.println("Init mat");
  MAX_MODE++;
  mat.init();
#endif
#ifdef USE_EIFFELMODE
  Serial.println("Init ef");
  MAX_MODE++;
  ef.init();
#endif
#ifdef USE_ANTSMODE
  Serial.println("Init ant");
  MAX_MODE++;
  ant.init();
#endif
#ifdef USE_CALIBRATEMODE
  Serial.println("Init cal");
  MAX_MODE++;
  cal.init();
#endif
#ifdef USE_TRADITIONALMODE
  Serial.println("Init trad");
  MAX_MODE++;
  trad.init();
#endif
#ifdef USE_REDWAVEMODE
  Serial.println("Init rw");
  MAX_MODE++;
  rw.init();
#endif
#ifdef USE_VIDEOMODE
  MAX_MODE++;
#endif
mode = (mode_display)EEPROM.read(0);
if (mode>=MAX_MODE){
  mode = (mode_display)0;
}
  Serial.println("Light test");

  for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
    leds[whiteLed].r = 0;
    leds[whiteLed].g = 255;
    leds[whiteLed].b = 0;
  }
  FastLED.show();
  delay(300);
  for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
    leds[whiteLed].r = 255;
    leds[whiteLed].g = 0;
    leds[whiteLed].b = 0;
  }
  FastLED.show();
  delay(300);
  for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
    leds[whiteLed].r = 0;
    leds[whiteLed].g = 0;
    leds[whiteLed].b = 255;
  }
  FastLED.show();
  delay(300);
  for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
    leds[whiteLed].r = 255;
    leds[whiteLed].g = 0;
    leds[whiteLed].b = 255;
  }
  FastLED.show();
  delay(300);
  
    for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
    leds[whiteLed].r = 0;
    leds[whiteLed].g = 255;
    leds[whiteLed].b = 255;
  }
  FastLED.show();
  delay(300);
  for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
    leds[whiteLed].r = 255;
    leds[whiteLed].g = 130;
    leds[whiteLed].b = 0;
  }
  FastLED.show();
  delay(300);
  for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
    leds[whiteLed].r = 0;
    leds[whiteLed].g = 0;
    leds[whiteLed].b = 0;
  }
  FastLED.show();
  delay(300);
  Serial.println("Light test ok");

#ifdef USE_VIDEOMODE   
  Serial.println("init SD");
  initMenu();
#endif
  Serial.println("done");

}

void loop(){
  if ( digitalRead(BUTTON_PIN) == LOW) {
    Serial.print(MAX_MODE);
    Serial.print(" ");
    Serial.print(mode);
    Serial.print("/");
    mode_display oldmode = mode;
    mode = (mode_display)(((int)mode+1)%MAX_MODE);
    Serial.println(mode);
    EEPROM.write(0, mode);
    switch(mode){
#ifdef USE_MATHIEUMODE
    case MODE_DISPLAY_MATHIEU:
      mat.init();
      break;
#endif
#ifdef USE_CALIBRATEMODE
    case MODE_DISPLAY_CALIBRATE:
      cal.init();
      break;
#endif
#ifdef USE_TRADITIONALMODE
    case MODE_DISPLAY_TRADITIONAL:
      trad.init();
      break;
#endif
#ifdef USE_ANTSMODE
    case MODE_DISPLAY_ANTS:
      ant.init();
      break;
#endif
#ifdef USE_EIFFELMODE
    case MODE_DISPLAY_EIFFEL:
      ef.init();
      break;
#endif
#ifdef USE_REDWAVEMODE
    case MODE_DISPLAY_REDWAVE:
      rw.init();
      break;
#endif
#ifdef USE_VIDEOMODE
    case MODE_DISPLAY_VIDEO:
      initDisplayVideo();
      break;
#endif
    }

    delay(1000);
  if ( digitalRead(BUTTON_PIN) == LOW) {
    mode = oldmode;
    EEPROM.write(0, mode);
      for(int a=0;a<255;a++){
         for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
          leds[whiteLed].r = 255-a;
          leds[whiteLed].g = 255-a;
          leds[whiteLed].b = 255-a;
        }
        FastLED.show();
      }
    while(digitalRead(BUTTON_PIN) == LOW){
      delay(100);
    }
    while(digitalRead(BUTTON_PIN) != LOW){
      delay(100);
    }
    
      for(int a=255;a>0;a--){
         for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
          leds[whiteLed].r = 255-a;
          leds[whiteLed].g = 255-a;
          leds[whiteLed].b = 255-a;
        }
        FastLED.show();
      }
  }
    }
  switch(mode){
#ifdef USE_MATHIEUMODE
  case MODE_DISPLAY_MATHIEU:
    mat.loop(leds);
    FastLED.show();
    break;
#endif
#ifdef USE_CALIBRATEMODE
  case MODE_DISPLAY_CALIBRATE:
    cal.loop(leds);
    FastLED.show();
    break;
#endif
#ifdef USE_TRADITIONALMODE
  case MODE_DISPLAY_TRADITIONAL:
    trad.loop(leds);
    FastLED.show();
    break;
#endif
#ifdef USE_ANTSMODE
  case MODE_DISPLAY_ANTS:
    ant.loop(leds);
    FastLED.show();
    break;
#endif
#ifdef USE_EIFFELMODE
  case MODE_DISPLAY_EIFFEL:
    ef.loop(leds);
    FastLED.show();
    break;
#endif
#ifdef USE_REDWAVEMODE
  case MODE_DISPLAY_REDWAVE:
    rw.loop(leds);
    FastLED.show();
    break;
#endif
#ifdef USE_VIDEOMODE
  case MODE_DISPLAY_VIDEO:
    if(file_initialized) loopDisplayVideo();
    break;
#endif
  }
}

#ifdef USE_VIDEOMODE
void initMenu(){

  if (!sd.begin(chipSelect, SPI_FULL_SPEED)) sd.initErrorHalt();
  SdFile file;
  sd.chdir("/",true);
  uint16_t count = 0;
  Serial.println("listing files");
  while (file.openNext(sd.vwd(),O_READ)&& count<10)
  {
    Serial.print("File ");
    Serial.print(count);
    Serial.print(" : ");
    file.getFilename(videofile);
    Serial.println(videofile);//files[count]);
    count++;
  }
  file.close();
  file_initialized = true;
}


void initDisplayVideo(){
  Serial.println("initDisplayVideo");

  if(!file_initialized){
    Serial.println("videofile not initialized");
    return;
  } 
  else {
    Serial.println(videofile);
    //startTime = millis();

#ifdef SD_DATA
    /*if (!sd.begin(chipSelect, SPI_FULL_SPEED)) sd.initErrorHalt();
     if (!file.open("TEST.DAT", O_RDONLY)) {
     error("open failed");
     }
     if (file.read(data, DATA_SIZE) != DATA_SIZE) {
     error("read failed");
     }*/
#endif
  }
}
void loopDisplayVideo(){
  Serial.println("frame");

}
#endif



