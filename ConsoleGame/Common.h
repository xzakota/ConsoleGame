#ifndef _COMMON_H_
#define _COMMON_H_

#include <iostream>
#include <cstdarg>

#ifdef __GNUC__
#include "conio.h"
#define Sleep(x) usleep(x * 1E3)
#define CLEAR_CMD_TEXT "clear"
#endif // __GNUC__

#ifdef _MSC_VER
#include <Windows.h>
#include <conio.h>
#define CLEAR_CMD_TEXT "cls"
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
