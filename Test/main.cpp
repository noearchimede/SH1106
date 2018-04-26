

#include <Arduino.h>
#include "Label.hpp"
#include "Image.hpp"

const char s [] = "Hello, world!\0";

void setup() {
 Serial.begin(9600);

    SH1106_driver oled(8, 128, 0);
    oled.init();

    Label screen(oled, 128, 8, 0,0);
    Label label(oled, 20, 1, 5, 30);
/*
    screen.fill(0xFF);
    screen.fill(0x7F, 0, 0, 0xff, 0);
    screen.fill(0xFE, 0, 7, 0xff, 7);
*/

    screen.clear();
    screen.print(s, 13, false);


}
void loop() {

}
