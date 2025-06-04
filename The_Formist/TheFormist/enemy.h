#ifndef ENEMY_H
#define ENEMY_H

#include <QImage>
#include <utility>

/**
 * @enum EType
 * @brief Enumeration of enemy types.
 *
 * Defines different enemy shapes or categories:
 * - CIRCLE
 * - TRIANGLE
 * - SQUARE
 * - BOSS
 */
enum EType{
    CIRCLE,
    TRIANGLE,
    SQUARE,
    BOSS
};

/**
 * @class Enemy
 * @brief Represents an enemy character in the game.
 *
 * Handles enemy position, movement, health, damage, experience points given,
 * and sprite representation.
 */

class Enemy
{
private:
    /**
 * @brief Current position of the enemy (x, y).
 */
    std::pair<int,int> itsPosition;

    /**
 * @brief Movement speed of the enemy.
 */
    float itsSpeed;

    /**
 * @brief Strength or damage potential of the enemy.
 */
    int itsStrength;

    /**
 * @brief Current health points of the enemy.
 */
    int itsHP;

    /**
 * @brief Maximum health points of the enemy.
 */
    int itsMaxHP;

    /**
 * @brief Experience points awarded to the player when enemy is defeated.
 */
    int itsGivenXP;

    /**
 * @brief Visual representation of the enemy.
 */
    QImage itsSprite;
    QRect itsEnemy;
public:
    /**
 * @brief Constructs an Enemy.
 * @param aPosition Initial position of the enemy.
 * @param aSprite Sprite image for the enemy.
 * @param aHP Initial health points.
 * @param aType Type of enemy from EType enum.
 */
    Enemy(std::pair<int,int> aPosition, QImage aSprite, int aHP, EType aType, int bossTimer); //bossTimer correspond au chrono du boss, il devra être passé en paramètre à chaque construction d'un ennemi dans la game loop


    /**
 * @brief Enemy shoots toward a target position.
 * @param aTarget Target position (x, y) to shoot at.
 */
    void shoot(std::pair<int,int> aTarget);

    /**
 * @brief Checks if the enemy is dead (HP <= 0).
 * @return true if enemy is dead, false otherwise.
 */
    bool isDead();
    /**
 * @brief Moves the enemy based on its speed and logic.
 */
    void move(std::pair<int, int> aTarget);
};

#endif // ENEMY_H
