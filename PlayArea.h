#ifndef PLAYAREA_H
#define PLAYAREA_H

#include "Table2D.h"
#include <QGraphicsRectItem>
#include <vector>


class PlayField;
class GameState;

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
    void setHittable(bool value = true);
    void hitField(int x, int y);
    void setAsAlly();
    void setAsEnemy();

signals:

public slots:

private:
    const uint width_;
    const uint height_;
    const qreal fieldMargin_;
    Table2D<PlayField*> fields_;
    bool hittable_;
    GameState* gameState_;
};

#endif // PLAYAREA_H
