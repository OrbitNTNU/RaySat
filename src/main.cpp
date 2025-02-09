#include <Arduino.h>
#include <Wire.h>
// local libraries
#include "sensors/pressure.h"
#include "sd/datastorage.h"
#include "radio/radio.h"

Radio radio;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Initializing...");
  // // Wire.begin();
  // int result = myFunction(2, 3);
  // setup_pressure();
  // setup_sdCard();
  
  radio.setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  // double pressure = read_pressure();
  // Serial.print("Pressure: ");
  // Serial.println(pressure);
  delay(1000);
  radio.loop();
}