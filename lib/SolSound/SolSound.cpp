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

    duration = 1000;
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
  repetitions++;
  oRepetitions++;
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
}
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
