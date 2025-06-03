#include "projectile.h"

Projectile::Projectile(std::pair<int, int> aTarget, std::pair<int, int> aPosition, std::pair<int,int> aSize, int aSpeed, int aDamage)
    : itsTarget(aTarget), itsPosition(aPosition), itsSize(aSize), itsSpeed(aSpeed), itsDamage(aDamage)
{

}

void Projectile::move()
{

}

void Projectile::createArea()
{

}
