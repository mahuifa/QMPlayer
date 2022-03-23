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

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
