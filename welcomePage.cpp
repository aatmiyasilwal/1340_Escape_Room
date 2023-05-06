#include <iostream>
#include <vector>
#include <chrono> // for sleep function
#include <thread> // for sleep function
#include <string>
#include <unistd.h>
#include <fstream>

using namespace std;

//animated text for cover page
int main() {
    system("clear");
    vector<string> message;
    message.push_back("| ___ \\              | |             | |  ");
    message.push_back("| |_/ /_ __ ___  __ _| | _____  _   _| |_ ");
    message.push_back("| ___ \\ '__/ _ \\/ _` | |/ / _ \\| | | | __|");
    message.push_back("| |_/ / | |  __/ (_| |   < (_) | |_| | |_ ");
    message.push_back("\\____/|_|  \\___|\\__,_|_|\\_\\___/ \\__,_|\\__|");
    
    for (int i = 0; i < 5; i++) {
        for (char c : message[i]) {
            cout << c << flush;
            this_thread::sleep_for(chrono::milliseconds(15)); // adjust delay time here
        }
        cout << endl;
    }
    sleep(5);
    return 0;
}
