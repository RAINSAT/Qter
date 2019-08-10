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
	 * ftp �ϴ�
	 * fileName: ���ϴ����ļ���
	 * filePath: ftp�������ϵ�·��
	 * eg:"ftp://172.16.104.205/1.txt" ���·�������ļ��� ȷ���ļ��д���
	 */
	void put(const QString& fileName, const QString& filePath);

	/**
	 * ftp ����
	 * fileName: �ļ�Ҫ�����ڱ��ص�·�� + �ļ���
	 * filePath: ftp���������ļ���λ�� ������ ftp://172.16.104.205/1.txt
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
