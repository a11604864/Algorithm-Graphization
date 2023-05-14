#include "widget.h"
#include <QApplication>
#include "mywidget.h"
#include <mywidgettwo.h>
#include "mywidgetthree.h"
#include "mywidgetfour.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);//必须有相当于main函数
    MyWidget mw;//创建窗口对象
    mw.show();//显示窗口
    return a.exec();//应用程序循坏，相当于while
}
