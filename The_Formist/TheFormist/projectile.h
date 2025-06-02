#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <utility>
class Projectile
{
private :
    int itsSpeed;
    std::pair<int,int> itsPosition;
    int itsDamage;
    std::pair<int,int> itsTarget;
public:
    Projectile(std::pair<int,int> aTarget,std::pair<int,int> aPosition, int aSpeed, int aDamage);
    void move();
    void createArea();

};

#endif // PROJECTILE_H
