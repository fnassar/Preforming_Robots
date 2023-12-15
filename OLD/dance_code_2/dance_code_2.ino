void setup() {
  // Pins 2 and 3 are connected to In1 and In2 respectively
  // of the L298 motor driver
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop() {

  //half turn in one direction
  oneWheelCW(1000);
  stop();

  //half turn in the other direction
  oneWheelACW(1000);
  stop();

  //full turn
  twoWheelCW(2000);
  stop();


  //go forward
  front(2000);
  stop();

  //go backward
  back(2000);
  stop();


}

void stop() {
  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(10, LOW);
  delay(500);
}

void back(int delayy) {
  digitalWrite(3, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(10, LOW);
  delay(delayy);
}
void front(int delayy) {
  digitalWrite(3, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(10, HIGH);
  delay(delayy);
}
void oneWheelCW(int delayy) { // delayy controls angle to turn
  digitalWrite(3, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(10, LOW);
  delay(delayy);

}
void oneWheelACW(int delayy) { // delayy controls angle to turn
  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(10, LOW);
  delay(delayy);
}

void twoWheelCW(int delayy) {
  digitalWrite(3, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(10, LOW);
  delay(delayy);
}

void twoWheelACW(int delayy) {
  digitalWrite(3, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(10, HIGH);
  delay(delayy);
}
