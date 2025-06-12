#ifndef MAINMENU_H
#define MAINMENU_H

#include "weapon.h"
#include <QObject>
#include <QRect>
#include <QString>
#include <QMouseEvent>

class MainMenu : public QObject
{
    Q_OBJECT

public:
    explicit MainMenu(QObject* parent = nullptr);

    void handleClick(const QPoint& pos);
    bool isVisible() const;
    void setVisible(bool visible);

    QString getTitle() const;
    QRect getPlayButtonRect() const;
    QRect getQuitButtonRect() const;
    QRect getWeaponButtonRect(WeaponType type) const;

private:
    bool visible;
    bool weaponSelection;

    QRect playBtn, quitBtn;
    QRect katanaBtn, fireballBtn, rocketBtn, gunBtn;

signals:
    void playSelected(WeaponType);
    void quitSelected();
};

#endif // MAINMENU_H
