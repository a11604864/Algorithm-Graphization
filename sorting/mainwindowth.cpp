#include "mainwindowth.h"
#include"mywidget.h"
mainWindowTH::mainWindowTH(QWidget *parent) : QWidget(parent)
{

    setGeometry(300,300,1300,1100);//设置窗体大小
    QPushButton *Button[3];
    Button[0] = new QPushButton(this);
    Button[1] = new QPushButton(this);
    Button[2] = new QPushButton(this);

    for(int i=0;i<3;i++)
    {
        Button[i]->setStyleSheet("font-size:50px;color:black");//字体设置
    };

    Button[0]->setGeometry(10,50,200,150);//分别是图标的位置x和y以及图表的大小以及对应x和y
    Button[1]->setGeometry(230,50,200,150);
    Button[2]->setGeometry(450,50,200,150);

    Button[0]->setText("冒泡排序");
    Button[1]->setText("快速排序");
    Button[2]->setText("返回");

    connect(Button[2],&QPushButton::clicked,this,&mainWindowTH::close);//绑定为双操作，关闭菜单
    connect(Button[2],&QPushButton::clicked,this,&mainWindowTH::ComeBack);//跳转返回主界面
    connect(Button[1],SIGNAL(clicked(bool)), this, SLOT(click_quick()));//快速排序
    connect(Button[1],SIGNAL(clicked(bool)), this, SLOT(close()));//关闭的双操作
    connect(Button[0],SIGNAL(clicked(bool)), this, SLOT(click_bubble()));//快速排序
    connect(Button[0],SIGNAL(clicked(bool)), this, SLOT(close()));//关闭的双操作
}

//快速排序
void mainWindowTH::click_quick()
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

//冒泡
void mainWindowTH::click_bubble()
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

void mainWindowTH::ComeBack()
{
    MyWidget *t = new MyWidget;
    t->show();
}
