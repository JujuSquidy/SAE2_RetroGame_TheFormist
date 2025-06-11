#include "areadamage.h"

void AreaDamage::addTick()
{
    itsNbOfTicks++;
}

void AreaDamage::resetBurn()
{
    isBurning = false;
    itsTimer->start(200);
}

void AreaDamage::burn()
{
    isBurning = true;
}

bool AreaDamage::getIsBurning() const
{
    return isBurning;
}

AreaDamage::AreaDamage(std::pair<int, int> anArea, std::pair<int, int> aPosition, int aNbOfTicks, int aDamage)
    : Projectile(std::pair(0,0), aPosition, anArea, 0, aDamage), itsFinalTick(aNbOfTicks)
{
    connect(itsTimer,SIGNAL(timeout()), this, SLOT(burn()));
}
