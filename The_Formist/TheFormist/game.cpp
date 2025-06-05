#include "game.h"
#include "gun.h"
#include "rangedweapon.h"
#include <QRandomGenerator>


Avatar *Game::getItsAvatar() const
{
    return itsAvatar;
}

Weapon *Game::getItsWeapon() const
{
    return itsWeapon;
}

std::vector<Projectile *> Game::getItsAvatarProjectiles() const
{
    return itsAvatarProjectiles;
}

std::pair<int,int> Game::getItsBorder() const
{
    return itsBorder;
}

std::vector<Projectile *> Game::getItsEnemyProjectiles() const
{
    return itsEnemyProjectiles;
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
    for (Projectile* p : itsAvatarProjectiles) {
        delete p;
    }
    itsAvatarProjectiles.clear();

    for (Projectile* p : itsEnemyProjectiles) {
        delete p;
    }
    itsEnemyProjectiles.clear();

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
    for (std::vector<Projectile*>::iterator avProjIt = itsAvatarProjectiles.begin(); avProjIt != itsAvatarProjectiles.end(); )
    {
        Projectile* proj = *avProjIt;
        if(proj->getItsPosition().first < 0 || proj->getItsPosition().first > 4000 || proj->getItsPosition().second < 0 || proj->getItsPosition().second > 2000)
        {
            delete proj;
            itsAvatarProjectiles.erase(avProjIt);
        }
        else
        {
            bool hit = false;

            for (std::vector<Enemy*>::iterator enemyIt = itsEnemies.begin(); enemyIt != itsEnemies.end(); )
            {
                Enemy* e = *enemyIt;

                if (proj->getItsRectF().intersects(e->getItsRectF()))
                {
                    e->takeDamage(itsWeapon->getItsDamage());
                    hit = true;
                    if (e->isDead())
                    {
                        delete e;
                        enemyIt = itsEnemies.erase(enemyIt);
                        itsAvatar->addXP(e->getItsGivenXP());
                    }
                    else
                        ++enemyIt;

                    break; // projectile touche un ennemi, on sort
                }
                else
                    ++enemyIt;
            }
            if (hit)
            {
                delete proj;
                avProjIt = itsAvatarProjectiles.erase(avProjIt);
            }
            else
                ++avProjIt;
        }
    }

    for (std::vector<Projectile*>::iterator enProjIt = itsEnemyProjectiles.begin(); enProjIt != itsEnemyProjectiles.end(); )
    {
        Projectile * proj = *enProjIt;
        if(proj->getItsPosition().first < 0 || proj->getItsPosition().first > 4000 || proj->getItsPosition().second < 0 || proj->getItsPosition().second > 2000)
        {
            delete proj;
            enProjIt = itsEnemyProjectiles.erase(enProjIt);
        }
        else
        {
            if(proj->getItsRectF().intersects(itsAvatar->getItsQRect()->toRectF()))
            {
                itsAvatar->takeDamage(proj->getItsDamage());
                delete proj;
                enProjIt = itsEnemyProjectiles.erase(enProjIt);
            }
            else
                ++enProjIt;
        }
    }

    // === COLLISION ENNEMIS / AVATAR ===
    for (std::vector<Enemy*>::iterator enemyIt = itsEnemies.begin(); enemyIt != itsEnemies.end(); ++enemyIt)
    {
        Enemy* e = *enemyIt;

        if (e->getItsRectF().intersects(*itsAvatar->getItsQRect()) && e->getType() != TRIANGLE)
        {
            itsAvatar->takeDamage(e->getItsStrength());
        }
    }
}


void Game::GameOver()
{
    return;
}


void Game::GameLoop()
{
    QRect* avatarRect = itsAvatar->getItsQRect();

    // Tir de l'arme
    if (itsWeapon->getIsShooting())
    {
        std::pair<int,int> avatarPos = itsAvatar->getItsPosition();
        if(mouseTarget != avatarPos)
        {
            QPoint center = itsAvatar->getItsQRect()->center();
            Projectile* p = new Projectile(mouseTarget, std::pair<int,int>(center.x(), center.y()), {5,5}, 10, 5);
            itsAvatarProjectiles.push_back(p);
            itsWeapon->setIsShooting(false);
        }
    }

    for (Enemy* enemy : itsEnemies)
    {
        std::pair<float, float> oldPos = enemy->getItsPosition();

        // Déplacement vers l'avatar
        enemy->act(std::pair<float, float>(avatarRect->center().x(), avatarRect->center().y()));

        // l'empêche de traverser l'avatar
        if (enemy->getItsRectF().intersects(*avatarRect))
        {
            enemy->setItsPosition(oldPos);
        }

        // Tir de l'ennemi
        if (enemy->getIsShooting())
        {
            Projectile* p = new Projectile(
                std::pair<float,float>(avatarRect->center().x(), avatarRect->center().y()),
                enemy->getItsPosition(),
                {5,5}, 10,
                enemy->getItsStrength()
                );
            itsEnemyProjectiles.push_back(p);
            enemy->setIsShooting(false);
        }
    }

    // Mettre à jour la position des projectiles
    for (Projectile * aProj : itsAvatarProjectiles)
        aProj->move();

    for (Projectile * eProj : itsEnemyProjectiles)
        eProj->move();


    itsAvatar->move(itsBorder);

    Collision();

    //prise de niveau et améliorations
    if (itsAvatar->getItsXP() >= itsAvatar->getItsMaxXP())
    {
        itsAvatar->levelUp();
        itsAvatar->addMaxXP(2);
        itsAvatar->setItsXP(0);
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
        Enemy* e = new Enemy ({60,60},img);
        itsEnemies.push_back(e);
    }
    delete img;
}

void Game::upgrade()
{
    RangedWeapon* rw = dynamic_cast<RangedWeapon*>(itsWeapon);
    if (itsAvatar->getItsLevel() % 5 == 0)
    {
        std::vector<int> availableUpgrades = {MORE_PROJECTILE, REVERSE_PROJECTILE, MORE_DAMAGE, MORE_HP};
        std::shuffle(availableUpgrades.begin(), availableUpgrades.end(), *QRandomGenerator::global());

        for (int upgrade : availableUpgrades)
        {
            switch (upgrade)
            {
            case MORE_PROJECTILE:
                if (rw->getItsNbProjectiles() < 3)
                {
                    rw->AddNbProjectile();
                    return;
                }
                break;

            case REVERSE_PROJECTILE:
                if (rw->getItsNbReverseProjectile() < 2)
                {
                    rw->AddNbReverseProjectile();
                    return;
                }
                break;

            case MORE_DAMAGE:
                rw->AddBaseDamage(2);
                return;

            case MORE_HP:
                itsAvatar->addHP(5);
                itsAvatar->addMaxHP(5);
                return;
            }
        }
    }
}
