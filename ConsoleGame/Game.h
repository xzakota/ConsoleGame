#ifndef _GAME_H_
#define _GAME_H_

#include "Canvas.h"
#include "GameRes.h"
#include "KeyControl.h"

// 游戏抽象类
class Game {
protected:
    // 游戏画布实例
    Canvas *gameCanvas;

    // 输入键
    int inuptKey = KEY_RIGHT;
    // 分数
    int score = 0;

    /**
     * 构造函数
     */
    Game();
    /**
     * 析构函数
     */
    virtual ~Game() = 0;

    /**
     * 获取游戏信息
     */
    virtual GameInfo getGameInfo() = 0;
public:
    /**
     * 欢迎界面
     *
     * isAutoStart 自动开始游戏
     */
    virtual void welcome(bool isAutoStart = true);
    /**
     * 开始
     */
    virtual void start();
    /**
     * 暂停
     */
    virtual void pause();
    /**
     * 结束
     *
     * signum 结束代码
     */
    virtual void stop(int signum);
};

#endif /* _GAME_H_ */
