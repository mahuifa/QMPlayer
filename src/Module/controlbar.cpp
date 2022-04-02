#include "controlbar.h"
#include "ui_controlbar.h"

#include <qdebug.h>
#include <qpropertyanimation.h>

ControlBar::ControlBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlBar)
{
    ui->setupUi(this);

    m_paShow = new QPropertyAnimation(this, "pos");
    m_paShow->setDuration(500);
}

ControlBar::~ControlBar()
{
    delete ui;
}

/**
 * @brief  打开显示动画
 */
void ControlBar::show()
{
    int y = this->parentWidget()->height() - this->height() - 20;
    m_paShow->setStartValue(QPoint(this->x(), this->parentWidget()->height()));
    m_paShow->setEndValue(QPoint(this->x(), y));
    m_paShow->setEasingCurve(QEasingCurve::OutQuad);
    m_paShow->start();
}

/**
 * @brief 关闭显示动画
 */
void ControlBar::hide()
{
    int y = this->parentWidget()->height() - this->height() - 20;
    m_paShow->setStartValue(QPoint(this->x(), y));
    qDebug() <<this->parentWidget()->height();
    m_paShow->setEndValue(QPoint(this->x(), this->parentWidget()->height()));
    m_paShow->setEasingCurve(QEasingCurve::OutQuad);
    m_paShow->start();
}
