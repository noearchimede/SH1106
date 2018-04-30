/*! @file Explanatory example program for the Label class.

    Imposratnt note: most printing functions in this class use C strings, i.e.
    unidimensional char arrays terminated by a NULL character ('\0').
    If the string passed to one of those functions is not NULL-terminated the
    function will read all the bytes following the actual string in memory and
    print them as if they were ASCII characters until reaching an emoty byte.
*/

#include <Arduino.h>

// To write text
#include "Label.hpp"
// to print bitmap images
#include "Image.hpp"



// First of all an instance of the display driver must be created.
// The constructor requires one parameter and can take three others:
// 1. (needed) an instance of a class derived from
// SH1106_interfaces, e.g. SH1106_I2C; 2. (optional) width in columns, 3.
// (optional) height in 8-bit pages, 4. (optional) horizontal offset
// (address of the first visible column; usually is 0, sometimes 2).
//
// ## I2C interface constructor ##
// It takes three optional parameters: 1. the device address, 2. whether to
// use internal (`true`) or external (`false`) pullup resistors for the bus,
// and 3. the bus clock frequency. The frequency may be different for other
// devices on the same bus.
SH1106_I2C oled_i2c(0x78, true, 100000);
SH1106_driver oled(oled_i2c, 128, 8, 0);


// Next we need to set some frames that will later be filled with text or
// images. The constructors for these containters take five parameters:
// 1. a reference to the driver of the display, 2. width (columns),
// 3. height (8-bit pages), 4. x position (columns), 5. y position (pages)
//
// In case of ovelapping of two frames writing to one will overwrite the other
Label mainLabel (oled, 100, 8, 0, 0);
Image image     (oled, 24, 4, 102, 1);
Label imageName (oled, 28, 1, 100, 6);
// It is always useful to have a label (or image) frame as large as the screen,
// e.g. to clear it (the driver doesn't provide any full-screen printing
// function)
Label screen    (oled, 128, 8, 0, 0);


// these will be used later
const char str [] = "This text is stored in RAM, \0";
const char flashStr [] PROGMEM = "this one is in PROGMEM. \0";
const uint8_t img [] PROGMEM =
{
// Image (24 x 4)
0xFF, 0xFF, 0xFF, 0xFF,
0x80, 0x04, 0x10, 0x01,
0xC0, 0x02, 0x10, 0x03,
0xB0, 0x01, 0x10, 0x05,
0x8C, 0x00, 0xA0, 0x09,
0x83, 0x00, 0x60, 0x11,
0xC0, 0xC0, 0x20, 0x21,
0xA0, 0x30, 0x40, 0x41,
0x90, 0xC, 0x40, 0x81,
0x88, 0x33, 0x41, 0x01,
0x84, 0xC2, 0xC2, 0x01,
0x83, 0x02, 0x34, 0x01,
0x8C, 0x04, 0x08, 0x01,
0xB0, 0x04, 0x10, 0x01,
0xC0, 0x08, 0x20, 0x01,
0x80, 0x08, 0x7F, 0xFF,
0xC0, 0x10, 0x80, 0x01,
0xBC, 0x11, 0x00, 0x01,
0x83, 0xE3, 0x80, 0x01,
0x80, 0x24, 0x70, 0x01,
0x80, 0x48, 0xE, 0x01,
0x80, 0x50, 0x01, 0xC1,
0x80, 0xA0, 0x00, 0x39,
0xFF, 0xFF, 0xFF, 0xFF,
};



void setup() { Serial.begin(9600);


    // ### INITIALIZATION & DRIVER ### //


    // The Driver class has a few public functions. The only one that the user
    // MUST call is `init()` (usually only once, during the program setup)
    oled.init();

    // The other public functions of the driver are:
    // * a function to check wether a display is connected as expected:
    if(!oled.connected()) while(1);
    // * the  turn off and turn on functions:
    oled.turnOff();
    oled.turnOn();
    // * the writeData function, wich can be used by the user but shouldn't be
    //   needed


    // ### CLEARING (any object) ### //

    // Clear a label (in this case the entire screen)
    screen.clear();


    // ### IMAGE ### //

    // Fill the image frame with a single repeated byte
    image.fill(0x55);
    delay(1000);

    // Fill it with a repeated pattern
    uint8_t pattern [2] = {0x55, 0xAA};
    image.fill(pattern, 2);
    delay(1000);

    // Draw an image. Note that the provided array must be of the same size as
    // the label. The elements of the array will be read in the following order:
    // 03-07-11-15-19-...
    // 02-06-10-14-18-...
    // 01-05-09-13-17-...
    // 00-04-08-12-16-...
    // The position of the array mst be specified choosing between RAM (false)
    // and PROGMEM (true).
    image.draw(img, true);



    // ### LABEL ### //

    // Print a string literal
    imageName.print("Image");



    // ## ADVANCED LABEL FUNCTIONS ## //


    // Write some text in a label
    mainLabel.print("Hello, ");
    // The text can also be wrapped in the F() macro
    mainLabel.print(F("world!\n"));
    // and can be a variable or constant char string
    mainLabel.print(str);
    // which can be stored in PROGMEM, but that needs to be specified ('false'
    // would make this function print a string in RAM, like the above one)
    mainLabel.print(flashStr, true);

    // There are other special characters, as listed in the table at the end
    // of this file.
    mainLabel.print(" <-");

    // The text can also include the ASCII control characters '\n', '\t' and
    // '\r'. The carriage return clears the current line.
    // Here are two ways to print a newline:
    mainLabel.newline();
    mainLabel.print("\n");


    // It is also possible to print numbers, and we may align them setting an
    // optional parameter to the minimum width of the integer part and (for
    // floats) another to the exact number of decimal positions.

    // Int
    mainLabel.print(273);
    mainLabel.tab();
    // Float, two decimal digits, align the integer part to the 4th position
    mainLabel.print(164.56, 2, 4);
    mainLabel.newline();
    // Number displayed in exadecimal format
    mainLabel.print(28, 16);
    mainLabel.tab();
    // Int casted to float, aligned as the float above
    mainLabel.print((float)6, 2, 4);
    mainLabel.newline();
    // Int variable, aligned to the 3th position: need to also specify base
    int x = 765; mainLabel.print(x, 10, 3);
    mainLabel.tab();
    // Complex number (not printable), aligned as above
    mainLabel.print(sqrt(-1), 2, 4);
    mainLabel.newline();


    // Now the label is full. This can be seen either empirically by running the
    // code on a real display either by checking the return value of each print
    // statement, wich will be false if anything could be printed, either by
    // using the availablePages() or/and availableColumns() functions.
    //
    // Sometimes it is useful not to need to care about the available space,
    // e.g. while printing a potentially infinite log. In those cases the
    // "infinite" mode may be useful.

    delay(5000);
    mainLabel.clear();

    // enable infinite mode (first parameter, 'false' to disable) with the
    // "empty line" option, i.e. request the line after the current one always
    // to be empty.
    mainLabel.setInfinite(true, true);

    // Generate a random pseudo-log
    while(1) {
        for(int i = random(5) + 1; i; i--) mainLabel.print((char)(random(26) + 'a'));
        mainLabel.tab();
        long x = 0; for(int i = random(3) + 1; i; i--) x += random(20*i+1) - 10*i;
        mainLabel.print(x, 10, 5);
        mainLabel.newline();
        delay(random(1000)+250);
    }



}
void loop() {

}



/* ### SPECIAL CHARACTERS ###

The print function allows to write ASCII printable characters (i.e. ASCII
characters 0x20 to 0x7E) as well as some special characters, obtained by
writing the following two character sequences.
The backslash '\' is used as escape character. Unless the user uses raw string
literals, the escape character must be written twice to pass it to the class
as a single backslash is interpreted by the compiler: e.g. write "\\^" to get
the escape sequence "\^" (up arrow).

| ASCII control characters                   ||
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
