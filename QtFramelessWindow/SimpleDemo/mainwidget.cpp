#include "mainwidget.h"
#include <QtWidgets>
#include "settinglistwidget.h"
#include "bannerwidget.h"

class MainWidget::MainWidgetPrivate
{
public:
    SettingListWidget* listWidget = Q_NULLPTR;
    QStackedWidget* stackedWidget = Q_NULLPTR;
};

MainWidget::MainWidget(QWidget *parent) :
    FramelessWidget(parent), d(new MainWidgetPrivate)
{
    setWindowTitle(tr("Simple Frameless Window Demo"));
    setWindowIcon(QPixmap(":/icon.ico"));

    auto createBottomLayout = [this] {
        auto layout = new QHBoxLayout;
        layout->setSpacing(0);
        layout->setContentsMargins(QMargins(0, 0, 0, 0));

        d->listWidget = new SettingListWidget(this);
        layout->addWidget(d->listWidget);

        d->stackedWidget = new QStackedWidget(this);
        layout->addWidget(d->stackedWidget);
        return layout;
    };

    auto layout = this->contentLayout();
    layout->addWidget(new BannerWidget(this));
    layout->addLayout(createBottomLayout());

    d->listWidget->setFixedWidth(96);
    d->listWidget->setWordWrap(true);

    {
        auto item = new QListWidgetItem;
        item->setIcon(QIcon(":/item1.png"));
        item->setText(QStringLiteral("Item 1"));
        d->listWidget->addItem(item);
    }
    {
        auto item = new QListWidgetItem;
        item->setIcon(QIcon(":/item2.png"));
        item->setText(QStringLiteral("Item 2"));
        d->listWidget->addItem(item);
    }
    {
        auto item = new QListWidgetItem;
        item->setIcon(QIcon(":/item3.png"));
        item->setText(QStringLiteral("Item 3"));
        d->listWidget->addItem(item);
    }
    {
        auto item = new QListWidgetItem;
        item->setIcon(QIcon(":/item4.png"));
        item->setText(QStringLiteral("Item 4"));
        d->listWidget->addItem(item);
    }

    d->stackedWidget->addWidget(new QWidget(this));

    d->stackedWidget->addWidget([this] {
        auto w = new QWidget;
        auto pal = w->palette();
        pal.setColor(QPalette::Window, QColor("skyblue"));
        w->setPalette(pal);
        w->setAutoFillBackground(true);
        return w;
    }());
    d->stackedWidget->addWidget([this] {
        auto w = new QWidget;
        auto pal = w->palette();
        pal.setColor(QPalette::Window, QColor("steelblue"));
        w->setPalette(pal);
        w->setAutoFillBackground(true);
        return w;
    }());
    d->stackedWidget->addWidget([this] {
        auto w = new QWidget;
        auto pal = w->palette();
        pal.setColor(QPalette::Window, QColor("dodgerblue"));
        w->setPalette(pal);
        w->setAutoFillBackground(true);
        return w;
    }());

    connect(d->listWidget, &QListWidget::currentRowChanged, d->stackedWidget, &QStackedWidget::setCurrentIndex);

    d->listWidget->setCurrentRow(0);

    this->fit();
}

MainWidget::~MainWidget()
{
}

void MainWidget::fit()
{
    auto screenSize = qApp->primaryScreen()->size();
    auto preferredSize = screenSize * 2 / 3;
    if (preferredSize.width() < 800) {
        preferredSize.setWidth(800);
    }
    if (preferredSize.height() < 640) {
        preferredSize.setHeight(640);
    }

    QSettings settings;

    if (settings.value("maximized", false).toBool()) {
        this->resize(preferredSize);
    } else {
        this->resize(settings.value("size", preferredSize).toSize());

        auto center = qApp->primaryScreen()->availableGeometry().center();
        auto windowPos = center - QPoint{this->width() / 2, this->height() / 2};

        this->move(windowPos);
    }
}
