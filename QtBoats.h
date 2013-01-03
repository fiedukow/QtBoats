#ifndef QTBOATS_H
#define QTBOATS_H

#include <QMainWindow>
#include <QString>

class QAction;
class QGraphicsView;
class QGraphicsScene;
class QLabel;
class PlayArea;
class GameState;

class QtBoats : public QMainWindow
{
    Q_OBJECT

public:
    QtBoats(QWidget *parent = 0);
    ~QtBoats();

    QString getPlayer1Name();
    QString getPlayer2Name();
    int wholeWidth();
    int wholeHeight();

public slots:
    void newGame();
    void updateScene();
    void setStatusBarMessage(const QString& msg);
    void openSettings();

protected:
    virtual void resizeEvent(QResizeEvent * event);
    virtual void showEvent(QShowEvent* event);

private:
    QAction* newGameAction;
    QAction* nextTurnAction;
    QAction* settingsAction;
    QGraphicsView* mainPanel_;
    GameState* gameState_;
    QLabel* statusBarLabel_;

    QString player1Name;
    QString player2Name;
};

#endif // QTBOATS_H
