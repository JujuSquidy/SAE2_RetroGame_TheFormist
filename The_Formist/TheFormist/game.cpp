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
    // Set the size of the game world and the visible game window.

    itsBorder = std::pair(4000,2000);
    gameWindowSize = {960, 540};

    // Create the player's avatar, positioned in the center of the game world
    itsAvatar = new Avatar(std::pair(itsBorder.first/2,itsBorder.second/2));

    // Initialize the player's weapon based on the selected type
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

    // Create and set up timers for the game
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

    // Create and configure the background music player
    backgroundMusicPlayer = new QMediaPlayer(this);
    backgroundMusicPlayer->setAudioOutput(audioOutput);

    backgroundMusicPlayer->setSource(QUrl("qrc:/Music/Game.mp3"));
    backgroundMusicPlayer->setLoops(QMediaPlayer::Infinite);  // <--- boucle infinie

    audioOutput->setVolume(1); // volume entre 0.0 et 1.0
    backgroundMusicPlayer->play();
}

Game::~Game()
{
    // Delete all avatar projectiles
    for (Projectile* p : itsAvatarProjectiles) {
        delete p;
    }
    itsAvatarProjectiles.clear();

    // Delete all enemy projectiles
    for (Projectile* p : itsEnemyProjectiles) {
        delete p;
    }
    itsEnemyProjectiles.clear();

    // Delete all enemies
    for (Enemy* e : itsEnemies) {
        delete e;
    }
    itsEnemies.clear();

    // Delete all power-ups
    for (PowerUp* p : itsPowerUp)
        delete p;
    itsPowerUp.clear();

    // Delete the avatar
    delete itsAvatar;
    itsAvatar = nullptr;

    // Delete the player's weapon
    delete itsWeapon;
    itsWeapon = nullptr;

    // Stop and delete the main game timer
    itsTimer->stop();
    delete itsTimer;
    itsTimer = nullptr;

    // Stop and delete the enemy spawn timer
    itsEnemyTimer->stop();
    delete itsEnemyTimer;
    itsEnemyTimer = nullptr;

    // Delete the in-game timer
    delete itsInGameTimer;
    itsInGameTimer = nullptr;

    // Delete the power-up spawn timer
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

        // Remove projectile if it leaves game bounds
        if(proj->getItsPosition().first < 0 || proj->getItsPosition().first > 4000 || proj->getItsPosition().second < 0 || proj->getItsPosition().second > 2000)
        {
            delete proj;
            itsAvatarProjectiles.erase(avProjIt);
        }
        else
        {
            bool hit = false;

            // Check collision with enemies
            for (std::vector<Enemy*>::iterator enemyIt = itsEnemies.begin(); enemyIt != itsEnemies.end(); )
            {
                Enemy* e = *enemyIt;

                if (proj->getItsRectF().intersects(e->getItsRectF()))
                {
                    e->takeDamage(itsWeapon->getItsDamage());
                    hit = true;
                    if (e->isDead())
                    {
                        // Grant XP and score based on enemy type
                        itsAvatar->addXP(e->getItsGivenXP());
                        switch (e->getType())
                        {
                            case TRIANGLE:
                                AddScore(2*itsScoreMult);
                                break;

                            case CIRCLE:
                                AddScore(1*itsScoreMult);
                                break;

                            case SQUARE:
                                AddScore(3*itsScoreMult);
                                break;

                            case BOSS:
                                AddScore(50*itsScoreMult);
                                break;
                        }
                        delete e; // Remove dead enemy
                        enemyIt = itsEnemies.erase(enemyIt);
                    }
                    else
                        ++enemyIt;

                    break; // One projectile can hit only one enemy
                }
                else
                    ++enemyIt;
            }

            // Handle projectile impact or range expiration
            if (hit || (typeid(*itsWeapon)==typeid(FireBall) && proj->getItsDistanceTraveled() >= dynamic_cast<FireBall*>(itsWeapon)->getItsFireBallRange()))
            {
                // RocketLauncher explosion effect
                if(typeid(*itsWeapon) == typeid(RocketLauncher))
                {
                    RocketLauncher * RL = dynamic_cast<RocketLauncher*>(itsWeapon);
                        AreaDamage * AD = new AreaDamage(
                                                    RL->getItsAreaSize(),                                               // AoE size
                                                    {proj->getItsRectF().center().x()-(RL->getItsAreaSize().first/2),   // x position of QRect
                                                     proj->getItsRectF().center().y()-(RL->getItsAreaSize().second/2)}, // y position of QRect
                                                    1,                                                                  // Damage dealt before AoE's disaparence
                                                    RL->getItsDamage()                                                  // Damage dealt by AoE
                                                    );
                    itsAreaDamages.push_back(AD);
                }

                // FireBall explosion effect
                else if(typeid(*itsWeapon) == typeid(FireBall))
                {
                    FireBall * FB = dynamic_cast<FireBall*>(itsWeapon);
                        AreaDamage * AD = new AreaDamage(
                                                    FB->getItsAreaSize(),                                               // AoE size
                                                    {proj->getItsRectF().center().x()-(FB->getItsAreaSize().first/2),   // x position of QRect
                                                     proj->getItsRectF().center().y()-(FB->getItsAreaSize().second/2)}, // y position of QRect
                                                    5,                                                                  // Damage dealt before AoE's disaparence
                                                    FB->getItsDamage()                                                   // Damage dealt by AoE
                                                    );
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
        if(AD->getIsBurning())  // Active area
        {
            if(AD->expired())
            {
                delete AD;
                ADit = itsAreaDamages.erase(ADit);
            }
            else
            {
                // Check damage to all enemies within area
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
                                AddScore(2*itsScoreMult);
                                break;

                            case CIRCLE:
                                AddScore(1*itsScoreMult);
                                break;

                            case SQUARE:
                                AddScore(3*itsScoreMult);
                                break;

                            case BOSS:
                                AddScore(50*itsScoreMult);
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
            AD->addTick(); // Increment internal counter
            AD->resetBurn(); // Prepare for next burn tick
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
            // Get katana hitbox from player to mouse target
            QRectF hitbox = katana->katanaAreaDamage({itsAvatar->getItsQRect()->center().x(),itsAvatar->getItsQRect()->center().y()}, mouseTarget);

            // Deal damage to all enemies inside the hitbox
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
                        AddScore(2*itsScoreMult);
                        break;
                    case CIRCLE:
                        AddScore(1*itsScoreMult);
                        break;
                    case SQUARE:
                        AddScore(3*itsScoreMult);
                        break;
                    case BOSS:
                        AddScore(50*itsScoreMult);
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
        // Remove if outside bounds
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
                    itsAvatar->desactivateShield();  // Shield absorbs the hit
                }
                else
                {
                    itsAvatar->takeDamage(proj->getItsDamage());  // Avatar takes damage
                }

                delete proj;
                enProjIt = itsEnemyProjectiles.erase(enProjIt);
            }
            else
                ++enProjIt;
        }
    }

    //Colision between enemies and avatar
    for (std::vector<Enemy*>::iterator enemyIt = itsEnemies.begin(); enemyIt != itsEnemies.end(); ++enemyIt)
    {
        Enemy* e = *enemyIt;

        if (e->getItsRectF().intersects(*itsAvatar->getItsQRect()) && e->getType() != TRIANGLE)
        {
            itsAvatar->takeDamage(e->getItsStrength()); // Apply contact damage
        }
    }

    for (std::vector<PowerUp*>::iterator it = itsPowerUp.begin(); it != itsPowerUp.end();  )
    {
        PowerUp* p = *it;

        if (p->getItsRectF().intersects(*itsAvatar->getItsQRect()))
        {
            if(p->getItsType() == SHIELD)
            {
                itsAvatar->activateShield(); // Enable shield
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
                itsAvatar->addHP(20); // Restore health
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
    //Stop all timers and emit a signal
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
            // Fire projectiles at intervals based on weapon's attack speed
            if (rw->getItsMultipleProjectileDelay().elapsed() > itsWeapon->getItsAttackSpeed()/3)
            {
                // Get the avatar's center position
                std::pair<int,int> avatarCenter = {itsAvatar->getItsQRect()->center().x(),itsAvatar->getItsQRect()->center().y()};

                if (mouseTarget != avatarCenter)
                {
                    // Forward projectiles
                    if (rw->getNbProjectilesShooted() < rw->getItsNbProjectiles())
                    {
                        std::pair<int,int> target = mouseTarget;
                        Projectile* p = new Projectile(target, {avatarCenter.first, avatarCenter.second}, rw->getItsProjSize(), 5, 5);
                        itsAvatarProjectiles.push_back(p);
                        rw->addNbProjectilesShooted();
                    }
                    // Reverse projectiles
                    if (rw->getNbReverseProjectilesShooted() < rw->getItsNbReverseProjectile())
                    {
                        int dx = mouseTarget.first - avatarCenter.first;
                        int dy = mouseTarget.second - avatarCenter.second;
                        std::pair<int,int> reversedTarget = {avatarCenter.first - dx, avatarCenter.second - dy};
                        Projectile* p = new Projectile(reversedTarget, {avatarCenter.first, avatarCenter.second}, rw->getItsProjSize(), 5, 5);
                        itsAvatarProjectiles.push_back(p);
                        rw->addNbReverseProjectilesShooted();
                    }
                    // Restart the delay timer for the next projectile
                    rw->getItsMultipleProjectileDelay().start();
                }
                // Stop shooting if all projectiles (forward + reverse) are fired
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

        // Move the enemy toward the avatar
        enemy->act(std::pair<float, float>(avatarRect->center().x(), avatarRect->center().y()));

        // Prevent enemies from overlapping the avatar
        if (enemy->getItsRectF().intersects(*avatarRect))
        {
            enemy->setItsPosition(oldPos);
        }

        // Enemy shoots at the avatar
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
            enemy->setIsShooting(false); // Reset shooting state
        }
    }

    // Update projectiles position
    for (Projectile * aProj : itsAvatarProjectiles)
        aProj->move();

    for (Projectile * eProj : itsEnemyProjectiles)
        eProj->move();

    // Move the avatar within the bounds
    itsAvatar->move(itsBorder);

    // HAndles collisions
    Collision();

    //Reset shooting state for melee weapons like the Katana
    if (dynamic_cast<Katana*>(itsWeapon))
    {
        if (itsWeapon->getIsShooting())
        {
            itsWeapon->setIsShooting(false);
        }
    }

    // Check if avatar died
    if (itsAvatar->getItsHP() == 0)
    {
        GameOver();
        return;
    }
    //Handle avatar leveling up
    if (itsAvatar->getItsXP() >= itsAvatar->getItsMaxXP())
    {
        int temp = itsAvatar->getItsXP() - itsAvatar->getItsMaxXP();
        itsAvatar->levelUp(); // Increase level
        itsAvatar->addMaxXP(2); // Increase XP needed for next level
        itsAvatar->addMaxHP(5);
        itsAvatar->addHP(5);
        itsWeapon->AddBaseDamage(1); 
        itsAvatar->setItsXP(temp); // Set leftover XP
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
            itsScoreMult+= 1;
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
                itsWeapon->AddBaseDamage(3);
                return;

            case MORE_HP:
                itsAvatar->addMaxHP(10);
                itsAvatar->addHP(10);
                return;
        }
    }
}

// Handle active and expired power-ups
void Game::updateTemporaryBoosts()
{
    for (std::vector<PowerUp*>::iterator it = itsPowerUp.begin(); it != itsPowerUp.end();)
    {
        PowerUp* p = *it;
        if (p->getIsFinished() == false && p->getIsPicked() == true) // Check if the boost is active
        {
            // Apply power-up effects depending on its type
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
            it++; // Move to the next power-up
        }
        // If the power-up effect has ended
        else if (p->getIsFinished() == true)
        {
            // Reset any multipliers previously applied
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
            it = itsPowerUp.erase(it);
        }
        else
        {
            // If not picked or not expired, just move to the next
            it++;
        }
    }
}
