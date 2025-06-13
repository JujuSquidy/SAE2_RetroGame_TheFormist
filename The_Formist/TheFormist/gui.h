#ifndef GUI_H
#define GUI_H

#include "game.h"
#include "gameovermenu.h"
#include "mainmenu.h"
#include <QMouseEvent>
#include <QWidget>
#include <QMessageBox>

/**
 * @class GUI
 * @brief Main graphical user interface for rendering the game using Qt.
 *
 * The GUI class inherits from QWidget and is responsible for rendering game entities
 * (avatar, enemies, projectiles, power-ups) and handling user input (keyboard and mouse).
 * It continuously updates the game view using a timer.
 */
class GUI : public QWidget
{
    Q_OBJECT

private:
/**
 * @brief Pointer to the main Game logic handler.
 */
    Game* itsGame;

/**
 * @brief Pointer to the Game Over menu UI.
 */
    GameOverMenu* itsGOM = nullptr;

/**
 * @brief Pointer to the Main Menu UI.
 */
    MainMenu* mainMenu;

/**
 * @brief Timer used to trigger game updates and rendering.
 */
    QTimer* itsTimer;

/**
 * @brief Formatted string of the final gameplay time.
 */
    QString itsFinalTimer;

/**
 * @brief Boolean indicating whether the game is over.
 */
    bool gameIsOver = false;

/**
 * @brief Top-left camera position in the game world.
 */
    QPointF cameraPosition;

/**
 * @brief Currently selected weapon type for the avatar.
 */
    WeaponType currentWeaponType;

    // Game element sprites

/**
 * @brief Image representing the boots power-up.
 */
    QImage boots;

/**
 * @brief Image representing the shield power-up.
 */
    QImage shield;

/**
 * @brief Image representing the syringe power-up.
 */
    QImage syringe;

/**
 * @brief Image for the blood bootle power-up.
 */
    QImage blood;

/**
 * @brief Image for the pepper power-up.
 */
    QImage pepper;

/**
 * @brief Image used for rendering boss enemies.
 */
    QImage boss;

/**
 * @brief Image representing a circular enemy.
 */
    QImage circle;

/**
 * @brief Image representing a triangular enemy.
 */
    QImage triangle;

/**
 * @brief Image representing a square enemy.
 */
    QImage square;

/**
 * @brief Avatar image facing left.
 */
    QImage avatarL;

/**
 * @brief Avatar image facing right.
 */
    QImage avatarR;

/**
 * @brief Avatar image facing up.
 */
    QImage avatarU;

/**
 * @brief Avatar image facing down.
 */
    QImage avatarD;

/**
 * @brief Avatar standing idle facing left.
 */
    QImage avatarLStand;

/**
 * @brief Avatar standing idle facing right.
 */
    QImage avatarRStand;

/**
 * @brief Avatar standing idle facing up.
 */
    QImage avatarUStand;

/**
 * @brief Avatar standing idle facing down.
 */
    QImage avatarDStand;

/**
 * @brief Image used as the background of the game scene.
 */
    QImage background;

/**
 * @brief Image used for rendering projectiles.
 */
    QImage proje;
    QImage explosion;

public:
/**
 * @brief Constructs the GUI and links it to a Game instance.
 * @param aGame Pointer to the Game object to be rendered and interacted with.
 * @param parent Optional Qt parent widget (defaults to nullptr).
 */
    GUI(Game * aGame, QWidget *parent = nullptr);

/**
 * @brief Destructor that cleans up resources.
 */
    ~GUI();

protected:
/**
 * @brief Handles the paint event to draw the game elements.
 * @param event Paint event from Qt.
 */
    void paintEvent(QPaintEvent* event) override;

/**
 * @brief Handles key press events for controlling the avatar or actions.
 * @param event Key event containing the pressed key.
 */
    void keyPressEvent(QKeyEvent * event) override;

/**
 * @brief Handles key release events to stop actions or movement.
 * @param event Key event containing the released key.
 */
    void keyReleaseEvent(QKeyEvent* event) override;

/**
 * @brief Handles the end-of-game logic and menu display.
 */
    void onGameOver();

/**
 * @brief Restarts the game by resetting state and UI.
 */
    void restartGame();

/**
 * @brief Handles mouse click events.
 * @param event Mouse event with click information.
 */
    void mousePressEvent(QMouseEvent* event) override;

private:
/**
 * @brief Draws the avatar on the screen.
 * @param aPainter Painter used for rendering.
 */
    void drawAvatar(QPainter * aPainter);

/**
 * @brief Draws the katana weapon effects or sprite.
 * @param aPainter Painter used for rendering.
 */
    void drawKatana(QPainter * aPainter);

/**
 * @brief Draws all enemies currently in the game.
 * @param aPainter Painter used for rendering.
 */
    void drawEnemies(QPainter * aPainter);

/**
 * @brief Draws all active projectiles currently in the game.
 * @param aPainter Painter used for rendering.
 */
    void drawProjectiles(QPainter * aPainter);

/**
 * @brief Draws the active power-ups on the screen.
 * @param aPainter Painter used for rendering.
 */
    void drawPowerUP(QPainter * aPainter);

/**
 * @brief Draws any active area damage effects.
 * @param aPainter Painter used for rendering.
 */
    void drawAreaDamage(QPainter * aPainter);

/**
 * @brief Draws the player’s health bar.
 * @param aPainter Painter used for rendering.
 * @param offsetX X offset for positioning.
 * @param offsetY Y offset for positioning.
 * @param screenH Height of the screen or UI area.
 */
    void drawPlayerLifeBar(QPainter * aPainter, float offsetX, float offsetY, int screenH);

/**
 * @brief Draws the current score on the screen.
 * @param aPainter Painter used for rendering.
 * @param offsetX X offset for positioning.
 * @param offsetY Y offset for positioning.
 * @param screenW Width of the screen or UI area.
 */
    void drawScore(QPainter *aPainter, float offsetX, float offsetY, int screenW);

/**
 * @brief Draws the player experience (XP) bar.
 * @param aPainter Painter used for rendering.
 * @param offsetX X offset for positioning.
 * @param offsetY Y offset for positioning.
 * @param screenH Height of the screen or UI area.
 * @param screenW Width of the screen or UI area.
 */
    void drawPlayerXPBar(QPainter *aPainter, float offsetX, float offsetY, int screenH, int screenW);

/**
 * @brief Draws the game timer on the screen.
 * @param aPainter Painter used for rendering.
 * @param offsetX X offset for positioning.
 * @param offsetY Y offset for positioning.
 * @param screenW Width of the screen or UI area.
 */
    void drawTimer(QPainter *aPainter, float offsetX, float offsetY, int screenW);

/**
 * @brief Draws the Game Over menu UI.
 * @param painter Painter used for rendering.
 */
    void drawGameOverMenu(QPainter* painter);

    /**
 * @brief Draws the Main Menu UI.
 * @param painter Painter used for rendering.
 */
    void drawMainMenu(QPainter* painter);

    /**
 * @brief Starts the game with a selected weapon type.
 * @param type The WeaponType to initialize.
 */
    void startGame(WeaponType type);

    /**
 * @brief Updates the current mouse position relative to the game view.
 */
    void updateMousePos();
};
#endif // GUI_H
