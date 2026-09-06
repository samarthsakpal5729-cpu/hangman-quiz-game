#ifndef PLAYER_H
#define PLAYER_H

class Player
{
private:
    int score;
    int lives;

public:
    Player();

    void addScore(int points);
    void loseLife();

    int getScore();
    int getLives();

    bool isAlive();

    void reset();
    void resetGame();
};

#endif