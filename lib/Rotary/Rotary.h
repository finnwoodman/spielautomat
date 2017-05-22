#ifndef Rotary_h
#define Rotary_h

#include "Arduino.h"

class Rotary
{
  public:
    Rotary(int _pin1, int _pin2);

    void refresh();
    void report(boolean _debug);
    void increase(int _inc);
    void decrease(int _dec);
    void autoDecrease(long _interval);
  ;


  private:
    //Pin 1  = DT --- Pin 2 = CLK
    int pin1;
    int pin2;

    //Steps, cycles and direction
    boolean bCW;
    int cycles = 0;
    int steps = 0;
    int last = 0;

    //Debug
    boolean debug = false;

  protected:
    boolean autoTime = false;
    long interval = 0;
    long oTime = 0;

};

#endif
