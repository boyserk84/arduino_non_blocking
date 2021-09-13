#include "oleddisplay.h"


OLEDDisplay::OLEDDisplay(uint8_t pinClock, uint8_t pinData, byte resetPin, unsigned int width, unsigned int height){
  m_pinClock = pinClock;
  m_pinSCA = pinData;
  m_reset_pin = resetPin;
  m_width = width;
  m_height = height;
  m_prevMiliSeconds = 0;
  m_writeMode = WRITE_MODE_NORMAL;
  Init();
}


OLEDDisplay::Init() {
  
  m_displayAdapter = Adafruit_SSD1306(m_width, m_height, &Wire, m_reset_pin);
  if(!m_displayAdapter.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  ClearDisplay();
}

OLEDDisplay::ClearDisplay() {
  m_displayAdapter.clearDisplay(); // empty buffer
  m_displayAdapter.display(); // write empty buffer out
  m_onScreenState = false;
}

OLEDDisplay::ResetMode() {
  m_onScreenState = false;
  m_stepOffsetX = 0;
  m_stepOffsetY = 0;
  m_currentOnScreenIndex = 0;
  m_writeMode = WRITE_MODE_NORMAL;
}

OLEDDisplay::WriteToScreen(char * str, float textSize, int x, int y, bool clearBeforeWrite) {
  if (clearBeforeWrite == true) {
    ClearDisplay();
  }
  m_displayAdapter.setTextSize(textSize);      // Normal 1:1 pixel scale
  m_displayAdapter.setTextColor(WHITE); // Draw white text
  m_displayAdapter.setCursor(x, y);     // Start at top-left corner
  m_displayAdapter.cp437(true);         // Use full 256 char 'Code Page 437' font
  m_displayAdapter.write(str);          // write to buffer
  m_displayAdapter.display();

  m_onScreenState = true;
}


OLEDDisplay::BlinkWriteToScreen(unsigned int waitMiliSeconds, char * str, float textSize, int x, int y){
  m_onScreenText = str;
  m_onScreenTextSize = textSize;
  m_onScreenText_XPos = x;
  m_onScreenText_YPos = y;
  m_writeMode = WRITE_MODE_BLINK;

  m_stepOffsetX = 0;
  m_stepOffsetY = 0;

  m_intervalMiliSeconds = waitMiliSeconds;
  m_onScreenState = false;
  m_onScreenClearBeforeWrite = false;
  
}

OLEDDisplay::AnimateWriteToScreen(unsigned int waitMiliSeconds, char * str, float textSize, int x, int y, int stepOffsetX, int stepOffsetY) {
  m_onScreenText = str;
  m_onScreenTextSize = textSize;
  m_onScreenText_XPos = x;
  m_onScreenText_YPos = y;
  m_writeMode = WRITE_MODE_ANIMATE;

  m_intervalMiliSeconds = waitMiliSeconds;
  m_onScreenState = false;
  m_stepOffsetX = stepOffsetX;
  m_stepOffsetY = stepOffsetY;
  m_tempX = x;
  m_tempY = y;

  m_displayOneCharEachInterval = true;  // check if deprecate
  m_currentOnScreenIndex = 0;
  m_onScreenClearBeforeWrite = false;
}


OLEDDisplay::OnUpdate(unsigned long miliSeconds) {
  if (m_writeMode == WRITE_MODE_NORMAL) {
    return;
  }

  // TODO: Check if blink vs animate can coexist here
  if (miliSeconds - m_prevMiliSeconds >= m_intervalMiliSeconds) {
      m_prevMiliSeconds = miliSeconds;
      
      if (m_writeMode == WRITE_MODE_BLINK) {
        if (m_onScreenState == false) {
          WriteToScreen(m_onScreenText, 
            m_onScreenTextSize, 
            m_onScreenText_XPos + m_stepOffsetX, 
            m_onScreenText_YPos + m_stepOffsetY, 
            m_onScreenClearBeforeWrite);
        } else {
          ClearDisplay();
        }
      } else if (m_writeMode == WRITE_MODE_ANIMATE) {
        if (m_currentOnScreenIndex > strlen(m_onScreenText)) {
          ClearDisplay();
          return;
        }

        if (m_currentOnScreenIndex == 0) {
          ClearDisplay();
        }
        
        //char * screenTextToDisplay = 
        char* oneChar = m_onScreenText[m_currentOnScreenIndex];
        char oneChar2 = oneChar[0];
        Serial.println(oneChar2);
        
        WriteToScreen(oneChar2, 
            m_onScreenTextSize, 
            m_tempX, 
            m_tempY, 
            m_onScreenClearBeforeWrite);

        Serial.println(m_tempX);
        m_tempX += m_stepOffsetX;
        m_tempY += m_stepOffsetY;
        m_currentOnScreenIndex++;
        
      }
  }
}
