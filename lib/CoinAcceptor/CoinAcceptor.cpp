#include "Arduino.h"
#include "CoinAcceptor.h"

//Class CoinAcceptor
//Max von Elverfeldt - RaktiPiepEkti - 2017

CoinAcceptor::CoinAcceptor()
{
  balance = 0;
  amount = 0;
  budget = 0;
  summand = 0.1;
  otime = millis();
  interval = 100;
}

void CoinAcceptor::reset(){
  balance = 0;
  amount = 0;
  budget = 0;
  if (debug == true){
    Serial.println("CoinAcceptor::reset()");
  }
}

void CoinAcceptor::setSummand(float _summand){
  summand = _summand;
  if (debug == true){
    Serial.print("CoinAcceptor::setSummand() -> ");
    Serial.println(summand);
  }
}

void CoinAcceptor::increase(){
  if ((millis() - otime) > interval){
      coins++;
      otime = millis();
  }
  otime = millis();
  amount+=summand;
  budget+=summand;

  if (debug == true){
    Serial.print("CoinAcceptor::Balance: ");
    Serial.println(amount);
    Serial.print("CoinAcceptor::Coins: ");
    Serial.println(coins);
  }
}

void CoinAcceptor::report(boolean _debug){
    if (!Serial){
      Serial.begin(9600);
    }
    debug = _debug;
}

void CoinAcceptor::setInterval(int _time){
  interval = _time;
  if (debug == true){
    Serial.print("CoinAcceptor::setInterval() ->");
    Serial.println(interval);
  }
}

float CoinAcceptor::getBudget(){
  if (debug == true){
    Serial.print("CoinAcceptor::Budget() ->");
    Serial.println(budget);
  }
  return budget;
}

boolean CoinAcceptor::getBudget(float _price){
  if (budget >= _price){
    return true;
  }
  else{
  return false;
}
}

void CoinAcceptor::level(){
  budget = 0;
}
