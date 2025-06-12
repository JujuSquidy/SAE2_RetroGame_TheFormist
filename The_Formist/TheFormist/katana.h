#ifndef KATANA_H
#define KATANA_H
#include "weapon.h"
#include <QObject>


class Katana : public Weapon
{
    Q_OBJECT

private:
    float itsRange=100;
    QRectF itsKatanaImpactArea;


public:
    Katana(int baseDamage, float baseAttackSpeed, QImage* sprite = nullptr);
    ~Katana();

    float getItsRange() const;
    QRectF katanaAreaDamage(std::pair<float, float> avatarPos, std::pair<int, int> aMouseTarget);
    void addItsRange();
};


#endif
