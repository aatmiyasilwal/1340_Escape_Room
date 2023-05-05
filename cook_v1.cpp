//This is a mini game based on Overcook
//Developed by Sai Zom

#include <iostream>
#include <cstdlib>
#include <ncurses.h>
#include <locale.h>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <ctime>
#include <sys/time.h>
#include "sprite.h"

using namespace std;

//size of windows
const int width = 50;
const int height = 15;
const int h_iBox = 6;
const int w_iBox = 12;
const int h_pantry = 3;
const int w_kitchen = width-w_iBox+1;

//initital position of player
int yPos = height/2, xPos = width/2;

void init(); //initialization required for ncurses library

//struct for items in pantry
struct item {
    string icon;
    int yPos;
    int xPos;
};
item newItem(string icon, int y, int x);

//Display items in pantry window
item ingredients[7] = {newItem("🍞",1,15), newItem("🧀",1,19), newItem("🍖",1,23), newItem("🥑",1,27), newItem("🍚",1,31), newItem("🥒",1,35), newItem("🍅",1,39)};
void fillPantry(WINDOW *win, item i[]);

//Display initial items in order window
vector<string> dropIngredient;
string dishServed;


//menu items
string menu[5] = {"🍱", "🥗", "🍔", "🍛", "🍕"};
map <string, vector<string> > recipe;
//void add(vector<string> v, string ingredients[], int size) {
//    for(int i=0; i<size; i++) {
//        v.push_back(ingredients[i]);
//    }
//}


bool same_item(vector<string> v1, vector<string> v2); //compare two vectors

//Initial duration
int duration = 90, countdown = 90;
//clock_t start_time = clock();
//void timeRemain(clock_t start_time, int& countdown) {
//    clock_t current_time = clock();
//    int timeElasped = (current_time - start_time) / CLOCKS_PER_SEC;
//    countdown -= timeElasped;
//}

//map for obstacle/wall sensing - required for sprite.h
map<pos, bool> obstacle;

int orderCount = 0; // global variable for number of order completed

int main(int argc, char ** argv) {
    //initialize
    setlocale(LC_ALL, "");
    init();
    
    //start tracking time
    struct timeval start_time, current_time;
    gettimeofday(&start_time, NULL);
    
    //initialize menu - map item to ingredients
//    recipe["🍔"] = {"🍞", "🧀", "🍖"};
//    recipe["🍱"] = {"🍚", "🥒", "🍖"};
//    recipe["🥗"] = {"🥒", "🍅", "🥑"};
//    recipe["🍛"] = {"🍚", "🍅", "🍖"};
//    recipe["🍕"] = {"🍞", "🧀", "🍅"};
    recipe["🍔"].push_back("🍞"); recipe["🍔"].push_back("🧀"); recipe["🍔"].push_back("🍖");
    recipe["🍱"].push_back("🍚"); recipe["🍱"].push_back("🥒"); recipe["🍱"].push_back("🍖");
    recipe["🥗"].push_back("🥒"); recipe["🥗"].push_back("🍅"); recipe["🥗"].push_back("🥑");
    recipe["🍛"].push_back("🍚"); recipe["🍛"].push_back("🍅"); recipe["🍛"].push_back("🍖");
    recipe["🍕"].push_back("🍞"); recipe["🍕"].push_back("🧀"); recipe["🍕"].push_back("🍅");
    
    //generate random item
    srand (time(NULL));
    int index = rand()%5;
    string orderItem = menu[index];
    vector<string> orderIngredient = recipe[orderItem];
    
    //main window
    WINDOW * win_main = newwin(height, width, h_iBox-1, 4);
    refresh();
    wborder(win_main, 0, 0, 0, 0, 0, 0, 0, 0);
    wrefresh(win_main);
    
    //order window
    WINDOW * win_order = newwin(h_iBox, w_iBox, 0, 4);
    refresh();
    wborder(win_order, 0, 0, 0, 0, 0, 0, 0, 0);
    mvwprintw(win_order, 1, 1, " ORDER %s ", orderItem.c_str()); //display the first order item and ingredients to pick
    for (int i=1; i<=3; i++) {
        mvwprintw(win_order, 3, (3*i)-1, "%s", orderIngredient[i-1].c_str());
    }
    wrefresh(win_order);
    
    //pantry window
    WINDOW * win_pantry = newwin(h_pantry, width, h_iBox+height-2, 4);
    refresh();
    wborder(win_pantry, 0, 0, 0, 0, 0, 0, 0, 0);
    mvwprintw(win_pantry, 1, 5, "PANTRY");
    fillPantry(win_pantry, ingredients);
    
    //kitchen window
    WINDOW * win_kitchen = newwin(h_iBox, w_kitchen, 0, 5+w_iBox-2);
    refresh();
    wborder(win_kitchen, 0, 0, 0, 0, 0, 0, 0, 0);
    mvwprintw(win_kitchen, 1, w_kitchen/2 -4, "KITCHEN 🔪");
    wrefresh(win_kitchen);
    
    //bin window
    WINDOW * win_bin = newwin(3, 5, h_iBox+height-5, 0);
    refresh();
    box(win_bin, 0, 0);
    mvwprintw(win_bin, 1, 1, "BIN");
    wrefresh(win_bin);
    
    //timer window
    WINDOW * win_timer = newwin(4, 7, 0, width+4);
    refresh();
    box(win_timer, 0, 0);
    mvwprintw(win_timer, 1, 1, "TIMER");
    
    //cart window
    WINDOW * win_cart = newwin(4, 8, 4, width+4);
    refresh();
    box(win_cart, 0, 0);
    mvwprintw(win_cart, 1, 1, "CART🛒");
    wrefresh(win_cart);
    
    //completed order window
    WINDOW * win_complete = newwin(6, 4, 8, width+4);
    refresh();
    box(win_complete, 0, 0);
    mvwprintw(win_complete, 1, 1, "✔✔");
    wrefresh(win_complete);
    
    //new sprite for player
    sprite * player = new sprite(win_main, yPos, xPos, "😋", "", obstacle);
    player->item = " "; //no item picked initially
    int timeElasped = 0; //for timer
    
    bool win = false;
    int t1; //for kitchen animation
    
    do {
        char command = player -> display(); //move player, get command for pick/drop
        wrefresh(win_main);
//        yPos = player->yLoc;
//        xPos = player->xLoc;
//        mvwprintw(win_main, 0, 22, "%d %d", yPos, xPos); //show player pos
        
        //print timer
        gettimeofday(&current_time, NULL);
        double timeElasped = (current_time.tv_sec - start_time.tv_sec) +
        (current_time.tv_usec - start_time.tv_usec) / 1000000.0;
        countdown = duration - timeElasped;
        
        //Time's Up - Game Over
        if (countdown < 0) {
            mvwprintw(win_main, height/2, width/2 - 5, "GAME OVER");
            wrefresh(win_main);
            napms(1500);
            break;
        }
        mvwprintw(win_timer, 2, 2, "    ", countdown);
        mvwprintw(win_timer, 2, 2, "%ds", countdown);
        wrefresh(win_timer);
        
        switch(command) //to prevent dropping items at unavailable positions
        {
            case 'k': //drop item for kitchen
                dropIngredient.push_back(player->item);
                mvwprintw(win_order, 4, (3*dropIngredient.size())-1, "%s", dropIngredient[dropIngredient.size()-1].c_str()); //show dropped item
                wrefresh(win_order);
                // check 3 items - all correct item -> one dish ; wrong items -> start over
                if ( dropIngredient.size() == 3 ) {
                    bool same = same_item(orderIngredient, dropIngredient);
                    if (same) {
                        mvwprintw(win_kitchen, h_iBox/2, w_kitchen/2, orderItem.c_str());
                        wrefresh(win_kitchen);
                        
                        //starts kitchen timer
                        t1 = countdown;
                        
                        //point+ & complete window update
                        orderCount++;
                        mvwprintw(win_complete, orderCount+1, 1, orderItem.c_str());
                        wrefresh(win_complete);
                        
                        //winning by completing 3 orders
                        if (orderCount == 3) {
                            mvwprintw(win_main, height/2, width/2 - 4, "YOU WIN");
                            wrefresh(win_main);
                            napms(1500);
                            win = true;
                        }
                        
                        //new item in order window
                        srand (time(NULL));
                        int index = rand()%5;
                        orderItem = menu[index];
                        orderIngredient = recipe[orderItem];
                        mvwprintw(win_order, 1, 1, " ORDER %s ", orderItem.c_str());
                        for (int i=1; i<=3; i++) {
                            mvwprintw(win_order, 3, (3*i)-1, "%s", orderIngredient[i-1].c_str());
                        }
                        wrefresh(win_order);
                    }
                    dropIngredient.clear();
                    mvwprintw(win_order, 4, 1, "        ");
                    wrefresh(win_order);
                }
                
                //refresh all items and commands
                player->item = " ";
                player->command = ' ';
                break;
                
            case 'b': //drop item in bin
                player->item = " ";
                player->command = ' ';
                break;
                
//            case 's': //drop item for server
//                dishServed = player->item;
//                player->item = " ";
//                player->command = ' ';
//                break;
        }
        mvwprintw(win_cart, 2, 3, player->item.c_str()); //show picked item in cart - only one item per time
        wrefresh(win_cart);
        
        if (win)
            break;
        
    } while(player -> getmv() != 'q'); //quit on 'q'
    
    napms(2000);
    
    //ending
    wclear(win_main);
    box(win_main, 0, 0);
    mvwprintw(win_main, height/2, width/2 - 12, "PRESS ENTER TO CONTINUE");
    wrefresh(win_main);
    int i;
    do {
    i = getch();
    } while (i != 10);
    
    getch();
    endwin();
    return 0;
}

//initialization required for ncurses library
void init() {
    initscr();
    cbreak();
    timeout(0);
    nodelay(stdscr,TRUE);
    noecho();
}
//make new item struct
item newItem(string icon, int y, int x) {
    item i;
    i.icon = icon;
    i.yPos = y;
    i.xPos = x;
    return i;
}
//fill pantry window
void fillPantry(WINDOW *win, item i[]) {
    for (int x=0; x<7; x++) {
        mvwprintw(win, i[x].yPos, i[x].xPos, i[x].icon.c_str());
        wrefresh(win);
    }
}
//check if two vectors contain same elements regardless of order
bool same_item(vector<string> v1, vector<string> v2) {
    vector<string> sorted_v1(v1);
    vector<string> sorted_v2(v2);
    sort(sorted_v1.begin(), sorted_v1.end());
    sort(sorted_v2.begin(), sorted_v2.end());
    
    return sorted_v1 == sorted_v2;
}
