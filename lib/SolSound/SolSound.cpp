#include "SolSound.h"
#include "Arduino.h"

/**
 SolSound class
 SolSound.cpp
 Purpose: Drive a solenoid for bell strokes and sequences of those.

 @author Max von Elverfeldt f. RaktiPiepEkti
 @version 0.1 21/06/17
 */


/**
 * Constructor of object SolSound including both pins on board.
 */

SolSound::SolSound(int _pin1, int _pin2){
    pin1 = _pin1;
    pin2 = _pin2;

    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);

    duration = 20;
    oDuration = duration;

}
/**
 * Disable solenoid.
 */
SolSound::up(){
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
}
/**
 * Enable solenoid.
 */
SolSound::down(){
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
}

/**
 * Adjust bell strole duration manually.
 * @param _dur Duration in ms.
 */
void SolSound::adjust(long _dur){
  oDuration = duration;
  duration = _dur;
}
