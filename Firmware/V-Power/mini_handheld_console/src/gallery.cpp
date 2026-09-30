#include "gallery.h"
#include "display.h"
#include "storage.h"
#include <SD.h>
#include <TJpg_Decoder.h>

static bool jpegCallback(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t *bitmap) {
    for (uint16_t yy = 0; yy < h; ++yy) {
        for (uint16_t xx = 0; xx < w; ++xx) {
            uint16_t c = bitmap[yy * w + xx];
            uint8_t r = (c >> 11) & 0x1F;
            uint8_t g = (c >> 5) & 0x3F;
            uint8_t b = c & 0x1F;
            uint16_t luma = (r * 255 / 31 * 30 + g * 255 / 63 * 59 + b * 255 / 31 * 11) / 100;
            if (luma > 120) display.drawPixel(x + xx, y + yy, SSD1306_WHITE);
        }
    }
    return true;
}

void galleryDraw(int index) {
    display.clearDisplay();

    if (photoFiles.empty()) {
        display.setCursor(24, 28);
        display.print("NO PHOTOS");
        display.display();
        return;
    }

    if (index < 0) index = 0;
    if (index >= (int)photoFiles.size()) index = photoFiles.size() - 1;

    TJpgDec.setJpgScale(4);
    TJpgDec.setSwapBytes(true);
    TJpgDec.setCallback(jpegCallback);
    TJpgDec.drawFsJpg(0, 0, photoFiles[index], SD);

    display.fillRect(0, 56, 128, 8, SSD1306_BLACK);
    display.setCursor(0, 56);
    display.printf("%d/%d  LEFT:BACK", index + 1, (int)photoFiles.size());
    display.display();
}
