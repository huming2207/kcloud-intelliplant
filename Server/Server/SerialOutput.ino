void SerialWeatherOutput(){
  DHT.read();
  Serial.print("1,");
  Serial.print(FinalDustDesity); 
  Serial.print(",");
  Serial.print(DHT.humidity / 10);
  Serial.print(",");
  Serial.print(DHT.temperature / 10);
  Serial.print(",");
  Serial.println(pressure);
  delay(300);
}

void SerialScheduleOutput(){
  Serial.print("2,");
  Serial.print(ScheduleHr); 
  Serial.print(",");
  Serial.print(ScheduleMin);
  Serial.print(",");
  Serial.print(ScheduleNum);
}
