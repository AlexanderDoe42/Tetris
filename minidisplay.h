#ifndef MINIDISPLAY_H
#define MINIDISPLAY_H

#include "display.h"
#include "figure.h"

class MiniDisplay : public Display
{
    Q_OBJECT
public:
    MiniDisplay(int w, int h, QWidget *parent = nullptr);
    ~MiniDisplay();

public slots:
    void play(int nextFigureType, int nextFigureColor);

protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void focusOutEvent(QFocusEvent *event);

};

#endif // MINIDISPLAY_H
