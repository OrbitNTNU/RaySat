#include "radio.h"

std::pair<int, String> Radio::setup(int aprsInterval /*= 20*/, bool _verbose /*= true*/)
{
        verbose = _verbose;

        
        std::vector<String> GNSSCommands = {
            "baud1 9600",
            "port1 nmea",
            "p1-out none",
            "p1-rfilter none",
            "p1-pfilter none",
            "verbose 3"};
        
        // auto results = sendConfiguration(GNSSCommands);
        // if (results.first < 0) {
        //     return results;
        // }

        std::vector<String> setupCommands = {
            "access always",
            "mode ax25-1k2",  // sets the radio communication protocol
            "power hi",
            "mycall LA9ORB-11",
            "path  ",
            "freq 145500000", // sets the frequency on the radio TX/RX
            "mice-cmt Orbit NTNU VHF test, \\vV \\tC HDOP\\h",
            "mice-cmtint 3",
            "mice-msg 7",
            "mice-symbol /O",
            "autoexec-cmd port-rf-mute 1\\nmode ax25-1k2\\nfreq 144800000\\nmice-tx\\nfreq  145500000\\nmode ax25-1k2\\nport-rf-mute 0",
            "autoexec-int " + String(aprsInterval),
            "baud1 9600",
            "port1 nmea",
            "p1-out all",
            "p1-rfilter none",
            "p1-pfilter none",
            "port0 text",  // This prevents airborn mode to be printed
            "verbose 3",
            "cfg-save",
        };
    
    radioSerial.begin(BAUD_RATE);

    enterSettingMode();

    return sendConfiguration(setupCommands);
}

void Radio::write(const String &message)
{
    radioSerial.println(message);
}

std::pair<int, String> Radio::transmit(String message)
{
    auto result = enterTransmitMode();
    if (result.first == -1) {return result;}

    write(message);
    return std::make_pair(0, "");
}

void Radio::sendCtrlC()
{   // Ctrl C in ASCII
    write("\x03\n");
}

void Radio::enterSettingMode()
{   // Entering configuration mode
    if (mode == RadioMode::transmit)
    {
        sendCtrlC();
        delay(100);
        Serial.println("Entering settings mode");
        mode = RadioMode::setting;
    }
    else if (mode == RadioMode::unknown){
        sendCtrlC();
        write("");
        delay(100);
        readFromRadio();
        Serial.println("Entering settings mode");
        mode = RadioMode::setting;
    }
}

std::pair<int, String> Radio::enterTransmitMode()
{   // Can transmit and recieve information
    if (mode != RadioMode::transmit)
    {
        if (mode == RadioMode::unknown)
        {
            enterSettingMode();
        }

        auto result = sendSetupCommand("set"); 
        delay(50);
        if (result.first == -1) {return result;}
        mode = RadioMode::transmit;
        if (verbose) {
            Serial.println("Radio set to transmit mode");
        }  

        return result;
    }

    return std::make_pair(0, "");
}

String Radio::readFromRadio()
{   // Read from radio and clear sending memory
    if (radioSerial.available()) 
    {   // If the radio-port is available, read from it)
        String response = radioSerial.readString();
        return response;
    }
    return "";
}

std::pair<int, String> Radio::sendSetupCommand(const String& command)
{

    if (mode != RadioMode::setting)
    {
        return std::make_pair(-1, "Not in settings mode");
    }

    write(command);

    delay(50);

    String response = readFromRadio();

    if (verbose)
    {
        Serial.print("Sending command: (");
        Serial.print(command);
        Serial.print(") got response: ");
        Serial.println(response);
    }

    // Hatlosning :))
    if ((std::string(command.c_str()).compare(0, 9, "mice-cmt ") == 0) || 
    (std::string(command.c_str()).compare(0, 13, "autoexec-cmd ") == 0)) {
        return (std::make_pair(0, response));
    }

    if (std::string(response.c_str()).find(std::string(command.c_str()) + " ok") == std::string::npos){
        return std::make_pair(-1, "Error running: " + command + " -> " + response);
    }

    return std::make_pair(0, response);
}

std::pair<int, String> Radio::sendConfiguration(std::vector<String> commandsToSend)
{
    enterSettingMode();
    for (int i = 0; i < commandsToSend.size(); i++)
    {
        auto result = sendSetupCommand(commandsToSend.at(i));
        if (result.first == -1) {
            return result;
        }
    }
    auto result = enterTransmitMode();
    if (result.first == -1) {
        return result;
    }
    return std::make_pair(0, "");
}

String Radio::getModeString(RadioMode mode)
{
    switch (mode)
    {
    case RadioMode::setting:
        return "Setting Mode";
    case RadioMode::transmit:
        return "Transmit Mode";
    case RadioMode::unknown:
        return "Unknown Mode";
    default:
        return "Invalid Mode";
    }
}

// 2. Sende sensordata
// 3. Koble gps slik som står på notion

/* Hvordan lese seriellporten til radioen via rasperry pi:
1. ssh inn (ssh orbit, nå)
2. ls -l /dev/serial/by-id (/dev/ttyUSB0)


Koble til rasperry pi: 
sudo minicom -b 38400 -o -D /dev/ttyUSB0
Ctrl + A og Q for å gå ut
Ctrl + A og Z, og O, serial port, skru av hardware flow control osv


*/