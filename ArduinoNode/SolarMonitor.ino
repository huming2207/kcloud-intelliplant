/* 
    SHSS KCloud IntelliPlant Server (master) source code
    Author: Jackson Ming Hu <huming2207@gmail.com>
            Technical Club Union of Shenzhen Highschool of Science
    ***THIS CODE IS PROTECTED BY GPLv2 LICENCE, FOR NON-COMMERCIAL USE ONLY! ***
    
    SolarMonitor.ino --->> Get the data from ACS712 current sensor & some analog voltage sensor module.
                       Then convert the data to the intensity of light and calculate the pump's water capacity.
                       Also it can monitor the status of the solar pannel.
                       
*/



long InputVcc() {
  /* 
    Since the input power supply does not have exactly 5v power input, so that means the voltage data calculated from the analog input is not very accurate like this:
        ...
        double Vcc = 5.0;
        int value = analogRead(0);
        double volt = (value / 1023.0) * Vcc;
        ...
    So, here I will read the actual voltage value first, by using the AVR Atmega168/328p microchip internal sensor.
    See these below for detail information:
          http://www.atmel.com/Images/Atmel-8271-8-bit-AVR-Microcontroller-ATmega48A-48PA-88A-88PA-168A-168PA-328-328P_datasheet.pdf
          https://code.google.com/p/tinkerit/wiki/SecretVoltmeter
          http://hacking.majenko.co.uk/node/57
          http://provideyourown.com/2012/secret-arduino-voltmeter-measure-battery-voltage/
          http://arduino.cc/en/Reference/analogRead
  */

  long result;
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  result = 1126400L / result; // Back-calculate AVcc in mV
  return result;
}

void SolarVoltageCalculate(){
  /* 
     Now only support the "Two-resistance voltage converting sensor" like this:
       http://item.taobao.com/item.htm?spm=a230r.1.14.47.n4PCDg&id=41392308613&ns=1&abbucket=20
     ...or this:
       http://item.taobao.com/item.htm?spm=a230r.1.14.1.n4PCDg&id=40217515848&ns=1&abbucket=20
       
      I will add support for Maxim MAX471 Voltage & current sensor or some LM324 operational amplifier type voltage sensor later.
  */
  
  SolarVoltage = (analogRead(SolarVoltageAnalog) / 1023) *  InputVcc() * 5;
}        

void SolarCurrentCalculate(){
    /* 
           Now only support the ACS712 current sensor
           I will add support for Maxim MAX471 Voltage & current sensor or some LM324 operational amplifier type voltage sensor later.
    */
  
  /* 
      According to the offical datasheet, the sensitivity of ACS712 chip is 185mV/A,
      that means if the current increase 1A, then the analog voltage will increase 185mV
  */
  SolarCurrent = (InputVcc() - (InputVcc() / 2)) * (1/185); 
}

