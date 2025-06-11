#include "powerup.h"

QRectF PowerUp::getItsRectF() const
{
    return itsRectF;
}

PType PowerUp::getItsType() const
{
    return itsType;
}

void PowerUp::ActivateBoots()
{
    bootsActive = true;
    boostTimer.start(5000);
}

void PowerUp::ActivateSyringe()
{
    syringeActive = true;
    boostTimer.start(5000);
}

void PowerUp::ActivatePepper()
{
    pepperActive = true;
    boostTimer.start(5000);
}

void PowerUp::DesactivatePU()
{
    if (itsType == SYRINGE)
    {
        syringeActive = false;
        isFinished = true;
        boostTimer.stop();
    }
    if (itsType == BOOTS)
    {
        bootsActive = false;
        isFinished = true;
        boostTimer.stop();
    }
    if (itsType == PEPPER)
    {
        pepperActive = false;
        isFinished = true;
        boostTimer.stop();
    }
}

bool PowerUp::getIsFinished() const
{
    return isFinished;
}

bool PowerUp::getIsPicked() const
{
    return isPicked;
}

void PowerUp::setIsPicked(bool newIsPicked)
{
    isPicked = newIsPicked;
}

PowerUp::PowerUp(std::pair<int,int> aPosition, PType aType, QImage *aSprite) {
    itsPosition = aPosition;
    itsType = aType;
    switch (aType)
    {
    case SHIELD:
        itsRectF = QRectF(itsPosition.first, itsPosition.second, 15.0, 15.0);

        break;

    case SYRINGE:
        itsRectF = QRectF(itsPosition.first, itsPosition.second, 15.0, 15.0);

        break;

    case BLOOD:
        itsRectF = QRectF(itsPosition.first, itsPosition.second, 15.0, 15.0);

        break;

    case PEPPER:
        itsRectF = QRectF(itsPosition.first, itsPosition.second, 15.0, 15.0);

        break;

    case BOOTS:
        itsRectF = QRectF(itsPosition.first, itsPosition.second, 15.0, 15.0);

        break;
    }

    connect(&boostTimer, SIGNAL(timeout()), this, SLOT(DesactivatePU()));
}

