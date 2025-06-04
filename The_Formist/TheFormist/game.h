#ifndef GAME_H
#define GAME_H

#include <QTimer>
#include "avatar.h"
#include "enemy.h"
#include "powerup.h"
#include "projectile.h"
#include <QElapsedtimer>
#include "weapon.h"
#include "gun.h"

/**
 * @class Game
 * @brief Manages the core game logic, entities, and real-time updates.
 *
 * Handles the state of the game including the avatar, enemies, projectiles,
 * power-ups, and weapon logic. Coordinates input, collisions, and rendering updates.
 */

class Game : public QObject
{
    Q_OBJECT

private :

    /**
     * @brief Timer used to manage boss apparition
     */

    QTimer *itsEnemyTimer;
    /**
 * @brief Timer used to show time elapsed in the game and manage enemies apparition.
 */
    QTimer *itsTimer;

    /**
 * @brief Defines the game area boundaries (width, height).
 */
    std::pair<int,int> itsBorder;

    /**
 * @brief Stores the player's current score.
 */
    long int itsScore;

    /**
 * @brief List of active projectiles in the game.
 */
    std::vector<Projectile*> itsProjectiles;

    /**
 * @brief Pointer to the player's avatar.
 */
    Avatar* itsAvatar;

    /**
 * @brief Pointer to the player's equipped weapon.
 */
    Weapon* itsWeapon;

    /**
 * @brief List of active enemies in the game.
 */
    std::vector<Enemy*> itsEnemies;

    /**
 * @brief The current power-up present in the game.
 */
    PowerUp *itsPowerUp = nullptr;

    /**
 * @brief The latest target position from the mouse (used for aiming).
 */
    std::pair<int,int> mouseTarget;


public:
    /**
 * @brief Constructs the Game object and initializes components.
 */
    Game(QObject *parent = nullptr);

    /**
 * @brief Destructor that cleans up dynamically allocated resources.
 */
    ~Game();

    /**
 * @brief Handles logic for applying or spawning power-ups.
 */
    void PowerUp();

    /**
 * @brief Detects and handles collisions and damages between entities.
 */
    void Collision();

    /**
 * @brief Ends the game, stopping the loop and triggering endgame behavior.
 */
    void GameOver();

    /**
 * @brief Updates the current mouse target position for aiming.
 * @param x X-coordinate of the mouse.
 * @param y Y-coordinate of the mouse.
 */
    void updateMouseTarget(int x, int y);

    Avatar *getItsAvatar() const;

    std::vector<Enemy *> getItsEnemies() const;

    std::vector<Projectile *> getItsProjectiles() const;

public slots:
    /**
 * @brief Core game loop executed on a timer tick; updates all game logic.
 */
    void GameLoop();
    void spawnEnemy();
};

#endif // GAME_H
