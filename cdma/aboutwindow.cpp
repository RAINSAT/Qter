#include "aboutwindow.h"

#include <QPushButton>
#include <QLabel>
Aboutwindow::Aboutwindow(QDialog *parent) : QDialog(parent)
{
    setWindowTitle("Cdma about");

    this->setBaseSize(640,480);
    this->m_label = new QLabel(this);
    m_label->setPixmap(QPixmap(":/img/2.jpg"));

    this->m_button = new QPushButton(this);
    this->m_button->setGeometry(QRect(500,350,100,50));
    this->m_button->setText("close");
    connect(m_button,&QPushButton::clicked,this,&Aboutwindow::on_btn_close);
}

void Aboutwindow::on_btn_close()
{
    this->close();
}
