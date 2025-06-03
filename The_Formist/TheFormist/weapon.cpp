#include "weapon.h"

float Weapon::getItsAttackSpeed() const
{
    return itsBaseAttackSpeed*itsAttackSpeedMult;
}

Weapon::Weapon(int aBaseDamage, float aAttackSpeed, QImage aSprite) {}

void Weapon::attack()
{

}

