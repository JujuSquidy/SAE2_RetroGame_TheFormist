#ifndef AREADAMAGE_H
#define AREADAMAGE_H

#include "projectile.h"

class AreaDamage : public Projectile
{
private:
    std::pair<int,int> itsArea;
    float itsDuration;
public:
    AreaDamage(std::pair<int,int> aArea,std::pair<int,int> aPosition, float aDuration, int aDamage);
};

#endif // AREADAMAGE_H
