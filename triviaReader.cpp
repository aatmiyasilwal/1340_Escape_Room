#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include<stdlib.h>
#include<time.h>
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
        cout << questions[i] << endl;
        for (int j = 0; j < options[i].size(); j++){
            cout << options[i][j] << endl;
        }
        cout << endl << answers[i] << endl;
    }
	return 0;
}
