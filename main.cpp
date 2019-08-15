#include "widget.h"
#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget *widget = new Widget;
    QMainWindow w;
    w.setCentralWidget(widget);
    w.setFixedSize(575, 720);
    w.show();
    return a.exec();
}
