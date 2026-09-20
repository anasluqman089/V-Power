#include "menu.h"
#include "display.h"
#include "storage.h"

void menuDraw(int index) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("GAME MENU");
    display.drawLine(0, 9, 127, 9, SSD1306_WHITE);

    if (gameFiles.empty()) {
        display.setCursor(16, 28);
        display.print("NO GAMES");
        display.display();
        return;
    }

    int first = index - 2;
    if (first < 0) first = 0;

    for (int i = 0; i < 5 && first + i < (int)gameFiles.size(); ++i) {
        int n = first + i;
        String name = gameFiles[n];
        name.replace("/games/", "");
        if (n == index) {
            display.fillRect(0, 12 + i * 10, 128, 9, SSD1306_WHITE);
            display.setTextColor(SSD1306_BLACK);
        }
        display.setCursor(2, 13 + i * 10);
        display.print(name);
        display.setTextColor(SSD1306_WHITE);
    }

    display.setCursor(0, 56);
    display.print("ENC MOVE  R PLAY  L CAM");
    display.display();
}
