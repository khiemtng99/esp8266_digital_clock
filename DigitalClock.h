#ifndef DIGITAL_CLOCK_H
#define DIGITAL_CLOCK_H

#define MODE_BUTTON 4
#define INCREASE_BUTTON 5 

int firstReadModeButton = 0;
int secondReadModeButton = 0;
int Mode = 0;

int firstReadIncreaseButton = 0;
int secondReadIncreaseButton = 0;
int fIncreaseButton = 0;
int fIncreaseButtonPressed1s = 0;
int stopwatchMode = 0;

int count1 = 0;
int count2 = 0;
int count3 = 0;
int count4 = 0;
int count5 = 0;

bool flag = false;

int hour = 0;
int minute = 0;
int second = 0;
int stopwatchMin = 0;
int stopwatchSec = 0;
int centiSec = 0;

void readModeButton();
void readIncreaseButton();

void increaseTime();
void blinkTime();

void clockCounter();
void stopwatchCounter();

void displayClock();
void displayStopwatch();

void increaseTimeState();
void clockMode();

#endif
