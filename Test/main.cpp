
#include <Arduino.h>
#include "SH1106.h"





void setup() {

    uint8_t empty[132] =  {};

    Serial.begin(9600);
    Serial.println("Inizio");

    SH1106 oled(128, 8, 0);

    oled.init();

    oled.drawPageArray(4, 20, empty, 30);
    oled.driver.columnAddr(100);

}
void loop() {

}
