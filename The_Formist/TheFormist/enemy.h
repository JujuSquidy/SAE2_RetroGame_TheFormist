#ifndef ENEMY_H
#define ENEMY_H

#include <QImage>
#include <utility>

enum EType{
    CIRCLE,
    TRIANGLE,
    SQUARE,
    BOSS
};

class Enemy
{
private:
    std::pair<int,int> itsPosition;
    float itsSpeed;
    int itsStrength;
    int itsHP;
    int itsMaxHP;
    int itsGivenXP;
    QImage itsSprite;
    QRect itsEnemy;
public:
    Enemy(std::pair<int,int> aPosition, QImage aSprite, int aHP, EType aType, int bossTimer); //bossTimer correspond au chrono du boss, il devra être passé en paramètre à chaque construction d'un ennemi dans la game loop
    void shoot(std::pair<int,int> aTarget);
    bool isDead();
    void move(std::pair<int, int> aTarget);
};

#endif // ENEMY_H
