/* 
    SHSS KCloud IntelliPlant Server (master) source code
    Author: Jackson Ming Hu <huming2207@gmail.com>
            Technical Club Union of Shenzhen Highschool of Science
    ***THIS CODE IS PROTECTED BY GPLv2 LICENCE, FOR NON-COMMERCIAL USE ONLY! ***
    
    Settings.ino --->> Write settings to EEPROM or IIC devices
                       
*/

void set_time(){
   RTC.init();
        /* 参数格式: 年, 月, 日, 时, 分, 秒, 星期 */
   Time t(SerialNumData[1],SerialNumData[2],SerialNumData[3],SerialNumData[4],SerialNumData[5],SerialNumData[6],SerialNumData[7]);
   RTC.setTime(t);
   t = RTC.getTime();
   Serial.println("**DEBUG: RTC CMD SUCCESS**");
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
  EEPROM_write(1, SerialNumData[1]); // Hr
  EEPROM_write(2, SerialNumData[2]); // Min
  EEPROM_write(3, SerialNumData[3]); // Sec
  EEPROM_write(4, SerialNumData[4]); // Capacity lasts 
  EEPROM_write(5, SerialNumData[5]); // ON/OFF
  EEPROM_write(6, SerialNumData[6]); // Auto ON/OFF
}

void set_relay_2(){
  EEPROM_write(7, SerialNumData[1]); // Hr
  EEPROM_write(8, SerialNumData[2]); // Min
  EEPROM_write(9, SerialNumData[3]); // Sec
  EEPROM_write(10, SerialNumData[4]); // Capacity lasts 
  EEPROM_write(11, SerialNumData[5]); // ON/OFF
  EEPROM_write(12, SerialNumData[6]); // Auto ON/OFF
}

void set_relay_3(){
  EEPROM_write(13, SerialNumData[1]); // Hr
  EEPROM_write(14, SerialNumData[2]); // Min
  EEPROM_write(15, SerialNumData[3]); // Sec
  EEPROM_write(16, SerialNumData[4]); // Capacity lasts 
  EEPROM_write(17, SerialNumData[5]); // ON/OFF
  EEPROM_write(18, SerialNumData[6]); // Auto ON/OFF
}

void set_weather_ratio(){
  EEPROM_write(20, SerialNumData[1]); // Temperature ratio
  EEPROM_write(21, SerialNumData[1]); // Humidity ratio
  EEPROM_write(22, SerialNumData[1]); // Air dust ratio
  EEPROM_write(23, SerialNumData[1]); // Air pressure ratio
}

