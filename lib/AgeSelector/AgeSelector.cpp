#include "Arduino.h"
#include "AgeSelector.h"

//Class AgeSelector
//Max von Elverfeldt - RaktiPiepEkti - 2017

//Comment: E(Blue or/and White) = GND, IN(Yellow, White) = VIN, OUT(Blue, Yellow) = A8, A9

AgeSelector::AgeSelector(int _pin1)
{
  pinMode(_pin1, INPUT);

  pin1 = _pin1;

  value1 = analogRead(pin1);

  adapt = false;
  buffer = 5;
  debug = false;
  oTime = millis();
}

void AgeSelector::refresh(){
  if ((millis()-oTime)>100){
  ovalue1 = value1;
  value1 = analogRead(pin1);
  if ((ovalue1 <= (value1 - buffer)) || (ovalue1 >= (value1 + buffer))){
    if (adapt == false){
      age = value1;
    }
    else {
      age = getCat(value1);
    }
    if (debug == true){
      Serial.print("AgeSelector::newage(): ");
      Serial.print(value1);
      Serial.print(" -> ");
      Serial.println(getValue());
    }
  }
  if(debug == true){
    if (value1 =! ovalue1){
      Serial.println(value1);
    }
  }
  oTime = millis();
  }
}

void AgeSelector::setSteps(int _age, int _step1,int _step2, int _step3, int _step4, int _step5,int _step6, int _max){
    adapt = true;
    steps[0] = _age;
    steps[1] = _step1;
    steps[2] = _step2;
    steps[3] = _step3;
    steps[4] = _step4;
    steps[5] = _step5;
    steps[6] = _step6;
    steps[7] = _max;
    if (debug == true){
      for (int i = 0; i < sizeof(ages); i++) {
        Serial.println(steps[i]);    /* code */
      }
    }
}

void AgeSelector::setAges(int _age1, int _age2, int _age3, int _age4, int _age5,int _age6, int _age7){
  ages[0] = _age1;
  ages[1] = _age2;
  ages[2] = _age3;
  ages[3] = _age4;
  ages[4] = _age5;
  ages[5] = _age6;
  ages[6] = _age7;
  if (debug == true){
    Serial.println("AgeSelector::setAges():");
    for (int i = 0; i < sizeof(ages); i++) {
      Serial.println(ages[i]);
    }
  }
}



int AgeSelector::getCat(int _value){
  int _age = 0;
  for (int i = 1; i < (sizeof(steps)/sizeof(int)); i++) {
    if (_value > steps[i-1]){
      _age = ages[i-1];
    }
    else break;
  }
  return _age;
}

void AgeSelector::setThreshold(int _buffer){
  buffer = _buffer;
  if (debug == true){
    Serial.print("AgeSelector::setThreshold(");
    Serial.print(_buffer);
    Serial.println(")");
  }
}

void AgeSelector::report(boolean _debug){
  debug = _debug;
  if (debug == true){
  if (!Serial){
    Serial.begin(9600);
  }
}
}

int AgeSelector::getValue(){
  return age;
}
