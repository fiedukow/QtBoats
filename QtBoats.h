#ifndef QTBOATS_H
#define QTBOATS_H

#include <QMainWindow>

class QAction;
class QGraphicsView;
class QGraphicsScene;
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

private:
    QAction* newGameAction;
    QAction* nextTurnAction;
    QGraphicsView* mainPanel_;
    GameState* gameState_;
};

#endif // QTBOATS_H
