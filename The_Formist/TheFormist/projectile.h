#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <utility>
class Projectile
{
private :
    std::pair<int,int> itsTarget;
    std::pair<int,int> itsPosition;
    std::pair<int,int> itsSize;
    int itsSpeed;
    int itsDamage;

public:
    Projectile(std::pair<int,int> aTarget, std::pair<int,int> aPosition, std::pair<int,int> aSize, int aSpeed, int aDamage);
    void move();
    void createArea();

};

#endif // PROJECTILE_H
