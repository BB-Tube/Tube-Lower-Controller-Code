#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <cmath>
#include <Adafruit_TCS34725.h>
#include "ballIndex.h"

// for a common anode LED, connect the common pin to +5V
// for common cathode, connect the common to ground

// set to false if using a common cathode LED
#define commonAnode true

// our RGB -> eye-recognized gamma color
byte gammatable[256];

void sortball();
int what_color_ball();
static char get_ball_color();
int difference_from(int color_state, int r, int g, int b);
int get_ball_value(int color_state, char diode);

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_1X);
//Sorter airsortone;

void setup() {

  Serial.begin(9600);
  Serial.println("Color View Test!");

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }

  // thanks PhilB for this gamma table!
  // it helps convert RGB colors to what humans see
  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;

    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;
    }
    //Serial.println(gammatable[i]);
  }
}

// The commented out code in loop is example of getRawData with clear value.
// Processing example colorview.pde can work with this kind of data too, but It requires manual conversion to 
// [0-255] RGB value. You can still uncomments parts of colorview.pde and play with clear value.

int iterator = 0;
const int upTo = 1; 

void loop() {
  sortball();
}
//sort ball que

void sortball(){
  if (Serial.available() > 0) {
    char data = Serial.read(); // Read the incoming data from Raspberry Pi
    // Serial.printf("Timer 1: %d\n", millis());
    int ball_num = get_ball_color();
    switch (ball_num)
    {
    case Black_ball:
      Serial.println('b');
      break;
    
    case White_ball:
      Serial.println('w');
      break;

    default:
      // Boops
      break;
    }
    // Serial.printf("Timer 1: %d\n", millis());
  }
} 

static char get_ball_color(){
  //get ball color from tcs (color sensor)
  float red, green, blue;
  tcs.setInterrupt(false);  // turn on LED
  // Serial.printf("Timer 2: %d\n", millis());
  tcs.getRGB(&red, &green, &blue);
  // Serial.printf("Timer 2: %d\n", millis());

  
  int diff_blank = 10000000;
  int diff_black = difference_from(Black_ball, int(red), int(green), int(blue));
  int diff_white = difference_from(White_ball, int(red), int(green), int(blue));


  int diffs[] = {diff_blank, diff_black, diff_white};
  // int diffs[] = {diff_black, diff_white};
  int closest = 0;
  for(int i = 1; i < num_color_states; i++){
    if (diffs[i] < diffs[closest])
      closest = i;
  }
  return closest;
}

//returns difference of color from 
int difference_from(int color_state, int r, int g, int b){
  int difference = 0;
  difference += abs(get_ball_value(color_state, 'r') - r);
  difference += abs(get_ball_value(color_state, 'g') - g);
  difference += abs(get_ball_value(color_state, 'b') - b);
  return difference;
}

//get diode reading for color_ball
int get_ball_value(int color_state, char diode){
  //converts diode char to color_state index
  int color_wanted = -1;
  switch(diode){
    case 'r':
      color_wanted = 0;
      break;
    case 'g':
      color_wanted = 1;
      break;
    case 'b':
      color_wanted = 2;
      break;
    default:
      Serial.println("get_ball_value asked for wrong diode");
    }

  //gets correct color reference behind color_state 
  switch(color_state){
    case Blank_ball:
      return BLANK[color_wanted];
      break;
    case Black_ball:
      return BLACK[color_wanted];
      break;
    case White_ball:
      return WHITE[color_wanted];
      break;
    default:
      Serial.println("non exsistent ball asked for");
    }
  return -1;
}