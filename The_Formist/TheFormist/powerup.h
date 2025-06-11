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

    QTimer boostTimer;

    bool bootsActive;

    bool syringeActive;

    bool pepperActive;

    bool isFinished = 0;

    bool isPicked = 0;

public:
    /**
 * @brief Constructs a PowerUp object with default properties.
 */
    PowerUp(std::pair<int,int> aPosition, PType itsType, QImage *aSprite = nullptr);
    QRectF getItsRectF() const;
    PType getItsType() const;

    void ActivateBoots();
    void ActivateSyringe();
    void ActivatePepper();

    bool getIsFinished() const;
    void setIsFinished(bool newIsFinished);

    bool getIsPicked() const;
    void setIsPicked(bool newIsPicked);

public slots :
    void DesactivatePU();
};

#endif // POWERUP_H
