#ifndef POWERUP_H
#define POWERUP_H

#include "qimage.h"
#include <utility>
class PowerUp
{
private:
    std::pair<int,int> itsPosition;
    QImage itsSprite;

public:
    PowerUp();
};

#endif // POWERUP_H
