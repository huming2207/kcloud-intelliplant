void GetDustData(){
  
  RTClock.setClockMode(false);
  digitalWrite(AirLED,LOW); 
  delayMicroseconds(PulseTime); 
  vM = analogRead(AirData); 
  delayMicroseconds(WaitTime); 
  digitalWrite(AirLED,HIGH);
  delayMicroseconds(WaitTime1);
  FinalVoltage = vM * (5.0 / 1024.0); 
  FinalDustDesity = 0.17 * FinalVoltage - 0.1; 
  
}
