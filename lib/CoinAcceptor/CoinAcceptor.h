#ifndef CoinAcceptor_h
#define CoinAcceptor_h

#include "Arduino.h"

class CoinAcceptor
{
  public:
    CoinAcceptor();
    void increase();
    void reset();
    void setSummand(float _summand);
    void report(boolean _debug);
    void setInterval(int _time);
    float getBudget();
    boolean getBudget(float _price);
    void level();

  private:


  protected:
    boolean debug = false;
    float amount;
    float balance;
    float summand;
    float budget;
    int coins = 0;
    unsigned long interval = 0;
    unsigned long otime = 0;

};

#endif
