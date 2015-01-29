#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <uartWIFI.h>
#include <avr/eeprom.h>
#define EEPROM_write(address, var) eeprom_write_block((const void *)&(var), (void *)(address), sizeof(var))
#define EEPROM_read(address, var) eeprom_read_block((void *)&(var), (const void *)(address), sizeof(var)) 

String WifiSSID;                
String WifiPassword;    
String SerialIn;
String YeelinkID1;
String YeelinkSensor1;
String YeelinkSensor2;
String YeelinkSensor3;
String YeelinkSensor4;
String YeelinkSensor5;
String YeelinkDeviceID;
int SerialReadMark;
float SerialNumData[8] = {0};
unsigned long lastConnectionTime = 0;          // last time you connected to the server, in milliseconds
boolean lastConnected = false;                 // state of the connection last time through the main loop
const unsigned long postingInterval = 5*1000; 
String returnValue = ""; 
boolean ResponseBegin = false;

LiquidCrystal_I2C lcd(0x27,20,4);  
WIFI wifi;
char server[] = "api.yeelink.net";

void setup()
{
  lcd.init();                      // Initialize the lcd 
  lcd.init();
  lcd.backlight();
  EEPROM_read(0,WifiSSID);   // Read the Wifi SSID
  EEPROM_read(5,WifiPassword); // Read the Wifi Password
  EEPROM_read(50,YeelinkID1);
  EEPROM_read(60,YeelinkSensor1);
  EEPROM_read(62,YeelinkSensor2);
  EEPROM_read(64,YeelinkSensor3);
  EEPROM_read(66,YeelinkSensor4);
  EEPROM_read(68,YeelinkSensor5);
  EEPROM_read(70,YeelinkDeviceID);
  DebugSerial.println("SHSS KGTCU IntelliPlant Client");
  DebugSerial.println("Now initalized.");
  wifi.begin();
  bool b = wifi.Initialize(STA, WifiSSID, WifiPassword);
  if(!b)
  {
    DebugSerial.println("...Wifi hasn't connected successfully.");
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("Hello, world!");
      lcd.setCursor(1,1);
      lcd.print("KCloud IntelliPlant");
      lcd.setCursor(0,2);
      lcd.print("WIFI CONNECTION FAIL");
      delay(10000);
  }
  delay(10000);
  lcd.setCursor(3,0);
  lcd.print("Hello, world!");
  lcd.setCursor(2,1);
  lcd.print("KCloud IntelliPlant");
  lcd.setCursor(0,2);
  lcd.print("IP:");
  lcd.print(wifi.showIP());
  lcd.setCursor(0,3);
  lcd.print("Waiting for WIFI...");
  delay(2000);
  wifi.confMux(1);
  delay(100);
  if(wifi.confServer(1,8080))
  {
     lcd.clear();
     DebugSerial.println("Server is set up");
     lcd.setCursor(3,0);
     lcd.print("Hello, world!");
     lcd.setCursor(1,1);
     lcd.print("KCloud IntelliPlant");
     lcd.setCursor(2,2);
     lcd.print("WIFI CONNECTED!!");
     delay(3000);
  }
  
}


void loop()
{
    int j = 0;
    while (Serial.available() > 0)  
    {
        SerialIn += char(Serial.read());
        delay(2);
    }
    if (SerialIn.length() > 0)
    {
      if(SerialIn[0] == 'Y' || SerialIn[0] == 'F' || SerialIn[0] == 'A' || SerialIn[0] == 'B' || SerialIn[0] == 'C' || SerialIn[0] == 'D' || SerialIn[0] == 'E')
      {
       YeelinkDeviceIDSave();
       YeelinkIDSave();
       YeelinkSensorSave1();
       YeelinkSensorSave2();
       YeelinkSensorSave3();
       YeelinkSensorSave4();
       YeelinkSensorSave5();
      }
      else
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
           1 = Normal weather data.
           2 = Backup & debug data.
          ******************************************************************************** */ 
        switch (int(SerialNumData[0])) {  
        case 1:
          
          if((millis() - lastConnectionTime > postingInterval)) {
             sendData(YeelinkDeviceID, YeelinkID1, YeelinkSensor1,SerialNumData[1]);
             sendData(YeelinkDeviceID, YeelinkID1, YeelinkSensor2,SerialNumData[2]);
             sendData(YeelinkDeviceID, YeelinkID1, YeelinkSensor3,SerialNumData[3]);
             sendData(YeelinkDeviceID, YeelinkID1, YeelinkSensor4,SerialNumData[4]);
             sendData(YeelinkDeviceID, YeelinkID1, YeelinkSensor5,SerialNumData[5]);
             char message[400];
             if(wifi.ReceiveMessage(message)) 
             {
                DebugSerial.println(message);   
             }
           }
          break;
        default: 
          break;
        }
        
        for(int i = 0; i < 7; i++)
        {
   	    SerialNumData[i] = 0;
        }
      }
    }



    
}
