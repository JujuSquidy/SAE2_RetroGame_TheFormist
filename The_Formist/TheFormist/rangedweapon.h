#ifndef RANGEDWEAPON_H
#define RANGEDWEAPON_H

#include "weapon.h"
/**
 * @class RangedWeapon
 * @brief Represents a weapon that fires projectiles from a distance.
 *
 * Inherits from Weapon and adds properties specific to ranged combat, such as projectile speed and count.
 */
class RangedWeapon : public Weapon
{
private:
    /**
 * @brief Speed of the projectiles fired by the weapon.
 */
    float itsProjectileSpeed;

    /**
 * @brief Number of projectiles fired per attack.
 */
    int itsNbProjectile =1;

    /**
 * @brief Number of reverse projectiles fired by attack
 */
    int   itsNbReverseProjectile=0;

public:
    /**
 * @brief Constructs a RangedWeapon with specified damage, attack speed, and sprite.
 * @param aBaseDamage Base damage per projectile.
 * @param aAttackSpeed Rate of fire for the weapon.
 * @param aSprite Visual representation of the weapon.
 */
    RangedWeapon(int aBaseDamage, float aAttackSpeed, QImage *aSprite);

    int getItsNbProjectiles() const;

    void setItsNbProjectiles(int aNbProjectile);

    int getItsNbReverseProjectile() const;

    void setItsNbReverseProjectile(int aNbReverseProjectile);

};

#endif // RANGEDWEAPON_H
