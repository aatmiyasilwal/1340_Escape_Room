#include <iostream>
#include <ncurses.h>
#include <locale.h>
#include <string>
#include <map>
#include "sprite.h"
#include <fstream>


using namespace std;

const int width = 76;
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

void reprint(WINDOW * r1, WINDOW * r2, WINDOW * r3, WINDOW * r4) {
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
}

void printGo(WINDOW * win, int r) {
    wclear(win);
    box(win, 0, 0);
    delayedText(win, 1, 5, "Going to room");
}

WINDOW* initWin(int height, int width, int startY, int startX) {
    WINDOW * win = newwin(height, width, startY ,startX);
    refresh();
    box(win, 0, 0);
    wrefresh(win);
    return win;
}

int main(int argc, char ** argv) {
    setlocale(LC_ALL, "");
    init();
    
    WINDOW * win_main = initWin(height, width, 0 ,0);
    WINDOW * win_text = initWin(h_tBox, width, height-1 ,0);
    WINDOW * door = initWin(h_door, w_door, height/2 - h_door/2, width-1);

    
    WINDOW * r1 = initWin(h_r1, w_r1, 0, 0);
    mvwprintw(r1, 4, 19, "🚪");
    wrefresh(r1);
    
    WINDOW * r2 = initWin(h_r2, w_r2, 0, w_r1+7);
    mvwprintw(r2, 3, 0, "🚪");
    wrefresh(r2);
    
    WINDOW * r3 = initWin(h_r3, w_r3, height-h_r3, 0);
    mvwprintw(r3, 0, 15, "🚪");
    wrefresh(r3);
    
    WINDOW * r4 = initWin(h_r4, w_r4, height-h_r4, w_r3+10);
    mvwprintw(r4, 0, 9, "🚪");
    wrefresh(r4);
    
    //locks and keys
    string lock[4] = {"🔒","🔒","🔒","🔒"};
    for (int i=1; i<h_door-1; i++) {
        mvwprintw(door, i, 1, lock[i-1].c_str());
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
    //need to make function with 2 corner coordinates - e.g - obs(1, 1, 4, 25)
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
    
    
    string text = "Press ENTER to start the game.";
    delayedText(win_text, 1, 20, text);
    
    int i;
    do {
    i = getch();
    } while (i != 10);
    wclear(win_text);
    box(win_text, 0, 0);
    wrefresh(win_text);
    
    sprite * player = new sprite(win_main, yPos, xPos, "😋", "", obstacle);
    char command;
    int counter=0;
    
    do {
        command = player -> display();
        yPos = player->yLoc;
        xPos = player->xLoc;
        mvwprintw(win_main, 0, w_r1 + 1, "%d %d", yPos, xPos);
        wrefresh(win_main);

        reprint(r1, r2, r3, r4);
        
        //open door
        if (command == 'p') {
            int complete = 0;
            
            //door 1
            if (yPos == 5 && (xPos>=17 && xPos<=21)) {
                wclear(win_text);
                box(win_text, 0, 0);
                delayedText(win_text, 2, 3, "Go into Room 1? (y for 'yes' or keep moving) ");
                char ans = getch();

                //go into room 1
                if (ans == 'y') {
                    printGo(win_text, 3);
                    
                    system("g++ -o loading3 loading3.cpp");
                    system("./loading3");

                    system("g++ room1.cpp -lncurses -o room1");
                    system("./room1");

                    //room 1
                    box(win_main, 0, 0);
                    mvwaddch(win_main, yPos, xPos, ' ');
                    wrefresh(win_main);
                    
                    map<pos, bool> temp_obstacle;
                    sprite * player = new sprite(win_main, yPos, xPos, "😋", "", temp_obstacle);
                    
                    bool r1complete = false;
                    do {
                        command = player -> display();
                    } while (player->getmv() != 'q');
                    box(win_main, 0, 0);
                    mvwaddch(win_main, yPos, xPos, ' ');
                    wrefresh(win_main);
                    
                    reprint(r1, r2, r3, r4);
                    player -> xLoc = 19;
                    player -> yLoc = 5;
                    player -> display();
                    complete = 1;
                }
                else {
                    player -> display();
                    wclear(win_text);
                    box(win_text, 0, 0);
                    wrefresh(win_text);
                }
            }
            
            //door 2
            if (xPos == 31 && (yPos>=2 && yPos<=4)) {
                wclear(win_text);
                box(win_text, 0, 0);
                delayedText(win_text, 1, 15, "Go into Room 2? (y for 'yes' or keep moving) ");
                char ans = getch();

                //go into room 1
                if (ans == 'y') {
                    printGo(win_text, 2);

                    //room 2
//                    system("g++ -o loading3 loading3.cpp");
//                    system("./loading3");

                    system("g++ room2.cpp -lncurses -o room2");
                    system("./room2");
                    
                    complete = 2;
                }
                else {
                    player -> display();
                    wclear(win_text);
                    box(win_text, 0, 0);
                    wrefresh(win_text);
                }
            }
            
            //door 3
            if (yPos == 9 && (xPos>=13 && xPos<=17)) {
                wclear(win_text);
                box(win_text, 0, 0);
                delayedText(win_text, 1, 15, "Go into Room 3? (y for 'yes' or keep moving) ");
                char ans = getch();

                //go into room 1
                if (ans == 'y') {
                    printGo(win_text, 3);

                    //room 3
                    system("g++ -o loading3 loading3.cpp");
                    system("./loading3");

                    system("g++ -o room3 room3.cpp");
                    system("./room3");
                    complete = 3;
                }
                else {
                    player -> display();
                    wclear(win_text);
                    box(win_text, 0, 0);
                    wrefresh(win_text);
                }
            }
            
            //door 4
            if (yPos == 12 && (xPos>=49 && xPos<=53)) {
                wclear(win_text);
                box(win_text, 0, 0);
                delayedText(win_text, 1, 15, "Go into Room 4? (y for 'yes' or keep moving) ");
                char ans = getch();

                //go into room 1
                if (ans == 'y') {
                    printGo(win_text, 4);

                    //room 4
//                    system("g++ -o loading3 loading3.cpp");
//                    system("./loading3");

                    system("g++ room4.cpp -lncurses -o room4");
                    system("./room4");
                    complete = 4;
                }
                else {
                    player -> display();
                    wclear(win_text);
                    box(win_text, 0, 0);
                    wrefresh(win_text);
                }
            }
            
            if (complete>=1 && complete<=4) {
                lock[complete-1] = "🔑";
                for (int i=1; i<h_door-1; i++) {
                    mvwprintw(door, i, 1, lock[i-1].c_str());
                }
                wrefresh(door);
                counter++;
                
                if (counter == 4) {
                    napms(1000);
                    wclear(win_text);
                    box(win_text, 0, 0);
                    delayedText(win_text, 1, 20, "CONGRATULATIONS!! YOU WIN");
                    napms(1000);
                    mvwprintw(win_text, 3, 21, "PRESS ENTER TO CONTINUE");
                    wrefresh(win_text);
                    int i;
                    do {
                    i = getch();
                    } while (i != 10);
                    break;
                }
            
            }
            player->command = ' ';
        }
        
        
    } while (player->getmv() != 'q');
    
    getch();
    endwin();
    return 0;
}
