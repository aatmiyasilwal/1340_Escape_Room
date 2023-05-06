#include <iostream>
#include <vector>
#include <chrono> // for sleep function
#include <thread> // for sleep function
#include <string>
#include <unistd.h>
using namespace std;

int main() {
    vector<string> message;
    #include <iostream>
    message.push_back( "  ______   ______   .__   __.   _______ .______          ___   .___________.__    __   __          ___   .___________.__    ______   .__   __.      _______.\n");
    message.push_back( " /      | /  __  \\  |  \\ |  |  /  _____||   _  \\        /   \\  |           |  |  |  | |  |        /   \\  |           |  |  /  __  \\  |  \\ |  |     /       |\n");
    message.push_back( "|  ,----'|  |  |  | |   \\|  | |  |  __  |  |_)  |      /  ^  \\ `---|  |----|  |  |  | |  |       /  ^  \\ `---|  |----|  | |  |  |  | |   \\|  |    |   (----`\n");
    message.push_back( "|  |     |  |  |  | |  . `  | |  | |_ | |      /      /  /_\\  \\    |  |    |  |  |  | |  |      /  /_\\  \\    |  |    |  | |  |  |  | |  . `  |     \\   \\    \n");
    message.push_back( "|  `----.|  `--'  | |  |\\   | |  |__| | |  |\\  \\----./  _____  \\   |  |    |  `--'  | |  `----./  _____  \\   |  |    |  | |  `--'  | |  |\\   | .----)   |   \n");
    message.push_back( " \\______| \\______/  |__| \\__|  \\______| | _| `._____/__/     \\__\\  |__|     \\______/  |_______/__/     \\__\\  |__|    |__|  \\______/  |__| \\__| |_______/    \n");
    
    for (int i = 0; i < 6; i++) {
        for (char c : message[i]) {
            cout << c << flush;
            this_thread::sleep_for(chrono::milliseconds(10)); // adjust delay time here
        }
        cout << endl;
    }
    sleep(5);
    return 0;
}
