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

void set_relay_4(){
  EEPROM_write(19, SerialNumData[1]); // Hr
  EEPROM_write(20, SerialNumData[2]); // Min
  EEPROM_write(21, SerialNumData[3]); // Sec
  EEPROM_write(22, SerialNumData[4]); // Capacity lasts 
  EEPROM_write(23, SerialNumData[5]); // ON/OFF
  EEPROM_write(24, SerialNumData[6]); // Auto ON/OFF
}

void set_relay_5(){
  EEPROM_write(25, SerialNumData[1]); // Hr
  EEPROM_write(26, SerialNumData[2]); // Min
  EEPROM_write(27, SerialNumData[3]); // Sec
  EEPROM_write(28, SerialNumData[4]); // Capacity lasts 
  EEPROM_write(29, SerialNumData[5]); // ON/OFF
  EEPROM_write(30, SerialNumData[6]); // Auto ON/OFF
}

void set_relay_6(){
  EEPROM_write(31, SerialNumData[1]); // Hr
  EEPROM_write(32, SerialNumData[2]); // Min
  EEPROM_write(33, SerialNumData[3]); // Sec
  EEPROM_write(34, SerialNumData[4]); // Capacity lasts 
  EEPROM_write(35, SerialNumData[5]); // ON/OFF
  EEPROM_write(36, SerialNumData[6]); // Auto ON/OFF
}

void set_debug_mode(){
  EEPROM_write(37, SerialNumData[1]); // 1 == Debug mode ON, 0 == Debug mode OFF.
}

