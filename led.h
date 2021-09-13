/**
 * Led.h
 * Non-blocking LED blinking implementation.
 * 
 * @author Nate K.
 */
#ifndef LED
#define LED

#include "Arduino.h"

class Led {
  private:
    /** Arduino Digital Pin/Channel */
    byte m_pin;
    
    /** Previous timestamp when LED is ON. */
    unsigned long m_prevMiliSeconds;
    
    /** Current state of LED */
    bool m_currState;

    /** Interval between Blink */
    unsigned long m_internvalMiliSeconds;

    /** How many times to blink */
    int m_blinkCount;
    
    void Init();
    
  public:
    Led(byte pin);
    void On();
    void Off();
    /** Non-blocking blink every nth interval. */
    void BlinkInterval(unsigned int intervalMiliSeconds, int count, bool overwrite);
    /** OnUpdate() for calling in Loop() to trigger blink without blocking. */
    void OnUpdate(unsigned long miliSeconds);
    bool CurrentState();
    unsigned int RemainingBlinkCount();
};

#endif
