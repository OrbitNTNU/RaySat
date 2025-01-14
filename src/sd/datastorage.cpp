// #include <SD.h>
// #include <SPI.h>

// File myFile;

// class FileObject {
//   public:
//     String name;
//     int index;
//     int datatype;
//     int fileWrite(String txt);
//     //int getTime();
//     // Constructor
//     FileObject(String fileObjectName, int fileObjectDataType){
//       datatype = fileObjectDataType;
//       name = fileObjectName;
//       mkDir(name);
//       index = 0;
//     }
//   private:
//     void newFile();
//     File openFile();
// };

// void mkDir(String dirname) {
//   if (dirExists(dirname)) {
//     return;
//   }
  
//   else if (!dirExists(dirname)) {
//     SD.mkdir(dirname);
//   }
// }

// bool dirExists(String dirname){
//   return SD.exists(dirname);
// }

// // TODO: get time stamp
// // TODO: Maybe add datatype to what will be printed
// int FileObject::fileWrite(String txt) {
  
//   File file = openFile();
  

//   file.println(txt);
  

//   file.close();
// }

// void FileObject::newFile() {
//   index++;
// }

// File FileObject::openFile() {
//   File file = SD.open("/"+name+"/"+name + String(index)+".txt", FILE_WRITE);
//   return file;
// }


// // void setup_sdCard() {
// //   // Open serial communications and wait for port to open:
// //   while (!Serial) {
// //     ; // wait for serial port to connect. Needed for native USB port only
// //   }
// //   Serial.print("Initializing SD card...");

// //   if (!SD.begin(10)) {
// //     Serial.println("initialization failed!");
// //     while (1);
// //   }
// //   Serial.println("initialization done.");

// //   // open the file. note that only one file can be open at a time,
// //   // so you have to close this one before opening another.
// //   myFile = SD.open("test.txt", FILE_WRITE);

// //   // if the file opened okay, write to it:
// //   if (myFile) {
// //     Serial.print("Writing to test.txt...");
// //     myFile.println("testing 1, 2, 3.");
// //     // close the file:
// //     myFile.close();
// //     Serial.println("done.");
// //   } else {
// //     // if the file didn't open, print an error:
// //     Serial.println("error opening test.txt");
// //   }

// //   // re-open the file for reading:
// //   myFile = SD.open("test.txt");
// //   if (myFile) {
// //     Serial.println("test.txt:");

// //     // read from the file until there's nothing else in it:
// //     while (myFile.available()) {
// //       Serial.write(myFile.read());
// //     }
// //     // close the file:
// //     myFile.close();
// //   } else {
// //     // if the file didn't open, print an error:
// //     Serial.println("error opening test.txt");
// //   }
// // }