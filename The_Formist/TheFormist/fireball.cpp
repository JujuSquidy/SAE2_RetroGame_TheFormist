#include "fireball.h"

int FireBall::getItsFireBallRange() const
{
    return itsFireBallRange;
}

std::pair<float,float> FireBall::getItsAreaSize() const
{
    return std::pair<float,float>(itsBaseAreaSize.first*itsAreaSizeMult, itsBaseAreaSize.second*itsAreaSizeMult);
}

FireBall::FireBall(int aBaseDamage, float anAttackSpeed, std::pair<int,int> aBaseAreaSize, QImage *aSprite)
    : RangedWeapon(aBaseDamage, anAttackSpeed, aSprite), itsBaseAreaSize(aBaseAreaSize) {}
