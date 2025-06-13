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


/**
 * @struct ScoreEntry
 * @brief Represents a single entry in the high score table.
 */
struct ScoreEntry {
    QString name;   ///< @brief The player's name.
    int score;      ///< @brief The score achieved by the player.
    QString time;   ///< @brief The time at which the score was recorded.
};

/**
 * @class GameOverMenu
 * @brief Manages the game over screen, including high scores, replay/quit options, and player input.
 */
class GameOverMenu : public QObject
{
    Q_OBJECT

public:
/**
 * @brief Constructs the GameOverMenu object.
 * @param score The score achieved in the game.
 * @param timeStr The formatted time string of gameplay duration.
 * @param parent Optional parent QObject.
 */
    GameOverMenu(int score, const QString& timeStr, QObject *parent = nullptr);

/**
 * @brief Gets the final score.
 * @return The score as an integer.
 */
    int getScore() const;

/**
 * @brief Gets the gameplay duration as a string.
 * @return A QString representing the time.
 */
    QString getTimeString() const;

/**
 * @brief Gets the name entered by the player.
 * @return Player's name (max 6 characters).
 */
    QString getPlayerName() const { return itsPlayerName; }

/**
 * @brief Sets the UI rectangle for name input.
 * @param rect Rectangle for name input field.
 */
    void setNameInputRect(const QRect& rect) { nameInputRect = rect; }

/**
 * @brief Gets the name input rectangle.
 * @return QRect of the input field.
 */
    QRect getNameInputRect() const { return nameInputRect; }

/**
 * @brief Sets the player's name (max 6 characters).
 * @param name The input name string.
 */
    void setPlayerName(const QString& name) { itsPlayerName = name.left(6); }

/**
 * @brief Sets the UI rectangle for the replay button.
 * @param rect Rectangle for the replay button.
 */
    void setReplayButtonRect(const QRect& rect);

/**
 * @brief Sets the UI rectangle for the quit button.
 * @param rect Rectangle for the quit button.
 */
    void setQuitButtonRect(const QRect& rect);

/**
 * @brief Gets the replay button rectangle.
 * @return QRect of the replay button.
 */
    QRect getReplayButtonRect() const;

/**
 * @brief Gets the quit button rectangle.
 * @return QRect of the quit button.
 */
    QRect getQuitButtonRect() const;

/**
 * @brief Handles a mouse click at the given position.
 * @param pos The click position in screen coordinates.
 */
    void handleClick(const QPoint& pos);

/**
 * @brief Gets the top stored scores.
 * @return A vector of ScoreEntry objects.
 */
    QVector<ScoreEntry> getTopScores() const;

/**
 * @brief Gets the path to the score storage file.
 * @return File path as a QString.
 */
    QString getScoresFilePath() const;

/**
 * @brief Gets the media player for game over music.
 * @return Pointer to a QMediaPlayer.
 */
    QMediaPlayer *getGameOverMusicPlayer() const;

/**
 * @brief Loads scores from persistent storage.
 */
    void loadScores();

/**
 * @brief Saves scores to persistent storage.
 */
    void saveScores();

/**
 * @brief Indicates whether the menu is currently visible.
 */
    bool isVisible = true;

signals:
/**
 * @brief Emitted when the replay button is clicked.
 */
    void replayRequested();

/**
 * @brief Emitted when the quit button is clicked.
 */
    void quitRequested();

private:
    int itsScore;                        ///< @brief The final score achieved by the player.
    QString itsTimeStr;                  ///< @brief The formatted string representing game duration.
    QString itsPlayerName;              ///< @brief The player's input name (up to 6 characters).
    QRect nameInputRect;                ///< @brief The UI rectangle for the name input field.

    QRect replayButtonRect;             ///< @brief The UI rectangle for the replay button.
    QRect quitButtonRect;               ///< @brief The UI rectangle for the quit button.

    QVector<ScoreEntry> topScores;      ///< @brief The list of top scores stored.

    QMediaPlayer* gameOverMusicPlayer;  ///< @brief Music player for the game over screen.
    QAudioOutput* audioOutput;          ///< @brief Audio output used for playing music.
};

#endif // GAMEOVERMENU_H
