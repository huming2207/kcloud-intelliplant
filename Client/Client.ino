#include <LiquidCrystal_I2C.h>
#include <uartWIFI.h>
#include <avr/eeprom.h>
#define EEPROM_write(address, var) eeprom_write_block((const void *)&(var), (void *)(address), sizeof(var))
#define EEPROM_read(address, var) eeprom_read_block((void *)&(var), (const void *)(address), sizeof(var)) 
String WifiSSID;                
String WifiPassword;                    

LiquidCrystal_I2C lcd(0x27,20,4);  

void setup()
{
  lcd.init();                      // Initialize the lcd 
  lcd.init();
  EEPROM_read(0,WifiSSID);   // Read the Wifi SSID
  EEPROM_read(5,WifiPassword); // Read the Wifi Password
}


void loop()
{
}
