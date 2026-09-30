#pragma once

#include <Arduino.h>
#include <vector>

extern std::vector<String> gameFiles;
extern std::vector<String> photoFiles;

bool storageBegin();
void scanGames();
void scanPhotos();
String nextPhotoPath();
