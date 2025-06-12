#ifndef FIREBALL_H
#define FIREBALL_H

#include "rangedweapon.h"

class FireBall : public RangedWeapon
{
private:
    std::pair<int,int> itsBaseAreaSize;
    float itsAreaSizeMult = 1;
    int itsFireBallRange = 350;
public:
    FireBall(int aBaseDamage, float aAttackSpeed, std::pair<int, int> aProjSize, std::pair<int, int> aBaseAreaSize);
    std::pair<float,float> getItsAreaSize() const;
    int getItsFireBallRange() const;
};

#endif // FIREBALL_H
