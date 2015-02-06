void SerialWeatherOutput(){
  DHT.read();
  Serial.print("1,");
  Serial.print(FinalDustDesity); 
  Serial.print(",");
  Serial.print(DHT.humidity / 10);
  Serial.print(",");
  Serial.print(DHT.temperature / 10);
  Serial.print(",");
  Serial.println(long(pressure)); // Here if we use float, it will comes up two more digits and one dot. It will use more serial brandwidth resource and maybe cause the unstability.
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
