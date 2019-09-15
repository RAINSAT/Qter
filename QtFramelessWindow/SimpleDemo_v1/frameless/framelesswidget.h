#ifndef FRAMELESSWIDGET_H
#define FRAMELESSWIDGET_H

#include <QWidget>
#include <memory>

class QVBoxLayout;

class FramelessWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QPixmap icon READ icon WRITE setWindowIcon)
public:
    explicit FramelessWidget(QWidget *parent = nullptr);
    ~FramelessWidget();

#if defined(Q_OS_WIN)
    bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;

    void paintEvent(QPaintEvent *event) override;

#endif

    QVBoxLayout* contentLayout() const;

    void setWindowTitle(const QString &);
    void setWindowIcon(const QPixmap &icon);

    QPixmap icon() const;
protected:
private:

    bool event(QEvent *event) override;

    class FramelessWidgetPrivate;
    const std::unique_ptr<FramelessWidgetPrivate> d;
};

#endif // FRAMELESSWIDGET_H
