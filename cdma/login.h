#ifndef LOGIN_H
#define LOGIN_H
#include <QDialog>
#include <QString>
QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

class Login : public QDialog
{
    Q_OBJECT
public:
    Login();
private:
    QLabel* user,*password;
    QLineEdit* lineUser,*linePass;
    QPushButton* in,*out;

private slots:
    void login();
    void cancel();

public:
    QString userName;
    QString passwd;

    bool islogin;

};

#endif // LOGIN_H
