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

int pos = 0;  // variable to store the servo position
const int pos11 = 0;
const int pos12 = 20;
int pos2 = 45;
int pos3 = 100;

unsigned long interval = 40;       // the time we need to wait
unsigned long previousMillis = 0;  // millis() returns an unsigned long.
unsigned long previousMillis2 = 0;

bool flag = false;

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

const int NEOPIXELPIN = m6;  // Neopixel pin for the mouth
#define NUMPIXELS_MOUTH 64   // Number of pixels in the mouth matrix

const int NUMPIXELS = m5;    // Neopixel pin for the other LED strip
#define NUMPIXELS_OTHER 180  // Number of pixels in the other LED strip

Adafruit_NeoPixel pixelsMouth = Adafruit_NeoPixel(NUMPIXELS_MOUTH, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixelsOther = Adafruit_NeoPixel(NUMPIXELS_OTHER, NUMPIXELS, NEO_GRB + NEO_KHZ800);

int ledState = LOW;
// unsigned long previousMillis = 0;
const long interval2 = 10;
int currentLED = 0;

int mouthClosed[] = { 18, 19, 20, 21, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 42, 43, 44, 45 };
int mouthOpen[] = { 3, 4, 10, 11, 12, 13, 17, 18, 21, 22, 24, 25, 30, 31, 32, 33, 38, 39, 41, 42, 45, 46, 50, 51, 52, 53, 59, 60 };
//int mouthClosed[] = { 18, 19, 20, 21, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 42, 43, 44, 45 };


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
// ================== Setup BEGIN =================
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
// =================== Setup END ==================
// ================================================

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
  myservo1.attach(m1);
  myservo2.attach(m2);
  myservo3.attach(m3);
  myservo1.write(10);
  myservo2.write(55);
  myservo3.write(110);
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

void ledStrip() {
  unsigned long currentMillis = millis();
  // Handling the other LED strip
  if (currentMillis - previousMillis >= interval2) {
    previousMillis = currentMillis;

    pixelsOther.clear();
    pixelsOther.setPixelColor(currentLED, pixelsOther.Color(random(255), random(255), random(255)));
    pixelsOther.show();

    currentLED = (currentLED + 1) % NUMPIXELS_OTHER;
  }
}

void dance() {
  unsigned long currentMillis = millis();
  Serial.print("servo: ");
  // Serial.print("pos1 ");
  // Serial.print(pos);

  // Serial.print("    pos2 ");
  // Serial.print(pos2);

  // Serial.print("    pos3 ");
  // Serial.println(pos3);


  if ((unsigned long)(currentMillis - previousMillis2) >= interval) {
    previousMillis2 = currentMillis;
    myservo1.write(pos);
    myservo2.write(pos2);
    myservo3.write(pos3);
    // check direction and add for one/ subtract for one
    if (flag) {
      Serial.print("flag: ");
      Serial.print("pos1 ");
      Serial.print(pos);

      Serial.print("    pos2 ");
      Serial.print(pos2);

      Serial.print("    pos3 ");
      Serial.println(pos3);

      pos -= 1;
      pos2 -= 1;
      pos3 -= 1;
    } else {
      Serial.print("!flag: ");
      Serial.print("pos1 ");
      Serial.print(pos);

      Serial.print("    pos2 ");
      Serial.print(pos2);

      Serial.print("    pos3 ");
      Serial.println(pos3);
      pos += 1;
      pos2 += 1;
      pos3 += 1;
    }
    // check location and change flag if direction will change
    if (pos >= pos12) {
      flag = true;
    }
    if (pos <= pos11) {
      flag = false;
    }
  }
}

void talkingMouth() {
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


// ================================================
// ============== LOOP FUNCTIONS END ==============
// ================================================

void loop() {
  // If there is data, read it,
  // and do the needfull
  // Become a receiver
  radio.startListening();
  pixelsOther.clear();

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
          if (data.stateNumber != 0) {
            break;
          }
        }
        break;

      //SCRIPT
      case 1:
        Serial.println(F("Playing track 001"));
        musicPlayer.startPlayingFile("/track1.mp3");

        while (musicPlayer.playingMusic) {
          radio.read(&data, sizeof(data));
          if (data.stateNumber == 18) {
            break;
          }
          dance();
          talkingMouth();
          //          ledStrip();
        }
        break;


      case 2:
        Serial.println(F("Playing track 002"));
        musicPlayer.startPlayingFile("/track2.mp3");

        while (musicPlayer.playingMusic) {
          radio.read(&data, sizeof(data));
          if (data.stateNumber == 18) {
            break;
          }
          dance();
          talkingMouth();
        }
        break;


      case 3:
        Serial.println(F("Playing track 003"));
        musicPlayer.startPlayingFile("/track3.mp3");

        while (musicPlayer.playingMusic) {
          radio.read(&data, sizeof(data));
          if (data.stateNumber == 18) {
            break;
          }
          dance();
          talkingMouth();
        }
        break;



      case 4:
        Serial.println(F("Playing track 004"));
        musicPlayer.startPlayingFile("/track4.mp3");

        while (musicPlayer.playingMusic) {
          radio.read(&data, sizeof(data));
          if (data.stateNumber == 18) {
            break;
          }
          dance();
          talkingMouth();
        }

        break;


      case 5:
        Serial.println(F("Playing track 005"));
        musicPlayer.startPlayingFile("/track5.mp3");

        while (musicPlayer.playingMusic) {
          radio.read(&data, sizeof(data));
          if (data.stateNumber == 18) {
            break;
          }
          dance();
          talkingMouth();
          //          ledStrip();
        }
        break;


      case 6:
        Serial.println(F("Playing track 006"));
        musicPlayer.startPlayingFile("/track6.mp3");

        while (musicPlayer.playingMusic) {
          // dancing
          radio.read(&data, sizeof(data));
          if (data.stateNumber == 18) {
            break;
          }
          dance();
          talkingMouth();
          //          ledStrip();
        }
        break;



      case 7:
        Serial.println(F("Playing track 007"));
        musicPlayer.startPlayingFile("/track7.mp3");

        while (musicPlayer.playingMusic) {
          radio.read(&data, sizeof(data));
          if (data.stateNumber == 18) {
            break;
          }
          dance();
          talkingMouth();
          //          ledStrip();
        }
        break;


      case 8:
        Serial.println(F("Playing track 008"));
        musicPlayer.startPlayingFile("/track8.mp3");

        while (musicPlayer.playingMusic) {
          radio.read(&data, sizeof(data));
          if (data.stateNumber == 18) {
            break;
          }
          dance();
          talkingMouth();
          //          ledStrip();
        }
        break;



      case 9:
        Serial.println(F("Playing track 009"));
        musicPlayer.startPlayingFile("/track9.mp3");

        while (musicPlayer.playingMusic) {
          radio.read(&data, sizeof(data));
          if (data.stateNumber == 18) {
            break;
          }
          dance();
          talkingMouth();
          //          ledStrip();
        }
        break;


      case 10:
        Serial.println(F("Playing track 10"));
        musicPlayer.startPlayingFile("/track10.mp3");

        while (musicPlayer.playingMusic) {
          radio.read(&data, sizeof(data));
          if (data.stateNumber == 18) {
            break;
          }
          dance();
          talkingMouth();
          //          ledStrip();
        }
        break;

      case 11:
        Serial.println(F("Playing monologue"));
        musicPlayer.startPlayingFile("/mono.mp3");
        // if (!SD.exists("monologue.mp3")) {
        //   Serial.println("File does not exist");
        // } else {
        //   if (!musicPlayer.startPlayingFile("/mono.mp3")) {
        //     Serial.println("Failed to play file");
        //   }
        // }

        while (musicPlayer.playingMusic) {
          radio.read(&data, sizeof(data));
          if (data.stateNumber == 18) {
            break;
          }
          dance();
          talkingMouth();
          ledStrip();
        }
        break;


      case 12:
        Serial.println(F("Playing alejandro"));
        // printDirectory(SD.open("/"), 0);
        musicPlayer.startPlayingFile("/alejan.mp3");
        // if (!SD.exists("/alejan.mp3")) {
        //   Serial.println("File does not exist");
        // } else {
        //   if (!musicPlayer.startPlayingFile("alejan.mp3")) {
        //     Serial.println("Failed to play file");
        //   }
        // }


        while (musicPlayer.playingMusic) {
          radio.read(&data, sizeof(data));
          if (data.stateNumber == 18) {
            break;
          }
          dance();
          talkingMouth();
          //          ledStrip();
        }
        break;


      case 13:
        Serial.println(F("Playing track agreed"));
        musicPlayer.startPlayingFile("agreed.mp3");

        while (musicPlayer.playingMusic) {
          radio.read(&data, sizeof(data));
          if (data.stateNumber == 18) {
            break;
          }
          dance();
          talkingMouth();
          //          ledStrip();
        }
        break;


      case 14:
        Serial.println(F("Playing track GASP"));
        musicPlayer.startPlayingFile("/GASP.mp3");

        while (musicPlayer.playingMusic) {
          radio.read(&data, sizeof(data));
          if (data.stateNumber == 18) {
            break;
          }
          dance();
          talkingMouth();
          ledStrip();
        }
        break;


      case 15:
        Serial.println(F("Playing track wohoo"));
        musicPlayer.startPlayingFile("/wohoo.mp3");

        while (musicPlayer.playingMusic) {
          radio.read(&data, sizeof(data));
          if (data.stateNumber == 18) {
            break;
          }
          dance();
          talkingMouth();
          ledStrip();
        }
        break;


      case 16:
        Serial.println(F("Playing track shikshak"));
        musicPlayer.startPlayingFile("shikshak.mp3");
        while (musicPlayer.playingMusic) {
          radio.read(&data, sizeof(data));
          if (data.stateNumber == 18) {
            break;
          }
          dance();
          talkingMouth();
          ledStrip();
        }
        break;


      case 17:
        Serial.println(F("Playing track seto_ana"));
        musicPlayer.startPlayingFile("seto_ana.mp3");

        while (musicPlayer.playingMusic) {
          radio.read(&data, sizeof(data));
          if (data.stateNumber == 18) {
            break;
          }
          dance();
          talkingMouth();
          ledStrip();
        }
        break;
      case 18:
        Serial.println("stop");
        if (musicPlayer.playingMusic) {
          musicPlayer.stopPlaying();
        }
        // musicPlayer.stopPlaying();
        myservo1.write(10);
        myservo2.write(55);
        myservo3.write(110);
        break;

      default:
        Serial.println(F("Invalid option"));
    }
    displayMouth(pixelsMouth, mouthClosed, sizeof(mouthClosed) / sizeof(mouthClosed[0]), 0xFF0000);  // Change color as needed
  }
}