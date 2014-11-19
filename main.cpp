#include "widget.h"

#include "capture/captureVga.h"
#include "com/membufUtils.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
