

#include <Arduino.h>
#include "Label.hpp"
#include "Image.hpp"


const uint8_t qdr [] = {
	// size is 10 x 15
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF3, 0x7F, 0xF8, 0x07, 0xFC, 0x00, 0x1E, 0x10, 0x01,
	0x00, 0x00, 0x00
};

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

    Image image (oled, 10, 2, 70, 5);

    image.fill(0x00);


    image.draw(qdr);

    //screen.clear();
    //screen.print("Hello, wordl!\n\nzero\t0\none\t1\ntwo\t2\ntree\t3");


}
void loop() {

}
