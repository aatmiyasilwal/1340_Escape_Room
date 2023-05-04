// MAKE THE CODE ERROR PROOF
// GIVE TWO LETTERS AT THE END 
// MAKE CODE BETTER IF POSSIBLE

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    // Set up the game
    const int PIN_LENGTH = 5;  // Length of the lock pin
    const int MAX_GUESSES = 10;  // Maximum number of guesses
    const int MAX_PRESSURE = 10;  // Maximum pressure that can be applied
    const int MIN_PRESSURE = 1;  // Minimum pressure that can be applied
    const int PRESSURE_INCREMENT = 1;  // Amount of pressure to increment with each turn
    const int MIN_WAIT_TIME = 1;  // Minimum wait time between turns
    const int MAX_WAIT_TIME = 3;  // Maximum wait time between turns
    const int SCORE_INCREMENT = 10;  // Amount to increment the score with each successful turn

    int pin[PIN_LENGTH];  // The lock pin
    int guess[PIN_LENGTH];  // The player's current guess
    int pressure = MIN_PRESSURE;  // The current pressure being applied
    int guessesLeft = MAX_GUESSES;  // Number of guesses left
    int waitTime;  // Amount of time to wait between turns
    int score = 0;  // The player's current score
    bool unlocked = false;  // Whether or not the door has been unlocked
    bool keyFound = false;  // Whether or not the key has been found

    // Seed the random number generator
    srand(time(NULL));

    // Generate the lock pin
    for (int i = 0; i < PIN_LENGTH; i++)
    {
        pin[i] = rand() % MAX_PRESSURE + MIN_PRESSURE;
    }

    // Print out the game instructions
    cout << "Welcome to lock picking mini-game!" << endl;
    cout << "You need to pick the lock to unlock the door or find a key." << endl;
    cout << "You have " << MAX_GUESSES << " attempts to pick the lock." << endl;
    cout << "You use a pick and tension wrench to apply pressure to the lock." << endl;
    cout << "You can apply pressure between " << MIN_PRESSURE << " and " << MAX_PRESSURE << "." << endl;
    cout << "You need to apply pressure in the right direction and at the right time to pick the lock." << endl;
    cout << "Each time you apply the right amount of pressure, you will earn " << SCORE_INCREMENT << " points." << endl;
    cout << "Good luck!" << endl << endl;

    // Game loop
    while (!unlocked && guessesLeft > 0){
        // Print out the current game state
        cout << "----------------------" << endl;
        cout << "Guesses left: " << guessesLeft << endl;
        cout << "Current pressure: " << pressure << endl;
        cout << "Current score: " << score << endl;
        cout << "----------------------" << endl;

        // Prompt the player for their guess
        cout << "Enter your guess (5 digits between 1 and 10): ";
        for (int i = 0; i < PIN_LENGTH; i++)
        {
            cin >> guess[i];
        }
    }}
        // Compare
