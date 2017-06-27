#ifndef LED_Wrapper_h
#define LED_Wrapper_h

#include "Arduino.h"
#include "FastLED.h"

/**
 *
 */
class LED_Wrapper
{
  public:
  LED_Wrapper(int _pin, int _num);
  void report(boolean _debug);
  void tint(CRGB _color);


  private:
    CRGB *leds;

  protected:
    int NUM_LEDS;
    int PIN;
    boolean debug = false;
  };

#endif
