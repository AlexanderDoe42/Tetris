#include "figure.h"

Figure::Figure(int figuretype, int figureColor, Display *dis)
    : figureType(figuretype), display(dis), condition(0)
{
    switch (figureType) {
    case 0:
        squareList << new Square(0, 1, figureColor, display);
        squareList << new Square(1, 1, figureColor, display);
        squareList << new Square(2, 1, figureColor, display);
        squareList << new Square(3, 1, figureColor, display);
        pointRotation = QPoint(2, 1);
        leftExtreme = 0;
        rightExtreme = 3;
        break;
    case 1:
        squareList << new Square(2, 0, figureColor, display);
        squareList << new Square(2, 1, figureColor, display);
        squareList << new Square(2, 2, figureColor, display);
        squareList << new Square(1, 2, figureColor, display);
        pointRotation = QPoint(2, 1);
        leftExtreme = 1;
        rightExtreme = 2;
        break;
    case 2:
        squareList << new Square(1, 0, figureColor, display);
        squareList << new Square(1, 1, figureColor, display);
        squareList << new Square(1, 2, figureColor, display);
        squareList << new Square(2, 2, figureColor, display);
        pointRotation = QPoint(1, 1);
        break;
    case 3:
        squareList << new Square(2, 0, figureColor, display);
        squareList << new Square(2, 1, figureColor, display);
        squareList << new Square(1, 1, figureColor, display);
        squareList << new Square(1, 2, figureColor, display);
        pointRotation = QPoint(2, 1);
        break;
    case 4:
        squareList << new Square(1, 0, figureColor, display);
        squareList << new Square(1, 1, figureColor, display);
        squareList << new Square(2, 1, figureColor, display);
        squareList << new Square(2, 2, figureColor, display);
        pointRotation = QPoint(2, 1);
        break;
    case 5:
        squareList << new Square(1, 0, figureColor, display);
        squareList << new Square(1, 1, figureColor, display);
        squareList << new Square(2, 0, figureColor, display);
        squareList << new Square(2, 1, figureColor, display);
        break;
    case 6:
        squareList << new Square(1, 1, figureColor, display);
        squareList << new Square(1, 2, figureColor, display);
        squareList << new Square(0, 2, figureColor, display);
        squareList << new Square(2, 2, figureColor, display);
        pointRotation = QPoint(1, 2);
        break;
    default:
        break;
    }
}

Figure::~Figure()
{
}

QList<Square *> Figure::getSquareList()
{
    return squareList;
}

void Figure::down()
{
    foreach (Square *square, squareList) {
        square->down();
    }
    pointRotation += QPoint(0, 1);
}

void Figure::left()
{
    foreach (Square *square, squareList) {
        if (square->intersect(-1, 0))
            return;
    }
    foreach (Square *square, squareList) {
        square->left();
    }
    leftExtreme--;
    rightExtreme--;
    pointRotation += QPoint(-1, 0);
}

void Figure::right()
{
    foreach (Square *square, squareList) {
        if (square->intersect(1, 0))
            return;
    }
    foreach (Square *square, squareList) {
        square->right();
    }
    leftExtreme++;
    rightExtreme++;
    pointRotation += QPoint(1, 0);
}

void Figure::addToScene()
{
    foreach (Square *square, squareList) {
        display->scene()->addItem(square);
    }
}

bool Figure::stay()
{
    foreach (Square *square, squareList) {
        if (square->intersect(0, 1))
            return true;
    }
    return false;
}

void Figure::moveToStart()
{
    int dy;
    switch (figureType) {
    case 0:
        dy = -1;
        break;
    case 1:
        dy = -2;
        break;
    case 2:
        dy = -2;
        break;
    case 3:
        dy = -2;
        break;
    case 4:
        dy = -2;
        break;
    case 5:
        dy = -1;
        break;
    case 6:
        dy = -2;
        break;
    default:
        break;
    }
    foreach (Square *square, squareList) {
        square->moveBy(3, dy);
    }
    pointRotation += QPoint(3, dy);
    leftExtreme += 3;
    rightExtreme += 3;
}

void Figure::turn()
{
    switch (figureType) {
    case 0:
        if (condition == 1 && leftExtreme == 0 && admissible(1)) {
            turnDirectly(1);
            pointRotation += QPoint(2, 0);
            rightExtreme = 3;
            condition = 0;
            return;
        }
        if (condition == 1 && leftExtreme == 9 && admissible(-2)) {
            turnDirectly(-2);
            pointRotation += QPoint(-1, 0);
            leftExtreme = 6;
            condition = 0;
            return;
        }
        if (condition == 0 && admissible(0)) {
            turnDirectly(0);
            leftExtreme = pointRotation.x();
            rightExtreme = leftExtreme;
            condition = 1;
            return;
        }
        if (condition == 0 && admissible(-1)) {
            turnDirectly(-1);
            condition = 1;
            pointRotation += QPoint(-1, 0);
            leftExtreme = pointRotation.x();
            rightExtreme = leftExtreme;
            return;
        }
        if (condition == 1 && admissible(-1)) {
            turnDirectly(-1);
            leftExtreme -= 2;
            rightExtreme++;
            condition = 0;
            return;
        }
        if (condition == 1 && admissible(0)) {
            turnDirectly(0);
            condition = 0;
            pointRotation += QPoint(1, 0);
            leftExtreme--;
            rightExtreme += 2;
            return;
        }
        break;
    case 1:
        if (condition == 0 && admissible(0)) {
            turnDirectly(0);
            condition = 1;
            return;
        }
        if (condition == 0 && admissible(-1)) {
            turnDirectly(-1);
            condition = 1;
            pointRotation += QPoint(-1, 0);
            return;
        }
        if (condition == 1 && admissible(0)) {
            turnDirectly(0);
            condition = 2;
            return;
        }
        if (condition == 1 && admissible(-1)) {
            turnDirectly(-1);
            condition = 2;
            pointRotation += QPoint(-1, 0);
            return;
        }
        if (condition == 2 && admissible(0)) {
            turnDirectly(0);
            condition = 3;
            return;
        }
        if (condition == 2 && admissible(1)) {
            turnDirectly(1);
            condition = 3;
            pointRotation += QPoint(1, 0);
            return;
        }
        if (condition == 3 && admissible(0)) {
            turnDirectly(0);
            condition = 0;
            return;
        }
        if (condition == 3 && admissible(1)) {
            turnDirectly(1);
            condition = 0;
            pointRotation += QPoint(1, 0);
            return;
        }
        break;
    case 2:
        if (condition == 0 && admissible(0)) {
            turnDirectly(0);
            condition = 1;
            return;
        }
        if (condition == 0 && admissible(1)) {
            turnDirectly(1);
            condition = 1;
            pointRotation += QPoint(1, 0);
            return;
        }
        if (condition == 1 && admissible(0)) {
            turnDirectly(0);
            condition = 2;
            return;
        }
        if (condition == 1 && admissible(1)) {
            turnDirectly(1);
            condition = 2;
            pointRotation += QPoint(1, 0);
            return;
        }
        if (condition == 2 && admissible(0)) {
            turnDirectly(0);
            condition = 3;
            return;
        }
        if (condition == 2 && admissible(-1)) {
            turnDirectly(-1);
            condition = 3;
            pointRotation += QPoint(-1, 0);
            return;
        }
        if (condition == 3 && admissible(0)) {
            turnDirectly(0);
            condition = 0;
            return;
        }
        if (condition == 3 && admissible(-1)) {
            turnDirectly(-1);
            condition = 0;
            pointRotation += QPoint(-1, 0);
            return;
        }
        break;
    case 3:
        if (condition == 0 && admissible(0)) {
            turnDirectly(0);
            condition = 1;
            return;
        }
        if (condition == 0 && admissible(-1)) {
            turnDirectly(-1);
            condition = 1;
            pointRotation += QPoint(-1, 0);
            return;
        }
        if (condition == 1 && admissible(-1)) {
            turnDirectly(-1);
            condition = 0;
            return;
        }
        if (condition == 1 && admissible(0)) {
            turnDirectly(0);
            condition = 0;
            pointRotation += QPoint(1, 0);
            return;
        }
        break;
    case 4:
        if (condition == 0 && admissible(0)) {
            turnDirectly(0);
            condition = 1;
            return;
        }
        if (condition == 0 && admissible(-1)) {
            turnDirectly(-1);
            condition = 1;
            pointRotation += QPoint(-1, 0);
            return;
        }
        if (condition == 1 && admissible(-1)) {
            turnDirectly(-1);
            condition = 0;
            return;
        }
        if (condition == 1 && admissible(0)) {
            turnDirectly(0);
            condition = 0;
            pointRotation += QPoint(1, 0);
            return;
        }
        break;
    case 5:
        break;
    case 6:
        if (condition == 0 && admissible(0)) {
            turnDirectly(0);
            condition = 1;
            return;
        }
        if (condition == 0 && admissible(-1)) {
            turnDirectly(-1);
            condition = 1;
            pointRotation += QPoint(-1, 0);
            return;
        }
        if (condition == 1 && admissible(0)) {
            turnDirectly(0);
            condition = 2;
            return;
        }
        if (condition == 1 && admissible(1)) {
            turnDirectly(1);
            condition = 2;
            pointRotation += QPoint(1, 0);
            return;
        }
        if (condition == 2 && admissible(0)) {
            turnDirectly(0);
            condition = 3;
            return;
        }
        if (condition == 2 && admissible(1)) {
            turnDirectly(1);
            condition = 3;
            pointRotation += QPoint(1, 0);
            return;
        }
        if (condition == 3 && admissible(0)) {
            turnDirectly(0);
            condition = 0;
            return;
        }
        if (condition == 3 && admissible(-1)) {
            turnDirectly(-1);
            condition = 0;
            pointRotation += QPoint(-1, 0);
            return;
        }
        break;
    default:
        break;
    }
}

bool Figure::admissible(int dx)
{
    foreach (Square *square, squareList) {
        if (square->intersect(pointRotation.x() + pointRotation.y() - square->getY() - square->getX() + dx,
                             -pointRotation.x() + pointRotation.y() + square->getX() - square->getY())) {
            return false;
        }
    }
    return true;
}

void Figure::turnDirectly(int dx)
{
    foreach (Square *square, squareList) {
        square->move(pointRotation.x() + pointRotation.y() - square->getY() + dx,
                    -pointRotation.x() + pointRotation.y() + square->getX());
    }
}
