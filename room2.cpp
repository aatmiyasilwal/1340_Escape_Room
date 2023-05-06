#include <iostream>
#include <ncurses.h>
#include <locale.h>
#include <string>
#include <map>
#include "sprite.h"
#include <fstream>

using namespace std;

const int width = 48;
const int height = 15;
const int h_tBox = 5;

int yPos = height/2, xPos = 1;

void init() {
    initscr();
    cbreak();
    noecho();
}

void delayedText(WINDOW * win, int y, int x, string text) {
    int yMax, xMax, cX = x, cY = y;
    getmaxyx(win, yMax, xMax);
    
    for (int i=0; i<text.length(); i++) {
        mvwaddch(win, cY, cX, text[i]);
        wrefresh(win);
        cX++;
        napms(50);
        if (i != 0 && i % (xMax-(2*x)-1) == 0) { // centralizing
            cY++;
            cX = x;
        }
        //implement clear window if reach yMax
    }
}

map<pos, bool> obstacle;

WINDOW* initWin(int height, int width, int startY, int startX) {
    WINDOW * win = newwin(height, width, startY ,startX);
    refresh();
    box(win, 0, 0);
    wrefresh(win);
    return win;
}

void drawObstacle(WINDOW * win, pos posArr[], int size, char shape) {
    for (int i=0; i<size; i++) {
        mvwaddch(win, posArr[i].yLoc, posArr[i].xLoc, shape);
        wrefresh(win);
        obstacle[posArr[i]] = true;
    }
}

int main(int argc, char ** argv) {
    setlocale(LC_ALL, "");
    init();
    
    WINDOW * win_main = initWin(height, width, 0 ,0);
    WINDOW * win_text = initWin(h_tBox, width, height-1 ,0);
    
    
    mvwprintw(win_main, 4, 15, "👾");
    mvwprintw(win_main, 13, 41, "💡");
    obstacle[pos(4,15)]=true;
    obstacle[pos(13,41)]=true;
    
    pos w1[15] = {pos(3,13), pos(3,15), pos(3,17), pos(3,19), pos(3,21), pos(3,23), pos(4,23), pos(5,23), pos(6,23), pos(6,19), pos(5,19), pos(5,17), pos(5,15), pos(5,13), pos(4,13)};
    drawObstacle(win_main, w1, 15, '#');
                    
    pos w2[8] = {pos(10,39), pos(11,39), pos(12,39), pos(13,39), pos(10,43), pos(11,43), pos(12,43), pos(13,43)};
    drawObstacle(win_main, w2, 8, '#');
                    
    sprite * player = new sprite(win_main, yPos, xPos, "😋", "", obstacle);
    char command;
    int game;
    
    do {
        command = player -> display();
        yPos = player->yLoc;
        xPos = player->xLoc;
        mvwprintw(win_main, 0, width/2 - 1, "%d %d", yPos, xPos);
        wrefresh(win_main);
        if (command == 'p') {
            if (yPos == 4 && xPos == 17) {
                delayedText(win_text, 1, 10, "Loading Monster");
                game = 1;
                break;
                
            }
            else if (yPos == 12 && xPos == 41) {
                delayedText(win_text, 1, 10, "Loading Trivia");
                game = 2;
                break;
            }
            
            player->command = ' ';

        }
        
    } while (player->getmv() != 'q');
    
    getch();
    endwin();
    
    switch (game) {
        case 1 :
            system("g++ -o monsterGame Aat_Room_Minigame_1.cpp");
            system("./monsterGame");
            break;
            
        case 2 :
            system("g++ -std=c++11 triviaReader.cpp -o triviaReader");
            system("./triviaReader trivia2.txt LEY. room2.cpp");
            break;
    }
    
    return 0;
}
