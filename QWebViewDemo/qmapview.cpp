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
	//���� WebView
	m_webView = new QWebEngineView(this);
	//���� WebChannel
	m_channel = new QWebChannel(this);
	//��ע��õ�WebChannel ����Ϊ��ǰҳ���ͨ��
	m_webView->page()->setWebChannel(m_channel);
	m_webView->setMinimumSize(1366, 768);
	m_webView->setGeometry(0, 0, 1366, 768);
	m_btn = new QPushButton(this);
	m_btn->setText("���");
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