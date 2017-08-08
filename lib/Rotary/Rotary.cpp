#include "Arduino.h"
#include "Rotary.h"

//Class Rotary
//Max von Elverfeldt - RaktiPiepEkti - 2017

Rotary::Rotary(int _pin1, int _pin2)
{
  pinMode(_pin1, INPUT);
  pinMode(_pin2, INPUT);
  pin1 = _pin1;
  pin2 = _pin2;
  last = digitalRead(pin1);
  max = 10;

}

void Rotary::setMax(int _max){
  max = _max;
}

int Rotary::getMax(){
  return max;
}

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

//Main function - Update RT Knobs Position - Calls autoDecrease() if activated.
void Rotary::refresh(){

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

  //AutoDecrease Section
  if ((autoTime == true) && (cycles > 0)){

    long nTime = millis();
    if ((nTime - oTime) > interval ){
      if (debug == true){
        Serial.print ("ROTARY LIB ::: autoTime() -> ");
        Serial.print (interval);
        Serial.println ("ms.");
      }
      decrease(1);
      oTime = nTime;
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
    if (debug == true ){
      Serial.print ("ROTARY LIB ::: decrease() -> ");
      Serial.print(cycles);
      Serial.print(".");
      Serial.println(steps);
    }
}

//Activate autoDecrease and set interval
void Rotary::autoDecrease(long _interval){

  interval = _interval;
  autoTime = true;

  if (debug == true ){
    Serial.print ("ROTARY LIB ::: autoDecrease() :::: ");
    Serial.print(_interval);
    Serial.println("ms");
  }

}
