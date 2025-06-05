#include "rangedweapon.h"

RangedWeapon::RangedWeapon(int aBaseDamage, float aAttackSpeed, QImage *aSprite) : Weapon(aBaseDamage, aAttackSpeed, aSprite)
{

}


int RangedWeapon::getItsNbProjectiles() const
{
    return itsNbProjectile;
}

void RangedWeapon::AddNbProjectile()
{
    itsNbProjectile++;
}

int RangedWeapon::getItsNbReverseProjectile() const
{
    return itsNbReverseProjectile;
}

void RangedWeapon::AddNbReverseProjectile()
{
    itsNbReverseProjectile++;
}
