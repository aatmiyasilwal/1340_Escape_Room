#include <iostream>
#include <ncurses.h>

int main() {
    // Initialize ncurses
    initscr();

    // Switch to the console terminal
    endwin();

    // Do console terminal stuff here
    std::cout << "This is printed in the console terminal 1" << std::endl;

    // Switch back to the ncurses window
    refresh();

    // Do ncurses window stuff here
    printw("This is printed in the ncurses window");

    // Refresh the ncurses window
    refresh();

    // Wait for user input
    getch();

    // End ncurses
    endwin();
    
    std::cout << "This is printed in the console terminal 2" << std::endl;
    std::cout << "This is printed in the console terminal 3" << std::endl;
    std::cout << "This is printed in the console terminal 4" << std::endl;

    return 0;
}
