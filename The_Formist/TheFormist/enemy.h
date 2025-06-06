#ifndef ENEMY_H
#define ENEMY_H

#include <QImage>
#include <utility>
#include <QElapsedTimer>

enum EType{
    CIRCLE,
    TRIANGLE,
    SQUARE,
    BOSS
};

class Enemy
{
private:
    /**
 * @brief The current position of the enemy (x, y).
 */
    std::pair<float, float> itsPosition;

    /**
 * @brief The movement speed of the enemy.
 */
    float itsSpeed;

    /**
 * @brief The strength of the enemy, used to determine the damage dealt.
 */
    int itsStrength;

    /**
 * @brief The current health points (HP) of the enemy.
 */
    int itsHP;

    /**
 * @brief The maximum health points (HP) of the enemy.
 */
    int itsMaxHP;

    /**
 * @brief The amount of experience (XP) given to the player when this enemy is defeated.
 */
    int itsGivenXP;

    /**
 * @brief A timer used to manage the cooldown between enemy shots.
 */
    QElapsedTimer itsShootCD;

    /**
 * @brief Indicates whether the enemy is currently shooting.
 */
    bool isShooting = false;

    /**
 * @brief The rectangular shape representing the enemy’s hitbox for collision detection.
 */
    QRectF itsRectF;


    /**
 * @brief Direction vector X component (normalized).
 */
    float dirX;

    /**
 * @brief Direction vector Y component (normalized).
 */
    float dirY;

    /**
 * @brief The sprite image representing the enemy visually.
 */
    QImage *itsSprite;

    /**
 * @brief The type of the enemy (e.g., TRIANGLE, SQUARE, CIRCLE, BOSS).
 */
    EType itsType;

public:

    /**
 * @brief Constructor for Enemy.
 * @param aPosition Initial position of the enemy (x, y).
 * @param aSprite Pointer to the sprite image for the enemy.
 */
    Enemy(std::pair<float,float> aPosition, QImage* aSprite);

    /**
 * @brief Makes the enemy shoot a projectile.
 */
    void shoot();

    /**
 * @brief Checks if the enemy is dead.
 * @return True if the enemy's HP is 0 or below, otherwise false.
 */
    bool isDead();

    /**
 * @brief Defines the enemy's behavior each frame (e.g., moving towards target, shooting).
 * @param aTarget The target position (x, y) the enemy acts upon (usually the player's position).
 */
    void act(std::pair<float, float> aTarget);

    /**
 * @brief Applies damage to the enemy.
 * @param amount The amount of damage to inflict.
 */
    void takeDamage(int amount);

    /**
 * @brief Gets the current health points of the enemy.
 * @return The current HP.
 */
    int getHP() const;

    
    /**
 * @brief Returns the current position of the enemy.
 * @return A pair containing the (x, y) coordinates.
 */
    std::pair<float, float> getItsPosition() const;

    /**
 * @brief Gets the enemy type.
 * @return The enemy type (EType).
 */
    EType getType() const;

    /**
 * @brief Gets the bounding rectangle of the enemy.
 * @return QRectF representing the enemy's bounding box.
 */
    QRectF getItsRectF() const;

    /**
 * @brief Gets the amount of XP given when the enemy is defeated.
 * @return The XP value.
 */
    int getItsGivenXP() const;

    /**
 * @brief Sets whether the enemy is currently shooting.
 * @param newIsShooting True if shooting, false otherwise.
 */
    void setIsShooting(bool newIsShooting);

    /**
 * @brief Checks if the enemy is currently shooting.
 * @return True if shooting, false otherwise.
 */
    bool getIsShooting() const;

    /**
 * @brief Sets the position of the enemy.
 * @param newItsPosition The new position as a pair (x, y).
 */
    void setItsPosition(const std::pair<float, float> &newItsPosition);

    /**
 * @brief Gets the strength (damage) of the enemy.
 * @return The enemy's strength value.
 */
    int getItsStrength() const;

};

#endif // ENEMY_H
