#ifndef _GAME_RES_H_
#define _GAME_RES_H_

// 游戏信息类
class GameInfo {
public:
    string name;
    string author = "XZAKOTA";
    int versionCode = 1;
    string versionName = "1.0";
};

// 坐标节点结构体
typedef struct NODE {
    int x;
    int y;
} Node;

// 颜色结构体
class Color {
public:
    int red;
    int green;
    int blue;
    int alpha;

    Color() = default;
    Color(int red, int green, int blue, int alpha = 0xFF) 
        : red(red), green(green), blue(blue), alpha(alpha) {};

    string toEscapeArgument() {
        return formatString("2;%d;%d;%d", red, green, blue);
    }
};

#endif /* _GAME_RES_H_ */
