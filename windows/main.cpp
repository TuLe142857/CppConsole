#include<iostream>
#include<conio.h>
#include<iomanip>
#include"console.h"
#include"keyboard.h"

using namespace std;

void testColor();

int main(){
    const console::Color
        BW(console::BLACK, console::WHITE), 
        WB(console::WHITE, console::BLACK),
        RB(console::RED, console::BLACK),
        GB(console::GREEN, console::BLACK);
        

    testColor();
    cout << "press any key to continue...";
    getch();
    system("cls");

    cout << "Hello world" << endl;
    console::Coord screen_size = console::getConsoleSize();
    console::Coord current = console::where();
    cout << "Sceen size: " << screen_size.x << "x" << screen_size.y
         << current + console::Coord(10, 1) << RB << "Title red on black"
         << current + console::Coord(3, 2)  << WB << "Content white on black"
         << current + console::Coord(3, 3)  << GB << "Content green on black";

    return 0;
}

void testColor(){
    console::Color defaultColor = console::getColor();

    string colorName[]={
        "black",
        "blue",
        "green",
        "cyan",
        "red",
        "purple",
        "yellow",
        "white",
        "gray",
        "light-blue",
        "light-green",
        "light-cyan",
        "light-red",
        "light-purple",
        "light-yellow",
        "bright-white"
    };
    
    int colorValue[]={
        console::BLACK,
        console::BLUE,
        console::GREEN,
        console::CYAN,
        console::RED,
        console::PURPLE,
        console::YELLOW,
        console::WHITE,
        console::GRAY,
        console::LIGHT_BLUE,
        console::LIGHT_GREEN,
        console::LIGHT_CYAN,
        console::LIGHT_RED,
        console::LIGHT_PURPLE,
        console::LIGHT_YELLOW,
        console::BRIGHT_WHITE
    };


    cout << left << "-------------- TEST COLOR --------------\n";
    cout << setw(25) << "text" << setw(25) << "background"  << "Result" << endl;
    for(int text : colorValue)
        for(int background : colorValue){
            cout << right << " " << console::Color(-1, text) << "   " << defaultColor << " "
                 << left << setw(20) << defaultColor << colorName[text]
                 << right << " " << console::Color(-1, background) << "   " << defaultColor << " "
                 << left << setw(20) << defaultColor << colorName[background]
                 << left << console::Color(text, background) << "Sample Text" << defaultColor << endl;
        }
}
