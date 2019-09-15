#ifndef SETTINGLISTWIDGET_H
#define SETTINGLISTWIDGET_H

#include <QListWidget>

class SettingListWidgetPrivate;
class SettingListWidget : public QListWidget
{
    Q_OBJECT
public:
    SettingListWidget(QWidget *parent = nullptr);
    ~SettingListWidget();

private:
    const QScopedPointer<SettingListWidgetPrivate> d;
};

#endif // SETTINGLISTWIDGET_H
