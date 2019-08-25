#include "qmapview.h"
#include "qjscontext.h"

#include <QWebChannel>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QPushButton>
#include <QHash>

#pragma execution_character_set("utf-8")

QMapView::QMapView(QWidget *parent) : QWidget(parent)
{
	initWebview();
	connect(m_webView, &QWebEngineView::loadFinished, [this]() {
		emit loadfinished();
	});
	connect(m_btn, &QPushButton::clicked, this, &QMapView::onBtnClicked);
}

QMapView::~QMapView()
{
}


void QMapView::initWebview()
{
	//创建 WebView
	m_webView = new QWebEngineView(this);
	//创建 WebChannel
	m_channel = new QWebChannel(this);
	//将注册好的WebChannel 设置为当前页面的通道
	m_webView->page()->setWebChannel(m_channel);
	m_webView->setMinimumSize(1366, 768);
	m_webView->setGeometry(0, 0, 1366, 768);
	m_btn = new QPushButton(this);
	m_btn->setText("点击");
	m_btn->setGeometry(1366, 0, 100, 25);
}

void QMapView::loadMap(QUrl& url)
{
	m_webView->load(url);
}

void QMapView::registerChannelObject(QObject* object)
{
	m_channel->registerObject("context", object);
}

const QWebEnginePage * QMapView::getSourcePage() const
{
	if (m_webView)
	{
		return m_webView->page();
	}
	return nullptr;
}

void QMapView::onBtnClicked()
{
	if (m_channel)
	{
		QHash<QString,QObject*> regObj = m_channel->registeredObjects();
		if (!regObj.keys().empty())
		{
			QJsContext* obj =qobject_cast<QJsContext*>(regObj["context"]);
			obj->sendSignal(116.404,39.919);
		}
	}
}