#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>
#include "Settings.h"


// some macro soup to account for compiling on different platforms
#if defined(_WIN32) || defined(_WIN64)

#define OS_WINDOWS

// defines _kbhit() and _getch()
#   include <conio.h>
#elif defined(__linux__)

#define OS_LINUX

#   include <termios.h>
#   include <unistd.h>
#   include <stdio.h>

    /* 
        reads from keypress, doesn't echo. same functionality 
        as Windows function with same signature 

        EDIT: idk if its a game bug or a library bug but wasd 
        does not work when compiling for linux
    */
    int _getch(void) {
        struct termios oldattr, newattr;
        int ch;
        tcgetattr( STDIN_FILENO, &oldattr );
        newattr = oldattr;
        newattr.c_lflag &= ~( ICANON | ECHO );
        tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
        ch = getchar();
        tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
        return ch;
    }

    int _kbhit(void) {
        timeval timeout;
        fd_set rdset;

        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO, &rdset);
        timeout.tv_sec  = 0;
        timeout.tv_usec = 0;

        return select(STDIN_FILENO + 1, &rdset, NULL, NULL, &timeout); 
    }

#else
#   error support for iOS/MacOS untested
#endif // various defines
