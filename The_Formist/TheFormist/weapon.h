#ifndef WEAPON_H
#define WEAPON_H

#include <QTimer>
#include <QImage>
/**
 * @class Weapon
 * @brief Base class for all weapons in the game.
 *
 * Defines the core attributes and behavior shared by all weapon types, such as damage and attack speed.
 */
class Weapon : public QObject
{
    Q_OBJECT

private:
    /**
 * @brief Base damage value of the weapon.
 */
    int itsBaseDamage;

    /**
 * @brief Multiplier applied to the base damage (e.g., for upgrades or power-ups).
 */
    float itsDamageMult = 1;

    /**
 * @brief Base attack speed (e.g., shots per second or time between attacks).
 */
    float itsBaseAttackSpeed;

    /**
 * @brief Multiplier applied to the base attack speed.
 */
    float itsAttackSpeedMult = 1;

    /**
 * @brief Sprite used to visually represent the weapon.
 */
    QImage *itsSprite;

/**
 * @brief Internal timer for managing attack intervals.
 */
    QTimer * itsTimer;

/**
 * @brief Indicates whether the weapon is currently firing.
 */
    bool isShooting = false;

    float itsPUAttackSpeedMult = 1;

    float itsPUDamageMult = 1;



public slots:
    /**
 * @brief Executes the weapon's attack behavior.
 *
 * Can be overridden by derived classes to define specific attack patterns.
 */
    virtual void attack();

public:
    /**
 * @brief Constructs a Weapon with specified base damage, attack speed, and sprite.
 * @param aBaseDamage The initial damage dealt by the weapon.
 * @param aAttackSpeed The base interval between attacks.
 * @param aSprite The graphical sprite representing the weapon.
 */
    Weapon(int aBaseDamage, float anAttackSpeed, QImage *aSprite = nullptr);

    /**
 * @brief Destruct a weapon.
 */
    virtual ~Weapon();

    /**
 * @brief Returns the effective attack speed, factoring in multipliers.
 * @return A float representing the current attack speed.
 */
    float getItsAttackSpeed() const;

    /**
     * @brief Returns whether the weapon is currently firing.
     * @return True if shooting, false otherwise.
     */
    bool getIsShooting() const;

    /**
     * @brief Sets whether the weapon is currently firing.
     * @param newIsShooting Boolean flag to set shooting state.
     */
    void setIsShooting(bool newIsShooting);

    /**
 * @brief Gets the current damage value of the weapon.
 *
 * @return int The amount of damage dealt by a single projectile.
 */
    int getItsDamage() const;

    /**
     * @brief Get the damage multiplicator
     * @return A float representing current damage multiplicator
     */
    float getItsBaseDamage() const;

    /**
     * @brief Set the damage multiplicator
     * @param aDamageMult float to set the new value
     */
    void AddBaseDamage(float aBaseDamage);

    /**
 * @brief Sets the damage multiplier.
 * @param m The multiplier value to set.
 */
    void setDamageMult(float m);

    /**
 * @brief Sets the attack speed multiplier.
 * @param m The multiplier value to set.
 */
    void setAttackSpeedMult(float m);

    void setItsPUAttackSpeedMult(float newItsPUAttackSpeedMult);
    void setItsPUDamageMult(float newItsPUDamageMult);
};

#endif // WEAPON_H
