#include "C2048Game.h"
#include <string.h>

GameInfo C2048Game::getGameInfo() {
    GameInfo info = GameInfo();
    info.name = "2048 Game";
    info.versionName = "alpha-1.0";
    return info;
}

C2048Game& C2048Game::build() {
    static C2048Game game = C2048Game();
    return game;
};

void C2048Game::welcome(bool isAutoStart) {
    Game::welcome(isAutoStart);
}

void C2048Game::start() {
    Game::start();

    gameCanvas->width = MATRIX_SIZE * 7 + 2;
    gameCanvas->height = MATRIX_SIZE * 3 + 2;
    gameCanvas->redraw();
    gameCanvas->gotoEnd();

    // 用时间初始化随机数产生器
    srand((unsigned) time(NULL));

    initData();

    cout << formatString("Game help: \t%c←\t%c↑\t%c→\t%c↓, \n\t\tSpace key to pause/resume \n", KEY_LEFT, KEY_UP, KEY_RIGHT, KEY_DOWN);
    cout << formatString("Your score: %d", score);

    showData();

    do {
        if (isGameOver()) {
            break;
        }
        if (_kbhit()) {
            fflush(stdin);
            inuptKey = _getch();

            if (moveJudge()) {
                showData();
                Sleep(150);
                loadOneRandom();
                showData();
            }
        }
    } while (true);

    stop(0);
}

void C2048Game::stop(int signum) {
    gameCanvas->gotoEnd();
    cout << "\n\n";

    Game::stop(signum);
}

bool C2048Game::isGameOver() {
    bool isOver = true;

    if (getEmptyDataSize() > 0) {
        return false;
    }
    if (hasPairDataDown()) {
        return false;
    }

    rotateData();
    if (hasPairDataDown()) {
        isOver = false;
    }
    rotateData();
    rotateData();
    rotateData();

    return isOver;
}

void C2048Game::initData() {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            data[i][j] = 0;
        }
    }

    loadOneRandom();
    loadOneRandom();
}

int C2048Game::getEmptyDataSize() {
    int size = 0;

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (data[i][j] == 0) {
                size++;
            }
        }
    }

    return size;
}

void C2048Game::loadOneRandom() {
    int i, j, len = 0;
    int list[MATRIX_SIZE * MATRIX_SIZE][2] { 0 };

    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            if (data[i][j] == 0) {
                list[len][0] = i;
                list[len][1] = j;
                len++;
            }
        }
    }

    if (len > 0) {
        int random = rand() % len;
        i = list[random][0];
        j = list[random][1];
        int value = (rand() % 10) / 9 + 1;
        data[i][j] = value;
    }
}

void C2048Game::showData() {
    for (int y = 0; y < MATRIX_SIZE; y++) {
        gameCanvas->gotoXY(2, y * 3 + 2);
        for (int x = 0; x < MATRIX_SIZE; x++) {
            string color = getColor(data[x][y]);
            cout << color;
            cout << "       ";
            cout << "\033[0m";
        }

        gameCanvas->gotoXY(2, y * 3 + 3);
        for (int x = 0; x < MATRIX_SIZE; x++) {
            string color = getColor(data[x][y]);
            cout << color;
            if (data[x][y] != 0) {
                string temp = formatString("%d", 1 << data[x][y]);
                int len = 7 - (unsigned int) temp.length();
                cout << formatString("%*s%s%*s", len - len / 2, "", temp.data(), len / 2, "");
            } else {
                cout << "   *   ";
            }
            cout << "\033[0m";
        }
   
        gameCanvas->gotoXY(2, y * 3 + 4);
        for (int x = 0; x < MATRIX_SIZE; x++) {
            string color = getColor(data[x][y]);
            cout << color;
            cout << "       ";
            cout << "\033[0m";
        }
    }

    cout << "\033[0m";
    gameCanvas->gotoEnd();
}

bool C2048Game::hasPairDataDown() {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE - 1; j++) {
            if (data[i][j] == data[i][j + 1]) {
                return true;
            }
        }
    }
    return false;
}

void C2048Game::rotateData() {
    int size = MATRIX_SIZE;

    for (int i = 0; i < size / 2; i++) {
        for (int j = i; j < size - i - 1; j++) {
            int tmp = data[i][j];
            data[i][j] = data[j][size - i - 1];
            data[j][size - i - 1] = data[size - i - 1][size - j - 1];
            data[size - i - 1][size - j - 1] = data[size - j - 1][i];
            data[size - j - 1][i] = tmp;
        }
    }
}

bool C2048Game::moveJudge() {
    bool result = false;

    // 输入键判断移动方向
    switch (inuptKey) {
        case KEY_UP:
            for (int i = 0; i < MATRIX_SIZE; i++) {
                result |= moveData(data[i]);
            }
            break;
        case KEY_DOWN:
            rotateData();
            rotateData();
            inuptKey = KEY_UP;
            result = moveJudge();
            rotateData();
            rotateData();
            break;
        case KEY_LEFT:
            rotateData();
            inuptKey = KEY_UP;
            result = moveJudge();
            rotateData();
            rotateData();
            rotateData();
            break;
        case KEY_RIGHT:
            rotateData();
            rotateData();
            rotateData();
            inuptKey = KEY_UP;
            result = moveJudge();
            rotateData();
            break;
        case KEY_SPACE:
            pause();
            break;
        default:
            break;
    }

    return result;
}

bool C2048Game::moveData(int* array) {
    bool result = false;

    for (int i = 0, t, stop = 0; i < MATRIX_SIZE; i++) {
        if (array[i] != 0) {
            t = findTargetPosition(array, i, stop);
            // 如位置改变，则移动或合并
            if (t != i) {
                if (array[t] == 0) {
                    // 移动
                    array[t] = array[i];
                } else if (array[t] == array[i]) {
                    // 合并
                    array[t]++;

                    gameCanvas->gotoXY(13, gameCanvas->height + 3, false);
                    score += 1 << array[t];
                    cout << score;

                    stop = t + 1;
                }
                array[i] = 0;
                result = true;
            }
        }
    }

    return result;
}

int C2048Game::findTargetPosition(int* array, int o, int stop) {
    if (o == 0) {
        return o;
    }

    for (int t = o - 1;;t--) {
        if (array[t] != 0) {
            if (array[t] != array[o]) {
                return t + 1;
            }
            return t;
        } else {
            if (t == stop) {
                return t;
            }
        }
    }

    return o;
}

string C2048Game::getColor(int value) {
    Color colors[] = {
        // r     g      b
        {0xFF, 0xFF, 0xFF},
        {0x00, 0x00, 0x00},

        {0x80, 0x80, 0x80}, // 0
        {0x15, 0x1A, 0xD6}, // 2
        {0xEE, 0xC9, 0x00}, // 4
        {0x8A, 0x7A, 0x57}, // 8

        {0x33, 0xCC, 0xFF}, // 16
        {0x00, 0x33, 0x99}, // 32
        {0x33, 0x00, 0x66}, // 64

        {0x66, 0x00, 0x00}, // 128
        {0x9A, 0xE4, 0xEB}, // 256
        {0xEE, 0xF1, 0x25}, // 512

        {0xC4, 0x62, 0xE6}, // 1024
        {0x79, 0x3A, 0x19}, // 2048
        {0xFD, 0x71, 0x49}, // 4096
        {0xF3, 0xAC, 0x75}, // 8192

        {0xDE, 0x24, 0x08}, // 16384
        {0xB1, 0x9A, 0x47}, // 32768
        {0x5E, 0xFD, 0xA3}  // 65536
    };
    Color* background = colors + 2;
    Color* foreground = colors;

    if (value > 0) {
        while (value--) {
            if (background + 1 < colors + sizeof(colors) / sizeof(Color) - 1) {
                background += 1;
            }
        }
    }

    return formatString("\033[38;%s;48;%sm", 
        foreground->toEscapeArgument().data(),
        background->toEscapeArgument().data()
    );
}
