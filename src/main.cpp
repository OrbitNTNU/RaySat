#include <Arduino.h>
#include <Wire.h>
// local libraries
#include "sd/datastorage.h"
#include "sensors/sensors.h"

// #include "sensors/scanner.h"

Radio radio;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Serial.println("Initializing...");
  sdSystemInit();
  // Serial.println("----------------------");
  initSensors();
  Serial.println("Setup complete");
}

void loop() {
  // put your main code here, to run repeatedly:
  readSensors(false);
  delay(1000);
  radio.loop();
}