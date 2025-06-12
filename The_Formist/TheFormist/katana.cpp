#include "katana.h"
#include <cmath>

Katana::Katana(int baseDamage, float baseAttackSpeed, QImage* sprite)
    : Weapon(baseDamage, baseAttackSpeed, sprite)
{
}

Katana::~Katana()
{
}

float Katana::getItsRange() const
{
    return itsRange;
}

void Katana::addItsRange()
{
    itsRange ++;
}

// Calcule la zone d'attaque du katana en fonction de la position de l'avatar et du ciblage souris
QRectF Katana::katanaAreaDamage(std::pair<float, float> avatarPos, std::pair<int, int> aMouseTarget)
{
    float avatarX = avatarPos.first;
    float avatarY = avatarPos.second;
    float width = itsRange*2;
    float height = itsRange;

    float dx = aMouseTarget.first - avatarX;
    float dy = aMouseTarget.second - avatarY;
    float norm = std::sqrt(dx*dx + dy*dy);
    if (norm == 0) norm = 1;
    float dirX = dx / norm;
    float dirY = dy / norm;

    float startX = avatarX + dirX * (height / 2);
    float startY = avatarY + dirY * (height / 2);

    return QRectF(startX - width / 2, startY - height / 2, width, height);
}

