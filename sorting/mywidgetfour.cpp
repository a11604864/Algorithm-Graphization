#include "mywidgetfour.h"
#include "QDebug"
#include "datastruct.h"
#include "QPainter"
#include "qedit.h"
#include "QQueue"
#include "mywidget.h"
MywidgetFour::MywidgetFour(QWidget *parent) : QWidget(parent)
{
    datastruct = new DataStruct;//定义结构体

//    A = "ABC###D##";


    setGeometry(300,300,1300,1100);//设置窗体大小

    Button1 = new QPushButton(this);
    Button2 = new QPushButton(this);
    Button3 = new QPushButton(this);
    Button4 = new QPushButton(this);
    Button5 = new QPushButton(this);
    edit1 = new QLineEdit(this);

    Button1->setText("先序遍历建立");
    Button2->setText("继续");
    Button3->setText("后序遍历");
    Button4->setText("中序遍历");
    Button5->setText("先序遍历");
    edit1->setPlaceholderText("请输入需要插入的元素值");//提示输入信息

    Button3->setGeometry(10,50,100,80);//分别是图标的位置x和y以及图表的大小以及对应x和y
    Button2->setGeometry(120,50,100,80);
    Button5->setGeometry(230,50,100,80);
    edit1->setGeometry(560,50,200,80);
    Button4->setGeometry(340,50,100,80);
    Button1->setGeometry(450,50,100,80);

    connect(Button1,&QPushButton::clicked,this,MywidgetFour::BuildTree);
    connect(edit1,&QLineEdit::editingFinished,this,&MywidgetFour::InputStr);//写入方式一：回车写入
    connect(Button2,&QPushButton::clicked,this,&MywidgetFour::AddTag);
    connect(Button5,&QPushButton::clicked,this,&MywidgetFour::BuildPre);
    connect(Button4,&QPushButton::clicked,this,&MywidgetFour::BuildIn);
    connect(Button3,&QPushButton::clicked,this,&MywidgetFour::BuildPo);

}

//窗体的绘图事件
//原理：利用qt提供的QPainter方法进行窗体的绘制
void MywidgetFour::paintEvent(QPaintEvent *)
{

    QPainter painter(this);

    QFont font;//设置字体，下面设置字体属性
    QPen pen(Qt::SolidLine);
    pen.setWidth(5);//设置笔的宽度
    pen.setColor(Qt::green);//设置笔的颜色
    painter.setPen(pen);//确认笔的状态

    //只有当树部位空的时候才画图
    if(datastruct->root!=nullptr && flag == 1)
    {

        for(int i=0;i<datastruct->size();i++)
        {
            pen.setColor(Qt::green);
            painter.setPen(pen);
            QPoint p=datastruct->getPoints()[i];//得到各个节点的坐标
            painter.drawEllipse(p,25,25);//圆的半径为25
            painter.drawText(p,QString(datastruct->getLevelStr()[i]));
            if(i!=0)
               painter.drawLine(datastruct->getLines()[i-1]);//得到线段的坐标

            if(flagT == 1)
            {
                pen.setColor(Qt::blue);//遍历过程染色区
                painter.setPen(pen);
                QPoint t;
                int j = 0;
                for(;Tag != datastruct->Tag[j];j++);
                t=datastruct->getPoints()[j];//颜色标注区
                painter.drawEllipse(t,50,50);
            }


        }
        pen.setColor(Qt::black);
        pen.setWidth(5);//设置笔的宽度
        font.setPointSize(10);
        painter.setFont(font);//设置字体
        painter.setPen(pen);
        for(int i = 0;i<datastruct->size();i++)//打印每个结点的左右子树
        {
            painter.drawText(QRect(920,300 + 50 * i,320,100),QString("以").append(datastruct->CRoot[i]).append("为根结点").append("的左子树为").append(datastruct->LTree[i]).append("之后的结点,").append("右子树为").append(datastruct->RTree[i]).append("之后的结点"));
        }

    }

        //将前序、中序、后序、层次遍历依次输出
       pen.setColor(Qt::darkCyan);
       pen.setWidth(5);//设置笔的宽度
       font.setPointSize(15);
       painter.setFont(font);//设置字体
       painter.setPen(pen);
       painter.drawText(QRect(120,200,320,100),QString("前序：").append(datastruct->getPreStr()));
       painter.drawText(QRect(420,200,320,100),QString("中序：").append(datastruct->getInStr()));
       painter.drawText(QRect(720,200,320,100),QString("后序：").append(datastruct->getPostStr()));
    painter.end();//结束绘制
}

//建立树
void MywidgetFour::BuildTree()
{
    int i = 0;
    datastruct->CreateBinTree(A,datastruct->root,i);//先序建立树
    datastruct->LevelOrder();//进行层次遍历，同时确认元素位置
    datastruct->SetLRtree();
    datastruct->setMyPoints();//利用层次遍历确认树的每个结点的坐标
    flag = 1;//激活绘画功能
    repaint();
}

void MywidgetFour::BuildPre()//前序的过程遍历
{
    int tag = 0;//建立染色顺序
    flagT = 1;//染色开始
    Tag = 0;//实现继续功能的关键
    datastruct->preOrder(datastruct->root,tag);
    datastruct->dealTag();


//    for(int i=0;i<datastruct->size();i++)
//    {
//        qDebug()<<datastruct->Tag[i];
//    }

    flag = 1;
    repaint();
}

void MywidgetFour::InputStr()
{
    A = edit1->text();//获取输入框的信息
}



void MywidgetFour::AddTag()//继续遍历过程的操作
{
    if (Tag < datastruct->size() - 1)
    {
    Tag++;//遍历的关键
    repaint();//重新绘制
    }
    else
    {
        Tag = 0;//重新开始遍历
        repaint();
    }
}

void MywidgetFour::BuildIn()//中序的过程遍历
{
    int tag = 0;//建立染色顺序
    flagT = 1;//染色开始
    Tag = 0;//实现继续功能的关键
    datastruct->inOrder(datastruct->root,tag);
    datastruct->dealTag();

//    for(int i=0;i<datastruct->size();i++)
//    {
//        qDebug()<<datastruct->Tag[i];
//    }
    flag = 1;
    repaint();
}

void MywidgetFour::BuildPo()//后序的过程遍历
{
    int tag = 0;//建立染色顺序
    flagT = 1;//染色开始
    Tag = 0;//实现继续功能的关键
    datastruct->postOrder(datastruct->root,tag);
    datastruct->dealTag();
    flag = 1;
    repaint();
}

void MywidgetFour::ComeBack() //返回主界面
{
    MyWidget *t = new MyWidget;
    t->show();
}

