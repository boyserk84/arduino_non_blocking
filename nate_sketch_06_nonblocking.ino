#include "led.h"
#include "buzzer.h"
#include "oleddisplay.h"

/** Analog Channels */
#define PHOTORESISTOR A3
#define DISPLAY_SCA A4
#define DISPLAY_CLOCK A5

/** Digital Channels */
#define LED_RED 11
#define LED_GREEN 12
#define BUZZER 3

Led* GREEN;
Led* RED;
Buzzer* SIREN;
OLEDDisplay* OLED_DISPLAY;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Setup starts");
  pinMode(BUZZER, OUTPUT);
  GREEN = new Led(LED_GREEN);
  RED = new Led(LED_RED);
  OLED_DISPLAY = new OLEDDisplay(DISPLAY_CLOCK, DISPLAY_SCA, 4, 128, 32);
  
  GREEN->BlinkInterval(1000,5, false);
  RED->BlinkInterval(1000,5, false);
  SIREN = new Buzzer(BUZZER);
  Serial.println("Setup Complete");
}

unsigned long currMilis = 0;
bool displayAlready = false;
unsigned int offset = 2;
unsigned long prevMilis = 0;
void loop() {
  // put your main code here, to run repeatedly:
  GREEN->OnUpdate(millis());
  RED->OnUpdate(millis());
  SIREN->OnUpdate(millis());
  OLED_DISPLAY->OnUpdate(millis());

  if (displayAlready == false) {
    Serial.println("Start blinking the screen");
    OLED_DISPLAY->AnimateWriteToScreen(500,"Hello ! World", 1, 15 ,15, 10,0);
    displayAlready = true;
  }

  
  if (GREEN->RemainingBlinkCount() < 1 && RED->RemainingBlinkCount() < 1) {
    if (millis() - currMilis > 5000) {
      //SIREN->PlaySirenInterval(); // play sound
      currMilis = millis();
    } else {
      // Blink
      GREEN->BlinkInterval(1500, 10, false);
      RED->BlinkInterval(2000, 10, false);
    }
  }
}
