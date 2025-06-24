#ifndef CUSTOM_HPP
#define CUSTOM_HPP

#include<cstdlib>

#ifdef _WIN32
    #include <conio.h>
    #ifndef getch
    #define getch() _getch()
    #endif // !getch
    
    inline void clearScreen() { 
        system("cls"); 
    }

#else
    #include <termios.h>
    #include <unistd.h>
    #include <cstdio>
    
    inline void clearScreen() { 
        system("clear"); 
    }
    
    inline char getch() {
        char buf = 0;
        struct termios old{};
        if (tcgetattr(STDIN_FILENO, &old) < 0) perror("tcgetattr()");
        struct termios current = old;
        current.c_lflag &= ~ICANON;
        current.c_lflag &= ~ECHO;
        if (tcsetattr(STDIN_FILENO, TCSANOW, &current) < 0) perror("tcsetattr ICANON");
        if (read(STDIN_FILENO, &buf, 1) < 0) perror("read()");
        if (tcsetattr(STDIN_FILENO, TCSANOW, &old) < 0) perror("tcsetattr ~ICANON");
        return buf;
    }
#endif // !LOGIC

#endif // !CUSTOM_HPP
