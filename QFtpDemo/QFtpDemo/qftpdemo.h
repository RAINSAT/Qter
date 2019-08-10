#pragma once

#include <QtWidgets/QWidget>
#include "ui_qftpdemo.h"

class QNetworkAccessManager;

class QFtpDemo : public QWidget
{
	Q_OBJECT

public:
	QFtpDemo(QWidget *parent = Q_NULLPTR);

private slots:

	void on_upBtn_clicked();
	void on_downBtn_clicked();
	void putfinish();

private:
	Ui::QFtpDemoClass ui;
	QNetworkAccessManager* m_manager;
};
