#include "LED_Wrapper.h"
#include "Arduino.h"
#include "FastLED.h"

/**
LED Wrapper Class
LED_Wrapper.cpp
Purpose: Small wrapper for FastLED breaking it down to some simple functions.

@author Max von Elverfeldt f. RaktiPiepEkti
@version 0.1 27/06/17
*/


/**
 * Contructor of LED_Wrapper
 * @param _pin Dedicated LED Strip's pin on board
 * @param _num NUmber of LEDs.
 */
LED_Wrapper::LED_Wrapper(){


  FastLED.addLeds<WS2812B, PIN, RGB>(leds, NUM_LEDS);
  tint(CRGB::Black);
}

/**
 * Enable / Disable serial debugging.
 * @param _debug Boolean true / false
 */
void LED_Wrapper::report(boolean _debug){
  debug = _debug;
  if (!Serial){
    Serial.begin(9600);
  }
  Serial.println("LED_Wrapper ::: report() :: ACTIVE");
}

/**
 * Change colour of all LEDs.
 * @param _color Color as CRGB::_name_of_color
 */
void LED_Wrapper::tint(CRGB _color){
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = _color;
  }
  FastLED.show();
}
