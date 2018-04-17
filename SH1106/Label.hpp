/*! @file Header of the SH1106 class
*/

#ifndef SH1106_Label_h
#define SH1106_Label_h

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
Since there isn't much available space in a single 8-bit page, the text size
and font style are fixed.

The text is printed using the `write()` function, wich takes either a string
literal or a single NULL-terminated char array either a char array and its
lenght as second parameter.
The write function allows to write ASCII printable characters (i.e. ASCII
characters 0x20 to 0x7E) as well as some special characters, obtained by
writing the following two character sequences.
The backslash '\' is used as escape character. Unless the user uses raw string
literals, the escape character must be written twice to bass it to the class
as a single backslash is interpreted by the compiler: e.g. write "\\^" to get
the escape sequence "\^" (up arrow).

| "Action" characters                        ||
|------|--------------------------------------|
| \n   | newline                              |
| \t   | tab                                  |
| \r   | carriage return; clears current line |

| Accents ||
|------|---|
| a`   | à |
| e`   | è |
| i`   | ì |
| o`   | ò |
| u`   | ù |

| Arrows            ||
|------|-------------|
| \^   | UP          |
| -^   | UP RIGHT    |
| ->   | RIGHT       |
| -v   | DOWN RIGHT  |
| \v   | DOWN        |
| v-   | DOWN LEFT   |
| <-   | LEFT        |
| ^-   | UP LEFT     |

_Note: up sign is a circumflex accent, down is a lower case 'v'_

| Digits at exponent position                                       ||
|--------------------------------------------------------------------|
| ^x   | where x is any number from 0 to 9                           |
| ^x^y | two or more exponent digits need repeated escape sequences  |

| Other special characters            ||
|-----|--------------------------------|
| ^o  | (lower case 'o') degree symbol |
| \c  | copyright symbol ©             |


| Escape character             ||
|-----|-------------------------|
| \\  | write it twice to print |


The escape character may be used within any of the above sequences to tell the
writing function to print them as they are (e.g. "^o" prints "°" while "^\o"
prints "^o" and "^\\o" prints "^\o").


*/
class Label {

public:

    //! Consturctor - provides label size and position
    Label(uint8_t width, uint8_t height, uint8_t startCol, uint8_t startPage);

    //! Move the cursor to a given location
    void moveCursor(uint8_t column, uint8_t page);

    //! Write a space
    /*! The space will overwrite any previouvsly written characters, but it
    will be cut if it is at end of a line.
    */
    void space();

    //! Write a tab
    /*! By default there is an anchor every 25 pixels. Those anchors are used
        when there is no paramenter or the 'anchor' parameter is 0.
        It is however possible to set a custom anchor defined in distance from
        the left (i.e. 60 will make the cursor jump to column 60). If the
        cursor is already placed right of the anchor the tab will draw a space.

        This function actually writes some empty bytes, i.e. it will overwrite
        any underlying pixel.
    */
    void tab();

    //! Go to the next line
    /*! @return `false` if there isn't any additional line below the current one
    */
    bool newline();

    //! Go to the beginning of current line and clear line
    void carriageReturnClear();

    //! Clear the label
    /*! The cursor will be moved to (0,0)
    void clear();

    //! Clear all characters written between two points
    /*! The cursor will be moved to the "begin" location.
        The "begin" and "end" points are given in the form (beginX, beginY, endX, endY) */
    void clear(uint8_t beginCol, uint8_t beginPag, uint8_t endCol, uint8_t endPag);

    //! Prints a NULL-TERMINATED string literal or char array on the screen
    /*! The text is encoded in ASCII.
        @warning The char array must end with a '\0' (NULL) character.
                 '\0' is automatically appended to string literals.

        @param text  The char array containting the text to print
        @return `false` if there wasn't space enough to print all the text.
                 The function will write as many character as possible given the
                 space available from current cursor position.
    */
    bool write(char text[]);
    //! Prints a char array of given lenght on the screen.
    /*! @param text A char array containing the text to print. NULL characters
                    ('\0') will be ignored.
        @param length Lengt of the text array.
    */
    bool write(char text[], uint16_t length);

    //! Draw a number of consecutive bytes on a page as if it were a character
    /*! Draw any number of bytes on a single page
        @param page     Frame page on wich data will be displayed
        @param column   Frame column of the first data byte
        @param data     Array of bytes to be displayed
        @param length   Length of the `data` array
    */
    void writeArray(uint8_t column, uint8_t page, uint8_t data[], uint8_t length);


private:

    // This enum is used in one parameter of the `readString` function
    enum class MoveType {none, space, tab, newline, carriageReturn};

    // Function used to read a characher array wich may contain escaped
    // characters. If the parameter `escaped` is true the two characters were
    // joined to produce a single output (e.g. 'e' and '`' will result in 'è').
    // If the character is a tab, newline or space the `move` parameter will
    // have a non-zero value according to the above enum.
    geFont::Char readString(bool& escaped, MoveType& move, char char1, char char2)

    // Get the width in pixels of a word with charCount characters
    uint16_t getWordWidth(char word[], uint16_t charCount);

    // Write one single character (used in the single character writing functions)
    bool writeSingleChar(PageFont::Char c);

    // Write a character
    bool writeChar(PageFont::Char c);

    // Instance of the class used to render characters
    PageFont font;

    // Information about the frame of the label
    struct Frame {
        Frame(uint8_t width, uint8_t height, uint8_t xPos, uint8_t yPos);
        // Position of the upper left corner (relative address 0,0) in the
        // screen (whose upper left corner is at absolute address 0,0)
        uint8_t colShift, pagShift;
        // Dimension of the frame
        uint8_t columns, pages;
        // Functions to convert a relative address to an absolute one
        uint8_t absoluteColumn (uint8_t relativeColumn);
        uint8_t absolutePage (uint8_t relativePage);
    };
    Frame frame;

    // Text writing cursor
    struct Cursor {
        Cursor(Label::Frame & frame);
        // Current cursor position
        uint8_t column, page;
        // Set to true when the cursor reaches the end of the label
        bool outOfFrame;
        // Put the cursor on the next available location to write a given
        // number of pixels, i.e. either leave it where it is either move it
        // to next line. Returns false if there isn't space enough.
        bool prepare(uint8_t textWidth);
        // Move the cursor forward for a given number of columns
        // By default the cursor will not move further after moving to next line
        // returns false if the cursor goes out of bounds
        bool move(uint8_t steps, bool stopAtNL = true);

    private:
        // Reference to the frame struct of the enclosing class
        Label::Frame & frame;
    };
    Cursor cursor;

};


#endif
