#include "enemy.h"
#include "game.h"
#include <QRandomGenerator>


Enemy::Enemy(std::pair<int,int> aPosition, QImage aSprite, int aHP, EType aType, int bossTimer)
{
    aPosition = std::make_pair(1, 2);
    if (bossTimer >= 210000)
    {
        aType = BOSS;
        bossTimer = 0;
    }
    else
    {
        std::uniform_int_distribution<int> dist(1, 3);
        int value = dist(*QRandomGenerator::global());

        switch (value) {
        case 1: aType = TRIANGLE; break;
        case 2: aType = SQUARE; break;
        case 3: aType = CIRCLE; break;
        }
    }

    switch (aType)
    {
    case BOSS:
        itsMaxHP=50;
        aHP=itsMaxHP;
        itsGivenXP=50;
        itsStrength = 20;
        itsSpeed = 1;
        break;

    case TRIANGLE:
        itsMaxHP=10;
        aHP=itsMaxHP;
        itsGivenXP=1;
        itsStrength = 10;
        itsSpeed = 1;
        break;

    case SQUARE:
        itsMaxHP=15;
        aHP=itsMaxHP;
        itsGivenXP=2;
        itsStrength = 15;
        itsSpeed = 0.5;
        break;

    case CIRCLE:
        itsMaxHP=10;
        aHP=itsMaxHP;
        itsGivenXP=1;
        itsStrength = 5;
        itsSpeed = 1.5;
        break;

    }

}

void Enemy::shoot(std::pair<int, int> aTarget)
{

}

bool Enemy::isDead()
{
    if (itsHP <= 0)
    {

        return true;
    }
}

void Enemy::move(std::pair<int, int> targetPos)
{
    int dx = targetPos.first - itsPosition.first;
    int dy = targetPos.second - itsPosition.second;

    float distance = std::sqrt(dx * dx + dy * dy);
    if (distance == 0) return;

    float vx = itsSpeed * dx / distance;
    float vy = itsSpeed * dy / distance;

    itsPosition.first += vx;
    itsPosition.second += vy;

    itsEnemy.moveTo(itsPosition.first, itsPosition.second);
}
