#ifndef AREADAMAGE_H
#define AREADAMAGE_H

#include "projectile.h"
/**
 * @class AreaDamage
 * @brief Represents a projectile that causes damage over an area for a limited time.
 *
 * Inherits from Projectile and adds support for area-of-effect (AoE) damage with duration.
 */

class AreaDamage : public Projectile
{
private:
    /**
 * @brief Size of the damage area (width, height).
 */
    std::pair<int,int> itsArea;

    /**
 * @brief Duration (in seconds) the area damage effect lasts.
 */
    float itsDuration;
public:
    /**
 * @brief Constructs an AreaDamage projectile.
 * @param aArea Dimensions of the area affected by the damage.
 * @param aPosition Initial position of the area effect.
 * @param aDuration How long the area damage persists.
 * @param aDamage Damage applied to entities within the area.
 */
    AreaDamage(std::pair<int,int> aArea,std::pair<int,int> aPosition, float aDuration, int aDamage);
};

#endif // AREADAMAGE_H
