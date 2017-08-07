

#include "Arduino.h"
#include "Toggle.h"

//Class Toggle.h
//Max von Elverfeldt - RaktiPiepEkti - 2017

Toggle::Toggle(int _pin1)
{
  pin = _pin1;
  pinMode(pin, INPUT);
  status = digitalRead(pin);
  }


boolean Toggle::get(){
  return status;
}

void Toggle::refresh(){
  status = digitalRead(pin);
}
