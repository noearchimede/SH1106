/*! @file Implementation of the I2C communication i2c for SH1106
*/


#include "SH1106_interfaces.hpp"
#include <avr/io.h> // for register names
#include <Arduino.h> // for SDA, SCL and digitalWrite


SH1106_I2C::SH1106_I2C (uint8_t address, bool useInternalPullup, uint32_t frequency) :
address(address),
useInternalPullup(useInternalPullup),
frequency(frequency)
{
}



void SH1106_I2C::init() {

    // Set internal pullups resistors if required
    if(useInternalPullup) {
        digitalWrite(SDA, 1);
        digitalWrite(SCL, 1);
    }

    // initialize twi prescaler and bit rate
    // Prescaler is always set to 0 (TWSR[1:0] == 0x0)
    _SFR_BYTE(TWSR) &= ~_BV(TWPS0);
    _SFR_BYTE(TWSR) &= ~_BV(TWPS1);
    TWBR = ((F_CPU / frequency) - 16) / 2;

}


bool SH1106_I2C::checkConnection() {
    start();
    // Send address with write flag
    addrWrite();
    // Check wheter an ACK has been received
    // Status code 0x18 means: "SLA+W has been transmitted; ACK has been received"
    bool ack = ((TWSR & 0xF8) == 0x18);
    // Release the bus
    stop();

    return ack;
}



void SH1106_I2C::sendCommand(uint8_t command) {
    start();
    addrWrite();
    controlByte(true, true);
    send(command);
    stop();
}


void SH1106_I2C::writeRAM(const uint8_t data[], uint8_t length) {
    start();
    addrWrite();
    controlByte(true, false);
    for(uint8_t i = 0; i < length; i++) {
        send(data[i]);
    }
    stop();
}

void SH1106_I2C::writeRAM(const uint8_t data) {
    start();
    addrWrite();
    controlByte(true, false);
    send(data);
    stop();
}



bool SH1106_I2C::isEnabled() {
    start();
    addrRead();
    uint8_t status = read(true);
    stop();
    return !(status & 0x40);
}


bool SH1106_I2C::isBusy() {
    start();
    addrRead();
    uint8_t status = read(true);
    stop();
    return (status & 0x80);
}





void SH1106_I2C::start() {
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
}


void SH1106_I2C::stop() {
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}


// SH1106 address = [0111 10xw], where x: settable adress bit and w: write bit
// Adress can be either 0x78 (x = 0) or 0x7A (x = 1)
//
void SH1106_I2C::addrWrite() {
    send(address);
}


void SH1106_I2C::addrRead() {
    send(address | 1);
}



void SH1106_I2C::send(uint8_t data) {
    // Write data in i2c Data Register
    TWDR = data;
    // Clear the interrupt flag (by writing a logical one to it) and enable TWI
    // to start the transmission
    TWCR = (1<<TWINT) | (1<<TWEN);
    // Wait for the transmission to complete
    while (!(TWCR & (1<<TWINT)));

}


uint8_t SH1106_I2C::read(bool isLastByte) {
    // If this byte is the last one to be received, send a NACK after getting it
    // else send an ACK
    if(isLastByte) TWCR = (1<<TWINT) | (1<<TWEN);
    else TWCR = (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
    // wait for data to be sent by slave
    while(!(TWCR & (1<<TWINT)));
    // return received data
    return TWDR;
}




void SH1106_I2C::controlByte(bool last, bool command) {
    uint8_t byt = 0;
    if(!last)    byt |= 0x80;
    if(!command) byt |= 0x40;
    send(byt);
}
