#ifndef WINDOWSIZER_H
#define WINDOWSIZER_H

#include <QWidget>
#include <QCursor>
#include <memory>

class WindowSizer : public QObject
{
    Q_OBJECT
public:
    explicit WindowSizer(QWidget* parent = Q_NULLPTR);
    ~WindowSizer() = default;

    void setBorderWidth(int width);

    void reset();
private:
    int mBorderWidth;

    QWidget*    mWidget;
    QCursor     mWidgetCursor;

    QPoint   mPressedPos;
    int      mSizeDirection = 0;

    bool eventFilter(QObject* target, QEvent* event);
};

#endif // WINDOWSIZER_H
