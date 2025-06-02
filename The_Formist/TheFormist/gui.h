#ifndef GUI_H
#define GUI_H

#include "game.h"
#include <QWidget>

class GUI : public QWidget
{
    Q_OBJECT
private:
    Game* itsGame;
    QTimer itsTimer;
protected:
    void paintEvent(QPaintEvent* event);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent* event);
public:
    GUI(Game aGame, QWidget *parent = nullptr);
    ~GUI();

private:
    void drawAvatar(QPainter * aPainter);
    void drawEnemies(QPainter * aPainter);
    void drawProjectiles(QPainter * aPainter);
    void drawPowerUP(QPainter * aPainter);
};
#endif // GUI_H
