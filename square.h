#ifndef SQUARE_H
#define SQUARE_H

#include <QGraphicsRectItem>
#include <QGraphicsView>

#include "display.h"

class Display;

class Square : public QGraphicsRectItem
{
public:
    Square(int X, int Y, int squareColor, Display *dis);
    ~Square();
    void down();
    void left();
    void right();
    int getX();
    int getY();
    bool intersect(int dx, int dy);
    void moveBy(int dx, int dy);
    void move(int xx, int yy);

private:
    int xGrig, yGrid;
    Display *display;
};

#endif // SQUARE_H
