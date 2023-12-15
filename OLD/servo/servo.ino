#define moto1 5
#define moto2 3

#include <Servo.h>

Servo servo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(9600);
  servo.attach(moto1);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  servo.write(45);                   // tell servo to go to position in variable 'pos'
  Serial.print("positive: ");
  Serial.println(45);
  delay(5000);                          // waits 10ms for the servo to reach the position
  servo.write(20);                   // tell servo to go to position in variable 'pos'
  Serial.print("positive: ");
  Serial.println(20);
  delay(5000);    
  //  for (pos = 0; pos <= 90; pos += 1) { // rotate from 0 degrees to 180 degrees
  //    // in steps of 1 degree
  //    servo.write(pos);                   // tell servo to go to position in variable 'pos'
  //    Serial.print("positive: ");
  //    Serial.println(pos);
  //    delay(10);                          // waits 10ms for the servo to reach the position
  //  }
  //
  //  for (pos = 90; pos >= 0; pos -= 1) { // rotate from 180 degrees to 0 degrees
  //    servo.write(pos);                   // tell servo to go to position in variable 'pos'
  //    Serial.print("negative: ");
  //    Serial.println(pos);
  //    delay(10);                          // waits 10ms for the servo to reach the position
  //  }
}
