#include "game.h"

Game::Game()
{

}

Game::~Game()
{

}

void Game::PowerUp()
{

}

void Game::Collision()
{

}

void Game::GameOver()
{

}

void Game::GameLoop()
{
    std::pair<int, int> avatarPos = itsAvatar->getPosition();

    for (int i = 0; i < itsEnemies.size(); ++i) {
        itsEnemies[i]->move(avatarPos);
    }

}
