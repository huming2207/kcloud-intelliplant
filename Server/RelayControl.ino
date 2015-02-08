/* 
    SHSS KCloud IntelliPlant Server (master) source code
    Author: Jackson Ming Hu <huming2207@gmail.com>
            Technical Club Union of Shenzhen Highschool of Science
    ***THIS CODE IS PROTECTED BY GPLv2 LICENCE, FOR NON-COMMERCIAL USE ONLY! ***
    
    RelayControl.ino -->> Pump relay controller & weather condition to pump water capacity calculation.
                       
*/

void CalculateWeather(){
  /* 
     This is a testing formula of the "Weather2WaterCapacity" part.
     It's too humble, but I will keep working on it. ----Jackson @ Jan 30 2015
     
     Some requirements:
     1. The pump must work longer than 10 seconds per schedule and less than 60 seconds per schedule.
     2. ... (To be continued. I will ask my mum and grandma some advices, who is expert in agriculture.)
   */
   DHT.read();
  XWeatherOut = (FinalDustDesity/DustRatio) + (DHT.humidity/HumidRatio) + (DHT.temperature/TempRatio) + (pressure/PressureRatio);
  YWeatherOut = -XWeatherOut + 60;
  if (YWeatherOut > 60){
    YWeatherOut = 60; // Force the output shorter than 60.
  }
  if (YWeatherOut < 10){
    YWeatherOut = 10; // Force the output longer than 60.
  }
}


/* BEGIN PUMP RELAY SCHEDULE PARTS */

void RelaySchedule1(){
  EEPROM_read(1, ScheduleHr);
  EEPROM_read(2, ScheduleMin);
  EEPROM_read(3, ScheduleSec);
  EEPROM_read(4, ScheduleCapacity);
  EEPROM_read(5, MainSwitch);
  EEPROM_read(6, AutoSwitch);
  
  if(MainSwitch == 1)
  {
  if(ScheduleHr == RTClock.getHour(hrs12,hrsPM12) && ScheduleMin == RTClock.getMinute())
  {
    if (AutoSwitch == 1)
    {
      Sec1 = RTClock.getSecond() + YWeatherOut;
      if (Sec1 > 59)
      {
        Min1++;
        Sec1 = 0;
        if((Min1 + ScheduleMin) > 59)
        {
          Min1 = 0;
          Hr1++;
          if((Hr1 + ScheduleHr) > 23)
          {
            ScheduleHr = 22; // I know here is a bug, but it does work as a place holder... I will fix it later.
          }
        }
      }
      digitalWrite(RelayControl,HIGH); 
      ScheduleNum = 1;
      SerialScheduleOutput();
      if (Sec1 == RTClock.getSecond()) // When it meets the time, then turn the pump off.
      {
        digitalWrite(RelayControl,LOW);
      }
    }
    else
    {
      digitalWrite(RelayControl,HIGH);
      ScheduleNum = 1;
      SerialScheduleOutput();
      if (RTClock.getSecond() == (ScheduleCapacity + ScheduleSec))
      {
        digitalWrite(RelayControl,LOW);
      }
    }
  }
  else
  {
    digitalWrite(RelayControl,LOW); 
  }
  }
  else
  {
    digitalWrite(RelayControl,LOW);
  }
}





void RelaySchedule2(){
  EEPROM_read(7, ScheduleHr);
  EEPROM_read(8, ScheduleMin);
  EEPROM_read(9, ScheduleSec);
  EEPROM_read(10, ScheduleCapacity);
  EEPROM_read(11, MainSwitch);
  EEPROM_read(12, AutoSwitch);
  if(MainSwitch == 1)
  {
  if(ScheduleHr == RTClock.getHour(hrs12,hrsPM12) && ScheduleMin == RTClock.getMinute())
  {
    if (AutoSwitch == 1)
    {
      Sec1 = RTClock.getSecond() + YWeatherOut;
      if (Sec1 > 59)
      {
        Min1++;
        Sec1 = 0;
        if((Min1 + ScheduleMin) > 59)
        {
          Min1 = 0;
          Hr1++;
          if((Hr1 + ScheduleHr) > 23)
          {
            ScheduleHr = 22; // I know here is a bug, but it does work as a place holder... I will fix it later.
          }
        }
      }
      digitalWrite(RelayControl,HIGH); 
      ScheduleNum = 2;
      SerialScheduleOutput();
      if (Sec1 == RTClock.getSecond()) // When it meets the time, then turn the pump off.
      {
        digitalWrite(RelayControl,LOW);
      }
    }
    else
    {
      digitalWrite(RelayControl,HIGH);
      ScheduleNum = 2;
      SerialScheduleOutput();
      if (RTClock.getSecond() == (ScheduleCapacity + ScheduleSec))
      {
        digitalWrite(RelayControl,LOW);
      }
    }
  }
  else
  {
    digitalWrite(RelayControl,LOW); 
  }
  }
  else
  {
    digitalWrite(RelayControl,LOW);
  }
}





void RelaySchedule3(){
  EEPROM_read(13, ScheduleHr);
  EEPROM_read(14, ScheduleMin);
  EEPROM_read(15, ScheduleSec);
  EEPROM_read(16, ScheduleCapacity);
  EEPROM_read(17, MainSwitch);
  EEPROM_read(18, AutoSwitch);
  if(MainSwitch == 1)
  {
  if(ScheduleHr == RTClock.getHour(hrs12,hrsPM12) && ScheduleMin == RTClock.getMinute())
  {
    if (AutoSwitch == 1)
    {
      Sec1 = RTClock.getSecond() + YWeatherOut;
      if (Sec1 > 59)
      {
        Min1++;
        Sec1 = 0;
        if((Min1 + ScheduleMin) > 59)
        {
          Min1 = 0;
          Hr1++;
          if((Hr1 + ScheduleHr) > 23)
          {
            ScheduleHr = 22; // I know here is a bug, but it does work as a place holder... I will fix it later.
          }
        }
      }
      digitalWrite(RelayControl,HIGH); 
      ScheduleNum = 3;
      SerialScheduleOutput();
      if (Sec1 == RTClock.getSecond()) // When it meets the time, then turn the pump off.
      {
        digitalWrite(RelayControl,LOW);
      }
    }
    else
    {
      digitalWrite(RelayControl,HIGH);
      ScheduleNum = 3;
      SerialScheduleOutput();
      if (RTClock.getSecond() == (ScheduleCapacity + ScheduleSec))
      {
        digitalWrite(RelayControl,LOW);
      }
    }
  }
  else
  {
    digitalWrite(RelayControl,LOW); 
  }
  }
  else
  {
    digitalWrite(RelayControl,LOW); 
  }
}




