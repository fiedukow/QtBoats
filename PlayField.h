#ifndef PLAYFIELD_H
#define PLAYFIELD_H
#include <QGraphicsRectItem>

class PlayField : public QGraphicsRectItem
{
public:
    enum FieldState { BOAT, WATER, HITTED_WATER, HITTED_BOAT };

public:
    PlayField(qreal pxX, qreal pxY,
              qreal pxWidth, qreal pxHeight,
              int x, int y,
              QGraphicsItem* parent);

    /* returns true if there was any change */
    bool markItem();
    void setHidden(bool hidden);

    bool isLiveBoat();
    bool isDeadBoat();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
    bool setState(FieldState newState);
    void updateColor();

private:
    FieldState state_;
    bool hidden_;
    const int x;
    const int y;
};

#endif // PLAYFIELD_H
