#include "battery.h"
#include <Arduino.h>
#include <Wire.h>
#include "pins.h"

static const uint8_t MAX17043_ADDR = 0x36;
static float soc = 100.0f;
static float voltage = 0.0f;
static unsigned long lastUpdate = 0;

static bool read16(uint8_t reg, uint16_t &value) {
    Wire.beginTransmission(MAX17043_ADDR);
    Wire.write(reg);
    if (Wire.endTransmission(false) != 0) {
        return false;
    }
    if (Wire.requestFrom(MAX17043_ADDR, (uint8_t)2) != 2) {
        return false;
    }
    value = ((uint16_t)Wire.read() << 8) | Wire.read();
    return true;
}

void batteryBegin() {
    uint16_t dummy;
    read16(0x02, dummy);
}

void batteryUpdate() {
    if (millis() - lastUpdate < 500) {
        return;
    }
    lastUpdate = millis();

    uint16_t rawV;
    uint16_t rawSoc;

    if (read16(0x02, rawV)) {
        voltage = ((rawV >> 4) * 1.25f) / 1000.0f;
    }

    if (read16(0x04, rawSoc)) {
        soc = ((float)(rawSoc >> 8)) + ((rawSoc & 0xFF) / 256.0f);
        if (soc < 0) soc = 0;
        if (soc > 100) soc = 100;
    }
}

float batteryPercent() {
    return soc;
}

float batteryVoltage() {
    return voltage;
}
