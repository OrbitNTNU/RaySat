#include <Arduino.h>
#include <Wire.h>
// local libraries
#include "sd/datastorage.h"
#include "sensors/sensors.h"
#include "radio/radio.h"
#include "reactionWheel/rwController.h"
#include "bms/bms.h"

#define DEBUGMODE true

// ----- Class Initilizations -----
Radio radio;
SensorData data;
RWController rwController;
const String callSign = "LA9ORB";

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
  sdSystemInit(DEBUGMODE);
  rwController.init(D2);
  Serial.println("----------------------");
  initSensors(DEBUGMODE);

  // ------------------- Radio Setup -------------------
  radio.mode = RadioMode::unknown;
  radio.initRadio();
  
  Serial.println(radio.readFromRadio());
  radio.checkGnssFix();
  radio.gnssFixInit();


  Serial.println("Setup complete");

  unsigned long startTime = millis();
}


// ------------------- Loop -------------------
void loop()
{
  readSensors(data);
  writeSensorData(data);
  rwController.control(data);
  
  bool rwState = rwController.getState();
  String rwOffOn = rwController.stateToString(rwState);
  bool rwManual = rwController.getManual();
  String manualOnOff = rwController.manualToString(rwManual); 

  unsigned long currentMillis = millis();
  if ((currentMillis - previousMillis) >= interval)
  {
    String dataString = transmitSensorData(data);
    auto transmitResult = radio.transmit(callSign + ";" + dataString + ";" + rwOffOn + ";" + manualOnOff);
    Serial.println(callSign + ";" + dataString + ";" + rwOffOn);

    // auto transmitResult = radio.transmit(callSign + ";" + "10000;1000;23;23;0;30;1;1;1;100;3" + ";" + "rwOn" + ";");
    // Serial.println(callSign + ";" + "10000;1000;23;23;0;30;1;1;1;100;3" + ";" + "rwOn" + ";");
    previousMillis = currentMillis;

    if (transmitResult.first == -1) {
      Serial.println("Transmission failed: " + transmitResult.second);
    }
  }
  
  String incomingMessage = radio.readFromRadio();
  std::string messageStr = incomingMessage.c_str();

  radio.checkIncomingRW(messageStr, rwController);

  Serial.println(radio.readFromRadio());

  if (DEBUGMODE){printSensorData(data);}
  delay(1000);
}
