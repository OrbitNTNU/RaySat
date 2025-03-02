#include "sensors/height.h"

#define R 287.05274 // general gass constant for dry air
#define g 9.8214675 // gravitational acceleration in cellar of NTNU

void Height::setupHeight(float temp, double pressure) {
    T0_ = temp;
    p0_ = pressure;
}

void Height::calculateHeight(SensorData& data) {
    data.height = (R/g)*((data.outsideTemperature+T0_)/2)*log(p0_/data.pressure);
}
Height::Height() {
    T0_ = 0.0;
    p0_ = 0.0;
}