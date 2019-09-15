#include "settinglistwidget.h"
#include <QtWidgets>

class SettingListDelegate: public QStyledItemDelegate
{
public:
    SettingListDelegate(QListView *list = nullptr) : QStyledItemDelegate(list) {
        this->list = list;
    }
    ~SettingListDelegate() {}

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
        auto sz = QStyledItemDelegate::sizeHint(option, index);
        sz.setHeight(96);
        return sz;
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
        auto style = list->style();
        auto icon = index.data(Qt::DecorationRole).value<QIcon>();
        auto iconSize = list->iconSize();
        auto pixmap = icon.pixmap(iconSize);
        if (option.state & QStyle::State_Selected) {
            painter->fillRect(option.rect, "steelblue");
        } else if (option.state & QStyle::State_MouseOver) {
            painter->fillRect(option.rect, "skyblue");
        }
        auto pen = painter->pen();
        pen.setColor(option.state & QStyle::State_Selected ? "#eee" : "#000");
        painter->setPen(pen);
        style->drawItemPixmap(painter, option.rect, Qt::AlignCenter, pixmap);
        style->drawItemText(painter, option.rect, Qt::AlignBottom | Qt::AlignHCenter, option.palette, true, index.data().toString());
    }
private:
    QListView* list = nullptr;
};

class SettingListWidgetPrivate
{
public:
};

SettingListWidget::SettingListWidget(QWidget *parent)
    : QListWidget(parent), d(new SettingListWidgetPrivate)
{
    setIconSize({64, 64});
    setItemDelegate(new SettingListDelegate(this));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedWidth(96);
    setFrameStyle(QFrame::NoFrame);
}

SettingListWidget::~SettingListWidget() {}

