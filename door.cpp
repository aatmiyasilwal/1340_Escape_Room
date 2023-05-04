#include <iostream>
#include <string>

int main()
{
    std::string input = "";
    std::string password = "BATMAN";
    bool unlocked = false;

    while (!unlocked)
    {
        std::cout << " _________   " << std::endl;
        std::cout << "|         |  " << std::endl;
        std::cout << "|    O    |  " << std::endl;
        std::cout << "|         |  " << std::endl;
        std::cout << "|         |  " << std::endl;
        std::cout << "|         |  " << std::endl;
        std::cout << "|         |  " << std::endl;
        std::cout << "|         |  " << std::endl;
        std::cout << "|_________|  " << std::endl;

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
