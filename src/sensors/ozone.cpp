#include "DFRobot_OzoneSensor.h"
#include "sensors/ozone.h"
#include "Arduino.h"

#define COLLECT_NUMBER      20
#define Ozone_I2CAddress    OZONE_ADDRESS_3


DFRobot_OzoneSensor Ozone;

int setup_ozone() {
    Serial.println("Trying to connect to Ozone Sensor");
    bool connected = false;
    // Ozone.begin(0x73);
    delay(1000);
    while (!Ozone.begin(0x73)) {
        Serial.print(".");
        delay(1000);
    } Serial.println("");
    Serial.println("Successfully connected to ozone sensor");
    Ozone.setModes(0x01);
    Serial.println("Ozone sensor successfully set up");
    return 0;
}
int read_ozone() {
    int16_t ozoneConcentration = Ozone.readOzoneData(COLLECT_NUMBER);
    // Serial.print("Ozone consentration is: "); Serial.print(ozoneConcentration); Serial.println("");
    return ozoneConcentration;
}