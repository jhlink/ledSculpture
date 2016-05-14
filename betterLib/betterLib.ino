#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 256

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 2
#define PIX_PER_ROW     8
#define COLUMNS     32

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() { 
	Serial.begin(57600);
	Serial.println("resetting");
	LEDS.addLeds<WS2812,2,RGB>(leds,NUM_LEDS);
	LEDS.setBrightness(84);
}


void loop() { 
	static int incTick = 0;
    static unsigned long pastTime = millis();
//    static uint8_t hue = 0;
    if ((millis() - pastTime) > 100) {
      wave(incTick);
       fadeToBlack();
        
    }
//    fadeRainbow();
	incTick++;
	incTick %= COLUMNS;
}

void fadeRainbow(uint8_t hue) {
	Serial.print("x");
	// First slide the led in one direction
	for(int i = 0; i < NUM_LEDS; i++) {
		// Set the i'th led to red 
		leds[i] = CHSV(hue++, 255, 255);
		// Show the leds
		FastLED.show(); 
		// now that we've shown the leds, reset the i'th led to black
		// leds[i] = CRGB::Black;
		fadeall();
		// Wait a little bit before we loop around and do it again
		delay(10);
	}
	Serial.print("x");

	// Now go in the other direction.  
	for(int i = (NUM_LEDS)-1; i >= 0; i--) {
		// Set the i'th led to red 
		leds[i] = CHSV(hue++, 255, 255);
		// Show the leds
		FastLED.show();
		// now that we've shown the leds, reset the i'th led to black
		// leds[i] = CRGB::Black;
		fadeall();
		// Wait a little bit before we loop around and do it again
		delay(10);
	}
}


void fadeall() { 
	for(int i = 0; i < NUM_LEDS; i++) { 
		leds[i].nscale8(250); 
	} 
}

void fadeToBlack() {
	for(int i = 0; i < NUM_LEDS; i++) {
		leds[i].fadeToBlackBy(25);
	}
}

void wave(int tick) { 
    // % 249 is just for error checking. It prevents the below from happening.
    // 249 + 8 = 257. There exist no pixel with that address. 
    int startingRow = (tick * PIX_PER_ROW) % 249;
    
    for (int i = 0; i < PIX_PER_ROW; i++) {  // position incrementation
		leds[startingRow + i].setColorCode(CRGB::White);
    }
    FastLED.show();
   	delay(10);
}
