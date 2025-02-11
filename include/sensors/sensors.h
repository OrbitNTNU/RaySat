#pragma once
#include "temperature.h"
#include "uv.h"
#include "pressure.h"
#include "ozone.h"
#include "gyro.h"
#include "sd/datastorage.h"

void initSensors();
void readSensors(bool print);