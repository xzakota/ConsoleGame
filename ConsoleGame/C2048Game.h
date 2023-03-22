#ifndef _C2018_GAME_H_
#define _C2018_GAME_H_

#include "Game.h"

#define MATRIX_SIZE 4

// 2048 游戏主类
class C2048Game : public Game {
private:
    // 数据数组，仅存储幂
    int data[MATRIX_SIZE][MATRIX_SIZE] { 0 };

    /**
     * 初始化数据
     */
    void initData();
    /**
     * 计数为空的数据（判定幂为 0 即是空）
     */
    int getEmptyDataSize();
    /**
     * 在数组一个不为空的元素位置处存储随机幂
     */
    void loadOneRandom();
    /**
     * 显示数据
     */
    void showData();
    /**
     * 向下是否有可以配对的数据
     */
    bool hasPairDataDown();
    /**
     * 旋转数据（逆时针旋转 90° 二维数组）
     */
    void rotateData();
    /**
     * 移动判断
     */
    bool moveJudge();
    /**
     * 移动数据
     * array 一行数据
     */
    bool moveData(int* array);
    /**
     * 寻找目标位置
     * array 一行数据
     * o 原位置
     */
    int findTargetPosition(int* array, int o, int stop);
    /**
     * 获取数据对应的颜色
     * 
     * value 数据对应幂
     */
    string getColor(int value);
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
    static C2048Game& build();

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

#endif /* _C2018_GAME_H_ */
