#ifndef PLAYAREA_H
#define PLAYAREA_H

#include "Table2D.h"
#include <QGraphicsRectItem>
#include <vector>
#include <list>

class PlayField;
class GameState;

typedef std::list< std::pair<int, int> > Boat;

class PlayArea : public QGraphicsRectItem
{
public:
    PlayArea(uint width, uint height,
             qreal pxX, qreal pxY,
             qreal pxWidth, qreal pxHeight,
             qreal fieldMargin,
             GameState* gameState,
             QGraphicsItem *parent = 0
             );

    void setHiddenShips(bool);
    void hitted();
    bool isHittable();
    bool isGameFinished();
    void setHittable(bool value = true);
    void chooseField(int x, int y);
    void placeBoat(int x, int y);
    void hitField(int x, int y);
    void setAsAlly();
    void setAsEnemy();
    void resetBoat();

    void revealSunked(int x,
                      int y,
                      std::list< std::pair<int,int> > stack
                                = std::list< std::pair<int,int> >());
    bool isSunked(int x, int y,
                  std::list< std::pair<int,int> > stack
                            = std::list< std::pair<int,int> >());

signals:

public slots:

private:
    const uint width_;
    const uint height_;
    const qreal fieldMargin_;
    Table2D<PlayField*> fields_;
    bool hittable_;
    GameState* gameState_;
    Boat currentBoat_;
};

#endif // PLAYAREA_H
