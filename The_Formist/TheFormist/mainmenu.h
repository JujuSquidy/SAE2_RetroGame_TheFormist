#ifndef MAINMENU_H
#define MAINMENU_H

#include "weapon.h"
#include <QObject>
#include <QRect>
#include <QString>
#include <QMouseEvent>
#include <QMediaPlayer>
#include <QAudioOutput>


    /**
 * @class MainMenu
 * @brief Manages the main menu interface, including weapon selection and menu interactions.
 *
 * Handles user input for the main menu, button interactions, and plays background menu music.
 */
class MainMenu : public QObject
{
    Q_OBJECT

public:
    /**
 * @brief Constructs the MainMenu object.
 * @param parent Optional QObject parent.
 */
    MainMenu(QObject* parent = nullptr);

    /**
 * @brief Handles mouse click events within the menu.
 * @param pos The position of the mouse click.
 */
    void handleClick(const QPoint& pos);

    /**
 * @brief Returns whether the menu is currently visible.
 * @return True if visible, false otherwise.
 */
    bool isVisible() const;

    /**
 * @brief Sets the visibility of the menu.
 * @param visible True to show the menu, false to hide.
 */
    void setVisible(bool visible);

    /**
 * @brief Gets the title text of the menu.
 * @return The menu title as a QString.
 */
    QString getTitle() const;

    /**
 * @brief Returns the bounding rectangle for the Play button.
 * @return QRect representing the Play button area.
 */
    QRect getPlayButtonRect() const;

    /**
 * @brief Returns the bounding rectangle for the Quit button.
 * @return QRect representing the Quit button area.
 */
    QRect getQuitButtonRect() const;

    /**
 * @brief Returns the bounding rectangle for a specific weapon selection button.
 * @param type The weapon type.
 * @return QRect representing the weapon button area.
 */
    QRect getWeaponButtonRect(WeaponType type) const;

    /**
 * @brief Starts playing the menu background music.
 */
    void playMusic();

private:
    /**
 * @brief Indicates if the main menu is visible.
 */
    bool visible;

    /**
 * @brief Flag indicating if the weapon selection menu is active.
 */
    bool weaponSelection;

    /**
 * @brief Bounding rectangle for the Play button.
 */
    QRect playBtn;

    /**
 * @brief Bounding rectangle for the Quit button.
 */
    QRect quitBtn;

    /**
 * @brief Bounding rectangle for the Katana weapon button.
 */
    QRect katanaBtn;

    /**
 * @brief Bounding rectangle for the Fireball weapon button.
 */
    QRect fireballBtn;

    /**
 * @brief Bounding rectangle for the Rocket weapon button.
 */
    QRect rocketBtn;

    /**
 * @brief Bounding rectangle for the Gun weapon button.
 */
    QRect gunBtn;

    /**
 * @brief Media player for background menu music.
 */
    QMediaPlayer* menuMusicPlayer;

    /**
 * @brief Audio output for the menu music player.
 */
    QAudioOutput* audioOutput;

signals:
    /**
 * @brief Signal emitted when the play button is selected with a weapon type.
 * @param type The chosen WeaponType.
 */
    void playSelected(WeaponType type);

    /**
 * @brief Signal emitted when the quit button is selected.
 */
    void quitSelected();
};

#endif // MAINMENU_H
