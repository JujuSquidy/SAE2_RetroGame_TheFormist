#include "areadamage.h"

AreaDamage::AreaDamage(std::pair<int, int> aArea, std::pair<int, int> aPosition, float aDuration, int aDamage)
    : Projectile(std::pair(0,0), aPosition, aArea, 0, aDamage), itsArea(aArea), itsDuration(aDuration) {}
