/*********************************************************
  This is a library for the MPR121 12-channel Capacitive touch sensor

  Designed specifically to work with the MPR121 Breakout in the Adafruit shop
  ----> https://www.adafruit.com/products/

  These sensors use I2C communicate, at least 2 pins are required
  to interface

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution

 Last edit: March 3rd 2018
 by Ahmed Islaih & Zach
 
 kept all the library the same but incresed the sensetivity by
 dropping the value of the threashhold
 
 created if-statments for each copacitive touch that when touched
 it plays a tone or a melody
**********************************************************/

#include <Wire.h>
#include "Adafruit_MPR121.h"

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

void setup() {
  Serial.begin(9600);

  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }

  Serial.println("Adafruit MPR121 Capacitive Touch sensor test");

  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");

  pinMode(8, OUTPUT);
}

void loop() {
  // Get the currently touched pads
  currtouched = cap.touched();

  //  for (uint8_t i=0; i<12; i++) {
  //    // it if *is* touched and *wasnt* touched before, alert!
  //    if (cap.touched() & (1 << 4)) {
  //      tone(8,329.63, 300);
  //      Serial.print(i); Serial.println(" touched");
  //    }
  //    // if it *was* touched and now *isnt*, alert!
  //    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
  //      Serial.print(i); Serial.println(" released");
  //    }
  // }
  //setThreshholds(10,5);

  //baselineData(10);

  for (uint8_t i = 0; i < 12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched");
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" released");
    }
  }

  if (cap.touched() & (1 << 4)) {
    tone(5, 329.63, 300);
    delay(300);
    tone(5, 100, 300);
    delay(400);
    tone(5, 225, 300);
    delay(300);
    tone(5, 329.63, 300);
  }

  if (cap.touched() & (1 << 3)) {
    tone(5, 70, 300);
    delay(500);
    tone(5, 220, 300);
  }

  if (cap.touched() & (1 << 2)) {
    tone(5, 50, 300);
    delay(150);
    tone(5, 120, 300);
  }

  if (cap.touched() & (1 << 1)) {
    tone(5, 65, 150);
  }

  if (cap.touched() & (1 << 5)) {
    tone(5, 250, 100);
  }

  if (cap.touched() & (1 << 10)) {
    tone(5, 200, 100);
  }

  if (cap.touched() & (1 << 7)) {
    tone(5, 130, 300);
    delay(200);
    tone(5, 80, 300);
    delay(100);
    tone(5, 170, 300);
    delay(100);
  }

  if (cap.touched() & (1 << 6)) {
    tone(5, 100, 300);
    delay(100);
    tone(5, 200, 300);
    delay(100);
    tone(5, 300, 300);
    delay(100);
  }

  if (cap.touched() & (1 << 8)) {
    tone(5, 80, 300);
    delay(100);
    tone(5, 80, 300);
    delay(200);
    tone(5, 144, 300);
    delay(100);
    tone(5, 144, 300);
    delay(200);
    tone(5, 180, 300);
    delay(100);
    tone(5, 180, 300);
    delay(100);
  }

  if (cap.touched() & (1 << 9)) {
    tone(5, 80, 300);
    delay(150);
    tone(5, 100, 300);
    delay(150);
    tone(5, 120, 300);
    delay(150);
    tone(5, 140, 300);
    delay(150);
    tone(5, 160, 300);
    delay(150);
    tone(5, 180, 300);
    delay(150);
    tone(5, 200, 300);
    delay(150);
  }

  // reset our state
  lasttouched = currtouched;

  // comment out this line for detailed data from the sensor!
  return;

  // debugging info, what
  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap.touched(), HEX);
  Serial.print("Filt: ");
  for (uint8_t i = 0; i < 12; i++) {
    Serial.print(cap.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  Serial.print("Base: ");
  for (uint8_t i = 0; i < 12; i++) {
    Serial.print(cap.baselineData(i)); Serial.print("\t");
  }
  Serial.println();

  // put a delay so it isn't overwhelming
  delay(100);
}
