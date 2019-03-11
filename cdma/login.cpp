#include "login.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>

Login::Login()
{
    islogin = false;
    setWindowTitle("登录");
    QGridLayout* layout = new QGridLayout(this);
    this->user = new QLabel("用户名：",this);
    this->password = new QLabel("密码：",this);

    this->in = new QPushButton("确定",this);
    this->out = new QPushButton("取消",this);

    this->lineUser = new QLineEdit(this);
    this->lineUser->setPlaceholderText("username");
    this->linePass = new QLineEdit(this);
    this->linePass->setPlaceholderText("input password");
    this->linePass->setEchoMode(QLineEdit::Password);

    layout->addWidget(user,0,0,Qt::AlignHCenter);
    layout->addWidget(password,1,0,Qt::AlignHCenter);
    layout->addWidget(in,2,0,Qt::AlignHCenter);
    layout->addWidget(out,2,1,Qt::AlignHCenter);
    layout->addWidget(lineUser,0,1,Qt::AlignHCenter);
    layout->addWidget(linePass,1,1,Qt::AlignHCenter);

    layout->setMargin(10);
    //this->setFixedSize(60,50);
    this->setContentsMargins(30,30,30,30);


    connect(in,&QPushButton::clicked,this,&Login::login);
    connect(out,&QPushButton::clicked,this,&Login::cancel);
}

void Login::login()
{
    islogin = true;
    QString strUser = this->lineUser->text().trimmed();
    QString strPass = this->linePass->text();
    if(strUser.isEmpty() || strPass.isEmpty())
    {
        QMessageBox::warning(this,"warn","请输入完整信息！！");
        return;
    }
    this->userName = strUser;
    this->passwd = strPass;
    close();
}

void Login::cancel()
{
    islogin = false;
    close();
}
