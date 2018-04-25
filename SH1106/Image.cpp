/*! @file implementation of the Image class */

#include "Image.hpp"
#include "avr/pgmspace.h"


Image::Image(SH1106_driver & display, uint8_t width, uint8_t height, uint8_t startColumn, uint8_t startPage)
:
driver(display),
frame(width, height, startColumn, startPage)
{
}




void Image::draw(const uint8_t *image) {
    uint16_t i = 0;
    for(uint8_t c = 0; c < frame.columns; c++) {
        for(uint8_t p = frame.pages; p > 0 ; p--) {
            driver.writeData(frame.absolutePage(p - 1), frame.absoluteColumn(c), image[i]);
            delay(500);
            i++;
        }
    }
}

void Image::clear() {
    fill(0x00);
}


void Image::fill(uint8_t data) {
    fill(&data, 1);
}

void Image::fill(uint8_t *pattern, uint8_t length) {
    for(int c = 0; c < frame.columns; c++) {
        for(int p = frame.pages; p; p--) {
            for(int i = 0; i < length; i++) {
                driver.writeData(frame.absolutePage(p), frame.absoluteColumn(c), pattern[i]);
            }
        }
    }
}




// ### Frame ### //



Image::Frame::Frame(uint8_t width, uint8_t height, uint8_t xPos, uint8_t yPos) {
    // Dimension
    columns  = width;
    pages    = height;
    // Position
    colShift = xPos;
    pagShift = yPos;
}



bool Image::Frame::isInFrame(uint8_t relativeColumn, uint8_t relativePage) {
    return (relativeColumn < columns && relativePage < pages);
}



// In case of invalid parameters, the first line/column of the label may be
// overwritten. This is preferred to overwriting other parts of the screen and
// shows that this class is somewhere ill-formed.
uint8_t Image::Frame::absoluteColumn(uint8_t relativeColumn) {
    if(relativeColumn < columns)
    return relativeColumn + colShift;
    else
    return colShift;
}


uint8_t Image::Frame::absolutePage(uint8_t relativePage) {
    if(relativePage < pages)
    return relativePage + pagShift;
    else
    return pagShift;
}
