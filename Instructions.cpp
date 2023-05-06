#include <iostream>
#include <vector>
#include <chrono> // for sleep function
#include <thread> // for sleep function
#include <string>
#include <unistd.h>
using namespace std;
int main() {
    system("clear");
    vector<string>instructions;
    instructions.push_back("Welcome to BREAKOUT!!\n\n");
    instructions.push_back("INSTRUCTIONS:\n");
    instructions.push_back("- BREAKOUT is a game where your goal is to BREAKOUT from the lobby.\n");
    instructions.push_back("- However, the lobby has 4 locks and each lock will unlock only once you complete tasks in each of the 4 rooms.\n");
    instructions.push_back("- Now, enter your room of choice. However, think carefully because you cannot go back to previous rooms!\n");
    instructions.push_back("- Every room has 2-3 mini-games and a unique word that unlocks the door.\n");
    instructions.push_back("- Complete all mini-games in a room to receive the letters that make up the unique word.\n");
    instructions.push_back("- Make a meaningful word out of the letters to unlock the door and escape the room.\n");
    instructions.push_back("- Complete all rooms to unlock the 4 locks in the lobby and BREAKOUT!\n");
    instructions.push_back("- Good luck and may the best person BREAKOUT!!\n\n");
    for (int i = 0; i < 11; i++) {
        for (char c : instructions[i]) {
            cout << c << flush;
            this_thread::sleep_for(chrono::milliseconds(30)); // adjust delay time here
        }
    }
    cout<<"Press any key to continue.";
    string input;
    getline(cin, input);
    return 0;
}
