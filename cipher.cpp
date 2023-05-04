// MAKE THE CODE ERROR PROOF
// MAKE CODE BETTER IF POSSIBLE

#include <iostream>
#include <string>
using namespace std;

int main()
{
    string ciphertext = "Gur avtug vf qnexrfg whfg orsber gur qnja. Naq V cebzvfr lbh, gur qnja vf pbzvat."; // Encrypted message
    string plaintext = ""; // Decrypted message
    string guess = ""; // User's guess
    int attempts = 10; // Number of attempts allowed
    int shift = 13; // Number of positions to shift each letter

    // Decrypt the message
    for (int i = 0; i < ciphertext.length(); i++)
    {
        char c = ciphertext[i];
        if (c >= 'a' && c <= 'z')
        {
            c = (c - 'a' + shift) % 26 + 'a';
        }
        else if (c >= 'A' && c <= 'Z')
        {
            c = (c - 'A' + shift) % 26 + 'A';
        }
        plaintext += c;
    }

    // Loop for user input
    while (attempts > 0)
    {
        // Prompt user for guess
        cout << "Enter your guess: ";
        getline(cin, guess);

        // Check if guess is correct
        if (guess == plaintext)
        {
            cout << "Congratulations, this riddle serves as a clue to the word that will help you escape this room!" << endl;
            break;
        }
        else
        {
            attempts--;
            cout << "Incorrect guess. " << attempts << " attempts remaining." << endl;
        }
    }

    if (attempts == 0)
    {
        cout << "You have run out of attempts. Game over." << endl;
    }

    return 0;
}
