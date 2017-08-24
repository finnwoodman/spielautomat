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

  void addArrow(int _center, CRGB _highlight);
  void setArrowSize(int _size);
  int getArrowSize();

  void setModus(int _modus);
  void resetModus();
  void setWaveColors(CRGB _wColor1, CRGB _wColor2);



  private:
    CRGB leds[NUM_LEDS];
    boolean debug = false;

  protected:
    CRGB color = CRGB::BlueViolet;
    int arrowSize;
    bool clw;
    CRGB scheme[NUM_LEDS];

    //Hue animation
    CRGB hueAnim[NUM_LEDS];
    long pTime;

    //Animation General
    int modus = 0;

    //Rainbow Animation
    long oTime;
    bool _rainbow;
    void rainbow(long _duration);

    //Wave Animation
    long wTime;
    bool _wave;
    CRGB wColor1 = CRGB::White;
    CRGB wColor2 = CRGB::Black;
    void wave(long _duration);



  };

#endif
