#include <Arduino.h>
#include <Wire.h>
// local libraries
#include "sd/datastorage.h"
#include "sensors/sensors.h"
#include "radio/radio.h"
#include "reactionWheel/rwController.h"

// #include "sensors/scanner.h"


// ------------------- Class Initilizations -------------------  
Radio radio;
SensorData data;
RWController rwController;
bool flightMode = false;
String callSign = "LA9ORB";

/* --- hvit -> RX, svart -> TX på OBC --- */

// ------------------- Clock Variables -------------------
unsigned long previousMillis;
const long interval = 5000;

// ------------------- Setup -------------------
void setup()
{
  Serial.begin(9600);
  Serial.println("Initializing...");
  // sdSystemInit();
  Serial.println("----------------------");
  initSensors();

  // ------------------- Radio Setup -------------------
  // Serial.println(radio.setup().second);
  radio.mode = RadioMode::unknown;
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
  radio.checkGnssFix();
  // while (true) {
  //   auto result = radio.checkGnssFix();
  //   if (result.first > 0) {
  //       break;
  //   }
  //   else if (result.first ) {}

  // }
  Serial.println("Setup complete");

  flightMode = true;
  unsigned long startTime = millis();
}


int i = 0;
// ------------------- Loop -------------------
void loop()
{

  readSensors(data);
  writeSensorData(data);
  rwController.control(data);
  printSensorData(data);

  unsigned long currentMillis = millis();
  if ((currentMillis - previousMillis) >= interval)
  {
    String dataString = transmitSensorData(data);
    auto transmitResult = radio.transmit(callSign + ";" + dataString);
    Serial.println(callSign + dataString);
    previousMillis = currentMillis;
    // auto transmitResult = radio.transmit(String(i) + ";1000;0;0;0;50;420;42;50");
    // auto transmitResult = radio.transmit(String(i) + "Hei Knut :-) Hilsen fra Orbit NTNU!");
    // Serial.println(String(i) + "Hei Knut :-) Hilsen fra Orbit NTNU!");
    // Serial.println((String(i) + ";1000;0;0;0;50;420;42;50")); 
    if (transmitResult.first == -1) {
      Serial.println("Transmission failed: " + transmitResult.second);
    }
  }
  

  Serial.println(radio.readFromRadio());
  if (Serial.available()>0) {
    Serial.println("From radio, here ya go: " + radio.readFromRadio());
  }
  Serial.println(i);
  i++;
  delay(5000);
}
