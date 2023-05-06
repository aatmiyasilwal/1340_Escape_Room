#include <iostream>
#include <ctime>
#include<string>
#include <stdlib.h>
#include <iomanip>
#include<unistd.h>
#include <fstream>

using namespace std;
void check(int sh,int sl,int rh,int rl,int &balance,int &bet){
    if(sh>sl){
        balance+=bet;
        cout<<"You won.Your current balance is "<<balance<<endl; 
    }
    else if(sh<sl){
        balance-=bet;
        cout<<"You lost.Your current balance is "<<balance<<endl;
    }
    else if(sh==sl){
        if(rh>rl){
            balance+=bet;
            cout<<"You won.Your current balance is "<<balance<<endl;
        }
        else if(rh<rl){
            balance-=bet;
            cout<<"You lost.Your current balance is "<<balance<<endl;
        }
        else{
            cout<<"It is a tie. No change in Balance."<<balance<<endl;
        }
    }

}
int card_suit(){
    int suit;
    suit = (1 + (rand() % (int)(4)));
    return suit;
}

int card_rank(){
    int rank;
    rank = (1 + (rand() % (int)(13)));
    return rank;
}

void print_card(int rank,int suit) {
    string suit_symbol;
      switch (suit) {
        case 1:
            suit_symbol = "♦";
            break;
        case 2:
            suit_symbol = "♥";
            break;
        case 3:
            suit_symbol = "♠";
            break;
        case 4:
            suit_symbol = "♣";
            break;
    }
    cout<<"|"<<"-------"<<"|"<<endl;
    cout<<"|"<<setw(8)<<"|"<<endl;
    cout<<"|"<<setw(4)<<rank<<setw(5)<<"|\n";
    cout<<"|"<<setw(6)<<suit_symbol<<setw(5)<<"|\n";
    cout<<"|"<<setw(8)<<"|"<<endl;
    cout<<"|"<<"-------"<<"|"<<endl;
    cout<<endl;
}

int main(){
    int balance=500;
    int bet;
    cout<<"| |  | |(_)       | |                          | |"<<endl;
    cout<<"| |__| | _   __ _ | |__     ___  __ _  _ __  __| |"<<endl;
    cout<<"|  __  || | / _` || '_ \\   / __|/ _` || '__|/ _` |"<<endl;
    cout<<"| |  | || || (_| || | | | | (__| (_| || |  | (_| |"<<endl;
    cout<<"|_|  |_||_| \\__, ||_| |_|  \\___|\\__,_||_|   \\__,_|"<<endl;
    cout<<"             __/ |                                "<<endl;
    cout<<"            |___/                                 "<<endl;
    cout<<"| |                                         | |"<<endl;
    cout<<"| |  ___  __      __      __ __ _ _ __ __ __| |"<<endl;
    cout<<"| | / _  \\ \\ /\\ / /     / __|/ _` || '__|/ _` |"<<endl;
    cout<<"| || (_) |\\ V  V /       (__| (_| || |  | (_| |"<<endl;
    cout<<"|_| \\___/  \\_/\\_/       \\___|\\__,_||_|   \\__,_|"<<endl;
    cout<<"You have $500. You have to bet and test your luck. Make the Balance $2000 to move onto the next game"<<endl;
    cout<<"You will have to bet if your card will be higher or lower than the dealer's card.\ndDepending on whether you win or lose, your balance will increase or decrease by the amount you bet.";
    cout<<"The suit rankings are mentioned below\n"<<"1. Diamonds ♦\n"<<"2. Hearts ♥\n"<<"3. Spades ♠\n"<<"4. Clubs ♣\n";
    sleep(5);
    while (true){
        cout<<"How much would you like to bet? ";
        cin>>bet;
        if (balance>=bet){
            srand(time(NULL));
            int player_rank=card_rank();
            int player_suit=card_suit();
            cout<<"YOU DREW"<<endl;
            print_card(player_rank,player_suit);
            cout<<"Will the next card be higher or lower? Enter "<<"h"<<" for higher or "<<"l"<<"for lower: ";
            char hl;
            cin>>hl;
            while (hl!='h' || hl!='l'){
                cout<<"Invalid Input. Please try again";
                cin>>hl;
            }
            int dealer_rank=card_rank();
            int dealer_suit=card_suit();
            cout<<"Dealer's Card"<<endl;
            print_card(dealer_rank,dealer_suit);
            if(hl=='h'){
                check(player_suit,dealer_suit,player_rank,dealer_rank,balance,bet);
            }
            else{
                check(dealer_suit,player_suit,dealer_rank,player_rank,balance,bet);
            }
        }
        else if(balance<bet){
            cout<<"You do not have enough balance"<<endl;
        }
        else if(balance>=2000){
            cout<<"Game Completed. Here is Your clue: M,A,R";
            ofstream fout;
            fout.open("r1check.txt", ios::app);
            fout << "Y";
            fout.close();
            break;
        }
        else if (balance==0)
        {
            cout<<"You have run out of money. Reset game.";
            balance=2000;
        }
        

    }
    
    
}
