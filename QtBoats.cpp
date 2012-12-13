#include "QtBoats.h"
#include <QToolBar>
#include <QAction>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "PlayArea.h"

QtBoats::QtBoats(QWidget *parent)
    : QMainWindow(parent),
      currentArea_(NULL)
{
    QToolBar* mainBar = new QToolBar;
    addToolBar(mainBar);
    newGameAction = new QAction(tr("New game"), mainBar);
    mainBar->addAction(newGameAction);
    mainPanel_ = new QGraphicsView(this);
    scene_ = new QGraphicsScene(mainPanel_);
    mainPanel_->setScene(scene_);
    installNewArea();
    setCentralWidget(mainPanel_);

    connect(newGameAction, SIGNAL(triggered()), this, SLOT(installNewArea()));
}

void QtBoats::installNewArea()
{
    if(currentArea_ != NULL)
        scene_->removeItem(currentArea_);

    currentArea_ = new PlayArea(10, 10, 0, 0, 400, 400, 20);
    scene_->addItem(currentArea_);
}

QtBoats::~QtBoats()
{
    
}
