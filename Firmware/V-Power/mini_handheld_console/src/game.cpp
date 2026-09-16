#include "game.h"
#include "display.h"
#include "input.h"

#include <esp_system.h>

enum BuiltinGame {
    GAME_SD,
    GAME_SNAKE,
    GAME_DODGE,
    GAME_PONG
};

static String currentGame;
static BuiltinGame gameType = GAME_SD;
static bool gameOver = false;
static unsigned long lastFrame = 0;

static const int SW = 128;
static const int SH = 64;

static int wrapValue(int value, int limit) {
    if (value < 0) return limit - 1;
    if (value >= limit) return 0;
    return value;
}

static void showGameOver(const char *name, int score) {
    display.clearDisplay();
    display.setCursor(30, 10);
    display.print(name);
    display.setCursor(38, 28);
    display.print("GAME OVER");
    display.setCursor(38, 42);
    display.print("SCORE ");
    display.print(score);
    display.display();
}

static int snakeX[64];
static int snakeY[64];
static int snakeLength;
static int snakeDir;
static int snakeFoodX;
static int snakeFoodY;
static int snakeScore;
static unsigned long snakeTick;

static void snakePlaceFood() {
    bool valid;

    do {
        valid = true;
        snakeFoodX = random(0, 21);
        snakeFoodY = random(0, 8);

        for (int i = 0; i < snakeLength; ++i) {
            if (snakeX[i] == snakeFoodX && snakeY[i] == snakeFoodY) {
                valid = false;
                break;
            }
        }
    } while (!valid);
}

static void snakeBegin() {
    snakeLength = 3;
    snakeX[0] = 10;
    snakeY[0] = 4;
    snakeX[1] = 9;
    snakeY[1] = 4;
    snakeX[2] = 8;
    snakeY[2] = 4;
    snakeDir = 0;
    snakeScore = 0;
    snakeTick = millis();
    gameOver = false;
    snakePlaceFood();
}

static void snakeSetDirection(int direction) {
    if ((snakeDir == 0 && direction == 2) ||
        (snakeDir == 2 && direction == 0) ||
        (snakeDir == 1 && direction == 3) ||
        (snakeDir == 3 && direction == 1)) {
        return;
    }

    snakeDir = direction;
}

static void snakeUpdate() {
    if (gameOver) {
        if (buttonPressed(BUTTON_RIGHT)) snakeBegin();
        showGameOver("SNAKE", snakeScore);
        return;
    }

    if (buttonDown(BUTTON_UP)) snakeSetDirection(0);
    if (buttonDown(BUTTON_RIGHT)) snakeSetDirection(1);
    if (buttonDown(BUTTON_DOWN)) snakeSetDirection(2);
    if (buttonDown(BUTTON_LEFT)) snakeSetDirection(3);

    int turn = encoderDelta();
    if (turn > 0) snakeSetDirection((snakeDir + 1) & 3);
    if (turn < 0) snakeSetDirection((snakeDir + 3) & 3);

    if (millis() - snakeTick < 150) return;
    snakeTick = millis();

    int nx = snakeX[0];
    int ny = snakeY[0];

    if (snakeDir == 0) ny--;
    if (snakeDir == 1) nx++;
    if (snakeDir == 2) ny++;
    if (snakeDir == 3) nx--;

    if (nx < 0 || nx >= 21 || ny < 0 || ny >= 8) {
        gameOver = true;
        return;
    }

    for (int i = 0; i < snakeLength; ++i) {
        if (snakeX[i] == nx && snakeY[i] == ny) {
            gameOver = true;
            return;
        }
    }

    bool eat = nx == snakeFoodX && ny == snakeFoodY;

    if (eat && snakeLength < 64) {
        ++snakeLength;
        ++snakeScore;
    }

    for (int i = snakeLength - 1; i > 0; --i) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    snakeX[0] = nx;
    snakeY[0] = ny;

    if (eat) snakePlaceFood();
}

static void snakeDraw() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("SNAKE ");
    display.print(snakeScore);

    for (int i = 0; i < snakeLength; ++i) {
        display.fillRect(
            snakeX[i] * 6,
            10 + snakeY[i] * 6,
            5,
            5,
            SSD1306_WHITE
        );
    }

    display.fillRect(
        snakeFoodX * 6,
        10 + snakeFoodY * 6,
        5,
        5,
        SSD1306_WHITE
    );

    display.display();
}

static int dodgePlayerX;
static int dodgeY[3];
static int dodgeX[3];
static int dodgeScore;
static unsigned long dodgeTick;

static void dodgeResetObstacle(int index) {
    dodgeX[index] = random(0, 124);
    dodgeY[index] = -random(4, 25);
}

static void dodgeBegin() {
    dodgePlayerX = 60;
    dodgeScore = 0;
    dodgeTick = millis();
    gameOver = false;

    for (int i = 0; i < 3; ++i) {
        dodgeResetObstacle(i);
        dodgeY[i] -= i * 18;
    }
}

static void dodgeUpdate() {
    if (gameOver) {
        if (buttonPressed(BUTTON_RIGHT)) dodgeBegin();
        showGameOver("DODGE", dodgeScore);
        return;
    }

    if (buttonDown(BUTTON_LEFT)) dodgePlayerX -= 2;
    if (buttonDown(BUTTON_RIGHT)) dodgePlayerX += 2;

    int encoder = encoderDelta();
    dodgePlayerX += encoder * 3;

    dodgePlayerX = constrain(dodgePlayerX, 0, 118);

    if (millis() - dodgeTick < 35) return;
    dodgeTick = millis();

    int speed = 1 + min(dodgeScore / 10, 3);

    for (int i = 0; i < 3; ++i) {
        dodgeY[i] += speed;

        if (dodgeY[i] > 62) {
            dodgeResetObstacle(i);
            ++dodgeScore;
        }

        int oy = dodgeY[i];
        int ox = dodgeX[i];

        if (
            ox < dodgePlayerX + 10 &&
            ox + 4 > dodgePlayerX &&
            oy < 61 &&
            oy + 4 > 55
        ) {
            gameOver = true;
            return;
        }
    }
}

static void dodgeDraw() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("DODGE ");
    display.print(dodgeScore);

    display.fillRect(
        dodgePlayerX,
        55,
        10,
        5,
        SSD1306_WHITE
    );

    for (int i = 0; i < 3; ++i) {
        display.fillRect(
            dodgeX[i],
            dodgeY[i],
            5,
            5,
            SSD1306_WHITE
        );
    }

    display.display();
}

static int pongPlayerX;
static int pongBallX;
static int pongBallY;
static int pongBallDX;
static int pongBallDY;
static int pongAiX;
static int pongScore;
static unsigned long pongTick;

static void pongBegin() {
    pongPlayerX = 51;
    pongAiX = 51;
    pongBallX = 62;
    pongBallY = 32;
    pongBallDX = random(0, 2) ? 1 : -1;
    pongBallDY = 1;
    pongScore = 0;
    pongTick = millis();
    gameOver = false;
}

static void pongUpdate() {
    if (gameOver) {
        if (buttonPressed(BUTTON_RIGHT)) pongBegin();
        showGameOver("PONG", pongScore);
        return;
    }

    if (buttonDown(BUTTON_LEFT)) pongPlayerX -= 2;
    if (buttonDown(BUTTON_RIGHT)) pongPlayerX += 2;
    if (buttonDown(BUTTON_UP)) pongPlayerX -= 1;
    if (buttonDown(BUTTON_DOWN)) pongPlayerX += 1;

    pongPlayerX += encoderDelta() * 2;
    pongPlayerX = constrain(pongPlayerX, 0, 116);

    if (millis() - pongTick < 25) return;
    pongTick = millis();

    if (pongAiX + 4 < pongBallX) pongAiX++;
    if (pongAiX > pongBallX) pongAiX--;
    pongAiX = constrain(pongAiX, 0, 116);

    pongBallX += pongBallDX;
    pongBallY += pongBallDY;

    if (pongBallX <= 0 || pongBallX >= 127) {
        pongBallDX = -pongBallDX;
        pongBallX += pongBallDX;
    }

    if (pongBallY <= 11) {
        pongBallDY = 1;
    }

    if (
        pongBallY >= 55 &&
        pongBallY <= 60 &&
        pongBallX >= pongPlayerX - 2 &&
        pongBallX <= pongPlayerX + 18
    ) {
        pongBallDY = -1;
        ++pongScore;
    }

    if (
        pongBallY <= 17 &&
        pongBallY >= 13 &&
        pongBallX >= pongAiX - 2 &&
        pongBallX <= pongAiX + 18
    ) {
        pongBallDY = 1;
    }

    if (pongBallY > 63) {
        gameOver = true;
    }
}

static void pongDraw() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("PONG ");
    display.print(pongScore);

    display.fillRect(
        pongAiX,
        13,
        18,
        4,
        SSD1306_WHITE
    );

    display.fillCircle(
        pongBallX,
        pongBallY,
        2,
        SSD1306_WHITE
    );

    display.fillRect(
        pongPlayerX,
        58,
        18,
        4,
        SSD1306_WHITE
    );

    display.display();
}

void gameBegin(const String &path) {
    currentGame = path;
    randomSeed((uint32_t)esp_random());

    if (path == "FLASH/SNAKE") {
        gameType = GAME_SNAKE;
        snakeBegin();
    } else if (path == "FLASH/DODGE") {
        gameType = GAME_DODGE;
        dodgeBegin();
    } else if (path == "FLASH/PONG") {
        gameType = GAME_PONG;
        pongBegin();
    } else {
        gameType = GAME_SD;
        gameOver = false;
        lastFrame = millis();
    }
}

void gameUpdate() {
    if (gameType == GAME_SNAKE) {
        snakeUpdate();
        if (!gameOver) snakeDraw();
        return;
    }

    if (gameType == GAME_DODGE) {
        dodgeUpdate();
        if (!gameOver) dodgeDraw();
        return;
    }

    if (gameType == GAME_PONG) {
        pongUpdate();
        if (!gameOver) pongDraw();
        return;
    }

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("SD GAME");
    display.setCursor(0, 16);
    display.print(currentGame);
    display.setCursor(0, 34);
    display.print("LEFT HOLD = MENU");
    display.display();
}
