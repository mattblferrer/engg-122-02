#define START_LED 2
#define END_LED 9

void setup() {
  Serial.begin(9600);
  for (int i = START_LED; i <= END_LED; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void loop() {
  for (int parity = 0; parity < 2; parity++) {
    for (int i = parity; i < 256; i += 2) {
      Serial.print("Decimal: ");
      Serial.print(i);
      Serial.print(" Hexadecimal: ");
      Serial.print(i, HEX);
      Serial.print(" Octal: ");
      Serial.print(i, OCT);
      Serial.print(" Binary: ");
      Serial.println(i, BIN);

      int test = i;
      int bit = 128;
      int led = END_LED;
      while (bit > 0) {
        if (test >= bit) {
          digitalWrite(led, HIGH);
          test -= bit;
        }
        else {
          digitalWrite(led, LOW);
        }
        bit /= 2;
        led -= 1;
      }
      delay(500);
    }
  }
}
