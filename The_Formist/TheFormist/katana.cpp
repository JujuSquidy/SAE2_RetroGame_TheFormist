#include "katana.h"


float Katana::getItsRange() const
{
    return itsRange;
}


float Katana::getDirX() const
{
    return dirX;
}

float Katana::getDirY() const
{
    return dirY;
}

Katana::Katana(std::pair<float, float> aTarget, std::pair<float, float> aPosition, std::pair<int, int> aSize, int baseDamage, float baseAttackSpeed, QImage* sprite)
    : Weapon(baseDamage, baseAttackSpeed, sprite)
{
    itsPosition = aPosition;

    float dx = aTarget.first - aPosition.first;
    float dy = aTarget.second - aPosition.second;

    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance != 0) {
        dirX = dx / distance;
        dirY = dy / distance;
    }
    else {
        dirX = 0;
        dirY = 0;
    }

    itsRectF = QRectF(aPosition.first, aPosition.second, aSize.first, aSize.second);

    itsRange = 200;
}



Katana::~Katana()
{
}
