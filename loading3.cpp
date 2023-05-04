#include <ncurses.h>
#include <string>
#include <chrono>
#include <thread>
using namespace std;
int main()
{
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    // Get the size of the terminal
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // Define the text to animate
    string text = "Loading.......%";

    // Define the position of the text
    int x = max_x / 2 - text.length() / 2;
    int y = max_y / 2;

    // Define the duration of the animation in seconds
    int duration_sec = 3;

    // Start the animation loop
    auto start_time = chrono::system_clock::now();
    while (true)
    {
        // Get the current time
        auto current_time = chrono::system_clock::now();

        // Calculate the elapsed time in seconds
        std::chrono::duration<double> elapsed_time = current_time - start_time;
        double elapsed_sec = elapsed_time.count();

        // If the animation has run for the desired duration, break out of the loop
        if (elapsed_sec >= duration_sec)
        {
            break;
        }

        // Clear the screen
        clear();

        // Calculate the position of the text
        int new_x = x + static_cast<int>(elapsed_sec * 20);
        int new_y = y;

        // Print the text at its new position
        mvprintw(new_y, new_x, text.c_str());

        // Refresh the screen
        refresh();

        // Sleep for a short amount of time
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    // End ncurses
    endwin();

    return 0;
}
