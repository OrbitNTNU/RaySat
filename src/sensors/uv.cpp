#include "Adafruit_LTR390.h"
#include "sensors/uv.h"

Adafruit_LTR390 ltr = Adafruit_LTR390();

int setup_uv(bool debugMode) {
    bool begun = ltr.begin();
    delay(1000);
    // Serial.print("UV sensor found: ");Serial.println(begun);
    if (!begun) {
        Serial.println("Couldn't find LTR sensor!");
        while (debugMode);
    } else {
        Serial.println("Found LTR sensor!");
    }
    delay(100);
    Serial.println("continuing to set up UV sensor");
    ltr.setMode(LTR390_MODE_UVS);
    delay(100);

    ltr.setGain(LTR390_GAIN_3);
    delay(100);

    ltr.setResolution(LTR390_RESOLUTION_16BIT);
    ltr.setThresholds(100,1000);
    ltr.configInterrupt(true, LTR390_MODE_UVS);  
    return 0;
}
// BUG: the uv sensor won't give out data and reverts itself
void get_uv_sensor_info() {

    Serial.print("Resolution : ");
    if (ltr.getMode() == LTR390_MODE_UVS) {
        Serial.println("In UVS mode");
    } else {
        Serial.println("In ALS mode");
    }
    switch (ltr.getResolution()) {
        case LTR390_RESOLUTION_13BIT: Serial.println(13); break;
        case LTR390_RESOLUTION_16BIT: Serial.println(16); break;
        case LTR390_RESOLUTION_17BIT: Serial.println(17); break;
        case LTR390_RESOLUTION_18BIT: Serial.println(18); break;
        case LTR390_RESOLUTION_19BIT: Serial.println(19); break;
        case LTR390_RESOLUTION_20BIT: Serial.println(20); break;
    }
    Serial.print("Gain: ");
    ltr390_gain_t test = ltr.getGain();
    switch (test) {
        case LTR390_GAIN_1: Serial.println(1); break;
        case LTR390_GAIN_3: Serial.println(3); break;
        case LTR390_GAIN_6: Serial.println(6); break;
        case LTR390_GAIN_9: Serial.println(9); break;
        case LTR390_GAIN_18: Serial.println(18); break;
    }
    delay(100);
}
uint32_t read_uv() {
    if (ltr.newDataAvailable()) {
        uint32_t uv = ltr.readUVS();
        // Serial.print("UV data: ");
        // Serial.println(uv);
        return uv;
    }
    return 0;
}