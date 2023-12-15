#include <Adafruit_NeoPixel.h>

#define PIN_MOUTH      6 // Neopixel pin for the mouth
#define NUMPIXELS_MOUTH 64 // Number of pixels in the mouth matrix

#define PIN_OTHER      3 // Neopixel pin for the other LED strip
#define NUMPIXELS_OTHER 180 // Number of pixels in the other LED strip

Adafruit_NeoPixel pixelsMouth = Adafruit_NeoPixel(NUMPIXELS_MOUTH, PIN_MOUTH, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixelsOther = Adafruit_NeoPixel(NUMPIXELS_OTHER, PIN_OTHER, NEO_GRB + NEO_KHZ800);

int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 10;
int currentLED = 0;

int mouthClosed[] = { 18,19,20, 21, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 42, 43, 44, 45};
int mouthOpen[] = {3, 4, 10, 11, 12, 13, 17, 18, 21, 22, 24, 25, 30, 31, 32, 33, 38, 39, 41, 42, 45, 46, 50, 51, 52, 53, 59, 60};

int currentState = 0; // 0 for closed mouth, 1 for open mouth
unsigned long previousMouthMillis = 0;
const unsigned long CLOSED_DELAY = 5000; // Delay for closed mouth (in milliseconds)
const unsigned long OPEN_DELAY = 5000; // Delay for open mouth (in milliseconds)

void setup() {
  pixelsMouth.begin();
  pixelsMouth.setBrightness(50); // Set the brightness (0-255)
  
  pixelsOther.begin();
}

void loop() {
  unsigned long currentMillis = millis();

  // Handling the other LED strip
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    pixelsOther.clear();
    pixelsOther.setPixelColor(currentLED, pixelsOther.Color(0, 150, 0));
    pixelsOther.show();

    currentLED = (currentLED + 1) % NUMPIXELS_OTHER;
  }

  // Handling the mouth LED strip
  unsigned long currentMouthMillis = millis();
  if (currentState == 0) { // Closed mouth
    displayMouth(pixelsMouth, mouthClosed, sizeof(mouthClosed) / sizeof(mouthClosed[0]), 0xFF0000); // Change color as needed
    if (currentMouthMillis - previousMouthMillis >= CLOSED_DELAY) {
      previousMouthMillis = currentMouthMillis;
      currentState = 1; // Change state to open mouth
    }
  } else { // Open mouth
    displayMouth(pixelsMouth, mouthOpen, sizeof(mouthOpen) / sizeof(mouthOpen[0]), 0xFF0000); // Change color as needed
    if (currentMouthMillis - previousMouthMillis >= OPEN_DELAY) {
      previousMouthMillis = currentMouthMillis;
      currentState = 0; // Change state to closed mouth
    }
  }
}

// Function to display mouth based on provided positions for a specific Neopixel strip
void displayMouth(Adafruit_NeoPixel &strip, int mouth[], int size, uint32_t color) {
  strip.clear();
  for (int i = 0; i < size; i++) {
    strip.setPixelColor(mouth[i], color);
  }
  strip.show();
}
