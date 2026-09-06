#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <windows.h>

#include "Game.h"

using namespace std;

Game::Game()
{
}

void Game::setColor(int color)
{
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        color
    );
}

void Game::showWelcome()
{
    setColor(11);

    cout << "======================================" << endl;
    cout << "          HANGMAN QUIZ GAME           " << endl;
    cout << "======================================" << endl;

    setColor(7);
}

int Game::startGame()
{
    player.resetGame();

    vector<Question> questions;

    questions.push_back(
        Question(
            "Which programming language is used for OOP?",
            "JAVA",
            "Programming"
        )
    );

    questions.push_back(
        Question(
            "Which language is known for web page structure?",
            "HTML",
            "Web Development"
        )
    );

    questions.push_back(
        Question(
            "Which operating system is open source?",
            "LINUX",
            "Operating System"
        )
    );

    questions.push_back(
        Question(
            "What is used to store multiple values in C++?",
            "ARRAY",
            "Programming"
        )
    );

    questions.push_back(
        Question(
            "Which language is popular for artificial intelligence?",
            "PYTHON",
            "Artificial Intelligence"
        )
    );

    cout << "\nGame Started!" << endl;

    for (int i = 0; i < questions.size(); i++)
    {
        player.reset();

        cout << "\n======================================" << endl;
        cout << "             QUESTION " << i + 1 << endl;
        cout << "======================================" << endl;

        playQuestion(questions[i]);

        if (!player.isAlive())
        {
            cout << "\nGame ended because you lost all lives." << endl;
            break;
        }
    }

    cout << "\n======================================" << endl;
    cout << "             GAME FINISHED            " << endl;
    cout << "======================================" << endl;

    cout << "Final Score: " << player.getScore() << endl;

    return 0;
}

void Game::playQuestion(Question question)
{
    string answer = question.getAnswer();
    string hiddenAnswer = "";
    string guessedLetters = "";

    for (int i = 0; i < answer.length(); i++)
    {
        if (answer[i] == ' ')
            hiddenAnswer += ' ';
        else
            hiddenAnswer += '_';
    }

    while (player.isAlive() && hiddenAnswer != answer)
    {
        cout << "\nCategory: "
             << question.getCategory() << endl;

        cout << "Question: "
             << question.getQuestion() << endl;

        showHangman();

        cout << "\nLives: "
             << player.getLives() << endl;

        cout << "Score: "
             << player.getScore() << endl;

        cout << "Guessed Letters: "
             << guessedLetters << endl;

        cout << "Answer: ";

        for (int i = 0; i < hiddenAnswer.length(); i++)
        {
            cout << hiddenAnswer[i] << " ";
        }

        cout << endl;

        string input;

        cout << "\nEnter a letter: ";
        cin >> input;

        if (input.length() != 1)
        {
            cout << "Please enter only ONE letter!" << endl;
            continue;
        }

        char guess = toupper(input[0]);

        if (!isalpha(guess))
        {
            cout << "Please enter a letter from A-Z!" << endl;
            continue;
        }

        if (guessedLetters.find(guess) != string::npos)
        {
            cout << "You already guessed "
                 << guess << "!" << endl;
            continue;
        }

        guessedLetters += guess;

        bool found = false;

        for (int i = 0; i < answer.length(); i++)
        {
            if (answer[i] == guess)
            {
                hiddenAnswer[i] = guess;
                found = true;
            }
        }

        if (found)
        {
            cout << "Correct guess!" << endl;
            player.addScore(5);
        }
        else
        {
            cout << "Wrong guess!" << endl;
            player.loseLife();
        }
    }

    if (hiddenAnswer == answer)
    {
        cout << "\nCORRECT ANSWER!" << endl;
        cout << "Answer: " << answer << endl;
    }
    else
    {
        cout << "\nGAME OVER!" << endl;
        cout << "Correct Answer: " << answer << endl;
    }
}

void Game::showHangman()
{
    int wrong = 5 - player.getLives();

    cout << endl;

    if (wrong == 0)
    {
        cout << "  +---+" << endl;
        cout << "  |   |" << endl;
        cout << "      |" << endl;
        cout << "      |" << endl;
        cout << "      |" << endl;
        cout << "=========" << endl;
    }
    else if (wrong == 1)
    {
        cout << "  +---+" << endl;
        cout << "  |   |" << endl;
        cout << "  O   |" << endl;
        cout << "      |" << endl;
        cout << "      |" << endl;
        cout << "=========" << endl;
    }
    else if (wrong == 2)
    {
        cout << "  +---+" << endl;
        cout << "  |   |" << endl;
        cout << "  O   |" << endl;
        cout << "  |   |" << endl;
        cout << "      |" << endl;
        cout << "=========" << endl;
    }
    else if (wrong == 3)
    {
        cout << "  +---+" << endl;
        cout << "  |   |" << endl;
        cout << "  O   |" << endl;
        cout << " /|   |" << endl;
        cout << "      |" << endl;
        cout << "=========" << endl;
    }
    else if (wrong == 4)
    {
        cout << "  +---+" << endl;
        cout << "  |   |" << endl;
        cout << "  O   |" << endl;
        cout << " /|\\  |" << endl;
        cout << "      |" << endl;
        cout << "=========" << endl;
    }
    else
    {
        cout << "  +---+" << endl;
        cout << "  |   |" << endl;
        cout << "  O   |" << endl;
        cout << " /|\\  |" << endl;
        cout << " / \\  |" << endl;
        cout << "=========" << endl;
    }
}

void Game::showMenu()
{
    cout << "\n======================================" << endl;
    cout << "              MAIN MENU               " << endl;
    cout << "======================================" << endl;

    cout << "1. Start Game" << endl;
    cout << "2. Instructions" << endl;
    cout << "3. Exit" << endl;

    cout << "\nEnter your choice: ";
}