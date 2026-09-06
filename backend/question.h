#ifndef QUESTION_H
#define QUESTION_H

#include <string>

using namespace std;

class Question
{
private:
    string questionText;
    string answer;
    string category;

public:
    Question(string q, string a, string c);

    string getQuestion();
    string getAnswer();
    string getCategory();
};

#endif