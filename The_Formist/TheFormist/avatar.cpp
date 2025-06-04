#include "avatar.h"


std::pair<float, float> Avatar::getItsPosition() const
{
    return itsPosition;
}

QRect *Avatar::getItsQRect() const
{
    return itsQRect;
}

Avatar::Avatar(QImage* aSprite, std::pair<int,int> aStartPos) : itsSprite(aSprite)
{
    itsLevel = 1;
    itsHP = 100;
    itsMaxHP = 100;
    itsPosition = aStartPos;
    itsMaxXP = 50;
    itsBaseSpeed = 1;
    itsSpeedMult = 1;
    itsXP = 0;
    itsQRect = new QRect(itsPosition.first, itsPosition.second, 30, 30);
}

void Avatar::move()
{
    if(isLeft and !isRight)
    {
        if(isUp and !isDown)
        {
            itsPosition.first-=float(0.7*itsBaseSpeed*itsSpeedMult);
            itsPosition.second-=float(0.7*itsBaseSpeed*itsSpeedMult);
        }
        else if(isDown and !isUp)
        {
            itsPosition.first-=float(0.7*itsBaseSpeed*itsSpeedMult);
            itsPosition.second+=float(0.7*itsBaseSpeed*itsSpeedMult);
        }
        itsPosition.first-=float(itsBaseSpeed*itsSpeedMult);
    }

    else if(isRight and !isLeft)
    {
        if(isUp and !isDown)
        {
            itsPosition.first+=float(0.7*itsBaseSpeed*itsSpeedMult);
            itsPosition.second-=float(0.7*itsBaseSpeed*itsSpeedMult);
        }
        else if(isDown and !isUp)
        {
            itsPosition.first+=float(0.7*itsBaseSpeed*itsSpeedMult);
            itsPosition.second+=float(0.7*itsBaseSpeed*itsSpeedMult);
        }
        itsPosition.first+=float(itsBaseSpeed*itsSpeedMult);
    }
    else if(isUp and !isDown)
    {
        itsPosition.second-=float(itsBaseSpeed*itsSpeedMult);
    }
    else if(isDown and !isUp)
    {
        itsPosition.second+=float(itsBaseSpeed*itsSpeedMult);
    }
    itsQRect->moveTo(itsPosition.first, itsPosition.second);
}

void Avatar::addXP(int aNB)
{
    itsXP += aNB;
}

void Avatar::upgrade()
{

}

void Avatar::levelUp()
{
    itsLevel++;
}


void Avatar::moveLeft(bool enable)
{
    isLeft = enable;
}

void Avatar::moveRight(bool enable)
{
    isRight = enable;
}

void Avatar::moveUp(bool enable)
{
    isUp = enable;
}

void Avatar::moveDown(bool enable)
{
    isDown = enable;
}

