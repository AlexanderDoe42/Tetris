#include "widget.h"

#include <QTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    Display *gamedisplay = new Display(10, 20);
    MenuWidget *menuwidget = new MenuWidget(gamedisplay);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(gamedisplay);
    layout->addWidget(menuwidget);
    setLayout(layout);
    setFocus();
}

Widget::~Widget()
{
    //delete this;
}
