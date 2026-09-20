# Mini Handheld Console

## Project

PlatformIO project for XIAO ESP32-S3 Sense with 128x64 OLED, four buttons, rotary encoder, two LEDs, MAX17043, camera and onboard microSD.

## Controls

Menu: encoder moves, RIGHT launches, LEFT enters camera.
Camera: RIGHT takes photo, UP opens gallery, LEFT returns to menu.
Gallery: encoder browses, LEFT returns to camera.
Game: LEFT held for 5 seconds returns to menu.
LED1: on when powered.
LED2: blinks below the configured battery threshold.

## SD layout

/sd/games/*.GAM
/sd/photos/*.JPG

## Important hardware note

The XIAO ESP32-S3 Sense onboard microSD uses GPIO21 for CS and D8/D9/D10 for SPI. The requested SW2=D8, SW3=D9 and SW4=D10 therefore conflict with the onboard microSD interface. The firmware can compile with the requested pin map, but the SD card and those three buttons cannot reliably operate at the same time on the stock Sense SD connection. Move those button signals to unused GPIOs or use a different SD connection before expecting the SD features to work.

## Build

Open the folder in VS Code with PlatformIO and build/upload the project.
