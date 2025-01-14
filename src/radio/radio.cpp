#include "radio.h"

void Radio::setup()
{
    radioSerial.begin(38400);
}

void Radio::sendCtrlC()
{
    radioSerial.print("\x03\n");
    mode = RadioMode::setting;
}

void Radio::enterTransmitMode()
{
    if (mode == RadioMode::unknown)
    {
        sendCtrlC()
    }
    radioSerial.println("set");
    mode = RadioMode::transmit;
}

void Radio::loop()
{
    sendCtrlC();
    delay(100);
    String readString = readFromRadio();
    Serial.print(readString);
    delay(5000);
}

String Radio::readFromRadio()
{
    if (radioSerial.available())
    {
        String response = radioSerial.readString();
        return response;
    }

    Serial.print("Uart not available");
    return "";
}

// 1. Koble til radio
// 2. Sende til ctrl c for å hoppe til instillinger
// 3. Lese hva radio sender tilbake
// 4. Sende radiosignalet til terminalen vår (>)

// 0. Klassen må vite hvilken modus radioen er i
// 1. Sende innstillinger til radio fra OBC, radioSerial.println
// 2. Sende en melding.Først sende kommando set->sende meldingen med ny linje
// 3. Sjekke om noen har sendt noe til oss
// 4. Sjekke om radioen er koblet til OBC-en. (Hvis vi sender ctrl-c skal radioen enten svare med > eller cmd_inv >)

// Underveis er det sikert lurt å print ting til monitor.

// Ctrl-C: Sende/motta->Innstillinger
// set : Innstillinger->Sende/motta

                                                                                