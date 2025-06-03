#ifndef GUN_H
#define GUN_H

#include "rangedweapon.h"

class Gun : public RangedWeapon
{
public:
    Gun(int aBaseDamage, float aAttackSpeed, QImage aSprite);
};

#endif // GUN_H
