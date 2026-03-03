#define ANALOG_IN A0
#define RED 9
#define GREEN 10
#define BLUE 11

void setup() {
  Serial.begin(9600);
  pinMode(ANALOG_IN, INPUT_PULLUP);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop() {
  double reading = analogRead(ANALOG_IN);  // from 0 to 1023
  double volts = reading * 5 / 1024;  // scale assuming max of 5 volts
  double ranges[7] = {0.70, 1.40, 2.10, 2.80, 3.50, 4.20, 5.00};  // top thresholds for every color
  double colors[7][3] = {
    {255, 0, 0},  // red
    {255, 165, 0},  // orange
    {255, 255, 0},  // yellow
    {0, 255, 0},  // green
    {0, 0, 255},  // blue
    {75, 0, 130},  // indigo
    {0, 255, 255}  // violet
  };
  for (int i = 0; i < 7; i++) {
    if (volts > ranges[i]) {  // check which range the potentiometer selected
      analogWrite(RED, colors[i][0]); 
      analogWrite(GREEN, colors[i][1]);  
      analogWrite(BLUE, colors[i][2]);
    }
  }
  delay(100);
}
