#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "framelesswidget.h"

class MainWidget : public FramelessWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

    void fit();
private:
    class MainWidgetPrivate;
    const QScopedPointer<MainWidgetPrivate> d;
};

#endif // MAINWIDGET_H
