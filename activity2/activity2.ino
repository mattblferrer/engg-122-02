#define A A5
#define B A4
#define C A3
#define START_LED 2
#define END_LED 9

void binaryWrite8bit(int n, int start) {
  int bit = 128;
  int led = start + 7;  // starting with MSB
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
  pinMode(A, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);
  pinMode(C, INPUT_PULLUP);

  for (int i = START_LED; i <= END_LED; i++) {  // output LED pins 2 to 9
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void loop() {
  int values[7][5] = {
    {0, 24, 60, 102, 195},
    {15, 63, 111, 207, 0},
    {240, 252, 246, 243, 0},
    {255, 255, 255, 255, 0},
    {0, 24, 102, 195, 0},
    {0, 48, 96, 192, 0},
    {0, 12, 6, 3, 0},
  };  // values for each pattern with ABC = 000 to 111 (0 to 7, or 8 choices)

  int abc = digitalRead(A) * 4 + digitalRead(B) * 2 + digitalRead(C);  // input read 
  Serial.println(abc);

  // converted decimal values to 8-bit LED outputs
  if (abc == 0) {  // 0 0 0 (5 values)
    for (int i = 0; i < 5; i++) {  // display 5 values in sequence
      binaryWrite8bit(values[0][i], START_LED);
      delay(500);
    }
  }
  else if (abc == 7) {   // 1 1 1 (starting pattern 0 all)
    binaryWrite8bit(0, START_LED);
    delay(500);
  }
  else {  // (4 values)
    for (int i = 0; i < 4; i++) {  // display 4 values in sequence
      binaryWrite8bit(values[abc][i], START_LED);
      delay(500);
    }
  }
}
