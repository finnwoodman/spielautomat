#ifndef AgeSelector_h
#define AgeSelector_h

#include "Arduino.h"

class AgeSelector
{
  public:
    AgeSelector(int _pin1, int _pin2);
    void setSteps(int _min, int _step1,int _step2, int _step3, int _step4, int _step5, int _max);
    void setAges(int _age1, int _age2, int _age3, int _age4, int _age5);
    void refresh();
    int getCat(int _value);
    void setThreshold(int _buffer);
    void report(boolean _debug);
    int steps[7];
    int ages[6];

  private:
    int buffer;
    boolean adapt;
    boolean debug;
    int pin1;
    int pin2;
    int value1;
    int value2;
    int ovalue1;
    int ovalue2;
    int min;
    int max;



  protected:




};

#endif
