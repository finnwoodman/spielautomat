#ifndef LED_Wrapper_h
#define LED_Wrapper_h

#include "Arduino.h"
#include "FastLED.h"

#define NUM_LEDS 100
#define PIN 35
/**
 *
 */
class LED_Wrapper
{
  public:
  LED_Wrapper();
  void report(boolean _debug);
  void tint(CRGB _color);
  void refresh();
  void line(int _pos, int _max, CRGB _color);


  private:
    CRGB leds[NUM_LEDS];
    //int NUM_LEDS;
    //int PIN;
    boolean debug = false;

  protected:

  };

#endif
