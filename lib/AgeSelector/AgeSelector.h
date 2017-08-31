#ifndef AgeSelector_h
#define AgeSelector_h

#include "Arduino.h"

class AgeSelector
{
  public:
    AgeSelector(int _pin1);
    void setSteps(int _min, int _step1,int _step2, int _step3, int _step4, int _step5, int _step6,  int _max);
    void setAges(int _age1, int _age2, int _age3, int _age4, int _age5,int _age6, int _age7);
    void refresh();
    int getCat(int _value);
    void setThreshold(int _buffer);
    void report(boolean _debug);
    int steps[8];
    int ages[7];
    int getValue();

  private:
    int buffer;
    boolean adapt;
    boolean debug;
    int pin1;
    int value1;
    int ovalue1;
    int age;



  protected:
    unsigned long oTime = 0;



};

#endif
