#include "ftpclientmanager.h"
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

FtpClientManager::FtpClientManager(QObject *parent)
	: QObject(parent)
{
	m_url.setScheme("ftp");
	m_manager = new QNetworkAccessManager(this);
	m_reply = Q_NULLPTR;
}

FtpClientManager::~FtpClientManager()
{
	
}

void FtpClientManager::setUserInfo(const QString & user, const QString & password)
{
	m_url.setUserName(user);
	m_url.setPassword(password);
}

void FtpClientManager::setHostInfo(const QString & host, int port)
{
	m_url.setHost(host);
	m_url.setPort(port);
}

//文件上传
void FtpClientManager::put(const QString & fileName, const QString & filePath)
{
	QFile file(fileName);
	m_url.setUrl(filePath);
	QByteArray array;
	if (file.open(QIODevice::ReadOnly))
	{
		array = file.readAll();
	}

	m_reply = m_manager->put(QNetworkRequest(m_url), array);
	QObject::connect(m_reply, SIGNAL(uploadProgress(qint64, qint64)), this, SIGNAL(uploadProgress(qint64, qint64)));
	QObject::connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SIGNAL(error(QNetworkReply::NetworkError)));
}

//文件下载
void FtpClientManager::get(const QString & fileName, const QString & filePath)
{
	m_fileName = fileName;
	m_url.setUrl(filePath);
	m_reply = m_manager->get(QNetworkRequest(m_url));

	connect(m_reply, &QNetworkReply::finished, this, &FtpClientManager::downloadFile);
	connect(m_reply, SIGNAL(downloadProgress(qint64, qint64)), this, SIGNAL(downloadProgress(qint64, qint64)));
}


void FtpClientManager::downloadFile()
{
	QFile file(m_fileName);
	if (file.open(QIODevice::ReadWrite | QIODevice::Append))
	{
		QByteArray array = m_reply->readAll();
		file.write(array);
		file.close();
	}

	m_reply->deleteLater();
	m_reply = Q_NULLPTR;
}