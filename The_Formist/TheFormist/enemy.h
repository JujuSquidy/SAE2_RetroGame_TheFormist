#ifndef ENEMY_H
#define ENEMY_H

#include <QImage>
#include <utility>

enum EType{
    CIRCLE,
    TRIANGLE,
    SQUARE,
    BOSS
};

class Enemy
{
private:
    std::pair<float,float> itsPosition;
    float itsSpeed;
    int itsStrength;
    int itsHP;
    int itsMaxHP;
    int itsGivenXP;
    /**
 * @brief Direction vector X component.
 */
    float dirX;

    /**
 * @brief Direction vector Y component.
 */
    float dirY;
    QImage itsSprite;

    QRect itsEnemy;
    EType itsType;
public:
    Enemy(std::pair<float,float> aPosition, QImage* aSprite, int bossTimer);
    void shoot(std::pair<float,float> aTarget);
    bool isDead();
    void move(std::pair<float, float> aTarget);
    /**
 * @brief Returns the current position of the enemy.
 * @return A pair containing the (x, y) coordinates.
 */
    std::pair<float, float> getItsPosition() const;
    EType getType() const;


};

#endif // ENEMY_H
