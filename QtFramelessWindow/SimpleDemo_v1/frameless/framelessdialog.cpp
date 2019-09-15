#include "framelessdialog.h"
#include <QtDebug>
#include <QtWidgets>
#include "windowsizer.h"

#if defined(Q_OS_WIN)
#include <QtWinExtras>
#endif

class FramelessDialog::FramelessDialogPrivate
{
public:
    QVBoxLayout* layout = nullptr;
    QWidget* centralWidget = nullptr;
    QWidget* titleBar = nullptr;
    QMenuBar* menuBar = nullptr;

    QVBoxLayout* contentLayout = nullptr;

    QLabel* iconLabel = nullptr;
    QLabel* titleLabel = nullptr;
    QToolButton* closeButton = nullptr;

    QString buttonStyle = QStringLiteral("QToolButton {color:lightgray;background-color:transparent;} QToolButton:pressed {color:white;} QToolButton:hover {color:white;}");

    QPoint dragPos;
    bool dragging = false;

    QPointer<WindowSizer> sizer = nullptr;

    bool animateIn = true;

    bool active = true;

    int borderWidth = 6;

    QWidget* w = nullptr;
};

FramelessDialog::FramelessDialog(QWidget *parent) : QDialog(parent), d(new FramelessDialogPrivate)
{
    d->layout = new QVBoxLayout(this);

#if defined(Q_OS_WIN)
    setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    setMouseTracking(true);

    d->layout->addWidget(d->titleBar = new QWidget);
    d->layout->addLayout(d->contentLayout = new QVBoxLayout, 1);

    d->titleBar->setFixedHeight(28);
    d->layout->setSpacing(0);
    d->layout->setContentsMargins(QMargins(d->borderWidth + 2, d->borderWidth + 2, d->borderWidth + 2, d->borderWidth + 2));

    auto makeTitleBar = [this] {
        auto layout = new QHBoxLayout(d->titleBar);
        layout->setContentsMargins(QMargins(11, 0, 8, 0));
        layout->setSpacing(0);
        layout->addWidget(d->iconLabel = new QLabel);
        d->iconLabel->setScaledContents(true);
        d->iconLabel->setFixedSize(16, 16);
        layout->addSpacing(6);
        layout->addWidget(d->titleLabel = new QLabel, 2);
        layout->addWidget(d->closeButton = new QToolButton);

        auto palette = d->titleLabel->palette();
        palette.setColor(QPalette::WindowText, Qt::white);
        d->titleLabel->setPalette(palette);

        d->closeButton->setAutoRaise(true);
    };

    makeTitleBar();

    connect(d->closeButton, &QToolButton::clicked, this, [this]{this->close();});

    auto font = d->closeButton->font();
    font.setFamily("FontAwesome");
    font.setPixelSize(16);
    d->closeButton->setFont(font);
    d->closeButton->setText(QChar(0xf00d));
    d->closeButton->setStyleSheet(d->buttonStyle);

    d->closeButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    d->closeButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    if (parent) {
        do {
            if (parent->metaObject()->indexOfProperty("icon") != -1) {
                auto pixmap = parent->property("icon").value<QPixmap>();
                if (!pixmap.isNull()) {
                    this->setIcon(pixmap);
                    break;
                }
            }
            if (parent->metaObject()->indexOfProperty("windowIcon") != -1) {
                auto pixmap = parent->property("windowIcon").value<QIcon>().pixmap(32, 32);
                if (!pixmap.isNull()) {
                    this->setIcon(pixmap);
                    break;
                }
            }

            QWidget* mainWindow = nullptr;
            auto windows = qApp->topLevelWidgets();
            if (windows.size() == 1) mainWindow = windows.first();

            if (!mainWindow) {
                for (auto window : windows) {
                    if (window->metaObject()->className() == QStringLiteral("MainWidget")) {
                        mainWindow = window;
                    }
                }
            }

            if (!mainWindow) break;

            if (mainWindow->metaObject()->indexOfProperty("icon") != -1) {
                auto pixmap = mainWindow->property("icon").value<QPixmap>();
                if (!pixmap.isNull()) {
                    this->setIcon(pixmap);
                    break;
                }
            }

            auto pixmap = mainWindow->windowIcon().pixmap(32, 32);
            if (!pixmap.isNull()) {
                this->setIcon(pixmap);
            }
        } while(false);
    }

    d->sizer = new WindowSizer(this);
    d->sizer->setBorderWidth(d->borderWidth);

    setAttribute(Qt::WA_TranslucentBackground);
    setMinimumSize(200, 50);

    d->titleBar->installEventFilter(this);

    d->iconLabel->installEventFilter(this);
#else
    d->layout->setContentsMargins(QMargins(0, 0, 0, 0));
#endif
}

FramelessDialog::~FramelessDialog()
{

}

void FramelessDialog::setCentralWidget(QWidget *w)
{
    d->w = w;

    if (d->w) {
        d->layout->addWidget(d->w);

#if defined(Q_OS_WIN)
        d->w->installEventFilter(this);
#endif
    }
}

bool FramelessDialog::eventFilter(QObject *watched, QEvent *event)
{
#if defined(Q_OS_WIN)
    if (d->w && watched == d->w) {
        if (event->type() == QEvent::Enter) {
            if (d->sizer) d->sizer->reset();
        }
    } else if (watched == d->titleBar) {
        if (event->type() == QEvent::Enter) {
            if (d->sizer) d->sizer->reset();
        }
    } else if (watched == d->iconLabel) {
        if (event->type() == QEvent::MouseButtonDblClick) {
            this->close();
            return true;
        }
    }
#endif
    return QDialog::eventFilter(watched, event);
}

void FramelessDialog::setResizeable(bool resize)
{
#if defined(Q_OS_WIN)
    if (resize) {
        if (!d->sizer) d->sizer = new WindowSizer(this);
    } else {
        this->removeEventFilter(d->sizer);
        d->sizer->deleteLater();
        d->sizer = nullptr;
    }
#else
    Q_UNUSED(resize)
#endif
}

void FramelessDialog::setWindowTitle(const QString &title)
{
#if defined(Q_OS_WIN)
    d->titleLabel->setText(title);
#else
    QDialog::setWindowTitle(title);
#endif
}

void FramelessDialog::setIcon(const QPixmap &icon)
{
#if defined(Q_OS_WIN)
    d->iconLabel->setPixmap(icon);
#else
    setWindowIcon(icon);
#endif
}

QPixmap FramelessDialog::icon() const
{
#if defined(Q_OS_WIN)
    if (d->iconLabel->pixmap())
        return *d->iconLabel->pixmap();
    return QPixmap();
#else
    return this->windowIcon().pixmap(48, 48);
#endif
}

QVBoxLayout* FramelessDialog::contentLayout() const
{
#if defined(Q_OS_WIN)
    return d->contentLayout;
#else
    return d->layout;
#endif
}

void FramelessDialog::paintEvent(QPaintEvent *event)
{
#if defined(Q_OS_WIN)
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    auto rect = this->rect() - QMargins(d->borderWidth, d->borderWidth, d->borderWidth, d->borderWidth);
    painter.fillRect(rect, Qt::white);

    QColor color(QRgb(0));

    auto pen = painter.pen();
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setCapStyle(Qt::RoundCap);

    auto w = this->width();
    auto h = this->height();

    for(auto i = 0; i < d->borderWidth; ++i) {
        color.setAlpha(50 - i * 10);
        pen.setColor(color);
        painter.setPen(pen);
        painter.drawRect(d->borderWidth - i, d->borderWidth - i, w - (d->borderWidth - i) * 2, h - (d->borderWidth - i) * 2);
    }

    QColor borderColor(QStringLiteral("#2E4F7B"));
    QColor tintColor(this->isActiveWindow() ? QStringLiteral("#4E79A8") : QStringLiteral("#7294BA"));
    if (this->isModal()) {
        tintColor = d->active ? QStringLiteral("#4E79A8") : QStringLiteral("#7294BA");
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(tintColor);
    painter.drawRect(QRect(rect.topLeft(), QSize(rect.width(), 28)));

    pen.setWidth(1);
    pen.setColor(borderColor);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(rect);

    pen.setWidth(2);
    pen.setColor(tintColor);
    painter.setPen(pen);
    painter.drawRect(rect - QMargins(1, 1, 1, 1));
#else
    QDialog::paintEvent(event);
#endif

}

void FramelessDialog::mousePressEvent(QMouseEvent *event)
{
#if defined(Q_OS_WIN)
    auto localPos = event->pos();

    if (event->button() == Qt::LeftButton && d->titleBar->frameGeometry().contains(localPos)) {
        d->dragPos = localPos;
        d->dragging = true;
    }
#endif

    QDialog::mousePressEvent(event);
}

void FramelessDialog::mouseMoveEvent(QMouseEvent *event)
{
#if defined(Q_OS_WIN)
    if (d->dragging && (event->buttons() & Qt::LeftButton)) {
        this->move(event->globalPos() - d->dragPos);
    }
#endif

    QDialog::mouseMoveEvent(event);
}

void FramelessDialog::mouseReleaseEvent(QMouseEvent *event)
{
    d->dragging = false;

    QDialog::mouseReleaseEvent(event);
}

void FramelessDialog::setAnimateIn(bool animate)
{
    d->animateIn = animate;
}

int FramelessDialog::exec()
{
#if defined(Q_OS_WIN)
    if (d->animateIn) {
        this->setWindowOpacity(0.0);
        QPropertyAnimation* anim = new QPropertyAnimation(this, "windowOpacity");
        anim->setDuration(500);
        anim->setEasingCurve(QEasingCurve::OutBack); // just demonstration, there are a lot of curves to choose
        anim->setStartValue(0.0);
        anim->setEndValue(1.0);
        anim->start(QAbstractAnimation::DeleteWhenStopped);
    }
#endif

    return QDialog::exec();
}

bool FramelessDialog::nativeEvent(const QByteArray &eventType, void *message, long *result)
{

#if defined(Q_OS_WIN)
    MSG* msg = reinterpret_cast<MSG*>(message);

    switch(msg->message) {
    case WM_NCACTIVATE:
        d->active = (bool)(msg->wParam);
        this->update();
        break;
    }
#endif

    return QDialog::nativeEvent(eventType, message, result);
}
