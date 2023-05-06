#include <iostream>
#include <ncurses.h>
#include <locale.h>
#include <string>
#include <map>
#include <vector>
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
    
    vector<string> cluesr1;
    bool solBool = false, betBool = false, triviaBool = false;
    ifstream fin;
    fin.open("r1check.txt");
    int total_complete_count = 0;
    string word_in_check, other_word;
    
    while (fin >> word_in_check){
        if (word_in_check == "Solitaire"){
            fin >> other_word;
            cluesr1.push_back(other_word);
            solBool = true;
        }
        
        else if (word_in_check == "Betting"){
            fin >> other_word;
            cluesr1.push_back(other_word);
            total_complete_count++;
            betBool = true;
        }

        else if (word_in_check == "Trivia"){
            fin >> other_word;
            cluesr1.push_back(other_word);
            triviaBool = true;
        }
    }
    fin.close();
    
    if(solBool && betBool && triviaBool){
        system("g++ -pedantic-errors -std=c++11 door.cpp -o door");
        system("./door SHAZAM");
        
    }

    setlocale(LC_ALL, "");
    init();
    
    WINDOW * win_main = initWin(height, width, 0 ,0);
    WINDOW * win_text = initWin(h_tBox, width, height-1 ,0);
    mvwprintw(win_text, 1, 1, "You have to finish all mini-games to get the ");
    mvwprintw(win_text, 2, 1, "clues and get out of the room.");
    wrefresh(win_text);
    
    mvwprintw(win_main, 12, 9, "🃏");
    mvwprintw(win_main, 2, 23, "💰");
    mvwprintw(win_main, 10, 43, "💡");
    obstacle[pos(12,9)]=true; obstacle[pos(2,23)]=true; obstacle[pos(10,43)]=true;
    
    
    pos w1[11] = {pos(10,7), pos(11,7), pos(12,7), pos(13,7), pos(13,8), pos(13,9), pos(13,10), pos(13,11), pos(12,11), pos(11,11), pos(10,11)};
    drawObstacle(win_main, w1, 11, '#');
    
    pos w2[8] = {pos(1,21), pos(2,21), pos(3,21), pos(4,21), pos(1,25), pos(2,25), pos(3,25), pos(4,25)};
    drawObstacle(win_main, w2, 8, '#');
                    
    pos w3[11] = {pos(8,39), pos(8,41), pos(8,43), pos(8,45), pos(9,45), pos(10,45), pos(11,45), pos(12,45), pos(12,43), pos(12,41), pos(12,39)};
    drawObstacle(win_main, w3, 11, '#');
                    
    sprite * player = new sprite(win_main, yPos, xPos, "😋", "", obstacle);
    char command;
    int game;
    
    do {
        command = player -> display();
        yPos = player->yLoc;
        xPos = player->xLoc;
//        mvwprintw(win_main, 0, width/2 - 1, "%d %d", yPos, xPos); //current pos
        wrefresh(win_main);
        if (command == 'p') {
            if (yPos == 11 && xPos == 9) {
                wclear(win_text);
                box(win_text, 0, 0);
                delayedText(win_text, 2, 17, "Loading Solitaire");
                game = 1;
                break;
            }
            else if (yPos == 3 && xPos == 23) {
                wclear(win_text);
                box(win_text, 0, 0);
                delayedText(win_text, 2, 17, "Loading Betting Game");
                game = 2;
                break;
            }
            else if ((yPos == 10 || yPos==9 || yPos==11) && xPos == 41) {
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
            system("g++ -pedantic-errors -std=c++11 main.cpp -o soltaire");
            system("./soltaire");
            break;
            
        case 2 :
            system("g++ -pedantic-errors -std=c++11 bettingGame.cpp -o bettingGame");
            system("./bettingGame");
            break;
            
        case 3 :
            system("g++ -pedantic-errors -std=c++11 triviaReader.cpp -o triviaReader");
            system("./triviaReader trivia1.txt ZA. room1.cpp");
            break;
    }
    
    return 0;
}
