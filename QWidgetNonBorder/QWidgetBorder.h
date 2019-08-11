#pragma once

#include <QWidget>
class QMouseEvent;

/****************************************!
*@brief  
*@author zyxwy
*@date   2019
 ÎÞ±ß¿ò¸¨ÖúÀà   
****************************************/

class QWidgetBorder : public QWidget
{
    Q_OBJECT

public:
    QWidgetBorder(QWidget *parent = Q_NULLPTR);
    ~QWidgetBorder();

protected:
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void mousePressEvent(QMouseEvent*) override;

private:
    void setNonBorder();

    QPoint m_pos;
    bool m_Moveing;
};

