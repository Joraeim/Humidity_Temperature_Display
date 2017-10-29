/**************************************************************************/
/*!
    @file     Adafruit_Si7021.h
    @author   Limor Fried (Adafruit Industries)
    @license  BSD (see license.txt)

    This is a library for the Adafruit Si7021 breakout board
    ----> https://www.adafruit.com/products/3251

    Adafruit invests time and resources providing this open source code,
    please support Adafruit and open-source hardware by purchasing
    products from Adafruit!

    @section  HISTORY

    v1.0  - First release

Sensor datasheet:
https://www.silabs.com/Support%20Documents%2FTechnicalDocs%2FSi7021-A20.pdf


Modified for Particle Photon/Electron
Need application.h for types    RMB
*/

#include "application.h"


/*=========================================================================
    I2C ADDRESS/BITS
    -----------------------------------------------------------------------*/
#define DISPLAY_ADDRESS 0x71 //This is the default address of the OpenSegment with both solder jumpers open
#define CLEAR_DISPLAY 0x76
#define DECIMAL_CONTROL 0x77
#define CURSOR_CONTROL 0x79
#define BRIGHTNESS_CONTROL 0x7A
#define DIGIT_CONTROL_1 0x7B
#define DIGIT_CONTROL_2 0x7C
#define DIGIT_CONTROL_3 0x7D
#define DIGIT_CONTROL_4 0x7E
#define BAUD_RATE_CONFIG 0x7F
#define I2C_ADDRESS_CONFIG 0x80
#define FACTORY_RESET 0x81

/*=========================================================================*/

class Sparkfun_S7S {
 public:
  Sparkfun_S7S(void);
  bool begin(void);
  void reset(void);
  //void WriteValue(uint value);
  //void WriteValue(float value, int precision);
  void WriteValue(float value);
  void WriteValue(uint8_t value);
  void WriteValue(uint8_t value[], int length);
  void SetCursorLoc(int location);
  void ClearDisplay(void);
  void SetDecimalLoc(int location);

 private:
  int8_t  _i2caddr;
};

/**************************************************************************/
