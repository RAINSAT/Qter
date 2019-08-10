/********************************************************************************
** Form generated from reading UI file 'qftpdemo.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QFTPDEMO_H
#define UI_QFTPDEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QFtpDemoClass
{
public:
    QLineEdit *lineEdit;
    QPushButton *upBtn;
    QPushButton *downBtn;

    void setupUi(QWidget *QFtpDemoClass)
    {
        if (QFtpDemoClass->objectName().isEmpty())
            QFtpDemoClass->setObjectName(QStringLiteral("QFtpDemoClass"));
        QFtpDemoClass->resize(453, 164);
        lineEdit = new QLineEdit(QFtpDemoClass);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(60, 50, 321, 20));
        upBtn = new QPushButton(QFtpDemoClass);
        upBtn->setObjectName(QStringLiteral("upBtn"));
        upBtn->setGeometry(QRect(90, 100, 75, 23));
        downBtn = new QPushButton(QFtpDemoClass);
        downBtn->setObjectName(QStringLiteral("downBtn"));
        downBtn->setGeometry(QRect(250, 100, 75, 23));

        retranslateUi(QFtpDemoClass);

        QMetaObject::connectSlotsByName(QFtpDemoClass);
    } // setupUi

    void retranslateUi(QWidget *QFtpDemoClass)
    {
        QFtpDemoClass->setWindowTitle(QApplication::translate("QFtpDemoClass", "QFtpDemo", Q_NULLPTR));
        upBtn->setText(QApplication::translate("QFtpDemoClass", "upload", Q_NULLPTR));
        downBtn->setText(QApplication::translate("QFtpDemoClass", "download", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QFtpDemoClass: public Ui_QFtpDemoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QFTPDEMO_H
