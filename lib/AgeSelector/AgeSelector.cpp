#include "Arduino.h"
#include "AgeSelector.h"

//Class AgeSelector
//Max von Elverfeldt - RaktiPiepEkti - 2017

AgeSelector::AgeSelector(int _pin1, int _pin2)
{
  pinMode(_pin1, INPUT);
	pinMode(_pin2, INPUT);
  pin1 = _pin1;
  pin2 = _pin2;
  value1 = analogRead(pin1);
  value2 = analogRead(pin2);
  adapt = false;
  buffer = 5;

}

void AgeSelector::refresh(){
  
  ovalue1 = value1;
  ovalue2 = value2;
  value1 = analogRead(pin1);
  value2 = analogRead(pin2);
  if ((ovalue1 <= (value1 - buffer)) || (ovalue1 >= (value1 + buffer))){
    Serial.print("Value1: ");
    Serial.println(value1);
    Serial.print("oValue1: ");
    Serial.println(value1);
    Serial.print("oValue1 - buffer: ");
    Serial.println(value1 - buffer);
    Serial.print("oValue1 + buffer: ");
    Serial.println(value1 + buffer);
    Serial.print("buffer: ");
    Serial.println(buffer);
    if (adapt == false){
      min = value1;
    }
    else {
      Serial.println(getCat(value1));
    }
  }
  if (ovalue2 != value2){
    if (adapt == false){
      max = value2;
    }
    else {
      //Serial.println(getCat(value2));
    }
  }
}

void AgeSelector::setSteps(int _min, int _step1,int _step2, int _step3, int _step4, int _step5, int _max){
    adapt = true;
    steps[0] = _min;
    steps[1] = _step1;
    steps[2] = _step2;
    steps[3] = _step3;
    steps[4] = _step4;
    steps[5] = _step5;
    steps[6] = _max;
}

void AgeSelector::setAges(int _age1, int _age2, int _age3, int _age4, int _age5){
  ages[0] = 0;
  ages[1] = _age1;
  ages[2] = _age2;
  ages[3] = _age3;
  ages[4] = _age4;
  ages[5] = _age4;
  //ages[6] = 99;
}



int AgeSelector::getCat(int _value){
  int _age;
  for (int i = 1; i < sizeof(steps); i++) {
    if ((_value > steps[i-1]) && (_value < steps[i])){
      _age = ages[i-1];
    }
  }
  return _age;
}

void AgeSelector::setThreshold(int _buffer){
  buffer = _buffer;
}
