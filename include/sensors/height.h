#pragma once
#include "sensors/sensors.h"
#include <math.h>
class Height {
private:
    float T0_;
    float p0_;
public:
    void setupHeight(float temp, double pressure);
    void calculateHeight(SensorData& data);
    Height();
};