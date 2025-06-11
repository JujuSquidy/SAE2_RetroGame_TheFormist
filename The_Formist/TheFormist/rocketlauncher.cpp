#include "rocketlauncher.h"

std::pair<float,float> RocketLauncher::getItsAreaSize() const
{
    return std::pair<float,float>(itsBaseAreaSize.first*itsAreaSizeMult, itsBaseAreaSize.second*itsAreaSizeMult);
}

RocketLauncher::RocketLauncher(int aBaseDamage, float aAttackSpeed, std::pair<int,int> aBaseArea, QImage *aSprite)
    : RangedWeapon(aBaseDamage, aAttackSpeed, aSprite), itsBaseAreaSize(aBaseArea)  {}
