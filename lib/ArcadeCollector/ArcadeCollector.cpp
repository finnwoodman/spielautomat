

#include "Arduino.h"
#include "ArcadeCollector.h"
#include "LED_Wrapper.h"
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
void ArcadeCollector::attachLine(LED_Wrapper* _line){
  attach = true;
  line = _line;
}

void ArcadeCollector::add(int _pin1, int _pin2){

  if (index < arcades){
    bus[index].add(_pin1, _pin2);
    if (debug == true ){
      bus[index].report(true);
      Serial.print("ArcadeCollector ::: added Arcade(");
    }
    else {
      bus[index].report(false);
    }
      index++;
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
          if (attach == true) {
            switch (active) {
              case 0:{
                line -> tint(CRGB::White);
                break;
                }
              case 1:{
                line -> tint(CRGB::Yellow);
                break;
                }
              case 2:{
                line -> tint(CRGB::Green);
                break;
                }
              case 3:{
                line -> tint(CRGB::Blue);
                break;
                }
              case 4:{
                line -> tint(CRGB::Red);
                break;
                }
              default: break;
            }
          }
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
debug = _debug;
if (debug==true) {
  if (!Serial){
    Serial.begin(9600);
  }
  Serial.println("ArcadeCollector ::: report() :: ACTIVE");
}
}

int ArcadeCollector::getActive(){
  return active;
}

void ArcadeCollector::test(int _interval){
  for (int i = 0; i < arcades ; i++){
    bus[i].activate();
    delay(_interval);
    bus[i].deactivate();
  }
  if (debug == true ){
    Serial.println("ArcadeCollector ::: Test()");
  }
}
