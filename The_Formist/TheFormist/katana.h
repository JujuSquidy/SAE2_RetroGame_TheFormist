#ifndef KATANA_H
#define KATANA_H

#include "weapon.h"
#include <QElapsedTimer>
#include <QObject>


class Katana : public Weapon
{
    Q_OBJECT

private:
    float itsRange=200;
    QElapsedTimer itsKatanaCooldownTimer;
    std::pair<float,float> itsPosition;
    QRectF itsRectF;
    float dirX;
    float dirY;



public:
    Katana(std::pair<float,float> aTarget, std::pair<float,float> aPosition, std::pair<int,int> aSize,int baseDamage, float baseAttackSpeed, QImage* sprite = nullptr);
    ~Katana();

    void attack();
    float getItsRange() const;
    QElapsedTimer getItsKatanaCooldownTimer() const;
};


#endif
