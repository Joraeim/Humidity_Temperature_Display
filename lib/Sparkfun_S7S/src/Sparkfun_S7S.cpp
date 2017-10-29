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
#include "Sparkfun_S7S.h"

Sparkfun_S7S::Sparkfun_S7S(void) {
  _i2caddr = DISPLAY_ADDRESS;
}

bool Sparkfun_S7S::begin(void)
{
  //If the I2C bus is not enabled, enable it and join it as a master.
  if(!Wire.isEnabled())
  {
    Wire.begin();
  }

  //Send the reset command to the display - this forces the cursor to return to
  // the beginning of the display
  reset();
}

void Sparkfun_S7S::reset(void)
{
  Wire.beginTransmission(_i2caddr);
  Wire.write(CLEAR_DISPLAY);
  Wire.endTransmission();
  delay(50);
  return;
}

//Given a number, i2cSendValue chops up an integer into four values and sends them out over I2C
// void Sparkfun_S7S::WriteValue(uint value)
// {
//   int8_t data[4];
//   Wire.beginTransmission(_i2caddr); // Start transmission to device @ _i2caddr
//   value %= 10000; //Drop anything over four digits.
//   data[0] = value / 1000; //Set the left most digit
//   value %= 1000; //Now remove the left most digit from the number we want to display
//   data[1]= value / 100;
//   value %= 100;
//   data[2] = value / 10;
//   value %= 10;
//   data[3] = value;//Send the right most digit
//   WriteValue(data, 4);
//   Wire.endTransmission(); //Stop I2C transmission
//   return;
// }

void Sparkfun_S7S::WriteValue(float value)
{
  uint8_t display_data[4];
  display_data[0]= (static_cast<uint8_t>(value) % 100) / 10;
  display_data[1]= (static_cast<uint8_t>(value) % 10);
  SetDecimalLoc(2);
  display_data[2]= (static_cast<uint8_t>(value * 10) % 10);
  display_data[3]= (static_cast<uint8_t>(value * 100) % 10);
  WriteValue(display_data, 4);
  return;
}

void Sparkfun_S7S::WriteValue(uint8_t value)
{
  uint8_t data[] = {value};
  WriteValue(data, 1);
  return;
}

void Sparkfun_S7S::WriteValue(uint8_t value[], int length)
{
  Wire.beginTransmission(_i2caddr);
  for(int i = 0; i < length; i++)
  {
    Wire.write(value[i]);
  }
  Wire.endTransmission();
  return;
}

void Sparkfun_S7S::SetCursorLoc(int location)
{
  Wire.beginTransmission(_i2caddr);
  Wire.write(CURSOR_CONTROL);
  if(location < 0)
  {
    location = 0;
  }
  else if(location > 3)
  {
    location = 3;
  }

  Wire.write(location);
  Wire.endTransmission();
  delay(50);
  return;
}

void Sparkfun_S7S::ClearDisplay()
{
  Wire.beginTransmission(_i2caddr);
  Wire.write(CLEAR_DISPLAY);
  Wire.endTransmission();
  delay(50);
  return;
}

void Sparkfun_S7S::SetDecimalLoc(int location)
{
  Wire.beginTransmission(_i2caddr);
  Wire.write(DECIMAL_CONTROL);
  Wire.write(location);
  Wire.endTransmission();
  delay(50);
  return;
}
