//cpp file that functions as our makefile

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
	//initializing new files
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
	
	//running c++ files in order
	system("g++ -pedantic-errors -std=c++11 welcomePage.cpp -o welcomePage");
	system("./welcomePage");

	system("g++ -pedantic-errors -std=c++11 Instructions.cpp -o instructions");
	system("./instructions");

	system("g++ -pedantic-errors -std=c++11 loading5.cpp -lncursesw -o loading5");
	system("./loading5");

	system("g++ -pedantic-errors -std=c++11 main_room.cpp -lncursesw -o mainRoom");
	system("./mainRoom");

	return 0;
}

