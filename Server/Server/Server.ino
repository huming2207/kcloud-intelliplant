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

/* AVR EEPROM R/W */
#include <avr/eeprom.h>
#define EEPROM_write(address, var) eeprom_write_block((const void *)&(var), (void *)(address), sizeof(var))
#define EEPROM_read(address, var) eeprom_read_block((void *)&(var), (const void *)(address), sizeof(var)) 

/* SHARP GP2Y1010AU0F Air dust sensor statements and settings */
int AirData = 0; // VOut from SHARP dust sensor
int AirLED = 3; // LED V-in to SHARP dust sensor
int PulseTime = 280; // Main pulse time
int WaitTime = 40; // Halt time 1
int WaitTime1 = 9680; //Halt time 2
float vM;
float FinalVoltage;
float FinalDustDesity;
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
      pinMode(AirLED,OUTPUT);
      pinMode(RelayControl,OUTPUT);
      RTClock.setClockMode(false);
      bmp085Calibration();
}




void loop(){
  
      temperature = bmp085GetTemperature(bmp085ReadUT()); 
      pressure = bmp085GetPressure(bmp085ReadUP());
   
       
        /* Simplify the code in main Server.ino */
       SerialDataRead();  // Read the serial data first. :-)
       GetDustData();
       SerialWeatherOutput();
        
        /* Check if the time meets the schedule */
       RelaySchedule1();
       RelaySchedule2();
       RelaySchedule3();
       
}
