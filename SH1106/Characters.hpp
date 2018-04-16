/*! @file This file contains the graphical definition of the most importand ASCII StoredChars. */

#include <inttypes.h>
#include <Arduino.h> // for PROGMEM

//! Definition of a set of StoredChars designed to fit an 8-bit page
struct PageFont {

    // All bitmap data of this class is stored in this struct
    template <int N>
    struct StoredChar {
        const uint8_t length;
        const uint8_t data[N];
    };

    // Characters of any width can be exported with this class
    struct Char {

        // Constructor called by the user when he wants to get a StoredChar
        Char() {};

        // Constructors called within this class to convert StoredChar to Char
        Char(StoredChar<0> c) {
            length = 0; for(int i = 0; i < 0; i++) data[i] = c.data[i];
        };
        Char(StoredChar<1> c) {
            length = 1; for(int i = 0; i < 1; i++) data[i] = c.data[i];
        };
        Char(StoredChar<2> c) {
            length = 2; for(int i = 0; i < 2; i++) data[i] = c.data[i];
        };
        Char(StoredChar<3> c) {
            length = 3; for(int i = 0; i < 3; i++) data[i] = c.data[i];
        };
        Char(StoredChar<4> c) {
            length = 4; for(int i = 0; i < 4; i++) data[i] = c.data[i];
        };
        Char(StoredChar<5> c) {
            length = 5; for(int i = 0; i < 5; i++) data[i] = c.data[i];
        };
        Char(StoredChar<6> c) {
            length = 6; for(int i = 0; i < 6; i++) data[i] = c.data[i];
        };
        Char(StoredChar<7> c) {
            length = 7; for(int i = 0; i < 7; i++) data[i] = c.data[i];
        };
        Char(StoredChar<8> c) {
            length = 8; for(int i = 0; i < 8; i++) data[i] = c.data[i];
        };

        uint8_t length;
        uint8_t data[8];
    };

    Char getUnknown() {
        return Char(unknown);
    }

    Char getAccentedVowel(char vowel) {
        switch(vowel) {
            case 'a': return Char(accentedA);
            case 'e': return Char(accentedE);
            case 'i': return Char(accentedI);
            case 'o': return Char(accentedO);
            case 'u': return Char(accentedU);
            default:  return Char(unknown);
        }
    }

    Char getArrow(unsigned int clockWise8Steps) {
        switch(clockWise8Steps) {
            case 0: return Char(arrowUp);
            case 1: return Char(arrowUpRight);
            case 2: return Char(arrowRight);
            case 3: return Char(arrowDownRight);
            case 4: return Char(arrowDown);
            case 5: return Char(arrowDownLeft);
            case 6: return Char(arrowLeft);
            case 7: return Char(arrowUpLeft);
            default: return Char(unknown);
        }

    }

    Char getExpDigit(unsigned int digit) {
        switch(digit) {
            case 0: return Char(expZero);
            case 1: return Char(expOne);
            case 2: return Char(expTwo);
            case 3: return Char(expThree);
            case 4: return Char(expFour);
            case 5: return Char(expFive);
            case 6: return Char(expSix);
            case 7: return Char(expSeven);
            case 8: return Char(expEight);
            case 9: return Char(expNine);
            default: return Char(unknown);
        }

    }

    enum class SpecialChar {copyright, degree, unknown};
    Char getSpecialChar(SpecialChar name) {
        switch(name) {
            case SpecialChar::copyright: return Char(copyright);
            case SpecialChar::degree:    return Char(degree);
            case SpecialChar::unknown:   return Char(unknown);
            default: return Char(unknown);
        }
    }



    // Lookup table function for ASCII StoredChars from 0x20 to 0x7E
    Char getAscii(char StoredChar) {

        switch (StoredChar) {

            case ' ':  return Char(space);                  // 0x20
            case '!':  return Char(exclamation);           	// 0x21
            case '"':  return Char(quote);                 	// 0x22
            case '#':  return Char(hash);                   // 0x23
            case '$':  return Char(dollar);                 // 0x24
            case '%':  return Char(percent);                // 0x25
            case '&':  return Char(ampersand);              // 0x26
            case '\'': return Char(apostrophe);             // 0x27
            case '(':  return Char(openParenthesis);        // 0x28
            case ')':  return Char(closeParenthesis);       // 0x29
            case '*':  return Char(asterix);                // 0x2A
            case '+':  return Char(plus);                   // 0x2B
            case ',':  return Char(comma);                  // 0x2C
            case '-':  return Char(dash);                   // 0x2D
            case '.':  return Char(dot);                    // 0x2E
            case '/':  return Char(slash);                  // 0x2F
            case '0':  return Char(zero);                  	// 0x30
            case '1':  return Char(one);                    // 0x31
            case '2':  return Char(two);                    // 0x32
            case '3':  return Char(three);                  // 0x33
            case '4':  return Char(four);                   // 0x34
            case '5':  return Char(five);                   // 0x35
            case '6':  return Char(six);                    // 0x36
            case '7':  return Char(seven);                  // 0x37
            case '8':  return Char(eight);                 	// 0x38
            case '9':  return Char(nine);                   // 0x39
            case ':':  return Char(colon);                 	// 0x3A
            case ';':  return Char(semicolon);              // 0x3B
            case '<':  return Char(greatherThan);           // 0x3C
            case '=':  return Char(equals);                 // 0x3D
            case '>':  return Char(lessThan);               // 0x3E
            case '?':  return Char(question);               // 0x3F
            case '@':  return Char(at);                    	// 0x40
            case 'A':  return Char(A);                    	// 0x41
            case 'B':  return Char(B);                    	// 0x42
            case 'C':  return Char(C);                    	// 0x43
            case 'D':  return Char(D);                    	// 0x44
            case 'E':  return Char(E);                    	// 0x45
            case 'F':  return Char(F);                    	// 0x46
            case 'G':  return Char(G);                    	// 0x47
            case 'H':  return Char(H);                    	// 0x48
            case 'I':  return Char(I);                    	// 0x49
            case 'J':  return Char(J);                    	// 0x4A
            case 'K':  return Char(K);                    	// 0x4B
            case 'L':  return Char(L);                    	// 0x4C
            case 'M':  return Char(M);                    	// 0x4D
            case 'N':  return Char(N);                    	// 0x4E
            case 'O':  return Char(O);                    	// 0x4F
            case 'P':  return Char(P);                    	// 0x50
            case 'Q':  return Char(Q);                    	// 0x51
            case 'R':  return Char(R);                    	// 0x52
            case 'S':  return Char(S);                    	// 0x53
            case 'T':  return Char(T);                    	// 0x54
            case 'U':  return Char(U);                    	// 0x55
            case 'V':  return Char(V);                    	// 0x56
            case 'W':  return Char(W);                    	// 0x57
            case 'X':  return Char(X);                    	// 0x58
            case 'Y':  return Char(Y);                    	// 0x59
            case 'Z':  return Char(Z);                    	// 0x5A
            case '[':  return Char(openBracket);         	// 0x5B
            case '\\': return Char(backslash);              // 0x5C
            case ']':  return Char(closeBracket);           // 0x5D
            case '^':  return Char(hat);                    // 0x5E
            case '_':  return Char(underscore);             // 0x5F
            case '`':  return Char(accent);                	// 0x60
            case 'a':  return Char(a);                    	// 0x61
            case 'b':  return Char(b);                    	// 0x62
            case 'c':  return Char(c);                    	// 0x63
            case 'd':  return Char(d);                    	// 0x64
            case 'e':  return Char(e);                    	// 0x65
            case 'f':  return Char(f);                    	// 0x66
            case 'g':  return Char(g);                    	// 0x67
            case 'h':  return Char(h);                    	// 0x68
            case 'i':  return Char(i);                    	// 0x69
            case 'j':  return Char(j);                    	// 0x6A
            case 'k':  return Char(k);                    	// 0x6B
            case 'l':  return Char(l);                    	// 0x6C
            case 'm':  return Char(m);                    	// 0x6D
            case 'n':  return Char(n);                    	// 0x6E
            case 'o':  return Char(o);                    	// 0x6F
            case 'p':  return Char(p);                    	// 0x70
            case 'q':  return Char(q);                    	// 0x71
            case 'r':  return Char(r);                    	// 0x72
            case 's':  return Char(s);                    	// 0x73
            case 't':  return Char(t);                    	// 0x74
            case 'u':  return Char(u);                    	// 0x75
            case 'v':  return Char(v);                    	// 0x76
            case 'w':  return Char(w);                    	// 0x77
            case 'x':  return Char(x);                    	// 0x78
            case 'y':  return Char(y);                    	// 0x79
            case 'z':  return Char(z);                    	// 0x7A
            case '{':  return Char(openBrace);              // 0x7B
            case '|':  return Char(bar);                 	// 0x7C
            case '}':  return Char(closeBrace);             // 0x7D
            case '~':  return Char(tilde);                 	// 0x7E

            default: return Char(unknown);
        }
    }


    
    StoredChar<4>  space = { 4 , {0x00, 0x00, 0x00, 0x00}};

    // Generated with an Excel table
    StoredChar<4>  a = { 4 , {0x20, 0x54, 0x54, 0x38}};
    StoredChar<4>  b = { 4 , {0x7E, 0x48, 0x48, 0x30}};
    StoredChar<3>  c = { 3 , {0x38, 0x44, 0x44}};
    StoredChar<4>  d = { 4 , {0x30, 0x48, 0x48, 0x7E}};
    StoredChar<4>  e = { 4 , {0x38, 0x54, 0x54, 0x08}};
    StoredChar<4>  f = { 4 , {0x08, 0x7C, 0xA, 0x02}};
    StoredChar<4>  g = { 4 , {0x18, 0xA4, 0xA4, 0x7C}};
    StoredChar<4>  h = { 4 , {0x7E, 0x08, 0x08, 0x70}};
    StoredChar<1>  i = { 1 , {0x7A}};
    StoredChar<2>  j = { 2 , {0x80, 0x7A}};
    StoredChar<3>  k = { 3 , {0x7E, 0x10, 0x68}};
    StoredChar<1>  l = { 1 , {0x7E}};
    StoredChar<7>  m = { 7 , {0x7C, 0x04, 0x04, 0x78, 0x04, 0x04, 0x78}};
    StoredChar<4>  n = { 4 , {0x7C, 0x04, 0x04, 0x78}};
    StoredChar<5>  o = { 5 , {0x38, 0x44, 0x44, 0x44, 0x38}};
    StoredChar<4>  p = { 4 , {0xFC, 0x24, 0x24, 0x18}};
    StoredChar<4>  q = { 4 , {0x18, 0x24, 0x24, 0xFC}};
    StoredChar<3>  r = { 3 , {0x7C, 0x08, 0x04}};
    StoredChar<3>  s = { 3 , {0x58, 0x54, 0x34}};
    StoredChar<3>  t = { 3 , {0x04, 0x3E, 0x44}};
    StoredChar<4>  u = { 4 , {0x3C, 0x40, 0x40, 0x7C}};
    StoredChar<5>  v = { 5 , {0xC, 0x30, 0x40, 0x30, 0xC}};
    StoredChar<5>  w = { 5 , {0x3C, 0x40, 0x20, 0x40, 0x3C}};
    StoredChar<5>  x = { 5 , {0x44, 0x28, 0x10, 0x28, 0x44}};
    StoredChar<4>  y = { 4 , {0xC, 0x50, 0x30, 0xC}};
    StoredChar<4>  z = { 4 , {0x64, 0x54, 0x54, 0x4C}};



    StoredChar<5>  A = { 5 , {0x7E, 0x09, 0x09, 0x09, 0x7E}};
    StoredChar<4>  B = { 4 , {0x7F, 0x49, 0x49, 0x36}};
    StoredChar<4>  C = { 4 , {0x3E, 0x41, 0x41, 0x41}};
    StoredChar<4>  D = { 4 , {0x7F, 0x41, 0x22, 0x1C}};
    StoredChar<4>  E = { 4 , {0x7F, 0x49, 0x49, 0x41}};
    StoredChar<4>  F = { 4 , {0x7F, 0x05, 0x05, 0x01}};
    StoredChar<5>  G = { 5 , {0x3E, 0x41, 0x49, 0x49, 0x39}};
    StoredChar<5>  H = { 5 , {0x7F, 0x08, 0x08, 0x08, 0x7F}};
    StoredChar<1>  I = { 1 , {0x7F}};
    StoredChar<3>  J = { 3 , {0x60, 0x40, 0x7F}};
    StoredChar<4>  K = { 4 , {0x7F, 0xC, 0x12, 0x61}};
    StoredChar<4>  L = { 4 , {0x7F, 0x40, 0x40, 0x40}};
    StoredChar<7>  M = { 7 , {0x7F, 0x03, 0x06, 0xC, 0x06, 0x03, 0x7F}};
    StoredChar<6>  N = { 6 , {0x7F, 0x03, 0xE, 0x38, 0x60, 0x7F}};
    StoredChar<5>  O = { 5 , {0x3E, 0x41, 0x41, 0x41, 0x3E}};
    StoredChar<4>  P = { 4 , {0x7F, 0x09, 0x09, 0x06}};
    StoredChar<6>  Q = { 6 , {0x3E, 0x41, 0x41, 0x51, 0x3E, 0x40}};
    StoredChar<4>  R = { 4 , {0x7F, 0x09, 0x19, 0x66}};
    StoredChar<4>  S = { 4 , {0x46, 0x49, 0x49, 0x31}};
    StoredChar<5>  T = { 5 , {0x01, 0x01, 0x7F, 0x01, 0x01}};
    StoredChar<5>  U = { 5 , {0x3F, 0x40, 0x40, 0x40, 0x3F}};
    StoredChar<5>  V = { 5 , {0x07, 0x18, 0x20, 0x18, 0x07}};
    StoredChar<7>  W = { 7 , {0x07, 0x18, 0x20, 0x10, 0x20, 0x18, 0x07}};
    StoredChar<5>  X = { 5 , {0x63, 0x14, 0x08, 0x14, 0x63}};
    StoredChar<5>  Y = { 5 , {0x03, 0x04, 0x78, 0x04, 0x03}};
    StoredChar<5>  Z = { 5 , {0x61, 0x51, 0x49, 0x45, 0x43}};



    StoredChar<5>  zero = { 5 , {0x3E, 0x41, 0x49, 0x41, 0x3E}};
    StoredChar<5>  one = { 5 , {0x44, 0x42, 0x7F, 0x40, 0x40}};
    StoredChar<5>  two = { 5 , {0x72, 0x51, 0x59, 0x4D, 0x46}};
    StoredChar<5>  three = { 5 , {0x22, 0x41, 0x49, 0x49, 0x36}};
    StoredChar<5>  four = { 5 , {0x18, 0x16, 0x11, 0x7F, 0x10}};
    StoredChar<5>  five = { 5 , {0x4F, 0x49, 0x49, 0x49, 0x31}};
    StoredChar<5>  six = { 5 , {0x3E, 0x49, 0x49, 0x49, 0x30}};
    StoredChar<5>  seven = { 5 , {0x61, 0x11, 0x09, 0x05, 0x03}};
    StoredChar<5>  eight = { 5 , {0x36, 0x49, 0x49, 0x49, 0x36}};
    StoredChar<5>  nine = { 5 , {0x06, 0x49, 0x49, 0x49, 0x3E}};


    StoredChar<1>  exclamation = { 1 , {0x9F}};
    StoredChar<3>  quote = { 3 , {0x07, 0x00, 0x07}};
    StoredChar<5>  hash = { 5 , {0x14, 0x7F, 0x14, 0x7F, 0x14}};
    StoredChar<5>  dollar = { 5 , {0x48, 0x54, 0xFE, 0x54, 0x24}};
    StoredChar<5>  percent = { 5 , {0x66, 0x36, 0x18, 0x6C, 0x66}};
    StoredChar<6>  ampersand = { 6 , {0x34, 0x4A, 0x4A, 0x54, 0x20, 0x40}};
    StoredChar<1>  apostrophe = { 1 , {0x07}};
    StoredChar<3>  openParenthesis = { 3 , {0x1C, 0x22, 0x41}};
    StoredChar<3>  closeParenthesis = { 3 , {0x41, 0x22, 0x1C}};
    StoredChar<2>  asterix = { 2 , {0x18, 0x18}};
    StoredChar<5>  plus = { 5 , {0x10, 0x10, 0x7C, 0x10, 0x10}};
    StoredChar<2>  comma = { 2 , {0xC0, 0x60}};
    StoredChar<5>  dash = { 5 , {0x10, 0x10, 0x10, 0x10, 0x10}};
    StoredChar<2>  dot = { 2 , {0x60, 0x60}};
    StoredChar<3>  slash = { 3 , {0x70, 0x1C, 0x07}};
    StoredChar<2>  colon = { 2 , {0x6C, 0x6C}};
    StoredChar<2>  semicolon = { 2 , {0xCC, 0x6C}};
    StoredChar<4>  lessThan = { 4 , {0x10, 0x38, 0x6C, 0x44}};
    StoredChar<5>  equals = { 5 , {0x28, 0x28, 0x28, 0x28, 0x28}};
    StoredChar<4>  greatherThan = { 4 , {0x44, 0x6C, 0x38, 0x10}};
    StoredChar<4>  question = { 4 , {0x02, 0x51, 0x09, 0x06}};
    StoredChar<6>  at = { 6 , {0x3C, 0x42, 0x5A, 0x5A, 0x52, 0x1C}};
    StoredChar<2>  openBracket = { 2 , {0x7F, 0x41}};
    StoredChar<2>  closeBracket = { 2 , {0x41, 0x7F}};
    StoredChar<3>  openBrace = { 3 , {0x08, 0x36, 0x41}};
    StoredChar<3>  closeBrace = { 3 , {0x41, 0x36, 0x08}};
    StoredChar<3>  backslash = { 3 , {0x07, 0x1C, 0x70}};
    StoredChar<5>  hat = { 5 , {0x04, 0x02, 0x01, 0x02, 0x04}};
    StoredChar<5>  underscore = { 5 , {0x40, 0x40, 0x40, 0x40, 0x40}};
    StoredChar<2>  accent = { 2 , {0x01, 0x02}};
    StoredChar<1>  bar = { 1 , {0xFF}};
    StoredChar<5>  tilde = { 5 , {0x10, 0x08, 0x10, 0x20, 0x10}};



    StoredChar<4>  accentedA = { 4 , {0x20, 0x55, 0x55, 0x39}};
    StoredChar<4>  accentedE = { 4 , {0x38, 0x55, 0x55, 0x09}};
    StoredChar<5>  accentedO = { 5 , {0x38, 0x45, 0x45, 0x45, 0x38}};
    StoredChar<3>  accentedI = { 3 , {0x00, 0x7D, 0x01}};
    StoredChar<5>  accentedU = { 5 , {0x00, 0x3C, 0x41, 0x41, 0x7D}};
    StoredChar<4>  degree = { 4 , {0x06, 0x09, 0x09, 0x06}};
    StoredChar<7>  arrowUp = { 7 , {0x08, 0x04, 0x02, 0xFF, 0x02, 0x04, 0x08}};
    StoredChar<7>  arrowDown = { 7 , {0x10, 0x20, 0x40, 0xFF, 0x40, 0x20, 0x10}};
    StoredChar<8>  arrowLeft = { 8 , {0x10, 0x38, 0x54, 0x92, 0x10, 0x10, 0x10, 0x10}};
    StoredChar<8>  arrowRight = { 8 , {0x10, 0x10, 0x10, 0x10, 0x92, 0x54, 0x38, 0x10}};
    StoredChar<8>  arrowUpRight = { 8 , {0x80, 0x40, 0x20, 0x11, 0x09, 0x05, 0x03, 0x1F}};
    StoredChar<8>  arrowDownRight = { 8 , {0x01, 0x02, 0x04, 0x88, 0x90, 0xA0, 0xC0, 0xF8}};
    StoredChar<8>  arrowDownLeft = { 8 , {0xF8, 0xC0, 0xA0, 0x90, 0x88, 0x04, 0x02, 0x01}};
    StoredChar<8>  arrowUpLeft = { 8 , {0x1F, 0x03, 0x05, 0x09, 0x11, 0x20, 0x40, 0x80}};
    StoredChar<6>  copyright = { 6 , {0x7C, 0x82, 0xBA, 0xAA, 0x82, 0x7C}};
    StoredChar<3>  unknown = { 3 , {0x7E, 0x7E, 0x7E}};
    StoredChar<3>  expZero = { 3 , {0xE, 0x11, 0xE}};
    StoredChar<3>  expOne = { 3 , {0x02, 0x01, 0x1F}};
    StoredChar<3>  expTwo = { 3 , {0x19, 0x15, 0x12}};
    StoredChar<3>  expThree = { 3 , {0x11, 0x15, 0xA}};
    StoredChar<3>  expFour = { 3 , {0xC, 0xA, 0x1D}};
    StoredChar<3>  expFive = { 3 , {0x17, 0x15, 0x09}};
    StoredChar<3>  expSix = { 3 , {0x1E, 0x15, 0x1D}};
    StoredChar<3>  expSeven = { 3 , {0x19, 0x05, 0x03}};
    StoredChar<3>  expEight = { 3 , {0x1B, 0x15, 0x1B}};
    StoredChar<3>  expNine = { 3 , {0x17, 0x15, 0xF}};

};
