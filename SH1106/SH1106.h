/*! @fle Header of the SH1106 class
*/

#ifndef SH1106_h
#define SH1106_h

#include <inttypes.h>
#include "SH1106_driver.hpp"
#include "characters.hpp"

/*!
The Label class allows to write any ASCII character plus some other symbols in
a frame of a given size set by the user in the constructor. There is no limit
to the amount of labels on a single display, as long as there is enough free
space. In case of overlapping of two displays (or other drawing entities) the
most recently active will partially or completely overwrite the other one.

The text is always written in a single page, so that the microcontroller
doesn't need to hold a copy of the dysplay RAM (all writing operations are to
be performed on whole pages, so if the text fills exactly one page there is no
need to preserve (thus know) some content when overwriting).

The text size and font style are fixed due to the limited space available in a
single 8 bit page.

*/
class SH1106_label {

public:

    //! Constructor
    /*! @param startColumn  position of the first left column of the frame
                            in the display
        @param startPage    position of the upper page of the frame in the                 display
        @param width        Width of the label frame in pixels
        @param pages        Height of the frame in single-byte pages (1 page =
                            8 pixels)
    */
    SH1106_label(SH1106_driver & driver, uint8_t pages, uint8_t columns, uint8_t startPage, uint8_t startColumn);


    //! Set the position where to write next character
    /*!
    @param page         Page. Will be updated to the position of the next
                        letter.
    @param column       First column to be used. Will be updated to the position
                        of the next letter.
    @param useNextLine  Decide whether this function can start using the
                        next line if text doesn't fit in the current one.
                        If `false` a character exceeding the display width
                        will not be displayed neither on the current line
                        nor on the following.
                        This option can be useful e.g. for writing a list
                        on a large label making sure that each listed item is
                        written on a single line.
    */
    void setCursor(uint8_t page, uint8_t column, bool useNextLine = true);


    //! write a newline
    bool newline();

    //! Add a tab
    /*! By default there is an anchor every 25 pixels. Those anchors are used
        when there is no paramenter or the 'anchor' parameter is 0.
        It is however possible to set a custom anchor defined in distance from
        the left (i.e. 60 will make the cursor jump to column 60). If the
        cursor is already placed right of the anchor the tab will draw a space.

        This function actually writes some empty bytes, i.e. it will overwrite
        any underlying pixel.
    */
    void tab(uint8_t anchor = 0);

    //! Write a space - shortcut for writeAscii(' ');`
    /*! The space is 4 pixels wide.
        This function actually writes 4 empty bytes, i.e. it will overwrite any
        underlying pixel.
    */
    void space();

    //! Delete all the content of this frame
    void clear();
    //! Delete the content of the current row
    void clearPage();
    //! Fill all the bytes beetween the start and the end positions with a given byte
    /*! The range includes the two bytes given by the user as start and end.

        @note This function writes each byte individually and thus is quite slow.

        @param content              the data to write on all target bytes
        @param startPage / startCol address of the fist byte to clear. Count
                                    starts from 0 (second page: nr. 1).
        @param endPage / endCol     address of the last byte to clear.
                                    If left empty the last byte in the label
                                    will be taken as end position.
    */
    void fillRange(uint8_t content, uint8_t startPag = 0, uint8_t startCol = 0, uint8_t endPag = 0, uint8_t endCol = 0);

    //! Drwas an ASCII character on a given page.
    /*! The font size is fixd so that it can be contained in a single page
        (i.e. 8 pixel line).
        @param character    ASCII character to write

        @return  false it couldn't write the character (out of bounds)
    */
    bool writeAscii(char character);

    //! Drwas an accented vowel
    /*! The accend is not clearly defined, i.e. it could be acute, grave or
        circumflex.
        This function works only with the following letters in lower case:
        a, e, i, o, u

        @see `writeCharOnPage()`
        @param letter  A vowel (in ASCII representation). The function will do
                       nothing if the letter is not a known vowel.
    */
    bool writeAccentedVowel(char letter);

    //! Draws a special arrow character on a page
    /*! This function prints a small arrow (the arrow fits in an 8x8 pixel
        square). The arrow can point at 8 diffrent directions, selected by a
        number in range 0-7 in a clockwise oredr: 0:up, 1:up/right, 2:right, ...

        @see `writeCharOnPage()`
        @param direction Direction of the arrow in 45° clockwise steps. 0 is up.

    */
    bool writeArrow8StepCW(uint8_t direction);

    //! Draws a small number in the upper half of the page
    /*! @see `writeCharOnPage()`
        @param number Direction of the arrow in 45° clockwise steps. 0 is up.
    */
    bool writeExpDigit(uint8_t digit);

    //! Draws a Copyright symbol (©)
    /*! @see `writeCharOnPage()`
    */
    bool writeCopyright();

    //! Draws a Degree symbol (°)
    /*! @see `writeCharOnPage()`
    */
    bool writeDegree();

    //! Draws a symbol representing an unknown character
    /*! @see `writeCharOnPage()`
    */
    bool writeUnknown();

    //! Draw a number of consecutive bytes on a page as if it were a character
    /*! Draw any number of bytes on a single page
        @param page     Frame page on wich data will be displayed
        @param column   Frame column of the first data byte
        @param data     Array of bytes to be displayed
        @param length   Length of the `data` array
    */
    void writeArray(uint8_t page, uint8_t column, uint8_t data[], uint8_t length);



    //! width of the label [columns]
    const uint8_t width;
    //! height of the label [pages]
    const uint8_t height;

private:

    // Write a character from the PageFont set in either a "proportional"
    // or a "monospaced" style
    bool writeChar(PageFont::Char8Bytes c, bool cut = false);


    // cursor for text input
    class Cursor {

    public:
        // Construct with the screen or frame physical dimensions
        Cursor (uint8_t pages, uint8_t columns, uint8_t pagShift, uint8_t colShift);

        // Location setters - relative
        // (the upper left corner of the label is always (0,0)
        void setPage (uint8_t page);
        void setColumn (uint8_t column);
        // Set mode: can the cursor change line (for- and backwards)?
        void setMode (bool useNextPage);

        // Location getters - relative
        // (the upper left corner of the label is always (0,0)
        uint8_t getPage();
        uint8_t getColumn();

        bool getMode();

        // Location getters - absolute
        // (the upper left corner of the label could be e.g. (30,4)
        uint8_t getAbsolutePage();
        uint8_t getAbsoluteColumn();

        // Returns true if the cursor is not in the writable frame (tus it will
        // not work, there isn't any out-of-bonds recording function)
        bool isOutOfBounds();

        // Returns the number of columns after the cursor in current line
        uint8_t remainingColumns();

        // Prepare cursor for writing x columns by switchng to next line if
        // necessary. Returns true if there is enough space to write that number
        // of bytes.
        bool prepare(unsigned int columns);

        // Move forwards or backwards by `columns` steps
        // returns false if the cursor went out of bounds
        //
        // When the stopAtNL option is set the cursor will be moved forward
        // until the end of current line is reached, and then if any additional
        // forward step is required it will just go to next line, then stop.
        // This option has no effect on backward movement.
        bool move(int columns, bool stopAtNL = true);

        // Move the cursor at beginning of next line, if possible
        // This function is able to switch to the next line even if the cursor
        // is set to no-newline mode.
        bool newline();


    private:

        // cursor location
        uint8_t col;
        uint8_t pag;
        // cursor mode (able to switch to a new line or not)
        bool useNL;
        // frame dimensions
        const uint8_t totPag;
        const uint8_t totCol;
        // frame location on the screen
        const uint8_t pagShift;
        const uint8_t colShift;
    };

    // Main text cursor
    Cursor cursor;

    // Reference to an instance of the SH1106 chip driver class
    SH1106_driver driver;

    // Basic ASCII character set
    PageFont font;

};

#endif
