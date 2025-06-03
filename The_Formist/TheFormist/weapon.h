#ifndef WEAPON_H
#define WEAPON_H

#include <QImage>
/**
 * @class Weapon
 * @brief Base class for all weapons in the game.
 *
 * Defines the core attributes and behavior shared by all weapon types, such as damage and attack speed.
 */
class Weapon
{
private:
    /**
 * @brief Base damage value of the weapon.
 */
    int itsBaseDamage;

    /**
 * @brief Multiplier applied to the base damage (e.g., for upgrades or power-ups).
 */
    float itsDamageMult;

    /**
 * @brief Base attack speed (e.g., shots per second or time between attacks).
 */
    float itsBaseAttackSpeed;

    /**
 * @brief Multiplier applied to the base attack speed.
 */
    float itsAttackSpeedMult;

    /**
 * @brief Sprite used to visually represent the weapon.
 */
    QImage itsSprite;


public:
    /**
 * @brief Constructs a Weapon with specified base damage, attack speed, and sprite.
 * @param aBaseDamage The initial damage dealt by the weapon.
 * @param aAttackSpeed The base interval between attacks.
 * @param aSprite The graphical sprite representing the weapon.
 */
    Weapon(int aBaseDamage, float aAttackSpeed, QImage aSprite);

    /**
 * @brief Executes the weapon's attack behavior.
 *
 * Can be overridden by derived classes to define specific attack patterns.
 */
    virtual void attack();

    /**
 * @brief Returns the effective attack speed, factoring in multipliers.
 * @return A float representing the current attack speed.
 */
    float getItsAttackSpeed() const;
};

#endif // WEAPON_H
