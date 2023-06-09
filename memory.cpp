#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <iomanip>  // for setw()
#include <fstream>
#include <string>

using namespace std;

// function to shuffle the DC comic book characters
void shuffle_characters(vector<string>& characters)
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(characters.begin(), characters.end(), default_random_engine(seed));
}

int main()
{
    system("clear");
    // DC comic book characters
    vector<string> DC_CHARACTERS;
    string superheros[]={"Batman", "Superman", "Wonder Woman", "Flash", "Aquaman", "Green Lantern", "Cyborg", "Shazam"};

    int i;
    for (i = 0; i < 8; i++) {
        DC_CHARACTERS.push_back(superheros[i]);
    }
    // Prompt user to pick the lock
    cout << "Welcome to the Memory mini game!\n\n";
    cout << "INSTRUCTIONS:\n";
    cout << "- 16 X spots on screen, with 8 unique DC character pairs.\n";
    cout << "- Enter a number (0-15) to flip a card.\n";
    cout << "- Incorrect guesses show the cards briefly. Remember them.\n";
    cout << "- Correct guesses reveal the cards on the 4x4 game board.\n";
    cout << "- Find all 8 pairs to win!\n\n";

    // initialize the game board
    const int ROWS = 4;
    const int COLS = 4;
    const int NUM_CARDS = ROWS * COLS;
    vector<string> game_board(NUM_CARDS);

    // populate the game board with DC comic book characters
    int character_index = 0;
    for (int i = 0; i < NUM_CARDS; i += 2)
    {
        game_board[i] = DC_CHARACTERS[character_index];
        game_board[i+1] = DC_CHARACTERS[character_index];
        character_index++;
    }

    // shuffle the DC comic book characters on the game board
    shuffle_characters(game_board);

    // initialize the game state
    vector<bool> card_flipped(NUM_CARDS, false);
    int num_matches_found = 0;
    int num_attempts = 0;

    // main game loop
    while (num_matches_found < NUM_CARDS / 2)
    {
        // display the game board
        for (int i = 0; i < NUM_CARDS; i++)
        {
            if (card_flipped[i])
            {
                cout << setw(15) << left << game_board[i];  // set width to 13
            }
            else
            {
                cout << setw(15) << left << "X";  // set width to 13
            }
            if ((i + 1) % COLS == 0)
            {
                cout << endl;
            }
        }

        // get user input for flipping cards
        int card1, card2;
        do
        {
            cout << "Enter two card numbers to flip (0-" << NUM_CARDS - 1 << "): ";
            cin >> card1 >> card2;
            
            if (card1 == card2) {
                cout << "Please enter two different card numbers." << endl;
                continue;
            }

            if (card1 < 0 || card1 >= NUM_CARDS || card2 < 0 || card2 >= NUM_CARDS) {
                cout << "Invalid input. Please enter two card numbers between 0 and " << NUM_CARDS - 1 << "." << endl;
                continue;
            }

            if (card_flipped[card1] || card_flipped[card2]) {
                cout << "Please enter two card numbers that have not been flipped yet." << endl;
                continue;
            }

            // flip the selected cards
            card_flipped[card1] = true;
            card_flipped[card2] = true;

            // display the selected cards
            cout << setw(15) << left << game_board[card1] << setw(15) << left << game_board[card2] << endl;

            // check for a match
            if (game_board[card1] == game_board[card2])
            {
                num_matches_found++;
                cout << "Match found!" << endl;
            }
            else
            {
                cout << "No match found." << endl;
                // close the cards if they don't match
                card_flipped[card1] = false;
                card_flipped[card2] = false;
            }

            num_attempts++;
        } while (game_board[card1] != game_board[card2]);

    }

    // display the final game state
    cout << "Congratulations, you found all the matches in " << num_attempts << " attempts!" << endl;
    cout << "Your two letters are: A & N\n";
    ofstream fout;
    fout.open("r3check.txt", ios::app);
    fout << "Memory AN" << endl;
    fout.close();
    this_thread::sleep_for(chrono::seconds(3));
    system("g++ -pedantic-errors -std=c++11 room3.cpp -lncursesw -o room3");
    system("./room3");
    return 0;
}
