#include <Keypad.h>

// keypad parameters
const byte ROWS = 4;
const byte COLS = 4;
char keypadKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {12, 11, 10, 9}; 
byte colPins[COLS] = {8, 7, 4, 2}; 
Keypad keypad = Keypad(makeKeymap(keypadKeys), rowPins, colPins, ROWS, COLS);

// RGB LED parameters
const int RED = 6;
const int GREEN = 3;
const int BLUE = 5;

void setColor(int r, int g, int b) {
  analogWrite(RED, r);
  analogWrite(GREEN, g);
  analogWrite(BLUE, b);
}

void setup() {
  Serial.begin(9600);
  
  // set pins of RGB LED to OUTPUT
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    switch (key) {
      case '1': setColor(255, 0, 0); break;
      case '2': setColor(0, 255, 255); break;
      case '3': setColor(255, 255, 0); break;
      case '4': setColor(0, 255, 128); break;
      case '5': setColor(128, 0, 128); break;
      case '6': setColor(255, 165, 0); break;
      case '7': setColor(75, 0, 130); break;
      case '8': setColor(0, 255, 0); break;
      case '9': setColor(255, 20, 147); break;
      case 'A': setColor(173, 216, 230); break;
      case 'B': setColor(210, 105, 30); break;
      case 'C': setColor(128, 128, 128); break;
      case 'D': setColor(255, 255, 255); break;
      case '0': setColor(0, 0, 0); break;
      case '*': setColor(192, 192, 192); break;
      case '#': setColor(255, 69, 0); break;
    }
  }
}
