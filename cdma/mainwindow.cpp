#include "mainwindow.h"
#include "login.h"
#include "aboutwindow.h"

#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <QCloseEvent>
#include <QPalette>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("CDMA");
    setWindowIcon(QIcon("main.png"));
    setMinimumSize(640,480);
    setAutoFillBackground(true);
    mdiArea = new QMdiArea(this);
    setCentralWidget(mdiArea);

    //这一段代码在没有设置mdiarea的时候可以实现用图片将背景涂满，但在mdi的时候有问题
//    QPalette palet;
//    palet.setBrush(QPalette::Background,QBrush(QPixmap(":/img/1.jpg")));
//    setPalette(palet);//mdiArea->setPalette(palet);也是不可以的

    mdiArea->setBackground(Qt::NoBrush);
    mdiArea->setStyleSheet("background-image:url(\":/img/1.jpg\")");

    //设置菜单以及动作
    CreateActions();

}

MainWindow::~MainWindow()
{

}

//设置菜单以及动作成员函数
void MainWindow::CreateActions()
{
    //管理菜单
    menuManager = menuBar()->addMenu("管理");

    login = menuManager->addAction("登陆");
    login->setShortcut(QKeySequence::Open);
    connect(login,&QAction::triggered,this,&MainWindow::loginfunc);

    logout = menuManager->addAction("注销");
    logout->setShortcut(QKeySequence("Ctrl+P"));
    connect(logout,&QAction::triggered,this,&MainWindow::logoutfunc);

    exits = menuManager->addAction("退出");
    exits->setShortcut(QKeySequence("Alt+F4"));
    connect(exits,&QAction::triggered,this,&MainWindow::close);

    //窗口菜单
    menuWindow = menuBar()->addMenu("窗口");
    actionScript = menuWindow->addAction("执行脚本");
    actionScript->setShortcut(QKeySequence("Ctrl+T"));
    connect(actionScript,&QAction::triggered,this,&MainWindow::execScript);

    //数据菜单
    menuData = menuBar()->addMenu("数据");

    //帮助菜单
    menuHelp = menuBar()->addMenu("帮助");
    actionHelp = menuHelp->addAction("关于");
    actionHelp->setShortcut(Qt::Key_F1);
    connect(actionHelp,&QAction::triggered,this,&MainWindow::about);

}

//重写closeevent事件
void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton button= QMessageBox::information(this,"退出","是否退出程序？",QMessageBox::Yes,QMessageBox::No);

    if(button == QMessageBox::Yes)
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }

}

void MainWindow::loginfunc()
{
    Login log;
    //log.setWindowModality(Qt::WindowModality);
    //log.setAttribute(Qt::WA_DeleteOnClose); //这一句是设置窗口属性为关闭后自己销毁内存，但是调用exec后关闭时会导致异常。
    log.exec();

    if(log.islogin)
    {
        qDebug()<<"denglu";
    }


}


void MainWindow::logoutfunc()
{

}


void MainWindow::execScript()
{
    qDebug()<<"execScript";
}

void MainWindow::about()
{
    Aboutwindow win;
    win.exec();
}
