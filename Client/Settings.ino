void YeelinkIDSave()
{
      if (SerialIn[0] == 'Y')
      {
        
        DebugSerial.println("New Yeelink ID has been received.");
        DebugSerial.print("The new ID is:");
        DebugSerial.println(SerialIn);
          for(unsigned int i = 1; i <= SerialIn.length() ; i++)
          {
               YeelinkID1 += SerialIn[i];  //Put the SerialIn data to YeelinkID without the identify word "Y"
          }
       EEPROM_write(50,YeelinkID1);
       DebugSerial.println("New Yeelink ID has been successfully saved");
      }
}

void YeelinkSensorSave1()
{
      if (SerialIn[0] == 'A')
      {
        
        DebugSerial.println("New Yeelink Sensor ID has been received.");
        DebugSerial.print("The new ID is:");
        DebugSerial.println(SerialIn);
          for(unsigned int i = 1; i <= SerialIn.length() ; i++)
          {
               YeelinkSensor1 += SerialIn[i];  //Put the SerialIn data to YeelinkID without the identify word "A"
          }
       EEPROM_write(60,YeelinkSensor1);
       DebugSerial.println("New Yeelink Sensor ID has been successfully saved");
      }
}

void YeelinkSensorSave2()
{
      if (SerialIn[0] == 'B')
      {
        
        DebugSerial.println("New Yeelink sensor ID has been received.");
        DebugSerial.print("The new ID is:");
        DebugSerial.println(SerialIn);
          for(unsigned int i = 1; i <= SerialIn.length() ; i++)
          {
               YeelinkSensor2 += SerialIn[i];  //Put the SerialIn data to YeelinkID without the identify word "B"
          }
       EEPROM_write(62,YeelinkSensor2);
       DebugSerial.println("New Yeelink sensor ID has been successfully saved");
      }
}

void YeelinkSensorSave3()
{
      if (SerialIn[0] == 'C')
      {
        
        DebugSerial.println("New Yeelink sensor ID has been received.");
        DebugSerial.print("The new ID is:");
        DebugSerial.println(SerialIn);
          for(unsigned int i = 1; i <= SerialIn.length() ; i++)
          {
               YeelinkSensor3 += SerialIn[i];  //Put the SerialIn data to YeelinkID without the identify word "C"
          }
       EEPROM_write(64,YeelinkSensor3);
       DebugSerial.println("New Yeelink sensor ID has been successfully saved");
      }
}

void YeelinkSensorSave4()
{
      if (SerialIn[0] == 'D')
      {
        
        DebugSerial.println("New Yeelink sensor ID has been received.");
        DebugSerial.print("The new ID is:");
        DebugSerial.println(SerialIn);
          for(unsigned int i = 1; i <= SerialIn.length() ; i++)
          {
               YeelinkSensor4 += SerialIn[i];  //Put the SerialIn data to YeelinkID without the identify word "D"
          }
       EEPROM_write(66,YeelinkSensor4);
       DebugSerial.println("New Yeelink sensor ID has been successfully saved");
      }
}

void YeelinkSensorSave5()
{
      if (SerialIn[0] == 'E')
      {
        
        DebugSerial.println("New Yeelink sensor ID has been received.");
        DebugSerial.print("The new ID is:");
        DebugSerial.println(SerialIn);
          for(unsigned int i = 1; i <= SerialIn.length() ; i++)
          {
               YeelinkSensor5 += SerialIn[i];  //Put the SerialIn data to YeelinkID without the identify word "E"
          }
       EEPROM_write(68,YeelinkSensor5);
       DebugSerial.println("New Yeelink sensor ID has been successfully saved");
      }
}

void YeelinkDeviceIDSave()
{
      if (SerialIn[0] == 'F')
      {
        
        DebugSerial.println("New Yeelink Self-device ID has been received.");
        DebugSerial.print("The new ID is:");
        DebugSerial.println(SerialIn);
          for(unsigned int i = 1; i <= SerialIn.length() ; i++)
          {
               YeelinkDeviceID += SerialIn[i];  //Put the SerialIn data to YeelinkID without the identify word "F"
          }
       EEPROM_write(70,YeelinkDeviceID);
       DebugSerial.println("New Yeelink device ID has been successfully saved");
      }
}


