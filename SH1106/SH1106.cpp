#include "SH1106.h"



void SH1106::init()
{
    if(!i2c.checkConnection()) {
        Serial.print(F("OLED not connected"));
    }

    i2c.init();

    displayEnable(false);
    sendCommand(0x8D); // charge pump
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

}

void SH1106::writeData(uint8_t page, uint8_t column, uint8_t data[], uint8_t length) {
    // check input
    if(page >= displayPages || column >= displayWidth) return;
    // "cut" data on max screen width
    if(length > displayWidth - column) length = displayWidth - column;
    // write data
    pageAddr(page);
    columnAddr(column);
    writeRAM(data, length);
}


void SH1106::writeRAM(uint8_t data[], uint8_t length) {
    i2c.start();
    i2c.addrWrite();
    i2c.controlByte(true, false);
    for(uint8_t i = 0; i < length; i++) {
        i2c.send(data[i]);
    }
    i2c.stop();
}


void SH1106::sendCommand(uint8_t command) {
    i2c.start();
    i2c.addrWrite();
    i2c.controlByte(true, true);
    i2c.send(command);
    i2c.stop();
}




uint8_t SH1106::readStatus() {
    i2c.start();
    i2c.addrRead();
    uint8_t status = i2c.read(true);
    i2c.stop();
    return status;
}


bool SH1106::isEnabled() {
    uint8_t status = readStatus();
    return !(status & 0x40);
}

bool SH1106::isBusy() {
    uint8_t status = readStatus();
    return (status & 0x80);
}




// ########################### SH1106 COMMANDS #################################


// 1, 2
void SH1106::columnAddr(uint8_t col) {
    sendCommand(0x10 | (col >> 4));
    sendCommand(col & 0x0f);
}
// 3
void SH1106::pumpVoltage0123(uint8_t level0123) {
    sendCommand(0x30 | level0123);
}
// 4
void SH1106::startLine(uint8_t line) {
    sendCommand(0x40 | (line & 0x3F));
}
// 5
void SH1106::contrast(uint8_t contrast) {
    sendCommand(0x81);
    sendCommand(contrast);
}
// 6
void SH1106::segmentRemap(bool reverse) {
    sendCommand(0xA0 | reverse);
}
// 7
void SH1106::setEntireDisplayOn(bool enable) {
    sendCommand(0xA4 | enable);
}
// 8
void SH1106::reverse(bool enable) {
    sendCommand(0xA6 | enable);
}
// 9
void SH1106::multiplex(uint8_t ratio) {
    sendCommand(0xA8);
    sendCommand(ratio & 0x3F);
}
// 10
void SH1106::dcDcEnable(bool enable) {
    bool displayOn = isEnabled();
    if(displayOn) displayEnable(false);
    sendCommand(0xAD);
    sendCommand(0x8A | enable);
    if(displayOn) displayEnable(true);
}
// 11
void SH1106::displayEnable(bool enable) {
    sendCommand(0xAE | enable);
}
// 12
void SH1106::pageAddr(uint8_t page) {
    sendCommand(0xB0 | (page & 0x7));
}
// 13
void SH1106::flipVertically(bool flip) {
    sendCommand(0xC0 | (flip << 3));
}
// 14
void SH1106::displayOffest(uint8_t offset) {
    sendCommand(0xD3);
    sendCommand(offset & 0x3F);
}
// 15
void SH1106::clockFrequency(uint8_t frequency, uint8_t divisor) {
    sendCommand(0xD5);
    sendCommand(((frequency & 0xF) << 4) | (divisor & 0xF));
}
// 15
void SH1106::clockFrequency(uint8_t regVal) {
    sendCommand(0xD5);
    sendCommand(regVal);
}
// 16
void SH1106::disPreChargeTime(uint8_t pre, uint8_t dis) {
    pre &= 0xF; if(pre == 0) pre = 1;
    dis &= 0xF; if(dis == 0) dis = 1;
    sendCommand(0xD9);
    sendCommand((dis << 4) | pre);
}
// 16
void SH1106::disPreChargeTime(uint8_t regVal) {
    sendCommand(0xD9);
    sendCommand(regVal);
}
// 17
void SH1106::comConfiguration(bool sequential) {
    sendCommand(0xDA);
    sendCommand(0x2 | (!sequential << 4));
}
// 18
void SH1106::comVoltage(uint8_t regValue) {
    sendCommand(0xDB);
    sendCommand(regValue);
}
// 19
void SH1106::rmwBegin() {
    sendCommand(0xE0);
}
// 20
void SH1106::rmwEnd() {
    sendCommand(0xEE);
}
// 21
void SH1106::nop() {
    sendCommand(0xE3);
}
