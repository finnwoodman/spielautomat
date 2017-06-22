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

SolSound::SolSound(int _pin,){
    pin = _pin;

    pinMode(pin2, OUTPUT);

    duration = 20;
    oDuration = duration;

}
/**
 * Disable solenoid.
 */
SolSound::up(){
    digitalWrite(pin, HIGH);
}
/**
 * Enable solenoid.
 */
SolSound::down(){
digitalWrite(pin, LOW);
}

/**
 * Adjust bell strole duration manually.
 * @param _dur Duration in ms.
 */
void SolSound::adjust(long _dur){
  oDuration = duration;
  duration = _dur;
}
