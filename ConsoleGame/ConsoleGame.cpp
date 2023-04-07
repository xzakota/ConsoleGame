#include <csignal>
#include "SnakeGame.h"
#include "C2048Game.h"

// 当前游戏
Game* game = NULL;
// 首页画布
Canvas* homeCanvas = new Canvas();

// 退出游戏函数
void stopGame(int signum) {
    if (game != NULL) {
        game->stop(signum);
    }
    cout << "\nExit code: " << signum << "\n";
    system(STOP_CMD_TEXT);
    delete homeCanvas;
    exit(signum);
}

// 主函数
int main() {
    #ifdef _MSC_VER
    SetConsoleTitle(TEXT("Console Game"));
    #endif // _MSC_VER


    // 处理程序被 Ctrl + C 终止
    signal(SIGINT, stopGame);

    // 首页提示文本
    string texts[] = {
        "hello, please choose",
        "0. exit",
        "1. SnakeGame",
        "2. 2048 Game"
    };
    // 首页画布宽高
    homeCanvas->width = 50;
    homeCanvas->height = 8;

    // 绘制首页
    homeCanvas->clrscr();
    homeCanvas->draw(DEFAULT_WALL_CHAR, false);
    homeCanvas->printStrings(texts, 4);
    homeCanvas->gotoEnd();

    // 监听用户选择
    char inputChar = 0;
    do {
        if (_kbhit()) {
            inputChar = _getch();
        }
    } while (inputChar < '0' || inputChar > '2');

    cout << inputChar;
    switch (inputChar) {
        default:
        case '0':
            goto end;
            break;
        case '1':
            game = &SnakeGame::build();
            break;
        case '2':
            game = &C2048Game::build();
            break;
    }

    // 进入游戏欢迎页
    game->welcome();

    end: stopGame(0);

    return 0;
}
