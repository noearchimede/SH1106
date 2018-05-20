/*! @file Implementation of the SH1106 class
*/
#include "Label.hpp"


Label::Label(SH1106_driver & display, uint8_t width, uint8_t height, uint8_t startColumn, uint8_t startPage)
:
// Make the frame two bytes less wide to allow a one-pixel margin on each side
driver(display),
frame((width - (2 * margin)), height, (startColumn + margin), startPage),
clearFrame(width, height, startColumn, startPage),
cursor(frame, *this)
{

}




void Label::clear() {
    fill();
}



// String (in RAM)
bool Label::print(const char * text) {
    uint16_t i = 0;
    while(text[++i]);
    return print(text, i, false);
}


// String literal in PROGMEM
bool Label::print(const __FlashStringHelper * text) {
    PGM_P flashPtr = reinterpret_cast<PGM_P>(text);
    uint16_t i = 0;
    while(pgm_read_byte(&(flashPtr[++i])));
    return print(flashPtr, i, true);
}


// String with memory specifier
bool Label::print(const char *text, bool progmem) {
    uint16_t i = 0;
    if(progmem)
    while(pgm_read_byte(&(text[++i])));
    else
    while(text[++i]);
    return print(text, i, progmem);
}


// single character
bool Label::print(char c) {
    return print(&c, 1, false);
}



// # print on a single line # //


// String (in RAM)
bool Label::printSingleLine(const char * text, Label::Alignment alignment) {
    uint16_t i = 0;
    while(text[++i]);
    return printSingleLine(text, i, false, alignment);
}


// String literal in PROGMEM
bool Label::print(const __FlashStringHelper * text) {
    PGM_P flashPtr = reinterpret_cast<PGM_P>(text);
    uint16_t i = 0;
    while(pgm_read_byte(&(flashPtr[++i])));
    return printSingleLine(flashPtr, i, true, alignment);
}


// String with memory specifier
bool Label::print(const char *text, bool progmem) {
    uint16_t i = 0;
    if(progmem)
    while(pgm_read_byte(&(text[++i])));
    else
    while(text[++i]);
    return printSingleLine(text, i, progmem, alignment);
}


// single character
bool Label::print(char c) {
    return printSingleLine(&c, 1, false, alignment);
}




// # Print numbers #

// Integers
bool Label::print(unsigned char n, uint8_t base, uint8_t minWidth, bool leadingZeros) {
    return printInt(n, minWidth, base, false, leadingZeros);
}
bool Label::print(char n, uint8_t base, uint8_t minWidth, bool leadingZeros) {
    if(n >= 0) return printInt((unsigned long) n, minWidth, base, false, leadingZeros);
    else return printInt((unsigned long) -n, minWidth, base, true, leadingZeros);
}
bool Label::print(unsigned int n, uint8_t base, uint8_t minWidth, bool leadingZeros) {
    return printInt(n, minWidth, base, false, leadingZeros);
}
bool Label::print(int n, uint8_t base, uint8_t minWidth, bool leadingZeros) {
    if(n >= 0) return printInt((unsigned long) n, minWidth, base, false, leadingZeros);
    else return printInt((unsigned long) -n, minWidth, base, true, leadingZeros);
}
bool Label::print(unsigned long n, uint8_t base, uint8_t minWidth, bool leadingZeros) {
    return printInt(n, minWidth, base, false, leadingZeros);
}
bool Label::print(long n, uint8_t base, uint8_t minWidth, bool leadingZeros) {
    if(n >= 0) return printInt((unsigned long) n, minWidth, base, false, leadingZeros);
    else return printInt((unsigned long) -n, minWidth, base, true, leadingZeros);
}

// Reals
bool Label::print(float n, uint8_t fractDigits, uint8_t minIntDigits) {
    return printFloat((double)n, fractDigits, minIntDigits);
}
bool Label::print(double n, uint8_t fractDigits, uint8_t minIntDigits) {
    return printFloat(n, fractDigits, minIntDigits);
}




bool Label::tab(uint8_t anchor) {


    if(anchor >= frame.columns) return false;

    // calculate tab width
    uint8_t tab;
    // user-defined anchor
    if(anchor) {
        if(cursor.column < anchor) {
            tab = anchor - cursor.column;
        }
        else {
            // The cursor is already on the right side of the anchor.
            // Just write a space to make sure that the previous word will not
            // be joined up with the next one.
            space();
            return false;
        }
    }
    // default tab
    else tab = defaultTab - (cursor.column % defaultTab);

    // Clear the space jumped by the tab
    bool inFrame = frame.isInFrame(cursor.column + tab);

    if(inFrame) fill(0x00, cursor.column, cursor.page, (cursor.column + tab), cursor.page);
    else fill(0x00, cursor.column, cursor.page, 0xFF, cursor.page);

    // move the cursor
    cursor.move(tab, true);

    if(inFrame) return true;
    return false;
}




bool Label::newline() {
    cursor.move(0xff, true);
    if(frame.isInFrame(cursor.column, cursor.page)) return true;
    return false;
}




bool Label::carriageReturnClear() {
    fill(0x0,0,cursor.page,0xFF,cursor.page);
    // here `fill` moves the cursor to the `begin` position.

    return true; //always
}




bool Label::space() {
    // Calculate the width of the space, if possible use the default one
    uint8_t width;
    font.readCharLenght(font.getAscii(' '), width);
    uint8_t availableSpace = frame.columns - cursor.column;
    if(width > availableSpace) width = availableSpace;

    for(uint8_t i = 0; i < width; i++) {
        driver.writeData(frame.absolutePage(cursor.page), frame.absoluteColumn(cursor.column), 0x00);
    }

    cursor.move(width);
    return true; //always
}






void Label::fill(uint8_t data, uint8_t beginCol, uint8_t beginPag, uint8_t endCol, uint8_t endPag) {

    // correct the indexing error created by the margin (see e.g. the
    // constructor to undestand the "problem")
    if(beginCol > 0 && beginCol != 0xFF) beginCol += margin;
    if(endCol > 0 && endCol != 0xFF) endCol += margin;

    // if one of the end parameters is 0xff replace it with its max value
    if(endPag == 0xFF) endPag = clearFrame.pages - 1;
    if(endCol == 0xFF) endCol = clearFrame.columns - 1;

    // if the range is "negative" return
    if(endPag < beginPag) return;
    else if(endPag == beginPag) {
        if(endCol < beginCol) return;
    }

    // If the region to fill is on a single page
    if(beginPag == endPag) {
        cursor.page = beginPag;
        for(int i = beginCol; i <= endCol; i++) {
            cursor.column = i;

            driver.writeData(clearFrame.absolutePage(cursor.page), clearFrame.absoluteColumn(cursor.column), data);
        }
    }

    // if multiple pages are to be filled
    else {
        // clear (part of) the first line
        cursor.page = beginPag;
        for(int i = beginCol; i < clearFrame.columns; i++) {
            cursor.column = i;

            driver.writeData(clearFrame.absolutePage(cursor.page), clearFrame.absoluteColumn(cursor.column), data);
        }
        // clear intermediate line(s)
        for(int k = beginPag + 1; k < endPag; k++) {
            cursor.page = k;
            for(int i = 0; i < clearFrame.columns; i++) {
                cursor.column = i;
                driver.writeData(clearFrame.absolutePage(cursor.page), clearFrame.absoluteColumn(cursor.column), data);
            }
        }
        // clear (part of) the last line
        cursor.page = endPag;
        for(unsigned int i = 0; i <= endCol; i++) {
            cursor.column = i;
            driver.writeData(clearFrame.absolutePage(cursor.page), clearFrame.absoluteColumn(cursor.column), data);
        }
    }

    cursor.page = beginPag;
    cursor.column = beginCol;
}





bool Label::printArray(const uint8_t data [], uint8_t length) {

    // cut the array, if needed, to fit in current page
    bool cut = false;
    if(!frame.isInFrame(cursor.column + length)) {
        length = frame.columns - cursor.column;
        cut = true;
    }

    if(!cursor.prepare(length)) return false;

    driver.writeData(frame.absolutePage(cursor.page), frame.absoluteColumn(cursor.column), data, length);

    cursor.move(length);

    return !cut;
}






bool Label::setCursor(uint8_t column, uint8_t page) {
    if(frame.isInFrame(column, page)) {
        cursor.column = column;
        cursor.page = page;
        return true;
    }
    return false;
}

void Label::getCursor(uint8_t& column, uint8_t& page) {
    column = cursor.column;
    page = cursor.page;
}



uint8_t Label::availableColumns() {
    return frame.columns - cursor.column;
}

uint8_t Label::availablePages() {
    return frame.pages - cursor.page;
}


void Label::getSize(uint8_t& columns, uint8_t& pages) {
    columns = frame.columns;
    pages = frame.pages;
}



void Label::setInfinite(bool enable, bool emptyLine) {
    frame.infinite = enable;
    frame.infiniteEmptyLine = emptyLine;
}




// Print: base function taking a char array of given length (not a C string)
bool Label::print(const char text[], uint16_t length, bool progmem) {

    // if the string is empty
    if(!text[0]) return true;

    uint16_t wordStartIndex = 0;
    bool charsToPrint = false;

    // Iterate over the entire string
    uint16_t i = 0;
    while(i < length) {

        // This variable will be set to true if two characters have beetween
        // joined together to print one single special character
        bool escapeSequence;

        // Check wheter the characrter at current index is an action one
        MoveType move;
        if(progmem) {
            move = getMoveChar(escapeSequence, pgm_read_byte(&(text[i])), (i+1 < length? pgm_read_byte(&(text[i+1])) : '\0'));
        }
        else {
            move = getMoveChar(escapeSequence, text[i], (i+1 < length? text[i+1] : '\0'));
        }

        // If it is an action character
        if(move != MoveType::none) {
            // Print last word
            if(charsToPrint) {
                charsToPrint = false;
                if(!writeWord(text, wordStartIndex, i, progmem)) return false;
            }

            // Perform required action on cursor
            switch(move) {
                case MoveType::space:
                // avoid spaces at the beginning of a line. This restriction
                // doesn't apply to the `space()` function.`
                if(cursor.column != 0)
                if(!space()) return false;
                break;
                case MoveType::tab:
                if(!tab()) return false;
                break;
                case MoveType::newline:
                if(!newline()) return false;
                break;
                case MoveType::carriageReturn:
                if(!carriageReturnClear()) return false;
                break;
                case MoveType::none: break; // Can't happen
            }
        }
        // else we know that the character has to be interpreted as text
        else {
            // If this is the first printable character after a space, tab, ...
            if(!charsToPrint) {
                wordStartIndex = i;
                charsToPrint = true;
            }
        }

        // The only possible escapes here are the "action" ones (e.g. "\\t").
        // The others are analyzed while measuring and printing a word.
        if(escapeSequence) i++;
        i++;
    }
    // Print last word
    if(charsToPrint) {
        charsToPrint = false;
        if(!writeWord(text, wordStartIndex, i, progmem))  return false;
    }

    return true;
}


// ################################ PRIVATE ################################# //

// Print a string of characters and spaces until the end of the line is reached
// This function allows to align simple text on the center and right side of the
// label, but doesn't compute action characters
bool Label::printSingleLine(const char text[], uint16_t length, bool progmem, Alignment alignment) {

    // if the string is empty
    if(!text[0]) return true;

    // Print all the string as if it were a single word (spaces are valid
    // characters)
    uint16_t width = getWordWidth(text, 0, length, progmem);
    int16_t freeSpace =  availableColumns() - width;

    // Special (not left) alignment
    if(freeSpace > 0) {
        // Right
        if(alignment == Alignment::right) cursor.column += freeSpace - 1;
        // center
        if(alignment == Alignment::center) cursor.column += freeSpace / 2;
    }
    writeWord(text, 0, length, progmem, true);

    return true;
}


const uint8_t* Label::getPrintableChar(bool& bothUsed, const char char1, const char char2) {


    // Default return values, will be changed according to the situation.
    const uint8_t* c = font.getUnknown();
    bothUsed = true;


    // Here begins a series of if - elseif conditions that looks for every
    // possible escape sequence. The else condition at the end is only reached
    // if the given text must simply be treated as plain text.

    // accented vowels
    if(char2 == '`') {
        if     (char1 == 'a') c = font.getAccentedVowel('a');
        else if(char1 == 'e') c = font.getAccentedVowel('e');
        else if(char1 == 'i') c = font.getAccentedVowel('i');
        else if(char1 == 'o') c = font.getAccentedVowel('o');
        else if(char1 == 'u') c = font.getAccentedVowel('u');
    }

    // Arrows
    else if(char1 == escape && char2 == '^') c = font.getArrow(0); // \^
    else if(char1 == '-'    && char2 == '^') c = font.getArrow(1); // -^
    else if(char1 == '-'    && char2 == '>') c = font.getArrow(2); // ->
    else if(char1 == '-'    && char2 == 'v') c = font.getArrow(3); // -v
    else if(char1 == escape && char2 == 'v') c = font.getArrow(4); // \v
    else if(char1 == 'v'    && char2 == '-') c = font.getArrow(5); // v-
    else if(char1 == '<'    && char2 == '-') c = font.getArrow(6); // <-
    else if(char1 == '^'    && char2 == '-') c = font.getArrow(7); // ^-

    // Digits at exponent position
    else if(char1 == '^' && ('0' <= char2 && char2 <= '9')) c = font.getExpDigit(char2 - '0');

    // Special characters
    // degree symbol
    else if((char1 == escape || char1 == '^') && char2 == 'o') c = font.getSpecialChar(PageFont::SpecialChar::degree);
    // Copyright symbol
    else if(char1 == escape && char2 == 'c') c =  font.getSpecialChar(PageFont::SpecialChar::copyright);

    // Double escape character
    else if(char1 == escape && char2 == escape) c = font.getAscii(escape);

    // "Action" characters escaped with the custom escape character are treated
    // by another function and will be considered as 'unknown' characters.
    // Thus this function should not be called if the character or character
    // sequence is a tab, newline or carriage return. Neither should it be
    // called for spaces, but if it were it would return a fixed width space.
    else if (char1 == escape && (char2 == 'n' || char2 == 't' || char2 == 'r')) c = font.getUnknown();

    // Unused escape character. It is ignored as may be used to avoid another
    // escape sequence: e.g. "->" prints a right arrow, "-\\>" prints "->",
    // where '\\' is the escape character.
    // There must always be at least two normal characters between two escapes
    // so that here we can assume that the second character is plain ASCII.
    else if(char1 == escape) c = font.getAscii(char2);


    // ### NO SPECIAL CHARACTER SEQUENCE ### //

    else {
        // plain ASCII text (will be a real character from ASCII '!' to '~',
        // i.e. 0x20 to 0x7E, and a printable 'unknown' character otherwise)
        // with one single exception: the vertical tab will be interpreted
        // as a space as wide as a character (it is used to align numbers).
        if (char1 == 0x0B) c = font.getSpecialChar(PageFont::SpecialChar::largeSpace);

        else c = font.getAscii(char1);
        // Update default return value
        bothUsed = false;
    }

    return c;
}




Label::MoveType Label::getMoveChar(bool& bothUsed, const char char1, const char char2) {

    MoveType move = MoveType::none;
    bothUsed = false;

    if(char1 == ' ') move = MoveType::space;
    else if(char1 == escape) {
        if(char2 == 'n') { move = MoveType::newline; bothUsed = true; }
        if(char2 == 't') { move = MoveType::tab; bothUsed = true; }
        if(char2 == 'r') { move = MoveType::carriageReturn; bothUsed = true; }
    }
    else if(char1 == '\n') move = MoveType::newline;
    else if(char1 == '\t') move = MoveType::tab;
    else if(char1 == '\r') move = MoveType::carriageReturn;

    return move;
}




uint16_t Label::getWordWidth(const char word[], uint16_t firstIndex, uint16_t stopIndex, bool progmem) {
    // All characters are assumed to be printable
    uint16_t width = 0;
    uint16_t i = firstIndex;
    while(i < stopIndex) {

        // get the character that should be printed
        const uint8_t* c;
        bool escapeSequence;
        if(progmem) {
            c = getPrintableChar(escapeSequence, pgm_read_byte(&(word[i])), (i < stopIndex ? pgm_read_byte(&(word[i+1])) : '\0'));
        }
        else {
            c = getPrintableChar(escapeSequence, word[i], (i < stopIndex ? word[i+1] : '\0'));
        }

        // get its width
        uint8_t length;
        font.readCharLenght(c, length);
        width += length;
        // Add the one byte space between letters
        width += 1;
        // Increase `i` by one or two if two characters were joined together
        if(escapeSequence) i++;
        i++;
    }
    return width;
}




bool Label::writeWord(const char word[], uint16_t firstIndex, uint16_t stopIndex, bool progmem, bool cutLastWord) {
    // All characters passed to this function are assumed to be printable.
    // If some non printable characters are found they will be print as
    // "unknown"

    // get word width
    const uint16_t width = getWordWidth(word, firstIndex, stopIndex, progmem);

    // check whether it is possible to print it and move the cursor if needed
    if(!cursor.prepare(width)) {
        if(!cutLastWord) return false;
        // The cursor didn't move. There could still be space for some
        // characters. The writeChar() function will take care of not printing
        // out of bounds.
    }


    uint16_t i = firstIndex;
    while(i < stopIndex) {
        // Get the printable character
        const uint8_t* c;
        bool escapeSequence;
        if(progmem) {
            c = getPrintableChar(escapeSequence, pgm_read_byte(&(word[i])), (i < stopIndex ? pgm_read_byte(&(word[i+1])) : '\0'));
        }
        else {
            c = getPrintableChar(escapeSequence, word[i], (i < stopIndex ? word[i+1] : '\0'));
        }
        if(!writeChar(c)) return false;

        // Go to next character
        if(escapeSequence) i++;
        i++;
    }
    return true;
}




bool Label::writeChar(const uint8_t * c) {

    // Get character
    uint8_t length;
    uint8_t data[font.maxWidth];
    font.readCharArray(c, length, data);

    if(!cursor.prepare(length)) return false;

    // Print character
    driver.writeData(frame.absolutePage(cursor.page), frame.absoluteColumn(cursor.column), data, length);

    if(!cursor.move(length)) return false;
    // Print one pixel space
    driver.writeData(frame.absolutePage(cursor.page), frame.absoluteColumn(cursor.column), 0x0);
    if(!cursor.move(1)) return false;

    return true;
}




// ### Printing of numbers ### //


bool Label::printInt(unsigned long n, uint8_t minWidth, uint8_t base, bool negative, bool leadingZeros) {
    // This function was taken from the Print class in the Arduino framework
    // and sligtly modified

    // dimension: 8*4 binary digits, minus sign/hex symbol, null character
    char buf[8 * sizeof(long) + 2 + 1];
    char *str = &buf[sizeof(buf) - 1];

    *str = '\0';

    // prevent crash if called with base == 1
    if (base < 2) base = 10;

    do {
        char c = n % base;
        n /= base;
        *--str = c < 10 ? c + '0' : c + 'A' - 10;
    } while(n);

    // add special symbols (- for negative numbers or 0x for exadecimal base)
    if(negative) *--str = '-';
    else if (base == 16) {
        *--str = 'x';
        *--str = '0';
    }

    // if needed add some spaces to reach the minimum width
    uint8_t width = &buf[sizeof(buf) - 1] - str;
    int8_t spaces = minWidth - width;
    while(spaces-- > 0) {
        if(leadingZeros) *--str = '0';
        // 0x0B is ascii vertical tab, interpredet by this class as a space as wide
        // as one digit
        else *--str = 0x0B;
    }

    return print(str);
}


bool Label::printFloat(double n, uint8_t fractDigits, uint8_t minIntDigits) {
    // Some parts of this functions were copied from the Print class in the
    // Arduino framework

    // dimension: minus sign, 10 digits in integral part, dot, 8 digits in
    // decimal part, null character, (arbitrarly) 4 spaces for alignment
    char buf[25];
    char *str = &buf[sizeof(buf) - 1];

    char *dotAddr = str; //used later for alignment

    *--str = '\0';

    // Handle invalid numbers
    // The two numbers for overflow are marked as "determined empirically" in
    // the Arduino Print library implementation
    if (isnan(n)) {*--str = 'n';*--str = 'a';*--str = 'n';}
    else if (isinf(n)) {*--str = 'f';*--str = 'n';*--str = 'i';}
    else if (n >  4294967040.0) {*--str = 'f';*--str = 'o';*--str = 'v';}
    else if (n <- 4294967040.0) {*--str = 'f';*--str = 'o';*--str = 'v';}

    // N is a valid number
    else {

        // Round correctly so that print(1.999, 2) prints as "2.00"
        double rounding = 0.5;
        for (uint8_t i = 0; i < fractDigits; ++i) rounding /= 10.0;
        n += rounding;

        // Extract the integer part of the number
        unsigned long intPart = (unsigned long)n;
        double rem = n - (double)intPart;

        // Extract digits from the remainder
        uint8_t actualFractDigits = 0;
        for(;actualFractDigits < fractDigits; actualFractDigits++) rem *= 10;
        // write in string
        do {
            char c = (unsigned long)rem % 10;
            rem /= 10;
            *--str = c + '0';
        } while(--actualFractDigits);

        // Print the decimal point, but only if there are digits beyond
        if (fractDigits > 0) {
            dotAddr = str;
            *--str = '.';
        }

        // count digits in intPart
        uint8_t intDigits = 0;
        for(uint8_t x = intPart; x /= 10; intDigits++);
        // write in string
        do {
            char c = intPart % 10;
            intPart /= 10;
            *--str = c + '0';
        } while(intPart);

        // Handle negative numbers
        if (n < 0.0)
        {
            *--str = '-';
            n = -n;
        }

    }

    // if needed add some spaces to reach the minimum width
    uint8_t width = dotAddr - str;
    int8_t spaces = minIntDigits - width + 1;
    // 0x0B is ascii vertical tab, interpredet by this class as a space as wide
    // as one digit
    if(spaces > 0) while(spaces--) *--str = 0x0B;
    // additional spaces if the number will be printed as a three letter code
    if(isnan(n) || isinf(n) || n >  4294967040.0 || n <- 4294967040.0)
    for(uint8_t i = 0; i < fractDigits; i++) *--str = 0x0B;

    return print(str);
}




// ### Frame ### //



Label::Frame::Frame(uint8_t width, uint8_t height, uint8_t xPos, uint8_t yPos) {
    // Dimension
    columns  = width;
    pages    = height;
    // Position
    colShift = xPos;
    pagShift = yPos;

    // settings
    infinite = false;
    infiniteEmptyLine = false;
}



bool Label::Frame::isInFrame(uint8_t relativeColumn, uint8_t relativePage) {
    return (relativeColumn < columns && relativePage < pages);
}


uint8_t Label::Frame::absoluteColumn(uint8_t relativeColumn) {
    return relativeColumn + colShift;
}
uint8_t Label::Frame::absolutePage(uint8_t relativePage) {
    return relativePage + pagShift;
}





// ### Cursor ### //



Label::Cursor::Cursor(Frame& frame, Label& label) :
frame(frame),
label(label)
{
    column = 0;
    page = 0;
}



bool Label::Cursor::prepare(uint8_t textWidth) {

    // The cursor is already out of frame
    if(page >= frame.pages || column >= frame.columns) return false;

    // there is enough space starting from current location, do nothing
    if(column + textWidth < frame.columns) return true;

    bool availableLine;
    if(page + 1 < frame.pages) availableLine = true;
    else if(frame.infinite) availableLine = true;
    else availableLine = false;

    // there isn't, try to move to next line but before doing it check if the
    // word would fit in an empty line.
    if(textWidth > frame.columns && availableLine) {
        // the word is too long to be written on a single page, but there are
        // enough pages to write it. Don't move to next line.
        return true;
    }
    if(availableLine) {
        // ok, there is another available line
        move(0xff, true);
        return true;
    }
    // no available page, don't move and return false
    return false;
}



bool Label::Cursor::move(uint8_t steps, bool stopAtNL) {
    // if needed go to another line
    while(column + steps >= frame.columns) {
        steps -= frame.columns - column;
        if(frame.infiniteEmptyLine) {
            uint8_t p = page;
            label.fill(0x00, 0, p + 2, 0xFF,  p + 2);
            label.fill(0x00, 0, p + 1, 0xFF,  p + 1);
            page = p + 1;
        }
        else page++;
        column = 0;
        // the cursor went past the last line
        if(page >= frame.pages) {
            if(frame.infinite) {
                if(frame.infiniteEmptyLine)  label.fill(0x00, 0, 1, 0xFF, 1);
                page = 0;
            }
            else return false;
        }
        // stopAtNL option
        if(stopAtNL) {
            return true;
        }
    }
    // now column + steps < totCol
    column += steps;
    return true;
}
