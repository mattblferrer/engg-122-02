// FERRER, Matt Brycen L.

#include <LiquidCrystal.h>
// define pins and modules
const int rs = 9, en = 8, d4 = 7, d5 = 6, d6 = 5, d7 = 4;  
const int hr = 3, mn = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// define variables for digital clock
int hours = 0, minutes = 0, seconds = 0, tenths = 0;
bool isAM = true;

void printTime(int hours, int minutes, int seconds) {
  lcd.setCursor(0, 0);
  lcd.print("FERRER, Matt");
  lcd.setCursor(0, 1);
  if (hours < 9) {  // print leading zero for hours
    lcd.print("0");
  }
  lcd.print(hours + 1, DEC);
  lcd.print(":");
  if (minutes < 10) {  // print leading zero for minutes
    lcd.print("0");
  }
  lcd.print(minutes, DEC);
  lcd.print(":");
  if (seconds < 10) {  // print leading zero for seconds
    lcd.print("0");
  }
  lcd.print(seconds, DEC);
  if (isAM) {
    if (hours == 11) {  // special case for 12 AM
      lcd.print(" PM");
    } 
    else {
      lcd.print(" AM");
    }
  } 
  else {
    if (hours == 11) {  // special case for 12 PM
      lcd.print(" AM");
    } 
    else {
      lcd.print(" PM");
    }
  }
}

void setup()
{
  pinMode(hr, INPUT);
  pinMode(mn, INPUT);
  lcd.begin(16, 2);
  printTime(hours, minutes, seconds);
}

void loop()
{
  tenths++;
  int hrReading = digitalRead(hr);
  int mnReading = digitalRead(mn);

  if (hrReading == HIGH) {
    hours++;
  }
  if (mnReading == HIGH) {
    minutes++;
  }
  if (tenths > 9) {
    tenths = 0;
    seconds++;
  }
  if (seconds > 59) {
    seconds = 0;
    minutes++;
  }
  if (minutes > 59) {
    minutes -= 60;
    hours++;
  }
  if (hours > 11) {
    hours -= 12;
    isAM = !isAM;
  }
  
  printTime(hours, minutes, seconds);
  delay(100);
}