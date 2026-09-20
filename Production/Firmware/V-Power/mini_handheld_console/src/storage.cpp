#include "storage.h"
#include <FS.h>
#include <SD.h>
#include "pins.h"

std::vector<String> gameFiles;
std::vector<String> photoFiles;

static const char *builtinGames[] = {
    "FLASH/SNAKE",
    "FLASH/DODGE",
    "FLASH/PONG"
};

static void addBuiltinGames() {
    for (const char *game : builtinGames) {
        gameFiles.push_back(game);
    }
}

bool storageBegin() {
    gameFiles.clear();
    photoFiles.clear();
    addBuiltinGames();

    if (!SD.begin(SD_CS)) {
        return false;
    }

    if (!SD.exists("/games")) SD.mkdir("/games");
    if (!SD.exists("/photos")) SD.mkdir("/photos");

    scanGames();
    scanPhotos();
    return true;
}

void scanGames() {
    gameFiles.clear();
    addBuiltinGames();

    File dir = SD.open("/games");
    if (!dir) return;

    while (true) {
        File file = dir.openNextFile();
        if (!file) break;

        if (!file.isDirectory()) {
            String name = file.name();
            String upper = name;
            upper.toUpperCase();

            if (upper.endsWith(".GAM")) {
                gameFiles.push_back(name);
            }
        }

        file.close();
    }

    dir.close();
}

void scanPhotos() {
    photoFiles.clear();

    File dir = SD.open("/photos");
    if (!dir) return;

    while (true) {
        File file = dir.openNextFile();
        if (!file) break;

        if (!file.isDirectory()) {
            String name = file.name();
            String upper = name;
            upper.toUpperCase();

            if (upper.endsWith(".JPG") || upper.endsWith(".JPEG")) {
                photoFiles.push_back(name);
            }
        }

        file.close();
    }

    dir.close();
}

String nextPhotoPath() {
    uint32_t n = photoFiles.size() + 1;
    String path;

    do {
        char name[32];
        snprintf(
            name,
            sizeof(name),
            "/photos/PHOTO%03lu.JPG",
            (unsigned long)n++
        );
        path = name;
    } while (SD.exists(path));

    return path;
}
