#ifndef BANNERWIDGET_H
#define BANNERWIDGET_H

#include <QWidget>

class BannerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BannerWidget(QWidget *parent = Q_NULLPTR);
    ~BannerWidget();

private:
    class BannerWidgetPrivate;
    const QScopedPointer<BannerWidgetPrivate> d;
};

#endif // BANNERWIDGET_H
