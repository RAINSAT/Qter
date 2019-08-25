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

	void loadMap(QUrl& url); //加载地图
	void registerChannelObject(QObject* object); //为QWebchannel 注册对象
	const QWebEnginePage* getSourcePage() const;

	QMapView (const QMapView&) = delete;
	QMapView& operator=(const QMapView&) = delete;
protected:
	void initWebview();			//初始化webview界面内容

signals:
	void loadfinished(); //加载结束

private slots:
	void  onBtnClicked();

private:
	QWebEngineView* m_webView;
	QWebChannel* m_channel;
	QPushButton* m_btn;
};
