#include "Player.h"

Player::Player()
{
    score = 0;
    lives = 5;
}

void Player::addScore(int points)
{
    score = score + points;
}

void Player::loseLife()
{
    if (lives > 0)
    {
        lives--;
    }
}

int Player::getScore()
{
    return score;
}

int Player::getLives()
{
    return lives;
}

bool Player::isAlive()
{
    return lives > 0;
}

void Player::reset()
{
    lives = 5;
}

void Player::resetGame()
{
    score = 0;
    lives = 5;
}