#ifndef GUN_H
#define GUN_H

#include "rangedweapon.h"
/**
 * @class Gun
 * @brief A specific type of ranged weapon used by the player or enemies.
 *
 * Inherits from RangedWeapon and represents a gun with specific damage and attack speed values.
 */
class Gun : public RangedWeapon
{
public:
    /**
 * @brief Constructs a Gun with the given base damage, attack speed, and sprite.
 * @param aBaseDamage Base damage dealt by the gun.
 * @param anAttackSpeed Time interval between shots.
 * @param aProjSize Specifie the projectile's size.
 */
    Gun(int aBaseDamage, float anAttackSpeed, std::pair<int,int> aProjSize);
};

#endif // GUN_H
