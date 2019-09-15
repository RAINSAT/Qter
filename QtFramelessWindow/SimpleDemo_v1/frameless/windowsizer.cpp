#include "windowsizer.h"
#include <QtWidgets>

WindowSizer::WindowSizer(QWidget* parent)
    : QObject(parent)
{
    Q_ASSERT(parent);
    mBorderWidth = 8;

    mWidget = parent;
    mWidgetCursor = parent->cursor();
    auto mw = qobject_cast<QMainWindow*>(mWidget);
    if (mw && mw->centralWidget())
    {
        mw->centralWidget()->setMouseTracking(true);
    }
    mWidget->setMouseTracking(true);
    mWidget->installEventFilter(this);
}

void WindowSizer::reset()
{
    mWidget->setCursor(mWidgetCursor);
    mSizeDirection = 0;
}

void WindowSizer::setBorderWidth(int width)
{
    if (mBorderWidth != width) {
        mBorderWidth = width;
    }
}

bool WindowSizer::eventFilter(QObject* target, QEvent* event)
{
    QMouseEvent* mouseEvent;
    switch(event->type()) {
    case QEvent::MouseButtonPress:
        if (mSizeDirection != 0) {
            mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent) {
                mPressedPos = mouseEvent->globalPos();
                return true;
            }
        }
        break;
    case QEvent::MouseButtonRelease:
        if (mSizeDirection != 0) {
            mSizeDirection = 0;
            return true;
        }
        break;
    case QEvent::MouseMove:
        mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->buttons() == Qt::NoButton) {
            const auto pos = mouseEvent->pos();
            const auto px = pos.x();
            const auto py = pos.y();

            if (px < mBorderWidth && py < mBorderWidth) { // top left
                mWidget->setCursor(Qt::SizeFDiagCursor);
                mSizeDirection = 5;
            } else if (px > (mWidget->width() - mBorderWidth) && py > (mWidget->height() - mBorderWidth)) { // bottom right
                mWidget->setCursor(Qt::SizeFDiagCursor);
                mSizeDirection = 10;
            } else if (px < mBorderWidth && py > (mWidget->height() - mBorderWidth)) { // bottom left
                mWidget->setCursor(Qt::SizeBDiagCursor);
                mSizeDirection = 6;
            } else if (px > (mWidget->width() - mBorderWidth) && py < mBorderWidth) { // top right
                mWidget->setCursor(Qt::SizeBDiagCursor);
                mSizeDirection = 9;
            } else if (py < mBorderWidth) {// top
                mWidget->setCursor(Qt::SizeVerCursor);
                mSizeDirection = 1;
            } else if (py > (mWidget->height() - mBorderWidth)) { // bottom
                mWidget->setCursor(Qt::SizeVerCursor);
                mSizeDirection = 2;
            } else if (px < mBorderWidth) { // left
                mWidget->setCursor(Qt::SizeHorCursor);
                mSizeDirection = 4;
            } else if (px > (mWidget->width() - mBorderWidth)) { // right
                mWidget->setCursor(Qt::SizeHorCursor);
                mSizeDirection = 8;
            } else {
                mWidget->setCursor(mWidgetCursor);
                mSizeDirection = 0;
            }
        }
        if (mouseEvent->buttons() & Qt::LeftButton) {
            QRect rt = mWidget->geometry();
            const auto pos = mouseEvent->globalPos();
            const auto px = pos.x();
            const auto py = pos.y();

            switch(mSizeDirection) {
            case 1: // top
                rt.setY(rt.y() + py - mPressedPos.y());
                break;
            case 2: // bottom
                rt.setBottom(rt.bottom() + py - mPressedPos.y());
                break;
            case 4: // left
                rt.setX(rt.x() + px - mPressedPos.x());
                break;
            case 8: // right
                rt.setRight(rt.right() + px - mPressedPos.x());
                break;
            case 5: // top left
                rt.setX(rt.x() + px - mPressedPos.x());
                rt.setY(rt.y() + py - mPressedPos.y());
                break;
            case 6: // bottom left
                rt.setX(rt.x() + px - mPressedPos.x());
                rt.setBottom(rt.bottom() + py - mPressedPos.y());
                break;
            case 9: // top right
                rt.setRight(rt.right() + px - mPressedPos.x());
                rt.setY(rt.y() + py - mPressedPos.y());
                break;
            case 10: // bottom right
                rt.setRight(rt.right() + px - mPressedPos.x());
                rt.setBottom(rt.bottom() + py - mPressedPos.y());
                break;
            }
            if (rt.width() >= mWidget->minimumWidth() && rt.width() <= mWidget->maximumWidth()
                    && rt.height() >= mWidget->minimumHeight() && rt.height() <= mWidget->maximumHeight()) {
                mWidget->setGeometry(rt);
                mPressedPos = mouseEvent->globalPos();
            }
        }
        break;
    default:
        break;
    }
    return QObject::eventFilter(target, event);
}
