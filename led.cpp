#include "led.h"

Led::Led(byte pin) {
  m_pin = pin;
  Init();
}

void Led::Init() {
  pinMode(m_pin, OUTPUT);
  m_prevMiliSeconds = 0;
  m_currState = false;
  m_blinkCount = 0;
  m_internvalMiliSeconds = 0;
}

void Led::On() {
  if (m_currState == false) {
    digitalWrite(m_pin, HIGH);
  }
  m_currState = true;
}

void Led::Off() {
  if (m_currState == true) {
    digitalWrite(m_pin, LOW);
  }
  m_currState = false;
}

bool Led::CurrentState() {
  return m_currState;
}

unsigned int Led::RemainingBlinkCount() {
  return m_blinkCount;
}

void Led::BlinkInterval(unsigned int intervalMiliSeconds, int count, bool overwrite) {
  if (overwrite == false) {
    if (m_blinkCount > 0) {
      // do nothing
      return;
    }
  }

  m_blinkCount = count;
  m_internvalMiliSeconds = intervalMiliSeconds;
}

void Led::OnUpdate(unsigned long miliSeconds) {
  
  if (miliSeconds - m_prevMiliSeconds >= m_internvalMiliSeconds) {
      if (m_currState == false && m_blinkCount > 0) {
        On();
        m_blinkCount--;
      } else {
        Off();
      }
      
      m_prevMiliSeconds = miliSeconds;
  }
  
}
