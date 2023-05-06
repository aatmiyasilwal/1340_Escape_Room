#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include<stdlib.h>
#include<time.h>
#include <algorithm>
#include <chrono> // for sleep function
#include <thread> // for sleep function
using namespace std;


void printq(string s){
    for (char c : s) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(30)); // adjust delay time here
    }
    cout << endl;
}
void prints(vector<string>s){
     for (string c : s) {
        cout << c << flush;
        cout<<endl;
        this_thread::sleep_for(chrono::milliseconds(30)); // adjust delay time here
    }
    cout << endl;
}
int main(int argc, char *argv[]) {
    system("clear");
    vector<string> questions;
    vector<vector<string> > options(5, vector<string>(4, ""));
    vector<string> answers;
    string ques_number, text, line, out_file_name;
    int line_count = 0, question_count = 0, inner_count = 0;
    ifstream fin;
    ofstream fout;
    string filename = argv[1];
    string clues = argv[2];
    string source_file = argv[3];
    
    if(filename == "trivia1.txt"){
        out_file_name = "r1check.txt";
    }
    else if (filename == "trivia2.txt"){
        out_file_name = "r2check.txt";
    }
    else if (filename == "trivia3.txt"){
        out_file_name = "r3check.txt";
    }
    else if (filename == "trivia4.txt"){
        out_file_name = "r4check.txt";
    }
    
    fin.open(filename.c_str());
    fout.open(out_file_name.c_str(), ios::app);

    while(fin >> ques_number){
        getline(fin, line);
        if (line_count % 6 == 0){
            questions.push_back(line.substr(1));
            inner_count=0;
        }
        else if (line_count % 6 >= 1 && line_count % 6 <= 4){
            options[question_count][inner_count] = line.substr(1);
            inner_count++;
        }
        else{
            answers.push_back(line.substr(1,1));
            question_count++;
        }
        line_count++;
    }
    
    fin.close();

    srand(time(NULL));
    int correct_answers = 0, random_value;
    int nums[5] = {0, 1, 2, 3, 4};
    random_shuffle(nums, nums + 5);

    string user_answer;
    for (int m = 0; m < 5; m ++){
        random_value = nums[m];
        printq(questions[random_value]);
        printq("The options are: ");
        cout << endl;

        for (int j = 0; j < options[random_value].size(); j++){
            cout << char('a' + j) << ". " << options[random_value][j] << endl;
        }

        cout << "What's your answer? (a/b/c/d): ";
        cin >> user_answer;

        if (user_answer.substr(0,1) == answers[random_value]){
            printq("Congratulations! That was the correct answer!");
            correct_answers++;
            if (correct_answers != 3){
                printq("Onto the next question!");
                cout << endl;
            }
        }
        else{
            printq("That was the wrong answer! Try another question!");
            cout << endl;
        }
        if (correct_answers >= 3){
            break;
        }
           
    }
    if (correct_answers >= 3){
        cout << endl << "You successfully passed the trivia round. The clues for this level are " << clues << endl;
        this_thread::sleep_for(chrono::seconds(3));
        fout << "Trivia " << clues << endl;  
        string system_running = "g++ -pedantic-errors -std=c++11 " + source_file + " -lncursesw -o room" + source_file.substr(4,1);
        string last_run = "./" + source_file.substr(0,5);
        system(system_running.c_str());
        system(last_run.c_str());
        
    }
    else{
        cout << endl << "You couldn't finish the trivia round!" << endl;
        this_thread::sleep_for(chrono::seconds(3));
        string system_running = "g++ -pedantic-errors -std=c++11 " + source_file + " -lncursesw -o room" + source_file.substr(4,1);
        string last_run = "./" + source_file.substr(0,5);
        system(system_running.c_str());
        system(last_run.c_str());
    }
    fout.close();
    return 0;
}
