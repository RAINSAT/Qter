#include "framelesswidget.h"
#include <QtDebug>
#include <QtWidgets>

#if defined(Q_OS_WIN)
#include <qt_windows.h>
#include <windowsx.h>
#include <QtWinExtras>
#include <windows.h>
#include <Winuser.h>
#endif

class FramelessWidget::FramelessWidgetPrivate
{
public:
    QVBoxLayout* layout = nullptr;

#if defined(Q_OS_WIN)
    LONG aeroBorderlessFlag = WS_POPUP | WS_THICKFRAME | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX;
    LONG basicBorderlessFlag = WS_POPUP | WS_THICKFRAME | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX;

    bool compositionEnabled() const
    {
        return QtWin::isCompositionEnabled();
    }

    QLabel* iconLabel = nullptr;
    QLabel* titleLabel = nullptr;
    QToolButton* minButton = nullptr;
    QToolButton* maxButton = nullptr;
    QToolButton* closeButton = nullptr;

    QString buttonStyle = "QToolButton {color:lightgray;background-color:transparent;} QToolButton:pressed {color:white;} QToolButton:hover {color:white;}";

    QWidget* centralWidget = nullptr;
    QWidget* titleBar = nullptr;
    QMenuBar* menuBar = nullptr;

    QVBoxLayout* contentLayout = nullptr;

#endif

};

FramelessWidget::FramelessWidget(QWidget *parent)
    : QWidget(parent), d(new FramelessWidgetPrivate)
{
#if defined(Q_OS_WIN)
    setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

    auto hwnd = reinterpret_cast<HWND>(this->winId());

    const LONG style = d->compositionEnabled() ? d->aeroBorderlessFlag : d->basicBorderlessFlag;
    SetWindowLongPtr(hwnd, GWL_STYLE, style);

    if (d->compositionEnabled()) {
        QtWin::extendFrameIntoClientArea(this, 1, 1, 1, 1);
    }

    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);

    d->layout = new QVBoxLayout(this);
    d->layout->addWidget(d->titleBar = new QWidget);
    d->layout->addLayout(d->contentLayout = new QVBoxLayout, 1);

    auto palette = d->titleBar->palette();
    palette.setColor(QPalette::Window, 0x4E79A8);
    d->titleBar->setPalette(palette);
    d->titleBar->setAutoFillBackground(true);

    d->titleBar->setFixedHeight(28);
    d->layout->setSpacing(0);
    d->layout->setContentsMargins(QMargins(2, 2, 2, 2));
    d->layout->setMargin(0);
    d->contentLayout->setContentsMargins(QMargins(2, 0, 2, 2));

    auto makeTitleBar = [this] {
        auto layout = new QHBoxLayout(d->titleBar);
        layout->setContentsMargins(QMargins(11, 0, 8, 0));
        layout->setSpacing(0);
        layout->addWidget(d->iconLabel = new QLabel);
        d->iconLabel->setScaledContents(true);
        d->iconLabel->setFixedSize(16, 16);
        layout->addSpacing(6);
        layout->addWidget(d->titleLabel = new QLabel, 2);
        layout->addWidget(d->minButton = new QToolButton);
        layout->addWidget(d->maxButton = new QToolButton);
        layout->addWidget(d->closeButton = new QToolButton);

        auto palette = d->titleLabel->palette();
        palette.setColor(QPalette::WindowText, Qt::white);
        d->titleLabel->setPalette(palette);

        d->minButton->setAutoRaise(true);
        d->maxButton->setAutoRaise(true);
        d->closeButton->setAutoRaise(true);
    };

    makeTitleBar();

    connect(d->closeButton, &QToolButton::clicked, this, [this]{this->close();});
    connect(d->minButton, &QToolButton::clicked, this, [this]{this->showMinimized();});
    connect(d->maxButton, &QToolButton::clicked, this, [this] {
        if (this->isMaximized()) {
            this->showNormal();
        } else {
            this->showMaximized();
        }
    });

    auto font = d->closeButton->font();
    font.setFamily("FontAwesome");
    font.setPixelSize(16);
    d->closeButton->setFont(font);
    d->closeButton->setText(QChar(0xf00d));
    d->closeButton->setStyleSheet(d->buttonStyle);

    font = d->maxButton->font();
    font.setFamily("FontAwesome");
    font.setPixelSize(12);
    d->maxButton->setFont(font);
    d->maxButton->setText(QChar(0xf2d0));
    d->maxButton->setStyleSheet(d->buttonStyle);

    d->minButton->setFont(font);
    d->minButton->setText(QChar(0xf2d1));
    d->minButton->setStyleSheet(d->buttonStyle);

    d->minButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    d->maxButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    d->closeButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    setMinimumSize(200, 200);
#else
    d->layout = new QVBoxLayout(this);
    d->layout->setContentsMargins(QMargins(0, 0, 0, 0));
    d->layout->setSpacing(0);
#endif
}

FramelessWidget::~FramelessWidget()
{

}

bool FramelessWidget::event(QEvent *event)
{
#if defined(Q_OS_WIN)
    if (event->type() == QEvent::WindowStateChange) {
        if (this->isMaximized()) {
            d->maxButton->setText(QChar(0xf2d2));
            if (d->compositionEnabled()) {
                auto margin = 8 / this->devicePixelRatioF();
                d->layout->setContentsMargins(QMargins(margin, margin, margin, margin));
                d->layout->update();
            } else {
                d->layout->setContentsMargins(QMargins(0, 0, 0, 0));
                d->layout->update();
            }
        } else {
            d->maxButton->setText(QChar(0xf2d0));
            d->layout->setContentsMargins(QMargins(0, 0, 0, 0));
            d->layout->update();
        }

        this->update();
    } else if (event->type() == QEvent::Resize) {
        this->update();
    } else if (event->type() == QEvent::WindowDeactivate || event->type() == QEvent::WindowActivate) {
        QColor tintColor(this->isActiveWindow() ? 0x4E79A8 : 0x7294BA);

        auto palette = d->titleBar->palette();
        palette.setColor(QPalette::Window, tintColor);
        d->titleBar->setPalette(palette);
    }

#endif

    return QWidget::event(event);
}

void FramelessWidget::setWindowTitle(const QString &title)
{
#if defined(Q_OS_WIN)
    d->titleLabel->setText(title);
#else
    QWidget::setWindowTitle(title);
#endif
}

void FramelessWidget::setWindowIcon(const QPixmap &icon)
{
#if defined(Q_OS_WIN)
    d->iconLabel->setPixmap(icon);
#else
    QWidget::setWindowIcon(icon);
#endif
}

QPixmap FramelessWidget::icon() const
{
#if defined(Q_OS_WIN)
    if (d->iconLabel->pixmap())
        return *d->iconLabel->pixmap();
    return QPixmap();
#else
    return this->windowIcon().pixmap(48, 48);
#endif
}

QVBoxLayout* FramelessWidget::contentLayout() const
{
#if defined(Q_OS_WIN)
    return d->contentLayout;
#else
    return d->layout;
#endif
}

#if defined(Q_OS_WIN)
bool FramelessWidget::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
#if (QT_VERSION == QT_VERSION_CHECK(5, 11, 1))
    MSG* msg = *reinterpret_cast<MSG**>(message);
#else
    MSG* msg = reinterpret_cast<MSG*>(message);
#endif

    switch(msg->message) {
    case WM_SETFOCUS:
    {
        Qt::FocusReason reason;
        if (::GetKeyState(VK_LBUTTON) < 0 || ::GetKeyState(VK_RBUTTON) < 0)
            reason = Qt::MouseFocusReason;
        else if (::GetKeyState(VK_SHIFT) < 0)
            reason = Qt::BacktabFocusReason;
        else
            reason = Qt::TabFocusReason;

        QFocusEvent e(QEvent::FocusIn, reason);
        QApplication::sendEvent(this, &e);
    }
        break;
    case WM_NCCALCSIZE:
    {
        *result = 0;
        return true;
    }
        break;
    case WM_SYSCOMMAND:
    {
        if (msg->wParam == SC_KEYMENU && msg->lParam == VK_SPACE) {

            auto hwnd = (HWND)this->winId();
            HMENU menu = GetSystemMenu(hwnd, false);

            if (menu) {
                MENUITEMINFO mii;
                mii.cbSize = sizeof(MENUITEMINFO);
                mii.fMask = MIIM_STATE;
                mii.fType = 0;

                mii.fState = MF_ENABLED;

                // update the options
                mii.fState = MF_ENABLED;
                SetMenuItemInfo(menu, SC_RESTORE, FALSE, &mii);
                SetMenuItemInfo(menu, SC_SIZE, FALSE, &mii);
                SetMenuItemInfo(menu, SC_MOVE, FALSE, &mii);
                SetMenuItemInfo(menu, SC_MAXIMIZE, FALSE, &mii);
                SetMenuItemInfo(menu, SC_MINIMIZE, FALSE, &mii);

                mii.fState = MF_GRAYED;

                WINDOWPLACEMENT wp;
                GetWindowPlacement(hwnd, &wp);

                switch (wp.showCmd)
                {
                case SW_SHOWMAXIMIZED:
                    SetMenuItemInfo(menu, SC_SIZE, FALSE, &mii);
                    SetMenuItemInfo(menu, SC_MOVE, FALSE, &mii);
                    SetMenuItemInfo(menu, SC_MAXIMIZE, FALSE, &mii);
                    SetMenuDefaultItem(menu, SC_CLOSE, FALSE);
                    break;
                case SW_SHOWMINIMIZED:
                    SetMenuItemInfo(menu, SC_MINIMIZE, FALSE, &mii);
                    SetMenuDefaultItem(menu, SC_RESTORE, FALSE);
                    break;
                case SW_SHOWNORMAL:
                    SetMenuItemInfo(menu, SC_RESTORE, FALSE, &mii);
                    SetMenuDefaultItem(menu, SC_CLOSE, FALSE);
                    break;
                }

                auto devicePixelRatio = qApp->devicePixelRatio();
                auto localPos = d->iconLabel->frameGeometry().bottomLeft();
                localPos.setY(d->titleBar->frameGeometry().bottom());
                auto globalPos = this->mapToGlobal(localPos);
                globalPos.rx() *= devicePixelRatio;
                globalPos.ry() *= devicePixelRatio;
                BOOL cmd = TrackPopupMenuEx(menu, TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RETURNCMD, globalPos.x(), globalPos.y(), hwnd, nullptr);
                if (cmd) PostMessage(hwnd, WM_SYSCOMMAND, cmd, 0);

                *result = 0;
                return true;
            }
        }
    }
        break;
    case WM_SYSKEYDOWN:
    {
        if (msg->wParam == VK_SPACE) {
            *result = 0;
            return true;
        }
    }
        break;
    case WM_NCHITTEST:
    {
        auto x = GET_X_LPARAM(msg->lParam);
        auto y = GET_Y_LPARAM(msg->lParam);
        auto borderX = GetSystemMetrics(SM_CXFRAME) + GetSystemMetrics(92);
        auto borderY = GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(92);
        borderX /= qApp->devicePixelRatio();
        borderY /= qApp->devicePixelRatio();
        RECT winrect;
        GetWindowRect((HWND)(this->winId()), &winrect);

        auto devicePixelRatio = qApp->devicePixelRatio();
        auto localPos = this->mapFromGlobal(QPoint(x / devicePixelRatio, y / devicePixelRatio));

        if (d->iconLabel->frameGeometry().contains(localPos)) {
            *result = HTSYSMENU;
            return true;
        }

        if (d->closeButton->frameGeometry().contains(localPos) || d->minButton->frameGeometry().contains(localPos) || d->maxButton->frameGeometry().contains(localPos)) {
            *result = HTCLIENT;
            return true;
        }

        auto titleBarGeometry = d->titleBar->frameGeometry();
        if (this->isMaximized()) {
            if (titleBarGeometry.contains(localPos)) {
                *result = HTCAPTION;
                return true;
            }
        }
        titleBarGeometry -= QMargins(borderX, borderY, borderX, 0);
        if (titleBarGeometry.contains(localPos)) {
            *result = HTCAPTION;
            return true;
        }

        if (x >= winrect.left && x <= winrect.left + borderX) {
            if (y >= winrect.top && y <= winrect.top + borderY) {
                *result = HTTOPLEFT;
                return true;
            }
            if (y > winrect.top + borderY && y < winrect.bottom - borderY) {
                *result = HTLEFT;
                return true;
            }
            if (y >= winrect.bottom - borderY && y <= winrect.bottom) {
                *result = HTBOTTOMLEFT;
                return true;
            }
        } else if (x > winrect.left + borderX && x < winrect.right - borderX) {
            if (y >= winrect.top && y <= winrect.top + borderY) {
                *result = HTTOP;
                return true;
            }
            if (y > winrect.top + borderY && y < winrect.top + borderY + 20) {
                *result = HTCAPTION;
                return true;
            }
            if (y >= winrect.bottom - borderY && y <= winrect.bottom) {
                *result = HTBOTTOM;
                return true;
            }
        } else if (x >= winrect.right - borderX && x <= winrect.right) {
            if (y >= winrect.top && y <= winrect.top + borderY) {
                *result = HTTOPRIGHT;
                return true;
            }
            if (y > winrect.top + borderY && y < winrect.bottom - borderY) {
                *result = HTRIGHT;
                return true;
            }
            if (y >= winrect.bottom - borderY && y <= winrect.bottom) {
                *result = HTBOTTOMRIGHT;
                return true;
            }
        } else {
            *result = HTNOWHERE;
            return true;
        }
    }
        break;
    case WM_NCACTIVATE:
    {
        if (!d->compositionEnabled()) {
            *result = 1;
            return true;
        }
    }
        break;
//    case WM_DWMCOMPOSITIONCHANGED:
//    {
//        if (this->isMaximized()) {
//            if (d->compositionEnabled()) {
//                auto margin = 8 / this->devicePixelRatioF();
//                d->layout->setContentsMargins(QMargins(margin, margin, margin, margin));
//            } else {
//                d->layout->setContentsMargins(QMargins(0, 0, 0, 0));
//            }
//        } else {
//            d->layout->setContentsMargins(QMargins(0, 0, 0, 0));
//        }
//    }
//        break;
    case WM_GETMINMAXINFO:
    {
        auto info = (MINMAXINFO*)msg->lParam;
        info->ptMinTrackSize.x = this->minimumWidth();
        info->ptMinTrackSize.y = this->minimumHeight();
        info->ptMaxTrackSize.x = this->maximumWidth();
        info->ptMaxTrackSize.y = this->maximumHeight();

        if (::MonitorFromWindow(::FindWindow(L"Shell_TrayWnd", nullptr), MONITOR_DEFAULTTONEAREST) ==
                ::MonitorFromWindow((HWND)(this->winId()) , MONITOR_DEFAULTTONEAREST))
        {
            info->ptMaxPosition.x = 0;
            info->ptMaxPosition.y = 0;

            info->ptMaxSize.x = GetSystemMetrics(SM_CXFULLSCREEN) + GetSystemMetrics(SM_CXDLGFRAME);
            // + GetSystemMetrics(SM_CXBORDER)+ GetSystemMetrics(SM_CYBORDER);

            info-> ptMaxSize.y = GetSystemMetrics(SM_CYFULLSCREEN) + GetSystemMetrics(SM_CYCAPTION);
            // + GetSystemMetrics(SM_CYDLGFRAME) + GetSystemMetrics(SM_CYBORDER);
        }
        return true;
    }
        break;
    default:
        break;
    }
    return QWidget::nativeEvent(eventType, message, result);
}

void FramelessWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    auto rect = this->rect();
    if (this->isMaximized() && d->compositionEnabled()) {
        auto margin = 8 / this->devicePixelRatioF();
        rect -= QMargins(margin, margin, margin, margin);
    }

    QColor borderColor(0x2E4F7B);
    QColor tintColor(this->isActiveWindow() ? 0x4E79A8 : 0x7294BA);

    painter.setPen(Qt::NoPen);
    painter.setBrush(tintColor);

    QPen pen;
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
}
#endif
