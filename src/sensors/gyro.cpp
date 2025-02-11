#include "Arduino.h"
#include "LSM6DS3-SOLDERED.h"
#include "sensors/gyro.h"

Soldered_LSM6DS3 myIMU;
float gyro_x_call, gyro_y_call, gyro_z_call;

int calibrate_gyro(int samples, float& calibrated_x, float& calibrated_y, float& calibrated_z) {
    Serial.println("Starting Gyro calibration");
    myIMU.begin();
    for (int i = 0; i < samples; ++i) {
        // print a dot every 200 samples
        if (i % 200 == 0) {
            Serial.print(".");
        }

        // Add values to calculate the average later
        gyro_x_call += myIMU.readFloatGyroX();
        gyro_y_call += myIMU.readFloatGyroY();
        gyro_z_call += myIMU.readFloatGyroZ();
        delay(3);
    }
    // Calculate averages
    gyro_x_call /= samples;
    gyro_y_call /= samples;
    gyro_z_call /= samples;
    Serial.println();
    Serial.println("Successfully calibrated gyro sensor");
    Serial.print("x: "); Serial.println(gyro_x_call);
    Serial.print("y: "); Serial.println(gyro_y_call);
    Serial.print("z: "); Serial.println(gyro_z_call);
    
    calibrated_x = gyro_x_call;
    calibrated_y = gyro_y_call;
    calibrated_z = gyro_z_call;
    return 0;
}

void read_gyro(float& x, float& y, float& z, float& calibrated_x, float& calibrated_y, float& calibrated_z) {
    x = myIMU.readFloatGyroX() - gyro_x_call;
    y = myIMU.readFloatGyroY() - gyro_y_call;
    z = myIMU.readFloatGyroZ() - gyro_z_call;
    // Serial.print("Gyroscope: ");
    // Serial.print("X = "); Serial.print(x);
    // Serial.print("Y = "); Serial.print(y);
    // Serial.print("Z = "); Serial.println(z);
    // static float gyroArray[] = {x, y, z};
    // return & gyroArray;
}