#include "weapon.h"

float Weapon::getItsAttackSpeed() const
{
    return itsBaseAttackSpeed * itsAttackSpeedMult;
}

Weapon::Weapon(int aBaseDamage, float anAttackSpeed, QImage *aSprite) :
    itsBaseDamage(aBaseDamage), itsBaseAttackSpeed(anAttackSpeed), itsSprite(aSprite)
{
    itsTimer = new QTimer;
    connect(itsTimer, SIGNAL(timeout()), this, SLOT(attack()));
    itsTimer->start(500 / (itsAttackSpeedMult * itsPUAttackSpeedMult * itsBaseAttackSpeed));
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
    return static_cast<int>(itsBaseDamage * itsDamageMult * itsPUDamageMult);
}

void Weapon::setItsPUAttackSpeedMult(float newItsPUAttackSpeedMult)
{
    itsPUAttackSpeedMult = newItsPUAttackSpeedMult;
}


void Weapon::setItsPUDamageMult(float newItsPUDamageMult)
{
    itsPUDamageMult = newItsPUDamageMult;
}

void Weapon::attack()
{
    isShooting = true;
}


float Weapon::getItsBaseDamage() const
{
    return itsBaseDamage;
}

void Weapon::AddBaseDamage(float aBaseDamage)
{
    itsBaseDamage+=aBaseDamage;
}

void Weapon::setDamageMult(float m)
{
    itsDamageMult = m;
}

void Weapon::setAttackSpeedMult(float m)
{
    itsAttackSpeedMult = m;
}

