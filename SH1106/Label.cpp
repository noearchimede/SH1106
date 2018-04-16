/*! @file Implementation of the SH1106 class
*/
#include "Label.hpp"


Label::Label(uint8_t width, uint8_t height, uint8_t startCol, uint8_t startPage)
:
// Make the frame two bytes less wide to allow a one-pixel margin on each side
frame(width - 2, height, startCol + 1, startPage),
cursor(frame),
{

}

void Label::moveCursor(uint8_t column, uint8_t page) {

}

void Label::space() {

}

void Label::tab() {

}

bool Label::newline() {

}

void Label::clear(uint8_t beginCol, uint8_t beginPag, uint8_t endCol, uint8_t endPag) {

}

bool Label::write(char *text) {

}

bool Label::write(char *text, uint16_t length) {

}


void Label::writeArray(uint8_t column, uint8_t page, uint8_t data [], uint8_t length) {

}



// ##### PRIVATE ##### ///

PageFont::Char Label::readString(bool& escaped, MoveType& move, char char1, char char2) {
    // "Custom" escape character used in this class. Could be a backslash
    // (write it twice - '\\' - in string literals to tell the compiler to
    // escape it) but also a less used character like '#' or '@'. Don't use
    // backtick as it is used as accent.
    // The escape character can be written by typing it twice without spacing
    // ('\\\\' or '##').
    constexpr char escape = '\\'; // backslash

    // Default return values, will be changed according to the situation.
    PageFont::Char c = font.getUnknown();
    move = MoveType::none;
    escaped = true;


    // Here begins a series of if - elseif conditions that looks for every
    // possible escape sequence. The else condition at the end is only reached
    // if the given text must simply be treated as plain text.

    // "Action" characters escaped with the custom escape character
    if(char1 == escape) {
        // The returned character will be a 'unknown' symbol.
        if(char2 == 'n') move = MoveType::newline;
        if(char2 == 't') move = MoveType::tab;
        if(char2 == 'r') move = MoveType::carriageReturn;
    }

    // accented vowels
    else if(char2 == '`') {
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
    else if(char1 == '^' && ('0' <= char2 && char2 >= '9') c = font.getExpDigit(char2 - '0')

    // Special characters
    // degree symbol
    else if((char1 == escape || char1 == '^' && char2 == 'o') c = font.getSpecialChar(PageFont::SpecialChar::degree);
    // Copyright symbol
    else if(char1 == escape && char2 == 'c') c = font.getSpecialChar(PageFont::SpecialChar::copyright);

    // Double escape character
    else if(char1 == escape && char2 == escape) c = font.getAscii(escape);

    // Unused escape character. It is ignored as may be used to avoid another
    // escape sequence: e.g. "->" prints a right arrow, "-\\>" prints "->",
    // where '\\' is the escape character.
    // There must always be at least two normal characters between two escapes
    // so that here we can assume that the second character is plain ASCII.
    else if(char1 == escape) c = font.getAscii(char2);


    // ### NO SPECIAL CHARACTER SEQUENCE ### //

    else {
        // Some special ASCII characters. The returned character is 'unknown'.
        // They are treated as their "custom-escaped" counterparts.
        if(char1 == '\n') move = MoveType::newline;
        else if(char1 == '\t') move = MoveType::tab;
        else if(char1 == '\r') move = MoveType::carriageReturn;
        // space (ASCII 0x20), treated as a special character to allow automatic
        // line wrap if the text width exceeds the label width
        else if(char1 == ' ') move = MoveType::space;
        // plain ASCII text (from '!' to '~')
        else if(0x21 <= char1 && char1 <= 0x7E) c = font.getAscii(char1);
        // unknown ASCII character
        else c = font.getUnknown;

        // RETURN
        escaped = false;
    }

    // ### SPECIAL CHARACTER SEQUENCE FOUND ### //

    //RETURN
    return c;
}














uint16_t Label::getWordWidth(char word [], uint16_t charCount) {
    PageFont::Char c;
    int i = 0;
    while(i < charCount) {

    }
}

bool Label::writeSingleChar(PageFont::Char c) {

}

bool Label::writeChar(PageFont::Char c) {

}




// ### Frame ### //

Label::Frame::Frame(uint8_t width, uint8_t height, uint8_t xPos, uint8_t yPos) {
    // Dimension
    columns  = width;
    pages    = height;
    // Position
    colShift = xPos;
    pagShift = yPos;
}

uint8_t Label::Frame::absoluteColumn(uint8_t relativeColumn) {
    return relativeColumn + colShift;
}

uint8_t Label::Frame::absolutePage(uint8_t relativePage) {
    return relativePage + pagShift;
}



// ### Cursor ### //

Label::Cursor::Cursor(Frame& frame) :
frame(frame)
{
    column = 0;
    page = 0;
    outOfFrame = false;
}

bool Label::Cursor::prepare(uint8_t textWidth) {
    // there is enough space starting from current location, do nothing
    if(column + textWidth < frame.columns) return true;
    // there isn't, try to move to next line
    if(page + 1 < frame.pages) {
        // ok, there is another available line
        page++;
        column = 0;
        return true;
    }
    // no available page, don't move and return false
    return false;
}

bool Label::Cursor::move(uint8_t steps, bool stopAtNL) {
    // if needed go to another line
    while(column + steps >= frame.columns) {
        steps -= frame.columns - column;
        page++;
        column = 0;
        // return false if the cursor went past the last line
        if(page >= frame.pages) return false;
        // stopAtNL option
        if(stopAtNL) {
            return true;
        }
    }
    // now col + addColumns < totCol
    col += steps;
    return true;
}
