#ifndef GAME_H
#define GAME_H

#include <QTimer>
#include "avatar.h"
#include "enemy.h"
#include "powerup.h"
#include "projectile.h"
#include "qelapsedtimer.h"
#include "weapon.h"
class Game
{
private :
    QTimer itsTimer;
    QElapsedTimer fireTimer;
    std::pair<int,int> itsBorder;
    long int itsScore;
    std::vector<Projectile*> itsProjectiles;
    Avatar* itsAvatar;
    Weapon* itsWeapon;
    std::vector<Enemy*> itsEnemies;
    PowerUp itsPowerUp;
    std::pair<int,int> mouseTarget;


public:
    Game();
    ~Game();
    void PowerUp();
    void Collision();
    void GameOver();
    void updateMouseTarget(int x, int y);

public slots:
    void GameLoop();
};

#endif // GAME_H
