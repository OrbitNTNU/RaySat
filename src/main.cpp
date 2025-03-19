#include <Arduino.h>
#include <Wire.h>
// local libraries
#include "sd/datastorage.h"
#include "sensors/sensors.h"
#include "radio/radio.h"
#include "reactionWheel/rwController.h"
#include "bms/bms.h"

// ----- Class Initilizations -----
Radio radio;
SensorData data;
RWController rwController;
String callSign = "LA9ORB";
bool flightMode = false;
bool rwOff = false;

/* --- hvit -> RX, svart -> TX på OBC --- */

// ----- Clock Variables -----
unsigned long previousMillis;
const long interval = 5000;

// ------------------- Setup -------------------
void setup()
{
  Serial.begin(9600);
  Serial.println("Initializing...");
  bmsInit();
  sdSystemInit();
  initSensors();

  // ------------------- Radio Setup -------------------
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
  while (true) {
    auto result = radio.checkGnssFix();
    if (result.first == 0) {
        break;
    }

    else if (result.first > 0) {
      Serial.println("Waiting for a valid GNSS fix...");
    }
    
    else {
      Serial.println("Erorr in GNSS fix check");
      break;
    }
  }


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
  // rwController.control(data);
  // printSensorData(data);

  unsigned long currentMillis = millis();
  if ((currentMillis - previousMillis) >= interval)
  {
    String dataString = transmitSensorData(data);
    auto transmitResult = radio.transmit(callSign + ";" + dataString);
    Serial.println(callSign + ";" + dataString);
    previousMillis = currentMillis;

    if (transmitResult.first == -1) {
      Serial.println("Transmission failed: " + transmitResult.second);
    }
  }
  
  String incomingMessage = radio.readFromRadio();
  std::string messageStr = incomingMessage.c_str();

  if (messageStr.find("rwoff") != std::string::npos) {
    rwOff = true;
  }
  if (messageStr.find("rwon") != std::string::npos) {
    rwOff = false;
  }

  Serial.println(radio.readFromRadio());

  Serial.println(i);
  i++;
  delay(5000);
}
