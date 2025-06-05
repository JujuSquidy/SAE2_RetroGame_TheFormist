#include "projectile.h"

#include <cmath>


QRectF Projectile::getItsRectF() const
{
    return itsRectF;
}

int Projectile::getItsDamage() const
{
    return itsDamage;
}

Projectile::Projectile(std::pair<float, float> aTarget, std::pair<float, float> aPosition, std::pair<int,int> aSize, int aSpeed, int aDamage)
    : itsPosition(aPosition), itsSize(aSize), itsSpeed(aSpeed), itsDamage(aDamage)
{
    float dx = aTarget.first - aPosition.first;
    float dy = aTarget.second - aPosition.second;

    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance != 0) {
        dirX = dx / distance;
        dirY = dy / distance;
    } else {
        dirX = 0;
        dirY = 0;
    }

    itsRectF = QRectF(itsPosition.first, itsPosition.second, aSize.first, aSize.second);
}

void Projectile::move()
{
    itsPosition.first += (dirX * itsSpeed);
    itsPosition.second += (dirY * itsSpeed);
    itsRectF.moveTo(itsPosition.first,itsPosition.second);
}

void Projectile::createArea()
{

}

std::pair<float, float> Projectile::getItsPosition() const
{
    return itsPosition;
}
