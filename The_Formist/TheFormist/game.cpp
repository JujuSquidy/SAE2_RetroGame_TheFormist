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

long Game::getItsScore() const
{
    return itsScore;
}

void Game::AddScore(long aScore)
{
    itsScore += aScore;
}

QElapsedTimer Game::getItsInGameTimer() const
{
    return *itsInGameTimer;
}

std::vector<PowerUp *> Game::getItsPowerUp() const
{
    return itsPowerUp;
}

Game::Game(QObject *parent)
    : QObject{parent}
{
    itsBorder = std::pair(4000,2000);
    gameWindowSize = {960, 540};
    itsAvatar = new Avatar(std::pair(itsBorder.first/2,itsBorder.second/2));
    itsWeapon = new Gun(10, 1);
    itsTimer = new QTimer(this);

    itsInGameTimer = new QElapsedTimer;
    itsEnemyTimer = new QTimer(this);

    connect(itsTimer, SIGNAL(timeout()), this, SLOT(GameLoop()));
    connect(itsEnemyTimer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));
    itsTimer->start(10);
    itsEnemyTimer->start(1000);
    itsInGameTimer->start();

    itsPowerUpTimer = new QTimer(this);
    connect(itsPowerUpTimer, SIGNAL(timeout()), this, SLOT(spawnPowerUP()));
    itsPowerUpTimer->start(10'000);
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

    for (PowerUp* p : itsPowerUp)
        delete p;
    itsPowerUp.clear();

    // Supprimer l'avatar
    delete itsAvatar;
    itsAvatar = nullptr;

    delete itsWeapon;
    itsWeapon = nullptr;

    itsTimer->stop();
    delete itsTimer;
    itsTimer = nullptr;

    itsEnemyTimer->stop();
    delete itsEnemyTimer;
    itsEnemyTimer = nullptr;

    delete itsInGameTimer;
    itsInGameTimer = nullptr;

    delete itsPowerUpTimer;
    itsPowerUpTimer = nullptr;
}

void Game::updateMouseTarget(int x, int y)
{
    mouseTarget = {x, y};
}

void Game::spawnPowerUP()
{

        int centerX = itsAvatar->getItsQRect()->center().x();
        int centerY = itsAvatar->getItsQRect()->center().y();
        int viewW  = gameWindowSize.first;
        int viewH  = gameWindowSize.second;
        int margin = 20;

        int left   = centerX - viewW/2  + margin;
        int right  = centerX + viewW/2  - margin;
        int top    = centerY - viewH/2  + margin;
        int bottom = centerY + viewH/2  - margin;

        left   = qMax(0, left);
        right  = qMin(itsBorder.first, right);
        top    = qMax(0, top);
        bottom = qMin(itsBorder.second, bottom);

        // Pick a random position in that rect
        int x = QRandomGenerator::global()->bounded(left,  right+1);
        int y = QRandomGenerator::global()->bounded(top,   bottom+1);

        // Pick a random power-up type
        std::uniform_int_distribution<int> typeDist(0, 4);
        PType ptype = static_cast<PType>(typeDist(*QRandomGenerator::global()));

        // Create and register
        PowerUp* pu = new PowerUp({x,y}, ptype);
        itsPowerUp.push_back(pu);
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
                        itsAvatar->addXP(e->getItsGivenXP());
                        switch (e->getType())
                        {
                            case TRIANGLE:
                                AddScore(1);
                                break;

                            case CIRCLE:
                                AddScore(1);
                                break;

                            case SQUARE:
                                AddScore(2);
                                break;

                            case BOSS:
                                AddScore(50);
                                break;
                        }
                        delete e;
                        enemyIt = itsEnemies.erase(enemyIt);
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
                if (itsAvatar->getHasShield() == true)
                {
                    itsAvatar->desactivateShield();  // Bouclier actif => pare le coup
                }
                else
                {
                    itsAvatar->takeDamage(proj->getItsDamage());  // Pas de bouclier => prend les dégâts
                }

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

    for (std::vector<PowerUp*>::iterator it = itsPowerUp.begin(); it != itsPowerUp.end();  )
    {
        PowerUp* p = *it;

        if (p->getItsRectF().intersects(*itsAvatar->getItsQRect()))
        {
            if(p->getItsType() == SHIELD)
            {
                itsAvatar->activateShield();
                delete p;
                it = itsPowerUp.erase(it);
                break;

            }
            else if(p->getItsType() == SYRINGE)
            {
                p->ActivateSyringe();
                p->setIsPicked(true);
                it++;
                break;

            }
            else if(p->getItsType() == BLOOD)
            {
                itsAvatar->addHP(10);
                delete p;
                it = itsPowerUp.erase(it);
                break;

            }
            else if(p->getItsType() == PEPPER)
            {
                p->ActivatePepper();
                p->setIsPicked(true);
                it++;
                break;

            }
            else if(p->getItsType() == BOOTS)
            {
                p->ActivateBoots();
                p->setIsPicked(true);
                it++;
                break;
            }
        }
        else
        {
            ++it;
        }
    }

}


void Game::GameOver()
{
    itsTimer->stop();
    itsEnemyTimer->stop();
    emit gameOver();
}


void Game::GameLoop()
{
    QRect* avatarRect = itsAvatar->getItsQRect();

    updateTemporaryBoosts();
    RangedWeapon* rw = dynamic_cast<RangedWeapon*>(itsWeapon);
    if (itsWeapon->getIsShooting())
    {
        if (rw->getItsMultipleProjectileDelay().elapsed() > 30)
        {
            std::pair<int,int> avatarPos = itsAvatar->getItsPosition();

            if (mouseTarget != avatarPos)
            {
                QPoint center = avatarRect->center();

                if (rw->getNbProjectilesShooted() < rw->getItsNbProjectiles())
                {
                    std::pair<int,int> target = mouseTarget;
                    Projectile* p = new Projectile(target, {center.x(), center.y()}, {5,5}, 10, 5);
                    itsAvatarProjectiles.push_back(p);
                    rw->addNbProjectilesShooted();
                }
                else if (rw->getNbReverseProjectilesShooted() < rw->getItsNbReverseProjectile())
                {
                    int dx = mouseTarget.first - avatarPos.first;
                    int dy = mouseTarget.second - avatarPos.second;
                    std::pair<int,int> reversedTarget = {avatarPos.first - dx, avatarPos.second - dy};
                    Projectile* p = new Projectile(reversedTarget, {center.x(), center.y()}, {5,5}, 10, 5);
                    itsAvatarProjectiles.push_back(p);
                    rw->addNbReverseProjectilesShooted();
                }

                rw->getItsMultipleProjectileDelay().start();
            }

            if (rw->getNbProjectilesShooted() >= rw->getItsNbProjectiles() &&
                rw->getNbReverseProjectilesShooted() >= rw->getItsNbReverseProjectile())
            {
                itsWeapon->setIsShooting(false);
            }
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

    if (itsAvatar->getItsHP() == 0)
    {
        GameOver();
        return;
    }
    //prise de niveau et améliorations
    if (itsAvatar->getItsXP() >= itsAvatar->getItsMaxXP())
    {
        itsAvatar->levelUp();
        itsAvatar->addMaxXP(2);
        itsAvatar->setItsXP(0);
        if (itsAvatar->getItsLevel() % 5 == 0)
        {
            upgrade();
        }
    }
}


std::vector<Enemy *> Game::getItsEnemies() const
{
    return itsEnemies;
}

void Game::spawnEnemy()
{
    if (!itsAvatar) return;

    int centerX = itsAvatar->getItsQRect()->center().x();
    int centerY = itsAvatar->getItsQRect()->center().y();
    int viewWidth = gameWindowSize.first;
    int viewHeight = gameWindowSize.second;
    int margin = 60;

    std::uniform_int_distribution<int> sideDist(0, 3); // 0 = left, 1 = right, 2 = top, 3 = bottom
    int side = sideDist(*QRandomGenerator::global());

    int x, y;
    switch (side)
    {
    case 0: // LEFT
    {
        std::uniform_int_distribution<int> xDist(centerX - viewWidth/2 - margin - 100, centerX - viewWidth/2 - margin);
        std::uniform_int_distribution<int> yDist(centerY - viewHeight/2 - margin, centerY + viewHeight/2 + margin);
        x = xDist(*QRandomGenerator::global());
        y = yDist(*QRandomGenerator::global());
        break;
    }
    case 1: // RIGHT
    {
        std::uniform_int_distribution<int> xDist(centerX + viewWidth/2 + margin, centerX + viewWidth/2 + margin + 100);
        std::uniform_int_distribution<int> yDist(centerY - viewHeight/2 - margin, centerY + viewHeight/2 + margin);
        x = xDist(*QRandomGenerator::global());
        y = yDist(*QRandomGenerator::global());
        break;
    }
    case 2: // TOP
    {
        std::uniform_int_distribution<int> xDist(centerX - viewWidth/2 - margin, centerX + viewWidth/2 + margin);
        std::uniform_int_distribution<int> yDist(centerY - viewHeight/2 - margin - 100, centerY - viewHeight/2 - margin);
        x = xDist(*QRandomGenerator::global());
        y = yDist(*QRandomGenerator::global());
        break;
    }
    case 3: // BOTTOM
    {
        std::uniform_int_distribution<int> xDist(centerX - viewWidth/2 - margin, centerX + viewWidth/2 + margin);
        std::uniform_int_distribution<int> yDist(centerY + viewHeight/2 + margin, centerY + viewHeight/2 + margin + 100);
        x = xDist(*QRandomGenerator::global());
        y = yDist(*QRandomGenerator::global());
        break;
    }
    }

    Enemy* e;
    if(itsInGameTimer->elapsed() > (120000 * NoBoss))
    {
        e = new Enemy({x, y}, BOSS);
        NoBoss++;
    }
    else
    {
        std::uniform_int_distribution<int> distrib(0, 2);
        int tEnemy = distrib(*QRandomGenerator::global());
        e = new Enemy({x, y}, EType(tEnemy));
    }
    itsEnemies.push_back(e);
}

void Game::upgrade()
{
    RangedWeapon* rw = dynamic_cast<RangedWeapon*>(itsWeapon);
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

void Game::updateTemporaryBoosts()
{
    for (std::vector<PowerUp*>::iterator it = itsPowerUp.begin(); it != itsPowerUp.end();)
    {
        PowerUp* p = *it;
        if (p->getIsFinished() == false && p->getIsPicked() == true) // Check if the boost is active
        {
            if(p->getItsType() == SYRINGE)
            {
                itsWeapon->setItsPUDamageMult(10);
            }
            else if(p->getItsType() == PEPPER)
            {
                itsWeapon->setItsPUAttackSpeedMult(10);
            }
            else if(p->getItsType() == BOOTS)
            {
                itsAvatar->setItsPUSpeedMult(3);
            }
            it++; // on avance proprement l'itérateur
        }
        else if (p->getIsFinished() == true)
        {
            if(p->getItsType() == SYRINGE)
            {
                itsWeapon->setItsPUDamageMult(1);
            }
            else if(p->getItsType() == PEPPER)
            {
                itsWeapon->setItsPUAttackSpeedMult(1);
            }
            else if(p->getItsType() == BOOTS)
            {
                itsAvatar->setItsPUSpeedMult(1);
            }

            delete p;
            it = itsPowerUp.erase(it); // ne pas faire it++ ici
        }
        else
        {
            // Aucun cas géré => avancer l'itérateur quand même
            it++;
        }
    }
}
