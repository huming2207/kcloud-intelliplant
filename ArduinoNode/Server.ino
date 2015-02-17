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

/* MQ135 toxic gas sensor */
float GasPPM;
float GasAlg;

/* Serial input statements */
String SerialIn;
float SerialNumData[9] = {0};

/* Relay control pin on D7 */
int RelayControl = 8;

/* Declare some schedule integers */
int ScheduleHr;
int ScheduleMin;
int ScheduleSec;
unsigned long ScheduleCapacity;
int ScheduleStatus;
int ScheduleNum;
int Sec1;
int Min1;
int Hr1;
int Ratio;
long XWeatherOut;
unsigned long YWeatherOut;
int AutoSwitch;
int MainSwitch = 0;

/* SolarMonitor statements */
int SolarVoltageAnalog = 0; // The solar voltage analog data from Analog Pin 0 (A0)
int SolarCurrentAnalog = 1; // The solar current analog data from Analog Pin 1 (A1)
float SolarVoltage;
float SolarCurrent;


void setup(){
      digitalWrite(7, HIGH)
      pinMode(7, OUTPUT)
      Serial.begin(9600);
      pinMode(RelayControl,OUTPUT);
      digitalWrite(RelayControl,LOW);
      bmp085Calibration();
      t = RTC.getTime();
}




void loop(){
      GasAlg = float(analogRead(A3));
      GasPPM = (GasAlg / 1023.00) * float(InputVcc()) * 0.25;
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

void BoardReset(){
  /* 
      Use a very short watchdog loop to force reset the arduino
      See also: http://www.atmel.com/images/Atmel-8271-8-bit-AVR-Microcontroller-ATmega48A-48PA-88A-88PA-168A-168PA-328-328P_datasheet_Complete.pdf
                http://playground.arduino.cc/Main/ArduinoReset
       But, unfortunately some Chinese Arduino ProMini clones (including mine)  have some issues on bootloader, so if we use the AVR internal watchdog, it would get stuck when reboot
       See also :http://arduino.stackexchange.com/questions/2922/watchdog-timer-stuck-in-restart-loop-green-led-flashing
            
  */
  
  /* 
      Here, we can connect a wire between pin D7 and pin DTR (reset)
      According to my experiments, a pull-up resistor is unnecessary.
  */    
  digitalWrite(7, LOW)

}
