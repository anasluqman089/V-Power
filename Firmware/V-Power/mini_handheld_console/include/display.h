#pragma once

#include <Arduino.h>
#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;

void displayBegin();
void displayMessage(const String &a, const String &b = "");
