#include "minidisplay.h"

MiniDisplay::MiniDisplay(int w, int h, QWidget *parent)
    : Display(w, h, parent)
{
}

MiniDisplay::~MiniDisplay()
{
    //delete this;
}

void MiniDisplay::play(int nextFigureType, int nextFigureColor)
{
    if (nextFigure) {
        delete nextFigure;
        scene()->clear();
    }
    nextFigure = new Figure(nextFigureType, nextFigureColor, this);
    nextFigure->addToScene();
}

void MiniDisplay::keyPressEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
}

void MiniDisplay::focusOutEvent(QFocusEvent *event)
{
    Q_UNUSED(event);
}
