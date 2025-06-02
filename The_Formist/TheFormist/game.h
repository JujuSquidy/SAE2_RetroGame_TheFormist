#ifndef GAME_H
#define GAME_H

#include "QTimer"
#include "avatar.h"
#include "enemy.h"
#include "powerup.h"
#include "projectile.h"
class Game
{
private :
    QTimer itsTimer;
    std::pair<int,int> itsBorder;
    long int itsScore;
    std::vector<Projectile*> itsProjectiles;
    Avatar* itsAvatar;
    std::vector<Enemy*> itsEnemies;
    PowerUp itsPowerUp;

public:
    Game();
    ~Game();
    void PowerUp();
    void Collision();
    void GameOver();

public slots:
    void GameLoop();
};

#endif // GAME_H
