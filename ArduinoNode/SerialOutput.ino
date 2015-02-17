/* 
    SHSS KCloud IntelliPlant Server (master) source code
    Author: Jackson Ming Hu <huming2207@gmail.com>
            Technical Club Union of Shenzhen Highschool of Science
    ***THIS CODE IS PROTECTED BY GPLv2 LICENCE, FOR NON-COMMERCIAL USE ONLY! ***
    
    SerialOutput.ino --->> Send the status & settings data to client (slave) side via wireless UART transmitter.
                       
*/

void SerialWeatherOutput(){
  DHT.read();
  Serial.print("1,");
  Serial.print(GasPPM); 
  Serial.print(",");
  Serial.print(DHT.humidity / 10);
  Serial.print(",");
  Serial.print(DHT.temperature / 10);
  Serial.print(",");
  Serial.println(long(pressure)); // Here if we use float, it will comes up two more digits and one dot. It will use more serial brandwidth resource and maybe cause the unstability.
  delay(360); 
}

void SerialScheduleOutput(){
  Serial.print("2,");
  Serial.print(ScheduleHr); 
  Serial.print(",");
  Serial.print(ScheduleMin);
  Serial.print(",");
  Serial.print(ScheduleNum);
}

void SerialTimeDebug(){
  t = RTC.getTime();
  Serial.println("***DEBUG: TIMEMSG******");
  Serial.print("***");
  Serial.print(t.month());
  Serial.print("/");
  Serial.print(t.day());
  Serial.print("/");
  Serial.println(t.year());
  Serial.print("***");
  Serial.print(t.hour());
  Serial.print(":");
  Serial.print(t.minute());
  Serial.print(":");
  Serial.println(t.second());
  
}

void SerialGasDebug(){
  Serial.println("***DEBUG: GASMSG******");
  Serial.print("GASANG:");
  Serial.println((analogRead(A3)));
}
