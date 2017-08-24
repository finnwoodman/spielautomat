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
  void line(int _pos, int _max);
  void counterClockwise();
  void clockwise();

  void setColor(CRGB _color);

  void addArrow(int _center, CRGB _highlight);
  void setArrowSize(int _size);
  int getArrowSize();

  void setModus(int _modus);
  void resetModus();
  void setWaveColors(CRGB _wColor1, CRGB _wColor2);
  void rainbow(long _duration);
  void rainbowSequence(long _duration);


  private:
    CRGB leds[NUM_LEDS];
    boolean debug = false;
    //Animation General
    int modus = 0;
    CRGB color = CRGB::BlueViolet;

  protected:
    int pos;

    int arrowSize;
    bool clw;
    CRGB scheme[NUM_LEDS];



    //Rainbow Animation
    long oTime;
    bool _rainbow = true;


    //Wave Animation
    long wTime;
    bool _wave;
    CRGB wColor1 = CRGB::White;
    CRGB wColor2 = CRGB::Black;
    void wave(long _duration);



  };

#endif
