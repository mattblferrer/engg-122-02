// define inputs, output LEDs, state, and time variables
const int keyInput = A3;
const int ignitionInput = A4;
const int seatbeltInput = A5;
const int LEDOff = 13;
const int LEDAccessory = 12;
const int LEDIgnition = 11;
const int LEDSingleLED = 10;
const int LEDSpeed = 9;
const int LEDAlarmHigh = 8;
const int LEDAlarmLow = 2;
enum states{off, accessory, ignition, singleLED, alarm};
auto currentState = off;
long long ignitionTime = 0;
long long blinkTime = 0;

// function to reset the ignition and blink timers
void resetTimer() {
  ignitionTime = millis();
  blinkTime = millis();
}

// function that blinks the alarm LEDs
void blinkAlarmLEDs(bool on) {
  long long currentTime = millis();
  if (!on) {  // alarm is off
    for (int i = LEDAlarmLow; i <= LEDAlarmHigh; i++) {
      digitalWrite(i, LOW);
    }
    blinkTime = currentTime;
    return;
  }
  if (currentTime - blinkTime >= 1000) {  // alarm is on and has to blink
    for (int i = LEDAlarmLow; i <= LEDAlarmHigh; i++) {
      if (digitalRead(i) == HIGH) {
        digitalWrite(i, LOW);
      }
      else {
        digitalWrite(i, HIGH);
      }
    }
    blinkTime = currentTime;
  }
}

// function that updates the LEDs to their corresponding outputs according to state
void updateLEDs() {
  switch (currentState) {
    case off:
      digitalWrite(LEDOff, HIGH);
      digitalWrite(LEDAccessory, LOW);
      digitalWrite(LEDIgnition, LOW);
      digitalWrite(LEDSingleLED, LOW);
      digitalWrite(LEDSpeed, LOW);
      blinkAlarmLEDs(false);
      break;
    
    case accessory:
      digitalWrite(LEDOff, LOW);
      digitalWrite(LEDAccessory, HIGH);
      digitalWrite(LEDIgnition, LOW);
      digitalWrite(LEDSingleLED, LOW);
      digitalWrite(LEDSpeed, LOW);
      blinkAlarmLEDs(false);
      break;

    case ignition:
      digitalWrite(LEDOff, LOW);
      digitalWrite(LEDAccessory, LOW);
      digitalWrite(LEDIgnition, HIGH);
      digitalWrite(LEDSingleLED, LOW);
      digitalWrite(LEDSpeed, LOW);
      blinkAlarmLEDs(false);
      break;

    case singleLED:
      digitalWrite(LEDOff, LOW);
      digitalWrite(LEDAccessory, LOW);
      digitalWrite(LEDIgnition, HIGH);
      digitalWrite(LEDSingleLED, HIGH);
      digitalWrite(LEDSpeed, LOW);
      blinkAlarmLEDs(false);
      break;

    case alarm:
      digitalWrite(LEDOff, LOW);
      digitalWrite(LEDAccessory, LOW);
      digitalWrite(LEDIgnition, HIGH);
      digitalWrite(LEDSingleLED, HIGH);
      digitalWrite(LEDSpeed, HIGH);
      blinkAlarmLEDs(true);
      break;
  }
}

void setup() {
  Serial.begin(9600);
  for (int i = LEDAlarmLow; i <= LEDOff; i++) {  // set output LED pins
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }  
  // set input button pins
  pinMode(keyInput, INPUT_PULLUP);  
  pinMode(ignitionInput, INPUT_PULLUP);
  pinMode(seatbeltInput, INPUT_PULLUP);
  updateLEDs();
}

void loop() {
  bool key = !digitalRead(keyInput);  // negative logic on buttons
  bool ign = !digitalRead(ignitionInput);
  bool seat = !digitalRead(seatbeltInput);
  long long currentTime = millis();  // for tracking ignition and alarm blinking times

  switch (currentState) {
    case off:
      if (key) {  // If the driver turns ON the key, the next state is in Accessory Mode
        currentState = accessory;
        updateLEDs();
      }
      resetTimer();
      break;

    case accessory:
      if (ign) {  // If the Ignition is turned ON, the next state is in Ignition Mode
        currentState = ignition;
        updateLEDs();
      }
      // Can ONLY go back to the initial state from the Accessory Mode when the key is turned OFF
      if (!key) {  
        currentState = off;
        updateLEDs();
      }
      resetTimer();
      break;

    case ignition:
      // During Ignition Mode, if after 5 seconds the seat belt is not yet fastened, a 
      // single LED notification will light up
      if ((currentTime - ignitionTime >= 5000) && (!seat)) {
        currentState = singleLED;
        updateLEDs();
      }
      if (seat || (!key) || (!ign)) {
        currentState = accessory;
        updateLEDs();
        resetTimer();
      }
      break;

    case singleLED:
      // If seat belt is still not fastened and the speed is at least 10kph (LED D9), 
      // a per-second blinking alarm will commence
      if ((currentTime - ignitionTime >= 10000) && (!seat)) {
        currentState = alarm;
        updateLEDs();
      }
      if (seat || (!key) || (!ign)) {
        currentState = accessory;
        updateLEDs();
        resetTimer();
      }
      break; 

    case alarm:
      if (seat || (!key) || (!ign)) {
        currentState = accessory;
        resetTimer();
      }
      updateLEDs();
      break;
  }
}
