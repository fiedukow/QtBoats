#include "PlayArea.h"
#include "PlayField.h"
#include "GameState.h"

#include <QBrush>
#include <QColor>
#include <QList>

#include <cassert>

PlayArea::PlayArea(uint width, uint height,
                   qreal pxX, qreal pxY,
                   qreal pxWidth, qreal pxHeight,
                   qreal fieldMargin,
                   GameState* gameState,
                   QGraphicsItem *parent)
  : QGraphicsRectItem(0,
                      0,
                      pxWidth+fieldMargin*2,
                      pxHeight+fieldMargin*2, parent),
    width_(width),
    height_(height),
    fieldMargin_(fieldMargin),
    fields_(width, height),
    hittable_(true),
    gameState_(gameState)
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
                                          i,
                                          j,
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

void PlayArea::hitField(int x, int y)
{
  if(x < 0 || x >= (int)width_ || y < 0 || y >= (int)height_)
    return;

  if(!isHittable())
    return;

  /*strzel*/
  if(!fields_[x][y]->markItem())
    return;

  hitted();

  if(!fields_[x][y]->isDeadBoat())
  {
    gameState_->showUserMessage("Missed...");
    return;
  }

  /*TRAFIONY*/
  gameState_->showUserMessage("Hit!");

  if((x+1 >= (int)width_  || !fields_[x+1][y]->isLiveBoat()) &&
     (x-1 < 0             || !fields_[x-1][y]->isLiveBoat()) &&
     (y+1 >= (int)height_ || !fields_[x][y+1]->isLiveBoat()) &&
     (y-1 < 0             || !fields_[x][y-1]->isLiveBoat()))
  {
    /*ZATOPIONY*/
    gameState_->showUserMessage("Hit & down!");
    for(int i = -1; i <= 1; ++i)
      for(int j = -1; j <= 1; ++j)
        hitField(x+i, y+j);
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

void PlayArea::setAsAlly()
{
  setHittable(false);
  setHiddenShips(false);
  setBrush(QBrush(Qt::green));
}

void PlayArea::setAsEnemy()
{
  setHittable(true);
  setHiddenShips(true);
  setBrush(QBrush(Qt::red));
}

