#include "QWidgetBorder.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidgetBorder w;
    w.show();

    return a.exec();
}
