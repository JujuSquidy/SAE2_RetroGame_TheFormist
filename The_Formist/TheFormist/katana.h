#ifndef KATANA_H
#define KATANA_H
#include "weapon.h"
#include <QObject>


/**
 * @class Katana
 * @brief Represents a melee weapon with a specific range and damage area.
 *
 * Inherits from Weapon and adds functionality specific to the katana,
 * including its attack range and the damage impact area.
 */
class Katana : public Weapon
{
    Q_OBJECT

private:
    /**
 * @brief The effective range of the katana attack.
 */
    float itsRange = 100;

    /**
 * @brief Rectangle area representing the katana's impact zone.
 */
    QRectF itsKatanaImpactArea;

public:
    /**
 * @brief Constructs a Katana with base damage and attack speed.
 * @param aBaseDamage Base damage inflicted by the katana.
 * @param aBaseAttackSpeed Base attack speed of the katana.
 */
    Katana(int aBaseDamage, float aBaseAttackSpeed);

    /**
 * @brief Destructor.
 */
    ~Katana();

    /**
 * @brief Gets the current attack range of the katana.
 * @return Range as a float value.
 */
    float getItsRange() const;

    /**
 * @brief Calculates the damage area rectangle based on avatar position and mouse target.
 * @param avatarPos The current position of the avatar.
 * @param aMouseTarget The target position indicated by the mouse.
 * @return QRectF representing the katana's damage impact area.
 */
    QRectF katanaAreaDamage(std::pair<float, float> avatarPos, std::pair<int, int> aMouseTarget);

    /**
 * @brief Increases the katana's attack range.
 */
    void addItsRange();
};


#endif
