/* 
    SHSS KCloud IntelliPlant Server (master) source code
    Author: Jackson Ming Hu <huming2207@gmail.com>
            Technical Club Union of Shenzhen Highschool of Science
    ***THIS CODE IS PROTECTED BY GPLv2 LICENCE, FOR NON-COMMERCIAL USE ONLY! ***
    
    Settings.ino --->> Write settings to EEPROM or IIC devices
                       
*/

void set_time(){
   RTC.init();
   Time t(SerialNumData[1],SerialNumData[2],SerialNumData[3],SerialNumData[4],SerialNumData[5],SerialNumData[6],SerialNumData[7]);  //Yr,Mon,Day,Hr,Min,Sec,DayOfWeek
   RTC.setTime(t);
   t = RTC.getTime();
   Serial.println("**DEBUG: RTC SET CMD SUCCESS**");
   Serial.print("**NOW NEW RTC TIME IS:");
   Serial.print(t.year());
   Serial.print("/");
   Serial.print(t.month());
   Serial.print("/");
   Serial.println(t.date());
   Serial.print("**");
   Serial.print(t.hour());
   Serial.print(":");
   Serial.print(t.minute());
   Serial.print(":");
   Serial.println(t.second());
   Serial.println("**DEBUG DATA ENDED***");
}

void set_relay_1(){
  EEPROM.write(1, byte(SerialNumData[1])); // Hr
  EEPROM.write(2, byte(SerialNumData[2])); // Min
  EEPROM.write(3, byte(SerialNumData[3])); // Sec
  EEPROM.write(4, byte(SerialNumData[4])); // Capacity lasts 
  EEPROM.write(5, byte(SerialNumData[5])); // ON/OFF
  EEPROM.write(6, byte(SerialNumData[6])); // Auto ON/OFF
}

void set_relay_2(){
  EEPROM.write(7, byte(SerialNumData[1])); // Hr
  EEPROM.write(8, byte(SerialNumData[2])); // Min
  EEPROM.write(9, byte(SerialNumData[3])); // Sec
  EEPROM.write(10, byte(SerialNumData[4])); // Capacity lasts 
  EEPROM.write(11, byte(SerialNumData[5])); // ON/OFF
  EEPROM.write(12, byte(SerialNumData[6])); // Auto ON/OFF
}

void set_relay_3(){
  EEPROM.write(13, byte(SerialNumData[1])); // Hr
  EEPROM.write(14, byte(SerialNumData[2])); // Min
  EEPROM.write(15, byte(SerialNumData[3])); // Sec
  EEPROM.write(16, byte(SerialNumData[4])); // Capacity lasts 
  EEPROM.write(17, byte(SerialNumData[5])); // ON/OFF
  EEPROM.write(18, byte(SerialNumData[6])); // Auto ON/OFF
}

void set_weather_ratio(){
  EEPROM.write(20, byte(SerialNumData[1])); // Temperature ratio
  EEPROM.write(21, byte(SerialNumData[2])); // Humidity ratio
  EEPROM.write(22, byte(SerialNumData[3])); // Solar ratio
  EEPROM.write(23, byte(SerialNumData[4])); // Air pressure ratio
}

