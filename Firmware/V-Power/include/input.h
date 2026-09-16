#pragma once

#include <Arduino.h>

enum ButtonId {
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_LEFT,
    BUTTON_RIGHT
};

void inputBegin();
void inputUpdate();
int encoderDelta();
bool buttonPressed(ButtonId button);
bool buttonDown(ButtonId button);
