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
  FastLED.addLeds<WS2812B, PIN, GRB>(leds, NUM_LEDS);
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
}

void LED_Wrapper::refresh(){
  FastLED.show();
}

void LED_Wrapper::line(int _pos, int _max, CRGB _color ){
  int _tmp = map(_pos, 0, _max, 0, 100);

  for (int i = 0; i < _tmp; i++) {
    leds[i] = _color;
  }
  Serial.println("SEE:");
  Serial.println(_pos);
  Serial.println(_max);
  Serial.println(_tmp);
}
