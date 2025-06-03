#include "gui.h"
#include <QKeyEvent>
#include <QPainter>
#include <iostream>

int avatarHeight = 30;
int avatarWidth = 30;

GUI::GUI(Game * aGame, QWidget *parent)
    : QWidget(parent), itsGame(aGame)
{
    setMouseTracking(true);
    setFixedSize(960, 540);

    itsTimer = new QTimer(this);
    connect(itsTimer, SIGNAL(timeout()), this, SLOT(update()));
    itsTimer->start(33);
}

GUI::~GUI()
{
    delete itsGame;
    delete itsTimer;
}

void GUI::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    painter.setBrushOrigin(itsGame->getItsAvatar()->getItsPosition().first+avatarWidth/2, itsGame->getItsAvatar()->getItsPosition().second+avatarHeight/2);

    drawAvatar(&painter);
}

void GUI::keyPressEvent(QKeyEvent *event)
{
    // Handle key press events for left and right arrow keys
    if (event->key() == Qt::Key_Left)
    {
        itsGame->getItsAvatar()->moveLeft(true);
        std::cout << "Gauche" << std::endl;
    }
    if (event->key() == Qt::Key_Right)
    {
        itsGame->getItsAvatar()->moveRight(true);
        std::cout << "Droite" << std::endl;
    }
    if (event->key() == Qt::Key_Up)
    {
        itsGame->getItsAvatar()->moveUp(true);
        std::cout << "Haut" << std::endl;
    }
    if (event->key() == Qt::Key_Down)
    {
        itsGame->getItsAvatar()->moveDown(true);
        std::cout << "Bas" << std::endl;
    }
}

void GUI::keyReleaseEvent(QKeyEvent *event)
{
    // Handle key release events for left and right arrow keys
    if (event->key() == Qt::Key_Left)
    {
        itsGame->getItsAvatar()->moveLeft(false);
        std::cout << "GaucheL" << std::endl;
    }
    if (event->key() == Qt::Key_Right)
    {
        itsGame->getItsAvatar()->moveRight(false);
        std::cout << "DroiteL" << std::endl;
    }
    if (event->key() == Qt::Key_Up)
    {
        itsGame->getItsAvatar()->moveUp(false);
        std::cout << "HautL" << std::endl;
    }
    if (event->key() == Qt::Key_Down)
    {
        itsGame->getItsAvatar()->moveDown(false);
        std::cout << "BasL" << std::endl;
    }
}

void GUI::mouseMoveEvent(QMouseEvent* event)
{
    QPoint pos = event->pos();
    itsGame->updateMouseTarget(pos.x(), pos.y());
}

void GUI::drawAvatar(QPainter *aPainter)
{
    aPainter->setPen(Qt::blue);
    aPainter->setBrush(Qt::SolidPattern);

    aPainter->drawRect(*itsGame->getItsAvatar()->getItsQRect());
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
