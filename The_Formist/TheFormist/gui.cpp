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

    boots.load(":/Pictures/boots.png");
    shield.load(":/Pictures/shield.png");
    syringe.load(":/Pictures/syringe.png");
    blood.load(":/Pictures/blood.png");
    pepper.load(":/Pictures/pepper.png");

    boss.load(":/Pictures/boss.png");
    circle.load(":/Pictures/circle.png");
    square.load(":/Pictures/square.png");
    triangle.load(":/Pictures/triangle.png");
    avatar.load(":/Pictures/avatar.png");
    background.load(":/Pictures/background.png");
    proje.load(":/Pictures/proj.png");

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
    painter.save();  // Sauvegarde avant translation
    painter.translate(-offsetX, -offsetY);

    painter.drawImage(QRectF(0, 0, mapW, mapH), background);

    // Dessin relatif à la carte
    drawAreaDamage(&painter);
    drawAvatar(&painter);
    drawProjectiles(&painter);
    drawEnemies(&painter);
    drawKatana(&painter); //à voir pour mettre un for car se dessine tout le temps là sinon
    drawPowerUP(&painter);

    // === Partie HUD et Menu Game Over : coordonnées écran ===
    drawPlayerLifeBar(&painter, offsetX, offsetY, screenH);
    drawPlayerXPBar(&painter, offsetX, offsetY, screenH, screenW);
    drawScore(&painter, offsetX, offsetY, screenW);
    drawTimer(&painter, offsetX, offsetY, screenW);

    painter.restore();  // Revenir au repère écran

    if (itsGOM && itsGOM->isVisible)
    {
        drawGameOverMenu(&painter);  // NE DOIT PAS être affecté par la translation
    }

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

    if (gameIsOver && itsGOM) {
        QString name = itsGOM->getPlayerName();

        if (event->key() == Qt::Key_Backspace) {
            if (!name.isEmpty()) {
                name.chop(1);
                itsGOM->setPlayerName(name);
                update();
            }
        } else {
            QString text = event->text();
            if (!text.isEmpty() && name.length() < 6) {
                QChar c = text.at(0);
                if (c.isLetterOrNumber()) {
                    name.append(c.toUpper());
                    itsGOM->setPlayerName(name);
                    update();
                }
            }
        }
    }
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
    aPainter->drawImage(*itsGame->getItsAvatar()->getItsQRect(), avatar);
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
            aPainter->drawImage(enemy->getItsRectF(), triangle);

                break;

            case SQUARE :
                aPainter->drawImage(enemy->getItsRectF(), square);

                break;

            case CIRCLE :
                aPainter->drawImage(enemy->getItsRectF(), circle);

                break;

            case BOSS :
                aPainter->drawImage(enemy->getItsRectF(), boss);

                break;
        }
    }
}

void GUI::drawProjectiles(QPainter *aPainter)
{
    const std::vector<Projectile*>& aProjectiles = itsGame->getItsAvatarProjectiles();

    for (const Projectile* proj : aProjectiles)
    {
        aPainter->drawImage(proj->getItsRectF(), proje);
    }

    const std::vector<Projectile*>& eProjectiles = itsGame->getItsEnemyProjectiles();

    for (const Projectile* proj : eProjectiles)
    {
        aPainter->drawImage(proj->getItsRectF(), proje);
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
                aPainter->drawImage(PU->getItsRectF(), shield);
                break;
            case SYRINGE:
                aPainter->drawImage(PU->getItsRectF(), syringe);
                break;
            case BLOOD:
                aPainter->drawImage(PU->getItsRectF(), blood);
                break;
            case PEPPER:
                aPainter->drawImage(PU->getItsRectF(), pepper);
                break;
            case BOOTS:
                aPainter->drawImage(PU->getItsRectF(), boots);
                break;
            }

        }
    }
}

void GUI::drawAreaDamage(QPainter *aPainter)
{
    aPainter->setPen(QPen(QColor(255,165,0)));
    aPainter->setBrush(Qt::SolidPattern);
    for(AreaDamage * AD : itsGame->getItsAreaDamages())
        aPainter->drawRect(AD->getItsRectF());
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

void GUI::drawGameOverMenu(QPainter* painter)
{
    int screenWidth = width();
    int screenHeight = height();
    int menuWidth = 360;
    int menuHeight = 420;

    int x = (screenWidth - menuWidth) / 2;
    int y = (screenHeight - menuHeight) / 2;

    // Fond du menu
    QRect backgroundRect(x, y, menuWidth, menuHeight);
    painter->setOpacity(1.0);
    painter->setBrush(Qt::black);
    painter->setPen(Qt::white);
    painter->drawRect(backgroundRect);

    // Titre
    QFont titleFont("Arial", 14, QFont::Bold);
    painter->setFont(titleFont);
    painter->drawText(QRect(x, y + 10, menuWidth, 30), Qt::AlignCenter, "GAME OVER");

    // Score & temps
    painter->drawText(QRect(x + 20, y + 50, menuWidth, 30), Qt::AlignLeft, "Score : " + QString::number(itsGOM->getScore()));
    painter->drawText(QRect(x + 20, y + 80, menuWidth, 30), Qt::AlignLeft, "Time  : " + itsGOM->getTimeString());

    // Nom
    painter->drawText(QRect(x + 20, y + 110, menuWidth, 20), Qt::AlignLeft, "Nom (max 6 caractères) :");
    QRect nameInputRect(x + 20, y + 135, menuWidth - 40, 30);
    itsGOM->setNameInputRect(nameInputRect);
    painter->setBrush(Qt::white);
    painter->drawRect(nameInputRect);
    painter->setPen(Qt::black);
    painter->drawText(nameInputRect.adjusted(5, 0, 0, 0), Qt::AlignVCenter | Qt::AlignLeft, itsGOM->getPlayerName().left(6));

    painter->setPen(Qt::white);

    // Leaderboard
    QFont fixedFont("Courier New", 10);
    painter->setFont(fixedFont);

    int lineHeight = 20;
    // Largeur de chaque colonne
    int colRangW = 40;
    int colNomW = 80;
    int colScoreW = 60;
    int colTempsW = 60;

    int totalColsW = colRangW + colNomW + colScoreW + colTempsW;
    int startX = x + (menuWidth - totalColsW) / 2;

    int colRangX = startX;
    int colNomX = colRangX + colRangW;
    int colScoreX = colNomX + colNomW;
    int colTempsX = colScoreX + colScoreW;

    int yOffset = y + 200;

    // Légende
    painter->drawText(colRangX, yOffset, "Rang");
    painter->drawText(colNomX, yOffset, "Nom");
    painter->drawText(colScoreX, yOffset, "Score");
    painter->drawText(colTempsX, yOffset, "Temps");

    yOffset += lineHeight;

    // Scores
    const QVector<ScoreEntry>& topScores = itsGOM->getTopScores();
    for (int i = 0; i < topScores.size(); ++i) {
        const ScoreEntry& entry = topScores[i];
        painter->drawText(colRangX, yOffset, QString::number(i + 1) + ".");
        painter->drawText(colNomX, yOffset, entry.name.left(6));
        painter->drawText(colScoreX, yOffset, QString::number(entry.score));
        painter->drawText(colTempsX, yOffset, entry.time);
        yOffset += lineHeight;
    }

    // Boutons centrés
    int buttonWidth = 100;
    int spacing = 20;
    int totalButtonWidth = buttonWidth * 2 + spacing;
    int buttonStartX = x + (menuWidth - totalButtonWidth) / 2;
    int buttonY = y + menuHeight - 50;

    QRect replayBtn(buttonStartX, buttonY, buttonWidth, 30);
    QRect quitBtn(buttonStartX + buttonWidth + spacing, buttonY, buttonWidth, 30);

    itsGOM->setReplayButtonRect(replayBtn);
    itsGOM->setQuitButtonRect(quitBtn);

    painter->setBrush(Qt::gray);
    painter->setPen(Qt::white);
    painter->drawRect(replayBtn);
    painter->drawRect(quitBtn);
    painter->drawText(replayBtn, Qt::AlignCenter, "Rejouer");
    painter->drawText(quitBtn, Qt::AlignCenter, "Quitter");
}

void GUI::onGameOver()
{
    int elapsedMs = itsGame->getItsInGameTimer().elapsed();
    QString timeStr = QString("%1:%2").arg(elapsedMs / 60000).arg((elapsedMs / 1000) % 60, 2, 10, QChar('0'));

    gameIsOver = true;

    itsGOM = new GameOverMenu(itsGame->getItsScore(), timeStr, this);
    connect(itsGOM, &GameOverMenu::replayRequested, this, &GUI::restartGame);
    connect(itsGOM, &GameOverMenu::quitRequested, this, &GUI::close);
    itsGOM->isVisible = true;
    update();
}

void GUI::restartGame()
{
    delete itsGame;
    itsGame = new Game();
    connect(itsGame, &Game::gameOver, this, &GUI::onGameOver);
    itsGOM->isVisible = false;
    gameIsOver = false;  // Reset
}

void GUI::mousePressEvent(QMouseEvent* event)
{
    if (itsGOM && itsGOM->isVisible)
    {
        itsGOM->handleClick(event->pos());
        return;
    }
}

void GUI::drawKatana(QPainter *aPainter)
{
    Weapon* weapon = itsGame->getItsWeapon();
    if (!weapon) return;

    auto avatarPos = itsGame->getItsAvatar()->getItsPosition();

    // Récupérer la position cible
    std::pair<float, float> targetPos = itsGame->getMouseTarget(); // à adapter selon ta fonction

    float dx = targetPos.first - (avatarPos.first + avatarWidth / 2);
    float dy = targetPos.second - (avatarPos.second + avatarHeight / 2);
    float angle = std::atan2(dy, dx);  // angle en radians

    // Taille du katana
    float width = 100;
    float height = 10;

    // Position du katana : on veut que le katana soit attaché au centre de l'avatar
    float cx = avatarPos.first + avatarWidth / 2;
    float cy = avatarPos.second + avatarHeight / 2;

    aPainter->save();

    // Translation vers le centre de l'avatar
    aPainter->translate(cx, cy);
    // Rotation pour orienter le katana vers la souris
    aPainter->rotate(angle * 180 / M_PI);

    // Dessin du katana, décalé pour que le "poignée" soit au centre
    QRectF rect(0, -height/2, width, height);

    aPainter->setPen(Qt::NoPen);
    aPainter->setBrush(Qt::yellow);
    aPainter->drawRect(rect);

    aPainter->restore();
}
