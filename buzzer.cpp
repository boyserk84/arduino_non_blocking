#include "buzzer.h"

Buzzer::Buzzer(byte pin) {
  m_pin = pin;
  Init();
}

void Buzzer::Init() {
  pinMode(m_pin, OUTPUT);
  
  m_prevMiliSeconds = 0;
  m_count = 0;
  m_internvalMiliSeconds = 0;
  m_currentHz = 0;
  m_endHz= 0;
  m_durationHz = 0;
  m_stepHz = 0;
  m_incrementStep = true;
}


void Buzzer::Play(unsigned int hz, unsigned int duration) {
  tone(m_pin, hz, duration);
}

void Buzzer::Stop() {
  noTone(m_pin);
  Init();
}

bool Buzzer::isFinishedPlaying() {
  return m_count <= 0;
}

void Buzzer::PlaySiren() {
  for(int hz = 440; hz < 1000; hz+=25)
  {
    Play(hz, 50);
    delay(5);
  }
      
  for(int hz = 1000; hz > 440; hz-=25)
  {
    Play(hz, 50);
    delay(5);
  }
}

void Buzzer::PlaySirenInterval() {
  if (m_currentHz == 0) {
    // first time ever
    m_currentHz = 440;
    m_endHz = 1000;
    m_stepHz = 25;
    m_durationHz = 50;
    m_internvalMiliSeconds = 5;
    m_count = 1000;
  }
  
  if (isFinishedPlaying()) {
    m_count = 1000;
    m_incrementStep != m_incrementStep;
    if (m_incrementStep) {
      m_currentHz = 440; 
      m_endHz = 1000;
    } else {
      m_currentHz = 1000;
      m_endHz = 440;
    }
  }
  
}

void Buzzer::PlayInterval(unsigned int hz, unsigned int endHz, unsigned int dur, int stepHz, bool increment,
  unsigned int intervalMiliSeconds, 
  unsigned long count, 
  bool overwrite) {
  if (overwrite == false) {
    if (m_count > 0) {
      // do nothing
      return;
    }
  }
  
  m_currentHz = hz;
  m_endHz = endHz;
  m_durationHz = dur;
  m_internvalMiliSeconds = intervalMiliSeconds;
  m_count = count;
  m_stepHz = stepHz;
  m_incrementStep = increment;
  
}

void Buzzer::OnUpdate(unsigned long miliSeconds) {
  
  if (miliSeconds - m_prevMiliSeconds >= m_internvalMiliSeconds) {
      bool shouldContinue = true;
      // determine to step up or down
      if (m_incrementStep) {
        shouldContinue = m_currentHz < m_endHz;
      } else {
        shouldContinue = m_endHz < m_currentHz;
      }

      // playing a sound or stop
      if (m_count > 0 && shouldContinue) {
        Play(m_currentHz, m_durationHz);
        if (m_incrementStep) {
          m_currentHz += m_stepHz;
        } else {
          m_currentHz -= m_stepHz;
        }
        m_count--;
      } else {
        m_count = 0;
        Stop();
      }
      
      m_prevMiliSeconds = miliSeconds;
  }
}
