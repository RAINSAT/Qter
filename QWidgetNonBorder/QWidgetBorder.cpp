#include "QWidgetBorder.h"
#include <QMouseEvent>

QWidgetBorder::QWidgetBorder(QWidget *parent)
    : QWidget(parent)
{
    setNonBorder();
}

QWidgetBorder::~QWidgetBorder()
{

}

void QWidgetBorder::mouseMoveEvent(QMouseEvent *e)
{
    if(m_Moveing && e->buttons() == Qt::LeftButton)
    {
        move(e->globalPos()-m_pos);
        m_pos = e->globalPos() - this->pos();
    }
    return QWidget::mouseMoveEvent(e);
}

void QWidgetBorder::mouseReleaseEvent(QMouseEvent *e)
{
    m_Moveing = false;
    return QWidget::mouseReleaseEvent(e);
}

void QWidgetBorder::mousePressEvent(QMouseEvent * e)
{
    m_pos =e->globalPos()- this->pos();
    m_Moveing = true;
    return QWidget::mousePressEvent(e);
}

void QWidgetBorder::setNonBorder()
{
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint|Qt::WindowStaysOnBottomHint);
}
