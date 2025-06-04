#include "areadamage.h"

AreaDamage::AreaDamage(std::pair<int, int> anArea, std::pair<int, int> aPosition, float aDuration, int aDamage)
    : Projectile(std::pair(0,0), aPosition, anArea, 0, aDamage), itsArea(anArea), itsDuration(aDuration) {}
