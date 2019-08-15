#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>

#include "minidisplay.h"

#include <QLCDNumber>

class MenuWidget : public QWidget
{
    Q_OBJECT
public:
    MenuWidget(Display *displayWidget, QWidget *parent = nullptr);
    ~MenuWidget();

signals:

public slots:
    void newScore(int n);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Display *display;
    QLCDNumber *lcdScore;
    int maxScore;
};

#endif // MENUWIDGET_H
