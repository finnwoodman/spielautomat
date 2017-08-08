#include "Arduino.h"
#include "RotarySwitch.h"

//  Class RotarySwitch
//  Use rotary switches with n-options + return the selected.
//  (C) Max von Elverfeldt for RaktiPiepEkti 2017


RotarySwitch::RotarySwitch(int _pin, int _intervals)
{
    oTime = millis();
    oIntervals = _intervals;
    intervals = 1024/_intervals;
    pin = _pin;
    pinMode(pin, INPUT);
    step = round(analogRead(pin)/intervals);
}


/**
 * Re-Read rot. switch and calc step.
 */
void RotarySwitch::refresh(){
  if ((millis()-oTime)>100){
  value = analogRead(pin);
  step = round(value/intervals);
  oTime = millis();
  if (debug == true) {
    Serial.println("RotarySwitch::Refresh:");
    Serial.print("Value : ");
    Serial.println(value);
    Serial.print("Step : ");
    Serial.println(step);
  }
  }
}

void RotarySwitch::setThreshold(int _threshold){
  intervals = (1024+_threshold)/oIntervals;
  if (debug == true){
    Serial.print("RotarySwitch::setThreshold -> +-");
    Serial.println(_threshold);
  }
}

/**
 * Return current position of the rot. switch.
 * @return Integer with step.
 */
int RotarySwitch::getPosition(){
  refresh();
  return step;
}

/**
 * Enable / Disables serial debug reporting
 * @param _debug True or false
 */
void RotarySwitch::report(boolean _debug){
  debug = _debug;
  if (debug == true){
  if (!Serial){
    Serial.begin(9600);
  }
}
}
