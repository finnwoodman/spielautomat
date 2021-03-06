#include "SolSound.h"
#include "Arduino.h"

/**
SolSound class
SolSound.cpp
Purpose: Drive a solenoid for bell strokes and sequences of those.

@author Max von Elverfeldt f. RaktiPiepEkti
@version 0.2 22/06/17
*/


/**
* Constructor of object SolSound including both pins on board.
*/

SolSound::SolSound(int _pin){
  pin = _pin;

  pinMode(pin, OUTPUT);

  stroke = 100;
  oStroke = stroke;

  duration = 100;
  oDuration = duration;

  timer = millis();
  pause = millis();

  repetitions = 0;
  oRepetitions = 0;

}

/**
* Trigger single bell stroke.
*/
void SolSound::bell(){
  repetitions = 1;
  oRepetitions = 1 ;
}


void SolSound::refresh(){
  if((millis() - pause) > duration){
    if ((millis() - timer) > stroke){
      if ((repetitions > 0) && (repetitions == oRepetitions)) {
        repetitions--;
        down();
        timer = millis();
      }
    }
    if ((millis() - timer) > stroke){
      if (repetitions != oRepetitions) {
        up();
        oRepetitions = repetitions;
        pause = millis();
      }
    }
    if ((repetitions == 0) && (oRepetitions == 0)){
      duration = oDuration;
    }
  }
}
/**
* Play a defined number of strokes with dedicated pause.
* @param _rep Number of repetitions.
* @param _dur Pause between bell strokes.
*/
void SolSound::sequence(int _rep, long _dur){
  repetitions = _rep;
  oRepetitions = repetitions;
  oDuration = duration;
  duration = _dur;
}
/**
* Disable solenoid.
*/
void SolSound::up(){
  digitalWrite(pin, LOW);
}
/**
* Enable solenoid.
*/
void SolSound::down(){
  digitalWrite(pin, HIGH);
}

/**
* Adjust bell stroke stroke manually.
* @param _stroke stroke in ms.
*/
void SolSound::adjust(long _stroke){
  oStroke = stroke;
  stroke = _stroke;
}

/**
* Adjustr bell stroke and min. pause inbetween manually.
* @param _stroke   stroke in ms.
* @param _duration min. pause in ms.
*/
void SolSound::adjust(long _stroke, long _duration){
  oStroke = stroke;
  stroke = _stroke;

  oDuration = duration;
  duration = _duration;
}
