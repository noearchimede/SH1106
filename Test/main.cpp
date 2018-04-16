
#include <Arduino.h>
#include "SH1106.h"





void setup() {

    Serial.begin(9600);
    Serial.println("Inizio");

    SH1106_driver oled(8, 128, 0);
    oled.init();

    //SH1106_label screen(oled, 7, 127, 0,0);
    SH1106_label label(oled, 3, 100, 2, 20);

    //screen.fillRange(0xFF);

    label.clear();

    label.setCursor(0,0,true);
    for(char i = 33; i < 127; i++) {
        label.writeAscii(i);
    }
    label.newline();
    label.writeAccentedVowel('a');
    label.space();
    label.writeAccentedVowel('e');
    label.tab();
    label.writeAccentedVowel('i');
    label.writeAccentedVowel('o');
    label.writeAccentedVowel('u');
    for(int i = 0; i < 8; i++)
    label.writeArrow8StepCW(i);
    for(int i = 0; i < 10; i++)
    label.writeExpDigit(i);
    label.writeCopyright();
    label.writeDegree();
    label.writeUnknown();
/**/
}
void loop() {

}
