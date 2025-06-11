#include "rangedweapon.h"

QElapsedTimer RangedWeapon::getItsMultipleProjectileDelay() const
{
    return itsMultipleProjectileDelay;
}

int RangedWeapon::getNbProjectilesShooted() const
{
    return nbProjectilesShooted;
}

void RangedWeapon::addNbProjectilesShooted()
{
    nbProjectilesShooted++;
}

void RangedWeapon::addNbReverseProjectilesShooted()
{
    nbReverseProjectilesShooted++;
}

int RangedWeapon::getNbReverseProjectilesShooted() const
{
    return nbReverseProjectilesShooted;
}

float RangedWeapon::getItsProjectileSpeed() const
{
    return itsProjectileSpeed;
}

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

void RangedWeapon::attack()
{
    setIsShooting(true);
    nbProjectilesShooted = 0;
    nbReverseProjectilesShooted = 0;
    itsMultipleProjectileDelay.start();
    itsTimer->start(500 / (itsAttackSpeedMult * itsPUAttackSpeedMult * itsBaseAttackSpeed));
}
