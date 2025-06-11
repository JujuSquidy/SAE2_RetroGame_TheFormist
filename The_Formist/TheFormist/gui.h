#ifndef GUI_H
#define GUI_H

#include "game.h"
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
     * @brief Pointer to the Game instance that contains game logic and state.
     */
    Game* itsGame;

    /**
     * @brief Qt timer that regularly triggers screen updates and game loop refresh.
     */
    QTimer* itsTimer;

    QString itsFinalTimer;

    bool gameIsOver = false;

    QPointF cameraPosition; // en haut à gauche du viewport dans le monde

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
 * @brief Slot triggered when the game is over.
 *
 * Handles any cleanup or UI changes needed when the game ends.
 */
    void onGameOver();

    /**
 * @brief Restarts the game.
 *
 * Resets the game state, reinitializes objects, and starts the game loop again.
 */
    void restartGame();


private:
    /**
 * @brief Draws the avatar on the screen.
 * @param aPainter Painter used for rendering.
 */
    void drawAvatar(QPainter * aPainter);

    /**
 * @brief Draws all enemies on the screen.
 * @param aPainter Painter used for rendering.
 */
    void drawEnemies(QPainter * aPainter);

    /**
 * @brief Draws all active projectiles on the screen.
 * @param aPainter Painter used for rendering.
 */
    void drawProjectiles(QPainter * aPainter);

    /**
 * @brief Draws the active power-up on the screen.
 * @param aPainter Painter used for rendering.
 */
    void drawPowerUP(QPainter * aPainter);

    void drawAreaDamage(QPainter * aPainter);

    /**
 * @brief Draws the player life bar.
 * @param aPainter ainter used for rendering.
 */
    void drawPlayerLifeBar(QPainter * aPainter,float offsetX,float offsetY,int screenH);

    void drawScore(QPainter *aPainter, float offsetX, float offsetY, int screenW);

    void drawPlayerXPBar(QPainter *aPainter, float offsetX, float offsetY, int screenH, int screenW);

    void drawTimer(QPainter *aPainter, float offsetX, float offsetY, int screenW);

    void updateMousePos();
};
#endif // GUI_H
