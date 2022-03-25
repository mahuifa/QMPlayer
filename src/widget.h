#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mwidgetbase.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public MWidgetBase
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void on_windowStateChanged(Qt::WindowStates windowStates);

private slots:
    void on_but_close_clicked();

    void on_but_max_clicked();

    void on_but_min_clicked();

private:
    void init();               // 初始化
    void connectSlot();        // 绑定信号槽
    void loadStyle();          // 加载样式表

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
