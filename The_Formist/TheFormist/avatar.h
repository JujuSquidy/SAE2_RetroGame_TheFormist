#ifndef AVATAR_H
#define AVATAR_H

#include <QImage>
#include <utility>
class Avatar
{
private :
    std::pair<int,int> itsPosition;
    bool isInvincible;
    QImage itsSprite;

    int itsLevel;
    int itsSpeed;
    int itsHP;
    int itsMaxHP;
    int itsXP;
    int itsMaxXP;

public:
    Avatar();
    void move();
    void addXP(int aNB);
    void upgrade();
    void levelUp();
    std::pair<int, int> getItsPosition() const;
};

#endif // AVATAR_H
