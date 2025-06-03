#ifndef POWERUP_H
#define POWERUP_H

#include <QImage>
#include <utility>

enum PType
{
    SHIELD,
    SYRINGE,
    BLOOD,
    PEPPER,
    BOOTS
};

class PowerUp
{
private:
    std::pair<int,int> itsPosition;
    QImage itsSprite;
    PType itsType;
public:
    PowerUp();
};

#endif // POWERUP_H
