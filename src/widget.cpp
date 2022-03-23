#include "widget.h"
#include "ui_widget.h"
#include "QWindow"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : MWidgetBase(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setTitleBar(ui->titleBar);
    connect(this, &MWidgetBase::windowStateChanged, this, &Widget::on_windowStateChanged);
}

Widget::~Widget()
{
    delete ui;
}

/**
 * @brief               窗口状态改变
 * @param windowStates
 */
void Widget::on_windowStateChanged(Qt::WindowStates windowStates)
{
    qDebug() << windowStates;
}

