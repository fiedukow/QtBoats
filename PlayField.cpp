#include "PlayField.h"
#include "PlayArea.h"
#include <cassert>
#include <cstdio>

#include <QBrush>
#include <QColor>
#include <QPen>

PlayField::PlayField(qreal pxX, qreal pxY,
                     qreal pxWidth, qreal pxHeight,
                     QGraphicsItem* parent)
    : QGraphicsRectItem(0, 0, pxWidth, pxHeight, parent),
      state_(rand()%3 ? WATER : BOAT)
{
    setPos(pxX, pxY);
    setPen(QPen(Qt::NoPen));
    updateColor();
}

bool PlayField::itemMarked()
{
    if(state_ == BOAT || state_ == HITTED_BOAT)
        return setState(HITTED_BOAT);
    if(state_ == WATER || state_ == HITTED_WATER)
        return setState(HITTED_WATER);

    assert(false && "state_ should never be out of enum values.");
}

void PlayField::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event);
    PlayArea* area = dynamic_cast<PlayArea*>(parentItem());
    assert(area != NULL);

    if(area->isHittable())
    {
      if(itemMarked())
        area->hitted();
    }
}

bool PlayField::setState(FieldState newState)
{
    if (state_ == newState)
        return false;

    state_ = newState;
    updateColor();
    return true;
}

void PlayField::setHidden(bool hidden)
{
  hidden_ = hidden;
  updateColor();
}

void PlayField::updateColor()
{
    switch(state_)
    {
    case WATER:
        setBrush(QBrush(QColor(200, 200, 255)));
        return;
    case HITTED_WATER:
        setBrush(QBrush(QColor(0, 0, 255)));
        return;
    case BOAT:
      if(hidden_)
        setBrush(QBrush(QColor(200, 200, 255)));
      else
        setBrush(QBrush(QColor(0, 0, 0)));
        return;
    case HITTED_BOAT:
        setBrush(QBrush(QColor(255, 0, 0)));
        return;
    default:
        setBrush(QBrush(QColor(127, 127, 127)));
        return;
    }
}
