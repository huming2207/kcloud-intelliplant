#include <EEPROM.h>
#include <DS3231.h>
#include <Wire.h>
#include <dht.h>
#include <Adafruit_BMP085.h>


#define DHT21_PIN 5
dht DHT;
Adafruit_BMP085 BMP085;
DS3231 RTClock;
bool hrs12;
bool hrsPM12;

/* AVR EEPROM R/W */
#include <avr/eeprom.h>
#define EEPROM_write(address, var) eeprom_write_block((const void *)&(var), (void *)(address), sizeof(var))
#define EEPROM_read(address, var) eeprom_read_block((void *)&(var), (const void *)(address), sizeof(var)) 

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
}




void loop(){
       
        /* Simplify the code in main Server.ino */
       SerialDataRead();  // Read the serial data first. :-)
       GetDustData();
       SerialWeatherOutput();
        
        /* Check if the time meets the schedule */
       RelaySchedule1();
       RelaySchedule2();
       RelaySchedule3();
       
}
