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
    float itsProjectileSpeed;

    /**
 * @brief Number of projectiles fired per attack.
 */
    int itsNbProjectile = 1;

    /**
 * @brief Number of reverse projectiles fired by attack
 */
    int itsNbReverseProjectile = 0;

    /**
 * @brief Timer managing delay between multiple projectile shots.
 */
    QElapsedTimer itsMultipleProjectileDelay;

    /**
 * @brief Counter for the number of projectiles shot.
 */
    int nbProjectilesShooted = 0;

    /**
 * @brief Counter for the number of reverse projectiles shot.
 */
    int nbReverseProjectilesShooted = 0;

    /**
 * @brief Size (width, height) of each projectile.
 */
    std::pair<int,int> itsProjSize;

public:
    /**
 * @brief Constructs a RangedWeapon with specified damage, attack speed, and sprite.
 * @param aBaseDamage Base damage per projectile.
 * @param anAttackSpeed Rate of fire for the weapon.
 * @param aProjSize Specifie the projectile's size.
 */
    RangedWeapon(int aBaseDamage, float anAttackSpeed, std::pair<int,int> aProjSize);

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

    /**
 * @brief Returns the timer managing delay between multiple projectile shots.
 * @return QElapsedTimer The timer object.
 */
    QElapsedTimer getItsMultipleProjectileDelay() const;

    /**
 * @brief Gets the count of projectiles that have been shot.
 * @return int Number of projectiles shot.
 */
    int getNbProjectilesShooted() const;

    /**
 * @brief Increments the count of projectiles shot by one.
 */
    void addNbProjectilesShooted();

    /**
 * @brief Increments the count of reverse projectiles shot by one.
 */
    void addNbReverseProjectilesShooted();

    /**
 * @brief Gets the count of reverse projectiles that have been shot.
 * @return int Number of reverse projectiles shot.
 */
    int getNbReverseProjectilesShooted() const;

    /**
 * @brief Executes an attack action with the weapon.
 */
    void attack();

    /**
 * @brief Gets the speed of the projectiles fired by the weapon.
 * @return float Projectile speed.
 */
    float getItsProjectileSpeed() const;

    /**
 * @brief Gets the size (width, height) of the projectiles.
 * @return std::pair<int,int> Projectile size.
 */
    std::pair<int, int> getItsProjSize() const;
};

#endif // RANGEDWEAPON_H
