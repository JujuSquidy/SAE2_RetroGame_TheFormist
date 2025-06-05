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

enum UType{
    REVERSE_PROJECTILE,
    MORE_PROJECTILE,
    MORE_DAMAGE,
    MORE_HP

};

class Avatar
{
private :
    /**
 * @brief Current position of the avatar (x, y).
 */
    std::pair<float,float> itsPosition;

    /**
 * @brief Indicates whether the avatar is currently invincible.
 */
    bool isInvincible;

    /**
 * @brief Visual representation (sprite) of the avatar.
 */
    QImage* itsSprite;

/**
 * @brief Graphical rectangle used for drawing and collision detection.
 */
    QRect* itsQRect;

/**
 * @brief Movement flags for each direction.
 */
    bool isLeft = 0;
    bool isRight = 0;
    bool isUp = 0;
    bool isDown = 0;

    /**
 * @brief Current level of the avatar.
 */
    int itsLevel;

    /**
 * @brief Movement speed of the avatar.
 */
    int itsBaseSpeed;

/**
 * @brief Speed multiplier for the avatar's movement.
 */
float itsSpeedMult;
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
    Avatar(QImage* aSprite, std::pair<int, int> aStartPos);

    /**
 * @brief Moves the avatar according to input or game logic.
 */
    void move(std::pair<int,int> aBorder);

    /**
 * @brief Adds experience points to the avatar.
 * @param aNB Number of experience points to add.
 */
    void addXP(int aNB);

    /**
 * @brief Levels up the avatar when enough experience is gained.
 */
    void levelUp();

    /**
 * @brief Returns the current position of the avatar.
 * @return A pair containing the (x, y) coordinates.
 */
    std::pair<float, float> getItsPosition() const;

/**
 * @brief Enables or disables left movement.
 * @param enable True to enable movement, false to disable.
 */
    void moveLeft(bool enable);

/**
 * @brief Enables or disables right movement.
 * @param enable True to enable movement, false to disable.
 */
    void moveRight(bool enable);

/**
 * @brief Enables or disables upward movement.
 * @param enable True to enable movement, false to disable.
 */
    void moveUp(bool enable);
/**
 * @brief Enables or disables downward movement.
 * @param enable True to enable movement, false to disable.
 */
    void moveDown(bool enable);
/**
 * @brief Gets the QRect used for rendering or collisions.
 * @return Pointer to the avatar's QRect.
 */
    QRect* getItsQRect() const;

    int getItsXP() const;

    void setItsXP(int aXP);

    int getItsMaxXP() const;

    void setItsMaxXP(int aMaxXP);

    int getItsMaxHP() const;

    void setItsMaxHP(int aMaxHP);

    int getItsHP() const;

    void setItsHP(int aHP);

    int getItsLevel() const;

    void setItsLevel(int aLevel);
};

#endif // AVATAR_H
