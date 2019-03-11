#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>

QT_BEGIN_NAMESPACE
class QMenu;
class QAction;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    void CreateActions();

    void closeEvent(QCloseEvent*);

private slots:
    void loginfunc();
    void logoutfunc();

    void execScript();

    void about();
private:
    QMdiArea* mdiArea;
    QMenu* menuManager;
    QMenu* menuWindow;
    QMenu* menuData;
    QMenu* menuHelp;

    QAction* login;
    QAction* logout;
    QAction* exits;

    QAction* actionScript;

    QAction* actionHelp;
};

#endif // MAINWINDOW_H
