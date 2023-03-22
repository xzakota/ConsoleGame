#include "SnakeGame.h"

GameInfo SnakeGame::getGameInfo() {
    GameInfo info = GameInfo();
    info.name = "SnakeGame";
    info.versionName = "alpha-1.0";
    return info;
}

SnakeGame& SnakeGame::build() {
    static SnakeGame game = SnakeGame();
    return game;
}

void SnakeGame::welcome(bool isAutoStart) {
    Game::welcome(isAutoStart);
}

void SnakeGame::start() {
    Game::start();

    gameCanvas->redraw();
    gameCanvas->gotoEnd();

    // 用时间初始化随机数产生器
    srand((unsigned) time(NULL));

    initSnake();

    cout << formatString("Game help: \t%c←\t%c↑\t%c→\t%c↓, \n\t\tSpace key to pause/resume \n", KEY_LEFT, KEY_UP, KEY_RIGHT, KEY_DOWN);
    cout << formatString("Snake length: %d\nYour score: %d", (unsigned int) snake.size(), score);

    showSnake(1);
    generateFood();

    do {
        if (isGameOver()) {
            gameCanvas->gotoXY(snake[0].x, snake[0].y);
            cout << "\033[31mX\033[0m";
            break;
        }
        if (_kbhit()) {
            fflush(stdin);
            inuptKey = _getch();
        }

        moveSnake();
    } while (true);

    stop(0);
}

void SnakeGame::stop(int signum) {
    gameCanvas->gotoEnd();
    cout << "\n\n\n";

    Game::stop(signum);
}

bool SnakeGame::isGameOver() {
    Node snakeHead = snake[0];
    // 是否撞墙判断
    if (snakeHead.x == 1 || snakeHead.x == gameCanvas->width || snakeHead.y == 1 || snakeHead.y == gameCanvas->height) {
        return true;
    }

    // 循环蛇身
    vector<Node>::iterator iterator = snake.begin() + 1;
    while (iterator != snake.end()) {
        // 是否撞到蛇身
        if (snakeHead.x == iterator->x && snakeHead.y == iterator->y) {
            return true;
        }
        iterator++;
    }
    return false;
}

void SnakeGame::initSnake(int snakeLength) {
    Node snakeHead = Node();
    snakeHead.x = gameCanvas->width / 2;
    snakeHead.y = gameCanvas->height / 2;
    snake.push_back(snakeHead);

    for (int i = 0; i < snakeLength; i++) {
        Node snakeBody = Node();
        snakeBody.x = snakeHead.x;
        snakeBody.y = snakeHead.y - i - 1;

        snake.push_back(snakeBody);
    }
}

void SnakeGame::showSnake(int showType) {
    Node snakeHead = snake[0];
    gameCanvas->gotoXY(snakeHead.x, snakeHead.y);
    cout << "\033[32m@\033[0m";

    if (showType == 1) {
        vector<Node>::iterator iterator = snake.begin() + 1;
        while (iterator != snake.end()) {
            gameCanvas->gotoXY(iterator->x, iterator->y);
            cout << 'O';
            iterator++;
        }
    } else if (showType == 2) {
        // 蛇头恢复蛇身
        snakeHead = snake[1];
        gameCanvas->gotoXY(snakeHead.x, snakeHead.y);
        cout << "O";
    }

    gameCanvas->gotoEnd();
}

void SnakeGame::moveSnake(bool isWait) {
    // 存储蛇头节点
    Node snakeHead = snake[0];
    int x = snakeHead.x, y = snakeHead.y;

    // 输入键判断移动方向
    switch (inuptKey) {
        case KEY_UP:
            if (snakeStatus != KEY_DOWN) {
                snakeStatus = KEY_UP;
            }
            break;
        case KEY_DOWN:
            if (snakeStatus != KEY_UP) {
                snakeStatus = KEY_DOWN;
            }
            break;
        case KEY_LEFT:
            if (snakeStatus != KEY_RIGHT) {
                snakeStatus = KEY_LEFT;
            }
            break;
        case KEY_RIGHT:
            if (snakeStatus != KEY_LEFT) {
                snakeStatus = KEY_RIGHT;
            }
            break;
        case KEY_SPACE:
            pause();
            break;
        default:
            break;
    }

    Node snakeTail = snake[snake.size() - 1];

    // 蛇的移动方向得到新的蛇头节点坐标
    switch (snakeStatus) {
        case KEY_UP:
            y -= 1;
            break;
        case KEY_DOWN:
            y += 1;
            break;
        case KEY_LEFT:
            x -= 1;
            break;
        case KEY_RIGHT:
            x += 1;
            break;
        default:
            break;
    }

    // 弹出存储蛇的 vector 的最后一个元素，插入新元素到开头作为新蛇头
    if (x != snakeHead.x || y != snakeHead.y) {
        snake.pop_back();

        Node snakeNewHead = Node();
        snakeNewHead.x = x;
        snakeNewHead.y = y;
        snake.insert(snake.begin(), snakeNewHead);
    }

    // 吃到食物判断
    if (eatingFood()) {
        // 长度显示
        snake.push_back(snakeTail);
        gameCanvas->gotoXY(15, gameCanvas->height + 3, false);
        cout << snake.size();

        // 分数显示
        gameCanvas->gotoXY(13, gameCanvas->height + 4, false);
        score += 10;
        cout << score;

        gameCanvas->gotoEnd();
        // 重新生成食物
        generateFood();
    } else {
        // 消除(取消显示)蛇身最后一个节点达到移动的效果
        gameCanvas->gotoXY(snakeTail.x, snakeTail.y);
        cout << (char)0x20;
    }

    // 显示蛇
    showSnake(2);

    // 使用 sleep 函数休眠达到移动速度效果
    if (isWait) {
        Sleep(speed);
    }
}

void SnakeGame::deleteSnake() {
    // None
}

void SnakeGame::generateFood() {
    // 随机产生食物的坐标
    food.x = rand() % (gameCanvas->width - 2) + 2;
    food.y = rand() % (gameCanvas->height - 2) + 2;

    vector<Node>::iterator iterator = snake.begin();
    while (iterator != snake.end()) {
        // 食物不能生成在蛇头或蛇身节点同坐标处
        if (food.x == iterator->x && food.y == iterator->y) {
            generateFood();
            return;
        }
        iterator++;
    }
    // 显示食物
    gameCanvas->gotoXY(food.x, food.y);
    cout << "\033[36m*\033[0m";

    gameCanvas->gotoEnd();
}

bool SnakeGame::eatingFood() {
    Node snakeHead = snake[0];
    // 蛇头节点与食物节点同坐标即吃到食物
    if (snakeHead.x == food.x && snakeHead.y == food.y) {
        return true;
    }

    return false;
}
