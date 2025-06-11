#ifndef KATANA_H
#define KATANA_H

#include "weapon.h"
#include <QTimer>
#include <QObject>


class Katana : public Weapon
{
    Q_OBJECT

private:
    float itsRange=500;
    QTimer itsKatanaCooldownTimer;
    std::pair<float,float> itsPosition;
    QRectF itsRectF;
    float dirX;
    float dirY;


public:
    Katana(std::pair<float,float> aTarget, std::pair<float,float> aPosition, std::pair<int,int> aSize,int baseDamage, float baseAttackSpeed, QImage* sprite = nullptr);
    ~Katana();

    float getItsRange() const;
    float getDirX() const;
    float getDirY() const;
};


#endif
