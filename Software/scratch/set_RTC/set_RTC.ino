#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 RTC;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();

  RTC.adjust(DateTime(__DATE__, __TIME__));
    Serial.println("\n\n**************************************************\n");
    Serial.println("\t\tTime set. Clock running.");
    Serial.println("\n**************************************************\n\n");
}

void loop() {
  // put your main code here, to run repeatedly:
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
    Serial.println();

//    Serial.print(DateTime(__DATE__, __TIME__));
    Serial.println();
    
    delay(1000); //wait for 1 second
}
