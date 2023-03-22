#include "Canvas.h"

Canvas::Canvas(int width, int height) {
    this->width = width;
    this->height = height;
}

Canvas::~Canvas() {
    release();
}

void Canvas::init() {
    // None
}

void Canvas::draw(char wall, bool playAnim, long animSpeed) {
    cout << "\033[33m";

    gotoStart();
    for (int i = 0; i < width; i++) {
        if (playAnim) {
            Sleep(animSpeed);
        }
        printChar(wall);
    }

    for (int i = 0; i < height; i++) {
        gotoXY(0, i);
        if (playAnim) {
            Sleep(animSpeed);
        }
        printChar(wall);
    }
    for (int i = 0; i < height; i++) {
        gotoXY(width, i);
        if (playAnim) {
            Sleep(animSpeed);
        }
        printChar(wall);
    }

    gotoXY(0, height);
    for (int i = 0; i < width; i++) {
        if (playAnim) {
            Sleep(animSpeed);
        }
        printChar(wall);
    }

    cout << "\033[0m";
}

void Canvas::redraw() {
    clrscr();
    draw();
}

void Canvas::release() {
    // None
}

void Canvas::gotoXY(int x, int y, bool isLimit) {
    if (isLimit) {
        if (x > width) {
            x = width;
        }
        if (y > height) {
            y = height;
        }
    }

    printf("\033[%d;%dH", y, x);

    pointerX = x;
    pointerY = y;
}

void Canvas::gotoStart() {
    gotoXY(0, 0, false);
}

void Canvas::gotoEnd() {
    gotoXY(0, height + 1, false);
}

void Canvas::hidePointer() {
    cout << "\033[?25l";
}

void Canvas::showPointer() {
    cout << "\033[?25h";
}

void Canvas::clrscr() {
    system(CLEAR_CMD_TEXT);
}

void Canvas::printStrings(string strs[], int len, bool isCenterShow) {
    for (int i = 0; i < len; i++) {
        string text = strs[i];
        if (isCenterShow) {
            gotoXY(width / 2 - (unsigned int) text.length() / 2, height / 2 - len + i + 3);
        } else {
            gotoXY(2, i + 2);
        }
        cout << text;
    }
}

void Canvas::printChar(char c, bool isWrap) {
    cout << c;

    if (isWrap) {
        cout << endl;
    }
}
