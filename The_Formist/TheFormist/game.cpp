#include "game.h"
#include "fireball.h"
#include "gun.h"
#include "rocketlauncher.h"
#include "katana.h"
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

std::pair<int, int> Game::getMouseTarget() const
{
    return mouseTarget;
}
std::vector<PowerUp *> Game::getItsPowerUp() const
{
    return itsPowerUp;
}

std::vector<AreaDamage *> Game::getItsAreaDamages() const
{
    return itsAreaDamages;
}

QMediaPlayer *Game::getBackgroundMusicPlayer() const
{
    return backgroundMusicPlayer;
}

Game::Game(WeaponType type, QObject *parent)
    : QObject{parent}
{
    itsBorder = std::pair(4000,2000);
    gameWindowSize = {960, 540};
    itsAvatar = new Avatar(std::pair(itsBorder.first/2,itsBorder.second/2));
    switch (type)
    {
    case GUN:
        itsWeapon = new Gun(10, 2, {5,5});   //initialisation d'un gun
        break;
    case KATANA:
        itsWeapon = new Katana(50, 2); //initialisation d'un katana
        break;
    case FIREBALL:
        itsWeapon = new FireBall(5,1,{5,5},{100,100});
        break;
    case ROCKETLAUNCHER:
        itsWeapon = new RocketLauncher(10,1,{5,5},{100,100});
        break;
    }
    itsTimer = new QTimer(this);
    itsInGameTimer = new QElapsedTimer;
    itsEnemyTimer = new QTimer(this);

    connect(itsTimer, SIGNAL(timeout()), this, SLOT(GameLoop()));
    connect(itsEnemyTimer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));
    itsTimer->start(10);
    itsEnemyTimer->start(itsEnemySpawnTime);
    itsInGameTimer->start();

    itsPowerUpTimer = new QTimer(this);
    connect(itsPowerUpTimer, SIGNAL(timeout()), this, SLOT(spawnPowerUP()));
    itsPowerUpTimer->start(30000);

    audioOutput = new QAudioOutput(this);

    backgroundMusicPlayer = new QMediaPlayer(this);
    backgroundMusicPlayer->setAudioOutput(audioOutput);

    backgroundMusicPlayer->setSource(QUrl("qrc:/Music/Game.mp3"));
    backgroundMusicPlayer->setLoops(QMediaPlayer::Infinite);  // <--- boucle infinie

    audioOutput->setVolume(1); // volume entre 0.0 et 1.0
    backgroundMusicPlayer->play();
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
            if (hit || (typeid(*itsWeapon)==typeid(FireBall) && proj->getItsDistanceTraveled() >= dynamic_cast<FireBall*>(itsWeapon)->getItsFireBallRange()))
            {
                if(typeid(*itsWeapon) == typeid(RocketLauncher))
                {
                    RocketLauncher * RL = dynamic_cast<RocketLauncher*>(itsWeapon);
                    //---------------------------------Création de la zone de dégats-------------------------------------------//
                        AreaDamage * AD = new AreaDamage(
                                                    RL->getItsAreaSize(),                                               // taille de la zone d'effet
                                                    {proj->getItsRectF().center().x()-(RL->getItsAreaSize().first/2),   // Position x du QRect de l'explosion
                                                     proj->getItsRectF().center().y()-(RL->getItsAreaSize().second/2)}, // Position y du QRect de l'explosion
                                                    1,                                                                  // Nombre de dégats infligés avant disparition de la zone
                                                    RL->getItsDamage()                                                  // Dégats infligés par l'explosion
                                                    );
                    //--------------------------------------------------------------------------------------------------------//
                    itsAreaDamages.push_back(AD);
                }
                else if(typeid(*itsWeapon) == typeid(FireBall))
                {
                    FireBall * FB = dynamic_cast<FireBall*>(itsWeapon);
                    //---------------------------------Création de la zone de dégats-------------------------------------------//
                        AreaDamage * AD = new AreaDamage(
                                                    FB->getItsAreaSize(),                                               // taille de la zone d'effet
                                                    {proj->getItsRectF().center().x()-(FB->getItsAreaSize().first/2),   // Position x du QRect de l'explosion
                                                     proj->getItsRectF().center().y()-(FB->getItsAreaSize().second/2)}, // Position y du QRect de l'explosion
                                                    5,                                                                  // Nombre de dégats infligés avant disparition de la zone
                                                    FB->getItsDamage()                                                  // Dégats infligés par l'explosion
                                                    );
                    //--------------------------------------------------------------------------------------------------------//
                    itsAreaDamages.push_back(AD);
                }
                delete proj;
                avProjIt = itsAvatarProjectiles.erase(avProjIt);
            }
            else
                ++avProjIt;
        }
    }

    for(std::vector<AreaDamage*>::iterator ADit = itsAreaDamages.begin(); ADit != itsAreaDamages.end(); )
    {
        AreaDamage* AD = *ADit;
        if(AD->getIsBurning())
        {
            if(AD->expired())
            {
                delete AD;
                ADit = itsAreaDamages.erase(ADit);
            }
            else
            {
                for (std::vector<Enemy*>::iterator enemyIt = itsEnemies.begin(); enemyIt != itsEnemies.end(); )
                {
                    Enemy* e = *enemyIt;

                    if (AD->getItsRectF().intersects(e->getItsRectF()))
                    {
                        e->takeDamage(AD->getItsDamage());
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
                    }
                    else
                        ++enemyIt;
                }
            AD->addTick();
            AD->resetBurn();
            ++ADit;
            }
        }
        else
        {
            ++ADit;
        }
    }
    if(Katana* katana = dynamic_cast<Katana*>(itsWeapon))
    {
        if (katana && katana->getIsShooting())
        {
            QRectF hitbox = katana->katanaAreaDamage({itsAvatar->getItsQRect()->center().x(),itsAvatar->getItsQRect()->center().y()}, mouseTarget);

            for (std::vector<Enemy*>::iterator enemyIt = itsEnemies.begin(); enemyIt != itsEnemies.end(); )
            {
                Enemy* e = *enemyIt;
                float ex = e->getItsPosition().first;
                float ey = e->getItsPosition().second;

                if (hitbox.contains(ex, ey))
                {
                    e->takeDamage(itsWeapon->getItsDamage());
                }

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
                {
                    ++enemyIt;
                }
            }
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
                if(!p->getIsPicked())
                {
                    p->ActivateSyringe();
                    p->setIsPicked(true);
                }
                ++it;
                break;
            }
            else if(p->getItsType() == BLOOD )
            {
                itsAvatar->addHP(20);
                delete p;
                it = itsPowerUp.erase(it);
                break;

            }
            else if(p->getItsType() == PEPPER )
            {
                if(!p->getIsPicked())
                {
                    p->ActivatePepper();
                    p->setIsPicked(true);
                }
                it++;
                break;
            }
            else if(p->getItsType() == BOOTS )
            {
                if(!p->getIsPicked())
                {
                    p->ActivateBoots();
                    p->setIsPicked(true);
                }

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
    itsPowerUpTimer->stop();
    emit gameOver();
}


void Game::GameLoop()
{
    updateTemporaryBoosts();
    if(RangedWeapon* rw = dynamic_cast<RangedWeapon*>(itsWeapon))
    {
        if (itsWeapon->getIsShooting())
        {
            if (rw->getItsMultipleProjectileDelay().elapsed() > itsWeapon->getItsAttackSpeed()/3)
            {
                std::pair<int,int> avatarCenter = {itsAvatar->getItsQRect()->center().x(),itsAvatar->getItsQRect()->center().y()};

                if (mouseTarget != avatarCenter)
                {
                    if (rw->getNbProjectilesShooted() < rw->getItsNbProjectiles())
                    {
                        std::pair<int,int> target = mouseTarget;
                        Projectile* p = new Projectile(target, {avatarCenter.first, avatarCenter.second}, rw->getItsProjSize(), 5, 5);
                        itsAvatarProjectiles.push_back(p);
                        rw->addNbProjectilesShooted();
                    }
                    if (rw->getNbReverseProjectilesShooted() < rw->getItsNbReverseProjectile())
                    {
                        int dx = mouseTarget.first - avatarCenter.first;
                        int dy = mouseTarget.second - avatarCenter.second;
                        std::pair<int,int> reversedTarget = {avatarCenter.first - dx, avatarCenter.second - dy};
                        Projectile* p = new Projectile(reversedTarget, {avatarCenter.first, avatarCenter.second}, rw->getItsProjSize(), 5, 5);
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
    }

    QRect* avatarRect = itsAvatar->getItsQRect();
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
                {5,5},
                2,
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

    //Pas appelé avant car sinon ne gère pas la collision (l'autre solution serait de mettre isShooting à false dans la collision)
    if (dynamic_cast<Katana*>(itsWeapon))
    {
        if (itsWeapon->getIsShooting())
        {
            itsWeapon->setIsShooting(false);
        }
    }

    if (itsAvatar->getItsHP() == 0)
    {
        GameOver();
        return;
    }
    //prise de niveau et améliorations
    if (itsAvatar->getItsXP() >= itsAvatar->getItsMaxXP())
    {
        int temp = itsAvatar->getItsXP() - itsAvatar->getItsMaxXP();

        itsAvatar->levelUp();
        itsAvatar->addMaxXP(2);
        itsAvatar->setItsXP(temp);
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

    int x = 0, y = 0;
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
    if(itsInGameTimer->elapsed() > (60000 * NoBoss))
    {
        e = new Enemy({x, y}, BOSS, itsEnemyHPMult);
        NoBoss++;
        if(itsEnemySpawnTime>500)
        {
            itsEnemySpawnTime-=100;
            itsEnemyTimer->start(itsEnemySpawnTime);
        }
        itsEnemyHPMult += 0.1;
    }
    else
    {
        std::uniform_int_distribution<int> distrib(0, 2);
        int tEnemy = distrib(*QRandomGenerator::global());
        e = new Enemy({x, y}, EType(tEnemy), itsEnemyHPMult);
    }
    itsEnemies.push_back(e);
}

void Game::upgrade()
{
    std::vector<int> availableUpgrades = {MORE_PROJECTILE, REVERSE_PROJECTILE, MORE_DAMAGE, MORE_HP};
    std::shuffle(availableUpgrades.begin(), availableUpgrades.end(), *QRandomGenerator::global());    

    for (int upgrade : availableUpgrades)
    {
        switch (upgrade)
        {
            case MORE_PROJECTILE:
                if (RangedWeapon* rw = dynamic_cast<RangedWeapon*>(itsWeapon))
                {
                    if (rw->getItsNbProjectiles() < 3)
                    {
                        rw->AddNbProjectile();
                        return;
                    }
                }
                else if (Katana* katana = dynamic_cast<Katana*>(itsWeapon))
                {
                    katana->addItsRange();
                    return;
                }
                break;

            case REVERSE_PROJECTILE:
                if (RangedWeapon* rw = dynamic_cast<RangedWeapon*>(itsWeapon))
                {
                    if (rw->getItsNbReverseProjectile() < 2)
                    {
                        rw->AddNbReverseProjectile();
                        return;
                    }
                }
                else if (dynamic_cast<Katana*>(itsWeapon))

                {
                    itsWeapon->addItsAttackSpeed();
                    return;
                }
                break;

            case MORE_DAMAGE:
                itsWeapon->AddBaseDamage(2);
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
                itsWeapon->setItsPUDamageMult(2);
            }
            else if(p->getItsType() == PEPPER)
            {
                itsWeapon->setItsPUAttackSpeedMult(10);
            }
            else if(p->getItsType() == BOOTS)
            {
                itsAvatar->setItsPUSpeedMult(2);
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
