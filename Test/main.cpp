
#include <Arduino.h>
#include "Label.hpp"



void setup() {

    SH1106_driver oled(8, 128, 0);
    oled.init();

    Label screen(oled, 128, 8, 0,0);
    Label label(oled, 100, 3, 20, 2);

    screen.fill(0xFF);

    label.clear();
    label.write("Hello,world!");


/**/
}
void loop() {

}
