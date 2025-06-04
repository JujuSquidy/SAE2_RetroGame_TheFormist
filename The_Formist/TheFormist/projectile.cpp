#include "projectile.h"
#include <cmath>



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
}

void Projectile::move()
{
    itsPosition.first += (dirX * itsSpeed);
    itsPosition.second += (dirY * itsSpeed);
}

void Projectile::createArea()
{

}

std::pair<float, float> Projectile::getItsPosition() const
{
    return itsPosition;
}
