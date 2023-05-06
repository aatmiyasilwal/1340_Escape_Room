#include <cstdlib>
#include <string>
#include <ctime>
#include <map>
#include<unistd.h>
#include "Card.cpp"
#include "Deck.cpp"
#include <fstream>
#include <chrono>
#include <thread>
using namespace std;

bool checkWin(vector<vector<Card> > f) {
    int i =0;
    while(i<f.size())
    {
        if (f[i].size() != 13) {
                return false;
            }
        i++;
    }

    return true;
}

//displaying main screen
int main() {
    system("clear");
    cout <<  "*******************************************************" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*             _____                                   *" << endl;
    cout <<  "*            |A .  | _____                            *" << endl;
    cout <<  "*            | /.\\ ||A ^  | _____                     *" << endl;
    cout <<  "*            |(_._)|| / \\ ||A _  | _____              *" << endl;
    cout <<  "*            |  |  || \\ / || ( ) ||A_ _ |             *" << endl;
    cout <<  "*            |____V||  .  ||(_'_)||( v )|             *" << endl;
    cout <<  "*                   |____V||  |  || \\ / |             *" << endl;
    cout <<  "*                          |____V||  .  |             *" << endl;
    cout <<  "*                                 |____V|             *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*         ╭━━━┳━━━┳╮╱╱╭━━┳━━━━┳━━━┳━━┳━━━┳━━━╮        *" << endl;
    cout <<  "*         ┃╭━╮┃╭━╮┃┃╱╱╰┫┣┫╭╮╭╮┃╭━╮┣┫┣┫╭━╮┃╭━━╯        *" << endl;
    cout <<  "*         ┃╰━━┫┃╱┃┃┃╱╱╱┃┃╰╯┃┃╰┫┃╱┃┃┃┃┃╰━╯┃╰━━╮        *" << endl;
    cout <<  "*         ╰━━╮┃┃╱┃┃┃╱╭╮┃┃╱╱┃┃╱┃╰━╯┃┃┃┃╭╮╭┫╭━━╯        *" << endl;
    cout <<  "*         ┃╰━╯┃╰━╯┃╰━╯┣┫┣╮╱┃┃╱┃╭━╮┣┫┣┫┃┃╰┫╰━━╮        *" << endl;
    cout <<  "*         ╰━━━┻━━━┻━━━┻━━╯╱╰╯╱╰╯╱╰┻━━┻╯╰━┻━━━╯        *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*             THANKS FOR PLAYING THE GAME!            *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*******************************************************" << endl;
    sleep(3);
    cout <<  "*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*" << endl;
    cout <<  "*                = WINNING THE GAME =                 *" << endl;
    cout <<  "*  The goal of the game is to fill the four win piles *" << endl;
    cout <<  "*  with cards from Ace to King with the piles' suits. *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*            = MOVING CARDS TO MAIN PILES =           *" << endl;
    cout <<  "*  Cards can be moved from the 7 main piles and the   *" << endl;
    cout <<  "*  hand to any other main pile, or to one of the win  *" << endl;
    cout <<  "*  piles. Only the next smallest card of the opposite *" << endl;
    cout <<  "*  color can be placed on one of the main 7 piles.    *" << endl;
    cout <<  "*  So, a black 5 can be placed on a red 6. Kings may  *" << endl;
    cout <<  "*  be moved to empty piles, and stacks of cards can   *" << endl;
    cout <<  "*  be moved by using the deepest card of that pile.   *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*            = MOVING CARDS TO WIN PILES =            *" << endl;
    cout <<  "*  Each win pile has a designated suit. The win piles *" << endl;
    cout <<  "*  start empty, and cards are placed on each pile of  *" << endl;
    cout <<  "*  their corresponding suit from Ace to King. Cards   *" << endl;
    cout <<  "*  from both the hand and the topmost position of a   *" << endl;
    cout <<  "*  main pile can be moved to a win pile.              *" << endl;
    cout <<  "*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*" << endl;
    cout << endl << endl;
    cout << "Instructions" << endl;
    cout << "------------" << endl;
    cout << "[ D ] = face down card" << endl;
    cout << "[h 8] = [suite number]" << endl;
    cout << "The above card is the 8 of Hearts" << endl << endl;
    cout << "Select a row to move and possible movements will be suggested, " << endl;
    cout << "Choose from the suggested moves. " << endl << endl;
    cout<<"GAME IS LOADING............";
    


    sleep(7);

    srand ( time(NULL) );
    char choice;
    
    map<char, int> foundeck;
    foundeck['1'] = 0;
    foundeck['2'] = 1;
    foundeck['3'] = 2;
    foundeck['4'] = 3;
    foundeck['5'] = 4;
    foundeck['6'] = 5;
    foundeck['7'] = 6;
    foundeck['z'] = 10;
    foundeck['x'] = 11;
    foundeck['c'] = 12;
    foundeck['v'] = 13;
    foundeck['a'] = 20;
    foundeck['s'] = 21;
    
    // sets up a deck of 52 cards
    Deck md = Deck();
    vector<char> sui;
    sui.push_back('c');
    sui.push_back('s');
    sui.push_back('h');
    sui.push_back('d');
    for (int i = 0; i < sui.size(); i++) {
        for (int j = 1; j < 14; j++) {
            Card c = Card(sui.at(i), j);
            c.hidec();
            md.add_back(c);
        }
    }
    // takes random cards from the generated deck to populate the table
    vector<vector<Card> > table;
    for (int i = 0; i < 7; i++) {
        vector<Card> row;
        table.push_back(row);
    }
    for (int i = 0; i < 7; i++) {
        for (int j = i; j < 7; j++) {
                // takes a random card, adds it to table, remove from deck
                int temp = (rand() % md.v.size());
                if (j != i) {
                    md.v[temp].hidec();
                } else {
                    md.v[temp].showc();
                }
                table[j].push_back(md.v[temp]);
                md.v.erase(md.v.begin() + temp);
        }
    }
    
    // generates foundations 4 decks
    vector<vector<Card> > foundation;
    int i = 0;
    while(i<4)
    {
        vector<Card> temp;
        foundation.push_back(temp);
        i++;
    }
    
    // DISPLAY AND GAME MECHANICS
    int step = 1;
    
    while (checkWin(foundation) != true) {
        int tmax = 0;
        for (int i = 0; i < table.size(); i++) {
            if (table[i].size() > tmax) {
                tmax = table[i].size();
            }
        }
        
        cout << endl;
        cout << "---------------" << endl;
        cout << " MOVE " << step << endl;
        cout << "---------------" << endl;
        cout << "Cards remaining in deck: " << md.gsize() << endl;
        cout << endl;

        // display foundations
        cout << " (z)   (x)   (c)   (v)           (A) to select, (S) to draw" << endl;
        for (int i = 0; i < 4; i++) {
            if (foundation[i].size() == 0) {
                cout << "[   ] ";
            } else {
                foundation[i][foundation[i].size() - 1].forcedisplayc();
            }
        }
        
        cout << "         [ Deck ] ";
        md.showthree();
        
        cout << endl << endl;
        cout << " (1)   (2)   (3)   (4)   (5)   (6)   (7)  "<< endl;
        for (int i = 0; i < tmax; i++) {
            for (int j = 0; j < table.size(); j++) {
                if (i < table[j].size()) {
                    table[j][i].displayc();
                }
                else {
                    cout << "      ";
                }
            }
            cout << endl;
        }
        cout << "Enter 'e' to exit" << endl;
        
        
        cout << "Select a row to move: ";
        cin >> choice;
        if (choice == 'e') {
            return 0;
        }
        
        int temp = foundeck[choice];
        int upper = 0;
        vector<int> potential;
        
        Card chosen = Card('j', 100);
        if (temp < 7) {
            for (int i = 0; i < table[temp].size(); i++) {
                if (table[temp][i].hidden == false) {
                    upper = i;
                    break;
                }
            }
            chosen = table[temp][upper];
            for (int j = 0; j < 7; j++) {
                if (j != temp) {
                    if (chosen.gNum() == 13 && table[j].size() == 0) {
                        potential.push_back(j);
                    }
                    if ((table[j][table[j].size() - 1].gNum() == (chosen.gNum() + 1)) && (chosen.gColor() != table[j][table[j].size() - 1].gColor())) {
                        potential.push_back(j);
                    }
                }
            }
            // compares end card against foundation decks
            for (int j = 0; j < 4; j++) {
                if (foundation[j].size() > 0) {
                    if ((foundation[j][foundation[j].size() - 1].gSuite() == table[temp][table[temp].size() - 1].gSuite()) && (foundation[j][foundation[j].size() - 1].gNum() == (table[temp][table[temp].size() - 1].gNum() - 1))) {
                        potential.push_back(j + 10);
                    }
                } else if (table[temp][table[temp].size() - 1].gNum() == 1) {
                    potential.push_back(j + 10);
                }
            }
        } else if (temp < 14 && (foundation[temp - 10].size() > 0)) {
            chosen = foundation[temp - 10][foundation[temp - 10].size() - 1];
            // compares selected against other rows on table, appending options to vector
            for (int j = 0; j < 7; j++) {
                if ((table[j][table[j].size() - 1].gNum() == (chosen.gNum() + 1)) && (chosen.gColor() != table[j][table[j].size() - 1].gColor())) {
                    potential.push_back(j);
                }
            }
        } else if (temp == 20) {
            if (md.showing == 0) {
                md.draw();
            } else {
                chosen = md.v[md.ind + md.showing - 1];
                // compares with table
                for (int j = 0; j < 7; j++) {
                    if (chosen.gNum() == 13 && table[j].size() == 0) {
                        potential.push_back(j);
                    }
                    if ((table[j][table[j].size() - 1].gNum() == (chosen.gNum() + 1)) && (chosen.gColor() != table[j][table[j].size() - 1].gColor())) {
                        potential.push_back(j);
                    }
                }
                // compares against foundation decks
                for (int j = 0; j < 4; j++) {
                    if (foundation[j].size() > 0) {
                        if ((foundation[j][foundation[j].size() - 1].gSuite() == chosen.gSuite()) && ((foundation[j][foundation[j].size() - 1].gNum() + 1) == (chosen.gNum()))) {
                            potential.push_back(j + 10);
                        }
                    } else if (chosen.gNum() == 1) {
                        potential.push_back(j + 10);
                    }
                }
            }
        } else if (temp == 21) {
            md.draw();
        } else {
            cout << "Invalid entry!" << endl;
        }
            
        // translates the indexes into key presses control
        vector<char> todo;
        for (int i = 0; i < potential.size(); i++) {
            map<char, int>::iterator it;
            for (it = foundeck.begin(); it != foundeck.end(); it++) {
                if (it->second == potential[i]) {
                    todo.push_back(it->first);
                }
            }
        }
        
        // returns possible moves
        cout << "Possible moves: ";
        if (todo.size() == 0) {
            cout << "none" << endl;
        } else {
            for (int i = 0; i < todo.size(); i++) {
                cout << "(" << todo[i] << ")  ";
            }
            char entry;
            cout << endl;
            cout << "Make your choice: ";
            cin >> entry;
            bool validchoice = false;
            for (int i = 0; i < todo.size(); i++) {
                if (todo[i] == entry) {
                    validchoice = true;
                    break;
                }
            }
            if (validchoice != true) {
                
                cout << "> Invalid choice! <" << endl;
                continue;
            }
            int move = foundeck[entry];
            if (move < 7 && temp < 7) {
                if ((table[temp].size() - 1) != upper){
                    for (int i = upper; i < table[temp].size(); i++) {
                        table[move].push_back(table[temp][i]);
                    }
                    for (int i = (table[temp].size() - 1); i >= upper; i--) {
                        table[temp].pop_back();
                    }
                } else {
                    table[move].push_back(chosen);
                    table[temp].pop_back();
                }
                for (int i = 0; i < 7; i++) {
                    table[i][table[i].size() - 1].showc();
                }
            } else if (move < 7 && temp == 20) {
                md.v.erase(md.v.begin() + (md.ind + md.showing - 1));
                table[move].push_back(chosen);
                md.showing--;
                for (int i = 0; i < 7; i++) {
                    table[i][table[i].size() - 1].showc();
                }
            } else if (move < 14 && temp == 20) {
                md.v.erase(md.v.begin() + (md.ind + md.showing - 1));
                foundation[move - 10].push_back(chosen);
                md.showing--;
            } else if (move < 14 && temp < 7) {
                foundation[move - 10].push_back(table[temp][table[temp].size() - 1]);
                table[temp].pop_back();
                for (int i = 0; i < 7; i++) {
                    table[i][table[i].size() - 1].showc();
                }
            } else if (move < 7 && temp < 14) {
                table[move].push_back(foundation[temp - 10][foundation[temp - 10].size() - 1]);
                foundation[temp - 10].pop_back();
            } else {
                cout << "Error processing move" << endl;
            }
        }
        step++;
    }

    cout << "---------------" << endl;
    cout << "YOU WIN! You have unlocked the Letters M,A" << endl;
    this_thread::sleep_for(chrono::seconds(3));
    ofstream fout;
    fout.open("r1check.txt", ios::app);
    fout << "Solitaire SPE" << endl;
    fout.close();
    cout << "---------------" << endl;
    system("g++ -pedantic-errors -std=c++11 room1.cpp -lncursesw -o room1");
    system("./room1");
    return 0;
    
}
