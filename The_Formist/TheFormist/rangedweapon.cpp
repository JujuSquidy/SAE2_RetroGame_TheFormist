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

std::pair<int, int> RangedWeapon::getItsProjSize() const
{
    return itsProjSize;
}

RangedWeapon::RangedWeapon(int aBaseDamage, float aAttackSpeed, std::pair<int,int> aProjSize) : Weapon(aBaseDamage, aAttackSpeed), itsProjSize(aProjSize)
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
    itsTimer->start(1000 / (itsAttackSpeedMult * itsPUAttackSpeedMult * itsBaseAttackSpeed));
}
