//move forward
int M1DIR = 8;
int M2DIR = 11;
int M1RUN = 9;
int M2RUN = 10;

void setup() {
  for (int i = 8; i <= 11; i++) {
     pinMode(i, OUTPUT);
  }
}

void loop() {
  // 1 - move forward
  digitalWrite(M1DIR, HIGH);
  digitalWrite(M2DIR, HIGH);
  analogWrite(M1RUN, 200);
  analogWrite(M2RUN, 200);
  delay(1000);

  // 2 - tight turn right and move forward
  digitalWrite(M1DIR, HIGH);
  digitalWrite(M2DIR, LOW);
  analogWrite(M1RUN, 200);
  analogWrite(M2RUN, 200);
  delay(1300);
  digitalWrite(M1DIR, HIGH);
  digitalWrite(M2DIR, HIGH);
  analogWrite(M1RUN, 200);
  analogWrite(M2RUN, 200);
  delay(1000);

  // 3 - 90 deg turn left and move forward
  digitalWrite(M1DIR, LOW);
  digitalWrite(M2DIR, LOW);
  analogWrite(M1RUN, 200);
  analogWrite(M2RUN, 0);
  delay(1500);
  digitalWrite(M1DIR, HIGH);
  digitalWrite(M2DIR, HIGH);
  analogWrite(M1RUN, 200);
  analogWrite(M2RUN, 200);
  delay(1000);

  // 4 - tight turn right and move forward
  digitalWrite(M1DIR, HIGH);
  digitalWrite(M2DIR, LOW);
  analogWrite(M1RUN, 200);
  analogWrite(M2RUN, 200);
  delay(1300);
  digitalWrite(M1DIR, HIGH);
  digitalWrite(M2DIR, HIGH);
  analogWrite(M1RUN, 200);
  analogWrite(M2RUN, 200);
  delay(1000);

  for (int i = 8; i <= 11; i++) {  // stop motors
    digitalWrite(i, LOW);
  }
  while (1);  // halt program
}
