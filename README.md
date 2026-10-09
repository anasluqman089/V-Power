# V-Power Handheld Console

<img width="745" height="494" alt="V-Power handheld console" src="https://github.com/user-attachments/assets/8ba8f43b-f751-4a3d-84f1-142ea906d29c" />

V-Power is a compact handheld console built around the Seeed Studio XIAO ESP32-S3 Sense. It brings together an OLED display, physical controls, a camera, SD-card storage, and battery monitoring in a custom PCB and 3D-printed case.

## Features

- Seeed Studio XIAO ESP32-S3 Sense
- 0.96-inch OLED display
- Four directional buttons and a rotary encoder
- Camera and photo gallery
- microSD card support
- MAX17043 battery fuel gauge
- Power indicator and low-battery LEDs
- Built-in Snake, Dodge, and Pong games in the `mini_handheld_console` project

## Bill of Materials

Prices are estimates and may change. The linked products are examples of the parts used for this build.

| Item | Component | Price (USD) | Qty | Example source |
| :--: | :--- | ---: | :--: | :--- |
| 1 | XIAO ESP32-S3 Sense | $13.90 | 1 | [Seeed Studio](https://www.seeedstudio.com/XIAO-ESP32S3-Sense-p-5639.html) |
| 2 | 0.96-inch OLED display | $6.99 | 1 | [Amazon](https://www.amazon.com/Dorhea-Display-3-3V-5V-Arduino-Raspberry/dp/B07FK8GB8T/ref=sr_1_5) |
| 3 | MAX17043 battery fuel gauge | $9.49 | 1 | [Amazon](https://www.amazon.com/HiLetgo-MAX17043-Lithium-Battery-Converter/dp/B01NBE99EP/ref=sr_1_3) |
| 4 | Rotary encoder | $6.99 | 1 | [Amazon](https://www.amazon.com/AIMPGSTL-Rotary-Encoder-Arduino-Raspberry/dp/B0FHDG9BKF/ref=sr_1_6) |
| 5 | Tactile push buttons | $4.99 | 4 | [Amazon](https://www.amazon.com/DAOKI-Miniature-Momentary-Tactile-Quality/dp/B01CGMP9GY/ref=sr_1_8) |
| 6 | LEDs | $6.99 | 2 | [Amazon](https://www.amazon.com/CHANZON-Assortment-Colors-Clear-Transparent/dp/B01AUI4VSI/ref=sr_1_6) |
| 7 | 40 x 30 x 8 mm Li-ion/LiPo battery | $2.20 | 1 | [Shopee](https://shopee.com.my/Original-Rechargeable-Battery-3.7V-150mAh-300mAh-600mAh-800mAh-1000mAh-1200mAh-1500mAh-3000mAh-5000mAh-bateri-china-cina-i.237274675.3651954444) |
| 8 | 3D printing | $5.00 | 1 | - |
| 9 | PCB | $4.00 | 1 | - |

## Controls

**Menu:** Turn the encoder to choose a game. Press **RIGHT** to launch it or **LEFT** to open the camera.

**Camera:** Press **RIGHT** to take a photo, **UP** to open the gallery, or **LEFT** to return to the menu.

**Gallery:** Turn the encoder to browse photos. Press **LEFT** to return to the camera.

**Games:** Use the directional buttons and encoder for game controls. Hold **LEFT** for five seconds to return to the menu.

The game-exit delay is set by `GAME_EXIT_TIME` in [the firmware pin definitions](Firmware/V-Power/mini_handheld_console/include/pins.h).

## Hardware Pinout

| Function | XIAO pin |
| :--- | :---: |
| UP button | D1 |
| Power LED | D2 |
| Low-battery LED | D3 |
| OLED and MAX17043 SDA | D4 |
| OLED and MAX17043 SCL | D5 |
| Rotary encoder A | D6 |
| Rotary encoder B | D7 |
| DOWN button | D8 |
| LEFT button | D9 |
| RIGHT button | D10 |

## Games and SD Card

The `mini_handheld_console` firmware includes Snake, Dodge, and Pong, which run without an SD card. The firmware also scans `/games` for files ending in `.GAM`, but external game files are not currently parsed or executed; selecting one displays a placeholder screen.

Photos taken with the camera are saved to `/photos`. The card is organized like this:

```text
games/
  game1.GAM
  game2.GAM
photos/
  PHOTO001.JPG
  PHOTO002.JPG
```

The gallery reads JPEG images from `/photos` and displays them on the OLED.

## Battery LEDs

The MAX17043 reports battery charge over I²C. The power LED stays on while the console is running. The warning LED blinks when the reported charge is at or below 15%; this threshold is defined by `LOW_BATTERY_PERCENT` in [the firmware pin definitions](Firmware/V-Power/mini_handheld_console/include/pins.h).

## Hardware Note

The current pinout assigns D8, D9, and D10 to buttons. On the XIAO ESP32-S3 Sense, these pins are also used by the onboard microSD interface. As a result, the buttons and onboard SD card cannot reliably operate together with this wiring. Change the wiring and pin assignments, or use a different SD connection, before relying on both at once.

## Build and Assembly

1. Assemble the circuit using the PCB or jumper wires. Follow the pinout above and check the SD-card pin conflict before soldering.
2. Install the [PlatformIO IDE extension for VS Code](https://docs.platformio.org/en/latest/integration/ide/vscode.html).
3. Open `Firmware/V-Power/mini_handheld_console` in VS Code and build the project with PlatformIO.
4. Connect the XIAO ESP32-S3 Sense and upload the firmware.
5. Print the case from the CAD files, or make a case of your own.

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




