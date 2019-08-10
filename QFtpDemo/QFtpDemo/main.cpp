#include "qftpdemo.h"
#include <QtWidgets/QApplication>

#include "ftpclientmanager.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	/*QFtpDemo w;
	w.show();*/

	FtpClientManager client;
	//client.get("E:/ZHD/QFtpDemo/x64/Debug/1.txt", "ftp://172.16.104.205/1.txt");
	client.put(R"(E:\\ZHD\\ZHDCloudService\\x64\\cloudservice\\upload\\3.txt)", "ftp://172.16.104.205/home/3.txt");

	return a.exec();
}
