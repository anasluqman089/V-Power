#include <Arduino.h>
#include <Wire.h>
#include <SD.h>

#include "pins.h"
#include "display.h"
#include "input.h"
#include "battery.h"
#include "storage.h"
#include "camera.h"
#include "menu.h"
#include "gallery.h"
#include "game.h"

enum Mode {
    MODE_MENU,
    MODE_GAME,
    MODE_CAMERA,
    MODE_GALLERY
};

static Mode mode = MODE_MENU;
static int gameIndex = 0;
static int photoIndex = 0;
static unsigned long leftStart = 0;
static bool lowBatteryState = false;
static unsigned long lowBatteryBlink = 0;

static void cameraScreen() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("CAMERA");
    display.drawLine(0, 9, 127, 9, SSD1306_WHITE);
    display.setCursor(6, 20);
    display.print("RIGHT TAKE PHOTO");
    display.setCursor(6, 32);
    display.print("UP GALLERY");
    display.setCursor(6, 44);
    display.print("LEFT MENU");
    display.display();
}

static void handleBatteryLed() {
    batteryUpdate();
    if (batteryPercent() <= LOW_BATTERY_PERCENT) {
        if (millis() - lowBatteryBlink >= 400) {
            lowBatteryBlink = millis();
            lowBatteryState = !lowBatteryState;
            digitalWrite(LED2, lowBatteryState);
        }
    } else {
        lowBatteryState = false;
        digitalWrite(LED2, LOW);
    }
}

static void menuLoop() {
    int delta = encoderDelta();
    if (delta) {
        gameIndex += (delta > 0 ? 1 : -1);
        if (gameIndex < 0) gameIndex = 0;
        if (gameIndex >= (int)gameFiles.size()) gameIndex = gameFiles.empty() ? 0 : gameFiles.size() - 1;
    }

    if (buttonPressed(BUTTON_RIGHT) && !gameFiles.empty()) {
        gameBegin(gameFiles[gameIndex]);
        mode = MODE_GAME;
        leftStart = 0;
    }

    if (buttonPressed(BUTTON_LEFT)) {
        mode = MODE_CAMERA;
    }

    menuDraw(gameIndex);
}

static void cameraLoop() {
    if (buttonPressed(BUTTON_RIGHT)) {
        if (takePhoto()) {
            displayMessage("PHOTO SAVED");
            delay(400);
        } else {
            displayMessage("PHOTO ERROR");
            delay(400);
        }
    }

    if (buttonPressed(BUTTON_UP)) {
        scanPhotos();
        photoIndex = 0;
        mode = MODE_GALLERY;
        return;
    }

    if (buttonPressed(BUTTON_LEFT)) {
        mode = MODE_MENU;
        return;
    }

    cameraScreen();
}

static void galleryLoop() {
    int delta = encoderDelta();
    if (delta && !photoFiles.empty()) {
        photoIndex += (delta > 0 ? 1 : -1);
        if (photoIndex < 0) photoIndex = 0;
        if (photoIndex >= (int)photoFiles.size()) photoIndex = photoFiles.size() - 1;
    }

    if (buttonPressed(BUTTON_LEFT)) {
        mode = MODE_CAMERA;
        return;
    }

    galleryDraw(photoIndex);
}

static void gameLoop() {
    if (buttonDown(BUTTON_LEFT)) {
        if (leftStart == 0) leftStart = millis();
        if (millis() - leftStart >= GAME_EXIT_TIME) {
            leftStart = 0;
            mode = MODE_MENU;
            return;
        }
    } else {
        leftStart = 0;
    }

    gameUpdate();
}

void setup() {
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);

    inputBegin();
    Wire.begin(SDA_PIN, SCL_PIN);
    displayBegin();
    batteryBegin();

    displayMessage("STARTING...");

    if (storageBegin()) {
        displayMessage("SD OK");
    } else {
        displayMessage("NO SD");
    }

    cameraBegin();
    delay(500);
}

void loop() {
    inputUpdate();
    handleBatteryLed();

    switch (mode) {
        case MODE_MENU:
            menuLoop();
            break;
        case MODE_GAME:
            gameLoop();
            break;
        case MODE_CAMERA:
            cameraLoop();
            break;
        case MODE_GALLERY:
            galleryLoop();
            break;
    }

    delay(5);
}
