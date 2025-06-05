#include "game.h"
#include "gun.h"
#include "rangedweapon.h"
#include <QRandomGenerator>
#include <random>


Avatar *Game::getItsAvatar() const
{
    return itsAvatar;
}

Weapon *Game::getItsWeapon() const
{
    return itsWeapon;
}

std::vector<Projectile *> Game::getItsProjectiles() const
{
    return itsProjectiles;
}

std::pair<int,int> Game::getItsBorder() const
{
    return itsBorder;
}

Game::Game(QObject *parent)
    : QObject{parent}
{
    QImage* img = new QImage("Patate.txt");
    itsBorder = std::pair(4000,2000);
    itsAvatar = new Avatar(img, std::pair(itsBorder.first/2,itsBorder.second/2));
    itsWeapon = new Gun(10, 1, img);
    itsTimer = new QTimer(this);
    itsEnemyTimer = new QTimer(this);
    connect(itsTimer, SIGNAL(timeout()), this, SLOT(GameLoop()));
    connect(itsEnemyTimer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));
    itsTimer->start(10);
    itsEnemyTimer->start(1000);
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

    delete itsTimer;

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
    for (std::vector<Projectile*>::iterator projIt = itsProjectiles.begin(); projIt != itsProjectiles.end(); )
    {
        Projectile* proj = *projIt;
        bool hit = false;

        for (std::vector<Enemy*>::iterator enemyIt = itsEnemies.begin(); enemyIt != itsEnemies.end(); )
        {
            Enemy* e = *enemyIt;

            if (proj->getItsRectF().intersects(e->getItsRectF()))
            {
                e->takeDamage(itsWeapon->getItsDamage());  // Utilisation de la méthode publique
                hit = true;

                if (e->isDead())
                {
                    delete e;
                    enemyIt = itsEnemies.erase(enemyIt);
                }
                else
                {
                    ++enemyIt;
                }

                break; // projectile touche un ennemi, on sort
            }
            else
            {
                ++enemyIt;
            }
        }

        if (hit)
        {
            delete proj;
            projIt = itsProjectiles.erase(projIt);
        }
        else
        {
            ++projIt;
        }
    }
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
            if(mouseTarget != avatarPos)
            {
                Projectile* p = new Projectile(mouseTarget, std::pair<int,int>(avatarPos.first + itsAvatar->getItsQRect()->width()/2,avatarPos.second + itsAvatar->getItsQRect()->height()/2), {5,5}, 10, 5);
                itsProjectiles.push_back(p);
                itsWeapon->setIsShooting(false);
            }
        }
    }

    // Mettre à jour la position des projectiles
    for (Projectile * proj : itsProjectiles)
        proj->move();

    //Mettre à jour la position des ennemis
    for (Enemy * enemi : itsEnemies)
        enemi->move(itsAvatar->getItsPosition());
    itsAvatar->move(itsBorder);


    Collision();

    //prise de niveau et améliorations
    if (itsAvatar->getItsXP() >= itsAvatar->getItsMaxXP())
    {
        itsAvatar->levelUp();
        itsAvatar->setItsMaxXP(2);
    }

}


std::vector<Enemy *> Game::getItsEnemies() const
{
    return itsEnemies;
}

void Game::spawnEnemy()
{
    QImage* img = new QImage("enemy.txt");
    if (itsAvatar)
    {
        Enemy* e = new Enemy ({60,60},img,10);
        itsEnemies.push_back(e);
    }
    delete img;
}

void Game::upgrade()
{
    RangedWeapon* rw = dynamic_cast<RangedWeapon*>(itsWeapon);
    if (itsAvatar->getItsLevel()%5)
    {
        std::uniform_int_distribution<int> dist(1, 4);
        int aUpgrade = dist(*QRandomGenerator::global());
        switch(aUpgrade) {
        case MORE_PROJECTILE:
            if (rw->getItsNbProjectiles() < 3)
                rw->setItsNbProjectiles(1);
            else
                aUpgrade++;
            break;

        case REVERSE_PROJECTILE:
            if (rw->getItsNbReverseProjectile() < 2)
                rw->setItsNbReverseProjectile(1);
            else
                aUpgrade++;
            break;

        case MORE_DAMAGE:
            rw->setItsBaseDamage(itsWeapon->getItsBaseDamage());

            break;

        case MORE_HP:
            itsAvatar->setItsHP(5);
            itsAvatar->setItsMaxHP(5);
            break;
        }
    }

}

