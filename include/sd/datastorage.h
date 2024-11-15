#include <SD.h>
#include <SPI.h>

class FileObject {
    public:
        String name;
        int index;
        int datatype;
        int fileWrite(String txt);
        FileObject(String fileObjectName, int fileObjectDataType);
    private:
        void newFile();
        File openFile();
};

// void setup_sdCard();