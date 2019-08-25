#include "qjscontext.h"

#include <QWebEnginePage>
#include <QDebug>

QJsContext::QJsContext(QObject *parent)
	: QObject(parent)
{
}

QJsContext::~QJsContext()
{
}

void QJsContext::sendJsCmd(QWebEnginePage* page, const QString& cmd)
{
	if (page)
	{
		page->runJavaScript(cmd, [](auto t) {
			qDebug() << "execuate success";
		});
	}
}

void QJsContext::jsCallBack(const QString& msg)
{
	qDebug() << msg;
}