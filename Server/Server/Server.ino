#include <EEPROM.h>
#include <DS3231.h>
#include <Wire.h>
#include <dht.h>
#include <Adafruit_BMP085.h>


#define DHT21_PIN 5
dht DHT;
Adafruit_BMP085 BMP085;
DS3231 RTClock;

int AirData = 0; // VOut from SHARP dust sensor
int AirLED = 2; // LED V-in to SHARP dust sensor
int PulseTime = 280; // Main pulse time
int WaitTime = 40; // Halt time 1
int WaitTime1 = 9680; //Halt time 2
float vM;
float FinalVoltage;
float FinalDustDesity;
String SerialIn;
int SerialReadMark;
int SerialNumData[8] = {0};

void setup(){
      Serial.begin(9600);
      pinMode(AirLED,OUTPUT);
}

void set_time(){
   Serial.print("RTC: Got a new RTC time, set it to DS3221...");
   Wire.begin();
   RTClock.setClockMode(false); // Set the RTC to "24-hour-per-day" format.
   RTClock.setSecond(SerialNumData[7]); 
   RTClock.setMinute(SerialNumData[6]); 
   RTClock.setHour(SerialNumData[5]);   
   RTClock.setDoW(SerialNumData[4]);    
   RTClock.setDate(SerialNumData[3]);   
   RTClock.setMonth(SerialNumData[2]);  
   RTClock.setYear(SerialNumData[1]); 
   Serial.println("...Command finished!");
}


void loop(){
     
	digitalWrite(AirLED,LOW); 
	delayMicroseconds(PulseTime); 
	vM = analogRead(AirData); 
	delayMicroseconds(WaitTime); 
	digitalWrite(AirLED,HIGH);
	delayMicroseconds(WaitTime1);
	FinalVoltage = vM * (5.0 / 1024.0); 
	FinalDustDesity = 0.17 * FinalVoltage - 0.1; 
        Serial.println("");
	Serial.print("D");
	Serial.println(FinalDustDesity); 
        delay(150);
        Serial.print("H");
        Serial.println(DHT.humidity, 1);
        delay(150);
        Serial.print("T");
        Serial.println(DHT.temperature, 1);
        delay(150);
        Serial.print("P");
        Serial.println(BMP085.readPressure(),1);
        delay(150);


        int j = 0;
        while (Serial.available() > 0)
        {
            SerialIn += char(Serial.read());
            delay(2);
            SerialReadMark = 1;
        }
        
       if(SerialReadMark == 1)  
       {
          Serial.println(SerialIn);             
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
        switch (SerialNumData[0]) {  
        case 1:
          set_time();
          break;
        case 2:
          
          break;
        default: 
          break;
        }
        
        for(int i = 0; i < 7; i++)
        {
   	    SerialNumData[i] = 0;
        }
        SerialReadMark = 0;
      }



}
