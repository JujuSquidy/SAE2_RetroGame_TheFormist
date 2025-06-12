#ifndef AREADAMAGE_H
#define AREADAMAGE_H

#include <QTimer>
#include "projectile.h"
/**
 * @class AreaDamage
 * @brief Represents a projectile that causes damage over an area for a limited time.
 *
 * Inherits from Projectile and adds support for area-of-effect (AoE) damage with duration.
 */

class AreaDamage : public QObject, public Projectile
{
    Q_OBJECT
private:
    /**
 * @brief Size of the damage area (width, height).
 */

    int itsNbOfTicks = 0;

    QTimer * itsTimer;

    bool isBurning = 1;

    /**
 * @brief Number of ticks before the area disappear.
 */
    int itsFinalTick;
public:
    /**
 * @brief Constructs an AreaDamage.
 * @param aArea Dimensions of the area affected by the damage.
 * @param aPosition Initial position of the area effect.
 * @param aDuration How long the area damage persists.
 * @param aDamage Damage applied to entities within the area.
 */
    AreaDamage(std::pair<int,int> anArea, std::pair<int,int> aPosition, int aNbOfTicks, int aDamage);
    std::pair<int, int> getItsArea() const;
    void addTick();
    void resetBurn();
    bool getIsBurning() const;
    bool expired();
public slots:
    void burn();
};

#endif // AREADAMAGE_H
