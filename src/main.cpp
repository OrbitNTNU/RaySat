#include <Arduino.h>
#include <Wire.h>
// local libraries
#include "sd/datastorage.h"
#include "sensors/sensors.h"
#include "radio/radio.h"
#include "radio/radioError.h"
// #include "sensors/scanner.h"

Radio radio;

unsigned long startTime = millis();
unsigned long previousMillis = millis();

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Serial.println("Initializing...");
  // sdSystemInit();
  // Serial.println("----------------------");
  // initSensors();


  try
  {
    radio.setup();
  } catch (RadioError err) {
    // Prints error message
    Serial.println("Error was caused by radio: ");
    Serial.println(err.what());
  }
  Serial.println("Setup complete");
}

void loop()
{
  // put your main code here, to run repeatedly:
  SensorData data;
  readSensors(data);
  writeSensorData(data);
  printSensorData(data);
  delay(1000);

  Serial.println("Hei hei");

  unsigned long currentMillis = millis();
  unsigned long interval = 5;
  // if ((currentMillis - previousMillis) >= interval)
  // {
  //   previousMillis = currentMillis;
  //   radio.read();
  // }

  try {
    radio.loop();
  } catch(RadioError err) {
    Serial.println("Error was caused by radio: ");
    Serial.println(err.what());
  }
}

// unsigned long currentMillis = millis();
// if ((currentMillis - Radio::previousMillis) >= Radio::interval)
// {
//     Radio::previousMillis = currentMillis;
//     Radio::read();
// }
