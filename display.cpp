#include "display.h"
#include "figure.h"
#include "square.h"

#include <QKeyEvent>

Display::Display(int w, int h, QWidget *parent)
    : QGraphicsView(parent), nextFigure(nullptr), timerId(0), isOn(false)
{
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    QGraphicsScene *graphscene = new QGraphicsScene;
    setFixedSize(w*35+4, h*35+4);
    graphscene->setSceneRect(qreal(2.), qreal(2.), qreal(w*35.), qreal(h*35.));
    setScene(graphscene);
    grid.fill(QVector< Square * >(h), w);
}

Display::~Display()
{
    //delete this;
}

QVector<QVector<Square *> > Display::getGrid()
{
    return grid;
}

void Display::play()
{
    setFocus();
    isOn = true;
    emit gamePlay();
    if (!nextFigure) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 20; j++) {
                grid[i][j] = nullptr;
            }
        }
        scene()->clear();
        figure = new Figure(qrand()%7, qrand()%7, this);
        figure->moveToStart();
        figure->addToScene();
        int nextFigureType = rand()%7;
        int nextFigureColor = rand()%7;
        nextFigure = new Figure(nextFigureType, nextFigureColor, this);
        emit startGame(nextFigureType, nextFigureColor);
        level = 1;
        score = 0;
        emit scoreChange(score);
        emit levelChange(level);
    }
    timerId = startTimer(1000/level);
}

void Display::pause()
{
    killTimer(timerId);
    isOn = false;
    emit gamePause();
}

void Display::keyPressEvent(QKeyEvent *event)
{
    if (isOn) {
        switch (event->key()) {
        case Qt::Key_Up:
            figure->turn();
            break;
        case Qt::Key_Down:
            if (!figure->stay())
                figure->down();
            break;
        case Qt::Key_Left:
            figure->left();
            break;
        case Qt::Key_Right:
            figure->right();
            break;
        default:
            QGraphicsView::keyPressEvent(event);
        }
    }
    if (event->key() == Qt::Key_Space) {
        if (!isOn)
            play();
        else
            pause();
    }
}

void Display::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);
    QPen penLine("#499B4F");
    QPen penGrid("#F3CB7B");
    penLine.setWidth(4);
    penGrid.setWidth(2);
    painter->setPen(penGrid);
    for (qreal i = 0; i <= width(); i += qreal(35.))
        painter->drawLine(i, qreal(0.), i, qreal(height()));
    for (qreal i = 0; i <= height(); i += qreal(35.))
        painter->drawLine(qreal(0.), i, qreal(width()), i);
    painter->setPen(penLine);
    painter->drawRect(scene()->sceneRect());
}

void Display::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    if (figure->stay()) {
        foreach (Square *square, figure->getSquareList()) {
            if (square->getY() < 0 || square->intersect(0, 0)) {
                emit gamePause();
                killTimer(timerId);
                timerId = 0;
                delete nextFigure;
                delete figure;
                nextFigure = nullptr;
                isOn = false;
                return;
            }
            grid[square->getX()][square->getY()] = square;
        }
        QList< int > fullRows;
        for (int j = 0; j < 20; j++) {
            for (int i = 0; i < 10; i++) {
                if (!grid[i][j]) {
                    break;
                }
                if (i == 9)
                    fullRows << j;
            }
        }
        foreach (int j, fullRows) {
            for (int i = 0; i < 10; i++) {
                delete grid[i][j];
                for (int jj = j; jj > 0; jj--) {
                    grid[i][jj] = grid[i][jj-1];
                    if (grid[i][jj])
                        grid[i][jj]->down();
                }
                delete grid[i][0];
                grid[i][0] = nullptr;
            }
            score += 10;
            if (score%100 == 0) {
                level++;
                killTimer(timerId);
                timerId = startTimer(1000/level);
                emit levelChange(level);
            }
            emit scoreChange(score);
        }
        figure = nextFigure;
        figure->moveToStart();
        figure->addToScene();
        int nextFigureType = rand()%7;
        int nextFigureColor = rand()%7;
        nextFigure = new Figure(nextFigureType, nextFigureColor, this);
        emit startGame(nextFigureType, nextFigureColor);
    } else {
        figure->down();
    }
}

void Display::focusOutEvent(QFocusEvent *event)
{
    Q_UNUSED(event);

    setFocus();
}
