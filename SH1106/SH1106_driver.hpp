/*! @fle Header of the SH1106_driver class
*/

#ifndef SH1106_driver_h
#define SH1106_driver_h

#include <Arduino.h>
#include "SH1106_interfaces.hpp"


/*! @brief SH1106 OLED controller communication management

This class gives easy access to all SH1106 basic commands and provides an
initialization and a write functions.
*/
class SH1106_driver {

public:

    // ### Constructor ### //

    //! Constructor
    /*! @note This constructor must be used if the display is connected to the
                microcontroller via the I2C interface.

    @param width        Width of the OLED screen (may be smaller than the 132
    bytes RAM of the SH1106)
    @param pages        Number of pages shown on screen. A page is 8 lines.
    The RAM has 8 pages.
    @param horizontalOffset RAM address of the first column. It may be not 0
    when the screen is less wide than the RAM (e.g. is
    sometimes 2 for 128 pixel screens).
    @param i2cAddress address of the display on the i2c bus. defaults to 0x78.
    @param i2cUseInternalPullups set whether to use internal or external pullup
            resistors fot the i2c bus

    */
    SH1106_driver(SH1106_interface & interface, uint8_t width = 132, uint8_t pages = 8, uint8_t horizontalOffset = 0);

    // we may create other constructors with different interfaces


    // ### Compound commands ### //

    //! Initialize display
    /*! @return false if the device was not connected
    */
    bool init();


    //! Chack whether an SH1106 is connected to the microcontroller
    bool connected();

    //! Turn on the display
    void turnOn();

    //! Turn off the display
    void turnOff();


    //! Write an array of bytes on the display
    /*!
    May be used by the user, but he/she shouldn't usually need to

    @param page     page on wich the array will be written
    @param column   column on wich the first by will be written, then the
    column address will be incremented until (column+lenght)
    is reached
    @param data     array of bytes to be written
    @param length   length of the data array
    */
    void writeData(uint8_t page, uint8_t column, const uint8_t data[], uint8_t lenght);

    //! Write a single byte on the display
    /*!
    May be used by the user, but he/she shouldn't usually need to

    @param page     page on wich the array will be written
    @param column   column on wich the first by will be written, then the
    column address will be incremented until (column+lenght)
    is reached
    @param data     bytes to be written
    */
    void writeData(uint8_t page, uint8_t column, const uint8_t data);


protected:

    //! @name SH1106 basic commands
    /*! The following functions give access to all SH1106 parameters. For detailed
    information about each setting refer to the datasheet (available e.g.
    here: http://www.allshore.com/pdf/SH1106.pdf).
    The numbres in comment refer to the command number in the datasheet
    */
    //!@{
    void   columnAddr         (uint8_t col);                          //!< 1, 2
    void   pumpVoltage0123    (uint8_t level0123);                    //!< 3
    void   startLine          (uint8_t line);                         //!< 4
    void   contrast           (uint8_t contrast);                     //!< 5
    void   segmentRemap       (bool reverse);                         //!< 6
    void   setEntireDisplayOn (bool enable);                          //!< 7
    void   reverse            (bool enable);                          //!< 8
    void   multiplex          (uint8_t ratio);                        //!< 9
    void   dcDcEnable         (bool enable);                          //!< 10
    void   displayEnable      (bool enable);                          //!< 11
    void   pageAddr           (uint8_t page);                         //!< 12
    void   flipVertically     (bool flip);                            //!< 13
    void   displayOffest      (uint8_t offset);                       //!< 14
    void   clockFrequency     (uint8_t frequency, uint8_t divisor);   //!< 15
    void   clockFrequency     (uint8_t regVal);                       //!< 15
    void   disPreChargeTime   (uint8_t pre, uint8_t dis);             //!< 16
    void   disPreChargeTime   (uint8_t regVal);                       //!< 16
    void   comConfiguration   (bool sequential);                      //!< 17
    void   comVoltage         (uint8_t regValue);                     //!< 18
    void   rmwBegin           (void);                                 //!< 19
    void   rmwEnd             (void);                                 //!< 20
    void   nop                (void);                                 //!< 21
    //!@}



private:

    // Communication interface handler
    SH1106_interface& interface;
    // Here we could add other interfaces, e.g. SH1106_SPI spi;

    // width of the display, usually 128, sometimes 132
    uint8_t screenWidth;
    // height of the display in pages (1 page = 8 lines), Uuually 8
    uint8_t screenPages;
    // If the display is less wide than the RAM (less than 132 pixels), the memory
    // address of the left column could not be 0 (eg. 2 for 128 pixel screens).
    uint8_t screenOffset;

};


#endif
