// FERRER, Matt Brycen L.

const float outofrange = 335.0; 

int touchPin = 13;
int trigPin = 12;
int echoPin = 11;

float Vs = 331.5 + 0.6 * 21; // sound velocity formula in m/s
//25 deg C, assumed room temperature

void setup() {
  Serial.begin(9600);
  pinMode(touchPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // measure distance from touch sensor
  int touch = digitalRead(touchPin);
  if (touch == HIGH) {
    // send sound pulse 10us TTL
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // listen for echo, tS in microseconds (us)
    float tS = pulseIn(echoPin, HIGH);
    // get half round-trip time, RTT_half
    float RTT_half = tS / 2.0;
    // convert sound velocity Vs (m/s) to Vcmus (cm/us)
    float Vcmus = Vs / 10000.0;
    // distance Dcm in centimeters (cm)
    float Dcm = Vcmus * RTT_half;

    // print measured distance in cm
    if (Dcm > outofrange) Serial.println("Out of range");
    else {
      Serial.print("Distance = ");
      Serial.print(Dcm);
      Serial.println(" cm");
    }
  }
  
  delay(200); //delay between sonar distance readings
}
