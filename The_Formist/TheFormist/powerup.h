#ifndef POWERUP_H
#define POWERUP_H

#include <QTimer>
#include <QImage>
#include <utility>
    /**
 * @enum PType
 * @brief Enumeration of different types of power-ups.
 *
 * Represents the type of effect the power-up provides:
 * - SHIELD: Grants protection against 1 attack.
 * - SYRINGE: Increases damage.
 * - BLOOD: Grant 20 HP.
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

class PowerUp : public QObject
{
    Q_OBJECT

private:
    /**
 * @brief Position of the power-up on the game map (x, y).
 */
    std::pair<int,int> itsPosition;

    /**
 * @brief Visual representation of the power-up.
 */
    QImage *itsSprite;

    /**
 * @brief Type of the power-up, determining the effect it applies.
 */
    PType itsType;

    /**
 * @brief The rectangular shape representing the enemy’s hitbox for collision detection.
 */
    QRectF itsRectF;

    /**
 * @brief Timer used to manage the duration of the power-up's effect.
 */
    QTimer boostTimer;

    /**
 * @brief Boolean indicating if the boots power-up effect is active.
 */
    bool bootsActive;

    /**
 * @brief Boolean indicating if the syringe power-up effect is active.
 */
    bool syringeActive;

    /**
 * @brief Boolean indicating if the pepper power-up effect is active.
 */
    bool pepperActive;

    /**
 * @brief Indicates if the power-up effect duration is finished.
 */
    bool isFinished = 0;

    /**
 * @brief Indicates if the power-up has been collected by the player.
 */
    bool isPicked = 0;

public:
    /**
 * @brief Constructs a PowerUp object at the specified position and type.
 * @param aPosition Position on the map (x, y).
 * @param aType The power-up type.
 */
    PowerUp(std::pair<int,int> aPosition, PType aType);

    /**
 * @brief Gets the rectangular hitbox for the power-up.
 * @return QRectF representing the power-up area.
 */
    QRectF getItsRectF() const;

    /**
 * @brief Gets the type of the power-up.
 * @return The power-up type (PType).
 */
    PType getItsType() const;

    /**
 * @brief Activates the boots power-up effect.
 */
    void ActivateBoots();

    /**
 * @brief Activates the syringe power-up effect.
 */
    void ActivateSyringe();

    /**
 * @brief Activates the pepper power-up effect.
 */
    void ActivatePepper();

    /**
 * @brief Checks if the power-up effect is finished.
 * @return True if finished, false otherwise.
 */
    bool getIsFinished() const;

    /**
 * @brief Checks if the power-up has been picked up.
 * @return True if picked, false otherwise.
 */
    bool getIsPicked() const;

    /**
 * @brief Sets the picked state of the power-up.
 * @param newIsPicked True if the power-up has been picked up.
 */
    void setIsPicked(bool newIsPicked);

public slots:
    /**
 * @brief Deactivates the power-up effect when its timer ends.
 */
    void DesactivatePU();
};

#endif // POWERUP_H
