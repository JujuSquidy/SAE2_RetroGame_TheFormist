#ifndef GAME_H
#define GAME_H

#include <QTimer>
#include "areadamage.h"
#include "avatar.h"
#include "enemy.h"
#include "powerup.h"
#include "projectile.h"
#include <QElapsedTimer>
#include "weapon.h"

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
 * @brief Timer used to manage enemies apparition
 */
    QTimer *itsEnemyTimer;

    QTimer *itsPowerUpTimer;

    /**
 * @brief Timer used to show time elapsed in the game.
 */
    QTimer *itsTimer;

    QElapsedTimer *itsInGameTimer;

    int NoBoss = 1;

    /**
 * @brief Defines the game area boundaries (width, height).
 */
    std::pair<int,int> itsBorder;

    /**
 * @brief Stores the player's current score.
 */
    long int itsScore = 0;

    /**
 * @brief List of active player projectiles in the game.
 */
    std::vector<Projectile*> itsAvatarProjectiles;

    /**
 * @brief List of active enemies projectiles in the game.
 */
    std::vector<Projectile*> itsEnemyProjectiles;

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
 * @brief List of active PowerUP in the game.
 */
    std::vector<PowerUp*> itsPowerUp;

    std::vector<AreaDamage*> itsAreaDamages;

    /**
 * @brief The latest target position from the mouse (used for aiming).
 */
    std::pair<int,int> mouseTarget;

    std::pair<int,int> gameWindowSize;

    QElapsedTimer bootsTimer;

    bool bootsActive;

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

    /**
 * @brief Gets the player's avatar.
 * @return Pointer to the Avatar object.
 */
    Avatar *getItsAvatar() const;

    /**
 * @brief Gets the current weapon used by the avatar.
 * @return Pointer to the Weapon object.
 */
    Weapon *getItsWeapon() const;

    /**
 * @brief Gets the list of enemies currently in the game.
 * @return Vector of pointers to Enemy objects.
 */
    std::vector<Enemy *> getItsEnemies() const;

    /**
 * @brief Gets the projectiles fired by the avatar.
 * @return Vector of pointers to Projectile objects.
 */
    std::vector<Projectile *> getItsAvatarProjectiles() const;

    /**
 * @brief Gets the game world border dimensions.
 * @return Pair of integers representing width and height.
 */
    std::pair<int,int> getItsBorder() const;

    /**
 * @brief Gets the projectiles fired by enemies.
 * @return Vector of pointers to Projectile objects.
 */
    std::vector<Projectile *> getItsEnemyProjectiles() const;

    long getItsScore() const;

    void AddScore(long aScore);

    QElapsedTimer getItsInGameTimer() const;


    std::vector<PowerUp *> getItsPowerUp() const;

    void updateTemporaryBoosts();

    std::vector<AreaDamage *> getItsAreaDamages() const;

public slots:
    /**
 * @brief Core game loop executed on a timer tick; updates all game logic.
 */
    void GameLoop();

    /**
 * @brief Spawns a new enemy in the game world.
 */
    void spawnEnemy();

    /**
 * @brief Handles logic for applying or spawning power-ups.
 */
    void spawnPowerUP();

    /**
 * @brief Applies upgrades to the avatar or weapon when appropriate.
 */
    void upgrade();

signals:
    /**
 * @brief Signal emitted when the game is over.
 */
    void gameOver();

};

#endif // GAME_H
