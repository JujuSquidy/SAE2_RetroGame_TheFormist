#ifndef GAMEOVERMENU_H
#define GAMEOVERMENU_H


#include <QString>
#include <QRect>
#include <QVector>
#include <QObject>
#include <QStandardPaths>
#include <QDir>

#include <QMediaPlayer>
#include <QAudioOutput>

struct ScoreEntry {
    QString name;
    int score;
    QString time;
};

class GameOverMenu : public QObject
{
    Q_OBJECT

public:
    GameOverMenu(int score, const QString& timeStr, QObject *parent = nullptr);

    int getScore() const;
    QString getTimeString() const;
    QString getPlayerName() const { return itsPlayerName; }
    void setNameInputRect(const QRect& rect) { nameInputRect = rect; }
    QRect getNameInputRect() const { return nameInputRect; }

    void setPlayerName(const QString& name) { itsPlayerName = name.left(6); }
    void setReplayButtonRect(const QRect& rect);
    void setQuitButtonRect(const QRect& rect);
    QRect getReplayButtonRect() const;
    QRect getQuitButtonRect() const;
    void handleClick(const QPoint& pos);

    QVector<ScoreEntry> getTopScores() const;
    QString getScoresFilePath() const;

    QMediaPlayer *getGameOverMusicPlayer() const;

    void loadScores();
    void saveScores();

    bool isVisible = true;

signals:
    void replayRequested();
    void quitRequested();

private:
    int itsScore;
    QString itsTimeStr;
    QString itsPlayerName;
    QRect nameInputRect;

    QRect replayButtonRect;
    QRect quitButtonRect;

    QVector<ScoreEntry> topScores;

    QMediaPlayer* gameOverMusicPlayer;

    QAudioOutput* audioOutput;
};

#endif // GAMEOVERMENU_H
