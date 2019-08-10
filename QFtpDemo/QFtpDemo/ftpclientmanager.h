#pragma once

#include <QObject>
#include <QUrl>
#include <QFileInfo>
#include <QNetworkReply>

class QNetworkAccessManager;

class FtpClientManager : public QObject
{
	Q_OBJECT

public:
	FtpClientManager(QObject *parent = Q_NULLPTR);
	~FtpClientManager();

	void setUserInfo(const QString& user, const QString& password);
	void setHostInfo(const QString&host, int port = 21);

	/**
	 * ftp 上传
	 * fileName: 待上传的文件名
	 * filePath: ftp服务器上的路径
	 * eg:"ftp://172.16.104.205/1.txt" 如果路径中有文件夹 确保文件夹存在
	 */
	void put(const QString& fileName, const QString& filePath);

	/**
	 * ftp 下载
	 * fileName: 文件要保存在本地的路径 + 文件名
	 * filePath: ftp服务器上文件的位置 类似于 ftp://172.16.104.205/1.txt
	 */
	void get(const QString& fileName, const QString& filePath);

private slots :
	void downloadFile();

signals:
	void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
	void error(QNetworkReply::NetworkError);
	void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

private:
	QNetworkAccessManager* m_manager;
	QNetworkReply* m_reply;
	QUrl m_url;
	QString m_fileName;
};
