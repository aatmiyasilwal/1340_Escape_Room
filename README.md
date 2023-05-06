# Identification of Team Members

**SILWAL Aatmiya** (3036056897) (GitHub: aatmiyasilwal)  
**SHETTY Siddhanth** (3036085965) (GitHub: shettysiddhanth)  
**LENG Sai Sinn Zom** (3036003682) (GitHub: saizom24)  
**KUMAR Uddashya** (3036085953) (GitHub: uddashya)

*NOTE: Our GitHub contributions may not provide an accurate representation of individual contributions as we frequently exchanged devices while working collaboratively on the code. Furthermore, we all contributed equally in various aspects beyond coding, such as video editing, ideation, and testing, which are not fully reflected in GitHub. As a team, we are proud of the collective effort that went into the project.*

## Description of Game & Overarching Game Rules

**BREAKOUT** is the ultimate escape room experience where you find yourself trapped in a lobby with 4 rooms and a main exit. Your only hope for freedom is to unlock all 4 locks on the main exit by completing a series of thrilling and challenging mini-games in each of the 4 rooms. But beware, once you enter a room, there's no going back! Each room has a unique set of mind-boggling puzzles that will put your skills to the test. With the successful completion of a room, you'll unlock the corresponding lock on the main exit. Are you up for the challenge? Play **BREAKOUT** now and see if you have what it takes to break free!

## Features Implemented

**1. Generation of random game sets or events:** The following parts of the game implement random sets or events:
  - The betting mini-game, Solitaire mini-game & Trivia mini-game in room 1.
  - The Monster mini-game & Trivia mini-game in room 2.
  - The Lock-Picking mini-game, Memory mini-game & Trivia mini-game in room 3.
  - The undercooked mini-game & Trivia mini-game in room 4.

**2. Data structures for storing game status:** We make use of different data structures like maps, vectors, and lists to set the grid for many of our minigames, while also storing game collectibles like coins.

**3. Dynamic memory management:** The game code features several instances of dynamic memory management, including a particularly efficient use of memory facilitated by the endwin() function.

**4. File input/output (e.g., for loading/saving game status):** The game implements an efficient data management system through the use of multiple files. This includes loading trivia questions from separate files, saving progress of each mini-game within rooms, and keeping track of overall room progress for a seamless gaming experience.

**5. Program codes in multiple files:** Multiple coding files are implemented for each of the rooms and all the mini-games within it. This is implemented in order to ensure better code readability and integration.

**6. Proper indentation and naming styles:** CamelCase has been used to name variables and proper indentation has been implemented throughout all .cpp files to ensure optimum code readability.

**7. In-code documentation:** Each function within each code file has comments which give brief explanations regarding the functionality of the code block. This ensures better code readability and interpretation.

## List of Non-standard C++ Libraries

N/A

## Compilation and execution instructions

To compile and run the game, run the following command onto the command line: `g++ -pedantic-errors -std=c++11 breakoutCombined.cpp -o breakoutCombined`
Then, run the executable file in the following way: `./breakoutCombined`.


