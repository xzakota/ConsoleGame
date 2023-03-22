#ifndef _CONIO_H_
#define _CONIO_H_

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>

static void terminal_lnbuf(int y) {
    struct termios T;

    tcgetattr(0, &T);

    if (y) {
        T.c_lflag |=  ICANON;
    } else {
        T.c_lflag &= ~ICANON;
    }
    
    tcsetattr(0, TCSANOW, &T);
}

static void terminal_echo(int y) {
    struct termios T;

    tcgetattr(0, &T);

    if (y) {
        T.c_lflag |=  ECHO;
    } else {
        T.c_lflag &= ~ECHO;
    }
    
    tcsetattr(0, TCSANOW, &T);
}

static void gotoxy(int x, int y) {
    printf("\x1B[%d;%df", y, x);
}

static void clrscr() {
    printf("\x1B[2J\x1B[0;0f");
}

static int getch() {
    terminal_lnbuf(0);
    terminal_echo(0);

    int ch = getchar();

    terminal_lnbuf(1);
    terminal_echo(1);

    return ch;
}

static int getche() {
    terminal_lnbuf(0);

    int ch = getchar();

    terminal_lnbuf(1);

    return ch;
}

static int kbhit() {
    terminal_lnbuf(0);
    terminal_echo(0);

    struct timeval tv;
    fd_set fds;

    FD_ZERO(&fds);
    FD_SET(0, &fds);
    tv.tv_sec  = 0;
    tv.tv_usec = 0;
    select(1, &fds, 0, 0, &tv);

    int ret = FD_ISSET(0, &fds);

    terminal_lnbuf(1);
    terminal_echo(1);

    return ret;
}

#define _gotoxy gotoxy
#define _clrscr clrscr
#define _getch  getch
#define _getche getche
#define _kbhit  kbhit

#endif /* _CONIO_H_ */