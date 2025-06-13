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
 * @brief Number of ticks that have elapsed since the effect started.
 */
    int itsNbOfTicks = 0;

/**
 * @brief Timer used to manage the update ticks for the area effect.
 */
    QTimer * itsTimer;

/**
 * @brief Indicates whether the area is currently active (burning).
 */
    bool isBurning = 1;

    /**
 * @brief Number of ticks before the area disappear.
 */
    int itsFinalTick;
public:
    /**
 * @brief Constructs an AreaDamage.
 * @param anArea Dimensions of the area affected by the damage.
 * @param aPosition Initial position of the area effect.
 * @param aNbOfTicks How long the area damage persists.
 * @param aDamage Damage applied to entities within the area.
 */
    AreaDamage(std::pair<int,int> anArea, std::pair<int,int> aPosition, int aNbOfTicks, int aDamage);

/**
 * @brief Gets the dimensions of the affected area.
 * @return A pair representing the width and height of the area.
 */
    std::pair<int, int> getItsArea() const;

/**
 * @brief Increments the tick counter for the area effect.
 */
    void addTick();

/**
 * @brief Resets the burning state of the area effect.
 */
    void resetBurn();

/**
 * @brief Checks whether the area is currently burning.
 * @return True if burning, otherwise false.
 */
    bool getIsBurning() const;

/**
 * @brief Checks whether the area effect has expired.
 * @return True if the number of ticks reached itsFinalTick, otherwise false.
 */
    bool expired();
public slots:
/**
 * @brief Handles the burning logic on each tick.
 */
    void burn();
};

#endif // AREADAMAGE_H
