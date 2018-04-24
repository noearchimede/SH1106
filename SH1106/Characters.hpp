/*! @file This file contains the graphical definition of the most importand ASCII Characters. */

#ifndef Characters_hpp
#define Characters_hpp

#include <inttypes.h>


//! Definition of a set of characters designed to fit an 8-bit page
struct PageFont {

    // width of the largest character
    static constexpr unsigned int maxWidth = 8;


    // Extract useful data from the charaacter array pointerd to by `ptr`
    // If `ptr` is not a poitner to the beginning of a character array stored in
    // PROGMEM in this class the result is not defined.
    //
    // The first parameter is a pointer to the beginning of a character array
    // of this class stored in Flash memory. `Data` must be an array of at least
    // PageFont::maxWidth bytes.
    // This function shuld be used as follows:
    //
    // uint8_t length;
    // uint8_t data[font.maxWidth];
    // font.readCharArray(pointer, length, data);
    //
    // where `pointer` is obtained using one of the following functions.
    void readCharArray(const uint8_t * ptr, uint8_t& length, uint8_t* data);

    // Like the above function but only returns the character's length
    void readCharLenght(const uint8_t * ptr, uint8_t& length);


    // Lookup table function for ASCII characters from 0x20 to 0x7E
    const uint8_t * getAscii(char character);

    // Getters for a non-ascii characters
    const uint8_t * getUnknown();
    const uint8_t * getAccentedVowel(char vowel);
    const uint8_t * getArrow(unsigned int clockWise8Steps);
    const uint8_t * getExpDigit(unsigned int digit);
    enum class SpecialChar {copyright, degree, unknown};
    const uint8_t * getSpecialChar(SpecialChar name);

};

#endif
