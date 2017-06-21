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
     * Class makes use of DC motor driver to drive solenoid
     * @param _pin1 dedicated digital out pin one on board
     * @param _pin2 dedicated digital out pin two board
     */
    SolSound(int _pin1, int _pin2);

    /**
     * Adjust the length of each bell stroke. Default = 20ms.
     * @param _time Duration in millis.
     */
    void adjust(long _dur);

    /**
     * Hit the bell once.
     */
    void bell();

    /*
     * Refresh bell actions.
     */
    void refresh();
    /**
     * Play a simple sequence
     * @param _rep Define the number of repititions.
     * @param _dur Define the pause inbetween.
     */
    void sequence(int _rep, long _dur);

    void melody(int* _note);

  private:
    /**
     * Dedicated digitalOuts pin on board.
     */
    int pin1;
    int pin2;
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
    void down();
    void up();

  };


#endif
