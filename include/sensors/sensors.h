#pragma once
#include "temperature.h"
#include "uv.h"
#include "pressure.h"
#include "ozone.h"
#include "gyro.h"
#include "sd/datastorage.h"
#include "sensors/clock.h"

struct SensorData {
    String timestamp_ms;
    int ozone_ppm;
    uint32_t uv;
    double pressure;
    float insideTemperature;
    float outsideTemperature;
    float gyro_x;
    float gyro_y;
    float gyro_z;
    float height;
    SensorData();
};
void initSensors();
void readSensors(SensorData& data);
void writeSensorData(const SensorData& data);
void printSensorData(const SensorData& data);
