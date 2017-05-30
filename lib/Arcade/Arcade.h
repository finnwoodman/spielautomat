#ifndef Arcade_h
#define Arcade_h

#include "Arduino.h"

class Arcade
{
  public:
    Arcade();
    Arcade(int _pin1, int _pin2);
    void add(int _pin1, int _pin2);
    void refresh();
    void report(boolean _debug);
    void activate();
    void deactivate();
    void blink_on(long _interval, int _loops);
    void blink_off();
    void setStatus(boolean _status);
    void reset();
    boolean getStatus();

  private:
    boolean status = false;
    boolean ostatus = false;
    int pin1;
    int pin2;
    //Debug
    boolean debug = false;

  protected:
    boolean led = false;

    boolean blink = false;
    unsigned long interval = 0;
    unsigned long oTime = 0;
    int  loops = 0;
    int  oloops = 0;



};

#endif
