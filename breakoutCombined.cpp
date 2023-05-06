#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include<stdlib.h>
#include<time.h>
#include <algorithm>
using namespace std;

int main(){

	ofstream foutOne("r1check.txt", ios::trunc);
	ofstream foutTwo("r2check.txt", ios::trunc);
	ofstream foutThree("r3check.txt", ios::trunc);
	ofstream foutFour("r4check.txt", ios::trunc);
	ofstream foutOverall("totalcheck.txt", ios::trunc);

	foutOne.close();
	foutTwo.close();
	foutThree.close();
	foutFour.close();
	foutOverall.close();

//	system("g++ -std=c++11 welcomePage.cpp -o welcomePage");
//	system("./welcomePage");
//
//	system("g++ -std=c++11 Instructions.cpp -o instructions");
//	system("./instructions");
//
//	system("g++ -std=c++11 loading5.cpp -lncurses -o loading5");
//	system("./loading5");

	system("g++ -std=c++11 main_room.cpp -lncurses -o mainRoom");
	system("./mainRoom");

//	system("g++ -0 finalScreen finalScreen.cpp");
//	system("./finalScreen");
	
	return 0;
}

/*int mainRoomStuff(){

	//after agreeing to enter to room 1
	system("g++ -o loading3 loading3.cpp");
	system("./loading3");

	system("g++ -o room1 room1.cpp");
	system("./room1");

	//inside room 1
		//after interacting with soltaire game
		system("g++ -o soltaire main.cpp");
		system("./soltaire");

		//inside soltaire: write into room1Progress.txt if level is completed

		//after interacting with betting game
		system("g++ -o bettingGame bettingGame.cpp");
		system("./bettingGame");/Users/sai3012/Desktop/Engg_1340/1340_Escape_Room-main/room2.cpp

		//after interacting with trivia game
		system("g++ -o triviaReader triviaReader.cpp");
		system("./triviaReader trivia1.txt");

		//after interacting with the door
		system("g++ -o door door.cpp");
		system("./door SUPERMAN");

	//inside room 2
		//after interacting with the monster minigame
		system("g++ -o monsterGame Aat_Room_Minigame_1.cpp");
		system("./monsterGame");

		//after interacting with trivia game
		system("g++ -o triviaReader triviaReader.cpp");
		system("./triviaReader trivia2.txt HAR.");

		//after interacting with the door
		system("g++ -o door door.cpp");
		system("./door HARLEY");

	//inside room 3
		//after interacting with lockpicking game
		system("g++ -o lockpicking lockpicking.cpp");
		system("./lockpicking");

		//after interacting with memory game
		system("g++ -o memory memory.cpp");
		system("./memory");

		//after interacting with trivia game
		system("g++ -o triviaReader triviaReader.cpp");
		system("./triviaReader trivia3.txt");	

		//after interacting with the door		
		system("g++ -o door door.cpp");
		system("./door BATMAN");

	//inside room 4
		//after interacting with cooking game
		system("g++ cook_v1.cpp -lncursesw -o cooking");
		system("./cooking");

		//after interacting with trivia game
		system("g++ -o triviaReader triviaReader.cpp");
		system("./triviaReader trivia4.txt");

		system("g++ -o door door.cpp");
		system("./door WONDER");	


		


}
*/
