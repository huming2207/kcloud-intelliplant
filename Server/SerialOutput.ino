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
  Serial.print(ratio); 
  Serial.print(",");
  Serial.print(DHT.humidity / 10);
  Serial.print(",");
  Serial.print(DHT.temperature / 10);
  Serial.print(",");
  Serial.println(long(pressure)); // Here if we use float, it will comes up two more digits and one dot. It will use more serial brandwidth resource and maybe cause the unstability.
  delay(60); 
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
  Serial.println("***DEBUG: TIMEMSG******");
  Serial.print("***");
  Serial.print(month());
  Serial.print("/");
  Serial.print(day());
  Serial.print("/");
  Serial.println(year());
  Serial.print("***");
  Serial.print(hour());
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.println(second());
  
}
