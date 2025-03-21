#include <SD.h>
#include <SPI.h>
#include <sd/datastorage.h>

Sd2Card card;
SdVolume volume;
SdFile root;
const int chipSelect = 10;

void sdSystemInit(bool debugMode) {
    Serial.println("----------------------");
    Serial.println("Initialising SD card");
    if (!card.init(SPI_HALF_SPEED, chipSelect)) {
        Serial.println("initialization failed. Things to check:");
        Serial.println("* is a card inserted?");
        Serial.println("* is your wiring correct?");
        Serial.println("* did you change the chipSelect pin to match your shield or module?");
        if (debugMode) {
            while(1);
        }
    } else {
        Serial.println("Wiring is correct and a card is present.");
    }
    if (!volume.init(card)) {
        Serial.println("Could not find FAT16/FAT32 patrition. \nMake sure you've formated the card");
        if (debugMode) {
            while(1);
        }
    }
    root.openRoot(volume);
    root.ls(LS_R | LS_DATE | LS_SIZE);
    root.close();
    if (!SD.begin(10)) {
        Serial.println(F("SD CARD FAILED, OR NOT PRESENT!"));
        if (debugMode) {
            while (1); // don't do anything more:
        }
    }
}

void DataObject::fileWriteTest() {
    String path = name+"/"+"test.txt";
    File file = SD.open(path,FILE_WRITE);
    if (file) {
        file.close();
    } else {
        Serial.println("error opening the file when trying to write  to test file");
        while (debug);
    }
}

void DataObject::init(String dataObjectName,bool debugMode) {
    Serial.println("----------------------");
    Serial.println("Initialising data storage: " + dataObjectName);
    name = dataObjectName;
    // datatype = dataObjectType;
    index=0;
    _lineCount = 0;
    debug = debugMode;
    Serial.println("Writing test file");
    fileWriteTest();
}
void DataObject::newFile() {
    index++;
    _lineCount = 0;
}

int DataObject::fileWrite(String txt,String timestamp) {
    // Serial.println(path);
    String path = name+"/"+name+String(index)+".txt";
    File file = SD.open(path, FILE_WRITE);
    if (file) {
        file.print(timestamp);
        file.print(",");
        file.println(txt);
        _lineCount++;
        if (_lineCount >= 1000) {
            newFile();
        }
        file.close();
    } else {
        Serial.print("error opening the file when trying to write "); Serial.print(txt); Serial.print(" to "); Serial.println(name);
        while(debug);
        return 1;
    }
    return 0;
}
