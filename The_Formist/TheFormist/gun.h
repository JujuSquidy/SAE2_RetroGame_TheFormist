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
 * @param aAttackSpeed Time interval between shots.
 * @param aSprite Visual representation of the gun.
 */
    Gun(int aBaseDamage, float aAttackSpeed, QImage *aSprite = nullptr);

};

#endif // GUN_H
