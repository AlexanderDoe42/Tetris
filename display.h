#ifndef DISPLAY_H
#define DISPLAY_H

#include <QGraphicsView>

class Figure;
class Square;

class Display : public QGraphicsView
{
    Q_OBJECT
public:
    Display(int w, int h, QWidget *parent = nullptr);
    ~Display();
    QVector< QVector< Square * > > getGrid();

signals:
    void startGame(int, int);
    void gamePlay();
    void gamePause();
    void scoreChange(int);
    void levelChange(int);

public slots:
    void play();
    void pause();

protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event);
    Figure *nextFigure;
    void focusOutEvent(QFocusEvent *event);

private:
    int timerId;
    int level, score;
    Figure *figure;
    QVector< QVector< Square * > > grid;
    bool isOn;
};

#endif // DISPLAY_H
