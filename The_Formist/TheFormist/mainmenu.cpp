#include "mainmenu.h"

MainMenu::MainMenu(QObject* parent)
    : QObject(parent), visible(true), weaponSelection(false)
{
    playBtn = QRect(330, 200, 300, 50);
    quitBtn = QRect(330, 270, 300, 50);

    katanaBtn = QRect(100, 200, 160, 50);
    fireballBtn = QRect(280, 200, 160, 50);
    rocketBtn = QRect(460, 200, 160, 50);
    gunBtn = QRect(640, 200, 160, 50);

    menuMusicPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    menuMusicPlayer->setAudioOutput(audioOutput);

    // Exemple avec un fichier dans les ressources
    menuMusicPlayer->setSource(QUrl("qrc:/Music/Menu.mp3"));
    audioOutput->setVolume(1);  // Volume entre 0.0 et 1.0
    menuMusicPlayer->play();
}

bool MainMenu::isVisible() const { return visible; }
void MainMenu::setVisible(bool v) { visible = v; }

QString MainMenu::getTitle() const {
    return weaponSelection ? "Choose your weapon" : "The Formist";
}

QRect MainMenu::getPlayButtonRect() const { return playBtn; }
QRect MainMenu::getQuitButtonRect() const { return quitBtn; }

QRect MainMenu::getWeaponButtonRect(WeaponType type) const {
    switch (type) {
    case KATANA: return katanaBtn;
    case FIREBALL: return fireballBtn;
    case ROCKETLAUNCHER: return rocketBtn;
    case GUN: return gunBtn;
    }
    return QRect();
}

void MainMenu::handleClick(const QPoint& pos)
{
    if (!weaponSelection) {
        if (playBtn.contains(pos)) {
            weaponSelection = true;
        }
        else if (quitBtn.contains(pos)) {
            emit quitSelected();
        }
    } else {
        if (katanaBtn.contains(pos)) {
            menuMusicPlayer->stop();
            emit playSelected(KATANA);
        }
        else if (fireballBtn.contains(pos)) {
            menuMusicPlayer->stop();
            emit playSelected(FIREBALL);
        }
        else if (rocketBtn.contains(pos)) {
            menuMusicPlayer->stop();
            emit playSelected(ROCKETLAUNCHER);
        }
        else if (gunBtn.contains(pos)) {
            menuMusicPlayer->stop();
            emit playSelected(GUN);
        }
    }
}
void MainMenu::playMusic() {
    if (menuMusicPlayer && menuMusicPlayer->playbackState() != QMediaPlayer::PlayingState)
        menuMusicPlayer->play();
}
