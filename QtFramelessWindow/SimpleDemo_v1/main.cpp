#include "mainwidget.h"
#include "mainapplication.h"
#include <QFontDatabase>
#include <QCryptographicHash>
#include <QtDebug>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
    //QCoreApplication::setAttribute(Qt::AA_DisableWindowContextHelpButton);

    MainApplication a(argc, argv);

    QFontDatabase::addApplicationFont(":/FontAwesome.otf");

    MainWidget w;
    w.show();

    return a.exec();
}
