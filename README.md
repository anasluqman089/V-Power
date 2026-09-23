# V-Power

<img width="745" height="494" alt="image" src="https://github.com/user-attachments/assets/8ba8f43b-f751-4a3d-84f1-142ea906d29c" />

*Hello everyone!*

What is V-Power? you might ask. Well, it is a custom mini handheld console built around the Seeed Studio XIAO ESP32-S3 Sense. The console combines an OLED display, directional buttons, rotary encoder, camera, SD card, battery monitoring, and built-in games into a compact system.

## Features

* XIAO ESP32-S3 Sense
* 0.96" OLED display
* 4 directional buttons
* Rotary encoder
* Camera
* SD card support
* MAX17043 battery fuel gauge
* Power indicator LED
* Low-battery warning LED
* Built-in games stored in ESP32 flash
* SD-card game support
* Camera mode
* Photo gallery
* Long-press game exit

## BOM


| Item | Component | Price ($) | Qty | Buy Link |
| :---: | :--- | :---: | :---: | :--- |
| 1 | XIAO ESP32-S3 Sense | $13.90 | 1 | [Seeed Studio](https://www.seeedstudio.com/XIAO-ESP32S3-Sense-p-5639.html) |
| 2 | 0.96 Inch OLED Display | $6.99 | 1 | [Amazon](https://www.amazon.com/Dorhea-Display-3-3V-5V-Arduino-Raspberry/dp/B07FK8GB8T/ref=sr_1_5) |
| 3 | MAX17043 | $9.49 | 1 | [Amazon](https://www.amazon.com/HiLetgo-MAX17043-Lithium-Battery-Converter/dp/B01NBE99EP/ref=sr_1_3) |
| 4 | Rotary Encoder | $6.99 | 1 | [Amazon](https://www.amazon.com/AIMPGSTL-Rotary-Encoder-Arduino-Raspberry/dp/B0FHDG9BKF/ref=sr_1_6) |
| 5 | Tactile Push Button | $4.99 | 4 | [Amazon](https://www.amazon.com/DAOKI-Miniature-Momentary-Tactile-Quality/dp/B01CGMP9GY/ref=sr_1_8) |
| 6 | LED | $6.99 | 2 | [Amazon](https://www.amazon.com/CHANZON-Assortment-Colors-Clear-Transparent/dp/B01AUI4VSI/ref=sr_1_6) |
| 7 | 40x30x8mm Li-ion/LiPo Battery | $2.20 | 1 | [Shopee](https://shopee.com.my/Original-Rechargeable-Battery-3.7V-150mAh-300mAh-600mAh-800mAh-1000mAh-1200mAh-1500mAh-3000mAh-5000mAh-bateri-china-cina-i.237274675.3651954444) |
| 8 | 3d printing | ~$5.00 | 1 | - |

## Controls

There 4 mode with its own control

### Main Menu

ENCODER - Move through games

RIGHT - Launch selected game

LEFT -  Enter camera mode

### Camera Mode

RIGHT - Take photo

UP - Open gallery

LEFT - Return to menu

### Gallery

ENCODER - Browse photos

LEFT -  Return to camera

### Game Mode

UP -  Game control

DOWN - Game control

LEFT -  Game control

RIGHT - Game control

ENCODER -  Game-specific control

LEFT held for 5 seconds -  Return to menu

The game exit time can be changed from **5 seconds to 10 seconds** in the source code.

## Hardware Pinout

| Function         | XIAO Pin |
| ---------------- | -------- |
| SW1 / UP         | D1       |
| LED 1            | D2       |
| LED 2            | D3       |
| OLED SDA         | D4       |
| OLED SCL         | D5       |
| Rotary Encoder A | D6       |
| Rotary Encoder B | D7       |
| SW2 / DOWN       | D8       |
| SW3 / LEFT       | D9       |
| SW4 / RIGHT      | D10      |
| MAX17043 SDA     | D4       |
| MAX17043 SCL     | D5       |

## LED Functions

### LED 1

LED 1 is turned on when the handheld is powered on.

Power ON
   ↓
LED 1 ON

### LED 2

LED 2 indicates a low battery condition.

Battery ≤ 15%
      ↓
LED 2 blinks


## Games

Some games are built directly into the ESP32-S3 firmware so that they do not require an SD card.

The current built-in games are:

SNAKE
DODGE
PONG

These games are compiled into the firmware and stored in the ESP32-S3 flash.

Additional games can be loaded from the SD card using the project's game format.

## SD Card Structure

The SD card uses the following structure:

  SD CARD
  │
  ├── games/
  │   ├── game1.GAM
  │   ├── game2.GAM
  │   └── game3.GAM
  │
  └── photos/
      ├── PHOTO001.JPG
      ├── PHOTO002.JPG
      └── PHOTO003.JPG

When the console starts, it scans the `games` folder and adds detected `.GAM` files to the game menu.

Photos captured by the camera are stored in:

  /photos/

## Game Menu

The menu combines built-in games and SD-card games.

Example:

GAME MENU

  > SNAKE
    DODGE
    PONG
    game1.GAM
    game2.GAM


The rotary encoder is used to move through the list.

Pressing **RIGHT** starts the selected game.

## Camera

The XIAO ESP32-S3 Sense camera is used to capture photographs.

When a picture is taken:

  Camera
     ↓
  Capture JPEG
     ↓
  Create filename
     ↓
  Save to SD
     ↓
  /photos/PHOTOxxx.JPG

The camera mode can be accessed from the main menu using the **LEFT** button.

## Gallery

The gallery reads JPEG files from:

  /photos/


The rotary encoder is used to browse the pictures.

The OLED displays the selected photograph.

## Battery Monitoring

The MAX17043 monitors the battery through I²C.

The battery percentage is checked periodically.

  Battery > 15%
      ↓
  LED 2 OFF
  
  Battery ≤ 15%
      ↓
  LED 2 BLINKING
  

## Flash Storage

The XIAO ESP32-S3 Sense version used by this project provides internal flash storage for the firmware.

Built-in games are compiled into the firmware, allowing the handheld to have games available even when an SD card is not present.

The SD card is intended for:

  External games
  Photos
  Additional files


The internal flash is primarily used for:

  System firmware
  Built-in games
  Game data
  Configuration
  
## Important Hardware Note

The current pin assignment uses:

  D8  → SW2
  D9  → SW3
  D10 → SW4

On the XIAO ESP32-S3 Sense, these pins are also associated with the board's SD-card interface.

## How to build it!

***Step 1 : Wiring***

Choose whether to use a PCB or dupont wire but I really recommend using PCB

***Step 2 : Buy the parts***

Buy the part that is listed in the BOM

***Step 3 : Solder***

Solder the parts to the PCB make sure you follow the traces correctly

***Step 4 : Casing***

3D print the CAD or make your own case, its up to you!

***Step 5 : Upload the firmware***

Upload the firmware make sure you use VSCode with PlatformIO extensions. Use this guide to get started https://docs.platformio.org/en/latest/integration/ide/vscode.html

*Finished*

## Schematic

<img width="585" height="614" alt="image" src="https://github.com/user-attachments/assets/ab026819-5be5-485e-bc71-c6169428c7ea" />

## PCB

<img width="612" height="496" alt="image" src="https://github.com/user-attachments/assets/8b0098cf-8b14-4d4f-a793-213824fc676f" />

<img width="625" height="493" alt="image" src="https://github.com/user-attachments/assets/6a5d2aa7-462b-4418-a1e4-5b58fef04f5d" />


## CAD

<img width="643" height="427" alt="image" src="https://github.com/user-attachments/assets/cb6cfd41-0643-459c-94d6-0b63567b7dd0" />

<img width="709" height="449" alt="image" src="https://github.com/user-attachments/assets/5c7a9f89-612e-445a-aadd-01878a3b4967" />

### Body 

<img width="656" height="439" alt="image" src="https://github.com/user-attachments/assets/13c6ef06-3088-4d2f-931f-3d80ecc1d724" />

<img width="677" height="374" alt="image" src="https://github.com/user-attachments/assets/1fac5c56-3332-41e9-887d-a0d6a5914c6b" />

### LID

<img width="742" height="425" alt="image" src="https://github.com/user-attachments/assets/eadc2ba4-a4c0-4f47-88ab-7103ed35c00e" />




