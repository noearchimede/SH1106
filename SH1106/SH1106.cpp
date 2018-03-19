#include "SH1106.h"

/*! @fle Implementation of the SH1106 class
*/

SH1106::SH1106(uint8_t width, uint8_t pages, uint8_t offset, uint8_t i2cAddress, bool i2cUseInternalPullup) :
driver(SH1106_I2C(i2cAddress,i2cUseInternalPullup, 100000), width, pages, offset)
{}



void SH1106::init() {
    if(!driver.init()) Serial.print(F("OLED not connected"));
}


void SH1106::drawPageArray(uint8_t page, uint8_t column, uint8_t data [], uint8_t length) {
    driver.writeData(page,column, data, length);
}
