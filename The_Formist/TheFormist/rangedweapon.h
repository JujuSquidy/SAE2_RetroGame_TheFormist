#ifndef RANGEDWEAPON_H
#define RANGEDWEAPON_H

#include "weapon.h"
#include <QElapsedTimer>

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
    float itsAvatarProjectilespeed;

    /**
 * @brief Number of projectiles fired per attack.
 */
    int itsNbProjectile = 2;

    /**
 * @brief Number of reverse projectiles fired by attack
 */
    int   itsNbReverseProjectile = 1;

    QElapsedTimer itsMultipleProjectileDelay;

    int nbProjectilesShooted = 0;

    int nbReverseProjectilesShooted = 0;


public:
    /**
 * @brief Constructs a RangedWeapon with specified damage, attack speed, and sprite.
 * @param aBaseDamage Base damage per projectile.
 * @param aAttackSpeed Rate of fire for the weapon.
 * @param aSprite Visual representation of the weapon.
 */
    RangedWeapon(int aBaseDamage, float aAttackSpeed, QImage *aSprite = nullptr);

    /**
 * @brief Gets the number of projectiles fired simultaneously.
 *
 * @return int The current number of projectiles.
 */
    int getItsNbProjectiles() const;

    /**
 * @brief Increases the number of projectiles fired by one.
 */
    void AddNbProjectile();

    /**
 * @brief Gets the number of reverse projectiles (projectiles fired in the opposite direction).
 *
 * @return int The current number of reverse projectiles.
 */
    int getItsNbReverseProjectile() const;

    /**
 * @brief Increases the number of reverse projectiles by one.
 */
    void AddNbReverseProjectile();


    QElapsedTimer getItsMultipleProjectileDelay() const;
    int getNbProjectilesShooted() const;
    void addNbProjectilesShooted();
    void addNbReverseProjectilesShooted();
    int getNbReverseProjectilesShooted() const;
    void attack();
};

#endif // RANGEDWEAPON_H
