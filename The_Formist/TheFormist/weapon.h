#ifndef WEAPON_H
#define WEAPON_H

#include <QImage>

class Weapon
{
private:
    int itsBaseDamage;
    float itsDamageMult;
    float itsBaseAttackSpeed;
    float itsAttackSpeedMult;
    QImage itsSprite;

public:
    Weapon(int aBaseDamage, float aAttackSpeed, QImage aSprite);
    virtual void attack();
    float getItsAttackSpeed() const;
};

#endif // WEAPON_H
