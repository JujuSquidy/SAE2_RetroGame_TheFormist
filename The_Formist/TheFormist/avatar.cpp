#include "avatar.h"


std::pair<float, float> Avatar::getItsPosition() const
{
    return itsPosition;
}

QRect *Avatar::getItsQRect() const
{
    return itsQRect;
}

Avatar::Avatar(std::pair<int,int> aStartPos, QImage* aSprite) : itsSprite(aSprite)
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

void Avatar::move(std::pair<int,int> aBorder)
{
    float dx = 0;
    float dy = 0;

    if (isLeft && !isRight)
        dx -= 1;
    else if (isRight && !isLeft)
        dx += 1;

    if (isUp && !isDown)
        dy -= 1;
    else if (isDown && !isUp)
        dy += 1;

    // Normalisation pour ne pas aller plus vite en diagonale
    float length = std::sqrt(dx*dx + dy*dy);
    if (length > 0)
    {
        dx /= length;
        dy /= length;
    }

    float speed = itsBaseSpeed * itsSpeedMult;
    float futurePosX = itsPosition.first  + dx * speed;
    float futurePosY = itsPosition.second + dy * speed;
    if(futurePosX >= 0 and futurePosX+itsQRect->width() <= aBorder.first)
        itsPosition.first  += dx * speed;
    if(futurePosY >= 0 and futurePosY+itsQRect->height() <= aBorder.second)
        itsPosition.second += dy * speed;

    itsQRect->moveTo(itsPosition.first, itsPosition.second);
}

void Avatar::addXP(int aNB)
{
    itsXP += aNB;
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

int Avatar::getItsXP() const
{
    return itsXP;
}

void Avatar::setItsXP(int aXP)
{
    itsXP=aXP;
}

int Avatar::getItsMaxXP() const
{
    return itsMaxXP;
}

void Avatar::addMaxXP(int aMaxXP)
{
    itsMaxXP+=aMaxXP;
}

int Avatar::getItsMaxHP() const
{
    return itsMaxHP;
}

void Avatar::addMaxHP(int aMaxHP)
{
    itsMaxHP+=aMaxHP;
}

int Avatar::getItsHP() const
{
    return itsHP;
}

void Avatar::addHP(int aHP)
{
    itsHP+=aHP;
}

int Avatar::getItsLevel() const
{
    return itsLevel;
}

void Avatar::takeDamage(int amount)
{
    if (!lastDamageTime.isValid() || lastDamageTime.elapsed() >= 500) {
        itsHP -= amount;
        if (itsHP < 0) itsHP = 0;
        lastDamageTime.restart();
    }
}
