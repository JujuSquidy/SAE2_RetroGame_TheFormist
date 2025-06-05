#include "enemy.h"
#include <QRandomGenerator>
#include <random>

QRectF Enemy::getItsRectF() const
{
    return itsRectF;
}

int Enemy::getItsGivenXP() const
{
    return itsGivenXP;
}

Enemy::Enemy(std::pair<float,float> aPosition, QImage* aSprite, int bossTimer)
{
    itsPosition = aPosition;

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
        itsRectF = QRectF(itsPosition.first, itsPosition.second, 50.0, 50.0);

        break;

    case TRIANGLE:
        itsMaxHP=10;
        itsHP=itsMaxHP;
        itsGivenXP=1;
        itsStrength = 10;
        itsSpeed = 1;

        itsRectF = QRectF(itsPosition.first, itsPosition.second, 30.0, 30.0);

        break;

    case SQUARE:
        itsMaxHP=15;
        itsHP=itsMaxHP;
        itsGivenXP=2;
        itsStrength = 15;
        itsSpeed = 0.5;
        itsRectF = QRectF(itsPosition.first, itsPosition.second, 30.0, 30.0);

        break;

    case CIRCLE:
        itsMaxHP=10;
        itsHP=itsMaxHP;
        itsGivenXP=1;
        itsStrength = 5;
        itsSpeed = 1.5;
        itsRectF = QRectF(itsPosition.first, itsPosition.second, 30.0, 30.0);

        break;

    }

}

void Enemy::shoot(std::pair<int, int> aTarget)
{

}

bool Enemy::isDead()
{
    return itsHP <= 0;
}

void Enemy::move(std::pair<float, float> aTarget)
{
    float dx = aTarget.first - itsRectF.width()/2 - itsPosition.first;
    float dy = aTarget.second - itsRectF.height()/2 - itsPosition.second;

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
    itsRectF.moveTo(itsPosition.first, itsPosition.second);
}

std::pair<float, float> Enemy::getItsPosition() const
{
    return itsPosition;
}


EType Enemy::getType() const
{
    return itsType;
}

void Enemy::takeDamage(int amount)
{
    itsHP -= amount;
    if (itsHP < 0)
        itsHP = 0;
}

int Enemy::getHP() const
{
    return itsHP;
}
