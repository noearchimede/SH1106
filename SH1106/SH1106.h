/*! @fle Header of the SH1106 class
*/

#ifndef SH1106_h
#define SH1106_h

#include <inttypes.h>
#include "SH1106_driver.hpp"

class SH1106 {

public:

    //! Constructor
    /*! @param width        Width of the display in pixels
        @param pages        Height of the display in single-byte pages (1 page =
                            8 pixels)
        @param offset       Address in RAM of the first left column (usually is 0)
        @param i2cAddress   Address of the display on the i2c bus
        @param i2i2cUseInternalPullup  Use internal I/O pin pullups as i2c pullups
    */
    SH1106(uint8_t width, uint8_t pages, uint8_t offset);


    //! Initialize the SH1106
    void init();


    //! Draw some consecutive bytes on a page
    /*! Draw any number of bytes on a single page
        @param page     Page on wich data will be displayed
        @param column   Column of the first data byte
        @param data     Array of bytes to be displayed
        @param length   Length of the `data` array
    */
    void drawPageArray(uint8_t page, uint8_t column, uint8_t data [], uint8_t length);

//
    // Instance of the SH1106 chip driver class
    SH1106_driver driver;

};

#endif
