#ifndef QTBOATS_H
#define QTBOATS_H

#include <QMainWindow>

class QAction;
class QGraphicsView;
class QGraphicsScene;
class PlayArea;

class QtBoats : public QMainWindow
{
    Q_OBJECT
    
public:
    QtBoats(QWidget *parent = 0);
    ~QtBoats();

public slots:
    void installNewArea();

private:
    QAction* newGameAction;
    QGraphicsView* mainPanel_;
    QGraphicsScene* scene_;
    PlayArea* currentArea_;
};

#endif // QTBOATS_H
