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
  EEPROM_write(5, SerialNumData[2]); // Min
  EEPROM_write(10, SerialNumData[3]); // Sec
  EEPROM_write(15, SerialNumData[4]); // Capacity lasts 
  EEPROM_write(20, SerialNumData[5]); // ON/OFF
  EEPROM_write(25, SerialNumData[6]); // Auto ON/OFF
}

void set_relay_2(){
  EEPROM_write(30, SerialNumData[1]); // Hr
  EEPROM_write(35, SerialNumData[2]); // Min
  EEPROM_write(40, SerialNumData[3]); // Sec
  EEPROM_write(45, SerialNumData[4]); // Capacity lasts 
  EEPROM_write(50, SerialNumData[5]); // ON/OFF
  EEPROM_write(55, SerialNumData[6]); // Auto ON/OFF
}

void set_relay_3(){
  EEPROM_write(60, SerialNumData[1]); // Hr
  EEPROM_write(65, SerialNumData[2]); // Min
  EEPROM_write(70, SerialNumData[3]); // Sec
  EEPROM_write(75, SerialNumData[4]); // Capacity lasts 
  EEPROM_write(80, SerialNumData[5]); // ON/OFF
  EEPROM_write(85, SerialNumData[6]); // Auto ON/OFF
}

void set_weather_ratio(){
  EEPROM_write(90, SerialNumData[1]); // Temperature ratio
  EEPROM_write(120, SerialNumData[2]); // Humidity ratio
  EEPROM_write(170, SerialNumData[3]); // Air dust ratio
  EEPROM_write(220, SerialNumData[4]); // Air pressure ratio
}

