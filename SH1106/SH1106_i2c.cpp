
#include "SH1106.h"
#include <avr/io.h>


SH1106::I2C::I2C(uint8_t address, bool useInternalPullup, uint32_t frequency) :
address(address),
useInternalPullup(useInternalPullup),
frequency(frequency)
{
}

void SH1106::I2C::init() {

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

// Send a start contdition on the i2c bus
void SH1106::I2C::start() {
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
}

// send a stop condition on the i2c bus
void SH1106::I2C::stop() {
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}


// SH1106 address = [0111 10xw], where x: settable adress bit and w: write bit
// Adress can be either 0x78 (x = 0) or 0x7A (x = 1)
//
void SH1106::I2C::addrWrite() {
    send(address);
}
//
void SH1106::I2C::addrRead() {
    send(address | 1);
}


void SH1106::I2C::controlByte(bool last, bool command) {
    uint8_t byt = 0;
    if(!last)    byt |= 0x80;
    if(!command) byt |= 0x40;
    send(byt);
}


void SH1106::I2C::send(uint8_t data) {
    // Write data in i2c Data Register
    TWDR = data;
    // Clear the interrupt flag (by writing a logical one to it) and enable TWI
    // to start the transmission
    TWCR = (1<<TWINT) | (1<<TWEN);
    // Wait for the transmission to complete
    while (!(TWCR & (1<<TWINT)));

}


bool SH1106::I2C::checkConnection() {
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


uint8_t SH1106::I2C::read(bool isLastByte) {
    // If this byte is the last one to be received, send a NACK after getting it
    if(isLastByte) TWCR &= ~(1<<TWEA);
    // else send an ACK
    else TWCR |= (1<<TWEA);
    // activate bus
    TWCR = (1<<TWINT) | (1<<TWEN);
    // wait for data to be sent by slave
    while(!(TWCR & (1<<TWINT)));
    return TWDR;
}
