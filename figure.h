#ifndef FIGURE_H
#define FIGURE_H

#include <QGraphicsItemGroup>

#include "square.h"
#include "display.h"

class Square;
class Display;

class Figure
{
public:
    Figure(int figuretype, int figureColor, Display *dis);
    ~Figure();
    QList< Square * > getSquareList();
    void down();
    void left();
    void right();
    void addToScene();
    bool stay();
    void moveToStart();
    void turn();

private:
    QList< Square * > squareList;
    int figureType;
    Display *display;
    QPoint pointRotation;
    int condition;
    int leftExtreme;
    int rightExtreme;
    bool admissible(int dx);
    void turnDirectly(int dx);
};

#endif // FIGURE_H
