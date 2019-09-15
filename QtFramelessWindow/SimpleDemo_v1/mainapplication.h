#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include <QApplication>

class MainApplication : public QApplication
{
    Q_OBJECT
public:
    MainApplication(int &argc, char** argv);
    ~MainApplication();

private:
    class MainApplicationPrivate;
    const QScopedPointer<MainApplicationPrivate> d;
};

#endif // MAINAPPLICATION_H
