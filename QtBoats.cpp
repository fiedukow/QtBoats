#include "QtBoats.h"
#include <QToolBar>
#include <QAction>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QStatusBar>
#include <QLabel>

#include "PlayArea.h"
#include "GameState.h"
#include "GameSettingsDialog.h"

QtBoats::QtBoats(QWidget *parent)
    : QMainWindow(parent),
      gameState_(NULL),
      player1Name("Player 1"),
      player2Name("Player 2")
{
    QToolBar* mainBar = new QToolBar;
    addToolBar(mainBar);
    newGameAction = new QAction(tr("New game"), mainBar);
    nextTurnAction = new QAction(tr("Next turn"), mainBar);
    settingsAction = new QAction(tr("Settings"), mainBar);
    mainBar->addAction(newGameAction);
    mainBar->addAction(nextTurnAction);
    mainBar->addAction(settingsAction);
    mainPanel_ = new QGraphicsView(this);
    setCentralWidget(mainPanel_);

    connect(newGameAction,
            SIGNAL(triggered()),
            this,
            SLOT(newGame()));
    connect(settingsAction,
            SIGNAL(triggered()),
            this,
            SLOT(openSettings()));

    QStatusBar* statusBar = new QStatusBar(this);
    setStatusBar(statusBar);
    statusBarLabel_ = new QLabel(statusBar);
    statusBar->addWidget(statusBarLabel_);
    setStatusBarMessage("Welcome!");

    newGame();
}

void QtBoats::openSettings()
{
    GameSettingsDialog* settingsDialog = new GameSettingsDialog(player1Name,
                                                                player2Name,
                                                                this);
    if(settingsDialog->exec() == QDialog::Accepted)
    {
        player1Name = settingsDialog->getPlayer1Name();
        player2Name = settingsDialog->getPlayer2Name();
    }
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

void QtBoats::setStatusBarMessage(const QString& msg)
{
  statusBarLabel_->setText(msg);
}

QtBoats::~QtBoats()
{
    delete gameState_;
}
