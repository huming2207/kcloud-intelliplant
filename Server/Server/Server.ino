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
int RelayControl = 10;

int ScheduleHr;
int ScheduleMin;
int ScheduleSec;
int ScheduleCapacity;
int ScheduleStatus;

int Sec1;
int Sec2;
int Sec3;
int Min1;
int Min2;
int Min3;
int Hr1;
int Hr2;
int Hr3;

int TempRatio;
int HumidRatio;
int PressureRatio;
int DustRatio;

int XWeatherOut;
int YWeatherOut;
int AutoSwitch;

void setup(){
      Serial.begin(9600);
      pinMode(AirLED,OUTPUT);
      pinMode(RelayControl,OUTPUT);
      RTClock.setClockMode(false);
}




void loop(){
        RTClock.setClockMode(false);
	digitalWrite(AirLED,LOW); 
	delayMicroseconds(PulseTime); 
	vM = analogRead(AirData); 
	delayMicroseconds(WaitTime); 
	digitalWrite(AirLED,HIGH);
	delayMicroseconds(WaitTime1);
	FinalVoltage = vM * (5.0 / 1024.0); 
	FinalDustDesity = 0.17 * FinalVoltage - 0.1; 
	Serial.print("1,");
	Serial.print(FinalDustDesity); 
        Serial.print(",");
        Serial.print(DHT.humidity);
        Serial.print(",");
        Serial.print(DHT.temperature);
        Serial.print(",");
        Serial.println(BMP085.readPressure());
        delay(300);
        
        /* Check if the time meets the schedule */
        RelaySchedule1();
       RelaySchedule2();
        RelaySchedule3();
        
        int j = 0;
        while (Serial.available() > 0)
        {
            SerialIn += char(Serial.read());
            delay(2);
        }
        
       if(SerialIn.length() > 0)  
       {       
          for(unsigned int i = 0; i < SerialIn.length() ; i++)
          {
            if(SerialIn[i] == ',')
            {
               j++;
            }
            else
            {
               SerialNumData[j] = SerialNumData[j] * 10 + (SerialIn[i] - '0');
            }
          }

        SerialIn = String("");
        /* *******************************************************************************
           The "SerialNumData[0]" lets the server decide which setting should be changed. 
           1 = Set the RTC time 
           2 = Set schedule time #1 
           3 = Set schedule time #2
           4 = Set schedule time #3
           5 = Set schedule time #4
           6 = Set schedule time #5
           7 = Set schedule time #6
           8 = Debug mode ON/OFF
           9 = Force relay ON/OFF
          ******************************************************************************** */ 
        switch (int(SerialNumData[0])) {  
        case 1:
          set_time();
          break;
        case 2:
          set_relay_1();
          break;
        case 3:
          set_relay_2();
          break;
        case 4:
          set_weather_ratio();
          break;
        case 5:
          if (SerialNumData[1] > 0)
          {
              digitalWrite(RelayControl,HIGH); 
          }
          else
          {
              digitalWrite(RelayControl,LOW); 
          }
        default: 
          break;
        }
        
        for(int i = 0; i < 7; i++)
        {
   	    SerialNumData[i] = 0;
        }
      }



}
