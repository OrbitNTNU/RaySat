#include <Arduino.h>
#include <Wire.h>
// local libraries
#include "sd/datastorage.h"
#include "sensors/sensors.h"
#include "reactionWheel/rwController.h"
#include "bms/bms.h"

// #include "sensors/scanner.h"
RWController rwController;

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Initializing...");
  bmsInit();
  sdSystemInit();
  // Serial.println("----------------------");
  initSensors();
  Serial.println("Setup complete");
}

void loop() {
  // put your main code here, to run repeatedly:
  SensorData data;
  readSensors(data);
  writeSensorData(data);
  rwController.control(data);
  printSensorData(data);
  delay(1000);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}