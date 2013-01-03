#ifndef QTBOATS_H
#define QTBOATS_H

#include <QMainWindow>

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

public slots:
    void newGame();
    void updateScene();
    void setStatusBarMessage(const QString& msg);

private:
    QAction* newGameAction;
    QAction* nextTurnAction;
    QAction* settingsAction;
    QGraphicsView* mainPanel_;
    GameState* gameState_;
    QLabel* statusBarLabel_;
};

#endif // QTBOATS_H
