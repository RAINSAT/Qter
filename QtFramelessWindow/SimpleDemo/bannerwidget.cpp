#include "bannerwidget.h"
#include <QtWidgets>

class BannerWidget::BannerWidgetPrivate
{
public:
    QLabel* websiteLabel = Q_NULLPTR;
    QLabel* techSupportLabel = Q_NULLPTR;
};

BannerWidget::BannerWidget(QWidget *parent) :
    QWidget(parent), d(new BannerWidgetPrivate)
{
    setFixedHeight(80);

    auto setBgColor = [this] {
        auto palette = this->palette();
        palette.setColor(QPalette::Window, Qt::gray);
        setPalette(palette);
        this->setAutoFillBackground(true);
    };

    auto createLogoWidget = [this] {
        auto logoWidget = new QLabel(this);
        logoWidget->setPixmap(QPixmap(":/logo.png"));
        return logoWidget;
    };

    auto createInfoLayout = [this] {
        auto vlayout = new QVBoxLayout;
        vlayout->setSpacing(0);
        vlayout->setAlignment(Qt::AlignCenter);

        auto formLayout = new QFormLayout;
        formLayout->addRow(tr("Website:"), d->websiteLabel = new QLabel);
        formLayout->addRow(tr("Tech Support:"), d->techSupportLabel = new QLabel);
        formLayout->addRow(tr("Version:"), new QLabel(qApp->applicationVersion()));

        d->websiteLabel->setTextFormat(Qt::RichText);
        d->websiteLabel->setOpenExternalLinks(true);
        d->websiteLabel->setText("<a href=\"http://www.mycompany.com.cn\">www.mycompany.com.cn</a>");

        d->techSupportLabel->setTextFormat(Qt::RichText);
        d->techSupportLabel->setOpenExternalLinks(true);
        d->techSupportLabel->setText("<a href=\"mailto:mymail@mycompany.com.cn\">mymail@mycompany.com.cn</a>");

        vlayout->addLayout(formLayout);
        return vlayout;
    };

    setBgColor();

    auto layout = new QHBoxLayout(this);
    layout->addSpacing(20);

    layout->addWidget(createLogoWidget());

    layout->addStretch(1);

    layout->addLayout(createInfoLayout());

    layout->addSpacing(40);
}

BannerWidget::~BannerWidget()
{
}
