#pragma once
int calibrate_gyro(int samples, float& calibrated_x, float& calibrated_y, float& calibrated_z);
void read_gyro(float& x, float& y, float& z, float& calibrated_x, float& calibrated_y, float& calibrated_z);