void SerialWeatherOutput(){
  Serial.print("1,");
  Serial.print(FinalDustDesity); 
  Serial.print(",");
  Serial.print(DHT.humidity);
  Serial.print(",");
  Serial.print(DHT.temperature);
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
