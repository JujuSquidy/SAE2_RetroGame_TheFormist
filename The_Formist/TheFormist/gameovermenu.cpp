#include "GameOverMenu.h"
#include <QFile>
#include <QTextStream>
#include <algorithm>

GameOverMenu::GameOverMenu(int score, const QString& timeStr, QObject *parent)
    : QObject(parent), itsScore(score), itsTimeStr(timeStr)
{
    loadScores();
}

int GameOverMenu::getScore() const { return itsScore; }
QString GameOverMenu::getTimeString() const { return itsTimeStr; }

void GameOverMenu::setReplayButtonRect(const QRect &rect) { replayButtonRect = rect; }
void GameOverMenu::setQuitButtonRect(const QRect &rect) { quitButtonRect = rect; }
QRect GameOverMenu::getReplayButtonRect() const { return replayButtonRect; }
QRect GameOverMenu::getQuitButtonRect() const { return quitButtonRect; }

void GameOverMenu::handleClick(const QPoint& pos)
{
    if (replayButtonRect.contains(pos))
    {
        saveScores();
        emit replayRequested();
    }
    else if (quitButtonRect.contains(pos))
    {
        saveScores();
        emit quitRequested();
    }
}


void GameOverMenu::loadScores() {
    topScores.clear();

    QFile file("leaderboard.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QStringList parts = line.split(' ');
        if (parts.size() == 3) {
            ScoreEntry entry = { parts[0], parts[1].toInt(), parts[2] };
            topScores.append(entry);
        }
    }

    file.close();
}

void GameOverMenu::saveScores() {
    if (!itsPlayerName.trimmed().isEmpty()) {
        // Ajouter le score uniquement si un nom est saisi
        ScoreEntry current = { itsPlayerName.left(6), itsScore, itsTimeStr };
        topScores.append(current);

        std::sort(topScores.begin(), topScores.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
            return a.score > b.score;
        });

        if (topScores.size() > 5)
            topScores.resize(5);

        QFile file("leaderboard.txt");
        QTextStream out(&file);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            for (int i = 0; i < topScores.size(); ++i) {
                const ScoreEntry& entry = topScores[i];
                out << entry.name.left(6) << " " << entry.score << " " << entry.time << "\n";
            }
            file.close();
        }
    } else {
        // Aucun nom → on recharge le leaderboard existant
        loadScores();
    }
}

QVector<ScoreEntry> GameOverMenu::getTopScores() const {
    return topScores;
}
