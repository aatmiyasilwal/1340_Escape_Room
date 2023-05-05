#include <iostream>
#include <ncurses.h>
#include <locale.h>
#include <string>
#include <map>
#include "sprite.h"

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
    
    mvwprintw(win_main, 3, 3, "🔪");
    mvwprintw(win_main, 13, 41, "💡");
    obstacle[pos(3,3)]=true;
    obstacle[pos(13,41)]=true;
    
    pos w1[12] = {pos(2,1), pos(2,3), pos(2,5), pos(2,7), pos(2,9), pos(2,11), pos(4,1), pos(4,3), pos(4,5), pos(4,7), pos(4,9), pos(4,11)};
    drawObstacle(win_main, w1, 12, '#');
                    
    pos w2[8] = {pos(13,39), pos(12,39), pos(12,41), pos(12,43), pos(11,43), pos(10,43), pos(9,43), pos(8,43)};
    drawObstacle(win_main, w2, 8, '#');
                    
    sprite * player = new sprite(win_main, yPos, xPos, "😋", "", obstacle);
    char command;
    
    do {
        command = player -> display();
        yPos = player->yLoc;
        xPos = player->xLoc;
        mvwprintw(win_main, 0, width/2 - 1, "%d %d", yPos, xPos);
        wrefresh(win_main);
        if (command == 'p') {
            if (yPos == 3 && xPos == 5) {
                delayedText(win_text, 1, 10, "Loading UnderCook");
            }
            else if (yPos == 13 && xPos == 43) {
                delayedText(win_text, 1, 10, "Loading Trivia");
            }
            
            player->command = ' ';
//            napms(500);
//            wclear(win_text);
//            box(win_text, 0, 0);
        }
        
    } while (player->getmv() != 'q');
    
    getch();
    endwin();
    return 0;
}
