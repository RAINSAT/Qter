#ifndef FRAMELESSDIALOG_H
#define FRAMELESSDIALOG_H

#include <QDialog>
#include <memory>

class QVBoxLayout;

class FramelessDialog : public QDialog
{
    Q_OBJECT
public:
    explicit FramelessDialog(QWidget *parent = nullptr);
    ~FramelessDialog();

    void paintEvent(QPaintEvent *event) override;

    QVBoxLayout* contentLayout() const;

    void setWindowTitle(const QString &);
    void setIcon(const QPixmap &icon);

    QPixmap icon() const;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void setResizeable(bool);

    void setAnimateIn(bool);

    int exec() override;

    bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;

    bool eventFilter(QObject *, QEvent *) override;

    void setCentralWidget(QWidget* w);
protected:
private:
    class FramelessDialogPrivate;
    const std::unique_ptr<FramelessDialogPrivate> d;
};

#endif // FRAMELESSDIALOG_H
