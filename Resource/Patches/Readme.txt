HardwareSerial.cpp:

The arduino original hardware serial library's transfer buffer is too small, so I've changed the SERIAL_BUFFER_SIZE (originally definition is 64 bit) to 256bit for ATMEGA8U2/ATMEGA*28P/ATMEGA16U2 and 512bit for Atmega 2560 in case  of the data loss.