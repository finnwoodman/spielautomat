#ifndef Rotary_h
#define Rotary_h

#include "Arduino.h"
#include "Voltmeter.h"
#include "LED_Wrapper.h"
#include "SolSound.h"

class Rotary
{
  public:
    Rotary(int _pin1, int _pin2);

    void refresh();
    void report(boolean _debug);
    void increase(int _inc);
    void decrease(int _dec);
    void increaseSteps(int _inc);
    void decreaseSteps(int _dec);
    void autoDecrease(long _interval);
    void autoDecreaseSteps(long _interval);
    void setMax(int _max);
    void measureSpeed();
    int getMax();
    int getModus();
    int getCycles();
    int getSteps();
    int getMaxSteps();
    int getSpeed();

    void attachVMeter(Voltmeter* _vMeter, int _vMax);
    void attachLine(LED_Wrapper* _Line);

    void level();
    void autoPause(bool _auto, long _aTime);
    void autoPause(bool _auto);
    void autoPauseIgnore(bool _ignoreAutoPause);

    void attachSolenoid(SolSound* _Solenoid);

  ;


  private:
    //Pin 1  = DT --- Pin 2 = CLK
    int pin1;
    int pin2;

    int max;
    //Steps, cycles and direction
    boolean bCW;
    int cycles = 0;
    int steps = 0;
    int last = 0;
    int speed = 0;
    int oSpeed = 0;
    //Debug
    boolean debug = false;
    //Status
    bool atMax = false;
    bool atMin = false;
    bool atRun = false;

  protected:
    boolean autoCycle = false;
    boolean autoSteps = false;
    long interval = 0;
    long oTime = 0;
    long pTime = 0;

    bool vOutput = false;
    int vMax = 50;
    Voltmeter* vMeter;

    bool hasLine = false;
    LED_Wrapper* Line;

    bool autoDecr = false;
    long aTime;
    long aInterval = 5000;

    bool ignoreAutoPause = false;

    //Status
    void resetStatus();

    //Solenoid
    SolSound* Solenoid;
    bool hasSolenoid = false;

};

#endif
