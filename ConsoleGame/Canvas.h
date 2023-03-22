#ifndef _CANVAS_H_
#define _CANVAS_H_

#include "Common.h"

// 默认宽高宏定义
#define DEFAULT_CANVAS_WIDTH 60
#define DEFAULT_CANVAS_HEIGHT 20

#define DEFAULT_WALL_CHAR '#'

// 画布（模拟）
class Canvas {
private:
    // 当前指针横坐标
    int pointerX = 0;
    // 当前指针纵坐标
    int pointerY = 0;
public:
    // 宽度
    int width;
    // 高度
    int height;

    /**
     * 构造函数
     */
    Canvas(int width = DEFAULT_CANVAS_WIDTH, int height = DEFAULT_CANVAS_HEIGHT);
    /**
     * 析构函数
     */
    ~Canvas();

    /**
     * 初始化
     */
    void init();
    /**
     * 绘制
     * 
     * wall 墙体显示符号
     * playAnim 是否播放动画
     * animSpeed 动画速度
     */
    void draw(char wall = DEFAULT_WALL_CHAR, bool playAnim = true, long animSpeed = 5);
    /**
     * 重新绘制
     */
    void redraw();
    /**
     * 释放资源
     */
    void release();

    /**
     * 移动到 XY 处
     * 
     * x 横坐标
     * y 纵坐标
     * isLimit 是否限制在画布内
     */
    void gotoXY(int x, int y, bool isLimit = true);
    /**
     * 移动到开头
     */
    void gotoStart();
    /**
     * 移动到结尾
     */
    void gotoEnd();
    /**
     * 隐藏输入光标
     */
    void hidePointer();
    /**
     * 显示输入光标
     */
    void showPointer();
    /**
     * 清屏
     */
    void clrscr();
    /**
     * 输出字符串数组
     * 
     * strs 字符串数组
     * len 数组长度
     * isCenterShow 居中显示
     */
    void printStrings(string strs[], int len, bool isCenterShow = true);
    /**
     * 输出字符
     * 
     * c 字符
     * isWrap 自动换行
     */
    void printChar(char c, bool isWrap = false);
};

#endif /* _CANVAS_H_ */
