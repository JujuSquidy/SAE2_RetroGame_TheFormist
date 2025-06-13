#include "GameOverMenu.h"
#include <QFile>
#include <QTextStream>
#include <algorithm>

GameOverMenu::GameOverMenu(int score, const QString& timeStr, QObject *parent)
    : QObject(parent), itsScore(score), itsTimeStr(timeStr)
{
    // Setup audio output and music player for Game Over music
    audioOutput = new QAudioOutput(this);
    gameOverMusicPlayer = new QMediaPlayer(this);
    gameOverMusicPlayer->setAudioOutput(audioOutput);
    gameOverMusicPlayer->setSource(QUrl("qrc:/Music/GO.wav"));
    gameOverMusicPlayer->setLoops(QMediaPlayer::Infinite);
    audioOutput->setVolume(1);
    gameOverMusicPlayer->play();
    loadScores(); // Load existing high scores from file
}

int GameOverMenu::getScore() const { return itsScore; }
QString GameOverMenu::getTimeString() const { return itsTimeStr; }

void GameOverMenu::setReplayButtonRect(const QRect &rect) { replayButtonRect = rect; }
void GameOverMenu::setQuitButtonRect(const QRect &rect) { quitButtonRect = rect; }
QRect GameOverMenu::getReplayButtonRect() const { return replayButtonRect; }
QRect GameOverMenu::getQuitButtonRect() const { return quitButtonRect; }

void GameOverMenu::handleClick(const QPoint& pos)
{
    // Check if click was inside the replay button rectangle
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

    QString path = getScoresFilePath();
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Si le fichier n'existe pas, initialiser depuis la ressource
        QFile res(":/LB/leaderboard.txt");
        if (res.open(QIODevice::ReadOnly)) {
            if (file.open(QIODevice::WriteOnly)) {
                file.write(res.readAll());
                file.close();
            }
            res.close();
            // Réouvrir le fichier pour lecture
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                return; // Échec total
            }
        } else {
            return; // Pas de ressource, rien à charger
        }
    }

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
    // Only save if player has entered a name
    if (!itsPlayerName.trimmed().isEmpty()) {
        // Create a new score entry for current player
        ScoreEntry current = { itsPlayerName.left(6), itsScore, itsTimeStr };
        topScores.append(current);

        std::sort(topScores.begin(), topScores.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
            return a.score > b.score;
        });

        // Keep only top 5 scores
        if (topScores.size() > 5)
            topScores.resize(5);

        QString path = getScoresFilePath();
        QFile file(path);
        // Open file to write updated leaderboard
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            for (int i = 0; i < topScores.size(); ++i) {
                const ScoreEntry& entry = topScores[i];
                out << entry.name.left(6) << " " << entry.score << " " << entry.time << "\n";
            }
            file.close();
        }
    } else {
        // Player name empty, just reload scores (do not save)
        loadScores();
    }
}

QString GameOverMenu::getScoresFilePath() const {
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(appDataPath);
    if (!dir.exists()) {
        dir.mkpath(".");  // Create directory if it doesn't exist
    }
    return dir.filePath("leaderboard.txt");
}

QVector<ScoreEntry> GameOverMenu::getTopScores() const {
    return topScores;
}

QMediaPlayer *GameOverMenu::getGameOverMusicPlayer() const
{
    return gameOverMusicPlayer;
}
