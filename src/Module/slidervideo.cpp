#include "slidervideo.h"

#include <qpropertyanimation.h>

SliderVideo::SliderVideo(QWidget *parent) : QSlider(parent)
{
    m_paShow = new QPropertyAnimation(this, "size");
    m_paShow->setDuration(500);
    connect(m_paShow, &QPropertyAnimation::finished, this, &SliderVideo::on_finished);
}

/**
 * @brief  打开显示动画（注意必须放在窗口改变后面，如全屏显示、还原）
 */
void SliderVideo::show()
{
    QWidget::show();
    m_paShow->setStartValue(QSize(0, this->height()));
    QSize size = this->size();
    size.setWidth(this->parentWidget()->width() * 3 / 5);
    m_paShow->setEndValue(size);
    m_paShow->setEasingCurve(QEasingCurve::OutQuad);
    m_paShow->start();
}

/**
 * @brief 关闭显示动画（注意必须放在窗口改变后面，如全屏显示、还原）
 */
void SliderVideo::hide()
{
    QSize size = this->size();
    size.setWidth(this->parentWidget()->width() * 3 / 5);
    m_paShow->setStartValue(size);
    m_paShow->setEndValue(QSize(0, this->height()));
    m_paShow->setEasingCurve(QEasingCurve::OutQuad);
    m_paShow->start();
}

void SliderVideo::on_finished()
{
    if(m_paShow->endValue().toSize().width() == 0)
    {
        QWidget::hide();
    }
}
