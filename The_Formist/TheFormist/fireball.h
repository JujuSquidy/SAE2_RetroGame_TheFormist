#ifndef FIREBALL_H
#define FIREBALL_H

#include "rangedweapon.h"

/**
 * @class FireBall
 * @brief Represents a ranged weapon that creates an area-of-effect (AoE) fireball attack.
 *
 * Inherits from RangedWeapon and adds properties for area size and range.
 */
class FireBall : public RangedWeapon
{
private:
/**
 * @brief Base size of the area affected by the fireball (width, height).
 */
    std::pair<int,int> itsBaseAreaSize;

/**
 * @brief Multiplier applied to the base area size for scaling.
 */
    float itsAreaSizeMult = 1;

/**
 * @brief The maximum range the fireball can travel.
 */
    int itsFireBallRange = 350;
public:

/**
 * @brief Constructs a FireBall weapon.
 * @param aBaseDamage The base damage dealt by the fireball.
 * @param anAttackSpeed The speed at which the fireball can be fired.
 * @param aProjSize The size of the fireball projectile.
 * @param aBaseAreaSize The base area affected by the fireball's explosion.
 */
    FireBall(int aBaseDamage, float anAttackSpeed, std::pair<int, int> aProjSize, std::pair<int, int> aBaseAreaSize);

/**
 * @brief Gets the effective area size of the fireball explosion.
 * @return A pair (width, height) representing the scaled AoE size.
 */
    std::pair<float,float> getItsAreaSize() const;

/**
 * @brief Gets the range the fireball can travel.
 * @return The fireball's range in pixels.
 */
    int getItsFireBallRange() const;
};

#endif // FIREBALL_H
