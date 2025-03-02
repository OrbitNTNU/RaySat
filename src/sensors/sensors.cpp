#include "sensors/sensors.h"
#include "sensors/height.h"

DataObject temperatureOutdoorsData;
DataObject temperatureInndoorsData;
DataObject pressureData;
DataObject ultravioletData;
DataObject gyroData;
DataObject ozoneData;

TempSensor tempOutdoors;
TempSensor tempIndoors;

float gyro_calibrated_x;
float gyro_calibrated_y;
float gyro_calibrated_z;

Height heightCalculator;

SensorData::SensorData() {
    timestamp_ms = "0";
    ozone_ppm = 0;
    uv = 0;
    pressure = 0.0;
    insideTemperature = 0.0;
    outsideTemperature = 0.0;
    gyro_x = 0.0;
    gyro_y = 0.0;
    gyro_z = 0.0;
    height = 0.0;
}

void initSensors() {
    // Setup sensors
    Serial.println("Setting up sensors");
    tempOutdoors.init(0x48);
    tempIndoors.init(0x49);
    setup_pressure();
    setup_uv();
    calibrate_gyro(2000, gyro_calibrated_x, gyro_calibrated_y, gyro_calibrated_z);
    setup_ozone();
    // setup sd card
    Serial.println("Setting up SD storage for sensors");
    temperatureOutdoorsData.init("tmpout");
    temperatureInndoorsData.init("tmpinn");
    pressureData.init("pressu");
    ultravioletData.init("violet");
    gyroData.init("gyrosc");
    ozoneData.init("ozones");
    float T0 = tempOutdoors.read();
    double P0 = read_pressure();
    heightCalculator.setupHeight(T0,P0);
}

void readSensors(SensorData& data) {
    // --------------------- Read ----------------------
    // time
    data.timestamp_ms = timeStamp();
    // Pressure
    data.pressure = read_pressure();
    // Temperature
    data.insideTemperature = tempIndoors.read();
    data.outsideTemperature= tempOutdoors.read();
    // Pressure
    data.pressure = read_pressure();
    // UV
    data.uv = read_uv();
    // Gyro
    read_gyro(data.gyro_x,data.gyro_y,data.gyro_z,
              gyro_calibrated_x,gyro_calibrated_y,gyro_calibrated_z);
    // Ozone
    data.ozone_ppm = read_ozone();
    heightCalculator.calculateHeight(data);
}

void writeSensorData(const SensorData& data) {
    // --------------------- Write to SD ----------------------
    ozoneData.fileWrite(String(data.ozone_ppm),data.timestamp_ms);
    ultravioletData.fileWrite(String(data.uv),data.timestamp_ms);
    pressureData.fileWrite(String(data.pressure),data.timestamp_ms);
    temperatureInndoorsData.fileWrite(String(data.insideTemperature),data.timestamp_ms);
    temperatureOutdoorsData.fileWrite(String(data.outsideTemperature),data.timestamp_ms);
    gyroData.fileWrite(String(data.gyro_x)+";"+String(data.gyro_y)+";"+String(data.gyro_z),data.timestamp_ms);

}

void printSensorData(const SensorData& data) {
    // --------------------- Print ----------------------
    Serial.print("Ozone Data: "); Serial.println(data.ozone_ppm);
    Serial.print("UV Data: "); Serial.println(data.uv);
    Serial.print("Pressure Data: "); Serial.println(data.pressure);
    Serial.print("Outdoors temperature Data: "); Serial.println(data.outsideTemperature);
    Serial.print("Inndoors temperature Data: "); Serial.println(data.insideTemperature);
    Serial.print("Gyro X: "); Serial.print(data.gyro_x); 
    Serial.print(" Gyro Y: "); Serial.print(data.gyro_y);
    Serial.print(" Gyro Z: "); Serial.println(data.gyro_z);
    Serial.print("Height: "); Serial.println(data.height);
}
