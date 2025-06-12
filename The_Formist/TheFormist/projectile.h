#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <QImage>

/**
 * @class Projectile
 * @brief Represents a moving projectile in the game, typically fired by a player or enemy.
 *
 * Contains logic for directional movement, collision area, and damage handling.
 */

class Projectile
{
private :
    /**
 * @brief Current position of the projectile (x, y).
 */
    std::pair<float,float> itsPosition;

    /**
 * @brief Size of the projectile (width, height).
 */
    std::pair<int,int> itsSize;

    /**
 * @brief Direction vector X component (normalized).
 */
    float dirX;

    /**
 * @brief Direction vector Y component (normalized).
 */
    float dirY;

    /**
 * @brief Speed of the projectile per game tick or frame.
 */
    int itsSpeed;

    /**
 * @brief Damage dealt by the projectile upon impact.
 */
    int itsDamage;

    float itsDistanceTraveled = 0;

    QRectF itsRectF;

public:
    /**
 * @brief Constructs a Projectile object.
 * @param aTarget Target position the projectile will move toward.
 * @param aPosition Starting position of the projectile.
 * @param aSize Dimensions of the projectile.
 * @param aSpeed Movement speed of the projectile.
 * @param aDamage Amount of damage the projectile will deal.
 */
    Projectile(std::pair<float,float> aTarget, std::pair<float,float> aPosition, std::pair<int,int> aSize, int aSpeed, int aDamage);

    /**
 * @brief Updates the position of the projectile based on its direction and speed.
 */
    void move();

    /**
 * @brief Returns the current position of the projectile.
 * @return A pair representing the (x, y) coordinates.
 */
    std::pair<float, float> getItsPosition() const;

    /**
 * @brief Gets the rectangular area representing the projectile's position and size.
 *
 * @return QRectF representing the projectile's bounding box.
 */
    QRectF getItsRectF() const;

    /**
 * @brief Gets the amount of damage this projectile inflicts.
 *
 * @return int The damage value.
 */
    int getItsDamage() const;
    float getItsDistanceTraveled() const;
};

#endif // PROJECTILE_H
