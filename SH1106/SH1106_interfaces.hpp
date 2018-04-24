/*! @file Headers of the SH1106_interface classes

This file contains the headers of the SH1106_interface abstract class and
those of all the classes derived from it.
*/


/*! @class Abstract class: describes any interface to communicate with SH1106

The SH1106 OLED Controller features many different communication interfaces:

* 8-bit 6800-series parallel
* 8-bit 8080-series parallel
* 3-wire SPI
* 4-wire SPI
* I2C

This library was originally intended designed to use i2c, but this interface
should not be hardcoded in the higher level functions. Hence this abstract
class will be used in all higher level classes and methods declaration
instead of an interface-specific "concrete" class. This way changing the
communication interface will only require a single change in the constructor
of the "next level" class, i.e. SH1106 (by passing e.g. an SH1106_3SPI object
instead of an SH1106_I2C one). If there is not any class for the desider
interface yet, the user will need to write a class derived from this one.

*/
#ifndef SH1106_interfaces_h
#define SH1106_interfaces_h

#include <inttypes.h>
#include "Arduino.h"



class SH1106_interface {

public:

    //! Initialize the communication interface
    virtual void init()                                     = 0;
    //! Returns true if a device is connected (possibly check whether it is an SH1106)
    virtual bool checkConnection()                          = 0;
    //! Send a command to the SH1106
    virtual void sendCommand(uint8_t command)               = 0;
    //! Write an array of data into the RAM of the SH1106
    virtual void writeRAM(uint8_t data[], uint8_t length)   = 0;
    //! Write a byte of data into the RAM of the SH1106
    virtual void writeRAM(uint8_t data)                     = 0;
    //! Check whether the display is on or off
    virtual bool isEnabled()                                = 0;
    //! Check whether the device is busy (i.e. it is executing a command)
    virtual bool isBusy()                                   = 0;

    // TODO (would allow text superposition)
    //! Read an array of data from the RAM of the SH1106
    //domani virtual void readRAM(uint8_t data[], uint8_t length)    = 0;
};





/*! @class This class allows to communicate with an SH1106 through i2c interface

This class provides low level i2c functions specific to the ATmega328
microcontroller (like `init()` and `start()`) as well as higher level functions
that match SH1106 requirements (e.g. `sendCommand()` and `controlByte()`).

The public functions are defined in the SH1106_interface abstract class.
*/
class SH1106_I2C : public SH1106_interface {

public:
    //! Constructor
    /*! @param address           Display I2C address [default: 0x78]
    @param useInternalPullup Use ATmega internal pullups as I2C bus pullup
    resistors [default: true]
    @param frequency         I2C bus frequency [default: 100000] i
    */
    SH1106_I2C (uint8_t address = 0x78, bool useInternalPullup = true, uint32_t frequency = 100000);


    //! Initialize the i2c interface
    void init();
    //! Returns true if the device at `address` sends an ACK on request
    bool checkConnection();

    //! Send a command to the SH1106
    /*! @note This function contains a full i2c transaction (from start to stop)
    @param command single byte that will be interpreted as a command
    */
    void sendCommand(uint8_t command);
    //! Write an array of data into the RAM of the SH1106 chip
    /*! @note This function contains one single i2c transaction
    @param data     array of bytes to be sent
    @param length   length of the data array
    */
    void writeRAM(uint8_t data[], uint8_t length);
    //! Write a byte of data into the RAM of the SH1106 chip
    /*! @note This function contains one single i2c transaction
    @param data     byte to send
    */
    void writeRAM(uint8_t data);

    //! Check whether the display is on or off
    bool isEnabled();
    //! Check whether the device is busy (i.e. it is executing a command)
    bool isBusy();


private:

    // i2c parameters
    const uint8_t address;
    const bool useInternalPullup;
    const uint32_t frequency;

    // ### I2C MANAGEMENT ###

    // Send a start condition
    void    start();
    // Send a stop condition
    void    stop();

    // Send the address with R/!W bit cleared (-> write)
    // The address has been set in the constructor of this class
    void    addrWrite();
    // Send the address with R/!W bit set (-> read)
    void    addrRead();

    // Send a byte of data
    void    send(uint8_t data);
    // Read a byte of data
    uint8_t read(bool isLastByte);

    // Send a control byte (as specified in the SH1106 datasheet)
    // - last:    this is the last control byte, only data follows (any lenght)
    //            If `false` only a data byte follows, and then another control.
    // - command: The following data byte(s) have to be interpreted as commands
    //            If `false` they willi be interpreted as data
    void controlByte(bool last, bool command);

};


#endif
