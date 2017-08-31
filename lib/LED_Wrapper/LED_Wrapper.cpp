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
  modus = 0;
  arrowSize = 0;


}


/**
 * Set basic highlight color.
 * @param _color Color as CRGB.
 */
void LED_Wrapper::setColor(CRGB _color){
  color = _color;
  for (int i = 0; i < NUM_LEDS; i++) {
    scheme[i] = color;
    leds[i] = scheme[i];
  }
}

/**
 * Add arrow to scheme mask
 * @param _center    highest point of the arrow.
 * @param _highlight highlight color for arrows gradient.
 */
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

/**
 * Define arrows over all size.
 * @param _size Size in pixel.
 */
void LED_Wrapper::setArrowSize(int _size){
  arrowSize = ((_size-1) / 2);
}

/**
 * Return size of the arrow.
 * @return Arrow size in int.
 */
int LED_Wrapper::getArrowSize(){
  return arrowSize;
}

/**
 * Define LED strips direction.
 */
void LED_Wrapper::counterClockwise(){
  clw = false;
  if (debug == true) {
    Serial.println("LED_Wrapper ::: counterClockwise() :: ACTIVE");
  }
}

/**
 * Define LED strips direction.
 */
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
  if (color != _color){
  if (modus == 0){
  for (int i = 0; i < NUM_LEDS; i++) {
    if (scheme[i] == color) {
        scheme[i] = _color;
    }
    else {
      int _tmp = i + arrowSize-1;
      fill_gradient_RGB(scheme, _tmp, scheme[_tmp], _tmp - arrowSize, _color );
      fill_gradient_RGB(scheme, _tmp, scheme[_tmp], _tmp + arrowSize, _color);
      i += 5;
    }
  }

  for (int i = NUM_LEDS; i > 0; i--) {
    leds[i] = scheme[i];
  }

  color = _color;
}

//Auskommentiert. Immer noch ein Rätsel. (Wird zwei Mal aufgerufen, modus 2 bleibt hängen.)
/*if (modus == 2){
    setWaveColors(_color, CRGB::White);
    color = _color;
    setModus(2);
  }*/
}
}


void LED_Wrapper::refresh(){
  switch (modus) {
    case 0: break;
    case 1: {
            rainbow(50);
            break;
            }
    case 2: {
            wave(50);
            break;
            }
    case 3: {
            rainbowSequence(50);
            break;
            }
    default: break;
  }
  FastLED.show();
}

void LED_Wrapper::line(int _pos, int _max ){
pos = _pos;
if (modus == 0){
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

void LED_Wrapper::rainbow(long _duration){
  if (_rainbow == true){
    fill_rainbow( leds, NUM_LEDS ,0, 20);
    _rainbow = false;
    oTime = millis();
  }
  else{
    if ((millis()-oTime) > _duration) {
      leds[NUM_LEDS] = leds[0];
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = leds[i+1];
      }
    oTime = millis();
    }
  }
}
void LED_Wrapper::rainbowSequence(long _duration){
  if (_rainbow == true){
    fill_rainbow( leds, NUM_LEDS ,0, 20);
    _rainbow = false;
    oTime = millis();
  }
  else{
    if ((millis()-oTime) > _duration) {
      leds[pos] = leds[0];
      for (int i = 0; i < pos; i++) {
        leds[i] = leds[i+1];
      }
    oTime = millis();
    }
  }
}

void LED_Wrapper::wave(long _duration){
  if (_wave == true){
    for (int i = 0; i < 10; i++) {
      fill_gradient_RGB(leds, (i*10), wColor1, (i*10)+5, wColor2 );
      fill_gradient_RGB(leds, (i*10)+5, wColor1, (i+1)*10, wColor2 );
    }
    _wave = false;
    wTime = millis();
  }
  else{
    if ((millis()-wTime) > _duration) {
      leds[NUM_LEDS] = leds[0];
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = leds[i+1];
      }
    wTime = millis();
    }
  }
}

void LED_Wrapper::setWaveColors(CRGB _wColor1, CRGB _wColor2){
  wColor1 = _wColor1;
  wColor2 = _wColor2;
}

void LED_Wrapper::setModus(int _modus){
  if (modus != _modus) {
    modus = _modus;
    switch (_modus) {
      case 0: break;
      case 1: {
              _rainbow = true;
              break;
              }
      case 2: {
              _wave = true;
              break;
              }
      case 3: {
              _rainbow = true;
              break;
               }
      default: break;
    }
  }


}

void LED_Wrapper::resetModus(){
  modus = 0;
}

int LED_Wrapper::getModus(){
  return modus;
}
