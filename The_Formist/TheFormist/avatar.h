#ifndef AVATAR_H
#define AVATAR_H

#include <QImage>
#include <QElapsedTimer>
#include <utility>


/**
 * @enum UType
 * @brief Types of power-ups or upgrades available to the avatar.
 */
enum UType{
    REVERSE_PROJECTILE,
    MORE_PROJECTILE,
    MORE_DAMAGE,
    MORE_HP

};

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
    std::pair<float,float> itsPosition;

    /**
 * @brief Indicates whether the avatar is currently invincible.
 */
    bool isInvincible;

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

/**
 * @brief Timer used to track time since last damage was taken.
 */
    QElapsedTimer lastDamageTime;

/**
 * @brief Indicates whether the avatar currently has an active shield.
 */
    bool hasShield = false;

/**
 * @brief Power-up speed multiplier affecting avatar movement.
 */
    float itsPUSpeedMult = 1;
public:
    /**
 * @brief Default constructor initializing the avatar.
 */
    Avatar(std::pair<int, int> aStartPos);

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

    /**
 * @brief Gets the current XP (experience points) of the avatar.
 * @return The current XP value.
 */
    int getItsXP() const;

    /**
 * @brief Sets the XP (experience points) of the avatar.
 * @param aXP The new XP value to set.
 */
    void setItsXP(int aXP);

    /**
 * @brief Gets the maximum XP required to level up.
 * @return The maximum XP value.
 */
    int getItsMaxXP() const;

    /**
 * @brief Increases the maximum XP required to level up.
 * @param aMaxXP The amount to add to the maximum XP.
 */
    void addMaxXP(int aMaxXP);

    /**
 * @brief Gets the maximum HP (health points) of the avatar.
 * @return The maximum HP value.
 */
    int getItsMaxHP() const;

    /**
 * @brief Increases the avatar's maximum HP.
 * @param aMaxHP The amount to add to the maximum HP.
 */
    void addMaxHP(int aMaxHP);

    /**
 * @brief Gets the current HP (health points) of the avatar.
 * @return The current HP value.
 */
    int getItsHP() const;

    /**
 * @brief Increases the avatar's current HP.
 * @param aHP The amount to add to the current HP.
 */
    void addHP(int aHP);

    /**
 * @brief Gets the current level of the avatar.
 * @return The avatar's level.
 */
    int getItsLevel() const;

    /**
 * @brief Reduces the avatar's HP based on the damage taken.
 * @param amount The amount of damage to apply.
 */
    void takeDamage(int amount);

    /**
 * @brief Increases the avatar's level by one.
 */
    void addLevel();

/**
 * @brief Activates the avatar's shield.
 */
    void activateShield();

/**
 * @brief Deactivates the avatar's shield.
 */
    void desactivateShield();

/**
 * @brief Checks if the avatar currently has a shield.
 * @return True if the shield is active, false otherwise.
 */
    bool getHasShield() const;

/**
 * @brief Gets the speed multiplier from power-ups.
 * @return The power-up speed multiplier.
 */
    float getItsPUSpeedMult() const;

/**
 * @brief Sets the speed multiplier from power-ups.
 * @param newItsPUSpeedMult The new speed multiplier value.
 */
    void setItsPUSpeedMult(float newItsPUSpeedMult);

/**
 * @brief Checks if left movement is active.
 * @return True if moving left, false otherwise.
 */
    bool getIsLeft() const;

/**
 * @brief Checks if right movement is active.
 * @return True if moving right, false otherwise.
 */
    bool getIsRight() const;

/**
 * @brief Checks if upward movement is active.
 * @return True if moving up, false otherwise.
 */
    bool getIsUp() const;

/**
 * @brief Checks if downward movement is active.
 * @return True if moving down, false otherwise.
 */
    bool getIsDown() const;
};

#endif // AVATAR_H
