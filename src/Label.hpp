/*! @file Header of the Label class
*/

#ifndef Label_hpp
#define Label_hpp

#include <Arduino.h> // for inttypes and the F() macro
#include "SH1106_driver.hpp"
#include "characters.hpp"



/*! @brief Text printing class

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

The text is printed using the `print()` function, wich takes either a string
literal or a NULL-terminated string either a char array and its lenght as
a second parameter.
The print function allows to write ASCII printable characters (i.e. ASCII
characters 0x20 to 0x7E) as well as some special characters, obtained by
writing the following two character sequences.
The backslash '\' is used as escape character. Unless the user uses raw string
literals, the escape character must be written twice to pass it to the class
as a single backslash is interpreted by the compiler: e.g. write "\\^" to get
the escape sequence "\^" (up arrow).

| ASCII control characters                   ||
|------|--------------------------------------|
| \\n   | newline                              |
| \\t   | tab                                  |
| \\r   | carriage return; clears current line |

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
| \\v  | DOWN        |
| v-   | DOWN LEFT   |
| <-   | LEFT        |
| ^-   | UP LEFT     |

_Note: up sign is a circumflex accent, down is a lower case 'v'_

| Digits at exponent position                                       ||
|------|-------------------------------------------------------------|
| ^x   | where x is any number from 0 to 9                           |
| ^x^y | two or more exponent digits need repeated escape sequences  |

| Other special characters            ||
|-----|--------------------------------|
| ^o  | (lower case 'o') degree symbol |
| \\c | copyright symbol ©             |


| Escape character              ||
|------|-------------------------|
| \\\\ | write it twice to print |


The escape character may be used within any of the above sequences to tell the
writing function to print them as they are (e.g. "^o" prints "°" while "^\o"
prints "^o" and "^\\o" prints "^\o").


*/
class Label {

public:

    //! Consturctor - provides label size and position
    Label(SH1106_driver & display, uint8_t width, uint8_t height, uint8_t startColumn, uint8_t startPage);


    //! Print a NULL-TERMINATED string literal or char array on the screen
    /*! The text is encoded in ASCII but can contain a number of special
    sequences, listed in the class description. It will be print starting
    from the current cursor position and will be cut at the end of the
    label. Words (sequences of characters beetween two spaces) will not be
    split between two lines, if there isn't enough space for a word on the
    current line the cursor will automatically move to the next one, but
    spacing will not be influenced by the amount of free space at the end
    of the line.

    @warning The char array must end with a '\0' (NULL) character.
    '\0' is automatically appended to string literals.

    @param text  The char array containting the text to print
    @return `false` if there wasn't space enough to print all the text.
    The function will write as many character as possible given the
    space available from current cursor position.
    */
    bool print(const char * text);

    //! Print a NULL_terminated string in a given memory space (PROGMEM/RAM)
    /*! @param progmem `true` if the `text` is stored in PROGMEM, `false` if it
    is in RAM
    */
    bool print(const char * text, bool progmem);

    //! Print a string literal put inside the `F()` macro
    /*! Like `print(char)` but works for string literals put in PROGMEM by the
    `F()` macro.
    */
    bool print(const __FlashStringHelper * text);

    //! Print a single ASCII character
    bool print(char c);


    //! Print an integer number
    /* @param base The base to show the number. For base 16 the '0x' symbol will
    be prepended unless the number is negative.
    @param minWidth Minimum number of digits. Unused positions will be filled
    with spaces. This option allows to align numbers on differen lines.
    @param leadingZeros Fill all the unused spaces of minWidth (if any) with
    0s instead of spaces. */
    bool print(unsigned char n, uint8_t base = 10, uint8_t minWidth = 0, bool leadingZeros = false);
    //! See above
    /*! To distinguish this function from the single character printing the base
    parameter is not optional here */
    bool print(char n, uint8_t base, uint8_t minWidth = 0, bool leadingZeros = false);
    //! See above
    bool print(unsigned int n, uint8_t base = 10, uint8_t minWidth = 0, bool leadingZeros = false);
    //! See above
    bool print(int n, uint8_t base = 10, uint8_t minWidth = 0, bool leadingZeros = false);
    //! See above
    bool print(unsigned long n, uint8_t base = 10, uint8_t minWidth = 0, bool leadingZeros = false);
    //! See aboveß
    bool print(long n, uint8_t base = 10, uint8_t minWidth = 0, bool leadingZeros = false);

    //! Print a floating point number
    /*  The base is always 10.
    @param fractDigits  Number of digits to display in the fractional part.
    Unused spaces will be filled with 0s.
    @param minIntDigits Minimum number of digits in the integer part.
    Unused positions will be filled with spaces. */
    bool print(float n, uint8_t fractDigits = 2, uint8_t minIntDigits = 0);
    //! same as above
    bool print(double n, uint8_t fractDigits = 2, uint8_t minIntDigits = 0);


    //! Print a char array of given lenght on the screen.
    /*! @see write(char text[])
    @param text A char array containing the text to print. NULL characters
    ('\0') will be ignored.
    @param length Lengt of the text array.
    @param progmem Set to true if the `text` is stored in Flash memory (not RAM)
    */
    bool print(const char text[], uint16_t length, bool progmem);

    //! Clear the label
    /*! The cursor will be moved to (0,0)
    */
    void clear();


    //! Write a tab
    /*! By default there is an anchor every 25 pixels. Those anchors are used
    when there is no paramenter or the 'anchor' parameter is 0.
    It is also possible to set a custom anchor defined as a distance from
    the left (i.e. 60 will make the cursor jump to column 60). If the
    cursor is at a column at the right side of the anchor only a space will
    be drawn.

    This function actually writes some empty bytes, i.e. it will overwrite
    any underlying pixel.

    @return `false`if a custom-defined anchor could not be respoected
    (because it was out of frame or the cursor was already on its
    right side) or the tab went out of the frame.
    */
    bool tab(uint8_t anchor = 0);

    //! Go to the next line
    /*! @return `false` if there isn't any additional line below the current one
    */
    bool newline();

    //! Go to the beginning of current line and clear line
    /*! @return This function will always return true.
    */
    bool carriageReturnClear();

    //! Write a space
    /*! The space will overwrite any previouvsly written characters, but it
    will be cut if it is at end of a line.

    @return This function will always return true.
    */
    bool space();


    //! Write a single byte on a given part of the label
    /*! The cursor will be moved to the "begin" location.
    The "begin" and "end" points are given in the form (beginX, beginY, endX, endY).
    `data` is a byte that will be repeatedly printed.
    If the end position is set to 0xff it will be changed to the end of the
    label.

    If called with the default arguments this function clears the entire
    label (i.e. writes 0s on it).

    After execution the cursor is moved to the `begin` position.
    */
    void fill(uint8_t data = 0x00, uint8_t beginCol = 0, uint8_t beginPag = 0, uint8_t endCol = 0xFF, uint8_t endPag = 0xFF);


    //! Draw a number of consecutive bytes on a page as if it were a character
    /*! Draw any number of bytes on a single page. If the array is wider than
    the remaining space on the current page only a part of it will be
    printed, i.e. the printing of an array will not continue on the next
    page as it would in the case of a string.
    The printing will begin at current cursor positio and the cursor will
    be moved to the end of the string.

    @param page     Frame page on wich data will be displayed
    @param column   Frame column of the first data byte
    @param data     Array of bytes to be displayed
    @param length   Length of the `data` array

    @return This function will only return `true` if the array has been
    _entirely_ print. This means that it could return `false` while
    some bytes were printed.

    */
    bool printArray(const uint8_t data[], uint8_t length);


    //! Move the cursor to a given location
    /*! If the given position is out of the label the cursor will not be moved
    and this function will return false.
    */
    bool setCursor(uint8_t column, uint8_t page);

    //! Get the current cursor position
    void getCursor(uint8_t& column, uint8_t& page);

    //! Get the remaining space on current line
    uint8_t availableColumns();

    //! Get the number of available pages under the cursor
    uint8_t availablePages();

    //! get the size of the label
    void getSize(uint8_t& columns, uint8_t& pages);


    //! Set the cursor to use the first line as the one after the last
    /*! This setting allows the user to continuously write text to the label
    without worrying about getting out of frame: after filling the last line
    the cursor will move back to the first one.
    It is possible to always clear the line under the cursor. More complex
    text overwriting functions must be implemented by the user.
    */
    void setInfinite(bool enable, bool emptyLine);


private:


    // ### SETTINGS ### //

    // "Custom" escape character used in this class. Could be a backslash
    // (write it twice - '\\' - in string literals to tell the compiler to
    // escape it) but also a less used character like '#' or '@'. Don't use
    // backtick as it is used as accent.
    // The escape character can be printed by typing it twice without spacing
    // ('\\\\' or '##').
    static constexpr char escape = '\\'; // backslash

    // Margin on each side of the label in pixels
    static constexpr unsigned int margin = 1;

    // Default tab anchors spacing
    static constexpr unsigned int defaultTab = 36;


    // ### FUNCTIONS ### //

    // This enum is used as return type of the `getMoveChar()` function
    enum class MoveType {none, space, tab, newline, carriageReturn};
    // Check whether `char1` or the char1-char2 sequence are an "action"
    // character (newline, tab, carriage return, space), i.e. if they require
    // this class to move the cursor.
    // Retruns MoveType::none if not.
    // If the characters were an escaped sequence the variable given as first
    // parameter will be `true`
    // The second character may be NULL while the first one should be a
    // printable character or one of '\n', '\t' and '\r'
    MoveType getMoveChar(bool& bothUsed, const char char1, const char char2 = '\0');

    // Function used to read a characher array wich may contain escaped
    // characters. If the parameter `bothUsed` is true the two characters were
    // joined to produce a single output (e.g. 'e' and '`' will result in 'è').
    // The second character may be NULL while the first one should be a
    // printable character.
    //
    // "Action" characters escaped with the custom escape character are treated
    // by another function and will be considered as 'unknown' characters here.
    // Thus this function should not be called if the character or character
    // sequence is a tab, newline or carriage return. Neither should it be
    // called for spaces, but if it were it would return a fixed width space.
    const uint8_t* getPrintableChar(bool& bothUsed, const char char1, const char char2 = '\0');


    // Get the printed width of the characters in the array between two indexes.
    // The string must not contain newlines, tabs or carriage returns and
    // should not contain spaces.
    // Only lements [firstIndex] to [stopIndex - 1] of the array will be
    // considered.
    // The progmem parameter must be true if the data array is stored in Flash
    // memory and false if it is in RAM
    uint16_t getWordWidth(const char word[], uint16_t firstIndex, uint16_t stopIndex, bool progmem);


    // Write a given number of printable characters. The string must not contain
    // newlines, tabs or carriage returns and should not contain spaces
    // Only lements [firstIndex] to [stopIndex - 1] of the array will be
    // considered.
    // The progmem parameter must be true if the data array is stored in Flash
    // memory and false if it is in RAM
    bool writeWord(const char word[], uint16_t firstIndex, uint16_t stopIndex, bool progmem);

    // Write a character
    bool writeChar(const uint8_t *);


    // Print an integer
    bool printInt(unsigned long n, uint8_t minWidth, uint8_t base, bool negative, bool leadingZeros);
    // Print a float
    bool printFloat(double n, uint8_t fractDigits, uint8_t minIntDigits);


    // ### VARIABLES ###


    // Reference to an instance of the display driver
    SH1106_driver & driver;
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
        // Check whether a given RELATIVE column/page address is in the label
        // The page may be omitted and will then be assumed to be in frame.
        bool isInFrame(uint8_t relativeColumn, uint8_t relativePage = 0);
        // Functions to convert a relative address to an absolute one
        uint8_t absoluteColumn (uint8_t relativeColumn);
        uint8_t absolutePage (uint8_t relativePage);

        // Set by the user. If true when performing a newline from the last
        // line the cursor will go back to first line.
        bool infinite;
        bool infiniteEmptyLine;
    };
    // frame used for all printing operations
    Frame frame;
    // Slightly wider frame used only by the fill() function, wich is also used
    // to clear. This frame must be made wider than `frame` in the constructor.
    Frame clearFrame;

    // Text writing cursor
    // Cursor needs to use the private nested class Frame
    friend class Cursor;
    struct Cursor {
        Cursor(Label::Frame & frame, Label & label);
        // Current cursor position
        uint8_t column, page;
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
        Label & label;
    };
    Cursor cursor;

};

#endif
