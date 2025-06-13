#include "gui.h"
#include <QKeyEvent>
#include <QPainter>
#include "katana.h"

int avatarHeight = 64;
int avatarWidth = 48;

enum Pos {RIGHT,LEFT,UP,DOWN};
Pos LastAvatarDir = RIGHT;

GUI::GUI(Game * aGame, QWidget *parent)
    : QWidget(parent), itsGame(aGame)
{
    setFixedSize(960,540);
    setMouseTracking(true);

    itsTimer = new QTimer(this);
    connect(itsTimer, SIGNAL(timeout()), this, SLOT(update()));
    itsTimer->start(17);
    connect(itsGame, &Game::gameOver, this, &GUI::onGameOver);

    mainMenu = new MainMenu(this);
    connect(mainMenu, &MainMenu::playSelected, this, &GUI::startGame);
    connect(mainMenu, &MainMenu::quitSelected, this, &GUI::close);

    boots.load(":/Pictures/boots.png");
    shield.load(":/Pictures/shield.png");
    syringe.load(":/Pictures/syringe.png");
    blood.load(":/Pictures/blood.png");
    pepper.load(":/Pictures/pepper.png");

    boss.load(":/Pictures/boss.png");
    circle.load(":/Pictures/circle.png");
    square.load(":/Pictures/square.png");
    triangle.load(":/Pictures/triangle.png");
    avatarR.load(":/Pictures/avatarR.png");
    avatarL.load(":/Pictures/avatarL.png");
    avatarU.load(":/Pictures/avatarU.png");
    avatarD.load(":/Pictures/avatarD.png");
    avatarRStand.load(":/Pictures/avatarRStand.png");
    avatarLStand.load(":/Pictures/avatarLStand.png");
    avatarUStand.load(":/Pictures/avatarUStand.png");
    avatarDStand.load(":/Pictures/avatarDStand.png");
    background.load(":/Pictures/background.png");
    proje.load(":/Pictures/proj.png");
    explosion.load(":/Pictures/explosion.png");
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

    if (mainMenu->isVisible()) {
        drawMainMenu(&painter);
        return;
    }

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
    if (dynamic_cast<Katana*>(itsGame->getItsWeapon()))
        drawKatana(&painter);
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
    // Handle key release events for keyboard direction keys
    if (event->key() == Qt::Key_Q)
        itsGame->getItsAvatar()->moveLeft(true);

    if (event->key() == Qt::Key_D)
        itsGame->getItsAvatar()->moveRight(true);

    if (event->key() == Qt::Key_Z)
        itsGame->getItsAvatar()->moveUp(true);

    if (event->key() == Qt::Key_S)
        itsGame->getItsAvatar()->moveDown(true);

    // If the game is over and the Game Over Menu (itsGOM) is active, handle player name input
    if (gameIsOver && itsGOM) {
        QString name = itsGOM->getPlayerName();

        // Handle Backspace key to delete last character of the player name
        if (event->key() == Qt::Key_Backspace) {
            if (!name.isEmpty()) {
                name.chop(1);
                itsGOM->setPlayerName(name);
                update();
            }
        } else {
            QString text = event->text();
            // Only add character if text is not empty and name length < 6
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
    // Handle key release events for keyboard direction keys
    if (event->key() == Qt::Key_Q)
        itsGame->getItsAvatar()->moveLeft(false);

    if (event->key() == Qt::Key_D)
        itsGame->getItsAvatar()->moveRight(false);

    if (event->key() == Qt::Key_Z)
        itsGame->getItsAvatar()->moveUp(false);

    if (event->key() == Qt::Key_S)
        itsGame->getItsAvatar()->moveDown(false);
}

void GUI::drawAvatar(QPainter *aPainter)
{
    Avatar * Av = itsGame->getItsAvatar();
    if(Av->getIsRight() && !Av->getIsLeft())
    {
        aPainter->drawImage(*itsGame->getItsAvatar()->getItsQRect(), avatarR);
        LastAvatarDir=RIGHT;
    }
    else if(Av->getIsLeft() && !Av->getIsRight())
    {
        aPainter->drawImage(*itsGame->getItsAvatar()->getItsQRect(), avatarL);
        LastAvatarDir=LEFT;
    }
    else if(Av->getIsUp() && !Av->getIsDown())
    {
        aPainter->drawImage(*itsGame->getItsAvatar()->getItsQRect(), avatarU);
        LastAvatarDir=UP;
    }
    else if(Av->getIsDown() && !Av->getIsUp())
    {
        aPainter->drawImage(*itsGame->getItsAvatar()->getItsQRect(), avatarD);
        LastAvatarDir=DOWN;
    }
    else
    {
        switch(LastAvatarDir)
        {
            case RIGHT :
                aPainter->drawImage(*itsGame->getItsAvatar()->getItsQRect(), avatarRStand);
                break;
            case LEFT :
                aPainter->drawImage(*itsGame->getItsAvatar()->getItsQRect(), avatarLStand);
                break;
            case UP :
                aPainter->drawImage(*itsGame->getItsAvatar()->getItsQRect(), avatarUStand);
                break;
            case DOWN :
                aPainter->drawImage(*itsGame->getItsAvatar()->getItsQRect(), avatarDStand);
                break;
        }
    }
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
        aPainter->drawImage(AD->getItsRectF(), explosion);
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
    painter->drawText(QRect(x + 20, y + 110, menuWidth, 20), Qt::AlignLeft, "Name (max 6 characters) :");
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
    painter->drawText(colRangX, yOffset, "Rank");
    painter->drawText(colNomX, yOffset, "Name");
    painter->drawText(colScoreX, yOffset, "Score");
    painter->drawText(colTempsX, yOffset, "Time");

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
    painter->drawText(replayBtn, Qt::AlignCenter, "Replay");
    painter->drawText(quitBtn, Qt::AlignCenter, "Quit");
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
    itsGame->getBackgroundMusicPlayer()->stop();
    itsGOM->getGameOverMusicPlayer()->setPosition(0);  // Remet au début
    itsGOM->getGameOverMusicPlayer()->play();
    update();
}

void GUI::restartGame()
{
    delete itsGame;
    itsGame = nullptr;

    itsGOM->isVisible = false;
    delete itsGOM;
    itsGOM = nullptr;

    mainMenu->setVisible(true);  // ← Affiche de nouveau le menu principal
    mainMenu->playMusic();
    gameIsOver = false;
}

void GUI::mousePressEvent(QMouseEvent* event)
{
    if (mainMenu->isVisible()) {
        mainMenu->handleClick(event->pos());
        return;
    }

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

void GUI::drawMainMenu(QPainter* painter)
{
    painter->setPen(Qt::white);
    painter->setBrush(Qt::black);
    painter->drawRect(rect());

    QFont titleFont("Arial", 28, QFont::Bold);
    painter->setFont(titleFont);
    painter->drawText(rect(), Qt::AlignTop | Qt::AlignHCenter, mainMenu->getTitle());

    QFont buttonFont("Arial", 14);
    painter->setFont(buttonFont);

    if (!mainMenu->getTitle().contains("weapon")) {
        painter->setBrush(Qt::darkGray);
        painter->drawRect(mainMenu->getPlayButtonRect());
        painter->drawRect(mainMenu->getQuitButtonRect());

        painter->drawText(mainMenu->getPlayButtonRect(), Qt::AlignCenter, "Play");
        painter->drawText(mainMenu->getQuitButtonRect(), Qt::AlignCenter, "Quit");
    } else {
        for (int i = 0; i < 4; ++i) {
            WeaponType wt = static_cast<WeaponType>(i);
            QRect btn = mainMenu->getWeaponButtonRect(wt);
            painter->setBrush(Qt::gray);
            painter->drawRect(btn);

            QString label;
            switch (wt) {
            case KATANA: label = "Katana"; break;
            case FIREBALL: label = "Fireball"; break;
            case ROCKETLAUNCHER: label = "Rocket Launcher"; break;
            case GUN: label = "Gun"; break;
            }

            painter->drawText(btn, Qt::AlignCenter, label);
        }
    }
}

void GUI::startGame(WeaponType type)
{
    currentWeaponType = type;
    itsGame = new Game(type);
    connect(itsGame, &Game::gameOver, this, &GUI::onGameOver);
    mainMenu->setVisible(false);
    gameIsOver = false;
}
