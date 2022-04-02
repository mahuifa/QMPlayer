#include "sidebar.h"
#include "ui_sidebar.h"
#include <QPropertyAnimation>
#include <qdebug.h>

Sidebar::Sidebar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sidebar)
{
    ui->setupUi(this);

    m_paShow = new QPropertyAnimation(this, "pos");
    m_paShow->setDuration(500);
}

Sidebar::~Sidebar()
{
    delete ui;
}

/**
 * @brief  打开显示动画
 */
void Sidebar::show()
{
    m_paShow->setStartValue(QPoint(0 - this->width(), 0));
    m_paShow->setEndValue(QPoint(0, 0));
    m_paShow->setEasingCurve(QEasingCurve::OutQuad);
    m_paShow->start();
}

/**
 * @brief 关闭显示动画
 */
void Sidebar::hide()
{
    m_paShow->setStartValue(QPoint(0, 0));
    m_paShow->setEndValue(QPoint(0 - this->width(), 0));
    m_paShow->setEasingCurve(QEasingCurve::OutQuad);
    m_paShow->start();
}
