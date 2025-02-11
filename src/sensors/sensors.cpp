#include "sensors/sensors.h"

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
}
void readSensors(bool print) {
    // --------------------- Read ----------------------
    // time
    String tid = timeStamp();
    // Pressure
    double pressure = read_pressure();
    // Temperature
    float tempOut = tempOutdoors.read();
    float tempInn = tempIndoors.read();
    // Pressure
    float pressu = read_pressure(); 
    // UV
    uint32_t uv = read_uv();
    // Gyro
    float x;
    float y;
    float z;
    read_gyro(x,y,z,gyro_calibrated_x,gyro_calibrated_y,gyro_calibrated_z);  
    // Ozone
    int ozone = read_ozone();
    // --------------------- Write to SD ----------------------
    ozoneData.fileWrite(String(ozone),tid);
    ultravioletData.fileWrite(String(uv),tid);
    pressureData.fileWrite(String(pressu),tid);
    temperatureInndoorsData.fileWrite(String(tempInn),tid);
    temperatureOutdoorsData.fileWrite(String(tempOut),tid);
    gyroData.fileWrite(String(x)+";"+String(y)+";"+String(z),tid);
    // --------------------- Print ----------------------
    if (print) {
        Serial.print("Ozone Data: "); Serial.println(ozone);
        Serial.print("UV Data: "); Serial.println(uv);
        Serial.print("Pressure Data: "); Serial.println(pressu);
        Serial.print("Outdoors temperature Data: "); Serial.println(tempOut);
        Serial.print("Inndoors temperature Data: "); Serial.println(tempInn);
        Serial.print("Gyro X: "); Serial.print(x); 
        Serial.print(" Gyro Y: "); Serial.print(y);
        Serial.print(" Gyro Z: "); Serial.print(z);
    }
}