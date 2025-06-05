#include "rangedweapon.h"

RangedWeapon::RangedWeapon(int aBaseDamage, float aAttackSpeed, QImage *aSprite) : Weapon(aBaseDamage, aAttackSpeed, aSprite)
{

}


int RangedWeapon::getItsNbProjectiles() const
{
    return itsNbProjectile;
}

void RangedWeapon::setItsNbProjectiles(int aNbProjectile)
{
    itsNbProjectile+=aNbProjectile;
}

int RangedWeapon::getItsNbReverseProjectile() const
{
    return itsNbReverseProjectile;
}

void RangedWeapon::setItsNbReverseProjectile(int aNbReverseProjectile)
{
    itsNbReverseProjectile+=aNbReverseProjectile;
}
