#include "widget.h"
#include "ui_widget.h"
#include "QWindow"
#include <QDebug>
#include <QFile>
#include <QStyle>

Widget::Widget(QWidget *parent)
    : MWidgetBase(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    init();
    connectSlot();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init()
{
    loadStyle();
    ui->label_title->setText(QString("QMPlayer V%1").arg(APP_VERSION));
    this->setTitleBar(ui->titleBar);   // 设置标题栏
}

void Widget::connectSlot()
{
    connect(this, &MWidgetBase::windowStateChanged, this, &Widget::on_windowStateChanged);
}

/**
 * @brief               窗口状态改变
 * @param windowStates
 */
void Widget::on_windowStateChanged(Qt::WindowStates windowStates)
{
    switch (windowStates)
    {
    case Qt::WindowMaximized:
        ui->but_max->setProperty("Max", true);
        break;
    case Qt::WindowNoState:
        ui->but_max->setProperty("Max", false);
        break;
    default:break;
    }
    ui->but_max->style()->polish(ui->but_max);
}

/**
 * @brief 加载样式表
 */
void Widget::loadStyle()
{
    QFile file(":/Style/main.css");
    if (file.open(QFile::ReadOnly))
    {
        //用QTextStream读取样式文件不用区分文件编码 带bom也行
        QStringList list;
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line;
            in >> line;
            list << line;
        }

        file.close();
        QString qss = list.join("\n");
//        QString paletteColor = qss.mid(20, 7);
//        qApp->setPalette(QPalette(paletteColor));
        this->setStyleSheet("");
        qApp->setStyleSheet(qss);
    }
}

void Widget::on_but_close_clicked()
{
    this->close();
}

void Widget::on_but_max_clicked()
{
    if(this->isMaximized())
    {
        this->showNormal();
    }
    else
    {
        this->showMaximized();
    }
}

void Widget::on_but_min_clicked()
{
    this->showMinimized();
}


