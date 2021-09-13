/**
 * OledDisplay.h
 * Non-blocking OLED display implementation.
 * 
 * @author Nate K.
 */
#ifndef OLEDDISPLAY
#define OLEDDISPLAY

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class OLEDDisplay {
  private:
    /** Analog Clock Pin */
    uint8_t m_pinClock;
    
    /** Analog Data Pin */
    uint8_t m_pinSCA;

    /** Display adapter */
    Adafruit_SSD1306 m_displayAdapter;
    
    /** Reset Pin */
    byte m_reset_pin = 4;

    /** Screen width */
    unsigned int m_width;
    /** Screen Height */
    unsigned int m_height;

    /** Previous timestamp when OLED display is ON. */
    unsigned long m_prevMiliSeconds;

    unsigned long m_intervalMiliSeconds;

    /** Text on-screen */
    char* m_onScreenText;
    /** Text Size */
    float m_onScreenTextSize;
    /** X Position */
    int m_onScreenText_XPos;
    /** Y position */
    int m_onScreenText_YPos;
    /** Current state of the onScreen. */
    bool m_onScreenState = false;
    /** Flag whether to clear screen before writing */
    bool m_onScreenClearBeforeWrite = true;

    /** 
     *  Mode
     *  0 = Normal
     *  1 = Blink
     *  2 = Animate - on character at a time.
     *  3 = Scroll left
     *  4 = Scroll Right
     */
    unsigned int m_writeMode = 0;

    unsigned const int WRITE_MODE_NORMAL = 0;
    unsigned const int WRITE_MODE_BLINK = 1;
    unsigned const int WRITE_MODE_ANIMATE = 2;
    unsigned const int WRITE_MODE_SCROLL_L = 3;
    unsigned const int WRITE_MODE_SCROLL_R = 4; 

    
    int m_stepOffsetX = 0;
    int m_stepOffsetY = 0;
    int m_tempX = 0;
    int m_tempY = 0;

    bool m_displayOneCharEachInterval = false;  // Deprecate this
    unsigned int m_currentOnScreenIndex = 0;
    
    Init();
    
  public:
    OLEDDisplay(uint8_t pinClock, uint8_t pinData, byte resetPin, unsigned int width, unsigned int height);
    WriteToScreen(char * str, float textSize, int x, int y, bool clearBeforeWrite);
    BlinkWriteToScreen(unsigned int waitMiliSeconds, char * str, float textSize, int x, int y);
    AnimateWriteToScreen(unsigned int waitMiliSeconds, char * str, float textSize, int x, int y, int stepOffsetX, int stepOffsetY);
    ScrollWriteToScreen(unsigned int waitMiliSeconds, char * str, float textSize, int x, int y, int stepOffsetX, int stepOffsetY);
    ClearDisplay();
    ResetMode();

    /** OnUpdate() for calling in Loop() to trigger a siren without blocking. */
    OnUpdate(unsigned long miliSeconds);
    
  
};
#endif
