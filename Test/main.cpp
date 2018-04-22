
#include <Arduino.h>
#include "Label.hpp"



void setup() {
 Serial.begin(9600);

    SH1106_driver oled(8, 128, 0);
    oled.init();

    Label screen(oled, 128, 8, 0,0);
    Label label(oled, 122, 6, 3, 1);

    screen.fill(0xFF);
    screen.fill(0x7F, 0, 0, 0xff, 0);
    screen.fill(0xFE, 0, 7, 0xff, 7);



    label.clear();
    label.print("Ahi quanto a dir qual'era e` cosa dura esta selva servaggia e aspra e forte che nel pensier rinova la paura");


/**/
}
void loop() {

}
