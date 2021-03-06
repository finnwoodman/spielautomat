#include "Arduino.h"
#include "Voltmeter.h"

//Class Voltmeter
//Max von Elverfeldt - RaktiPiepEkti - 2017

Voltmeter::Voltmeter(int _pin1)
{
  pin1 = _pin1;
  pos = 0;
  interval= 0;
  debug = true;
  pinMode(_pin1, OUTPUT);
}

int Voltmeter::getPosition(){
  return pos;
  if (debug == true) {
    Serial.print ("VOLTMETER ::: getPosition()");
    Serial.println (pos);
  }
}

void Voltmeter::reset(){
  change = true;
  pos = 0;
  if (debug == true) {
    Serial.println ("VOLTMETER ::: reset()");
  }
}

void Voltmeter::set(int _pos){
  change = true;
  pos = _pos;
  if (debug == true) {
    Serial.print("VOLTMETER ::: set() ");
    Serial.println(pos);
  }
}

void Voltmeter::set(int _pos, long _interval){
  change = true;
  interval= _interval;
  o_pos = pos;
  pos = _pos;
  if (debug == true) {
    Serial.print("VOLTMETER ::: set() ");
    Serial.print(pos);
    Serial.print(" POS and ITV ");
    Serial.println(interval);
  }
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
    if (debug == true) {
      Serial.println("VOLTMETER ::: refresh() ");
    }
}
}

void Voltmeter::report(boolean _debug){
  debug = _debug;
  if (debug == true){
    if (!Serial){
      Serial.begin(9600);
    }
  }
}

void Voltmeter::test(){
  set(100);
  refresh();
  delay(500);
  set(200);
  refresh();
  delay(500);
  set(150);
  refresh();
  delay(500);
  set(0);
  refresh();
}
