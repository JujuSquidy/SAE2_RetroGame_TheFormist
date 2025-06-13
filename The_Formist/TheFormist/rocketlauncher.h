#ifndef ROCKETLAUNCHER_H
#define ROCKETLAUNCHER_H

#include "rangedweapon.h"

    /**
 * @class RocketLauncher
 * @brief Specialized ranged weapon that fires explosive rockets.
 *
 * Inherits from RangedWeapon and adds functionality for an area damage effect,
 * defined by a base explosion size and a size multiplier.
 */
class RocketLauncher : public RangedWeapon
{
private:
    /**
 * @brief Base size of the explosion area caused by the rocket.
 */
    std::pair<int,int> itsBaseAreaSize;

    /**
 * @brief Multiplier applied to the base explosion area size.
 */
    float itsAreaSizeMult = 1;
public:
    /**
 * @brief Constructs a RocketLauncher with damage, attack speed, projectile size, and base area size.
 * @param aBaseDamage Base damage of the rocket.
 * @param anAttackSpeed Attack speed of the weapon.
 * @param aProjSize Size of the rocket projectile.
 * @param aBaseAreaSize Base explosion area size.
 */
    RocketLauncher(int aBaseDamage, float anAttackSpeed, std::pair<int,int> aProjSize, std::pair<int,int> aBaseAreaSize);

    /**
 * @brief Gets the current explosion area size after applying the multiplier.
 * @return std::pair<float,float> The calculated area size.
 */
    std::pair<float, float> getItsAreaSize() const;
};

#endif // ROCKETLAUNCHER_H
