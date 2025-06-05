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
    QRectF itsRectF;
    /**
 * @brief Direction vector X component (normalized).
 */
    float dirX;

    /**
 * @brief Direction vector Y component (normalized).
 */
    float dirY;
    QImage *itsSprite;

    QRect itsEnemy;
    EType itsType;
public:
    Enemy(std::pair<float,float> aPosition, QImage* aSprite, int bossTimer);
    void shoot(std::pair<int,int> aTarget);
    bool isDead();
    void move(std::pair<float, float> aTarget);
    void takeDamage(int amount);
    int getHP() const;
    
    /**
 * @brief Returns the current position of the enemy.
 * @return A pair containing the (x, y) coordinates.
 */
    std::pair<float, float> getItsPosition() const;
    EType getType() const;
    QRectF getItsRectF() const;
    int getItsGivenXP() const;
    int getItsStrength() const;
    void setItsPosition(const std::pair<float, float> &newItsPosition);
};

#endif // ENEMY_H
