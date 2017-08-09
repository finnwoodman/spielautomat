#define UPDATES_PER_SECOND 100
#define FASTLED_ALLOW_INTERRUPTS 0

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

  pinMode(PIN, OUTPUT);
  FastLED.addLeds<WS2812, PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(5);
  clw = true;
  arrowSize = 0;

  //FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);
}

void LED_Wrapper::setAnimation(long _duration){
  duration = _duration;
  animation = true;
}

void LED_Wrapper::setColor(CRGB _color){
  color = _color;
}

void LED_Wrapper::initArrows(){
  for (int i = 0; i < NUM_LEDS; i++) {
    scheme[i] = color;
    leds[i] = scheme[i];
  }
}

void LED_Wrapper::addArrow(int _center, CRGB _highlight){
    int _tmp;
    if (clw == true)   {
      _tmp = _center;
    }
    if (clw == false)  {
      _tmp = (NUM_LEDS - _center);
    }

    fill_gradient_RGB(scheme, _tmp, _highlight, _tmp - arrowSize, color );
    fill_gradient_RGB(scheme, _tmp, _highlight, _tmp + arrowSize, color);

    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = scheme[i];
    }
}

void LED_Wrapper::setArrowSize(int _size){
  arrowSize = ((_size-1) / 2);
}

int LED_Wrapper::getArrows(){
  return sizeof(arrows);
}

int LED_Wrapper::getArrowSize(){
  return arrowSize;
}

void LED_Wrapper::counterClockwise(){
  clw = false;
  if (debug == true) {
    Serial.println("LED_Wrapper ::: counterClockwise() :: ACTIVE");
  }
}
void LED_Wrapper::clockwise(){
  clw = true;
  if (debug == true) {
    Serial.println("LED_Wrapper ::: clockwise() :: ACTIVE");
  }
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
  if (_pos > _max){
    if (animation == true){
      fill_rainbow( leds, NUM_LEDS ,0, 20);
      animation = false;
      oTime = millis();
    }
    else{
      if ((millis()-oTime) > duration) {
        leds[NUM_LEDS] = leds[0];
        for (int i = 0; i < NUM_LEDS; i++) {
          leds[i] = leds[i+1];
        }
      oTime = millis();
      }
    }
  }
  else {
  animation = true;
  if (clw == true){
    int _tmp = map(_pos, 0, _max, 0, 100);
    for (int i = 0; i < _tmp; i++) {
        //  if (leds[i] != _color){
        leds[i] = scheme[i];
        //  }
      }

      for (int i = NUM_LEDS; i >= _tmp; i--) {
        if (leds[i] =! CRGB::Black){
          leds[i] = CRGB::Black;
      }
    }
  }

  if (clw == false){
    int _tmp = map(_pos, 0, _max, 100, 0);
    for (int i = NUM_LEDS; i > _tmp; i--) {
        //  if (leds[i] != _color){
        leds[i] = scheme[i];
        //  }
      }

      for (int i = 0; i <= _tmp; i++) {
        if (leds[i] =! CRGB::Black){
          leds[i] = CRGB::Black;
      }
    }
  }
}
}
