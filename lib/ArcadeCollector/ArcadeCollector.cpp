

#include "Arduino.h"
#include "ArcadeCollector.h"
#include "Arcade.h"

//Class Rotary
//Max von Elverfeldt - RaktiPiepEkti - 2017

ArcadeCollector::ArcadeCollector(int _arcades)
{
  arcades = _arcades;

  bus = (Arcade *)malloc(sizeof(Arcade) * arcades);
  if (debug == true ){
    Serial.println("ArcadeCollector ::: initial Creation()");
  }
}

void ArcadeCollector::add(int _pin1, int _pin2){

  if (index < arcades){
    bus[index].add(_pin1, _pin2);
    bus[index].report(true);
    index++;
    if (debug == true ){
      Serial.print("ArcadeCollector ::: added Arcade(");
    //  Serial.println(_pin1 + " , " + _pin2 + ")" );
    }
  }
}

void ArcadeCollector::refresh(){
  for (int i = 0; i < arcades; i++){
    bus[i].refresh();
    boolean _tmp = bus[i].getStatus();
    if (_tmp == true){
        if (i != active){
          bus[i].reset();
          active = i;
        }
    }
  }
  if (debug == true ){
    Serial.println("ArcadeCollector ::: refresh()");
  }
}

void ArcadeCollector::setBlink(int _duration, int _cycles){
  for (int i = 0; i < arcades ; i++){
    bus[i].blink_on(_duration, _cycles);
  }
  if (debug == true ){
    Serial.println("ArcadeCollector ::: setBlink");
  }
}

void ArcadeCollector::report(boolean _debug){
  if (!Serial){
    Serial.begin(9600);
  }
  debug = _debug;
  Serial.println("ArcadeCollector ::: report() :: ACTIVE");
}
