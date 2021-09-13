/**
 * Buzzer.h
 * Non-blocking active buzzer implementation.
 * 
 * @author Nate K.
 */

#ifndef BUZZER
#define BUZZER

#include "Arduino.h"

class Buzzer {
  private:
    /** Arduino Digital Pin/Channel */
    byte m_pin;
    
    /** Previous timestamp when BUZZ is ON. */
    unsigned long m_prevMiliSeconds;

    /** Interval between buzzing */
    unsigned long m_internvalMiliSeconds;

    /** How many times to play */
    unsigned long m_count;

    /** Current Frequency in Hz being played. (interval mode) */
    unsigned int m_currentHz;

    /** Ending Frequency in Hz. (internval mode)*/
    unsigned int m_endHz;

    /** Duration of each frequency in Hz. */
    unsigned int m_durationHz;

    /** Increment/decrement HZ for each duration. */
    int m_stepHz;

    /** Increment mode if true.*/
    bool m_incrementStep;

    void Init();

  public:
    Buzzer(byte pin);

    void Play(unsigned int hz, unsigned int duration);
    void Stop();
    bool isFinishedPlaying();

    /** Blocking Method */
    void PlaySiren();

    /** Non-blocking method */
    /**
     * Play a customized set of frequency/buzzer sound on the given interval.
     */
    void PlayInterval(unsigned int hz, unsigned int endHz, unsigned int dur, int stepHz, bool increment, unsigned int intervalMiliSeconds, unsigned long count, bool overwrite);
    /**
     * Play a siren alarm sound every interval.
     */
    void PlaySirenInterval();
    
    /** OnUpdate() for calling in Loop() to trigger a siren without blocking. */
    void OnUpdate(unsigned long miliSeconds);
};

#endif
