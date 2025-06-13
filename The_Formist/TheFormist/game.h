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

#include <QMediaPlayer>
#include <QAudioOutput>

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
 * @brief Timer used to manage enemy spawns.
 */
    QTimer *itsEnemyTimer;

    /**
 * @brief Int used to set the ennemies's spawn time.
 */
    int itsEnemySpawnTime = 1500;

    /**
 * @brief Float used to set the multplier for ennemies's HP.
 */
    float itsEnemyHPMult = 1;

    /**
 * @brief Float used to set the multplier for ennemies's given score.
 */
    float itsScoreMult = 1;

/**
 * @brief Timer used to manage power-up spawns.
 */
    QTimer *itsPowerUpTimer;

    /**
 * @brief Timer used to show time elapsed in the game.
 */
    QTimer *itsTimer;

/**
 * @brief Timer tracking in-game time.
 */
    QElapsedTimer *itsInGameTimer;

/**
 * @brief Boolean ndicate whether the boss has spawned.
 */
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

/**
 * @brief List of active area damage instances in the game.
 */
    std::vector<AreaDamage*> itsAreaDamages;

    /**
 * @brief The latest target position from the mouse (used for aiming).
 */
    std::pair<int,int> mouseTarget;

/**
 * @brief Dimensions of the game window (width, height).
 */
    std::pair<int,int> gameWindowSize;

/**
 * @brief Timer used to manage the temporary speed boost.
 */
    QElapsedTimer bootsTimer;

/**
 * @brief Boolean indicating whether a temporary speeed boost is currently active.
 */
    bool bootsActive;

/**
 * @brief Background music player.
 */
    QMediaPlayer* backgroundMusicPlayer;

/**
 * @brief Audio output device for the music.
 */
    QAudioOutput* audioOutput;


public:
/**
 * @brief Constructs the Game object and initializes components.
 * @param type The weapon type selected at game start.
 * @param parent The parent QObject, if any.
 */
    Game(WeaponType type, QObject *parent = nullptr);

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

/**
 * @brief Gets the current score.
 * @return The score as a long integer.
 */
    long getItsScore() const;

/**
 * @brief Increases the player's score.
 * @param aScore Amount to add to the score.
 */
    void AddScore(long aScore);

/**
 * @brief Gets the in-game timer.
 * @return QElapsedTimer object.
 */
    QElapsedTimer getItsInGameTimer() const;

/**
 * @brief Gets the current mouse target position.
 * @return A pair of integers (x, y).
 */
    std::pair<int, int> getMouseTarget() const;

/**
 * @brief Gets the list of active power-ups in the game.
 * @return Vector of pointers to PowerUp objects.
 */
    std::vector<PowerUp *> getItsPowerUp() const;

/**
 * @brief Updates temporary boosts and their state.
 */
    void updateTemporaryBoosts();

/**
 * @brief Gets the list of active area damage zones.
 * @return Vector of pointers to AreaDamage objects.
 */
    std::vector<AreaDamage *> getItsAreaDamages() const;

/**
 * @brief Gets the background music player.
 * @return Pointer to QMediaPlayer.
 */
    QMediaPlayer *getBackgroundMusicPlayer() const;

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

/**
 * @brief Signal emitted to pause the game.
 */
    void pauseGame();

};

#endif // GAME_H
