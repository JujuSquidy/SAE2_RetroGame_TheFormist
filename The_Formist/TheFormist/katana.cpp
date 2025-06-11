#include "katana.h"
#include <cmath>
#include <vector>


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

std::vector<float> Katana::katanaAreaDamage(Avatar* aAvatar, pair<int,int> aMouseTarget)
{
    float avatarX = aAvatar->getItsPosition().first;
    float avatarY = aAvatar->getItsPosition().second;

    float dx = aMouseTarget.first - avatarX;
    float dy = aMouseTarget.second - avatarY;
    float norm = std::sqrt(dx*dx + dy*dy);
    if (norm == 0) norm = 1;
    float dirX = dx / norm;
    float dirY = dy / norm;

    float range = this->getItsRange();
    float angle = M_PI / 4; // 45 degrés, sans .0f
    float cosHalfAngle = std::cos(angle / 2);

    return {avatarX, avatarY, dirX, dirY, range, cosHalfAngle};
}
