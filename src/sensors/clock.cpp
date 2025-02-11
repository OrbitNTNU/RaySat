#include "sensors/clock.h"


String timeStamp() {
    String time = String(getCurrentMillis());
    // Serial.println(time);
    return time; 
}