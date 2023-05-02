#include <iostream>
#include <cstdlib>
#include <ncurses.h>
#include <locale.h>
#include <string>
#include <vector>
#include <algorithm>
#include "sprite.h"

using namespace std;

const int width = 50;
const int height = 15;
const int h_iBox = 6;
const int w_iBox = 12;
const int h_pantry = 3;
const int w_kitchen = width-w_iBox+1;

int yPos = height/2, xPos = width/2;

void init() {
    initscr();
    cbreak();
    noecho();
}

string icon[5] = {"🍞", "🧀", "🥓", "🥑", "🍆"};
struct item {
    string icon;
    int yPos;
    int xPos;
};

item newItem(string icon, int y, int x) {
    item i;
    i.icon = icon;
    i.yPos = y;
    i.xPos = x;
    return i;
}

item ingredients[5] = {newItem("🍞",1,15), newItem("🧀",1,20), newItem("🥓",1,25), newItem("🥑",1,30), newItem("🍆",1,35)};

void fillPantry(WINDOW *win, item i[]) {
    for (int x=0; x<5; x++) {
        mvwprintw(win, i[x].yPos, i[x].xPos, i[x].icon.c_str());
        wrefresh(win);
    }
}

string orderItem = "🍔";
string orderIngredient[3] = {"🍞", "🧀", "🥓"};
vector<string> dropIngredient;
string dishServed;

bool same_item(string order[3], vector<string> v) {
    vector<string> sorted_v(v);
    sort(sorted_v.begin(), sorted_v.end());
    sort(order, order + 3);
    
    return sorted_v == vector<string>(order, order+3);
}

int main(int argc, char ** argv) {
    setlocale(LC_ALL, "");
    init();
    
    //main window
    WINDOW * win_main = newwin(height, width, h_iBox-1, 0);
    refresh();
    wborder(win_main, 0, 0, 0, 0, 0, 0, 0, 0);
    wrefresh(win_main);
    
    //order window
    WINDOW * win_order = newwin(h_iBox, w_iBox, 0, 0);
    refresh();
    wborder(win_order, 0, 0, 0, 0, 0, 0, 0, 0);
    mvwprintw(win_order, 1, 1, " ORDER %s ", orderItem.c_str());
    for (int i=1; i<=3; i++) {
        mvwprintw(win_order, 3, (3*i)-1, "%s", orderIngredient[i-1].c_str());
    }
    wrefresh(win_order);
    
    //pantry window
    WINDOW * win_pantry = newwin(h_pantry, width, h_iBox+height-2, 0);
    refresh();
    wborder(win_pantry, 0, 0, 0, 0, 0, 0, 0, 0);
    mvwprintw(win_pantry, 1, 5, "PANTRY");
    fillPantry(win_pantry, ingredients);
    
    //kitchen window
    WINDOW * win_kitchen = newwin(h_iBox, w_kitchen, 0, w_iBox-1);
    refresh();
    wborder(win_kitchen, 0, 0, 0, 0, 0, 0, 0, 0);
    mvwprintw(win_kitchen, h_iBox/2, w_kitchen/2, "🔪");
    wrefresh(win_kitchen);
    
    sprite * player = new sprite(win_main, yPos, xPos, "😋", "");
    player->item = " ";
    
    do {
        char command = player -> display();
        wrefresh(win_main);
        //yPos = player->yLoc;
        //xPos = player->xLoc;
        //mvwprintw(win_main, 0, 0, "%d %d", yPos, xPos); //show player pos
        switch(command)
        {
            case 'k':
                dropIngredient.push_back(player->item);
                mvwprintw(win_order, 4, (3*dropIngredient.size())-1, "%s", dropIngredient[dropIngredient.size()-1].c_str());
                wrefresh(win_order);
                if ( dropIngredient.size() == 3 ) {
                    bool same = same_item(orderIngredient, dropIngredient);
                    if (same) {
                        mvwprintw(win_kitchen, h_iBox/2, w_kitchen/2, orderItem.c_str());
                        wrefresh(win_kitchen);
                    }
                    napms(1000);
                    dropIngredient.clear();
                    mvwprintw(win_order, 4, 1, "        ");
                    wrefresh(win_order);
                }
                
                player->item = " ";
                player->command = ' ';
                break;
            case 'b':
                player->item = " ";
                player->command = ' ';
                break;
            case 's':
                dishServed = player->item;
                player->item = " ";
                player->command = ' ';
                break;
        }
        
        mvwprintw(win_main, 0, 0, player->item.c_str());
        wrefresh(win_main);
        napms(40);
        
    } while(player->getmv() != 'q');
    
    getch();
    endwin();
    return 0;
}
