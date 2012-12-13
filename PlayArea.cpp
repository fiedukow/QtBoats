#include "PlayArea.h"
#include "PlayField.h"
#include <QBrush>
#include <QColor>

PlayArea::PlayArea(uint width, uint height,
                   qreal pxX, qreal pxY,
                   qreal pxWidth, qreal pxHeight,
                   qreal fieldMargin,
                   QGraphicsItem *parent) :
    QGraphicsRectItem(pxX - fieldMargin, pxY - fieldMargin, pxWidth+fieldMargin*2, pxHeight+fieldMargin*2, parent),
    width_(width),
    height_(height),
    fieldMargin_(fieldMargin),
    fields_(width, height)
{
    setBrush(QBrush(Qt::yellow));
    const qreal fieldWidth = pxWidth/width;
    const qreal fieldHeight = pxHeight/height;

    for(uint i = 0; i < width; ++i)
        for(uint j = 0; j < height; ++j)
            fields_[i][j] = new PlayField(i*fieldWidth,
                                          j*fieldHeight,
                                          fieldWidth,
                                          fieldHeight,
                                          this);

}


