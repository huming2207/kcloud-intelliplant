/* 
    SHSS KCloud IntelliPlant Server (master) source code
    Author: Jackson Ming Hu <huming2207@gmail.com>
            Technical Club Union of Shenzhen Highschool of Science
    ***THIS CODE IS PROTECTED BY GPLv2 LICENCE, FOR NON-COMMERCIAL USE ONLY! ***
    
    SerialInput.ino --->> Read the UART serial input settings' data.
                       
*/

void SerialDataRead(){
        int j = 0;
        while (Serial.available() > 0)
        {
            SerialIn += char(Serial.read());
            delay(2); // It does have a delay longer than 2ms, otherwise it will lose some data.
        }
        
       if(SerialIn.length() > 0)  
       {       
          for(unsigned int i = 0; i < SerialIn.length() ; i++)
          {
            if(SerialIn[i] == ',')  // If it meets a comma, then j+1, jumps to the next setting data.
            {
               j++;
            }
            else
            {
               SerialNumData[j] = SerialNumData[j] * 10 + (SerialIn[i] - '0');
            }
          }

        SerialIn = String(""); // Clear up all the old things in SerialIn
        
        /* *******************************************************************************
           The "SerialNumData[0]" lets the server decide which setting should be changed. 
           1 = Set the RTC time 
           2 = Set schedule time #1 
           3 = Set schedule time #2
           4 = Set schedule time #3
           5 = Force relay ON/OFF
           6 = Debug message
           7 = Set weather2water ratio
           8 = Debug mode ON/OFF
           9 = Force relay ON/OFF
          ******************************************************************************** */ 
        switch (int(SerialNumData[0])) {  
        case 1:
          set_time();
          break;
        case 2:
          set_relay_1();
          break;
        case 3:
          set_relay_2();
          break;
        case 4:
          set_relay_3();
          break;
        case 5:
          if (SerialNumData[1] > 0)
          {
              digitalWrite(RelayControl,HIGH); 
          }
          else
          {
              digitalWrite(RelayControl,LOW); 
          }
          break;
        case 6:
          SerialTimeDebug();
          EEPROMDebug();
           SerialGasDebug();
          break;
        case 7:
          set_weather_ratio();
          break;
        default: 
          break;
        }
        
        for(int i = 0; i < 10; i++)
        {
   	    SerialNumData[i] = 0;  // Clear up all the data in SerialNumData
        }
      }

}
