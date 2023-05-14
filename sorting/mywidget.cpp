#include "mywidget.h"
#include "ui_mywidget.h"
#include "QPushButton"
#include "QGridLayout"
#include "widget.h"
#include <QDebug>
#include "mywidgetthree.h"
#include "mywidgetfour.h"
#include "mainwindow.h"
#include"mainwindowt.h"
#include"mainwindowth.h"
MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent)
    //ui(new Ui::MyWidget)
{
//    ui->setupUi(this);文字的背景
    //配置主场景
   //设置初始位置
    setGeometry(300,300,1300,1100);
   //设置主窗口图标


    setWindowTitle("算法图形化解析软件设计与实现");//设置程序标题

    QPushButton *Button[8];
    for(int i=0;i<8;i++)
    {
        Button[i]=new QPushButton(this);//图片依附于窗口
        Button[i]->setStyleSheet("font-size:50px;color:black");//字体设置

    };

    Button[0]->setText("选择排序");
    Button[1]->setText("插入排序");
    Button[2]->setText("交换排序");
    Button[3]->setText("归并排序");
    Button[4]->setText("栈的操作");
    Button[5]->setText("基数排序");
    Button[6]->setText("退出程序");
    Button[7]->setText("树的操作");


    Button[0]->setGeometry(10,50,200,150);//分别是图标的位置x和y以及图表的大小以及对应x和y
    Button[1]->setGeometry(230,50,200,150);
    Button[2]->setGeometry(450,50,200,150);//分别是图标的位置x和y以及图表的大小以及对应x和y
    Button[3]->setGeometry(670,50,200,150);
    Button[4]->setGeometry(230,220,200,150);//分别是图标的位置x和y以及图表的大小以及对应x和y
    Button[5]->setGeometry(890,50,200,150);//分别是图标的位置x和y以及图表的大小以及对应x和y
    Button[6]->setGeometry(450,220,200,150);
    Button[7]->setGeometry(10,220,200,150);

    connect(Button[0],&QPushButton::clicked, this, &MyWidget::click_XZ);//选择排序
    connect(Button[0],SIGNAL(clicked(bool)), this, SLOT(close()));//关闭的双操作

    connect(Button[1],&QPushButton::clicked, this, &MyWidget::click_CR);//插入排序
    connect(Button[1],SIGNAL(clicked(bool)), this, SLOT(close()));//关闭的双操作

    connect(Button[2],&QPushButton::clicked, this, &MyWidget::click_JH);//交换排序
    connect(Button[2],SIGNAL(clicked(bool)), this, SLOT(close()));//关闭的双操作


    connect(Button[3],SIGNAL(clicked(bool)), this, SLOT(click_merge()));//归并排序
    connect(Button[3],SIGNAL(clicked(bool)), this, SLOT(close()));//关闭的双操作

    connect(Button[4],SIGNAL(clicked(bool)), this, SLOT(click_Stack()));//栈的操作
    connect(Button[4],SIGNAL(clicked(bool)), this, SLOT(close()));//关闭的双操作


    connect(Button[5],SIGNAL(clicked(bool)), this, SLOT(click_radix()));//基数排序
    connect(Button[5],SIGNAL(clicked(bool)), this, SLOT(close()));//关闭的双操作

    connect(Button[6],&QPushButton::clicked,this,&MyWidget::close);//关闭程序

    connect(Button[7],SIGNAL(clicked(bool)), this, SLOT(click_Tree()));//树的操作
    connect(Button[7],SIGNAL(clicked(bool)), this, SLOT(close()));//关闭的双操作

}




MyWidget::~MyWidget()
{
    //delete ui;
}

//新增部分
void MyWidget::ComeBack()
{

    ;
}



void MyWidget::click_bubble()
{

    Widget *w =new Widget;
    w->setWindowTitle("冒泡排序");
    w->show();
    w->setFont(font2);

    button2 = new QPushButton(w);//注意按钮的声明需要现在头文件进行
    button2->setText("关闭程序");
    button3 = new QPushButton(w);
    button3->setText("返回");

    button1=new QPushButton(w);
    button1->setText("开始排序");
    //button1->setStyleSheet("border:2px groove blue;border-radius:5px;background-color:rgb(250,250,250);");

    button1->setGeometry(10,50,70,80);//分别是图标的位置x和y以及图表的大小以及对应x和y
    button2->setGeometry(90,50,70,80);
    button3->setGeometry(170,50,70,80);

    connect(button1,&QPushButton::clicked,w,&Widget::open_bubble);
    connect(button2,&QPushButton::clicked,w,&Widget::close);//暂时为关闭
    connect(button3,&QPushButton::clicked,w,&Widget::close);//绑定为双操作，关闭菜单
    connect(button3,&QPushButton::clicked,w,&Widget::ComeBack);//跳转返回主界面

    //实现按钮在窗口的显示
    button1->show();
    button2->show();
    button3->show();

}
void MyWidget::click_insert()
{
    Widget *w =new Widget;
    w->setWindowTitle("插入排序");
    w->show();
    w->setFont(font2);
    button1=new QPushButton(w);
    button1->setText("开始排序");
    //button1->setStyleSheet("border:2px groove blue;border-radius:5px;background-color:rgb(250,250,250);");

    button2 = new QPushButton(w);//注意按钮的声明需要现在头文件进行
    button2->setText("关闭程序");
    button3 = new QPushButton(w);
    button3->setText("返回");

    button1->setGeometry(10,50,70,80);//分别是图标的位置x和y以及图表的大小以及对应x和y
    button2->setGeometry(90,50,70,80);
    button3->setGeometry(170,50,70,80);
    connect(button1,&QPushButton::clicked,w,&Widget::open_insert);
    connect(button2,&QPushButton::clicked,w,&Widget::close);//暂时为关闭
    connect(button3,&QPushButton::clicked,w,&Widget::close);//绑定为双操作，关闭菜单
    connect(button3,&QPushButton::clicked,w,&Widget::ComeBack);//跳转返回主界面
    button1->show();//需要两次调用显示才能显示
    button2->show();
    button3->show();
}
void MyWidget::click_heap()
{
    Widget *w =new Widget;
    w->setWindowTitle("堆排序");
    w->show();
    w->setFont(font2);
    button1=new QPushButton(w);
    button1->setText("开始排序");

    button2 = new QPushButton(w);//注意按钮的声明需要现在头文件进行
    button2->setText("关闭程序");
    button3 = new QPushButton(w);
    button3->setText("返回");

    //button1->setStyleSheet("border:2px groove blue;border-radius:5px;background-color:rgb(250,250,250);");
    button1->setGeometry(10,50,70,80);//分别是图标的位置x和y以及图表的大小以及对应x和y
    button2->setGeometry(90,50,70,80);
    button3->setGeometry(170,50,70,80);
    connect(button1,&QPushButton::clicked,w,&Widget::open_heap);
    connect(button2,&QPushButton::clicked,w,&Widget::close);//暂时为关闭
    connect(button3,&QPushButton::clicked,w,&Widget::close);//绑定为双操作，关闭菜单
    connect(button3,&QPushButton::clicked,w,&Widget::ComeBack);//跳转返回主界面
    button1->show();
    button2->show();
    button3->show();
}

void MyWidget::click_merge()
{
    Widget *w =new Widget;
    w->setWindowTitle("合并排序");
    w->show();
    w->setFont(font2);
    button1=new QPushButton(w);
    button1->setText("开始排序");

    button2 = new QPushButton(w);//注意按钮的声明需要现在头文件进行
    button2->setText("关闭程序");
    button3 = new QPushButton(w);
    button3->setText("返回");
    //button1->setStyleSheet("border:2px groove blue;border-radius:5px;background-color:rgb(250,250,250);");
    button1->setGeometry(10,50,70,80);//分别是图标的位置x和y以及图表的大小以及对应x和y
    button2->setGeometry(90,50,70,80);
    button3->setGeometry(170,50,70,80);
    connect(button1,&QPushButton::clicked,w,&Widget::open_merge);
    connect(button2,&QPushButton::clicked,w,&Widget::close);//暂时为关闭
    connect(button3,&QPushButton::clicked,w,&Widget::close);//绑定为双操作，关闭菜单
    connect(button3,&QPushButton::clicked,w,&Widget::ComeBack);//跳转返回主界面
    button1->show();
    button2->show();
    button3->show();
}
void MyWidget::click_bucket()
{
    Widget *w =new Widget;
    w->setWindowTitle("桶排序");
    w->show();
    w->setFont(font2);
    button1=new QPushButton(w);
    button1->setText("开始排序");

    button2 = new QPushButton(w);//注意按钮的声明需要现在头文件进行
    button2->setText("关闭程序");
    button3 = new QPushButton(w);
    button3->setText("返回");

    //button1->setStyleSheet("border:2px groove blue;border-radius:5px;background-color:rgb(250,250,250);");
    button1->setGeometry(10,50,70,80);//分别是图标的位置x和y以及图表的大小以及对应x和y
    button2->setGeometry(90,50,70,80);
    button3->setGeometry(170,50,70,80);
    connect(button1,&QPushButton::clicked,w,&Widget::open_bucket);
    connect(button2,&QPushButton::clicked,w,&Widget::close);//暂时为关闭
    connect(button3,&QPushButton::clicked,w,&Widget::close);//绑定为双操作，关闭菜单
    connect(button3,&QPushButton::clicked,w,&Widget::ComeBack);//跳转返回主界面
    button1->show();
    button2->show();
    button3->show();
}
void MyWidget::click_quick()
{
    Widget *w =new Widget;
    w->setWindowTitle("快速排序");
    w->show();
    w->setFont(font2);
    button1=new QPushButton(w);
    button1->setText("开始排序");

    button2 = new QPushButton(w);//注意按钮的声明需要现在头文件进行
    button2->setText("关闭程序");
    button3 = new QPushButton(w);
    button3->setText("返回");
    //button1->setStyleSheet("border:2px groove blue;border-radius:5px;background-color:rgb(250,250,250);");
    button1->setGeometry(10,50,70,80);//分别是图标的位置x和y以及图表的大小以及对应x和y
    button2->setGeometry(90,50,70,80);
    button3->setGeometry(170,50,70,80);
    connect(button1,&QPushButton::clicked,w,&Widget::open_quick);
    connect(button2,&QPushButton::clicked,w,&Widget::close);//暂时为关闭
    connect(button3,&QPushButton::clicked,w,&Widget::close);//绑定为双操作，关闭菜单
    connect(button3,&QPushButton::clicked,w,&Widget::ComeBack);//跳转返回主界面
    button1->show();
    button2->show();
    button3->show();
}
void MyWidget::click_shell()
{
    Widget *w =new Widget;
    w->setWindowTitle("希尔排序");
    w->show();
    w->setFont(font2);
    button1=new QPushButton(w);
    button1->setText("开始排序");

    button2 = new QPushButton(w);//注意按钮的声明需要现在头文件进行
    button2->setText("关闭程序");
    button3 = new QPushButton(w);
    button3->setText("返回");

    //button1->setStyleSheet("border:2px groove blue;border-radius:5px;background-color:rgb(250,250,250);");
    button1->setGeometry(10,50,70,80);//分别是图标的位置x和y以及图表的大小以及对应x和y
    button2->setGeometry(90,50,70,80);
    button3->setGeometry(170,50,70,80);
    connect(button1,&QPushButton::clicked,w,&Widget::open_shell);
    connect(button2,&QPushButton::clicked,w,&Widget::close);//暂时为关闭
    connect(button3,&QPushButton::clicked,w,&Widget::close);//绑定为双操作，关闭菜单
    connect(button3,&QPushButton::clicked,w,&Widget::ComeBack);//跳转返回主界面
    button1->show();
    button2->show();
    button3->show();
}
void MyWidget::click_radix()
{
    Widget *w =new Widget;
    w->setWindowTitle("基数排序");
    w->show();
    w->setFont(font2);
    button1=new QPushButton(w);
    button1->setText("开始排序");

    button2 = new QPushButton(w);//注意按钮的声明需要现在头文件进行
    button2->setText("关闭程序");
    button3 = new QPushButton(w);
    button3->setText("返回");

    //button1->setStyleSheet("border:2px groove blue;border-radius:5px;background-color:rgb(250,250,250);");
    button1->setGeometry(10,50,70,80);//分别是图标的位置x和y以及图表的大小以及对应x和y
    button2->setGeometry(90,50,70,80);
    button3->setGeometry(170,50,70,80);
    connect(button1,&QPushButton::clicked,w,&Widget::open_radix);
    connect(button2,&QPushButton::clicked,w,&Widget::close);//暂时为关闭
    connect(button3,&QPushButton::clicked,w,&Widget::close);//绑定为双操作，关闭菜单
    connect(button3,&QPushButton::clicked,w,&Widget::ComeBack);//跳转返回主界面
    button1->show();
    button2->show();
    button3->show();
}
void MyWidget::click_choice()
{
    Widget *w =new Widget;
    w->setWindowTitle("选择排序");
    w->show();
    w->setFont(font2);
    button1=new QPushButton(w);
    button1->setText("开始排序");

    button2 = new QPushButton(w);//注意按钮的声明需要现在头文件进行
    button2->setText("关闭程序");
    button3 = new QPushButton(w);
    button3->setText("返回");

    //button1->setStyleSheet("border:2px groove blue;border-radius:5px;background-color:rgb(250,250,250);");
    button1->setGeometry(10,50,70,80);//分别是图标的位置x和y以及图表的大小以及对应x和y
    button2->setGeometry(90,50,70,80);
    button3->setGeometry(170,50,70,80);
    connect(button1,&QPushButton::clicked,w,&Widget::open_choice);
    connect(button2,&QPushButton::clicked,w,&Widget::close);//暂时为关闭
    connect(button3,&QPushButton::clicked,w,&Widget::close);//绑定为双操作，关闭菜单
    connect(button3,&QPushButton::clicked,w,&Widget::ComeBack);//跳转返回主界面
    button1->show();
    button2->show();
    button3->show();
}

void MyWidget::click_Stack()
{
    StackWidget *s = new StackWidget;
    s->setWindowTitle("栈");
    s->show();
    button1=new QPushButton(s);
    button1->setText("返回");
    button1->setGeometry(1150,50,70,80);//分别是图标的位置x和y以及图表的大小以及对应x和y
    connect(button1,&QPushButton::clicked,s,&StackWidget::close);
    connect(button1,&QPushButton::clicked,s,&StackWidget::ComeBack);//跳转返回主界面
    button1->show();
}


void MyWidget::click_Tree()
{
    MywidgetFour *s = new MywidgetFour;
    s->setWindowTitle("栈");
    s->show();
    button1=new QPushButton(s);
    button1->setText("返回");
    button1->setGeometry(900,50,70,80);//分别是图标的位置x和y以及图表的大小以及对应x和y
    connect(button1,&QPushButton::clicked,s,&MywidgetFour::close);
    connect(button1,&QPushButton::clicked,s,&MywidgetFour::ComeBack);//跳转返回主界面
    button1->show();
}

void MyWidget::click_XZ()
{
    mainWindow *mainwindow = new mainWindow;
    mainwindow->show();
}

void MyWidget::click_CR()
{
    mainWindowT *mainwindowT = new mainWindowT;
    mainwindowT->show();
}

void MyWidget::click_JH()
{
    mainWindowTH *mainwindowTH = new mainWindowTH;
    mainwindowTH->show();
}

