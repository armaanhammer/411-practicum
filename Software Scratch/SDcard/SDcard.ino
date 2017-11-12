#include <SD.h>
#include <SPI.h>

File myFile;
//int pinCS = 9; 
int csPin = 9; 

void setup() {
  
  
  Serial.begin(115200);
  Serial.println("Debug checkpoint 1\n");
  //pinMode(pinCS, OUTPUT);
  pinMode(csPin, OUTPUT);

  Serial.println("Debug checkpoint 2\n");
  // SD Card Initialization
  if (SD.begin(csPin))
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
  
  // Create/Open file 
  myFile = SD.open("test.txt", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.println("Writing to file...");
    // Write to file
    myFile.println("Testing text 1, 2 ,3...");
    myFile.close(); // close the file
    Serial.println("Done.");
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening test.txt");
  }
  // Reading the file
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("Read:");
    // Reading the whole file
    while (myFile.available()) {
      Serial.write(myFile.read());
   }
    myFile.close();
  }
  else {
    Serial.println("error opening test.txt");
  }
  
}
void loop() {
  // empty
}
