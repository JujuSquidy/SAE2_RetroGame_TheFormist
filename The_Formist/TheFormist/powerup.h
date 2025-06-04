#ifndef POWERUP_H
#define POWERUP_H

#include <QImage>
#include <utility>
/**
 * @enum PType
 * @brief Enumeration of different types of power-ups.
 *
 * Represents the type of effect the power-up provides:
 * - SHIELD: Grants protection against 1 attack.
 * - SYRINGE: Increases damage.
 * - BLOOD: Grant 10 HP.
 * - PEPPER: Increases attack speed.
 * - BOOTS: Increases player movement speed.
 */
enum PType
{
    SHIELD,
    SYRINGE,
    BLOOD,
    PEPPER,
    BOOTS
};

/**
 * @class PowerUp
 * @brief Represents a collectible item that temporarily boosts player stats or abilities.
 *
 * Power-ups appear in the game world and grant bonuses based on their type when collected.
 */

class PowerUp
{
private:
    /**
 * @brief Position of the power-up on the game map (x, y).
 */
    std::pair<int,int> itsPosition;

    /**
 * @brief Visual representation of the power-up.
 */
    QImage itsSprite;

    /**
 * @brief Type of the power-up, determining the effect it applies.
 */
    PType itsType;
public:
    /**
 * @brief Constructs a PowerUp object with default properties.
 */
    PowerUp();
};

#endif // POWERUP_H
