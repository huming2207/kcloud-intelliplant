/* 
    SHSS KCloud IntelliPlant Server (master) source code
    Author: Jackson Ming Hu <huming2207@gmail.com>
            Technical Club Union of Shenzhen Highschool of Science
    ***THIS CODE IS PROTECTED BY GPLv2 LICENCE, FOR NON-COMMERCIAL USE ONLY! ***
    
    Server.ino -->> This is the main arduino project file, including some statements and header files.
*/

#include <dsm501.h>
#include <AM2321.h>
#include <Weather.h>
#include <EEPROM.h>
#include <DS3231.h>
#include <Wire.h>


 /* BMP180/BMP085 barometer statements and settings */
#define BMP085_ADDRESS 0x77 
float temperature;
float pressure;

const unsigned char OSS = 0; 
int ac1;
int ac2;
int ac3;
unsigned int ac4;
unsigned int ac5;
unsigned int ac6;
int b1;
int b2;
int mb;
int mc;
int md;
long b5; 

/* Dallas (Maxim) DS3231 RTC Clock statements and settings */
DS3231 RTClock;
bool hrs12;
bool hrsPM12;
bool CenturyDisplay = false;

/* DHT22 (aka. AM232x) statements */
AM2321 DHT;

/* Korean DSM501A Dust sensor statements */
unsigned long OriginDustDesity, FinalDustDesity;
dsm501 DSM501A;

/* AVR EEPROM R/W */
#include <avr/eeprom.h>
#define EEPROM_write(address, var) eeprom_write_block((const void *)&(var), (void *)(address), sizeof(var))
#define EEPROM_read(address, var) eeprom_read_block((void *)&(var), (const void *)(address), sizeof(var)) 


String SerialIn;
float SerialNumData[9] = {0};

/* Relay control pin on D10 */
int RelayControl = 10;

/* Declare some schedule integers */
int ScheduleHr;
int ScheduleMin;
int ScheduleSec;
int ScheduleCapacity;
int ScheduleStatus;
int ScheduleNum;
int Sec1;
int Min1;
int Hr1;
int TempRatio;
int HumidRatio;
int PressureRatio;
int DustRatio;
int XWeatherOut;
int YWeatherOut;
int AutoSwitch;
int MainSwitch = 0;

void setup(){
      Serial.begin(9600);
      pinMode(RelayControl,OUTPUT);
      RTClock.setClockMode(false);
      bmp085Calibration();
      DSM501A.setDatapin(8); // Set the DSM501 DATA pin to 8 (D8)
      DSM501A.enableFilter();
}




void loop(){
  
      temperature = bmp085GetTemperature(bmp085ReadUT()); 
      pressure = bmp085GetPressure(bmp085ReadUP());
      DSM501A.getParticles(OriginDustDesity,FinalDustDesity);
       
        /* Simplify the code in main Server.ino */
       SerialDataRead();  // Read the serial data first. :-)
       SerialWeatherOutput();
        
        /* Check if the time meets the schedule */
       RelaySchedule1();
       RelaySchedule2();
       RelaySchedule3();
       
}
