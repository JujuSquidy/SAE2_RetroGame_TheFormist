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
    connect(itsGame, &Game::gameOver, this, &GUI::onGameOver);
}

GUI::~GUI()
{
    itsTimer->stop();
    delete itsTimer;
    itsTimer = nullptr;

    delete itsGame;
    itsGame = nullptr;
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
    drawPowerUP(&painter);

    drawPlayerLifeBar(&painter, offsetX, offsetY, screenH);
    drawPlayerXPBar(&painter, offsetX, offsetY, screenH, screenW);
    drawScore(&painter, offsetX, offsetY, screenW);
    drawTimer(&painter, offsetX, offsetY, screenW);

    updateMousePos();
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

void GUI::drawAvatar(QPainter *aPainter)
{
    aPainter->setPen(QPen(QColor(0, 255, 127)));
    aPainter->setBrush(Qt::SolidPattern);

    aPainter->drawRect(*itsGame->getItsAvatar()->getItsQRect());
}

void GUI::drawEnemies(QPainter *aPainter)
{
    aPainter->setBrush(Qt::SolidPattern);
    const std::vector<Enemy*>& enemies = itsGame->getItsEnemies();
    for (const Enemy* enemy : enemies)
    {
        switch (enemy->getType())
        {
            case TRIANGLE :
                aPainter->setPen(QPen(QColor(191, 0, 255)));
                aPainter->drawRect(enemy->getItsRectF());
                break;

            case SQUARE :
                aPainter->setPen(Qt::red);
                aPainter->drawRect(enemy->getItsRectF());
                break;

            case CIRCLE :
                aPainter->setPen(QPen(QColor(107, 142, 35)));
                aPainter->drawRect(enemy->getItsRectF());
                break;

            case BOSS :
                aPainter->setPen(Qt::yellow);
                aPainter->drawRect(enemy->getItsRectF());
                break;
        }
    }
}

void GUI::drawProjectiles(QPainter *aPainter)
{
    aPainter->setPen(Qt::red);
    aPainter->setBrush(Qt::SolidPattern);

    const std::vector<Projectile*>& aProjectiles = itsGame->getItsAvatarProjectiles();

    for (const Projectile* proj : aProjectiles)
    {
        aPainter->drawRect(proj->getItsRectF());
    }

    const std::vector<Projectile*>& eProjectiles = itsGame->getItsEnemyProjectiles();

    for (const Projectile* proj : eProjectiles)
    {
        aPainter->drawRect(proj->getItsRectF());
    }
}

void GUI::drawPowerUP(QPainter *aPainter)
{
    aPainter->setBrush(Qt::SolidPattern);
    const std::vector<PowerUp*>& PowerUP = itsGame->getItsPowerUp();
    for (const PowerUp* PU : PowerUP)
    {
        if (PU->getIsPicked()==false)
        {
            switch (PU->getItsType())
            {
            case SHIELD:
                aPainter->setPen(Qt::blue);
                aPainter->drawRect(PU->getItsRectF());
                break;

            case SYRINGE :
                aPainter->setPen(Qt::red);
                aPainter->drawRect(PU->getItsRectF());
                break;

            case BLOOD :
                aPainter->setPen(Qt::green);
                aPainter->drawRect(PU->getItsRectF());
                break;

            case PEPPER :
                aPainter->setPen(Qt::yellow);
                aPainter->drawRect(PU->getItsRectF());
                break;

            case BOOTS :
                aPainter->setPen(QPen(QColor(255, 105, 180)));
                aPainter->drawRect(PU->getItsRectF());
                break;
            }
        }
    }
}

void GUI::drawPlayerLifeBar(QPainter *aPainter, float offsetX, float offsetY, int screenH)
{
    int currentHP = itsGame->getItsAvatar()->getItsHP();
    int maxHP = itsGame->getItsAvatar()->getItsMaxHP();

    int barWidth = 100;
    int barHeight = 10;


    int positionInScreenX = 10;
    int positionInScreenY = screenH - barHeight - 10;

    float barX = offsetX + positionInScreenX;
    float barY = offsetY + positionInScreenY;

    float filledWidth = barWidth * currentHP / maxHP;

    aPainter->setPen(Qt::black);
    aPainter->setBrush(Qt::red);
    aPainter->drawRect(QRectF(barX, barY, barWidth, barHeight));

    aPainter->setPen(Qt::NoPen);
    aPainter->setBrush(Qt::green);
    aPainter->drawRect(QRectF(barX, barY, filledWidth, barHeight));

    QFont font("Arial", 10, QFont::Bold);
    aPainter->setFont(font);
    aPainter->setPen(Qt::white);

    QString hpText = QString("HP: %1 / %2").arg(currentHP).arg(maxHP);
    aPainter->drawText(QPointF(barX, barY - 5), hpText);
}

void GUI::drawScore(QPainter *aPainter, float offsetX, float offsetY, int screenW)
{
    int currentScore = itsGame->getItsScore();
    QFont font("Arial", 16, QFont::Bold);
    aPainter->setFont(font);
    aPainter->setPen(Qt::white);  // Couleur du texte

    QString scoreText = QString("Score: %1").arg(currentScore);
    int textHeight = 30;
    QRectF textRect(offsetX, offsetY, screenW, textHeight);

    // Affiche le texte centré horizontalement et aligné en haut
    aPainter->drawText(textRect, Qt::AlignHCenter | Qt::AlignTop, scoreText);
}

void GUI::drawTimer(QPainter *aPainter, float offsetX, float offsetY, int screenW)
{
    QString timeText;
    if (gameIsOver) {
        timeText = itsFinalTimer;  // Affiche le temps figé
    } else {
        int currentTime = itsGame->getItsInGameTimer().elapsed();
        int seconds = (currentTime / 1000) % 60;
        int minutes = (currentTime / 60000);

        timeText = QString("Time: %1:%2")
                       .arg(minutes)
                       .arg(seconds, 2, 10, QChar('0'));
    }

    QFont font("Arial", 16, QFont::Bold);
    aPainter->setFont(font);
    aPainter->setPen(Qt::white);

    int lineHeight = 30;

    QRectF textRect(offsetX, offsetY + lineHeight, screenW, lineHeight); // Juste sous le score
    aPainter->drawText(textRect, Qt::AlignHCenter | Qt::AlignTop, timeText);
}

void GUI::drawPlayerXPBar(QPainter *aPainter, float offsetX, float offsetY, int screenH, int screenW)
{
    int currentXP = itsGame->getItsAvatar()->getItsXP();
    int maxXP = itsGame->getItsAvatar()->getItsMaxXP();
    int currentLevel = itsGame->getItsAvatar()->getItsLevel();

    int barWidth = 100;
    int barHeight = 10;


    int positionInScreenX = screenW - barWidth - 10;
    int positionInScreenY = screenH - barHeight - 10;

    float barX = offsetX + positionInScreenX;
    float barY = offsetY + positionInScreenY;

    float filledWidth = barWidth * currentXP / maxXP;

    aPainter->setPen(Qt::black);
    aPainter->setBrush(Qt::black);
    aPainter->drawRect(QRectF(barX, barY, barWidth, barHeight));

    aPainter->setPen(Qt::NoPen);
    aPainter->setBrush(Qt::blue);
    aPainter->drawRect(QRectF(barX, barY, filledWidth, barHeight));


    QFont font("Arial", 10, QFont::Bold);
    aPainter->setFont(font);
    aPainter->setPen(Qt::white);

    QString xpText = QString("XP: %1 / %2").arg(currentXP).arg(maxXP);
    QString levelText = QString("Level: %1").arg(currentLevel);

    aPainter->drawText(QPointF(barX, barY - 5), xpText);
    aPainter->drawText(QPointF(barX, barY - 20), levelText);  // Un peu plus haut
}

void GUI::updateMousePos()
{
    int halfWidth = width() / 2;
    int halfHeight = height() / 2;

    float newCameraX = itsGame->getItsAvatar()->getItsQRect()->center().x() - halfWidth;
    float newCameraY = itsGame->getItsAvatar()->getItsQRect()->center().y() - halfHeight;

    // Limiter aux bords du monde
    newCameraX = std::clamp(newCameraX, 0.0f, float(itsGame->getItsBorder().first - width()));
    newCameraY = std::clamp(newCameraY, 0.0f, float(itsGame->getItsBorder().second - height()));

    cameraPosition = QPointF(newCameraX, newCameraY);
    QPoint mouseInWindow = mapFromGlobal(QCursor::pos());
    QPointF mouseWorldPos = cameraPosition + mouseInWindow;
    itsGame->updateMouseTarget(mouseWorldPos.x(), mouseWorldPos.y());
}

void GUI::onGameOver()
{
    gameIsOver = true;
    int elapsedMs = itsGame->getItsInGameTimer().elapsed();  // Temps en millisecondes
    int seconds = (elapsedMs / 1000) % 60;
    int minutes = elapsedMs / 60000;

    itsFinalTimer = QString("%1:%2")
                        .arg(minutes)
                        .arg(seconds, 2, 10, QChar('0'));

    QMessageBox::information(this, "Game Over",
                             "Vous avez perdu !\nScore: " + QString::number(itsGame->getItsScore()) +
                                 "\nTime survived: " + itsFinalTimer);

    QMessageBox::StandardButton ret = QMessageBox::question(this, "Rejouer ?", "Voulez-vous recommencer ?", QMessageBox::Yes | QMessageBox::No);

    if (ret == QMessageBox::Yes)
    {
        restartGame();
    }else{
        close();
    }
}

void GUI::restartGame()
{
    delete itsGame;
    itsGame = new Game();
    connect(itsGame, &Game::gameOver, this, &GUI::onGameOver);
    gameIsOver = false;  // Reset
}
