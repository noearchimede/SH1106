/*! @fle Implementation of the SH1106_driver class
*/

#include "SH1106_driver.hpp"


SH1106_driver::SH1106_driver(uint8_t pages, uint8_t width, uint8_t horizontalOffset) :
interface(0x78, true, 100000),
// 132 and 8 are the RAM limits
screenWidth((width < 132) ? width : 132),
screenPages((pages < 8) ? pages : 8),

screenOffset(horizontalOffset)
{
}


bool SH1106_driver::init()
{

    interface.init();

    if(!interface.checkConnection()) {
        return false;
    }

    displayEnable(false);
    interface.sendCommand(0x8D); // charge pump
    clockFrequency(0x80);
    pumpVoltage0123(2);
    segmentRemap(true);
    flipVertically(true);
    comConfiguration(false);
    multiplex(63);
    displayOffest(0);
    columnAddr(0);
    startLine(0);
    pageAddr(0);
    displayEnable(true);

    return true;
}




void SH1106_driver::writeData(uint8_t page, uint8_t column, uint8_t data[], uint8_t length) {
    // check input
    if(page >= screenPages || column >= screenWidth) return;
    // subtract horizontal offset
    column -= screenOffset;
    // "cut" data on max screen width
    if(length > screenWidth - column) length = screenWidth - column;
    // write data
    pageAddr(page);
    columnAddr(column);
    interface.writeRAM(data, length);
}


void SH1106_driver::writeData(uint8_t page, uint8_t column, uint8_t data) {
    // check input
    if(page >= screenPages || column >= screenWidth) return;
    // subtract horizontal offset
    column -= screenOffset;
    // write data
    pageAddr(page);
    columnAddr(column);
    interface.writeRAM(data);
}



bool SH1106_driver::checkConnection() {
    return interface.checkConnection();
}


void SH1106_driver::turnOn() {
    displayEnable(true);
}

void SH1106_driver::turnOff() {
    displayEnable(false);
}



// ########################### SH1106 COMMANDS #################################


// 1, 2
void SH1106_driver::columnAddr(uint8_t col) {
    interface.sendCommand(0x10 | (col >> 4));
    interface.sendCommand(col & 0x0f);
}
// 3
void SH1106_driver::pumpVoltage0123(uint8_t level0123) {
    interface.sendCommand(0x30 | level0123);
}
// 4
void SH1106_driver::startLine(uint8_t line) {
    interface.sendCommand(0x40 | (line & 0x3F));
}
// 5
void SH1106_driver::contrast(uint8_t contrast) {
    interface.sendCommand(0x81);
    interface.sendCommand(contrast);
}
// 6
void SH1106_driver::segmentRemap(bool reverse) {
    interface.sendCommand(0xA0 | reverse);
}
// 7
void SH1106_driver::setEntireDisplayOn(bool enable) {
    interface.sendCommand(0xA4 | enable);
}
// 8
void SH1106_driver::reverse(bool enable) {
    interface.sendCommand(0xA6 | enable);
}
// 9
void SH1106_driver::multiplex(uint8_t ratio) {
    interface.sendCommand(0xA8);
    interface.sendCommand(ratio & 0x3F);
}
// 10
void SH1106_driver::dcDcEnable(bool enable) {
    bool displayOn = interface.isEnabled();
    if(displayOn) displayEnable(false);
    interface.sendCommand(0xAD);
    interface.sendCommand(0x8A | enable);
    if(displayOn) displayEnable(true);
}
// 11
void SH1106_driver::displayEnable(bool enable) {
    interface.sendCommand(0xAE | enable);
}
// 12
void SH1106_driver::pageAddr(uint8_t page) {
    interface.sendCommand(0xB0 | (page & 0x7));
}
// 13
void SH1106_driver::flipVertically(bool flip) {
    interface.sendCommand(0xC0 | (flip << 3));
}
// 14
void SH1106_driver::displayOffest(uint8_t offset) {
    interface.sendCommand(0xD3);
    interface.sendCommand(offset & 0x3F);
}
// 15
void SH1106_driver::clockFrequency(uint8_t frequency, uint8_t divisor) {
    interface.sendCommand(0xD5);
    interface.sendCommand(((frequency & 0xF) << 4) | (divisor & 0xF));
}
// 15
void SH1106_driver::clockFrequency(uint8_t regVal) {
    interface.sendCommand(0xD5);
    interface.sendCommand(regVal);
}
// 16
void SH1106_driver::disPreChargeTime(uint8_t pre, uint8_t dis) {
    pre &= 0xF; if(pre == 0) pre = 1;
    dis &= 0xF; if(dis == 0) dis = 1;
    interface.sendCommand(0xD9);
    interface.sendCommand((dis << 4) | pre);
}
// 16
void SH1106_driver::disPreChargeTime(uint8_t regVal) {
    interface.sendCommand(0xD9);
    interface.sendCommand(regVal);
}
// 17
void SH1106_driver::comConfiguration(bool sequential) {
    interface.sendCommand(0xDA);
    interface.sendCommand(0x2 | (!sequential << 4));
}
// 18
void SH1106_driver::comVoltage(uint8_t regValue) {
    interface.sendCommand(0xDB);
    interface.sendCommand(regValue);
}
// 19
void SH1106_driver::rmwBegin() {
    interface.sendCommand(0xE0);
}
// 20
void SH1106_driver::rmwEnd() {
    interface.sendCommand(0xEE);
}
// 21
void SH1106_driver::nop() {
    interface.sendCommand(0xE3);
}
