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
public:
    Enemy(std::pair<int,int> aPosition, QImage aSprite, int aHP, EType aType);
    void shoot(std::pair<int,int> aTarget);
    bool isDead();
    void move();;
};

#endif // ENEMY_H
