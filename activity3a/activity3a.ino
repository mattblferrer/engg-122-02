#define ANALOG_IN A0
#define START_LED 2
#define END_LED 11

void binaryWrite10bit(int n, int start) {
  int bit = 512;
  int led = start + 9;  // starting with MSB
  while (bit > 0) {  // calculate from MSB to LSB
    if (n >= bit) {  // 1
      digitalWrite(led, HIGH);
      n -= bit;
    }
    else {  // 0
      digitalWrite(led, LOW);
    }
    bit /= 2;
    led -= 1;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(ANALOG_IN, INPUT_PULLUP);

  for (int i = START_LED; i <= END_LED; i++) {  // output LED pins 2 to 11
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void loop() {
  double reading = analogRead(ANALOG_IN);  // from 0 to 1023
  int scale = reading * 11 / 1023;  // scale in steps of 0.5 volts and floor
  double volts = reading * 5 / 1023;  // real volt reading (assuming 5 volts max)
  int led[11] = {0, 1, 3, 7, 15, 31, 63, 127, 255, 511, 1023};  // mapping from reading to LED output

  // print raw and volt reading read from analog input
  Serial.print("Analog Reading: ");
  Serial.print(reading);
  Serial.print(" Volts: ");
  Serial.println(volts);  
  binaryWrite10bit(led[scale], START_LED);
  delay(100);
}
