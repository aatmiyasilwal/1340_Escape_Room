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


int main(int argc, char *argv[]) {
    vector<string> questions;
    vector<vector<string> > options(5, vector<string>(4, ""));
    vector<string> answers;
    string ques_number, text, line;
    int line_count = 0, question_count = 0, inner_count = 0;
    ifstream fin;
    ofstream fout;
    string filename = argv[1];

    fin.open(filename.c_str());

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
    
    for (int i = 0; i < options.size(); i++){
        
    }

    srand(time(0));
    int correct_answers = 0, random_value;
    int nums[5] = {0, 1, 2, 3, 4};
    random_shuffle(nums, nums + 5);
    string user_answer;
    for (int m = 0; m < 5; m ++){
        random_value = nums[m];
        cout << questions[random_value] << endl << "The options are: " << endl;

        for (int j = 0; j < options[random_value].size(); j++){
            cout << char('a' + j) << ". " << options[random_value][j] << endl;
        }

        cout << "What's your answer? (a/b/c/d): ";
        cin >> user_answer;

        if (user_answer.substr(0,1) == answers[random_value]){
            correct_answers++;
        }
        if (correct_answers >= 3){
            break;
        }
           
    }
    if (correct_answers >= 3){
        cout << "You successfully passed the trivia round. The clues for this level are '', ''";
    }
	return 0;
}
