#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
using namespace std;


int main() {
    vector<string> questions;
    vector<vector<string> > options(5, vector<string>(4, ""));
    vector<string> answers;
    string ques_number, text, line;
    int line_count = 0, question_count = 0, inner_count = 0;
    ifstream fin;
    ofstream fout;
    
    fin.open("trivia2.txt");

    while(fin >> ques_number){
        getline(fin, line);
        if (line_count % 6 == 0){
            questions.push_back(line);
            inner_count = 0;
        }
        else if (line_count % 6 >= 1 && line_count % 6 <= 4){
            options[question_count][inner_count] = line;
            inner_count++;
        }
        else{
            answers.push_back(line);
            question_count++;
        }
        line_count++;
    }
    
    fin.close();

	return 0;
}
