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
  void counterClockwise();
  void clockwise();

  void setColor(CRGB _color);

  void initArrows();
  void addArrow(int _center, CRGB _highlight);
  void setArrowSize(int _size);
  int getArrows();
  int getArrowSize();

  void setAnimation(long _duration);



  private:
    CRGB leds[NUM_LEDS];
    boolean debug = false;

  protected:
    CRGB color = CRGB::BlueViolet;
    int arrowSize;
    bool clw;
    int* arrows;
    CRGB scheme[NUM_LEDS];

    //Rainbow Animation
    long oTime;
    long duration;
    bool animation;



  };

#endif
