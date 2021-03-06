#ifndef RotarySwitch_h
#define RotarySwitch_h

#include "Arduino.h"

class RotarySwitch
{
  public:
  /**
   * Class RotarySwitch constructor. Needs analog pin and number of steps.
   */
    RotarySwitch(int _pin, int _intervals);


    void refresh();


  /** set threshhold in order to calm switching.
   * @param _puffer size of threshold
   */
    void setThreshold(int _threshold);
  /** Report to Serial
   *  @param _debug Use "true" to enable Serial.port debugging.
   */
    void report(boolean _debug);

  /** Return position
   *  @return The current position (step) of the rotary switch.
   *  @see _steps
   */
   int getPosition();
   int getMapping();
   void addMapping(int *_mapping);
   void addCorrector(int _corrector);


  private:
    int pin;
    int oIntervals;
    int intervals;
    int value;
    int step;
    boolean debug = false;
    unsigned long oTime = 0;
    int *mapping;
    int corrector = 0;


};

#endif
