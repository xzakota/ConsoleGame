#ifndef _SNAKE_GAME_H_
#define _SNAKE_GAME_H_

#include <cstring>
#include <vector>
#include "Game.h"

// 贪吃蛇游戏主类
class SnakeGame : public Game {
private:
    // 存储 蛇 容器
    std::vector<Node> snake;

    // 实际方向状态
    int snakeStatus = KEY_RIGHT;
    // 刷新速度
    long speed = 250;
    // 食物 使用类内初始化防止警告
    Node food{};

    /**
     * 初始化 蛇
     *
     * snakeLength 初始长度
     */
    void initSnake(int snakeLength = 3);
    /**
     * 显示 蛇
     * 
     * showType 显示方式
     */
    void showSnake(int showType = 2);
    /**
     * 移动 蛇
     *
     * isWait 速度控制
     */
    void moveSnake(bool isWait = true);
    /**
     * 删除 蛇
     */
    void deleteSnake();

    /**
     * 生成食物
     */
    void generateFood();
    /**
     * 是否吃到食物
     */
    bool eatingFood();
    /**
     * 游戏是否 Over
     */
    bool isGameOver();
public:
    /**
     * 获取游戏信息
     */
    GameInfo getGameInfo();
    /**
     * 获取游戏实例
     */
    static SnakeGame& build();

    /**
     * 欢迎界面
     *
     * isAutoStart 自动开始游戏
     */
    void welcome(bool isAutoStart = true);
    /**
     * 开始
     */
    void start();
    /**
     * 结束
     *
     * signum 结束代码
     */
    void stop(int signum);
};

#endif /* _SNAKE_GAME_H_ */
