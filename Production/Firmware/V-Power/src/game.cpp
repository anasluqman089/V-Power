#include "game.h"
#include "display.h"
#include "input.h"

static String currentGame;

void gameBegin(const String &path) {
    currentGame = path;
}

void gameUpdate() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("GAME");
    display.setCursor(0, 16);
    display.print(currentGame);

    display.setCursor(0, 32);
    if (buttonDown(BUTTON_UP)) display.print("UP ");
    if (buttonDown(BUTTON_DOWN)) display.print("DOWN ");
    if (buttonDown(BUTTON_LEFT)) display.print("LEFT ");
    if (buttonDown(BUTTON_RIGHT)) display.print("RIGHT ");

    display.display();
}
