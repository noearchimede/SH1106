/*! @file Header of the Image class
*/

#ifndef Image_hpp
#define Image_hpp

#include <inttypes.h>
#include "SH1106_driver.hpp"


/*!
Tha Image class allows to write a bitmap image on a given area of the screen.
The frame can have any size in width, but it's height must be a multiple of 8
as well as its y position because it needs to fit an integer number of pages.

The image must be represented as an unidimensional array of bytes. One byte
represents a vertical 8-pixel line whose top pixel is the most significant bit
of the pixel. The byte sequence procedes from left to right and then from top to
bottom.

@warning The image array must have enough bytes to fill the entire frame, i.e.
         to a 20 columns x 24 rows (i.e. 3 pages) an array of (at least) 60
         bytes must be passed.

*/
class Image {

public:

    //! Consturctor - provides image size and position
    Image(SH1106_driver & display, uint8_t width, uint8_t height, uint8_t startColumn, uint8_t startPage);

    //! Draw an image in the label
    /*! The size of the image must match the frame size. If it doesn't the
        behaviour is not defined.
    */
    void draw(const uint8_t image[]);

    //! Clear the frame
    /*! The cursor will be moved to (0,0)
    */
    void clear();

    //! fill the frame with a given single byte
    /*!
        @param data the byte that will be repeatedly printed.
    */
    void fill(uint8_t data = 0x00);

    //! fill the image with a given pattern
    /*!
        @param pattern this array will be repeatedly print to fill the frame
        @param length length of the pattern array
    */
    void fill(uint8_t * pattern, uint8_t length);


private:

    // Reference to an instance of the display driver
    SH1106_driver & driver;

    // Information about the frame of the image
    struct Frame {
        Frame(uint8_t width, uint8_t height, uint8_t xPos, uint8_t yPos);
        // Position of the upper left corner (relative address 0,0) in the
        // screen (whose upper left corner is at absolute address 0,0)
        uint8_t colShift, pagShift;
        // Dimension of the frame
        uint8_t columns, pages;
        // Check whether a given RELATIVE column/page address is in the label
        // The page may be omitted and will then be assumed to be in frame.
        bool isInFrame(uint8_t relativeColumn, uint8_t relativePage = 0);
        // Functions to convert a relative address to an absolute one
        uint8_t absoluteColumn (uint8_t relativeColumn);
        uint8_t absolutePage (uint8_t relativePage);
    };
    // frame used for all printing operations
    Frame frame;

};

#endif
