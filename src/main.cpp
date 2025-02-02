#include <Arduino.h>
#include <Wire.h>
// local libraries
#include "sensors/pressure.h"
#include "sensors/temperature.h"
#include "sensors/uv.h"
#include "sensors/gyro.h"
#include "sd/datastorage.h"

// put function declarations here:
int myFunction(int, int);
DataObject temperature;
DataObject pressure;
DataObject ultraviolet;

float gyro_calibrated_x;
float gyro_calibrated_y;
float gyro_calibrated_z;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Serial.println("Initializing...");
  // sdSystemInit();
  // Serial.println("----------------------");
  // setup_temperature();
  // temperature.init("temper",2);
  // setup_pressure();
  // pressure.init("pressu",2);
  // setup_uv();
  // ultraviolet.init("violet",2);
  // calibrate_gyro(2000, gyro_calibrated_x, gyro_calibrated_y, gyro_calibrated_z);
  // Serial.print("Gyroverdier: "); Serial.print(gyro_calibrated_x);Serial.print(gyro_calibrated_y);Serial.print(gyro_calibrated_z);
}

void loop() {
  // put your main code here, to run repeatedly:
  // double pressure = read_pressure();
  // Serial.print("Pressure: ");
  // Serial.println(pressure);

  // --------------------- Sensor ----------------------
  // Temperature
  // float temp = read_temperature(); 
  // temperature.fileWrite(String(temp));
  //Serial.print("Temperature: ");Serial.println(temp);
  // Pressure
  // float pressu = read_pressure(); 
  // pressure.fileWrite(String(pressu));
  //Serial.print("Pressure: ");Serial.println(pressu);
  // UV
  // uint32_t uv = read_uv();
  // ultraviolet.fileWrite(String(uv));
  // Serial.print("UV: ");Serial.println(String(uv));
  // float x;
  // float y;
  // float z;
  // read_gyro(x,y,z,gyro_calibrated_x,gyro_calibrated_y,gyro_calibrated_z);
  
  // Serial.print("Gyro: "); Serial.println(x); Serial.print(y); Serial.println(z);
  delay(1000);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}