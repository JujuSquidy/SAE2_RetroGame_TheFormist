#ifndef AVATAR_H
#define AVATAR_H

#include <QImage>
#include <utility>
/**
 * @class Avatar
 * @brief Represents the player character in the game.
 *
 * Handles the avatar's position, movement, experience, level, health, and invincibility state.
 */

class Avatar
{
private :
    /**
 * @brief Current position of the avatar (x, y).
 */
    std::pair<int,int> itsPosition;

    /**
 * @brief Indicates whether the avatar is currently invincible.
 */
    bool isInvincible;

    /**
 * @brief Visual representation (sprite) of the avatar.
 */
    QImage itsSprite;

    /**
 * @brief Current level of the avatar.
 */
    int itsLevel;

    /**
 * @brief Movement speed of the avatar.
 */
    int itsSpeed;

    /**
 * @brief Current health points of the avatar.
 */
    int itsHP;

    /**
 * @brief Maximum health points of the avatar.
 */
    int itsMaxHP;

    /**
 * @brief Current experience points of the avatar.
 */
    int itsXP;

    /**
 * @brief Experience points required to reach the next level.
 */
    int itsMaxXP;

public:
    /**
 * @brief Default constructor initializing the avatar.
 */
    Avatar();

    /**
 * @brief Moves the avatar according to input or game logic.
 */
    void move();

    /**
 * @brief Adds experience points to the avatar.
 * @param aNB Number of experience points to add.
 */
    void addXP(int aNB);

    /**
 * @brief Upgrades the avatar’s attributes or abilities.
 */
    void upgrade();

    /**
 * @brief Levels up the avatar when enough experience is gained.
 */
    void levelUp();

    /**
 * @brief Returns the current position of the avatar.
 * @return A pair containing the (x, y) coordinates.
 */
    std::pair<int, int> getItsPosition() const;
};

#endif // AVATAR_H
