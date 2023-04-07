#ifndef _COMMON_H_
#define _COMMON_H_

#include <iostream>
#include <ctime>
#include <string>
#include <cstdarg>

#ifdef __GNUC__
#include "conio.h"
#define Sleep(x) usleep(x * 1E3)
#define CLEAR_CMD_TEXT "clear"
#define START_CMD_TEXT ""
#define STOP_CMD_TEXT "echo \"按回车键退出...\";read -s -n 1"
#endif // __GNUC__

#ifdef _MSC_VER
#include <Windows.h>
#include <conio.h>
#define CLEAR_CMD_TEXT "cls"
#define START_CMD_TEXT "chcp 65001"
#define STOP_CMD_TEXT "pause"
#endif // _MSC_VER

using namespace std;

static string formatString(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    const size_t len = vsnprintf(nullptr, 0, fmt, args);
    va_end(args);
    string r;
    r.resize(static_cast<size_t>(len) + 1);
    va_start(args, fmt);
    vsnprintf(&r.front(), len + 1, fmt, args);
    va_end(args);
    r.resize(static_cast<size_t>(len));

    return r;
}

#endif /* _COMMON_H_ */
