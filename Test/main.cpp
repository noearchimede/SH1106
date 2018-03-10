
#include <Arduino.h>
#include "SH1106.h"

SH1106 lcd;



void setup() {
    Serial.begin(9600);
    Serial.println("Inizio");

    lcd.init();


}
void loop() {
    Serial.println();
    Serial.println("Contrast");
    delay(2000);
    for(int i = 255; i; i--) {
        lcd.contrast(i);
        Serial.print(i); Serial.print(" ");
        delay(30);
    }

    Serial.println();Serial.println();Serial.println();
    Serial.println("Flip");
    delay(2000);
    for(int i = 4; i; i--) {
        lcd.flipVertically(i%2);
        delay(500);

    }

    Serial.println();Serial.println();Serial.println();
    Serial.println("reverse");
    delay(2000);
    for(int i = 4; i; i--) {
        lcd.reverse(i%2);
        delay(500);
    }

    Serial.println();Serial.println();Serial.println();
    Serial.println("voltage");
    delay(2000);
    for(int i = 4; i; i--) {
        lcd.pumpVoltage0123(i);
        delay(500);
    }

    Serial.println();Serial.println();Serial.println();
    Serial.println("segment remap");
    delay(2000);
    for(int i = 4; i; i--) {
        lcd.segmentRemap(i%2);
        delay(500);
    }
}
