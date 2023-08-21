#include <Arduino.h>

// for a common anode LED, connect the common pin to +5V
// for common cathode, connect the common to ground

// Define the pin number for analog input
const int analogInputPin = A10; // Use A0 for GPIO 10 on most Arduino boards

bool printHallState(int pin, int threshhold);

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  bool thingie = printHallState(analogInputPin, 500);
  delay(500);
}

bool printHallState(int pin, int threshhold){
  int analogValue = analogRead(pin);
  // Serial.print("Analog value on GPIO 10: ");
  Serial.println(analogValue);
  if(analogValue < threshhold){
    Serial.println('0');
    return false;
  }else{
    Serial.println('1');
    return true;
  }
}