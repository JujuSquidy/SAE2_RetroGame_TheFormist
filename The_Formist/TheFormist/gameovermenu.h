#ifndef GAMEOVERMENU_H
#define GAMEOVERMENU_H

#include <QObject>
#include <QString>
#include <QRect>

class GameOverMenu : public QObject
{
    Q_OBJECT

public:
    GameOverMenu(int score, const QString& timeStr, QObject *parent = nullptr);

    int getScore() const;
    QString getTimeString() const;

    void setReplayButtonRect(const QRect& rect);
    void setQuitButtonRect(const QRect& rect);
    QRect getReplayButtonRect() const;
    QRect getQuitButtonRect() const;

    bool isVisible = true;

signals:
    void replayRequested();
    void quitRequested();

    /**
     * @brief Call when a click happens to determine what to do.
     */
public:
    void handleClick(const QPoint& pos);

private:
    int itsScore;
    QString itsTimeStr;

    QRect replayButtonRect;
    QRect quitButtonRect;
};

#endif // GAMEOVERMENU_H
