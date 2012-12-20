#include "PlayArea.h"
#include "PlayField.h"
#include <QBrush>
#include <QColor>
#include <QList>

#include <cassert>

PlayArea::PlayArea(uint width, uint height,
                   qreal pxX, qreal pxY,
                   qreal pxWidth, qreal pxHeight,
                   qreal fieldMargin,
                   QGraphicsItem *parent) :
    QGraphicsRectItem(0,
                      0,
                      pxWidth+fieldMargin*2,
                      pxHeight+fieldMargin*2, parent),
    width_(width+fieldMargin*2),
    height_(height+fieldMargin*2),
    fieldMargin_(fieldMargin),
    fields_(width, height),
    hittable_(true)
{
    setPos(pxX, pxY);
    setBrush(QBrush(Qt::yellow));
    const qreal fieldWidth = pxWidth/width;
    const qreal fieldHeight = pxHeight/height;

    for(uint i = 0; i < width; ++i)
        for(uint j = 0; j < height; ++j)
            fields_[i][j] = new PlayField(i*fieldWidth+fieldMargin,
                                          j*fieldHeight+fieldMargin,
                                          fieldWidth,
                                          fieldHeight,
                                          this);

}

void PlayArea::setHiddenShips(bool hidden)
{
  QList<QGraphicsItem*> childs = childItems();
  QListIterator<QGraphicsItem*> it(childs);
  while(it.hasNext())
  {
    PlayField* item = dynamic_cast<PlayField*>(it.next());
    assert(item != NULL);
    item->setHidden(hidden);
  }
}

void PlayArea::hitted()
{
  setHittable(false);
}

bool PlayArea::isHittable()
{
  return hittable_;
}

void PlayArea::setHittable(bool value)
{
  hittable_ = value;
}



