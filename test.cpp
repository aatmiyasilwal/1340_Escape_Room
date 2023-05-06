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
    WINDOW * win = newwin(24, 50, 0, 0);
    refresh();
    box(win, 0, 0);
    mvwprintw(win, 12, 10, "This is printed in the ncurses window");
    wrefresh(win);

    // Refresh the ncurses window
    refresh();

    // Wait for user input
    getch();

    // End ncurses
    endwin();
    int x;
    
    std::cout << "This is printed in the console terminal 2" << std::endl;
    std::cin >> x;
    std::cout << "This is printed in the console terminal 3" << std::endl;
    
    system("g++ -pedantic-errors -std=c++11 Aat_Room_Minigame_1.cpp -o monsterGame");
    system("./monsterGame");
    
    std::cout << "This is printed in the console terminal 4" << std::endl;
    
    system("g++ -pedantic-errors -std=c++11 cook_v1.cpp -lncursesw -o cooking");
    system("./cooking");

    return 0;
}
