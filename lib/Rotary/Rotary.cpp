#include "Arduino.h"
#include "Rotary.h"
#include "Voltmeter.h"
#include "LED_Wrapper.h"

//Class Rotary
//Max von Elverfeldt - RaktiPiepEkti - 2017

Rotary::Rotary(int _pin1, int _pin2)
{
  pinMode(_pin1, INPUT);
  pinMode(_pin2, INPUT);
  pin1 = _pin1;
  pin2 = _pin2;
  pTime = millis();
  last = digitalRead(pin1);
  oSpeed = 0;
  max = 10;

}

void Rotary::attachLine(LED_Wrapper *_Line){
  Line = _Line;
  hasLine = true;
}

/**
 * Set the ultimate needed cycles.
 * @param _max Max number of turns.
 */

void Rotary::setMax(int _max){
  max = _max;
}

/**
 * Returns the max  set.
 * @return max  in integer.
 */
int Rotary::getMax(){
  return max;
}

/**
 * Returns the max cycles
 * @return Cycles.
 */
int Rotary::getCycles(){
  return cycles;
}

int Rotary::getSteps(){
  int _steps = cycles*40;
  _steps+= steps;
  return _steps;
}

int Rotary::getMaxSteps(){
  int _max = max*40;
  return _max;
}

void Rotary::measureSpeed(){
  if ((millis() - pTime) > 250) {
    speed = getSteps();
    if ((speed-oSpeed)>=0) {
        speed -= oSpeed;
    }
    else {
      speed = 0;
    }

    pTime = millis();
    oSpeed = getSteps();

    if (debug == true){
      Serial.print("ROTARY LIB ::: Speed() -> ");
      Serial.print(oSpeed);
      Serial.print(" = ");
      Serial.print(speed);
      Serial.println();
    }
  }
if (vOutput == true){
  vMeter -> set(map(getSpeed(), 0,vMax,0,255));
}

}

int Rotary::getSpeed(){
  return speed;
}

//Main function - Update RT Knobs Position - Calls autoDecrease() if activated.
void Rotary::refresh(){
  measureSpeed();
  if (Line->arrowStatus() == true) {
    autoPause(true, 5000);
  }
  else{
    autoPause(false);
  }
  //Magic rotary section
  int val = digitalRead(pin1);
  if (val != last){
    if (digitalRead(pin2) != val) {  //pin1 moved first
      steps++;
      bCW = true;
      if (steps > 40 ){
        cycles++;
        steps = 0;
      }
    } else {//pin 2 changed first
      bCW = false;
      steps--;
      if (steps < 0 ){
        cycles--;
        steps = 40;
      }
    }

    //Debug Section
    if (debug == true ){
      Serial.print ("ROTARY LIB ::: Refresh() ->");
      Serial.print ("Rotated: ");
      if (bCW){
        Serial.println ("clockwise");
      }else{
        Serial.println("counterclockwise");
      }
      Serial.print(cycles);
      Serial.print(".");
      Serial.println(steps);
  }
  oTime = millis(); //Sync timer to last action
  }
  last = val;

  if ((autoDecr == true) && ((millis() - aTime) > aInterval)){
      decreaseSteps((max*40)/40);
      autoDecr == false;
  }
  //AutoDecrease Section
  if (autoDecr == false) {
  if ((autoCycle == true) && (cycles > 0)){

    long nTime = millis();
    if ((nTime - oTime) > interval ){
    /*  if (debug == true){
        Serial.print ("ROTARY LIB ::: autoCycle() -> ");
        Serial.print (interval);
        Serial.println ("ms.");
      }*/
      decrease(1);
      oTime = nTime;
    }

    }

    //AutoDecreaseSteps Section
    if ((autoSteps == true) && (steps >= 0)){
      long nTime = millis();
      if ((nTime - oTime) > interval ){
      /*  if (debug == true){
          Serial.print ("ROTARY LIB ::: autoCycle() -> ");
          Serial.print (interval);
          Serial.println ("ms.");
        }*/


        if ((steps == 0) && (cycles == 0)) {
        increaseSteps(1);
        }
        decreaseSteps(1);
        oTime = nTime;
      }
      }
    }
    //Line Communication

      if ((getSteps() > getMaxSteps()) && (atMax == false)) {
        resetStatus();
        atMax = true;
        if (hasLine == true){
          Line -> setModus(1);
        }
      }

      if ((getSteps() < 1) && (atMin == false)) {
        resetStatus();
        atMin = true;
        if (hasLine == true){
          Line -> setModus(2);
        }
      }

      if ((getSteps() > 1) && (getSteps() < getMaxSteps()) && (atRun == false)) {
        resetStatus();
        atRun = true;
        if (hasLine == true){
          Line -> setModus(0);
        }
      }




}

//Activate Debug via Serial Output
void Rotary::report(boolean _debug){
debug = _debug;
if (debug == true) {
  if (!Serial){
    Serial.begin(9600);
  }
}
}

//Increase cycles manually
void Rotary::increase(int _inc){
    cycles+=_inc;
    if (debug == true ){
      Serial.print ("ROTARY LIB ::: increase() -> ");
      Serial.print(cycles);
      Serial.print(".");
      Serial.println(steps);
    }
}

//Decrease cycles manually
void Rotary::decrease(int _dec){
    cycles-=_dec;
    /*if (debug == true ){
      Serial.print ("ROTARY LIB ::: decrease() -> ");
      Serial.print(cycles);
      Serial.print(".");
      Serial.println(steps);
    }*/
}

void Rotary::increaseSteps(int _inc){
  steps+=_inc;

/*  if (debug == true ){
    Serial.print ("ROTARY LIB ::: increaseSteps() -> ");
    Serial.print(cycles);
    Serial.print(".");
    Serial.println(steps);
  }*/
}

void Rotary::decreaseSteps(int _dec){
if (cycles == 0){
  if ((steps -= _dec) < 0){
    steps = 1;
  }
  if ((steps -= _dec) >= 0){
    steps -= _dec;
  }
}
if (cycles > 0){
  if ((steps -= _dec) < 0){
    steps = 40 - (_dec - steps);
    cycles--;
  }
}


  if (debug == true ){
    Serial.print ("ROTARY LIB ::: decreaseSteps() -> ");
    Serial.print(cycles);
    Serial.print(".");
    Serial.println(steps);
  }
}
void Rotary::autoPause(bool _auto, long _aInterval){
  if (_auto != autoDecr){
    autoDecr = _auto;
    aTime = millis();
    aInterval = _aInterval;
  }
}

void Rotary::autoPause(bool _auto){
    if (_auto != autoDecr){
      autoDecr = _auto;
  }
}
//Activate autoDecrease and set interval
void Rotary::autoDecrease(long _interval){
  interval = _interval;
  autoCycle = true;
  autoSteps = false;

  if (debug == true ){
    Serial.print ("ROTARY LIB ::: autoDecrease() :::: ");
    Serial.print(_interval);
    Serial.println("ms");
  }
}
//Activate autoDecrease and set interval
void Rotary::autoDecreaseSteps(long _interval){

  interval = _interval;
  autoCycle = false;
  autoSteps = true;

  if (debug == true ){
    Serial.print ("ROTARY LIB ::: autoDecreaseSteps() :::: ");
    Serial.print(_interval);
    Serial.println("ms");
  }
}

void Rotary::attachVMeter(Voltmeter* _vMeter, int _vMax){
  vMax = _vMax;
  vMeter = _vMeter;
  vOutput = true;
}

int Rotary::getModus(){
  //return Line -> modus;
}

void Rotary::resetStatus(){
  atMax = false;
  atMin = false;
  atRun = false;
}

void Rotary::level(){
  cycles = 0;
  steps = 0;
}
