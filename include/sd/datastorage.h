#ifndef FileObject_h
#define FileObject_h

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
/*
This is a system for data storage meant for the RAYSAT.

---
example of usage:
DataObject dataVar;
void setup() {
    sdSystemInit(); // Initialises the SD card system
    // The data types can be:
    // 1: 
    // 2: 
    dataVar.init(dataName, dataType);
    
}
void loop() {
    dataVar.fileWrite("DATA");
}

---
Requirements for SD card:
- The SD card must be formated in FAT32 (FAT16 should also work¨
although this is not tested)
- The data storage system has no way of creating folders
therefore, the specific folder of each data type must be
created beforehand. 
- The names of the items can max be 6 letters long


*/
void sdSystemInit();

class DataObject {
    public:
        String name;
        int index;
        // int datatype;
        int fileWrite(String txt);
        void init(String dataObjectName);
    private:
        void newFile();
        int _lineCount = 0;
};

#endif