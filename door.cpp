#include <iostream>
#include <string>
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
        }
        else
        {
            std::cout << "The knob doesn't turn. The door remains locked." << std::endl;
        }
    }

    return 0;
}
