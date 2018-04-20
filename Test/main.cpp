
#include <Arduino.h>
#include "Label.hpp"



void setup() {
 Serial.begin(9600);

    SH1106_driver oled(8, 128, 0);
    oled.init();

    Label screen(oled, 128, 8, 0,0);
    Label label(oled, 100, 3, 20, 2);

    //screen.fill(0xEF);

    //label.clear();
    char s[5] =  {'H', 'e', 'l', 'l', 'o'};
    label.print(s, 5);


/**/
}
void loop() {

}
