#include <iostream>
#include <ncurses.h>
#include <locale.h>
#include <string>
#include <map>
#include "sprite.h"

using namespace std;

const int width = 80;
const int height = 20;
const int h_tBox = 5;
const int h_door = 6;
const int w_door = 4;
const int h_r1 = 5, w_r1 = 27;
const int h_r2 = 6, w_r2 = width-w_r1-7;
const int h_r3 = 10, w_r3 = 31;
const int h_r4 = 7, w_r4 = width-w_r3-10;

int yPos = height/3, xPos = 1;

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

int main(int argc, char ** argv) {
    setlocale(LC_ALL, "");
    init();
    
    WINDOW * win_main = newwin(height, width, 0 ,0);
    refresh();
    box(win_main, 0, 0);
    wrefresh(win_main);
    
    WINDOW * win_text = newwin(h_tBox, width, height-1 ,0);
    refresh();
    box(win_text, 0, 0);
    wrefresh(win_text);
    
    WINDOW * door = newwin(h_door, w_door, height/2 - h_door/2, width-1);
    refresh();
    box(door, 0, 0);
    wrefresh(door);
    
    WINDOW * r1 = newwin(h_r1, w_r1, 0, 0);
    refresh();
    box(r1, 0, 0);
    mvwprintw(r1, 4, 19, "🚪");
    wrefresh(r1);
    
    WINDOW * r2 = newwin(h_r2, w_r2, 0, w_r1+7);
    refresh();
    box(r2, 0, 0);
    mvwprintw(r2, 3, 0, "🚪");
    wrefresh(r2);
    
    WINDOW * r3 = newwin(h_r3, w_r3, height-h_r3, 0);
    refresh();
    box(r3, 0, 0);
    mvwprintw(r3, 0, 15, "🚪");
    wrefresh(r3);
    
    WINDOW * r4 = newwin(h_r4, w_r4, height-h_r4, w_r3+10);
    refresh();
    box(r4, 0, 0);
    mvwprintw(r4, 0, 9, "🚪");
    wrefresh(r4);
    
    for (int i=1; i<h_door-1; i++) {
        mvwprintw(door, i, 1, "🔒");
    }
    wrefresh(door);
    
    //assing all pos to non-obstacle
    for (int x=2; x<width-1; x++) {
        for (int y=2; y<height-1; y++) {
            pos temp = pos(y,x);
            obstacle[temp] = false;
        }
    }

    //assign obstacles
    //r1
    for (int i=1; i<27; i++) {
        pos temp = pos(4, i);
        obstacle[temp] = true;
    }
    for (int i=1; i<5; i++) {
        pos temp = pos(i, 25);
        obstacle[temp] = true;
    }
    //r3
    for (int i=1; i<30; i++) {
        pos temp = pos(10, i);
        obstacle[temp] = true;
    }
    for (int i=10; i<height; i++) {
        pos temp = pos(i, 29);
        obstacle[temp] = true;
    }
    //r2
    for (int i=33; i<width; i++) {
        pos temp = pos(5, i);
        obstacle[temp] = true;
    }
    for (int i=1; i<6; i++) {
        pos temp = pos(i, 33);
        obstacle[temp] = true;
    }
    //r4
    for (int i=41; i<width; i++) {
        pos temp = pos(13, i);
        obstacle[temp] = true;
    }
    for (int i=13; i<height; i++) {
        pos temp = pos(i, 41);
        obstacle[temp] = true;
    }
    
    
    string text = "I'm not afraid to take a stand.";
    delayedText(win_text, 1, 5, text);
    
    sprite * player = new sprite(win_main, yPos, xPos, "😋", "", obstacle);
    char command;
    
    do {
        command = player -> display();
        yPos = player->yLoc;
        xPos = player->xLoc;
        mvwprintw(win_main, 0, w_r1 + 1, "%d %d", yPos, xPos);
        wrefresh(win_main);

        //reprint
        box(r1, 0, 0);
        mvwprintw(r1, 4, 19, "🚪");
        wrefresh(r1);
    
        box(r2, 0, 0);
        mvwprintw(r2, 3, 0, "🚪");
        wrefresh(r2);
        
        box(r3, 0, 0);
        mvwprintw(r3, 0, 15, "🚪");
        wrefresh(r3);
        
        box(r4, 0, 0);
        mvwprintw(r4, 0, 9, "🚪");
        wrefresh(r4);
        
        //open door
        if (command == 'p') {
            //door 1
            if (yPos == 5 && (xPos>=17 && xPos<=21)) {
                wclear(win_text);
                box(win_text, 0, 0);
                delayedText(win_text, 1, 5, "Go into Room 1? (y/n) ");
                char ans = getch();
                if (ans == 'y') {
                    wclear(win_text);
                    box(win_text, 0, 0);
                    delayedText(win_text, 1, 5, "Going to room 1");
                }
            }
            
            player->command = ' ';
        }
        wclear(win_text);
        box(win_text, 0, 0);
        
    } while (player->getmv() != 'q');
    
    getch();
    endwin();
    return 0;
}
