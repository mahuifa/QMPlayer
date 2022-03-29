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
    this->setWindowTitle(QString("QMPlayer V%1").arg(APP_VERSION));
    this->setTitleBar(ui->titleBar->getBackground());   // 设置标题栏
}

void Widget::connectSlot()
{
    connect(this, &MWidgetBase::windowStateChanged, ui->titleBar, &TitleBar::on_windowStateChanged);
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
        this->setStyleSheet("");
        qApp->setStyleSheet(qss);
    }
}

/**
 * @brief       隐藏Widget设置标题文本功能，添加设置标题栏文本功能
 * @param title
 */
void Widget::setWindowTitle(const QString &title)
{
    QWidget::setWindowTitle(title);
    ui->titleBar->setWindowTitle(title);
}

/**
 * @brief  界面动态布局
 */
void Widget::windowLayout()
{
    // 设置组件大小
    int l_widget = ui->videoWidget->width() * 3 / 5;
    QSize size = ui->controlBar->size();
    size.setWidth(l_widget);
    ui->controlBar->resize(size);
    size.setHeight(ui->slider_video->height());
    ui->slider_video->resize(size);

    // 设置组件位置
    int x = (ui->videoWidget->width() - ui->controlBar->width()) / 2;
    int y = ui->videoWidget->height() - ui->controlBar->height() - 20;
    ui->controlBar->move(x, y);
    int sliderY = y - ui->slider_video->height() - 5;
    ui->slider_video->move(x, sliderY);

    // 侧边栏
    int l_height = sliderY - 20;
    size = ui->sidebar->size();
    size.setHeight(l_height);
    ui->sidebar->resize(size);
    x = ui->videoWidget->width() - ui->sidebar->width();
    ui->sidebar->move(x, 0);
}

void Widget::showEvent(QShowEvent *event)
{
    MWidgetBase::showEvent(event);
    windowLayout();
}

void Widget::resizeEvent(QResizeEvent *event)
{
    MWidgetBase::resizeEvent(event);
    windowLayout();
}


