#include <SoftwareSerial.h>
#include <vector>

enum class RadioMode{unknown, setting, transmit};   // Modes that the radio can be in

class Radio{
    HardwareSerial radioSerial{PC5, PC4};  // Uart pins to radio (D1=TX/D0=RX on CN9)
    RadioMode mode = RadioMode::unknown;   // Makes the mode unknown
    void enterSettingMode();           // Entering settings mode
    void enterTransmitMode();   // Entering communicate mode
    // void sendSetup();   // Sending settings/setup commands
    void sendMessage(String message);
    void sendCtrlC();
    void setMode(RadioMode desiredMode);
    String getModeString(RadioMode mode);
    void menu();
    void write(const String& message);

    unsigned long previousMillis = 0; 
    const long interval = 10000;
public: 
    void setup();   
    void loop();
   
    String readFromRadio();     // Reading from radio
};