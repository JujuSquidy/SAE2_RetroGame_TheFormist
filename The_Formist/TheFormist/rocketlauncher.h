#ifndef ROCKETLAUNCHER_H
#define ROCKETLAUNCHER_H

#include "rangedweapon.h"

class RocketLauncher : public RangedWeapon
{
private:
    std::pair<int,int> itsBaseAreaSize;
    float itsAreaSizeMult = 1;
public:
    RocketLauncher(int aBaseDamage, float aAttackSpeed, std::pair<int,int> aBaseArea, QImage *aSprite = nullptr);
    std::pair<float, float> getItsAreaSize() const;
};

#endif // ROCKETLAUNCHER_H
