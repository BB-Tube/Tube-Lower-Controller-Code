#include <Adafruit_NeoPixel.h>

#define PIN            6  // Change this to the pin you've connected to the NeoPixel data input
#define NUMPIXELS      1  // Number of NeoPixels you are controlling

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();           // Initialize the strip
  strip.show();            // Initialize all pixels to 'off'
}

void loop() {
  strip.setPixelColor(0, strip.Color(255,0,0)); // Set the first pixel to red
  strip.show();            // Update the strip with new color settings
  delay(1000);             // Wait for a second
  
  strip.setPixelColor(0, strip.Color(0,0,0)); // Turn off the pixel
  strip.show();
  delay(1000);
}
