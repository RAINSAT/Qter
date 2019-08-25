
#include <QtWidgets/QApplication>
#include <QUrl>

#include "qjscontext.h"
#include "qmapview.h"
#include <QFile>
#include <QTextCodec>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
#if 1
	QMapView view;
	view.loadMap(QUrl::fromLocalFile(R"(E:\ZHD\ZHDCloudService\QWebviewDemo\Resources\BMap.html)"));
	//view.loadMap(QUrl("http://www.google.cn/maps/@23.1368266,113.2981891,10.96z"));
	QJsContext context;
	view.registerChannelObject(&context);
	view.show();
#endif

	return a.exec();
}
