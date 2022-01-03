//#include "DigitalClock.h"
//#include <Arduino.h>
//
//void readModeButton() {
//  firstReadModeButton = secondReadModeButton;
//  secondReadModeButton = digitalRead(MODE_BUTTON);
//  if(secondReadModeButton != firstReadModeButton) {
//    if(firstReadModeButton) {
//      Mode++;
//      if(Mode > 4)
//        Mode = 0;
//    }
//  }
//}
//
//void readIncreaseButton() {
//  firstReadIncreaseButton = secondReadIncreaseButton;
//  secondReadIncreaseButton = digitalRead(INCREASE_BUTTON);
//  if(secondReadIncreaseButton == firstReadIncreaseButton) {
//    if(firstReadIncreaseButton) {
//      fIncreaseButton = 1;
//      count1++;
//      if(count1 > 100) {
//        fIncreaseButtonPressed1s = 1;
//        count2++;
//        if(count2 > 20)
//          count2 = 0;
//      }
//    }
//    else {
//      fIncreaseButton = 0;
//      fIncreaseButtonPressed1s = 0;
//      count1 = 0;
//      count2 = 0;
//    }
//  }
//  else if(Mode == 4) {
//    if(firstReadIncreaseButton) {
//      stopwatchMode++;
//      if(stopwatchMode > 2)
//        stopwatchMode = 0;
//    }
//  }
//}
//
//void clockCounter() {
//  count3++;
//  if(count3 > 99) {
//    count3 = 0;
//    second++;
//    if(second > 59) {
//      second = 0;
//      minute++;
//      if(minute > 59) {
//        minute = 0;
//        hour++;
//        if(hour > 23) 
//          hour = 0;
//      }
//    }
//  }
//}
//
//void stopwatchCounter() {
//  if(flag) {
//    centiSec++;
//    if(centiSec > 99) {
//      centiSec = 0;
//      stopwatchSec++;
//      if(stopwatchSec > 59) {
//        stopwatchSec = 0;
//        stopwatchMin++;
//        if(stopwatchMin > 59) 
//          stopwatchMin = 0;
//      }
//    }
//  }  
//}
//
//enum {
//  STATE0,
//  STATE1,
//  STATE2
//} eState;
//
//void increaseTimeState() {
//  switch(eState) {
//    case STATE0:
//      if(fIncreaseButton) {
//        increaseTime();
//        eState = STATE1;
//      }
//    break;
//    case STATE1:
//      if(!fIncreaseButton)
//        eState = STATE0;
//      else if(fIncreaseButtonPressed1s)
//        eState = STATE2;
//    break;
//    case STATE2:
//      if(count2 == 20)
//        increaseTime();
//      if(!fIncreaseButton)
//        eState = STATE0;
//    break;
//  }
//}
