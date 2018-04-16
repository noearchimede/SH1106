
#include "SH1106.h"

/*! @fle Implementation of the SH1106 class
*/

SH1106_label::SH1106_label(SH1106_driver& driver, uint8_t pages, uint8_t columns, uint8_t startPage, uint8_t startColumn)
:
width(columns),
height(pages),
cursor(pages, columns, startPage, startColumn),
driver(driver)
{
}



void SH1106_label::writeArray(uint8_t page, uint8_t column, uint8_t data [], uint8_t length) {
    cursor.setPage(page);
    cursor.setColumn(column);
    if(!cursor.isOutOfBounds())
    driver.writeData(cursor.getAbsolutePage(), cursor.getAbsoluteColumn(), data, length);
    cursor.move(length, true);
}



// #### TEXT WRITING #### //


bool SH1106_label::newline() {
    return cursor.newline();
}

void SH1106_label::tab(uint8_t anchor) {
    constexpr uint8_t defaultTab = 25;

    uint8_t x = defaultTab - (cursor.getColumn() % defaultTab);

    for(int i = 0; i < x; i++) {
        if(!cursor.isOutOfBounds())
        driver.writeData(cursor.getAbsolutePage(), cursor.getAbsoluteColumn(), 0x0);
    }
    cursor.move(x, true);
}


void SH1106_label::space() {
    writeChar(font.getAscii(' '));
}



void SH1106_label::clear() {
    fillRange(0x00, 0,0,height - 1, width - 1);
}


void SH1106_label::clearPage() {
    fillRange(0x00, cursor.getPage(), 0, cursor.getPage(), width - 1);
}


void SH1106_label::fillRange(uint8_t content, uint8_t startPag, uint8_t startCol, uint8_t endPag, uint8_t endCol) {

    // if the end is 0,0 replace it with the end of the label
    if(endPag == 0 && endCol == 0) {
        endPag = height - 1;
        endCol = width - 1;
    }

    // if the range is "negative" return
    if(endPag < startPag) return;
    else if(endPag == startPag) {
        if(endCol < startCol) return;
    }

    // clear (part of) the first line
    cursor.setPage(startPag);
    for(int i = startCol; i < width; i++) {
        cursor.setColumn(i);
        if(!cursor.isOutOfBounds())
        driver.writeData(cursor.getAbsolutePage(), cursor.getAbsoluteColumn(), content);
    }
    // clear intermediate line
    for(int k = startPag + 1; k < endPag; k++) {
        cursor.setPage(k);
        for(int i = 0; i < width; i++) {
            cursor.setColumn(i);
            if(!cursor.isOutOfBounds())
            driver.writeData(cursor.getAbsolutePage(), cursor.getAbsoluteColumn(), content);
        }
    }
    // clear (part of) the last line
    cursor.setPage(endPag);
    for(int i = 0; i <= endCol; i++) {
        cursor.setColumn(i);
        if(!cursor.isOutOfBounds())
        driver.writeData(cursor.getAbsolutePage(), cursor.getAbsoluteColumn(), content);
    }
}

// ### Character drawing functions ### //


bool SH1106_label::writeChar(PageFont::Char8Bytes c, bool cut) {

    uint8_t length = c.length;

    // check wheter there is enough space for this character in this frame
    // and if needed and possible place the cursor on the next line
    //
    // If the character is "cuttable", this is not needed
    if(!cut) {
        if(!cursor.prepare(c.length)) {
            return false;
        }
    }
    else {
        if(cursor.remainingColumns() < length)
        length = cursor.remainingColumns();
    }

    // Write the character
    if(!cursor.isOutOfBounds())
    driver.writeData(cursor.getAbsolutePage(), cursor.getAbsoluteColumn(), c.data, c.length);
    // Save the current page
    uint8_t page = cursor.getPage();
    // Move the cursor
    cursor.move(c.length, true);

    // Write an intracharacterial space if the cursor didn't change line
    if(page == cursor.getPage()) {
        if(!cursor.isOutOfBounds())
        driver.writeData(cursor.getAbsolutePage(), cursor.getAbsoluteColumn(), 0x0);
        cursor.move(1, true);
    }

    return true;
}


bool SH1106_label::writeAscii(char character) {
    // characthers which may be cut if there isn't enough space on current line
    if(character == ' ') {
        return writeChar(font.getAscii(character), true);
    }
    // normal characters wich must always be entierly written
    return writeChar(font.getAscii(character));
}

bool SH1106_label::writeAccentedVowel(char letter) {
    return writeChar(font.getAccentedVowel(letter));
}


bool SH1106_label::writeArrow8StepCW(uint8_t direction) {
    return writeChar(font.getArrow(direction));
}

bool SH1106_label::writeExpDigit(uint8_t digit) {
    return writeChar(font.getExpDigit(digit));
}

bool SH1106_label::writeCopyright() {
    return writeChar(font.getSpecialChar(PageFont::SpecialChar::copyright));
}

bool SH1106_label::writeDegree() {
    return writeChar(font.getSpecialChar(PageFont::SpecialChar::degree));
}

bool SH1106_label::writeUnknown() {
    return writeChar(font.getSpecialChar(PageFont::SpecialChar::unknown));
}





// ### Public method to move cursor ####

void SH1106_label::setCursor(uint8_t page, uint8_t column, bool useNextLine) {
    cursor.setPage(page);
    cursor.setColumn(column);
    cursor.setMode(useNextLine);
}



// ### Cursor (private) ### //


SH1106_label::Cursor::Cursor(uint8_t pages, uint8_t columns, uint8_t pagShift, uint8_t colShift) :
totPag(pages),
totCol(columns),
pagShift(pagShift),
colShift(colShift)
{
    col = 0;
    pag = 0;
    useNL = true;
}

void SH1106_label::Cursor::setPage(uint8_t page)     { pag = page; }
void SH1106_label::Cursor::setColumn(uint8_t column) { col = column; }
void SH1106_label::Cursor::setMode(bool useNextPage) { useNL = useNextPage; }

uint8_t SH1106_label::Cursor::getPage()   { return pag; }
uint8_t SH1106_label::Cursor::getColumn() { return col; }

bool SH1106_label::Cursor::getMode()  {return useNL; }

uint8_t SH1106_label::Cursor::getAbsolutePage()   { return (pag + pagShift); }
uint8_t SH1106_label::Cursor::getAbsoluteColumn() { return (col + colShift); }

bool SH1106_label::Cursor::isOutOfBounds() {
    if(pag >= totPag || col >= totCol) return true;
    return false;
}

uint8_t SH1106_label::Cursor::remainingColumns() {
    return totCol - col;
}

bool SH1106_label::Cursor::prepare(unsigned int columns) {
    // there is enough space starting from current location
    if(col + columns < totCol) return true;
    // there isn't
    if(useNL) {
        // the cursor must be moved on next line
        if(pag + 1 < totPag) {
            // ok, there is another available line
            pag++;
            col = 0;
            return true;
        }
    }
    // no available page, stay on current location and return false
    return false;
}


bool SH1106_label::Cursor::move(int columns, bool stopAtNL) {
    // move forwards
    if(columns > 0) {
        if(useNL) {
            while(col + columns >= totCol) {
                // we need to switch to next line
                columns -= totCol-1 - col;
                pag++;
                col = 0;
                // return false if the cursor went past the last line
                if(pag >= totPag) return false;

                // if the stopAtNL option is enabled
                if(stopAtNL) {
                    col = 0;
                    return true;
                }
            }
            // col + addColumns < totCol
            col += columns;
            return true;
        }
        else {
            if(col + columns < totCol) {
                col += totCol;
                return true;
            }
            else {
                // remember: the `totCol` number used as index is out of bounds
                col = totCol;
                return false;
            }
        }
    }

    // move backwards
    else if (columns < 0) {
        if(useNL) {
            while(col < columns) {
                // we need to switch to previous line
                columns -= (col + 1);
                if(pag != 0) pag--;
                col = totCol - 1;
            }
            // col >= subtractColumns
            col -= columns;
        }
        else {
            if(col >= columns) col -= columns;
            else col = 0;
        }
        // backward movenet always returns true, as it can't go lead of bounds.
        return true;
    }

    // never happens
    return false;
}


bool SH1106_label::Cursor::newline() {
    pag++;
    col = 0;
    if(pag < totPag) return true;
    else return false; //cursor is out of bounds
}
