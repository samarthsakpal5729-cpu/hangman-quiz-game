#ifndef GAME_H
#define GAME_H

#include "Question.h"
#include "Player.h"

class Game
{
private:
    Player player;

public:
    Game();

    void showWelcome();
    void showMenu();
    int startGame();
    void playQuestion(Question question);
    void showHangman();
    void setColor(int color);
};

#endif