#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <random>

using namespace std;

int main(int argc, char *argv[])
{
    std::string input = "";
    std::string password = argv[1];
    bool unlocked = false;

    while (!unlocked)
    {
        std::cout << " ___________________ " << std::endl;
        std::cout << "|                   |" << std::endl;
        std::cout << "|   _________       |" << std::endl;
        std::cout << "|  |         |      |" << std::endl;
        std::cout << "|  |    O    |      |" << std::endl;
        std::cout << "|  |         |      |" << std::endl;
        std::cout << "|  |         |      |" << std::endl;
        std::cout << "|  |         |      |" << std::endl;
        std::cout << "|  |         |      |" << std::endl;
        std::cout << "|__|_________|______|" << std::endl;

        cout << endl << endl;

        string str = password;
        shuffle(str.begin(), str.end(), mt19937{random_device{}()});
        cout << "The jumbled up clue for this door is: " << str << endl;

        std::cout << "Enter the password (6 characters): ";
        std::cin >> input;

        if (input.length() != 6)
        {
            std::cout << "Password must be 6 characters long!" << std::endl;

            continue;
        }

        if (input == password)
        {
            unlocked = true;
            std::cout << "The knob turns and the door opens!" << std::endl;

            ofstream fout;
            fout.open("totalcheck.txt", ios::app);
            if (password == "SHAZAM"){
                fout << "Room1" << endl;
            }
            else if (password == "HARLEY"){
                fout << "Room2" << endl;

            }
            else if (password == "BATMAN"){
                fout << "Room3" << endl;

            }
            else if (password == "WONDER"){
                fout << "Room4" << endl;
            }

            fout.close();
            
            system("g++ -std=c++11 main_room.cpp -lncurses -o mainRoom");
	        system("./mainRoom");
        }
        else
        {
            std::cout << "The knob doesn't turn. The door remains locked." << std::endl;
        }
    }

    return 0;
}
