#ifndef SolSound_h
#define SolSound_h

#include "Arduino.h"

/**
 *
 */
class SolSound
{
  public:
    /**
     * Constructor of SolSound
     * @param _pin dedicated digital out pin on board
     */
    SolSound(int _pin);

    /**
     * Adjust the length of each bell stroke. Default = 20ms.
     * @param _time Duration in millis.
     */
    void adjust(long _dur);

    /**
     * Hit the bell once.
     */
    void bell();

    /**
     * Play a simple sequence
     * @param _rep Define the number of repititions.
     * @param _dur Define the pause inbetween.
     */
    void sequence(int _rep, long _dur);

    void melody(int* _note);

  private:
    /**
     * Dedicated digitalOut pin on board.
     */
    int pin;
    /**
     * Length of a bell stroke in ms.
     */
    long duration;
    /**
     * Default length of a bell stroke.
     */
    long oDuration;

    /**
     * Queue for repitions. 
     */
    int repetitions;


  protected:

  };
#endif
