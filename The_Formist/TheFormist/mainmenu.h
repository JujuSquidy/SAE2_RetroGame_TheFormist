#ifndef MAINMENU_H
#define MAINMENU_H

#include "weapon.h"
#include <QObject>
#include <QRect>
#include <QString>
#include <QMouseEvent>
#include <QMediaPlayer>
#include <QAudioOutput>


class MainMenu : public QObject
{
    Q_OBJECT

public:
    MainMenu(QObject* parent = nullptr);

    void handleClick(const QPoint& pos);
    bool isVisible() const;
    void setVisible(bool visible);

    QString getTitle() const;
    QRect getPlayButtonRect() const;
    QRect getQuitButtonRect() const;
    QRect getWeaponButtonRect(WeaponType type) const;
    void playMusic();


private:
    bool visible;
    bool weaponSelection;

    QRect playBtn, quitBtn;
    QRect katanaBtn, fireballBtn, rocketBtn, gunBtn;

    QMediaPlayer* menuMusicPlayer;
    QAudioOutput* audioOutput;

signals:
    void playSelected(WeaponType);
    void quitSelected();
};

#endif // MAINMENU_H
