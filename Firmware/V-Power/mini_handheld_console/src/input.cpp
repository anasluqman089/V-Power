#include "input.h"
#include "pins.h"

static const uint8_t pins[] = {
    SW1_UP,
    SW2_DOWN,
    SW3_LEFT,
    SW4_RIGHT
};

static bool state[4] = {HIGH, HIGH, HIGH, HIGH};
static bool pressEvent[4] = {false, false, false, false};
static int encLast;
static int encDeltaValue = 0;

void inputBegin() {
    for (uint8_t i = 0; i < 4; ++i) {
        pinMode(pins[i], INPUT_PULLUP);
    }
    pinMode(ENC_A, INPUT_PULLUP);
    pinMode(ENC_B, INPUT_PULLUP);
    encLast = digitalRead(ENC_A);
}

void inputUpdate() {
    for (uint8_t i = 0; i < 4; ++i) {
        bool current = digitalRead(pins[i]);
        if (state[i] == HIGH && current == LOW) {
            pressEvent[i] = true;
        }
        state[i] = current;
    }

    int a = digitalRead(ENC_A);
    if (a != encLast) {
        encDeltaValue += digitalRead(ENC_B) != a ? 1 : -1;
        encLast = a;
    }
}

int encoderDelta() {
    int value = encDeltaValue;
    encDeltaValue = 0;
    return value;
}

bool buttonPressed(ButtonId button) {
    uint8_t i = static_cast<uint8_t>(button);
    if (!pressEvent[i]) return false;
    pressEvent[i] = false;
    return true;
}

bool buttonDown(ButtonId button) {
    return digitalRead(pins[static_cast<uint8_t>(button)]) == LOW;
}
