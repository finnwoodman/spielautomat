#ifndef Voltmeter_h
#define Voltmeter_h

#include "Arduino.h"

class Voltmeter
{
  public:
    Voltmeter(int _pin1);
    void reset();
    void set(int _pos);
    void set(int _pos, long _interval);
    void refresh();
    int getPosition();
    void report(boolean _debug);
  ;


  private:
    int pin1;
    int pos;
    int o_pos;
    boolean change;
  protected:
    unsigned long interval;
    unsigned long oTime;
    boolean debug;

};

#endif
