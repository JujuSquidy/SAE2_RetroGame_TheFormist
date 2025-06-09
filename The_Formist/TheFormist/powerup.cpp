#include "powerup.h"

QRectF PowerUp::getItsRectF() const
{
    return itsRectF;
}

PType PowerUp::getItsType() const
{
    return itsType;
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
}
