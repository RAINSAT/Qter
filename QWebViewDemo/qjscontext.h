#pragma once

#include <QObject>

class QWebEnginePage;

class QJsContext : public QObject
{
	Q_OBJECT

public:
	QJsContext(QObject *parent = Q_NULLPTR);
	~QJsContext();

	//��htmlҳ�淢����Ϣ cmdΪjs
	void sendJsCmd(QWebEnginePage* page, const QString& cmd);
	//�������ʹ����ź�
	void sendSignal(float x,float y) {
		emit sendPositionSignal(x,y);
	}
Q_SIGNALS:
	void sendPositionSignal(float x,float y); //����λ���ź�

public slots:
	void jsCallBack(const QString& msg);	//��js �е� channel ������е���
};
