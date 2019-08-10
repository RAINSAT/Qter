#include "qftpdemo.h"
#include <QNetworkAccessManager>
#include <QFile>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "ftpclientmanager.h"

QFtpDemo::QFtpDemo(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	this->m_manager = new QNetworkAccessManager(this);

	QObject::connect(ui.upBtn, &QPushButton::clicked, this, &QFtpDemo::on_upBtn_clicked);
	QObject::connect(ui.downBtn, &QPushButton::clicked, this, &QFtpDemo::on_downBtn_clicked);
}

void QFtpDemo::on_downBtn_clicked()
{
	ui.lineEdit->setText("downing");
}

void QFtpDemo::on_upBtn_clicked()
{
	QString filePth = "E:\\ZHD\\ZHDCloudService\\x64\\cloudservice\\upload\\1.txt";
	QFile file(filePth);
	QByteArray fileArray;
	if (file.open(QIODevice::ReadOnly))
	{
		fileArray = file.readAll();
	}

	m_manager->setNetworkAccessible(QNetworkAccessManager::Accessible);

	QUrl url("ftp://172.16.104.205/1.txt");
	url.setScheme("ftp");
	url.setPort(21);
	
	QNetworkReply* reply = m_manager->put(QNetworkRequest(url),fileArray);
	connect(m_manager, &QNetworkAccessManager::finished, this, &QFtpDemo::putfinish);

}

void QFtpDemo::putfinish()
{
	ui.lineEdit->setText("put finish");

	QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
	QByteArray ar = reply->readAll();
}