#include "weapon.h"

float Weapon::getItsAttackSpeed() const
{
    return itsBaseAttackSpeed*itsAttackSpeedMult;
}

Weapon::Weapon(int aBaseDamage, float anAttackSpeed, QImage aSprite) {}

void Weapon::attack()
{

}

