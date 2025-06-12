#include "gameovermenu.h"

GameOverMenu::GameOverMenu(int score, const QString& timeStr, QObject *parent)
    : QObject(parent), itsScore(score), itsTimeStr(timeStr)
{}

int GameOverMenu::getScore() const { return itsScore; }
QString GameOverMenu::getTimeString() const { return itsTimeStr; }

void GameOverMenu::setReplayButtonRect(const QRect &rect) { replayButtonRect = rect; }
void GameOverMenu::setQuitButtonRect(const QRect &rect) { quitButtonRect = rect; }
QRect GameOverMenu::getReplayButtonRect() const { return replayButtonRect; }
QRect GameOverMenu::getQuitButtonRect() const { return quitButtonRect; }

void GameOverMenu::handleClick(const QPoint& pos)
{
    if (replayButtonRect.contains(pos))
        emit replayRequested();
    else if (quitButtonRect.contains(pos))
        emit quitRequested();
}
