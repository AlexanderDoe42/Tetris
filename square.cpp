#include "square.h"

Square::Square(int X, int Y, int squareColor, Display *dis)
    : xGrig(X), yGrid(Y), display(dis)
{
    setRect(qreal(xGrig*35), qreal(yGrid*35), qreal(35.), qreal(35.));
    QColor c;
    switch (squareColor) {
    case 0:
        c = Qt::red;
        break;
    case 1:
        c = Qt::green;
        break;
    case 2:
        c = Qt::blue;
        break;
    case 3:
        c = Qt::cyan;
        break;
    case 4:
        c = Qt::magenta;
        break;
    case 5:
        c = Qt::yellow;
        break;
    case 6:
        c = Qt::gray;
        break;
    default:
        break;
    }
    QBrush br(c);
    QPen p(Qt::black);
    p.setWidth(3);
    setBrush(br);
    setPen(p);
}

Square::~Square()
{
}

void Square::down()
{
    yGrid++;
    QGraphicsRectItem::moveBy(qreal(0.), qreal(35.));
}

void Square::left()
{
    xGrig--;
    QGraphicsRectItem::moveBy(qreal(-35.), qreal(0.));
}

void Square::right()
{
    xGrig++;
    QGraphicsRectItem::moveBy(qreal(35.), qreal(0.));
}

int Square::getX()
{
    return xGrig;
}

int Square::getY()
{
    return yGrid;
}

bool Square::intersect(int dx, int dy)
{
    if (yGrid+dy < 0) {
        if (xGrig+dx > 9 || xGrig+dx < 0)
            return true;
        return false;
    }
    if (yGrid+dy > 19 || xGrig+dx > 9 || xGrig+dx < 0)
        return true;
    if (!display->getGrid()[xGrig+dx][yGrid+dy])
        return false;
    return true;
}

void Square::moveBy(int dx, int dy)
{
    xGrig += dx;
    yGrid += dy;
    QGraphicsRectItem::moveBy(qreal(dx*35), qreal(dy*35));
}

void Square::move(int xx, int yy)
{
    QGraphicsRectItem::moveBy(qreal((xx-xGrig)*35), qreal((yy-yGrid)*35));
    xGrig = xx;
    yGrid = yy;
}
