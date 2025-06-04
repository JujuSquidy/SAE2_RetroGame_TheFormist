#include "enemy.h"
#include <QRandomGenerator>
#include <random>

Enemy::Enemy(std::pair<float,float> aPosition, QImage* aSprite, int bossTimer)
{
    if (bossTimer >= 210000)
    {
        itsType = BOSS;
        bossTimer = 0;
    }
    else
    {
        std::uniform_int_distribution<int> dist(1, 3);
        int typeValue = dist(*QRandomGenerator::global());

        switch (typeValue) {
        case 1: itsType = TRIANGLE; break;
        case 2: itsType = SQUARE; break;
        case 3: itsType = CIRCLE; break;
        }
    }

    switch (itsType)
    {
    case BOSS:
        itsMaxHP=50;
        itsHP=itsMaxHP;
        itsGivenXP=50;
        itsStrength = 20;
        itsSpeed = 1;
        break;

    case TRIANGLE:
        itsMaxHP=10;
        itsHP=itsMaxHP;
        itsGivenXP=1;
        itsStrength = 10;
        itsSpeed = 1;
        break;

    case SQUARE:
        itsMaxHP=15;
        itsHP=itsMaxHP;
        itsGivenXP=2;
        itsStrength = 15;
        itsSpeed = 0.5;
        break;

    case CIRCLE:
        itsMaxHP=10;
        itsHP=itsMaxHP;
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
    else
        return false;
}

void Enemy::move(std::pair<int, int> aTarget)
{
    float dx = aTarget.first - itsPosition.first;
    float dy = aTarget.second - itsPosition.second;

    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance != 0)
    {
        dirX = dx / distance;
        dirY = dy / distance;
    }

    else
    {
        dirX = 0;
        dirY = 0;
    }

    itsPosition.first += (dirX * itsSpeed);
    itsPosition.second += (dirY * itsSpeed);

}

std::pair<float, float> Enemy::getItsPosition() const
{
    return itsPosition;
}


EType Enemy::getType() const
{
    return itsType;
}
