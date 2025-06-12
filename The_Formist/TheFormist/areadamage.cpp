#include "areadamage.h"

void AreaDamage::addTick()
{
    itsNbOfTicks++;
}

void AreaDamage::resetBurn()
{
    isBurning = false;
    itsTimer->start(400);
}

void AreaDamage::burn()
{
    isBurning = true;
}

bool AreaDamage::getIsBurning() const
{
    return isBurning;
}

bool AreaDamage::expired()
{
    return itsNbOfTicks == itsFinalTick;
}

AreaDamage::AreaDamage(std::pair<int, int> anArea, std::pair<int, int> aPosition, int aNbOfTicks, int aDamage)
    : Projectile(aPosition, aPosition, anArea, 0, aDamage), itsFinalTick(aNbOfTicks)
{
    itsTimer = new QTimer(this);
    connect(itsTimer, SIGNAL(timeout()), this, SLOT(burn()));
}
