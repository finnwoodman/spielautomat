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
     * Class makes use of irlz34n to control a solenoid.
     * @param _pin1 dedicated digital out pin one on board
     */
    SolSound(int _pin);

    /**
     * Adjust the length of each bell stroke. Default = 20ms.
     * @param _time stroke in millis.
     */
    void adjust(long _stroke);

    /**
     * Adjustr bell stroke and min. pause inbetween manually.
     * @param _stroke   stroke in ms.
     * @param _duration min. pause in ms.
     */
    void adjust(long _stroke, long _dur);

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
     * @param _rep Define the number of repetitions.
     * @param _dur Define the pause inbetween.
     */
    void sequence(int _rep, long _dur);

    //void melody(int* _note);

  private:
    /**
     * Dedicated digitalOut pin on board.
     */
    int pin;

    /**
     * Length of a bell stroke in ms.
     */
    long stroke;
    long oStroke;

    /**
     * Min. Pause between bell strokes.
     */
    long duration;
    long oDuration;
    /**
     * Variable for timing.
     */
    long timer;
    long pause;

    /**
     * Queue for repitions.
     */
    int repetitions;
    int oRepetitions;


  protected:
    void down();
    void up();

  };


#endif
