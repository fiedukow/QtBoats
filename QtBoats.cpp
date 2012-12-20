#include "QtBoats.h"
#include <QToolBar>
#include <QAction>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "PlayArea.h"
#include "GameState.h"

QtBoats::QtBoats(QWidget *parent)
    : QMainWindow(parent),
      gameState_(NULL)
{
    QToolBar* mainBar = new QToolBar;
    addToolBar(mainBar);
    newGameAction = new QAction(tr("New game"), mainBar);
    nextTurnAction = new QAction(tr("Next turn"), mainBar);
    mainBar->addAction(newGameAction);
    mainBar->addAction(nextTurnAction);
    mainPanel_ = new QGraphicsView(this);
    setCentralWidget(mainPanel_);

    connect(newGameAction,
            SIGNAL(triggered()),
            this,
            SLOT(newGame()));

    newGame();
}

void QtBoats::newGame()
{
    delete gameState_;
    gameState_ = new GameState(this);
    updateScene();

    connect(nextTurnAction,
            SIGNAL(triggered()),
            gameState_,
            SLOT(gotoNextTurn()));

    connect(gameState_,
            SIGNAL(sceneChanged()),
            this,
            SLOT(updateScene()));

}

void QtBoats::updateScene()
{
  mainPanel_->setScene(gameState_->getScene());
}

QtBoats::~QtBoats()
{
    delete gameState_;
}
