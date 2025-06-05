#include "weapon.h"

float Weapon::getItsAttackSpeed() const
{
    return itsBaseAttackSpeed*itsAttackSpeedMult;
}

Weapon::Weapon(int aBaseDamage, float anAttackSpeed, QImage aSprite) :
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

void Weapon::attack()
{
    isShooting = true;
}

int Weapon::getItsDamage() const
{
    return itsBaseDamage * itsDamageMult;
}


float Weapon::getItsDamageMult() const
{
    return itsDamageMult;
}

void Weapon::setItsDamageMult(float aDamageMult)
{
    itsDamageMult +=0.2;

    /*
     * je fais un commentaire ici car c'est ce setter et le guetteur en commun que ça concerne et vu l'heure à laquelle j'écris ceci vous dormez sans doute
     * de base on devait rajouter +1 mais comme on ajoute via un multiplicateur, c'était étrange. donc soit on change itsBaseDamage, ce qui serait étrange vu que c'est censé être la valeur de base ou alors on rajoute 0.2 au multiplacteur, au choix
     * soit on fait comme ci-dessus du coup
     * sinon, dans avatar.cpp, dans le case de MORE_DAMAGE on écrit aWeapon->setItsBaseDamage(aWeapon->getItsBaseDamage+1)
     * voilà, j'écris les deux comme ça si le choix que j'ai fait est pas le bon ça sera pas long de retourner en arrière
     * */
}
