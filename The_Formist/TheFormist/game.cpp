#include "game.h"

Avatar *Game::getItsAvatar() const
{
    return itsAvatar;
}

std::vector<Projectile *> Game::getItsProjectiles() const
{
    return itsProjectiles;
}

Game::Game(QObject *parent)
    : QObject{parent}
{
    QImage* img = new QImage("Patate.txt");
    itsBorder = std::pair(4000,2000);
    itsAvatar = new Avatar(img, std::pair(0,0));
    itsWeapon = new Gun(10, 1, *img);
    itsTimer = new QTimer(this);
    connect(itsTimer, SIGNAL(timeout()), this, SLOT(GameLoop()));
    itsTimer->start(10);
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

    delete itsWeapon;
    itsWeapon = nullptr;

    itsTimer->stop();

}
void Game::updateMouseTarget(int x, int y)
{
    mouseTarget = {x, y};
}

void Game::PowerUp()
{
    return;
}

void Game::Collision()
{
    return;
}

void Game::GameOver()
{
    return;
}

void Game::GameLoop()
{

    // Tir de l'arme
    if (itsWeapon->getIsShooting())
    {
        if (itsAvatar)
        {
            std::pair<int,int> avatarPos = itsAvatar->getItsPosition();
            Projectile* p = new Projectile(mouseTarget, avatarPos, {5,5}, 10, 5);
            itsProjectiles.push_back(p);
            itsWeapon->setIsShooting(false);
        }

    }

    // Mettre à jour la position des projectiles
    for (Projectile * proj : itsProjectiles)
        proj->move();

    itsAvatar->move();
}

