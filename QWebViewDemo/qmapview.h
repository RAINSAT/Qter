#pragma once

#include <QObject>
#include <QWidget>

class QWebChannel;
class QJsContext;
class QPushButton;
class QWebEngineView;
class QWebEnginePage;

class QMapView : public QWidget
{
	Q_OBJECT

public:
	QMapView(QWidget *parent = Q_NULLPTR);
	~QMapView();

	void loadMap(QUrl& url); //���ص�ͼ
	void registerChannelObject(QObject* object); //ΪQWebchannel ע�����
	const QWebEnginePage* getSourcePage() const;

	QMapView (const QMapView&) = delete;
	QMapView& operator=(const QMapView&) = delete;
protected:
	void initWebview();			//��ʼ��webview��������

signals:
	void loadfinished(); //���ؽ���

private slots:
	void  onBtnClicked();

private:
	QWebEngineView* m_webView;
	QWebChannel* m_channel;
	QPushButton* m_btn;
};
