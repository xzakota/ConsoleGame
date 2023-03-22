#include "Game.h"

Game::Game() {
    gameCanvas = new Canvas();
}

Game::~Game() {
    delete gameCanvas;
}

void Game::welcome(bool isAutoStart) {
    gameCanvas->clrscr();
    gameCanvas->draw(DEFAULT_WALL_CHAR, false);

    GameInfo info = getGameInfo();

    string welcomeTexts[] = {
        formatString("Welcome to %s!", info.name.data()),
        formatString("By %s", info.author.data()),
        formatString("Version %s", info.versionName.data()),
        "Press Key 'y' to continue."
    };
    gameCanvas->printStrings(welcomeTexts, 4);

    gameCanvas->gotoEnd();

    for (char inputChar = 0; inputChar != 0x59 && inputChar != 0x79;) {
        if (_kbhit()) {
            inputChar = _getch();
        }
    }

    if (isAutoStart) {
        start();
    }
}

void Game::start() {
    gameCanvas->hidePointer();
}

void Game::pause() {
    while (true) {
        if ((inuptKey = _getch()) == KEY_SPACE) {
            break;
        }
    }
}

void Game::stop(int signum) {
    cout << "\n\033[41;1mGame Over!!\033[0m\n";
    gameCanvas->showPointer();
    gameCanvas->release();
}
