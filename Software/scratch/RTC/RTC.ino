#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 RTC;

//#define D1 5 // I2C Bus SCL (clock)
//#define D2 4 // I2C Bus SDA (data)

void setup () {
  //delay(10000); //Debug
    Serial.begin(115200);
    Wire.begin(0,2);
    RTC.begin();
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}
void loop () {
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
    delay(1000);
}
