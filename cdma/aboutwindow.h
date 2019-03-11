#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
QT_END_NAMESPACE

class Aboutwindow : public QDialog
{
    Q_OBJECT
public:
    explicit Aboutwindow(QDialog *parent = nullptr);

signals:

public slots:
    void on_btn_close();
private:
    QLabel* m_label;
    QPushButton* m_button;
};

#endif // ABOUTWINDOW_H
