#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <utility>
class Projectile
{
private :
    std::pair<int,int> itsPosition;
    std::pair<int,int> itsSize;
    float dirX, dirY;
    int itsSpeed;
    int itsDamage;

public:
    Projectile(std::pair<int,int> aTarget, std::pair<int,int> aPosition, std::pair<int,int> aSize, int aSpeed, int aDamage);
    void move();
    void createArea();
    std::pair<int, int> getItsPosition() const;
};

#endif // PROJECTILE_H
