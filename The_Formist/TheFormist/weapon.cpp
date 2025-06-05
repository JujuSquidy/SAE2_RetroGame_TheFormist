#include "weapon.h"

float Weapon::getItsAttackSpeed() const
{
    return itsBaseAttackSpeed*itsAttackSpeedMult;
}

Weapon::Weapon(int aBaseDamage, float anAttackSpeed, QImage *aSprite) :
    itsBaseDamage(aBaseDamage), itsBaseAttackSpeed(anAttackSpeed), itsSprite(aSprite)
{
    itsTimer = new QTimer;
    connect(itsTimer, SIGNAL(timeout()), this, SLOT(attack()));
    itsTimer->start(1000);
}

Weapon::~Weapon()
{
    delete itsTimer;
    itsTimer = nullptr;
}

bool Weapon::getIsShooting() const
{
    return isShooting;
}

void Weapon::setIsShooting(bool newIsShooting)
{
    isShooting = newIsShooting;
}

int Weapon::getItsDamage() const
{
    return itsBaseDamage * itsDamageMult;
}

void Weapon::attack()
{
    isShooting = true;
}

