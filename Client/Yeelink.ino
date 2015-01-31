void sendData(String device_id, String api_id, String sensor_id,float sensor_data) {
  // if there's a successful connection:
  if (wifi.ipConfig(TCP,server, 80)) {
    DebugSerial.println("Connecting to Yeelink...");
    // send the HTTP PUT request:
    String cmd;
        cmd = "POST /v1.0/device/";
        cmd += device_id;
        cmd += "/sensor/";
        cmd += sensor_id;
        cmd += "/datapoints";
        cmd += " HTTP/1.1\r\n";
        cmd += "Host: api.yeelink.net\r\n";
        cmd += "Accept: *";
        cmd += "/";
        cmd += "*\r\n";
        cmd += "U-ApiKey: ";
        cmd += api_id;
        cmd += "\r\n";
        cmd += "Content-Length: ";
        int thisLength = 10 + getLength(sensor_data);
        cmd += String(thisLength);
        cmd += "\r\n";
        cmd += "Content-Type: application/x-www-form-urlencoded\r\n";
        cmd += "Connection: close\r\n";
        cmd += "\r\n";
        cmd += "{\"value\":";
        cmd += String(sensor_data);
        cmd += "}\r\n";
  
  
        DebugSerial.println(cmd);
  
    wifi.Send(cmd);
    // note the time that the connection was made:
    lastConnectionTime = millis();
  } 
  else {
    // if you couldn't make a connection:
    DebugSerial.println("...Yeelink connection failed. Disconnected, try again.");
    wifi.closeMux();
    WifiStatus = 2;
  }
}
  
int getLength(int someValue) {
  // there's at least one byte:
  int digits = 1;
  // continually divide the value by ten, 
  // adding one to the digit count for each
  // time you divide, until you're at 0:
  int dividend = someValue /10;
  while (dividend > 0) {
    dividend = dividend /10;
    digits++;
  }
  // return the number of digits:
  return digits;
}


void YeeLinkSendSensorData(){
     if((millis() - lastConnectionTime > postingInterval)) {
        sendData(YeelinkDeviceID, YeelinkID1, YeelinkSensor1,SerialNumData[1]);
        sendData(YeelinkDeviceID, YeelinkID1, YeelinkSensor2,SerialNumData[2]);
        sendData(YeelinkDeviceID, YeelinkID1, YeelinkSensor3,SerialNumData[3]);
        sendData(YeelinkDeviceID, YeelinkID1, YeelinkSensor4,SerialNumData[4]);
        sendData(YeelinkDeviceID, YeelinkID1, YeelinkSensor5,SerialNumData[5]);
        char message[400];
        if(wifi.ReceiveMessage(message)) 
        {
          DebugSerial.println(message);   
        }
     }
}
