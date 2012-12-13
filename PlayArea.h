#ifndef PLAYAREA_H
#define PLAYAREA_H

#include "Table2D.h"
#include <QGraphicsRectItem>
#include <vector>


class PlayField;

class PlayArea : public QGraphicsRectItem
{
public:
    PlayArea(uint width, uint height,
             qreal pxX, qreal pxY,
             qreal pxWidth, qreal pxHeight,
             qreal fieldMargin,
             QGraphicsItem *parent = 0);
    
signals:
    
public slots:
    
private:
    uint width_;
    uint height_;
    qreal fieldMargin_;
    Table2D<PlayField*> fields_;
};

#endif // PLAYAREA_H
