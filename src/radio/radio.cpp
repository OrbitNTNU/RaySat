#include "radio.h"

std::pair<int, String> Radio::setup(int aprsInterval /*= 20*/, bool _verbose /*= true*/)
{
        verbose = _verbose;

        
        // std::vector<String> GNSSCommands = {
        //     "baud1 9600",
        //     "port1 nmea",
        //     "p1-out none",
        //     "p1-rfilter none",
        //     "p1-pfilter none",
        //     "verbose 3"};

        /*
        */

        std::vector<String> setupCommands = {
            "access always",
            "mode ax25-1k2",  // sets the radio communication protocol
            "power mid",    // CHANGE TO HI!!!!!!
            "mycall LA9ORB-11",
            "path  ",
            "freq 144700000", // sets the frequency on the radio TX/RX
            "mice-cmt SO Test, \\vV \\tC HDOP\\h",
            "mice-cmtint 3",
            "mice-msg 7",
            "mice-symbol /O",
            "autoexec-cmd port-rf-mute 1\\nmode ax25-1k2\\nfreq 144800000\\nmice-tx\\nfreq 144700000\\nmode ax25-1k2\\nport-rf-mute 0",
            "autoexec-int " + String(aprsInterval),
            "tdma-frame 1000",
            "tx-pos 16",
            "tx-src 16",
            "tx-stat 16",
            "baud1 9600",
            "port1 nmea",
            "p1-out none",
            "p1-rfilter none",
            "p1-pfilter none",
            "port0 text",  // This prevents airborn mode to be printed
            "verbose 3"
        };
    
    radioSerial.begin(BAUD_RATE);

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

std::pair<int, String> Radio::checkGnssFix() {
    auto result = sendSetupCommand("info");
    Serial.println(result.second);
    if (result.first < 0) {return result;}

    String fixString = result.second;
    fixString.replace(" ", ""); 

    int fixIndex = fixString.indexOf("g_fix");
    if (fixIndex != -1) {
        String fixValue = fixString.substring(fixIndex+5);
        Serial.println("Processed String: " + fixString);
        Serial.println("Extracted Fix Value: " + fixValue);

        if (fixValue.toInt() > 0) {
            Serial.println("GNSS fix acquired");
            gnssFix = true;
            return std::make_pair(0, "");
        }
        else {
            Serial.println("No GNSS fix");
            return std::make_pair(1, "No GNSS fix");
        }
    } else {
        Serial.println("g_fix not found.");
        return std::make_pair(-2, "g_fix not found");
    }
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

    delay(10);
    auto response = readFromRadio();
    
    if (verbose)
    {
        Serial.print("Sending command: (");
        Serial.print(command);
        Serial.print(") got response: ");
        Serial.println(response);
    }

    // Exceptions
    if ((std::string(command.c_str()).compare(0, 9, "mice-cmt ") == 0) || 
    (std::string(command.c_str()).compare(0, 13, "autoexec-cmd ") == 0)) {
        return (std::make_pair(0, response));
    }

    if (std::string(command.c_str()).compare(0, 5, "info ") == 0) {
        return std::make_pair(0, response);
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