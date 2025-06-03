#include "gui.h"

GUI::GUI(Game * aGame, QWidget *parent)
    : QWidget(parent), itsGame(aGame)
{
    setMouseTracking(true);
}

GUI::~GUI()
{

}

void GUI::paintEvent(QPaintEvent *event)
{

}

void GUI::keyPressEvent(QKeyEvent *event)
{

}

void GUI::keyReleaseEvent(QKeyEvent *event)
{

}

void GUI::mouseMoveEvent(QMouseEvent* event)
{
    QPoint pos = event->pos();
    itsGame->updateMouseTarget(pos.x(), pos.y());
}

void GUI::drawAvatar(QPainter *aPainter)
{

}

void GUI::drawEnemies(QPainter *aPainter)
{

}

void GUI::drawProjectiles(QPainter *aPainter)
{

}

void GUI::drawPowerUP(QPainter *aPainter)
{

}
