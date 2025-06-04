#ifndef GAME_H
#define GAME_H

#include <QTimer>
#include "avatar.h"
#include "enemy.h"
#include "powerup.h"
#include "projectile.h"
class Game
{
private :
    QTimer itsTimer;
    QTimer itsBossTimer; // à chaque construction d'ennemi dans la game loop on devra passer le timer en paramètre du constructeur d'enemy (dernière valeur). ça permet de crée le boss à intervales régulières
    std::pair<int,int> itsBorder;
    long int itsScore;
    std::vector<Projectile*> itsProjectiles;
    Avatar* itsAvatar;
    std::vector<Enemy*> itsEnemies;
    PowerUp itsPowerUp;
    Game *itsgame;

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
