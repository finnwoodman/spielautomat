#ifndef ArcadeCollector_h
#define ArcadeCollector_h

#include "Arduino.h"
#include "Arcade.h"

class ArcadeCollector {
public:
  ArcadeCollector(int _arcades);
  void add(int _pin1, int _pin2);
  void add(int _pin1, int _pin2, LED_Wrapper* _line, CRGB _color);
  void refresh();
  void setBlink(int _duration, int _cycles);
  void report(boolean _debug);
  void test(int _interval);
  int getActive();


private:
  Arcade *bus;

  //Arcade* bus = new Arcade[2];

protected:
  int active;
  int arcades = 0;
  int index = 0;
  int debug = false;

};

#endif
