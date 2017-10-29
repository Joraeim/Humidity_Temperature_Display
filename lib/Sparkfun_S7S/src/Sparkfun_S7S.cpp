/*
 11-2-2012
 Spark Fun Electronics
 Nathan Seidle

 This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
 Serial7Segment is an open source seven segment display.
 This is example code that shows how to send data over I2C to the display.

 Please Note: 0x71 is the 7-bit I2C address. If you are using a different language than Arduino you will probably
 need to add the Read/Write bit to the end of the address. This means the default read address for the OpenSegment
 is 0b.1110.0011 or 0xE3 and the write address is 0b.1110.0010 or 0xE2.
 For more information see https://learn.sparkfun.com/tutorials/i2c
 Note: This code expects the display to be listening at the default I2C address. If your display is not at 0x71, you can
 do a software or hardware reset. See the Wiki for more info:
 http://github.com/sparkfun/Serial7SegmentDisplay/wiki/Special-Commands

 To get this code to work, attached an Serial7Segment to an Arduino Uno using the following pins:
 A5 to SCL
 A4 to SDA
 VIN to PWR
 GND to GND

 For this example pull up resistors are not needed on SDA and SCL. If you have other devices on the
 I2C bus then 4.7k pull up resistors are recommended.

 OpenSegment will work at 400kHz Fast I2C. Use the .setClock() call shown below to set the data rate
 faster if needed.
*/

#include <Wire.h>

Sparkfun_S7S::Sparkfun_S7S(void) {
  _i2caddr = DISPLAY_ADDRESS;
}

int cycles = 0;

bool Sparkfun_S7S::begin(void)
{
  Wire.begin(); //Join the bus as master

  //By default .begin() will set I2C SCL to Standard Speed mode of 100kHz
  //Wire.setClock(400000); //Optional - set I2C SCL to High Speed Mode of 400kHz

  //Serial.begin(9600); //Start serial communication at 9600 for debug statements
  //Serial.println("OpenSegment Example Code");

  //Send the reset command to the display - this forces the cursor to return to the beginning of the display
  reset();
}

void Sparkfun_S7S::reset(void) {
  Wire.beginTransmission(_i2caddr);
  Wire.write(CLEAR_DISPLAY);
  Wire.endTransmission();
  delay(50);
}

//Given a number, i2cSendValue chops up an integer into four values and sends them out over I2C
void WriteValue(int value)
{
  Wire.beginTransmission(_i2caddr); // transmit to device #1
  Wire.write(value / 1000); //Send the left most digit
  tempCycles %= 1000; //Now remove the left most digit from the number we want to display
  Wire.write(value / 100);
  tempCycles %= 100;
  Wire.write(value / 10);
  tempCycles %= 10;
  Wire.write(value); //Send the right most digit
  Wire.endTransmission(); //Stop I2C transmission
}
