/*
  m1->19
  m2->21
  m3->20
  m4->16
  m5->18
  m6->17
*/
// code : https://github.com/michaelshiloh/resourcesForClasses/tree/master/src/arduinoSketches/nRF24L01/rf24PerformingRobotsTemplate_2023
#define m1 19
#define m2 21
#define m3 20
#define m4 16
#define m5 18
#define m6 17
// ================================================
// ============= RADIO DECLARE BEGIN ==============
// ================================================

const int NRF_CE_PIN = A11, NRF_CSN_PIN = A15;

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(NRF_CE_PIN, NRF_CSN_PIN);  // CE, CSN
const byte addr = 0x76;               // change as per the above assignment
const int RF24_CHANNEL_NUMBER = 30;   // change as per the above assignment

// Do not make changes here
const byte xmtrAddress[] = { addr, addr, 0xC7, 0xE6, 0xCC };
const byte rcvrAddress[] = { addr, addr, 0xC7, 0xE6, 0x66 };

const int RF24_POWER_LEVEL = RF24_PA_LOW;

// global variables
uint8_t pipeNum;
unsigned int totalTransmitFailures = 0;

struct DataStruct {
  uint8_t stateNumber;
};
DataStruct data;

// ================================================
// ============== RADIO DECLARE END ===============
// ================================================

// ================================================
// ============= SERVO DECLARE BEGIN ==============
// ================================================

#include <Servo.h>

Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
// twelve servo objects can be created on most boards

int pos = 0;  // variable to store the servo position
const int pos11 = 0;
const int pos12 = 20;
int pos2 = 45;
int pos3 = 105;


unsigned long previousMillis = 0;  // Variable to store timekeeping
const int intervalServo = 50;      // Interval between servo movements in milliseconds


// Servo library
// #include <Servo.h>
// Servo motors
// const int NOSE_SERVO_PIN = 19; // TODO why doesn't pin 21 work?
// const int ANTENNA_SERVO_PIN = 10;
// const int TAIL_SERVO_PIN = 11;
// const int GRABBER_SERVO_PIN = 12;
// Servo nose;  // change names to describe what's moving
// Servo antenna;
// Servo tail;
// Servo grabber;
// Servo disk;

// ================================================
// ============== SERVO DECLARE END ===============
// ================================================

// ================================================
// ============ NEOPIXEL DECLARE BEGIN ============
// ================================================

// Additional libraries for graphics on the Neo Pixel Matrix
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#ifndef PSTR
#define PSTR  // Make Arduino Due happy
#endif

// const int NEOPIXELPIN = 18;
// const int NUMPIXELS = 64;

// Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);
//  Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, NEOPIXELPIN,
//                              NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
//                              NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
//                              NEO_GRB            + NEO_KHZ800);

const int NEOPIXELPIN = 17;  // Neopixel pin for the mouth
#define NUMPIXELS_MOUTH 64   // Number of pixels in the mouth matrix

const int NUMPIXELS = 18;    // Neopixel pin for the other LED strip
#define NUMPIXELS_OTHER 180  // Number of pixels in the other LED strip

Adafruit_NeoPixel pixelsMouth = Adafruit_NeoPixel(NUMPIXELS_MOUTH, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixelsOther = Adafruit_NeoPixel(NUMPIXELS_OTHER, NUMPIXELS, NEO_GRB + NEO_KHZ800);

int ledState = LOW;
// unsigned long previousMillis = 0;
const long interval = 10;
int currentLED = 0;

int mouthClosed[] = { 18, 19, 20, 21, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 42, 43, 44, 45 };
int mouthOpen[] = { 3, 4, 10, 11, 12, 13, 17, 18, 21, 22, 24, 25, 30, 31, 32, 33, 38, 39, 41, 42, 45, 46, 50, 51, 52, 53, 59, 60 };

int currentState = 0;  // 0 for closed mouth, 1 for open mouth
unsigned long previousMouthMillis = 0;
const unsigned long CLOSED_DELAY = 500;  // Delay for closed mouth (in milliseconds)
const unsigned long OPEN_DELAY = 500;    // Delay for open mouth (in milliseconds)

// ================================================
// ============= NEOPIXEL DECLARE END =============
// ================================================

// ================================================
// ============= MUSIC DECLARE BEGIN ==============
// ================================================

// Additional libraries for music maker shield
#include <Adafruit_VS1053.h>
#include <SD.h>

// Adafruit music maker shield
#define SHIELD_RESET -1  // VS1053 reset pin (unused!)
#define SHIELD_CS 7      // VS1053 chip select pin (output)
#define SHIELD_DCS 6     // VS1053 Data/command select pin (output)
#define CARDCS 4         // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3  // VS1053 Data request, ideally an Interrupt pin
Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

// ================================================
// ============== MUSIC DECLARE END ===============
// ================================================

// ================================================
// ================== IDKK BEGIN ==================
// ================================================

// change as per your robot
// const int NOSE_WRINKLE = 45;
// const int NOSE_TWEAK = 90;
// const int TAIL_ANGRY = 0;
// const int TAIL_HAPPY = 180;
// const int GRABBER_RELAX = 0;
// const int GRABBER_GRAB = 180;

// ================================================
// ================== IDKK END ====================
// ================================================

void setup() {
  Serial.begin(9600);
  // printf_begin();

  // Set up all the attached hardware
  setupMusicMakerShield();
  setupServoMotors();
  setupNeoPixels();

  setupRF24();

  // Brief flash to show we're done with setup()
  //  flashNeoPixels();
}
// ================================================
// =============== SETUP FUNCTIONS ================
// ================================================
void setupRF24Common() {

  // RF24 setup
  if (!radio.begin()) {
    Serial.println(F("radio  initialization failed"));
    while (1)
      ;
  } else {
    Serial.println(F("radio successfully initialized"));
  }

  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(RF24_CHANNEL_NUMBER);
  radio.setPALevel(RF24_POWER_LEVEL);
}
void setupRF24() {
  setupRF24Common();

  // Set us as a receiver
  radio.openWritingPipe(rcvrAddress);
  radio.openReadingPipe(1, xmtrAddress);

  // radio.printPrettyDetails();
  Serial.println(F("I am a receiver"));
}

void setupMusicMakerShield() {
  if (!musicPlayer.begin()) {  // initialise the music player
    Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
    while (1)
      ;
  }
  Serial.println(F("VS1053 found"));

  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD card failed or not present"));
    while (1)
      ;  // don't do anything more
  }

  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(20, 20);

  // Timer interrupts are not suggested, better to use DREQ interrupt!
  // musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT); // timer int

  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int
}

void setupServoMotors() {
  myservo1.attach(m1);  // m1
  myservo2.attach(m2);  // m2
  myservo3.attach(m3);  // m3
}

void setupNeoPixels() {
  pixelsMouth.begin();
  pixelsMouth.setBrightness(50);  // Set the brightness (0-255)

  pixelsOther.begin();
}

// ================================================
// ================== SETUP END ===================
// ================================================

// ================================================
// =============== LOOP FUNCTIONS =================
// ================================================

// Function to display mouth based on provided positions for a specific Neopixel strip
void displayMouth(Adafruit_NeoPixel &strip, int mouth[], int size, uint32_t color) {
  strip.clear();
  for (int i = 0; i < size; i++) {
    strip.setPixelColor(mouth[i], color);
  }
  strip.show();
}

void ledStrip(int num) {
  // while (true) {
  if (num == 1 || num == 3) {
    unsigned long currentMillis = millis();
    // Handling the other LED strip
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

      pixelsOther.clear();
      pixelsOther.setPixelColor(currentLED, pixelsOther.Color(0, 150, 0));
      pixelsOther.show();

      currentLED = (currentLED + 1) % NUMPIXELS_OTHER;
    }
  }
  // mouth
  if (num == 2 || num == 3) {
    unsigned long currentMouthMillis = millis();
    if (currentState == 0) {                                                                           // Closed mouth
      displayMouth(pixelsMouth, mouthClosed, sizeof(mouthClosed) / sizeof(mouthClosed[0]), 0xFF0000);  // Change color as needed
      if (currentMouthMillis - previousMouthMillis >= CLOSED_DELAY) {
        previousMouthMillis = currentMouthMillis;
        currentState = 1;  // Change state to open mouth
      }
    } else {                                                                                     // Open mouth
      displayMouth(pixelsMouth, mouthOpen, sizeof(mouthOpen) / sizeof(mouthOpen[0]), 0xFF0000);  // Change color as needed
      if (currentMouthMillis - previousMouthMillis >= OPEN_DELAY) {
        previousMouthMillis = currentMouthMillis;
        currentState = 0;  // Change state to closed mouth
      }
    }
  }
}

void dance(int num) {
  unsigned long currentMillis = millis();  // Get the current time


  if (currentMillis - previousMillis >= intervalServo) {  // Check if it's time to move the servos
    previousMillis = currentMillis;                       // Save the current time for the next iteration

    if (pos11 <= pos12) {  // First loop: from pos1 to pos2
      pos2 += 1;
      pos3 += 2;
      myservo1.write(pos);  // Move servos
      myservo2.write(pos);
      myservo3.write(pos3);
      pos++;                                     // Increment position
    } else if (pos11 > pos12 && pos >= pos11) {  // Second loop: from pos2 to pos1
      pos2 -= 1;
      pos3 -= 2;
      myservo1.write(pos);  // tell servo to go to position in variable 'pos'
      myservo2.write(pos2);
      myservo3.write(pos3);
      delay(40);  // Decrement position
    }


    if (pos == pos11 && pos3 == 105) {  // Check if the sequence has completed
      delay(50);                      // Add a delay before restarting the sequence
    }
  }
}

void talkingMouth() {
  int count = 1;
  while (true) {
    unsigned long currentMouthMillis = millis();
    if (currentState == 0) {                                                                           // Closed mouth
      displayMouth(pixelsMouth, mouthClosed, sizeof(mouthClosed) / sizeof(mouthClosed[0]), 0xFF0000);  // Change color as needed
      if (currentMouthMillis - previousMouthMillis >= CLOSED_DELAY) {
        previousMouthMillis = currentMouthMillis;
        currentState = 1;  // Change state to open mouth
        count += 1;
      }
    } else {                                                                                     // Open mouth
      displayMouth(pixelsMouth, mouthOpen, sizeof(mouthOpen) / sizeof(mouthOpen[0]), 0xFF0000);  // Change color as needed
      if (currentMouthMillis - previousMouthMillis >= OPEN_DELAY) {
        previousMouthMillis = currentMouthMillis;
        currentState = 0;  // Change state to closed mouth
      }
    }
    if (count == 5) {
      break;
    }
  }
}

// ================================================
// ============== LOOP FUNCTIONS END ==============
// ================================================

void loop() {
  // If there is data, read it,
  // and do the needfull
  // Become a receiver
  radio.startListening();

  if (radio.available(&pipeNum)) {
    radio.read(&data, sizeof(data));
    Serial.print(F("message received Data = "));
    Serial.print(data.stateNumber);
    Serial.println();

    switch (data.stateNumber) {
      case 0:
        while (true) {
          radio.read(&data, sizeof(data));
          pixelsOther.clear();
          // tail.write(TAIL_ANGRY);
          if (data.stateNumber != 0) {
            break;
          }
        }
        break;
      case 1:
        while (true) {
          radio.read(&data, sizeof(data));
          // Serial.print(F("moving nose and drawing rectangle"));
          // LED
          ledStrip(1);
          // Music
          //
          // Servo
          //
          if (data.stateNumber != 1) {
            break;
          }
        }

        // Music
        Serial.println(F("Playing track 001"));
        musicPlayer.startPlayingFile("/track001.mp3");

        break;
      case 2:
        while (true) {
          radio.read(&data, sizeof(data));
          // LED
          ledStrip(3);
          // Music
          // Servo
          pos3 = 95;
          dance(0);
          //
          if (data.stateNumber != 0) {
            break;
          }
        }
        Serial.println(F("Playing track 002"));
        musicPlayer.startPlayingFile("/track002.mp3");
        break;
      case 3:
        while (true) {
          radio.read(&data, sizeof(data));
          // LED
          ledStrip(3);
          // Servo
          pos3 = 95;
          dance(0);
          //
          if (data.stateNumber != 0) {
            break;
          }
        }        break;
      case 4:
        break;

      case 5:
        break;

      default:
        Serial.println(F("Invalid option"));
    }
  }
}  // end of loop()

/*
  m1->19
  m2->21
  m3->20
  m4->16
  m5->18
  m6->17

// code : https://github.com/michaelshiloh/resourcesForClasses/tree/master/src/arduinoSketches/nRF24L01/rf24PerformingRobotsTemplate_2023

const int NRF_CE_PIN = A11,
          NRF_CSN_PIN = A15;

// In summary,
// nRF 24L01 pin    Uno Mega   name
//          1                     GND
//          2                     3.3V
//          3       9   A11       CE
//          4       10  A15       CSN
//          5       13  SCLK
//          6       11  MOSI/COPI
//          7       12  MISO/CIPO

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(NRF_CE_PIN, NRF_CSN_PIN); // CE, CSN

// #include <printf.h>  // for debugging

// See note in rf24Handshaking about address selection
//

// Channel and address allocation:
// Fatema, Jannah: Channel 30, addr = 0x76
// Andres, Ryan: Channel 40, addr = 0x73
// Nouf, Shaikha:  Channel 50, addr = 0x7C
// Aadhar, Shanaia: Channel 60, addr = 0xC6
// Akhat, Yunho:  Channel 70, addr = 0xC3
// Aakif, Marta: Channel 80, addr = 0xCC
// Yerk, Hamad: Channel 90, addr = 0x33
const byte addr = 0x76;             // change as per the above assignment
const int RF24_CHANNEL_NUMBER = 30; // change as per the above assignment

// Do not make changes here
const byte xmtrAddress[] = {addr, addr, 0xC7, 0xE6, 0xCC};
const byte rcvrAddress[] = {addr, addr, 0xC7, 0xE6, 0x66};

const int RF24_POWER_LEVEL = RF24_PA_LOW;

// global variables
uint8_t pipeNum;
unsigned int totalTransmitFailures = 0;

struct DataStruct
{
  uint8_t stateNumber;
};
DataStruct data;

/////////////////////////////////////////////////////
////////////////LED CODE BEGIN///////////////////////
/////////////////////////////////////////////////////

#include <Adafruit_NeoPixel.h>

#define PIN_MOUTH 17       // Neopixel pin for the mouth
#define NUMPIXELS_MOUTH 64 // Number of pixels in the mouth matrix

#define PIN_OTHER 18        // Neopixel pin for the other LED strip
#define NUMPIXELS_OTHER 180 // Number of pixels in the other LED strip

Adafruit_NeoPixel pixelsMouth = Adafruit_NeoPixel(NUMPIXELS_MOUTH, PIN_MOUTH, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixelsOther = Adafruit_NeoPixel(NUMPIXELS_OTHER, PIN_OTHER, NEO_GRB + NEO_KHZ800);

int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 10;
int currentLED = 0;

int mouthClosed[] = {18, 19, 20, 21, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 42, 43, 44, 45};
int mouthOpen[] = {3, 4, 10, 11, 12, 13, 17, 18, 21, 22, 24, 25, 30, 31, 32, 33, 38, 39, 41, 42, 45, 46, 50, 51, 52, 53, 59, 60};

int currentState = 0; // 0 for closed mouth, 1 for open mouth
unsigned long previousMouthMillis = 0;
const unsigned long CLOSED_DELAY = 500; // Delay for closed mouth (in milliseconds)
const unsigned long OPEN_DELAY = 500;   // Delay for open mouth (in milliseconds)

/////////////////////////////////////////////////////
////////////////LED CODE END/////////////////////////
/////////////////////////////////////////////////////

void setupRF24Common()
{

  // RF24 setup
  if (!radio.begin())
  {
    Serial.println(F("radio  initialization failed"));
    while (1)
      ;
  }
  else
  {
    Serial.println(F("radio successfully initialized"));
  }

  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(RF24_CHANNEL_NUMBER);
  radio.setPALevel(RF24_POWER_LEVEL);
}

// Receiver Code

// Additional libraries for music maker shield
#include <Adafruit_VS1053.h>
#include <SD.h>

// Servo library
#include <Servo.h>

// Additional libraries for graphics on the Neo Pixel Matrix
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif

// Additional pin usage for receiver

// Adafruit music maker shield
#define SHIELD_RESET -1 // VS1053 reset pin (unused!)
#define SHIELD_CS 7     // VS1053 chip select pin (output)
#define SHIELD_DCS 6    // VS1053 Data/command select pin (output)
#define CARDCS 4        // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3 // VS1053 Data request, ideally an Interrupt pin
Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

// Servo motors
const int NOSE_SERVO_PIN = 19; // TODO why doesn't pin 21 work?
// const int ANTENNA_SERVO_PIN = 10;
// const int TAIL_SERVO_PIN = 11;
// const int GRABBER_SERVO_PIN = 12;

// Neopixel
const int NEOPIXELPIN = 18;
const int NUMPIXELS = 64;
// #define NEOPIXELPIN 18
// #define NUMPIXELS 64  // change to fit
// Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, NEOPIXELPIN,
                                               NEO_MATRIX_TOP + NEO_MATRIX_RIGHT +
                                                   NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
                                               NEO_GRB + NEO_KHZ800);

Servo nose; // change names to describe what's moving
Servo antenna;
Servo tail;
Servo grabber;
Servo disk;

// change as per your robot
const int NOSE_WRINKLE = 45;
const int NOSE_TWEAK = 90;
const int TAIL_ANGRY = 0;
const int TAIL_HAPPY = 180;
const int GRABBER_RELAX = 0;
const int GRABBER_GRAB = 180;

void setup()
{
  Serial.begin(9600);
  // printf_begin();

  // Set up all the attached hardware
  setupMusicMakerShield();
  setupServoMotors();
  setupNeoPixels();

  setupRF24();

  // Brief flash to show we're done with setup()
  //  flashNeoPixels();
}
void flashNeoPixels()
{

  // Using the Matrix library
  matrix.fillScreen(matrix.Color(0, 255, 0));
  matrix.show();
  delay(500);
  matrix.fillScreen(0);
  matrix.show();

  //  // all on
  //  for (int i = 0; i < NUMPIXELS; i++) {  // For each pixel...
  //    pixels.setPixelColor(i, pixels.Color(0, 100, 0));
  //  }
  //  pixels.show();
  //  delay(500);
  //
  //  // all off
  //  pixels.clear();
  //  pixels.show();
}

void setupRF24()
{
  setupRF24Common();

  // Set us as a receiver
  radio.openWritingPipe(rcvrAddress);
  radio.openReadingPipe(1, xmtrAddress);

  // radio.printPrettyDetails();
  Serial.println(F("I am a receiver"));
}

void setupMusicMakerShield()
{
  if (!musicPlayer.begin())
  { // initialise the music player
    Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
    while (1)
      ;
  }
  Serial.println(F("VS1053 found"));

  if (!SD.begin(CARDCS))
  {
    Serial.println(F("SD card failed or not present"));
    while (1)
      ; // don't do anything more
  }

  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(20, 20);

  // Timer interrupts are not suggested, better to use DREQ interrupt!
  // musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT); // timer int

  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT); // DREQ int
}

void setupServoMotors()
{
  nose.attach(NOSE_SERVO_PIN);
  nose.write(90);
  //  antenna.attach(ANTENNA_SERVO_PIN);
  //  tail.attach(TAIL_SERVO_PIN);
  //  grabber.attach(GRABBER_SERVO_PIN);
  //
  //  tail.write(TAIL_HAPPY);
}

void setupNeoPixels()
{
  pixelsMouth.begin();
  pixelsMouth.setBrightness(50); // Set the brightness (0-255)

  pixelsOther.begin();
}

void ledStrip()
{
  unsigned long currentMillis = millis();

  // Handling the other LED strip
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    pixelsOther.clear();
    pixelsOther.setPixelColor(currentLED, pixelsOther.Color(0, 150, 0));
    pixelsOther.show();

    currentLED = (currentLED + 1) % NUMPIXELS_OTHER;
  }
}

// Function to display mouth based on provided positions for a specific Neopixel strip
void displayMouth(Adafruit_NeoPixel &strip, int mouth[], int size, uint32_t color)
{
  strip.clear();
  for (int i = 0; i < size; i++)
  {
    strip.setPixelColor(mouth[i], color);
  }
  strip.show();
}

void mouthopenclose()
{
  unsigned long currentMouthMillis = millis();
  if (currentState == 0)
  {                                                                                                 // Closed mouth
    displayMouth(pixelsMouth, mouthClosed, sizeof(mouthClosed) / sizeof(mouthClosed[0]), 0xFF0000); // Change color as needed
    if (currentMouthMillis - previousMouthMillis >= CLOSED_DELAY)
    {
      previousMouthMillis = currentMouthMillis;
      currentState = 1; // Change state to open mouth
    }
  }
  else
  {                                                                                           // Open mouth
    displayMouth(pixelsMouth, mouthOpen, sizeof(mouthOpen) / sizeof(mouthOpen[0]), 0xFF0000); // Change color as needed
    if (currentMouthMillis - previousMouthMillis >= OPEN_DELAY)
    {
      previousMouthMillis = currentMouthMillis;
      currentState = 0; // Change state to closed mouth
    }
  }
}

void loop()
{
  // If there is data, read it,
  // and do the needfull
  // Become a receiver
  radio.startListening();

  if (radio.available(&pipeNum))
  {
    radio.read(&data, sizeof(data));
    Serial.print(F("message received Data = "));
    Serial.print(data.stateNumber);
    Serial.println();

    switch (data.stateNumber)
    {
    case 0:
      pixelsOther.clear();
      tail.write(TAIL_ANGRY);
      // play track 0
      // display something on LEDs
      break;
    case 1:
      //        pixelsOther.clear();
      Serial.print(F("moving nose and drawing rectangle"));
      //        nose.write(180);

      matrix.drawRect(2, 2, 5, 5, matrix.Color(200, 90, 30));
      matrix.show();

      Serial.println(F("Playing track 002"));
      musicPlayer.startPlayingFile("/track002.mp3");

      break;
    case 2:
      mouthopenclose();
      //        nose.write(30);
      //
      //        matrix.drawRect(2, 2, 5, 5, matrix.Color(0, 200, 30));
      //        matrix.show();

      Serial.println(F("Playing track 001"));
      musicPlayer.startPlayingFile("/track001.mp3");
      break;
    case 3:
      pixelsOther.clear();

      break;
    case 4:
      pixelsOther.clear();

      break;

    default:
      pixelsOther.clear();
      Serial.println(F("Invalid option"));
    }
  }
} // end of loop()
  // end of receiver code

/*
   code: https://github.com/michaelshiloh/resourcesForClasses/tree/master/src/arduinoSketches/nRF24L01/rf24PerformingRobotsTemplate_2023
   Using the nRF24L01 radio module to communicate
   between two Arduinos with much increased reliability following
   various tutorials, conversations, and studying the nRF24L01 datasheet
   and the library reference.

   Transmitter is
   https://github.com/michaelshiloh/resourcesForClasses/tree/master/kicad/Arduino_Shield_RC_Controller

  Receiver is
  https://github.com/instituteforcriticalrobotics/instituteforcriticalrobotics.github.io/tree/main/kicad/nRF_Mega

   This file contains code for both transmitter and receiver.
   Transmitter at the top, receiver at the bottom.
   One of them is commented out.

   These sketches require the RF24 library by TMRh20
   Documentation here: https://nrf24.github.io/RF24/index.html

   change log

   11 Oct 2023 - ms - initial entry based on
                  rf24PerformingRobotsTemplate
   26 Oct 2023 - ms - revised for new board: nRF_Servo_Mega rev 2
   28 Oct 2023 - ms - add demo of NeoMatrix, servo, and Music Maker Shield
*/

// Common code
//

// Common pin usage
// Note there are additional pins unique to transmitter or receiver
//

// nRF24L01 uses SPI which is fixed
// on pins 11, 12, and 13 on the Uno
// and on pins 50, 51, and 52 on the Mega

// It also requires two other signals
// (CE = Chip Enable, CSN = Chip Select Not)
// Which can be any pins:

// For the transmitter
// const int NRF_CE_PIN = A4, NRF_CSN_PIN = A5;

// for the receiver