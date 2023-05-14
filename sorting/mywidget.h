#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <widget.h>
#include "mywidgetthree.h"
//namespace Ui {
//class MyWidget;
//}

class MyWidget : public QWidget
{
    Q_OBJECT//公有的

public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget();//使用信号与操必须有的东西


    //新增部分
    void ComeBack();


private:
//    Ui::MyWidget *ui;
    Widget *w;
    QFont font2;//字体设置
    QPushButton *button1;//开始排序按钮
    QPushButton *button2;//关闭按钮
    QPushButton *button3;//返回按钮

public slots:
    void  click_bubble();
    void  click_insert();
    void  click_heap();
    void  click_shell();
    void  click_choice();
    void  click_merge();
    void  click_bucket();
    void  click_quick();
    void  click_radix();
    void  click_Stack();
    void  click_Tree();
    void click_XZ();
    void click_CR();
    void click_JH();



};

#endif // MYWIDGET_H
