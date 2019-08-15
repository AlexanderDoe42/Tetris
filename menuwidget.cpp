#include "menuwidget.h"

#include <QPainter>
#include <QPushButton>
#include <fstream>

MenuWidget::MenuWidget(Display *displayWidget, QWidget *parent)
    : QWidget(parent), display(displayWidget)
{
    setFixedSize(200, 700);

    std::fstream scoreFile("score.dat");
    if (scoreFile.is_open()) {
        scoreFile.close();
        scoreFile.open("score.dat", std::ios_base::in);
        scoreFile >> maxScore;
    } else {
        scoreFile.open("score.dat", std::ios_base::out);
        scoreFile << 0;
    }
    scoreFile.close();

    MiniDisplay *minidisplay = new MiniDisplay(4, 3, this);
    minidisplay->move(rect().center().x()-minidisplay->rect().center().x(),
                      rect().center().y()-minidisplay->rect().center().y()-100);

    QPushButton *playButton = new QPushButton(this);
    playButton->setText("Play");
    QFont font;
    font.setPointSize(14);
    playButton->setFont(font);
    playButton->setFixedSize(100, 50);
    playButton->move(rect().center().x()-playButton->rect().center().x(),
                     rect().bottom()-playButton->height()-50);
    playButton->setToolTip("(Space)");

    QPushButton *pauseButton = new QPushButton(this);
    pauseButton->hide();
    pauseButton->setText("Pause");
    pauseButton->setFont(font);
    pauseButton->setFixedSize(100, 50);
    pauseButton->move(rect().center().x()-pauseButton->rect().center().x(),
                     rect().bottom()-pauseButton->height()-50);
    pauseButton->setToolTip("(Space)");

    lcdScore = new QLCDNumber(this);
    lcdScore->setFixedSize(190, 90);
    lcdScore->move(rect().center().x() - lcdScore->rect().center().x(), 20);

    QLCDNumber *lcdLevel = new QLCDNumber(this);
    lcdLevel->setFixedSize(70, 70);
    lcdLevel->setDigitCount(2);
    lcdLevel->move(rect().center().x() - lcdLevel->rect().center().x(), 400);

    connect(playButton, SIGNAL(clicked()), display, SLOT(play()));

    connect(pauseButton, SIGNAL(clicked()), display, SLOT(pause()));

    connect(display, SIGNAL(gamePause()), pauseButton, SLOT(hide()));
    connect(display, SIGNAL(gamePause()), playButton, SLOT(show()));

    connect(display, SIGNAL(gamePlay()), playButton, SLOT(hide()));
    connect(display, SIGNAL(gamePlay()), pauseButton, SLOT(show()));

    connect(display, SIGNAL(startGame(int, int)), minidisplay, SLOT(play(int, int)));
    connect(display, SIGNAL(levelChange(int)), lcdLevel, SLOT(display(int)));
    connect(display, SIGNAL(scoreChange(int)), this, SLOT(newScore(int)));
}

MenuWidget::~MenuWidget()
{
    delete lcdScore;
    //delete this;
}

void MenuWidget::newScore(int n)
{
    lcdScore->display(n);
    if (n > maxScore) {
        maxScore = n;
        std::ofstream scoreFile("score.dat");
        scoreFile << maxScore;
        scoreFile.close();
        update();
    }
}

void MenuWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    QFont font("Consolas", 12);
    painter.setFont(font);
    painter.drawText(10, 15, "Score:");
    painter.drawText(30, 130, "Highest score:");
    painter.drawText(60, 155, QString::number(maxScore));
    painter.drawText(30, 190, "Next figure:");
    painter.drawText(70, 390, "Level:");
}

