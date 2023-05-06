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
    
    bool memoryBool = false, lootBool = false, triviaBool = false;
    vector<string> cluesr3;
    ifstream fin;
    fin.open("r3check.txt");
    int total_complete_count = 0;
    string word_in_check, other_word;

    while (fin >> word_in_check){
        if (word_in_check == "Memory"){
            fin >> other_word;
            cluesr3.push_back(other_word);
            memoryBool = true;
        }
        else if (word_in_check == "Lockpicking"){
            fin >> other_word;
            cluesr3.push_back(other_word);
            lootBool = true;
        }
        else if (word_in_check == "Trivia"){
            fin >> other_word;
            cluesr3.push_back(other_word);
            triviaBool = true;
        }
    }
    fin.close();
    if(memoryBool && lootBool && triviaBool){
        system("g++ -pedantic-errors -std=c++11 door.cpp -o door");
        system("./door BATMAN");

    }

    setlocale(LC_ALL, "");
    init();
    
    WINDOW * win_main = initWin(height, width, 0 ,0);
    WINDOW * win_text = initWin(h_tBox, width, height-1 ,0);
    mvwprintw(win_text, 1, 1, "You have to finish all mini-games to get the ");
    mvwprintw(win_text, 2, 1, "clues and get out of the room.");
    wrefresh(win_text);
    
    mvwprintw(win_main, 13, 1, "🔓");
    mvwprintw(win_main, 7, 23, "🎴");
    mvwprintw(win_main, 1, 45, "💡");
    obstacle[pos(13,1)]=true;
    obstacle[pos(7,23)]=true;
    obstacle[pos(1,45)]=true;
    
    pos w1[8] = {pos(10,1), pos(10,3), pos(10,5), pos(10,7), pos(12,7), pos(12,5), pos(12,3), pos(13,3)};
    drawObstacle(win_main, w1, 8, '#');
                    
    pos w2[7] = {pos(6,25), pos(6,23), pos(6,21), pos(7,21), pos(8,21), pos(8,23), pos(8,25)};
    drawObstacle(win_main, w2, 7, '#');
    
    pos w3[5] = {pos(2,37), pos(2,45), pos(2,43), pos(2,41), pos(2,39)};
    drawObstacle(win_main, w3, 5, '#');
                    
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
            if (yPos == 12 && xPos == 1) {
                wclear(win_text);
                box(win_text, 0, 0);
                delayedText(win_text, 2, 17, "Loading Lockpicking");
                game = 1;
                break;
            }
            else if (yPos == 7 && xPos == 25) {
                wclear(win_text);
                box(win_text, 0, 0);
                delayedText(win_text, 2, 17, "Loading Memory");
                game = 2;
                break;
            }
            else if (yPos == 1 && xPos == 43) {
                wclear(win_text);
                box(win_text, 0, 0);
                delayedText(win_text, 2, 17, "Loading Trivia");
                game = 3;
                break;
            }
            
            player->command = ' ';
        }
        
    } while (player->getmv() != 'q');

    endwin();
    
    switch (game) {
        case 1 :
            system("g++ -pedantic-errors -std=c++11 lockpicking.cpp -o lockpicking");
            system("./lockpicking");
            break;
            
        case 2 :
            system("g++ -pedantic-errors -std==c++11 memory.cpp -o memory");
            system("./memory");
            break;
            
        case 3 :
            system("g++ -pedantic-errors -std=c++11 triviaReader.cpp -o triviaReader");
            system("./triviaReader trivia3.txt TM. room3.cpp");
            break;
    }
    
    return 0;
}
