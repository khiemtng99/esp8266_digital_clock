#include "DigitalClock.h"
#include <Wire.h>
#include <Ticker.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Ticker timer;

void ISR() {
  readIncreaseButton();
  readModeButton();

  clockCounter();
  stopwatchCounter();
}

void setup() {
  Serial.begin(115200);
  Wire.begin(2, 0);

  pinMode(MODE_BUTTON, INPUT);
  pinMode(INCREASE_BUTTON, INPUT);

  lcd.init();
  lcd.backlight();

  timer.attach_ms(10, ISR);
}

void loop() {
  increaseTimeState();
  clockMode();
}

void readModeButton() {
  firstReadModeButton = secondReadModeButton;
  secondReadModeButton = digitalRead(MODE_BUTTON);
  if(secondReadModeButton != firstReadModeButton) {
    if(firstReadModeButton) {
      Mode++;
      if(Mode > 4)
        Mode = 0;
    }
  }
}

void readIncreaseButton() {
  firstReadIncreaseButton = secondReadIncreaseButton;
  secondReadIncreaseButton = digitalRead(INCREASE_BUTTON);
  if(secondReadIncreaseButton == firstReadIncreaseButton) {
    if(firstReadIncreaseButton) {
      fIncreaseButton = 1;
      count1++;
      if(count1 > 100) {
        fIncreaseButtonPressed1s = 1;
        count2++;
        if(count2 > 20)
          count2 = 0;
      }
    }
    else {
      fIncreaseButton = 0;
      fIncreaseButtonPressed1s = 0;
      count1 = 0;
      count2 = 0;
    }
  }
  else if(Mode == 4) {
    if(firstReadIncreaseButton) {
      stopwatchMode++;
      if(stopwatchMode > 2)
        stopwatchMode = 0;
    }
  }
}

void clockCounter() {
  count3++;
  if(count3 > 99) {
    count3 = 0;
    second++;
    if(second > 59) {
      second = 0;
      minute++;
      if(minute > 59) {
        minute = 0;
        hour++;
        if(hour > 23) 
          hour = 0;
      }
    }
  }
}

void stopwatchCounter() {
  if(flag) {
    centiSec++;
    if(centiSec > 99) {
      centiSec = 0;
      stopwatchSec++;
      if(stopwatchSec > 59) {
        stopwatchSec = 0;
        stopwatchMin++;
        if(stopwatchMin > 59) 
          stopwatchMin = 0;
      }
    }
  }  
}

void increaseTime() {
  switch(Mode) {
    case 1:
      hour++;
      if(hour > 23)
        hour = 0;
      lcd.setCursor(4, 0);
      if(hour < 10)
        lcd.print("0");
      lcd.print(hour);     
    break;
    case 2:
      minute++;
      if(minute > 59)
        minute = 0;
      lcd.setCursor(7, 0);
      if(minute < 10)
        lcd.print("0");
      lcd.print(minute);
    break;
    case 3:
      second++;
      if(second > 59)
        second = 0;
      lcd.setCursor(10, 0);
      if(second < 10)
        lcd.print("0");
      lcd.print(second);
    break;
  }
}

void displayClock() {
  lcd.setCursor(4, 0);
  if(hour < 10)
    lcd.print("0");
  lcd.print(hour);
  lcd.print(":");
  if(minute < 10)
    lcd.print("0");
  lcd.print(minute);
  lcd.print(":");
  if(second < 10)
    lcd.print("0");
  lcd.print(second);
}

void displayStopwatch() {
  lcd.setCursor(3, 0);
  lcd.print("STOPWATCH:");
  lcd.setCursor(4, 1);
  if(stopwatchMin < 10)
    lcd.print("0");
  lcd.print(stopwatchMin);
  lcd.print(":");
  if(stopwatchSec < 10)
    lcd.print("0");
  lcd.print(stopwatchSec);
  lcd.print(":");
  if(centiSec < 10)
    lcd.print("0");
  lcd.print(centiSec);
}

void blinkTime() {
  count4++;
  if(count4 > 50) {
    count4 = 0;
    switch(Mode) {
      case 1:
        count5 = 0;
        while(count5 <= 50) {
          lcd.setCursor(4, 0);
          lcd.print("  ");
          count5++;
        }
      break;
      case 2:
        count5 = 0;
        while(count5 <= 50) {
          lcd.setCursor(7, 0);
          lcd.print("  ");
          count5++;
        }
      break;
      case 3:
        count5 = 0;
        while(count5 <= 50) {
          lcd.setCursor(10, 0);
          lcd.print("  ");
          count5++;
        }
      break;
    }
  }
}

enum {
  STATE0,
  STATE1,
  STATE2
} eState;

void increaseTimeState() {
  switch(eState) {
    case STATE0:
      if(fIncreaseButton) {
        increaseTime();
        eState = STATE1;
      }
    break;
    case STATE1:
      if(!fIncreaseButton)
        eState = STATE0;
      else if(fIncreaseButtonPressed1s)
        eState = STATE2;
    break;
    case STATE2:
      if(count2 == 20)
        increaseTime();
      if(!fIncreaseButton)
        eState = STATE0;
    break;
  }
}
 
enum {
  MODE0,
  MODE1,
  MODE2,
  MODE3,
  MODE4,
  MODE5,
  MODE6
} eMode;

void clockMode() {
  switch(eMode) {
    case MODE0:
      Serial.println("mode 0");
      displayClock();
      if(Mode == 1) {
        lcd.clear();
        eMode = MODE1;
      }
    break;
    case MODE1:
      Serial.println("mode 1");
      displayClock();
      blinkTime();
      if(Mode == 2) {
        lcd.clear();
        eMode = MODE2;
      }
    break;
    case MODE2:
      Serial.println("mode 2");
      displayClock();
      blinkTime();
      if(Mode == 3) {
        lcd.clear();
        eMode = MODE3;
      }
    break;
    case MODE3:
      Serial.println("mode 3");
      displayClock();
      blinkTime();
      if(Mode == 4) {
        lcd.clear();
        eMode = MODE4;
      }
    break;
    case MODE4:
      Serial.print(hour);
      Serial.print(":");
      Serial.print(minute);
      Serial.print(":");
      Serial.print(second);
      Serial.print("------->");
      Serial.println("mode 4-0");
      if(!flag) {
        stopwatchMin = 0;
        stopwatchSec = 0;
        centiSec = 0;
      }
      displayStopwatch();
      if(Mode == 0) {
        stopwatchMode = 0;
        lcd.clear();
        eMode = MODE0;
      }
      else if(stopwatchMode == 1)
        eMode = MODE5;
    break;
    case MODE5:
      Serial.print(hour);
      Serial.print(":");
      Serial.print(minute);
      Serial.print(":");
      Serial.print(second);
      Serial.print("------->");
      Serial.println("mode 4-1");
      flag = true;
      displayStopwatch();
      if(Mode == 0) {
        lcd.clear();
        eMode = MODE0;
      }
      else if(stopwatchMode == 2)
        eMode = MODE6;
    break;
    case MODE6:
      Serial.print(hour);
      Serial.print(":");
      Serial.print(minute);
      Serial.print(":");
      Serial.print(second);
      Serial.print("------->");
      Serial.println("mode 4-2");
      flag = false;
      displayStopwatch();
      if(Mode == 0) {
        stopwatchMode = 0;
        lcd.clear();
        eMode = MODE0;
      }
    break;
  }
}
