#include "gui.h"
#include <QKeyEvent>
#include <QPainter>

int avatarHeight = 30;
int avatarWidth = 30;

GUI::GUI(Game * aGame, QWidget *parent)
    : QWidget(parent), itsGame(aGame)
{
    setFixedSize(960,540);
    setMouseTracking(true);

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

    // Position de l'avatar
    std::pair<float, float> avatarPos = itsGame->getItsAvatar()->getItsPosition();

    // Taille de la zone d'affichage
    int screenW = width();
    int screenH = height();

    // Taille de la carte
    int mapW = itsGame->getItsBorder().first;
    int mapH = itsGame->getItsBorder().second;

    // Calcul de l’offset pour centrer l’avatar
    float offsetX = avatarPos.first + avatarWidth/2 - screenW / 2;
    float offsetY = avatarPos.second + avatarHeight/2 - screenH / 2;

    // Empêcher l’offset de sortir de la carte
    if (offsetX < 0) offsetX = 0;
    if (offsetY < 0) offsetY = 0;
    if (offsetX > mapW - screenW) offsetX = mapW - screenW;
    if (offsetY > mapH - screenH) offsetY = mapH - screenH;

    // Appliquer la translation inversée
    painter.translate(-offsetX, -offsetY);

    // Dessin relatif à la carte
    drawAvatar(&painter);
    drawProjectiles(&painter);
    drawEnemies(&painter);
}

void GUI::keyPressEvent(QKeyEvent *event)
{
    // Handle key press events for left and right arrow keys
    if (event->key() == Qt::Key_Left)
        itsGame->getItsAvatar()->moveLeft(true);

    if (event->key() == Qt::Key_Right)
        itsGame->getItsAvatar()->moveRight(true);

    if (event->key() == Qt::Key_Up)
        itsGame->getItsAvatar()->moveUp(true);

    if (event->key() == Qt::Key_Down)
        itsGame->getItsAvatar()->moveDown(true);
}

void GUI::keyReleaseEvent(QKeyEvent *event)
{
    // Handle key release events for left and right arrow keys
    if (event->key() == Qt::Key_Left)
        itsGame->getItsAvatar()->moveLeft(false);

    if (event->key() == Qt::Key_Right)
        itsGame->getItsAvatar()->moveRight(false);

    if (event->key() == Qt::Key_Up)
        itsGame->getItsAvatar()->moveUp(false);

    if (event->key() == Qt::Key_Down)
        itsGame->getItsAvatar()->moveDown(false);
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
    aPainter->setBrush(Qt::SolidPattern);
    const std::vector<Enemy*>& enemies = itsGame->getItsEnemies();
    for (const Enemy* enemi : enemies)
    {
        switch (enemi->getType())
        {
            case TRIANGLE :
                aPainter->setPen(Qt::blue);
                aPainter->drawRect(enemi->getItsRectF());
                break;

            case SQUARE :
                aPainter->setPen(Qt::red);
                aPainter->drawRect(enemi->getItsRectF());
                break;

            case CIRCLE :
                aPainter->setPen(Qt::green);
                aPainter->drawRect(enemi->getItsRectF());
                break;

            case BOSS :
                aPainter->setPen(Qt::yellow);
                aPainter->drawRect(enemi->getItsRectF());
                break;
        }
    }
}

void GUI::drawProjectiles(QPainter *aPainter)
{
    aPainter->setPen(Qt::red);
    aPainter->setBrush(Qt::SolidPattern);

    const std::vector<Projectile*>& projectiles = itsGame->getItsProjectiles();

    for (const Projectile* proj : projectiles)
    {
        aPainter->drawRect(proj->getItsRectF());
    }
}
void GUI::drawPowerUP(QPainter *aPainter)
{

}
