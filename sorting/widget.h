#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "bubble.h"
#include <QPainter>
#include <QDialog>
#include "mywidgettwo.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();


    //新增部分
    void DealData();

    void paintEvent(QPaintEvent *e);
    void open_bubble();
    void open_bucket();
    void open_insert();
    void open_heap();
    void open_shell();
    void open_choice();
    void open_merge();
    void open_radix();
    void open_quick();
    int flag;




signals:
    void start();       //开启子线程
public slots:
    void deal(int c);   //处理来自子线程的消息
    void deal_Color(int c1,int c2,int c3);
    //新增部分
    void ComeBack();


private slots:


public:
    Ui::Widget *ui;
    int blockH;     //绘图方块的高
    int blockW;     //绘图方块的宽
    int length;     //数组长度
    int *data;      //数组
    int cur;        //排序的位子
    int cur1,cur2;
    QThread *thread;
    Bubble *bubble;
    MywidgetTwo *My;
    QDialog *d1;
    QPushButton *button1;

};

#endif // WIDGET_H
