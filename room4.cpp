#include <iostream>
#include <ncurses.h>
#include <locale.h>
#include <string>
#include <map>
#include "sprite.h"
#include <fstream>
#include <vector>

using namespace std;

const int width = 48;
const int height = 15;
const int h_tBox = 5;

int yPos = height/2, xPos = 1;

//initialize ncurses files
void init() {
    initscr();
    cbreak();
    noecho();
}

//display delayed texts
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

//initialize window by refreshing
WINDOW* initWin(int height, int width, int startY, int startX) {
    WINDOW * win = newwin(height, width, startY ,startX);
    refresh();
    box(win, 0, 0);
    wrefresh(win);
    return win;
}

//drawing obstacles into game space
void drawObstacle(WINDOW * win, pos posArr[], int size, char shape) {
    for (int i=0; i<size; i++) {
        mvwaddch(win, posArr[i].yLoc, posArr[i].xLoc, shape);
        wrefresh(win);
        obstacle[posArr[i]] = true;
    }
}

//added game functionality and redirection
int main(int argc, char ** argv) {
    
    //shut down
    bool room1Complete = false, room2Complete = false, room3Complete = false, room4Complete = false;
    string check;
    ifstream Fin;
    
    Fin.open("totalcheck.txt");
    while(Fin >> check){
        if (check == "Room1"){
            room1Complete = true;
        }
        else if (check == "Room2"){
            room2Complete = true;
        }
        else if (check == "Room3"){
            room3Complete = true;
        }
        else if (check == "Room4"){
            room4Complete = true;
        }
    }
    Fin.close();

    if (room1Complete && room2Complete && room3Complete && room4Complete){
        return 0;
    }
    
    bool cookBool = false, triviaBool = false;
    vector<string> cluesr4;
    ifstream fin;
    fin.open("r4check.txt");
    int total_complete_count = 0;
    string word_in_check, other_word;

    while (fin >> word_in_check){
        if (word_in_check == "Cook"){
            fin >> other_word;
            cluesr4.push_back(other_word);
            cookBool = true;
        }

        else if (word_in_check == "Trivia"){
            fin >> other_word;
            cluesr4.push_back(other_word);
            triviaBool = true;
        }
    }
    fin.close();
    if(cookBool && triviaBool){
        system("g++ -pedantic-errors -std=c++11 door.cpp -o door");
        system("./door WONDER");

    }

    setlocale(LC_ALL, "");
    init();
    
    WINDOW * win_main = initWin(height, width, 0 ,0);
    WINDOW * win_text = initWin(h_tBox, width, height-1 ,0);
    mvwprintw(win_text, 1, 1, "You have to finish all mini-games to get the ");
    mvwprintw(win_text, 2, 1, "clues and get out of the room.");
    wrefresh(win_text);
    
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
    int game;
    
    do {
        command = player -> display();
        yPos = player->yLoc;
        xPos = player->xLoc;
//        mvwprintw(win_main, 0, width/2 - 1, "%d %d", yPos, xPos);
        wrefresh(win_main);
        if (command == 'p') {
            if (yPos == 3 && xPos == 5) {
                wclear(win_text);
                box(win_text, 0, 0);
                delayedText(win_text, 2, 17, "Loading UnderCook");
                game = 1;
                break;
            }
            else if (yPos == 13 && xPos == 43) {
                wclear(win_text);
                box(win_text, 0, 0);
                delayedText(win_text, 2, 17, "Loading Trivia");
                game = 2;
                break;
            }
            
            player->command = ' ';
        }
        
    } while (player->getmv() != 'q');

    endwin();
    
    switch (game) {
        case 1 :
            system("g++ -pedantic-errors -std=c++11 cook_v1.cpp -lncursesw -o cooking");
            system("./cooking");
            break;
            
        case 2 :
            system("g++ -pedantic-errors -std=c++11 triviaReader.cpp -o triviaReader");
            system("./triviaReader trivia4.txt DER. room4.cpp");
            break;
    }
    
    return 0;
}
