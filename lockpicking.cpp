#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>

using namespace std;

int main() {
    system("clear");
    srand(time(NULL));
    const int NUM_DIGITS = 4;
    int combination[NUM_DIGITS];
    int guess[NUM_DIGITS];
    bool isGuessCorrect = false;

    // Generate random combination
    for (int i = 0; i < NUM_DIGITS; i++) {
        combination[i] = rand() % 10; // Generate a random number between 0 and 9
    }

    // Prompt user to pick the lock
    cout << "Welcome to the lock picking mini game!\n\n";
    cout << "INSTRUCTIONS:\n";
    cout << "- Guess the combination of a " << NUM_DIGITS << " digit lock by entering 4 digits separated by space.\n";
    cout << "- The system will check only the first digit initially.\n";
    cout << "- If it's correct, you will feel a notch and you will see a # in the interactive lock.\n";
    cout << "- Keep the first digit the same and proceed to the second digit.\n";
    cout << "- Repeat the process until all 4 digits are guessed correctly to unlock the lock.\n\n";

    // Start guessing
    int num_guesses = 0;
    do {
        // Prompt user for a guess
        num_guesses++;
        string input;
        cout << "Guess #" << num_guesses << " (enter 4 digits separated by a space): ";
        getline(cin, input);
        stringstream ss(input);
        bool isInputValid = true;
        for (int i = 0; i < NUM_DIGITS; i++) {
            if (!(ss >> guess[i])) {
                isInputValid = false;
                break;
            }
        }
        if (!isInputValid) {
            cout << "Invalid input. Please enter four digits separated by a space.\n";
            continue;
        }

        // Check if the guess is correct
        bool hasNotch[NUM_DIGITS] = {false, false, false, false};
        for (int i = 0; i < NUM_DIGITS; i++) {
            if (guess[i] == combination[i]) {
                hasNotch[i] = true;
            }
        }

        // Display result
        bool allCorrect = true;
        for (int i = 0; i < NUM_DIGITS; i++) {
            if (hasNotch[i]) {
                cout << "You feel a notch at digit " << i + 1 << "!\n";
            } else {
                cout << "Sorry, that digit is incorrect. Please try again.\n";
                allCorrect = false;
                break;
            }
        }

        // Display interactive lock
        cout << "\n";
        for (int i = 0; i < NUM_DIGITS; i++) {
            if (hasNotch[i]) {
                cout << "# ";
            } else {
                cout << "- ";
            }
        }
        cout << "\n\n";

        if (allCorrect) {
            isGuessCorrect = true;
            cout << "Congratulations! You have successfully picked the lock!\n";
            cout << "Your two letters are: B & A\n";
            ofstream fout;
            fout.open("r3check.txt", ios::app);
            fout << "Lockpicking BA" << endl;
            fout.close();
            this_thread::sleep_for(chrono::seconds(5));

        }

    } while (!isGuessCorrect);
    
    system("g++ room3.cpp -lncurses -o room3");
    system("./room3");
    return 0;
}
