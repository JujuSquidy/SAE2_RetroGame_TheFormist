#include "game.h"

Game::Game()
{
    fireTimer.start(); // démarrer le chrono
}

Game::~Game()
{
    // Supprimer tous les projectiles
    for (Projectile* p : itsProjectiles) {
        delete p;
    }
    itsProjectiles.clear();

    // Supprimer les ennemis
    for (Enemy* e : itsEnemies) {
        delete e;
    }
    itsEnemies.clear();

    // Supprimer l'avatar
    delete itsAvatar;
    itsAvatar = nullptr;

    itsTimer.stop();

}
void Game::updateMouseTarget(int x, int y)
{
    mouseTarget = {x, y};
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

    // Tir de l'arme
    if (fireTimer.elapsed() >= 1000 * itsWeapon->getItsAttackSpeed())
    {
        if (itsAvatar)
        {
            std::pair<int,int> avatarPos = itsAvatar->getItsPosition();
            Projectile* p = new Projectile(mouseTarget, avatarPos, {5,5}, 10, 5);
            itsProjectiles.push_back(p);
        }
        fireTimer.restart(); // réinitialiser pour la prochaine seconde
    }

    // Mettre à jour la position des projectiles
    for (Projectile * proj : itsProjectiles)
        proj->move();
}

