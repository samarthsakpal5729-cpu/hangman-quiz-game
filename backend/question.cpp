#include "Question.h"

Question::Question(string q, string a, string c)
{
    questionText = q;
    answer = a;
    category = c;
}

string Question::getQuestion()
{
    return questionText;
}

string Question::getAnswer()
{
    return answer;
}

string Question::getCategory()
{
    return category;
}