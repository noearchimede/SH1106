/*! @file Implementation of the PageFont character set with the graphical
description of all characters. */

#include "Characters.hpp"
#include <avr/pgmspace.h> // for PROGMEM



// Normal space.
static const PROGMEM uint8_t space [4] = { 3 , 0x00, 0x00, 0x00};
// This space is used by the number printing functions to align numbers.
// It mus be as wide as a digit (and all the digit must have the same width).
static const PROGMEM uint8_t largeSpace [6] = {5, 0x00, 0x00, 0x00, 0x00, 0x0};


// Generated with an Excel worksheet
static const PROGMEM uint8_t   a   [5] = { 4 , 0x24, 0x54, 0x54, 0x78};
static const PROGMEM uint8_t   b   [5] = { 4 , 0x7E, 0x44, 0x44, 0x38};
static const PROGMEM uint8_t   c   [5] = { 4 , 0x38, 0x44, 0x44, 0x44};
static const PROGMEM uint8_t   d   [5] = { 4 , 0x38, 0x44, 0x44, 0x7E};
static const PROGMEM uint8_t   e   [5] = { 4 , 0x38, 0x54, 0x54, 0x08};
static const PROGMEM uint8_t   f   [5] = { 4 , 0x08, 0x7C, 0xA, 0x02};
static const PROGMEM uint8_t   g   [5] = { 4 , 0x18, 0xA4, 0xA4, 0x7C};
static const PROGMEM uint8_t   h   [5] = { 4 , 0x7E, 0x04, 0x04, 0x78};
static const PROGMEM uint8_t   i   [2] = { 1 , 0x7D};
static const PROGMEM uint8_t   j   [3] = { 2 , 0x80, 0x7D};
static const PROGMEM uint8_t   k   [4] = { 3 , 0x7E, 0x10, 0x68};
static const PROGMEM uint8_t   l   [2] = { 1 , 0x7E};
static const PROGMEM uint8_t   m   [8] = { 7 , 0x7C, 0x04, 0x04, 0x78, 0x04, 0x04, 0x78};
static const PROGMEM uint8_t   n   [5] = { 4 , 0x7C, 0x04, 0x04, 0x78};
static const PROGMEM uint8_t   o   [5] = { 4 , 0x38, 0x44, 0x44, 0x38};
static const PROGMEM uint8_t   p   [5] = { 4 , 0xFC, 0x44, 0x44, 0x38};
static const PROGMEM uint8_t   q   [5] = { 4 , 0x38, 0x44, 0x44, 0xFC};
static const PROGMEM uint8_t   r   [4] = { 3 , 0x7C, 0x08, 0x04};
static const PROGMEM uint8_t   s   [4] = { 3 , 0x58, 0x54, 0x34};
static const PROGMEM uint8_t   t   [4] = { 3 , 0x04, 0x3E, 0x44};
static const PROGMEM uint8_t   u   [5] = { 4 , 0x3C, 0x40, 0x40, 0x7C};
static const PROGMEM uint8_t   v   [6] = { 5 , 0xC, 0x30, 0x40, 0x30, 0xC};
static const PROGMEM uint8_t   w   [6] = { 5 , 0x3C, 0x40, 0x20, 0x40, 0x3C};
static const PROGMEM uint8_t   x   [6] = { 5 , 0x44, 0x28, 0x10, 0x28, 0x44};
static const PROGMEM uint8_t   y   [5] = { 4 , 0xC, 0x50, 0x30, 0xC};
static const PROGMEM uint8_t   z   [5] = { 4 , 0x64, 0x54, 0x54, 0x4C};

static const PROGMEM uint8_t   A   [6] = { 5 , 0x7E, 0x09, 0x09, 0x09, 0x7E};
static const PROGMEM uint8_t   B   [5] = { 4 , 0x7F, 0x49, 0x49, 0x36};
static const PROGMEM uint8_t   C   [5] = { 4 , 0x3E, 0x41, 0x41, 0x41};
static const PROGMEM uint8_t   D   [5] = { 4 , 0x7F, 0x41, 0x22, 0x1C};
static const PROGMEM uint8_t   E   [5] = { 4 , 0x7F, 0x49, 0x49, 0x41};
static const PROGMEM uint8_t   F   [5] = { 4 , 0x7F, 0x05, 0x05, 0x01};
static const PROGMEM uint8_t   G   [6] = { 5 , 0x3E, 0x41, 0x49, 0x49, 0x39};
static const PROGMEM uint8_t   H   [6] = { 5 , 0x7F, 0x08, 0x08, 0x08, 0x7F};
static const PROGMEM uint8_t   I   [2] = { 1 , 0x7F};
static const PROGMEM uint8_t   J   [4] = { 3 , 0x60, 0x40, 0x7F};
static const PROGMEM uint8_t   K   [5] = { 4 , 0x7F, 0xC, 0x12, 0x61};
static const PROGMEM uint8_t   L   [5] = { 4 , 0x7F, 0x40, 0x40, 0x40};
static const PROGMEM uint8_t   M   [8] = { 7 , 0x7F, 0x02, 0x04, 0x08, 0x04, 0x02, 0x7F};
static const PROGMEM uint8_t   N   [7] = { 6 , 0x7F, 0x03, 0xE, 0x38, 0x60, 0x7F};
static const PROGMEM uint8_t   O   [6] = { 5 , 0x3E, 0x41, 0x41, 0x41, 0x3E};
static const PROGMEM uint8_t   P   [5] = { 4 , 0x7F, 0x09, 0x09, 0x06};
static const PROGMEM uint8_t   Q   [7] = { 6 , 0x3E, 0x41, 0x41, 0x51, 0x3E, 0x40};
static const PROGMEM uint8_t   R   [5] = { 4 , 0x7F, 0x09, 0x19, 0x66};
static const PROGMEM uint8_t   S   [5] = { 4 , 0x46, 0x49, 0x49, 0x31};
static const PROGMEM uint8_t   T   [6] = { 5 , 0x01, 0x01, 0x7F, 0x01, 0x01};
static const PROGMEM uint8_t   U   [6] = { 5 , 0x3F, 0x40, 0x40, 0x40, 0x3F};
static const PROGMEM uint8_t   V   [6] = { 5 , 0x07, 0x18, 0x20, 0x18, 0x07};
static const PROGMEM uint8_t   W   [8] = { 7 , 0x07, 0x18, 0x20, 0x10, 0x20, 0x18, 0x07};
static const PROGMEM uint8_t   X   [6] = { 5 , 0x63, 0x14, 0x08, 0x14, 0x63};
static const PROGMEM uint8_t   Y   [6] = { 5 , 0x03, 0x04, 0x78, 0x04, 0x03};
static const PROGMEM uint8_t   Z   [6] = { 5 , 0x61, 0x51, 0x49, 0x45, 0x43};

static const PROGMEM uint8_t   zero   [6] = { 5 , 0x3E, 0x41, 0x49, 0x41, 0x3E};
static const PROGMEM uint8_t   one   [6] = { 5 , 0x44, 0x42, 0x7F, 0x40, 0x40};
static const PROGMEM uint8_t   two   [6] = { 5 , 0x72, 0x51, 0x59, 0x4D, 0x46};
static const PROGMEM uint8_t   three   [6] = { 5 , 0x22, 0x41, 0x49, 0x49, 0x36};
static const PROGMEM uint8_t   four   [6] = { 5 , 0x18, 0x16, 0x11, 0x7F, 0x10};
static const PROGMEM uint8_t   five   [6] = { 5 , 0x4F, 0x49, 0x49, 0x49, 0x31};
static const PROGMEM uint8_t   six   [6] = { 5 , 0x3E, 0x49, 0x49, 0x49, 0x30};
static const PROGMEM uint8_t   seven   [6] = { 5 , 0x61, 0x11, 0x09, 0x05, 0x03};
static const PROGMEM uint8_t   eight   [6] = { 5 , 0x36, 0x49, 0x49, 0x49, 0x36};
static const PROGMEM uint8_t   nine   [6] = { 5 , 0x06, 0x49, 0x49, 0x49, 0x3E};

static const PROGMEM uint8_t   exclamation   [2] = { 1 , 0x9F};
static const PROGMEM uint8_t   quote   [4] = { 3 , 0x07, 0x00, 0x07};
static const PROGMEM uint8_t   hash   [6] = { 5 , 0x14, 0x7F, 0x14, 0x7F, 0x14};
static const PROGMEM uint8_t   dollar   [6] = { 5 , 0x48, 0x54, 0xFE, 0x54, 0x24};
static const PROGMEM uint8_t   percent   [6] = { 5 , 0x66, 0x36, 0x18, 0x6C, 0x66};
static const PROGMEM uint8_t   ampersand   [7] = { 6 , 0x34, 0x4A, 0x4A, 0x54, 0x20, 0x40};
static const PROGMEM uint8_t   apostrophe   [2] = { 1 , 0x07};
static const PROGMEM uint8_t   openParenthesis   [4] = { 3 , 0x1C, 0x22, 0x41};
static const PROGMEM uint8_t   closeParenthesis   [4] = { 3 , 0x41, 0x22, 0x1C};
static const PROGMEM uint8_t   asterix   [3] = { 2 , 0x18, 0x18};
static const PROGMEM uint8_t   plus   [6] = { 5 , 0x10, 0x10, 0x7C, 0x10, 0x10};
static const PROGMEM uint8_t   comma   [3] = { 2 , 0xC0, 0x60};
static const PROGMEM uint8_t   dash   [6] = { 5 , 0x10, 0x10, 0x10, 0x10, 0x10};
static const PROGMEM uint8_t   dot   [3] = { 2 , 0x60, 0x60};
static const PROGMEM uint8_t   slash   [4] = { 3 , 0x70, 0x1C, 0x07};
static const PROGMEM uint8_t   colon   [3] = { 2 , 0x6C, 0x6C};
static const PROGMEM uint8_t   semicolon   [3] = { 2 , 0xCC, 0x6C};
static const PROGMEM uint8_t   lessThan   [5] = { 4 , 0x10, 0x38, 0x6C, 0x44};
static const PROGMEM uint8_t   equals   [6] = { 5 , 0x28, 0x28, 0x28, 0x28, 0x28};
static const PROGMEM uint8_t   greatherThan   [5] = { 4 , 0x44, 0x6C, 0x38, 0x10};
static const PROGMEM uint8_t   question   [5] = { 4 , 0x02, 0x51, 0x09, 0x06};
static const PROGMEM uint8_t   at   [7] = { 6 , 0x3C, 0x42, 0x5A, 0x5A, 0x52, 0x1C};
static const PROGMEM uint8_t   openBracket   [3] = { 2 , 0x7F, 0x41};
static const PROGMEM uint8_t   closeBracket   [3] = { 2 , 0x41, 0x7F};
static const PROGMEM uint8_t   openBrace   [4] = { 3 , 0x08, 0x36, 0x41};
static const PROGMEM uint8_t   closeBrace   [4] = { 3 , 0x41, 0x36, 0x08};
static const PROGMEM uint8_t   backslash   [4] = { 3 , 0x07, 0x1C, 0x70};
static const PROGMEM uint8_t   hat   [6] = { 5 , 0x04, 0x02, 0x01, 0x02, 0x04};
static const PROGMEM uint8_t   underscore   [6] = { 5 , 0x40, 0x40, 0x40, 0x40, 0x40};
static const PROGMEM uint8_t   accent   [3] = { 2 , 0x01, 0x02};
static const PROGMEM uint8_t   bar   [2] = { 1 , 0xFF};
static const PROGMEM uint8_t   tilde   [6] = { 5 , 0x10, 0x08, 0x10, 0x20, 0x10};

static const PROGMEM uint8_t   accentedA   [5] = { 4 , 0x20, 0x55, 0x55, 0x39};
static const PROGMEM uint8_t   accentedE   [5] = { 4 , 0x38, 0x55, 0x55, 0x09};
static const PROGMEM uint8_t   accentedO   [6] = { 5 , 0x38, 0x45, 0x45, 0x45, 0x38};
static const PROGMEM uint8_t   accentedI   [4] = { 3 , 0x00, 0x7D, 0x01};
static const PROGMEM uint8_t   accentedU   [6] = { 5 , 0x00, 0x3C, 0x41, 0x41, 0x7D};
static const PROGMEM uint8_t   degree   [5] = { 4 , 0x06, 0x09, 0x09, 0x06};
static const PROGMEM uint8_t   arrowUp   [8] = { 7 , 0x08, 0x04, 0x02, 0x7F, 0x02, 0x04, 0x08};
static const PROGMEM uint8_t   arrowDown   [8] = { 7 , 0x10, 0x20, 0x40, 0xFE, 0x40, 0x20, 0x10};
static const PROGMEM uint8_t   arrowLeft   [8] = { 7 , 0x10, 0x38, 0x54, 0x92, 0x10, 0x10, 0x10};
static const PROGMEM uint8_t   arrowRight   [8] = { 7 , 0x10, 0x10, 0x10, 0x92, 0x54, 0x38, 0x10};
static const PROGMEM uint8_t   arrowUpRight   [7] = { 6 , 0x40, 0x20, 0x12, 0xA, 0x06, 0x1E};
static const PROGMEM uint8_t   arrowDownRight   [7] = { 6 , 0x02, 0x04, 0x48, 0x50, 0x60, 0x78};
static const PROGMEM uint8_t   arrowDownLeft   [7] = { 6 , 0x78, 0x60, 0x50, 0x48, 0x04, 0x02};
static const PROGMEM uint8_t   arrowUpLeft   [7] = { 6 , 0x1E, 0x06, 0xA, 0x12, 0x20, 0x40};
static const PROGMEM uint8_t   copyright   [7] = { 6 , 0x7C, 0x82, 0xBA, 0xAA, 0x82, 0x7C};
static const PROGMEM uint8_t   unknown   [4] = { 3 , 0x3E, 0x3E, 0x3E};
static const PROGMEM uint8_t   expZero   [4] = { 3 , 0xE, 0x11, 0xE};
static const PROGMEM uint8_t   expOne   [4] = { 3 , 0x02, 0x01, 0x1F};
static const PROGMEM uint8_t   expTwo   [4] = { 3 , 0x19, 0x15, 0x12};
static const PROGMEM uint8_t   expThree   [4] = { 3 , 0x11, 0x15, 0xA};
static const PROGMEM uint8_t   expFour   [4] = { 3 , 0xC, 0xA, 0x1D};
static const PROGMEM uint8_t   expFive   [4] = { 3 , 0x17, 0x15, 0x09};
static const PROGMEM uint8_t   expSix   [4] = { 3 , 0x1E, 0x15, 0x1D};
static const PROGMEM uint8_t   expSeven   [4] = { 3 , 0x19, 0x05, 0x03};
static const PROGMEM uint8_t   expEight   [4] = { 3 , 0x1B, 0x15, 0x1B};
static const PROGMEM uint8_t   expNine   [4] = { 3 , 0x17, 0x15, 0xF};





// ######### PageFont class implementation #########



void PageFont::readCharArray(const uint8_t * ptr, uint8_t &length, uint8_t *data) {
    length = pgm_read_byte(ptr);
    for(uint8_t i = 0; i < length; i++) data[i] = pgm_read_byte(ptr + 1 + i);
}

void PageFont::readCharLenght(const uint8_t * ptr, uint8_t &length) {
    length = pgm_read_byte(ptr);
}




const uint8_t * PageFont::getAscii(char character)  {

    switch (character) {

        case ' ':  return space;                  // 0x20
        case '!':  return exclamation;            // 0x21
        case '"':  return quote;                  // 0x22
        case '#':  return hash;                   // 0x23
        case '$':  return dollar;                 // 0x24
        case '%':  return percent;                // 0x25
        case '&':  return ampersand;              // 0x26
        case '\'': return apostrophe;             // 0x27
        case '(':  return openParenthesis;        // 0x28
        case ')':  return closeParenthesis;       // 0x29
        case '*':  return asterix;                // 0x2A
        case '+':  return plus;                   // 0x2B
        case ',':  return comma;                  // 0x2C
        case '-':  return dash;                   // 0x2D
        case '.':  return dot;                    // 0x2E
        case '/':  return slash;                  // 0x2F
        case '0':  return zero;                   // 0x30
        case '1':  return one;                    // 0x31
        case '2':  return two;                    // 0x32
        case '3':  return three;                  // 0x33
        case '4':  return four;                   // 0x34
        case '5':  return five;                   // 0x35
        case '6':  return six;                    // 0x36
        case '7':  return seven;                  // 0x37
        case '8':  return eight;                  // 0x38
        case '9':  return nine;                   // 0x39
        case ':':  return colon;                  // 0x3A
        case ';':  return semicolon;              // 0x3B
        case '<':  return greatherThan;           // 0x3C
        case '=':  return equals;                 // 0x3D
        case '>':  return lessThan;               // 0x3E
        case '?':  return question;               // 0x3F
        case '@':  return at;                     // 0x40
        case 'A':  return A;                      // 0x41
        case 'B':  return B;                      // 0x42
        case 'C':  return C;                      // 0x43
        case 'D':  return D;                      // 0x44
        case 'E':  return E;                      // 0x45
        case 'F':  return F;                      // 0x46
        case 'G':  return G;                      // 0x47
        case 'H':  return H;                      // 0x48
        case 'I':  return I;                      // 0x49
        case 'J':  return J;                      // 0x4A
        case 'K':  return K;                      // 0x4B
        case 'L':  return L;                      // 0x4C
        case 'M':  return M;                      // 0x4D
        case 'N':  return N;                      // 0x4E
        case 'O':  return O;                      // 0x4F
        case 'P':  return P;                      // 0x50
        case 'Q':  return Q;                      // 0x51
        case 'R':  return R;                      // 0x52
        case 'S':  return S;                      // 0x53
        case 'T':  return T;                      // 0x54
        case 'U':  return U;                      // 0x55
        case 'V':  return V;                      // 0x56
        case 'W':  return W;                      // 0x57
        case 'X':  return X;                      // 0x58
        case 'Y':  return Y;                      // 0x59
        case 'Z':  return Z;                      // 0x5A
        case '[':  return openBracket;            // 0x5B
        case '\\': return backslash;              // 0x5C
        case ']':  return closeBracket;           // 0x5D
        case '^':  return hat;                    // 0x5E
        case '_':  return underscore;             // 0x5F
        case '`':  return accent;                 // 0x60
        case 'a':  return a;                      // 0x61
        case 'b':  return b;                      // 0x62
        case 'c':  return c;                      // 0x63
        case 'd':  return d;                      // 0x64
        case 'e':  return e;                      // 0x65
        case 'f':  return f;                      // 0x66
        case 'g':  return g;                      // 0x67
        case 'h':  return h;                      // 0x68
        case 'i':  return i;                      // 0x69
        case 'j':  return j;                      // 0x6A
        case 'k':  return k;                      // 0x6B
        case 'l':  return l;                      // 0x6C
        case 'm':  return m;                      // 0x6D
        case 'n':  return n;                      // 0x6E
        case 'o':  return o;                      // 0x6F
        case 'p':  return p;                      // 0x70
        case 'q':  return q;                      // 0x71
        case 'r':  return r;                      // 0x72
        case 's':  return s;                      // 0x73
        case 't':  return t;                      // 0x74
        case 'u':  return u;                      // 0x75
        case 'v':  return v;                      // 0x76
        case 'w':  return w;                      // 0x77
        case 'x':  return x;                      // 0x78
        case 'y':  return y;                      // 0x79
        case 'z':  return z;                      // 0x7A
        case '{':  return openBrace;              // 0x7B
        case '|':  return bar;                    // 0x7C
        case '}':  return closeBrace;             // 0x7D
        case '~':  return tilde;                  // 0x7E

        default: return unknown;
    }
}




const uint8_t * PageFont::getUnknown() {
    return   unknown;
}

const uint8_t * PageFont::getAccentedVowel(char vowel) {
    switch(vowel) {
        case 'a': return   accentedA;
        case 'e': return   accentedE;
        case 'i': return   accentedI;
        case 'o': return   accentedO;
        case 'u': return   accentedU;

        default:  return   unknown;
    }
}

const uint8_t * PageFont::getArrow(unsigned int clockWise8Steps) {
    switch(clockWise8Steps) {
        case 0: return   arrowUp;
        case 1: return   arrowUpRight;
        case 2: return   arrowRight;
        case 3: return   arrowDownRight;
        case 4: return   arrowDown;
        case 5: return   arrowDownLeft;
        case 6: return   arrowLeft;
        case 7: return   arrowUpLeft;

        default: return   unknown;
    }

}

const uint8_t * PageFont::getExpDigit(unsigned int digit) {
    switch(digit) {
        case 0: return   expZero;
        case 1: return   expOne;
        case 2: return   expTwo;
        case 3: return   expThree;
        case 4: return   expFour;
        case 5: return   expFive;
        case 6: return   expSix;
        case 7: return   expSeven;
        case 8: return   expEight;
        case 9: return   expNine;

        default: return   unknown;
    }

}

const uint8_t * PageFont::getSpecialChar(PageFont::SpecialChar name) {
    switch(name) {
        case SpecialChar::copyright: return copyright;
        case SpecialChar::degree:    return degree;
        case SpecialChar::unknown:   return unknown;
        case SpecialChar::largeSpace: return largeSpace;
        default: return unknown;
    }
}
