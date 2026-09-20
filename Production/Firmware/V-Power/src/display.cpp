#include "display.h"
#include "pins.h"

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void displayBegin() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
        while (true) {
            delay(1000);
        }
    }
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.clearDisplay();
}

void displayMessage(const String &a, const String &b) {
    display.clearDisplay();
    display.setCursor(0, 20);
    display.print(a);
    if (b.length()) {
        display.setCursor(0, 36);
        display.print(b);
    }
    display.display();
}
