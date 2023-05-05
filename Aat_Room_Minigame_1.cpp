#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;


//initialized emojis for better display
const string user_char = "😀︎";
const string trap_char = "💣";
const string monster_char = "👾";
const string coin_char = "🪙";
const string treasure_char = "🚩";
const string blank_char = "⬜";
const string water_char = "🟦";

//initializing global variables
bool perk_purchased = false;
bool monster_activate = false;
bool win_lose = false;
bool gameOver = false;


int monster_row, monster_col;
int treasure_row, treasure_col; 
int trap1_row, trap1_col;
int trap2_row, trap2_col;
int coin1_row, coin1_col;
int coin2_row, coin2_col;
int player_row = 0, player_col = 0;
int trigger_count = 0, coin_count = 0;

//function that makes the board in vector form
vector<vector<string> > initialise_board() {
    vector<vector<string> > board(5, vector<string>(8, blank_char));
    return board;
}

//function that displays board
void displayBoard(vector<vector<string> >& board){
    if (monster_activate){
        board[monster_row][monster_col] = monster_char;
    }  
    if (perk_purchased){
        board[treasure_row][treasure_col] = treasure_char;
    }
    if (trigger_count > 0){
        board[trap1_row][trap1_col] = trap_char;
        board[trap2_row][trap2_col] = trap_char;
    }
    for (size_t row = 0; row < board.size(); row++) {
        for (size_t col = 0; col < board[row].size(); col++) {
            cout << board[row][col] << " ";
        }
        cout << endl;
    }
}

//function that is responsibly to smartly move the monster
void monsterMove(vector<vector<string> >& board){
    int x_move = 0, y_move = 0;
    int rowDiff, colDiff;
    rowDiff = monster_row - player_row;
    colDiff = monster_col - player_col;
    cout << endl << "The monster moved two steps closer to you" << endl;
    
    if (abs(rowDiff) == 1){
        y_move = rowDiff * (-1);
    }
    else if (abs(rowDiff) > 1){
        if (colDiff != 0) {
            y_move = (-1) * (rowDiff / abs(rowDiff));
        }
        else{
            y_move = (-2) * (rowDiff / abs(rowDiff));
        }
    }
    if (abs(colDiff) == 1){
        x_move = colDiff * (-1);
    }
    else if (abs(colDiff) > 1){
        if (rowDiff != 0) {
            x_move = (-1) * (colDiff / abs(colDiff));
        }
        else{
            y_move = (-2) * (colDiff / abs(colDiff));
        }     
    }
    board[monster_row][monster_col] = blank_char;
    monster_row = (5 + monster_row + y_move) % 5;
    monster_col = (8 + monster_col + x_move) % 8;
    
    if (monster_row == treasure_row && monster_col == treasure_col){
        treasure_row = monster_row - y_move;
        treasure_col = monster_col - x_move;
        cout << endl << "The treasure and the monster recently switched places!" << endl;
    }
}

//fucntion that randomly places characters on the board
void characterAllocation(vector<vector<string> >& board){
    srand(time(nullptr));
    monster_row = rand() % 5;
    monster_col = rand() % 4 + 4;
    board[player_row][player_col] = user_char;
    
    while (true){
        trap1_row = rand() % 3;
        trap1_col = rand() % 8;
        trap2_row = rand() % 2 + 3;
        trap2_col = rand() % 8;
        
        if (!((trap1_row == 0 && trap1_col == 0) || (trap2_row == 0 && trap2_col == 0) || (trap1_row == monster_row && trap1_col == monster_col) || (trap2_row == monster_row && trap2_col == monster_col))){
            break;
        }
    }
    
    while (true){
        bool check = false;
        coin1_row = rand() % 3;
        coin2_row = rand() % 2 + 3;
        coin1_col = rand() % 4;
        coin2_col = rand() % 4 + 4; 
        int coin_list[2][2] = {{coin1_row, coin1_col}, {coin2_row, coin2_col}};
        for (int i = 0; i < 2; i++) {
            int row = coin_list[i][0];
            int col = coin_list[i][1];
            if (board[row][col] != blank_char || (row == 0 && col == 0) || (row == monster_row && col == monster_col) || row == trap1_row && col == trap1_col || row == trap2_row && col == trap2_col) {
                check = false;
                break;
            } 
            else {
                check = true;
            }
        }
        if (check){
            board[coin1_row][coin1_col] = coin_char;
            board[coin2_row][coin2_col] = coin_char;
            break;
        }
    }
    
    while (true){
        treasure_row = rand() % 5;
        treasure_col = rand() % 4 + 4;
        if (!(board[treasure_row][treasure_col] != blank_char || (treasure_row == monster_row && treasure_col == monster_col))){
            break;
        }
    }
}

//function that checks whether the game has ended and returns a boolean
bool end_check(vector<vector<string> >& board){
    if (player_row == treasure_row && player_col == treasure_col){
        system("clear");
        displayBoard(board);
        cout << "You finished Minigame 1! The clue to the key is 'Q' 'U'." << endl;
        win_lose = true;
        return true;
    }
    else if (player_row == monster_row && player_col == monster_col){
        system("cls");
        displayBoard(board);
        cout << "You were devoured! Try again!" << endl;
        win_lose = false;
        return true;
    }
    else{
        return false;
    }
}

//implementation of cyclic player movement
void movePlayer(vector<vector<string> >& board, string move){
    board[player_row][player_col] = blank_char;
    move = toupper(move[0]);
    if (move == "W") {
        player_row = (5 +player_row - 1) % 5;
    }
    else if (move == "S"){
        player_row = (5 + player_row + 1) % 5;
    }
    else if (move == "D"){
        player_col = (8 +player_col + 1) % 8;

    }
    else if (move == "A"){
        player_col = (8 + player_col - 1) % 8;
    }
    board[player_row][player_col] = user_char;
}

//main function
int main() {
    while (true){
        coin_count = 0;
        trigger_count = 0;
        player_row = 0;
        player_col = 0;
        
        gameOver = false;
        monster_activate = false;
        perk_purchased = false;
        win_lose = false;
        system("clear");

        vector<vector<string> > board = initialise_board();
        characterAllocation(board);
        displayBoard(board);
        while (true){
            while (true){
                //prompt to move the character
                string move;
                cout << "Enter where you want to move (W/A/S/D): ";
                cin >> move;
                if (move == "W" || move == "A" || move == "S" || move == "D" || move == "w" || move == "a" || move == "s" || move == "d"){
                    movePlayer(board, move);
                    break;
                }
            }
            //checking for gameOver possibilities
            gameOver = end_check(board);
            if (gameOver){
                break;
            }
            if (monster_activate){
                monsterMove(board);
                gameOver = end_check(board);
                if (gameOver){
                    break;
                }
            }
            if ((player_row == trap1_row && player_col == trap1_col) || (player_row == trap2_row && player_col == trap2_col)){
                trigger_count++;
                monster_activate = true;
                if (trigger_count == 1){
                    cout << "You have now awakened the monster" << endl;
                }
            }
            
            if((player_row == coin1_row && player_col == coin1_col) || (player_row == coin2_row && player_col == coin2_col)){
                coin_count++;
                cout << "You collected coin # " << coin_count << "!" << endl;
            }
            
            //implementation of powerups into this game
            if (coin_count == 2 && !perk_purchased){
                char user_choice;
                if (!monster_activate){
                    cout << endl << endl << "You now have an option to buy a powerup to make the treasure visible." << endl << "However, this will also activate the monster!" << endl << endl << "Do you want to buy the powerup for 2 coins? (Y/N): ";
                }
                else{
                    cout << endl << endl << "You now have an option to buy a powerup to make the treasure visible." << endl << endl << "Do you want to buy the powerup for 2 coins? (Y/N): ";
                }
                cin >> user_choice;
                if (toupper(user_choice) == 'Y'){
                    coin_count -= 2;
                    perk_purchased = true;
                    monster_activate = true;
                }
            }
            displayBoard(board);
        }
        //check to see if the player has won or lost
        if (win_lose){
            break;        
        }
        else{
            char userInput;
            cout << "Do you want to continue playing? (Y/N): " << endl;
            cin >> userInput;
            
            if (userInput == 'N' || userInput == 'n'){
                //go back to the main room
                break;
            }
        }
    }
    return 0;
}
