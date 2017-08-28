#include "Arduino.h"
#include "Arcade.h"
#include "LED_Wrapper.h"


//Class Arcade
//Max von Elverfeldt - RaktiPiepEkti - 2017

Arcade::Arcade(int _pin1, int _pin2)
{
  pinMode(_pin1, INPUT);
	pinMode(_pin2, OUTPUT);
  pin1 = _pin1;
  pin2 = _pin2;
	deactivate();
}

Arcade::Arcade()
{
}

void Arcade::attachLine(LED_Wrapper* _line, CRGB _color){
  attach = true;
  line = _line;
  color = _color;
}
void Arcade::add(int _pin1, int _pin2){
  pinMode(_pin1, INPUT);
  pinMode(_pin2, OUTPUT);
  pin1 = _pin1;
  pin2 = _pin2;
  deactivate();
}

void Arcade::refresh(){
  int _last = digitalRead(pin1);

	//zweiter Aufruf
	if ((_last == LOW) && (status == true)){
		if ((millis()-oTime)>300){
			ostatus = true;
			oTime = millis();
		}

	}

	//Erster Aufruf
	if ((_last == LOW) && (status == false)){

		status = true;
		ostatus = false;
		activate();
		if (debug == true) {
			Serial.print ("ARCADE LIB ::: refresh() -> Pin");
			Serial.print(pin1);
			Serial.print(" = ");
			Serial.print(status);
			Serial.println(".");
		}
		if (blink == true){
			oTime = millis();
		}
	}


if ((blink == true) && (ostatus == true)){
			if ((millis() - oTime) > interval){
				oTime = millis();
				if (loops >= 0){
						if (led == true){
							deactivate();
						}
						else {
							activate();
							loops--;
						}
					}
				else {
					ostatus = false;
					loops = oloops;
				}
			}
	}
}

void Arcade::setStatus(boolean _status){
	ostatus = status;
	status = _status;
	if (status == true){
		activate();
	}
	else deactivate();
}

void Arcade::reset(){
	ostatus = false;
	status = false;
	deactivate();
}

void Arcade::report(boolean _debug){
  debug = _debug;
  if (debug == true){
    if (!Serial){
      Serial.begin(9600);
    }
  }
}



void Arcade::activate(){
	digitalWrite(pin2, HIGH);
	led = true;
	if (debug == true) {
		Serial.print ("ARCADE LIB ::: activate() -> Pin");
		Serial.print(pin2);
		Serial.println(".");
	}
}

void Arcade::deactivate(){
	digitalWrite(pin2, LOW);
	led = false;
	if (debug == true) {
		Serial.print ("ARCADE LIB ::: deactivate() -> Pin");
		Serial.print(pin2);
		Serial.println(".");
	}
}

void Arcade::blink_on(long _interval, int _loops){
  interval = _interval;
	loops = _loops;
	oloops = loops;
	oTime = millis();
  blink = true;
  if (debug == true ){
    Serial.print ("ARCADE LIB ::: blink_on() :::: ");
    Serial.print(_interval);
    Serial.print("ms with");
	  Serial.print(_loops);
		Serial.println( "Loops");
  }
}

boolean Arcade::getStatus(){

  if (debug == true) {
    Serial.print ("ARCADE LIB ::: getStatus() :: ");
    Serial.println(status);
  }

  return status;
}
