// MAKE THE CODE ERROR PROOF
// GIVE TWO LETTERS AT THE END 
// MAKE CODE BETTER IF POSSIBLE

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

// Function to generate a shuffled grid of DC comics characters
vector<string> generateGrid()
{
    vector<string> characters = {"Batman", "Superman", "Wonder Woman", "Aquaman", "Flash", "Green Lantern", "Cyborg", "Martian Manhunter"};
    vector<string> grid;

    // Duplicate each character to create pairs
    for (int i = 0; i < characters.size(); i++)
    {
        grid.push_back(characters[i]);
        grid.push_back(characters[i]);
    }

    // Shuffle the grid using a random number generator
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(grid.begin(), grid.end(), default_random_engine(seed));

    return grid;
}

// Function to print the current state of the grid
void printGrid(vector<string> grid, vector<bool> revealed)
{
    for (int i = 0; i < grid.size(); i++)
    {
        if (revealed[i])
        {
            cout << grid[i] << " ";
        }
        else
        {
            cout << "X ";
        }

        if ((i + 1) % 4 == 0)
        {
            cout << endl;
        }
    }
}

// Function to check if two cards match
bool matchCards(vector<string> grid, int index1, int index2)
{
    return grid[index1] == grid[index2];
}

int main()
{
    vector<string> grid = generateGrid();
    vector<bool> revealed(grid.size(), false);

    int numMatches = 0;
    int numAttempts = 0;

    cout << "Welcome to the DC comics memory game!" << endl;
    cout << "Match pairs of DC comics characters to win." << endl;
    cout << "Enter two card positions (e.g. 1 2):" << endl;

    // Main game loop
    while (numMatches < grid.size() / 2)
    {
        // Print the current state of the grid
        printGrid(grid, revealed);

        // Prompt the user for input
        int index1, index2;
        cin >> index1 >> index2;

        // Check if the user's input is valid
        if (index1 < 1 || index1 > grid.size() || index2 < 1 || index2 > grid.size() || index1 == index2 || revealed[index1-1] || revealed[index2-1])
        {
            cout << "Invalid input. Please enter two different card positions (e.g. 1 2)." << endl;
            continue;
        }

        // Increment the number of attempts
        numAttempts++;

        // Reveal the selected cards
        revealed[index1-1] = true;
        revealed[index2-1] = true;

        // Check if the selected cards match
        if (matchCards(grid, index1-1, index2-1))
        {
            cout << "Match!" << endl;
            numMatches++;
        }
        else
        {
            cout
