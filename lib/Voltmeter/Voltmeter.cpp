#include "Arduino.h"
#include "Voltmeter.h"

//Class Voltmeter
//Max von Elverfeldt - RaktiPiepEkti - 2017

Voltmeter::Voltmeter(int _pin1)
{
  pin1 = _pin1;
  pos = 0;
  interval= 0;
  pinMode(_pin1, OUTPUT);
}

int Voltmeter::getPosition(){
  return pos;
}

void Voltmeter::reset(){
  change = true;
  pos = 0;
}

void Voltmeter::set(int _pos){
  change = true;
  pos = _pos;
}

void Voltmeter::set(int _pos, long _interval){
  change = true;
  interval= _interval;
  o_pos = pos;
  pos = _pos;
}

void Voltmeter::refresh(){

  if ((change == true) && (interval == 0)){
    analogWrite(pin1, pos);
    change = false;
  }

  if ((change == true) && (interval > 0)){
    if ((millis()-oTime) > interval){
    if (o_pos < pos){
      o_pos++;
      analogWrite(pin1, o_pos);
  }
    if (o_pos > pos){
      o_pos--;
      analogWrite(pin1, o_pos);
  }
    if (o_pos == pos){
      interval= 0;
      change = false;
    }
    oTime = millis();
    }
  }
}
