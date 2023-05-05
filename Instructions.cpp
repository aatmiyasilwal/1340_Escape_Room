#include <iostream>
#include <string>

using namespace std;

int main() {
    // Instructions
    cout << "Welcome to BREAKOUT!!\n\n"
         << "INSTRUCTIONS:\n"
         << "- BREAKOUT is a game where your goal is to BREAKOUT from the lobby.\n"
         << "- However, the lobby has 4 locks and each lock will unlock only once you complete tasks in each of the 4 rooms.\n"
         << "- Now, enter your room of choice. However, think carefully because you cannot go back to previous rooms!\n"
         << "- Every room has 2-3 mini-games and a unique word that unlocks the door.\n"
         << "- Complete all mini-games in a room to receive the letters that make up the unique word.\n"
         << "- Make a meaningful word out of the letters to unlock the door and escape the room.\n"
         << "- Complete all rooms to unlock the 4 locks in the lobby and BREAKOUT!\n"
         << "- Good luck and may the best person BREAKOUT!!\n\n"
         << "Press any key to continue.";

    // Wait for user input to continue
    string input;
    cin >> input;

    return 0;
}
