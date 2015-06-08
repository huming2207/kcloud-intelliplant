/* 
    SHSS KCloud IntelliPlant Node source code
    Author: Jackson Ming Hu <huming2207@gmail.com>
            Technical Club Union of Shenzhen Highschool of Science
            ...and some unknown guys including the TAOBAO retailers, thanks them!!
			深圳科学高中 科高云子项目 智慧农业物联网灌溉机
			深圳科学高中技术类社团联合会自动化电子项目组
			程序作者：胡铭 huming2207@gmail.com
			
    ***THIS CODE IS PROTECTED BY LGPL LICENCE, FOR NON-COMMERCIAL USE ONLY! ***
        本程序受LGPL协议保护，严禁商用。
     
     RelayControl.ino -->   Relay timing controller 
                            
                       
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
  Ratio = int(EEPROM.read(20));
  XWeatherOut = (int((DHT.humidity/2)) - int((DHT.temperature/1.5)) - int((pressure/5000)));
  YWeatherOut = -XWeatherOut + 60 + Ratio;
  if (YWeatherOut > 60){
    YWeatherOut = 60; // Force the output shorter than 60.
  }
  if (YWeatherOut < 10){
    YWeatherOut = 10; // Force the output longer than 60.
  }
}


/* 
     BEGIN PUMP RELAY SCHEDULE PARTS 
     
     Feb 11 2015: I have no choice but to use delay(), since it is the easiest and the most stable way to control the interruption of the pump without Time library.
     
*/

void RelaySchedule1(){
  t = RTC.getTime();
  ScheduleHr = int(EEPROM.read(1));
  ScheduleMin = int(EEPROM.read(2));
  ScheduleSec = int(EEPROM.read(3));
  ScheduleCapacity = int(EEPROM.read(4));
  MainSwitch = int(EEPROM.read(5));
  AutoSwitch = int(EEPROM.read(6));
  
  
  if (MainSwitch == 1 && ScheduleHr == t.hour() && ScheduleMin == t.minute() && ScheduleSec == t.second())
  {
    digitalWrite(RelayControl, HIGH);
    if (AutoSwitch == 1)
    {
        SerialScheduleOutput();
        delay(YWeatherOut * 1000L);
        digitalWrite(RelayControl,LOW);
        //BoardReset();
    }
    else
    {
        SerialScheduleOutput();
        delay(ScheduleCapacity * 1000L);
        digitalWrite(RelayControl,LOW);
        //BoardReset();
    }
  }
}


void RelaySchedule2(){
  t = RTC.getTime();
  ScheduleHr = int(EEPROM.read(7));
  ScheduleMin = int(EEPROM.read(8));
  ScheduleSec = int(EEPROM.read(9));
  ScheduleCapacity = int(EEPROM.read(10));
  MainSwitch = int(EEPROM.read(11));
  AutoSwitch = int(EEPROM.read(12));
  
  
  if (MainSwitch == 1 && ScheduleHr == t.hour() && ScheduleMin == t.minute() && ScheduleSec == t.second())
  {
    digitalWrite(RelayControl, HIGH);
    if (AutoSwitch == 1)
    {
        SerialScheduleOutput();
        delay(YWeatherOut * 1000L);
        digitalWrite(RelayControl,LOW);
        //BoardReset();
    }
    else
    {
        SerialScheduleOutput();
        delay(ScheduleCapacity * 1000L);
        digitalWrite(RelayControl,LOW);
        //BoardReset();
    }
  }
}

void RelaySchedule3(){
  t = RTC.getTime();
  ScheduleHr = int(EEPROM.read(13));
  ScheduleMin = int(EEPROM.read(14));
  ScheduleSec = int(EEPROM.read(15));
  ScheduleCapacity = int(EEPROM.read(16));
  MainSwitch = int(EEPROM.read(17));
  AutoSwitch = int(EEPROM.read(18));
  
  
  if (MainSwitch == 1 && ScheduleHr == t.hour() && ScheduleMin == t.minute() && ScheduleSec == t.second())
  {
    digitalWrite(RelayControl, HIGH);
    if (AutoSwitch == 1)
    {
        SerialScheduleOutput();
        delay(YWeatherOut * 1000L);
        digitalWrite(RelayControl,LOW);
        //BoardReset();
    }
    else
    {
        SerialScheduleOutput();
        delay(ScheduleCapacity * 1000);
        digitalWrite(RelayControl,LOW);
        //BoardReset();
    }
  }
}




void EEPROMDebug(){
  ScheduleHr = int(EEPROM.read(1));
  ScheduleMin = int(EEPROM.read(2));
  ScheduleSec = int(EEPROM.read(3));
  ScheduleCapacity = int(EEPROM.read(4));
  MainSwitch = int(EEPROM.read(5));
  AutoSwitch = int(EEPROM.read(6));
  Serial.println("** DEBUG: EEPROM - SCHEDULE");
  Serial.print("** ");
  Serial.print(ScheduleHr);
  Serial.print("  ");
  Serial.print(ScheduleMin);
  Serial.print("  ");
  Serial.print(ScheduleSec);
  Serial.print("  ");
  Serial.print(ScheduleCapacity);
  Serial.print("  ");
  Serial.println(MainSwitch);
}  

