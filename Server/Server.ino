/* 
    SHSS KCloud IntelliPlant Server (master) source code
    Author: Jackson Ming Hu <huming2207@gmail.com>
            Technical Club Union of Shenzhen Highschool of Science
    ***THIS CODE IS PROTECTED BY GPLv2 LICENCE, FOR NON-COMMERCIAL USE ONLY! ***
    
    Server.ino -->> This is the main arduino project file, including some statements and header files.
    
    This project contains some 3rd party libraries, including:
    AM232x library
    Author: Wang Dong       From: https://github.com/wangdong/AM2321
    
    DS3231 RTC library
    Author: pamisisi        From: https://github.com/pamisisi/arduino-DS3231RTC
    
    ...and some other libraries from TAOBAO.COM's retailer which the authors are unknown. I don't know who they are but thanks for their hard work.
*/

#include <AM2321.h>
#include <Weather.h>
#include <EEPROM.h>
#include <Wire.h>
#include <DS3231RTC.h>

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
DS3231RTC RTC;
Time t;

/* DHT33 (aka. AM232x) statements */
AM2321 DHT;

/* Korean DSM501A Dust sensor statements */
int pin = 8;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 30000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;


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

/* SolarMonitor statements */
int SolarVoltageAnalog = 0; // The solar voltage analog data from Analog Pin 0 (A0)
int SolarCurrentAnalog = 1; // The solar current analog data from Analog Pin 1 (A1)
float SolarVoltage;
float SolarCurrent;


void setup(){
      pinMode(8,INPUT);
      Serial.begin(9600);
      pinMode(RelayControl,OUTPUT);
      bmp085Calibration();
      starttime = millis();
      t = RTC.getTime();
}




void loop(){
  
      /* 
          DM501A Sensor code
          Author: Unknown (From taobao's retailer)
      */
      duration = pulseIn(pin, LOW);
      lowpulseoccupancy = lowpulseoccupancy+duration;
    
      if ((millis()-starttime) > sampletime_ms)
      {
        ratio = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
        //concentration = (1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62)/2.5;  // This is the code to convert the ratio to concentration which is the captialist standard (pcs/ft^3)
        concentration = (ratio * 8.57) / 2.5;    // This is the damn communist standard which is ug/m^3 :-) 
        lowpulseoccupancy = 0;
        starttime = millis();
      } 
      pressure = bmp085GetPressure(bmp085ReadUP());
       
        /* Simplify the code in main Server.ino */
       SerialDataRead();  // Read the serial data first. :-)
       SerialWeatherOutput();
        
        /* Check if the time meets the schedule */
       RelaySchedule1();
       RelaySchedule2();
       RelaySchedule3();
       
       SolarVoltageCalculate();
       SolarCurrentCalculate();

       
}
