#pragma once

#include <QObject>

class QWebEnginePage;

class QJsContext : public QObject
{
	Q_OBJECT

public:
	QJsContext(QObject *parent = Q_NULLPTR);
	~QJsContext();

	//向html页面发送消息 cmd为js
	void sendJsCmd(QWebEnginePage* page, const QString& cmd);
	//主动发送触发信号
	void sendSignal(float x,float y) {
		emit sendPositionSignal(x,y);
	}
Q_SIGNALS:
	void sendPositionSignal(float x,float y); //发送位置信号

public slots:
	void jsCallBack(const QString& msg);	//由js 中的 channel 对象进行调用
};
