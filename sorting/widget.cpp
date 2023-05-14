#include "widget.h"
#include "ui_widget.h"
#include "qpushbutton.h"
#include "unistd.h"
#include "mywidget.h"
#include "QDebug"
#include "mywidgettwo.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QPushButton *button1=new QPushButton;
    button1->setText("排序");

    length = 15;
    blockH = 5;
    blockW = 5;
    data = new int [length];
    cur = 0;//标志颜色位
    cur1 = cur2 = 0;
    bubble = new Bubble(length,length,20,data);//建立bubble对象时传入的参数

    setWindowTitle("排序算法可视化过程");//这个代码没有用

    //setFixedSize(600,600);//固定窗体大小
    setGeometry(100,100,length*blockW + 200,length*blockH + 500);//确定窗体大小


    My = new MywidgetTwo;//成功的关键一步



}

//新增
void Widget::DealData()
{
    My->Wirte(data,length);
    My->Read();
}

//实现排序的跳转到主界面
void Widget::ComeBack()
{
    MyWidget *t = new MyWidget;
    t->show();
}

//绘画的整体工程
void Widget::paintEvent(QPaintEvent *){

    QPainter painter;
    if(data == nullptr)
        return ;
    painter.begin(this);
    for(int i = 0; i< length;i++){
        QRect rect(i*blockW,height()-data[i]*blockH*5,//确定对应值的相应高度
                   blockW - 1,data[i]*blockH*5);
        if(i == cur){
            painter.fillRect(rect,Qt::green);//cur是确定每次比对的曲线位置以及对应颜色
        }else {
            painter.fillRect(rect,Qt::red);//非正在对比元素的对应颜色
        }
    }
    painter.end();

}



void Widget::deal(int c)//将cur值通过deal进行传值
{
    cur = c;

    repaint();  //进行重绘，这是绘制的核心部分，缺少则动画无法进行任何滚动；且不能使用睡眠，因为会导致多次比较不断进行
}



Widget::~Widget()//析构函数
{
    thread->quit();     //结束子线程
    thread->wait();     //回收子线程资源
    delete ui;
}


void Widget::open_bubble()
{
    My->flagC = 2;
    thread = new QThread(this);
    bubble->moveToThread(thread);
    connect(bubble,&Bubble::bubbleSignal,this,&Widget::deal);//建立信号和响应的槽函数（在排序算法中会重复调用）
    connect(bubble,&Bubble::bubbleSignal4,this,&Widget::deal_Color);//建立信号和响应的槽函数（最新
    connect(bubble,&Bubble::bubbleSignal3,this,&Widget::DealData);//建立信号和响应的槽函数（在排序算法中会重复调用）(新增
    connect(bubble,&Bubble::bubbleSignal2,My,&MywidgetTwo::printTable);//最后完成时打印排好的表格(新增
    connect(this,&Widget::start,bubble,&Bubble::run_bubble);//建立信号和响应的槽函数（即排序算法）
    thread->start();    //开启子线程
    emit start();       //运行子线程的goBubble函数，运行的起始端
}



void Widget::open_bucket()
{
    thread = new QThread(this);//创建线程
    bubble->moveToThread(thread);
    connect(bubble,&Bubble::bubbleSignal,this,&Widget::deal);
    connect(bubble,&Bubble::bubbleSignal3,this,&Widget::DealData);//建立信号和响应的槽函数（在排序算法中会重复调用）(新增
    connect(bubble,&Bubble::bubbleSignal2,My,&MywidgetTwo::printTable);//最后完成时打印排好的表格(新增
    connect(bubble,&Bubble::bubbleSignal4,this,&Widget::deal_Color);//建立信号和响应的槽函数（最新
    connect(this,&Widget::start,bubble,&Bubble::run_bucket);
    thread->start();    //开启子线程
    emit start();       //运行子线程的goBubble函数
}
void Widget::open_shell()
{
    My->flagC = 8;
    thread = new QThread(this);//创建线程
    bubble->moveToThread(thread);
    connect(bubble,&Bubble::bubbleSignal,this,&Widget::deal);
    connect(bubble,&Bubble::bubbleSignal3,this,&Widget::DealData);//建立信号和响应的槽函数（在排序算法中会重复调用）(新增
    connect(bubble,&Bubble::bubbleSignal2,My,&MywidgetTwo::printTable);//最后完成时打印排好的表格(新增
    connect(bubble,&Bubble::bubbleSignal4,this,&Widget::deal_Color);//建立信号和响应的槽函数（最新
    connect(this,&Widget::start,bubble,&Bubble::run_shell);
    thread->start();    //开启子线程
    emit start();       //运行子线程的goBubble函数
}
void Widget::open_choice()
{
    My->flagC = 4;
    thread = new QThread(this);
    bubble->moveToThread(thread);
    connect(bubble,&Bubble::bubbleSignal,this,&Widget::deal);
    connect(bubble,&Bubble::bubbleSignal3,this,&Widget::DealData);//建立信号和响应的槽函数（在排序算法中会重复调用）(新增
    connect(bubble,&Bubble::bubbleSignal2,My,&MywidgetTwo::printTable);//最后完成时打印排好的表格(新增
    connect(bubble,&Bubble::bubbleSignal4,this,&Widget::deal_Color);//建立信号和响应的槽函数（最新
    connect(this,&Widget::start,bubble,&Bubble::run_choice);
    thread->start();    //开启子线程
    emit start();       //运行子线程的goBubble函数
}
void Widget::open_insert()
{
    My->flagC = 1;
    thread = new QThread(this);
    bubble->moveToThread(thread);
    connect(bubble,&Bubble::bubbleSignal,this,&Widget::deal);//deal绘制操作
    connect(bubble,&Bubble::bubbleSignal3,this,&Widget::DealData);//建立信号和响应的槽函数（在排序算法中会重复调用）(新增
    connect(bubble,&Bubble::bubbleSignal2,My,&MywidgetTwo::printTable);//最后完成时打印排好的表格(新增
    connect(bubble,&Bubble::bubbleSignal4,this,&Widget::deal_Color);//建立信号和响应的槽函数（最新
    connect(this,&Widget::start,bubble,&Bubble::run_insertion);//执行算法
    thread->start();    //开启子线程
    emit start();       //运行子线程的goBubble函数
}
void Widget::open_merge()
{
    My->flagC = 5;
    thread = new QThread(this);
    bubble->moveToThread(thread);
    connect(bubble,&Bubble::bubbleSignal,this,&Widget::deal);
    connect(bubble,&Bubble::bubbleSignal3,this,&Widget::DealData);//建立信号和响应的槽函数（在排序算法中会重复调用）(新增
    connect(bubble,&Bubble::bubbleSignal2,My,&MywidgetTwo::printTable);//最后完成时打印排好的表格(新增
    connect(bubble,&Bubble::bubbleSignal4,this,&Widget::deal_Color);//建立信号和响应的槽函数（最新
    connect(this,&Widget::start,bubble,&Bubble::run_merge);
    thread->start();    //开启子线程
    emit start();       //运行子线程的goBubble函数
}
void Widget::open_quick()
{
    My->flagC = 7;
    thread = new QThread(this);
    bubble->moveToThread(thread);
    connect(bubble,&Bubble::bubbleSignal,this,&Widget::deal);
    connect(bubble,&Bubble::bubbleSignal3,this,&Widget::DealData);//建立信号和响应的槽函数（在排序算法中会重复调用）(新增
    connect(bubble,&Bubble::bubbleSignal2,My,&MywidgetTwo::printTable);//最后完成时打印排好的表格(新增
    connect(bubble,&Bubble::bubbleSignal4,this,&Widget::deal_Color);//建立信号和响应的槽函数（最新
    connect(bubble,&Bubble::bubbleSignal5,My,&MywidgetTwo::dealSimple);
    connect(this,&Widget::start,bubble,&Bubble::run_quick);
    thread->start();    //开启子线程
    emit start();       //运行子线程的goBubble函数
}
void Widget::open_radix()
{
    My->flagC = 6;
    thread = new QThread(this);
    bubble->moveToThread(thread);
    connect(bubble,&Bubble::bubbleSignal,this,&Widget::deal);
    connect(bubble,&Bubble::bubbleSignal3,this,&Widget::DealData);//建立信号和响应的槽函数（在排序算法中会重复调用）(新增
    connect(bubble,&Bubble::bubbleSignal2,My,&MywidgetTwo::printTable);//最后完成时打印排好的表格(新增
    connect(bubble,&Bubble::bubbleSignal4,this,&Widget::deal_Color);//建立信号和响应的槽函数（最新
    connect(this,&Widget::start,bubble,&Bubble::run_radix);
    thread->start();    //开启子线程
    emit start();       //运行子线程的goBubble函数
}
void Widget::open_heap()
{
    My->flagC = 3;
    thread = new QThread(this);
    bubble->moveToThread(thread);
    connect(bubble,&Bubble::bubbleSignal,this,&Widget::deal);
    connect(bubble,&Bubble::bubbleSignal3,this,&Widget::DealData);//建立信号和响应的槽函数（在排序算法中会重复调用）(新增
    connect(bubble,&Bubble::bubbleSignal2,My,&MywidgetTwo::printTable);//最后完成时打印排好的表格(新增
    connect(bubble,&Bubble::bubbleSignal4,this,&Widget::deal_Color);//建立信号和响应的槽函数（最新
    connect(this,&Widget::start,bubble,&Bubble::run_heap);//RUN_HEAP即运行算法
    thread->start();    //开启子线程
    emit start();       //运行子线程的goBubble函数
}

void Widget::deal_Color(int c1,int c2,int c3)
{
    My->deal_Color(c1,c2,c3);
}





