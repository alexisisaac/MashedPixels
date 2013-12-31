MashedPixels
============

An Arduino based Christmas light


* [demo](https://www.youtube.com/watch?v=gfSNxLwvbII)
* [breadboard demo](https://www.youtube.com/watch?v=gfSNxLwvbII)
* [strip demo](https://www.youtube.com/watch?v=dMHQV0NTcpk)
* [Christmas tree demo](https://www.youtube.com/watch?v=ITD6IiKeDy0)


# Configuration
At the beginning of the file there are switches to choose which effects will be available.

Add // before the effect you do not want to be compiled

	#define USE_MATHIEUMODE
	#define USE_EIFFELMODE
	#define USE_ANTSMODE
	#define USE_CALIBRATEMODE
	#define USE_TRADITIONALMODE
	#define USE_REDWAVEMODE
	#define USE_ICECRYSTALSMODE
	//#define USE_VIDEOMODE

## Description of the effects

### MATHIEUMODE
Mathieu is the name of my 4yo son. He designed this effect. It's a rainbow oscillating between each side of the led strip.

### EIFFELMODE
Named after the Eiffel tower in Paris, France. Random white flashes progressively turning off with a yellowish tint.

### ANTSMODE
Particle system on "ants" walking at different speeds along the LED strip.

### CALIBRATEMODE
Used for the upcomming VIDEOMODE. lights every LED one after another alternating between colors Cyan, Magenta and Yellow.

### TRADITIONALMODE
Emulates traditionnal chrismas lights each led has a predefined color (Red, green, blue, yellow) and blinks all at the same time.

### REDWAVEMODE
A red wave is progressing along the led strip and the brighter leds randomnly flashes white.

### VIDEOMODE
NOT READY YET. DO NOT USE.

### ICECRYSTALSMODE
Blue light grows (become lighter) at a point then flickers for some time then explodes. 

## Pins configuration

	#define DATA_PIN 2  
	#define BUTTON_PIN 3
### DATA_PIN
The pin onto which the data line of the led strip is linked.
### BUTTON_PIN
The pin where the button is connected.

## LED Strip configuration
	#define NUM_LEDS 100
Setup the number of leds in the strip

Configure the type of strip (in the setup function line 133)

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


# Usage
Press the button to change the effect. Press the button a long time to turn the strip off (the strip turns fully white then gradually turns off). To turn on again press the button. THe strip turns fully white gradually then starts the last effect used.
