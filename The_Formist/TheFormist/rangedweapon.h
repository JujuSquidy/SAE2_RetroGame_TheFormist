#ifndef RANGEDWEAPON_H
#define RANGEDWEAPON_H

#include "weapon.h"
class RangedWeapon : public Weapon
{
private:
    float itsProjectileSpeed;
    int itsNbProjectile;
public:
    RangedWeapon(int aBaseDamage, float aAttackSpeed, QImage aSprite);
};

#endif // RANGEDWEAPON_H
