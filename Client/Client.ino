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
String YeelinkSensor6;
int SerialReadMark;
float SerialNumData[8] = {0};

LiquidCrystal_I2C lcd(0x27,20,4);  

void setup()
{
  lcd.init();                      // Initialize the lcd 
  lcd.init();
  EEPROM_read(0,WifiSSID);   // Read the Wifi SSID
  EEPROM_read(5,WifiPassword); // Read the Wifi Password
  DebugSerial.println("SHSS KGTCU IntelliPlant Client");
  DebugSerial.println("Now initalized.");
}


void loop()
{
    while (Serial.available() > 0)  
    {
        SerialIn += char(Serial.read());
        delay(2);
    }
    if (SerialIn.length() > 0)
    {
      YeelinkIDSave();
      YeelinkSensorSave1();
      YeelinkSensorSave2();
      YeelinkSensorSave3();
      YeelinkSensorSave4();
      YeelinkSensorSave5();
      YeelinkSensorSave6();
    }
}
