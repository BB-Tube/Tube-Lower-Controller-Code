#include <Adafruit_NeoPixel.h>
#include <stdint.h> // Explicitly include the header for uint32_t

#define PIN            6  // Change this to the pin you've connected to the NeoPixel data input
#define NUMPIXELS      4  // Number of NeoPixels you are controlling

void setColorRange(int startPixel, int endPixel, uint32_t color);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();           // Initialize the strip
  strip.show();            // Initialize all pixels to 'off'
}

void loop() {
  setColorRange(0, 3, strip.Color(32, 32, 32)); // Set first 6 pixels to red
  strip.show();            // Update the strip with new color settings
  delay(1000);             // Wait for a second
  
  setColorRange(0, 3, strip.Color(0, 0, 0)); // Set first 6 pixels to red
  strip.show();
  delay(1000);
}

// Function to set a range of NeoPixels to a specific color
void setColorRange(int startPixel, int endPixel, uint32_t color) {
  for (int i = startPixel; i <= endPixel; i++) {
    strip.setPixelColor(i, color);
  }
}