/*
---------------------------------------------
|           ONLY FOR WINDOWS                |
---------------------------------------------
 */
#if (defined(__WIN32) || defined(__WIN64) ) && (!defined(CONSOLE_UTIL_FOR_WINDOWS))
#define CONSOLE_UTIL_FOR_WINDOWS

#include<iostream>
#include<windows.h>

namespace console{
    const int 
        CURRENT_COLOR = -1,
        BLACK = 0,
        BLUE = 1,
        GREEN = 2,
        CYAN = 3,
        RED = 4,
        PURPLE = 5,
        YELLOW = 6,
        WHITE = 7,
        GRAY = 8,
        LIGHT_BLUE = 9,
        LIGHT_GREEN = 10,
        LIGHT_CYAN = 11,
        LIGHT_RED = 12,
        LIGHT_PURPLE = 13,
        LIGHT_YELLOW = 14,
        BRIGHT_WHITE = 15;

    struct Color{
        int text;
        int background;
        Color(): text(CURRENT_COLOR), background(CURRENT_COLOR){}
        Color(int text, int background): text(text), background(background){}
    };

    struct Coord{
        int x;
        int y;
        Coord():x(0), y(0){}
        Coord(int x, int y):x(x), y(y){}
        Coord operator+(Coord other){
            return Coord(x + other.x, y + other.y);
        } 
        Coord operator-(Coord other){
            return Coord(x - other.x, y - other.y);
        }
    };  
    
    /*
    -----------------------------------------------------
    |               FUNCTION PROTOTYPE                  |
    -----------------------------------------------------
    */

    Color getColor();
    void setColor(int text, int background);
    void setColor(Color c);
    void setTextColor(int textColor);
    void setBackgroundColor(int backgroundColor);

    //set color while using cout<<
    std::ostream& operator<<(std::ostream& os, Color c);

    Coord getConsoleSize();
    Coord where();
    void gotoxy(int x, int y);
    void gotoxy(Coord coord);

    //gotoxy while using cout <<
    std::ostream& operator<<(std::ostream& os, Coord c); 
    
    void setCursorVisible(bool visible);

    /*
    -----------------------------------------------------
    |               FUNCTION DEFINITION                 |
    -----------------------------------------------------
    */

    Color getColor() {
        Color currentColor;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        int attributes = csbi.wAttributes; 
        currentColor.text = attributes & 0x0F;
        currentColor.background = (attributes & 0xF0) >> 4;
        return currentColor;
    }

    void setColor(int text, int background) {
        if(! (text >= CURRENT_COLOR && text <= BRIGHT_WHITE))
            text = -1;
        if(! (background >= CURRENT_COLOR && background <= BRIGHT_WHITE) )
            background = -1;

        if(text == CURRENT_COLOR || background == CURRENT_COLOR){
            Color currentColor = getColor();
            if(text == CURRENT_COLOR)
                text = currentColor.text;
            if(background == CURRENT_COLOR){
                background = currentColor.background;
            }
        }
        int color = text + (background * 16);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    void setColor(Color c){
        setColor(c.text, c.background);
    }

    void setTextColor(int textColor) {
        setColor(textColor, CURRENT_COLOR);
    }

    void setBackgroundColor(int backgroundColor) {
        setColor(CURRENT_COLOR, backgroundColor);
    }

    std::ostream& operator<<(std::ostream& os, Color c){
        setColor(c);
        return os;
    }


    Coord getConsoleSize(){
        Coord size;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        size.x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        size.y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        return size;
    }

    Coord where(){
        Coord current;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        current.x = csbi.dwCursorPosition.X;
        current.y = csbi.dwCursorPosition.Y;
        
        return current;
    }

    void gotoxy(int x, int y){
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos = { (SHORT)x, (SHORT)y };
        SetConsoleCursorPosition(hConsole, pos);
    }

    void gotoxy(Coord c){
        gotoxy(c.x, c.y);
    }

    std::ostream& operator<<(std::ostream& os, Coord c){
        gotoxy(c);
        return os;
    }

    void setCursorVisible(bool visible) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
    
        GetConsoleCursorInfo(hConsole, &cursorInfo);
        cursorInfo.bVisible = visible;
        SetConsoleCursorInfo(hConsole, &cursorInfo);
    }
}


#endif