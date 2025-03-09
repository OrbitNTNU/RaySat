#include <Arduino.h>
#include <Wire.h>
// local libraries
#include "sd/datastorage.h"
#include "sensors/sensors.h"
#include "radio/radio.h"
// #include "sensors/scanner.h"

// ------------------- Class Initilizations -------------------  
Radio radio;
SensorData data;

// ------------------- Clock Variables -------------------
unsigned long startTime = millis();
unsigned long previousMillis = startTime;
const long interval = 5000;

void setup()
{
  Serial.begin(9600);
  Serial.println("Initializing...");
  // sdSystemInit();
  Serial.println("----------------------");
  // initSensors();

  // ------------------- Radio Setup -------------------
  Serial.println(radio.setup().second);
  for (int i = 0; i<10; i++) {
    auto radioSetup = radio.setup();
    if (radioSetup.first == -1) {
      Serial.println("Error was caused by radio setup: ");
      Serial.println(radioSetup.second);
      Serial.println("Trying again... [" + String(i+1) + "/10]");
    }
    else if (radioSetup.first == 0) {
      Serial.println("Radio configuration successful");
      break;
    }
  }

  Serial.println(radio.readFromRadio());
  Serial.println("Setup complete");

}


int i = 0;
void loop()
{
//   readSensors(data);
//   // writeSensorData(data);
//   printSensorData(data);

  if (radio.mode == RadioMode::unknown)
  {
      radio.enterSettingMode();
  }
  radio.enterTransmitMode();

  unsigned long currentMillis = millis();
  if ((currentMillis - previousMillis) >= interval)
  {
      previousMillis = currentMillis;
      radio.transmit(String(i)+";1000;27;28;100;50;420;42;50");
  }

  Serial.println(radio.readFromRadio());
  Serial.println(i);
  i++;
  delay(5000);
}
