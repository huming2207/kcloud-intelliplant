void SerialWeatherOutput(){
  Serial.print("1,");
  Serial.print(FinalDustDesity); 
  Serial.print(",");
  Serial.print(DHT.humidity);
  Serial.print(",");
  Serial.print(DHT.temperature);
  Serial.print(",");
  Serial.println(BMP085.readPressure());
  delay(300);
}
