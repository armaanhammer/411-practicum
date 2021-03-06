#include <SPI.h> //SD card
#include <SD.h>
#include <Wire.h>
#include "RTClib.h"

const int chipSelect = 15; //SD card

File myFile;
RTC_DS1307 RTC;

//float voltage = 0.1; //debug

void setup () {
  Serial.begin(115200);
  Wire.begin();

  //SD Setup
  Serial.print("Initializing SD card...");
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");



  //RTC setup
  RTC.begin();
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
  } else{
    Serial.println("RTC is running.\n");
//    RTC.adjust(DateTime(__DATE__, __TIME__));
  }


  //This is just to test the file. Prints all data already in file.
  // re-open the file for reading:
  myFile = SD.open("datalog.txt");
  if (myFile) {
    Serial.println("\n\n**************************************************\n");
    Serial.println("\t\tPrinting datalog.txt:");
    Serial.println("\n**************************************************\n\n");

    // read from the file until there's nothing else in it:
//    while (myFile.available()) {
//      Serial.write(myFile.read());
//    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

    Serial.println("\n\n**************************************************\n");
    Serial.println("\t\tNow outputting in realtime");
    Serial.println("\n**************************************************\n\n");
}


void loop () {
    //UV section
    // read the input on analog pin 0:
    int sensorValue = analogRead(A0);
    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
    float voltage = sensorValue * (5.0 / 1023.0);
//    voltage = voltage + 0.1; //debug

    //convert the voltage level to UV Index units
    //y=(1.4/12)*x+1
//    float uvIndex = ( (12 / 1.4) * voltage ) + 1;
    float uvIndex = 12 * (voltage - 1.47);
    
    //SD section
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    File dataFile = SD.open("datalog.txt", FILE_WRITE);

    // if the file is available, write to it:
      if (dataFile) {
      //RTC section
      DateTime now = RTC.now(); 
      dataFile.print(now.year(), DEC);
      dataFile.print('/');
      dataFile.print(now.month(), DEC);
      dataFile.print('/');
      dataFile.print(now.day(), DEC);
      dataFile.print(' ');
      dataFile.print(now.hour(), DEC);
      dataFile.print(':');
      dataFile.print(now.minute(), DEC);
      dataFile.print(':');
      dataFile.print(now.second(), DEC);

      //print UV section
      dataFile.print("\tAnalog value: \t");
      dataFile.print(sensorValue);
      dataFile.print("\tVoltage: \t");
      dataFile.print(voltage);
      dataFile.print("\tUV Index:\t");
      dataFile.print(uvIndex);
      dataFile.print("\n");

      //Serial.print("Wrote a new line\n");

      dataFile.close();
    }
    // if the file isn't open, pop up an error:
      else {
        Serial.println("error opening datalog.txt");
    }
    
    //RTC section
    DateTime now = RTC.now(); 
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);

    //print UV section
    Serial.print("\tAnalog value: \t");
    Serial.print(sensorValue);
    Serial.print("\tVoltage: \t");
    Serial.print(voltage);
    Serial.print("\tUV Index:\t");
    Serial.print(uvIndex);
    Serial.print("\n");

  delay(1000); //wait for 1 second
}
