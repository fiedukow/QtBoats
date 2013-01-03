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

void PlayArea::chooseField(int x, int y)
{
  gameState_->chooseField(x, y, this);
}

void PlayArea::placeBoat(int x, int y)
{
  bool acceptablePlace = currentBoat_.empty();

  for(Boat::const_iterator i = currentBoat_.begin();
      i != currentBoat_.end() && !acceptablePlace;
      ++i)
  {
    if((i->first == x+1 && i->second == y  ) ||
       (i->first == x-1 && i->second == y  ) ||
       (i->first == x   && i->second == y+1) ||
       (i->first == x   && i->second == y-1))
    {
      acceptablePlace = true;
    }
  }

  acceptablePlace = (acceptablePlace && fields_[x][y]->isWater());

  bool hasColision = false;

  for(int i = -1; i <= 1; ++i)
    for(int j = -1; j <= 1; ++j)
    {
      if(x+i >= (int)width_ || y+j >= (int)height_ || x+i < 0 || y+j < 0)
        continue;

      bool found = (std::find(currentBoat_.begin(),
                              currentBoat_.end(),
                              std::pair<int,int>(x+i,y+j)) != currentBoat_.end());
      hasColision = (hasColision ||
                    (!fields_[x+i][y+j]->isWater() && !found));
    }

  bool possibleToAdd = (acceptablePlace && !hasColision);

  if(!possibleToAdd)
  {
    gameState_->showUserMessage("You cannot place this mast here.");
  }
  else
  {
    currentBoat_.push_back(std::pair<int,int>(x,y));
    if(gameState_->consumeMast(this))
    {
      fields_[x][y]->placeBoat();
    }
    else
    {
      currentBoat_.pop_back();
      gameState_->showUserMessage("No more ships.");
    }
  }
}

void PlayArea::resetBoat()
{
  currentBoat_.clear();
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

