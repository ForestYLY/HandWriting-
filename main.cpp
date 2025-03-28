#include "widget.h"

#include <QApplication>
#include <QRect>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    int widgetWidth = 800;
    int widgetHeight = 560;
    QRect screenRect = QApplication::primaryScreen()->geometry();
    w.setGeometry((screenRect.width() - widgetWidth) / 2, (screenRect.height() - widgetHeight) / 2, widgetWidth, widgetHeight);

    w.show();
    return a.exec();
}
