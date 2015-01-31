void LCDClearWithoutBlink(){
    lcd.setCursor(0,0);
    lcd.print("                    ");
    lcd.setCursor(0,1);
    lcd.print("                    ");
    lcd.setCursor(0,2);
    lcd.print("                    ");
    lcd.setCursor(0,3);
    lcd.print("                    ");
}

void LCDShowSchedule(){
    lcd.setCursor(0,1);
    lcd.print("Tmp:");
    lcd.print(int(SerialNumData[3]));
    lcd.print(" Humid:");
    lcd.print(int(SerialNumData[2]));
    lcd.setCursor(2,2);
    lcd.print("Dust:");
    lcd.print(int(SerialNumData[1]));
    lcd.setCursor(0,3);
    lcd.print("Last: ");
    lcd.print(int(SerialNumData[1]));
    lcd.print(":");
    lcd.print(int(SerialNumData[2]));
    lcd.print(" M");
    lcd.print(int(SerialNumData[3]));
}
