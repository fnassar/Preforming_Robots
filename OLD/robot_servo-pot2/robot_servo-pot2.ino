/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013
  by Scott Fitzgerald
  https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
// twelve servo objects can be created on most boards

int pos = 0;  // variable to store the servo position
const int pos11 = 0;
const int pos12 = 20;
int pos2 = 0;
int pos3 = 0;

void setup() {
  myservo1.attach(19);  // m1
  myservo2.attach(21);  // m2
  myservo3.attach(20);  // m3
  Serial.begin(9600);
}

void loop() {
  pos2 = 45;
  pos3 = 105;
  myservo1.write(pos);  // tell servo to go to position in variable 'pos'
  myservo2.write(pos2);

  for (pos = pos11; pos <= pos12; pos += 1) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree

    pos2 += 1;
    pos3 += 1;
    Serial.print("pos1 ");
    Serial.print(pos);

    Serial.print("    pos2 ");
    Serial.print(pos2);

    Serial.print("    pos3 ");
    Serial.println(pos3);

    myservo1.write(pos);  // tell servo to go to position in variable 'pos'
    myservo2.write(pos2);
    myservo3.write(pos3);
    delay(40);  // waits 15 ms for the servo to reach the position
  }
  for (pos = pos12; pos >= pos11; pos -= 1) {  // goes from 180 degrees to 0 degrees
    pos2 -= 1;
    pos3 -= 1;
    Serial.print("pos1 ");
    Serial.print(pos);

    Serial.print("    pos2 ");
    Serial.print(pos2);

    Serial.print("    pos3 ");
    Serial.println(pos3);

    myservo1.write(pos);  // tell servo to go to position in variable 'pos'
    myservo2.write(pos2);
    myservo3.write(pos3);
    delay(40);  // waits 15 ms for the servo to reach the position
  }
  // delay(50);
}
