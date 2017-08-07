#ifndef Toggle_h
#define Toggle_h

#include "Arduino.h"
#include "Toggle.h"

class Toggle {
  public:
    Toggle(int _pin1);
    boolean status;
    void refresh();
    boolean get();
    ;
  private:

  protected:
    int pin;

  };

#endif
