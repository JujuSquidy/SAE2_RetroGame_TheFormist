#include "avatar.h"

std::pair<float, float> Avatar::getItsPosition() const
{
    return itsPosition;
}

QRect *Avatar::getItsQRect() const
{
    return itsQRect;
}

bool Avatar::getHasShield() const
{
    return hasShield;
}

float Avatar::getItsPUSpeedMult() const
{
    return itsPUSpeedMult;
}

void Avatar::setItsPUSpeedMult(float newItsPUSpeedMult)
{
    itsPUSpeedMult = newItsPUSpeedMult;
}

bool Avatar::getIsLeft() const
{
    return isLeft;
}

bool Avatar::getIsRight() const
{
    return isRight;
}

bool Avatar::getIsUp() const
{
    return isUp;
}

bool Avatar::getIsDown() const
{
    return isDown;
}

Avatar::Avatar(std::pair<int,int> aStartPos) : itsPosition(aStartPos)
{
    itsLevel = 1;
    itsHP = 100;
    itsMaxHP = 100;
    itsMaxXP = 50;
    itsBaseSpeed = 1;
    itsSpeedMult = 1;
    itsXP = 0;
    itsQRect = new QRect(itsPosition.first, itsPosition.second, 48, 64);
}

void Avatar::move(std::pair<int,int> aBorder)
{
    // Initialize movement deltas
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

    // Normalize the direction vector to avoid faster diagonal movement (pythagore's theory)
    float length = std::sqrt(dx*dx + dy*dy);
    if (length > 0)
    {
        dx /= length;
        dy /= length;
    }

    // Calculate actual movement speed using base speed and multipliers
    float speed = itsBaseSpeed * itsSpeedMult * itsPUSpeedMult;

    // Compute future positions based on speed and direction
    float futurePosX = itsPosition.first  + dx * speed;
    float futurePosY = itsPosition.second + dy * speed;

    if(futurePosX >= 0 and futurePosX+itsQRect->width() <= aBorder.first)
        itsPosition.first  += dx * speed;
    if(futurePosY >= 0 and futurePosY+itsQRect->height() <= aBorder.second)
        itsPosition.second += dy * speed;

    // Move the visual representation (QRect) to the new position
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

    // Make sure HP does not exceed the maximum allowed
    if(itsHP > itsMaxHP)
    {
        itsHP = itsMaxHP;
    }
}

int Avatar::getItsLevel() const
{
    return itsLevel;
}

void Avatar::addLevel()
{
    itsLevel++;
}

void Avatar::activateShield()
{
    hasShield = true;
}

void Avatar::desactivateShield()
{
    hasShield = false;
}

void Avatar::takeDamage(int amount)
{
    // Either it's the first time taking damage (invalid time), or enough time has passed since last damage

    if (!lastDamageTime.isValid() || lastDamageTime.elapsed() >= 500) {
        itsHP -= amount;
        if (itsHP < 0) itsHP = 0;

        // Restart the damage cooldown timer
        lastDamageTime.restart();
    }
}
