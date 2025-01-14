#include <SoftwareSerial.h>

enum class RadioMode{unknown, setting, transmit};

class Radio{
    HardwareSerial radioSerial{PC5, PC4};
    RadioMode mode = RadioMode::unknown;
    void sendCtrlC();
    void enterTransmitMode();
public: 
    void setup();
    void loop();
   
    String readFromRadio();
};