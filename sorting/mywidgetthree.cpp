#include "mywidgetthree.h"
#include "QDebug"
#include "QPushButton"
#include "QGridLayout"
#include "QLineEdit"
#include "QPainter"   //只有调用painter才能使用painter
#include "mywidget.h"
StackWidget::StackWidget(QWidget *parent) : QWidget(parent)
{
    dataStruct = new DataStruct;
    dataStruct->InitialStack();
    qDebug()<<dataStruct->GetLength();
    Button1 = new QPushButton(this);
    Button2 = new QPushButton(this);
    Button3 = new QPushButton(this);
    Button4 = new QPushButton(this);
    Button5 = new QPushButton(this);
    edit1 = new QLineEdit(this);

    flag = -1;

    Button1->setText("查看栈内元素 look()");
    Button2->setText("删除栈顶元素 pop()");
    Button3->setText("插入栈顶元素 push()");
    Button4->setText("栈是否为空 StackEmpty()");
    Button5->setText("销毁栈 DestroyStack()");
    setGeometry(300,300,1300,1100);

    Button1->setGeometry(10,50,150,80);//分别是图标的位置x和y以及图表的大小以及对应x和y
    Button2->setGeometry(180,50,150,80);
    Button3->setGeometry(350,50,150,80);
    Button4->setGeometry(520,50,200,80);
    edit1->setGeometry(1040,50,100,80);
    Button5->setGeometry(740,50,250,80);
    edit1->setPlaceholderText("请输入需要插入的元素值");//提示输入信息
    connect(Button1,&QPushButton::clicked,this,&StackWidget::Look);
    connect(Button2,&QPushButton::clicked,this,&StackWidget::DelteNode);
    connect(Button3,&QPushButton::clicked,this,&StackWidget::AddN0de);
    connect(Button4,&QPushButton::clicked,this,&StackWidget::StackEmpty);
    connect(Button5,&QPushButton::clicked,this,&StackWidget::DestroyStack);
    connect(edit1,&QLineEdit::editingFinished,this,&StackWidget::GetText);//写入方式一：回车写入
    //connect(Button3,&QPushButton::clicked,this,&StackWidget::GetText);//写入方式二：点击写入，不采用是因为无法跟上写入的速度

//    数字转化器
//    QString str1 = "10";
//    int num1 = str1.toInt();
//    qDebug()<<num1;
//    for (int i = 0;i<=99;i++)
//    Data[i] = 0;
}


void StackWidget::Look()//封装dataStruct的Look方法，方便在窗口模式可以进入调用状态；真正的look函数在datastruct中已经封装完毕
{
    dataStruct->Look();
    repaint();
}

int StackWidget::DelteNode()//返回值是一个删除的栈顶元素
{
    int k =dataStruct->DeleteNode();
    repaint();
    return k;
}

void StackWidget::AddN0de()
{
    qDebug()<<"本次插入的栈顶元素为:"<<x;
    dataStruct->AddNode(x);
    repaint();
}

void StackWidget::StackEmpty()//检验栈是否为空
{
    if (dataStruct->StackEmpty() == true)
        flag = 0;
    if(dataStruct->StackEmpty() == false)
        flag = 1;
    repaint();
}

void StackWidget::DestroyStack()
{
    dataStruct->DestroyStack();
    repaint();
}

void StackWidget::GetText()
{
    x = QString(edit1->text()).toInt();//获取输入框的信息，并将信息转为整数
}

//窗体绘制事件
//原理：利用qt提供的QPainter方法进行窗体的绘制
void StackWidget::paintEvent(QPaintEvent *event)
{

    int i = 0;
    dataStruct->t = dataStruct->S;
    QPainter painter(this);
    // 设置画笔颜色
    painter.setPen(QColor(0, 160, 230));
    // 设置字体：微软雅黑、点大小50、斜体
    QFont font;
    font.setPointSize(50);
    font.setItalic(true);
    painter.setFont(font);
    // 绘制文本
    if(flag == 1)
        painter.drawText(QRect(620, 400 , 820, 100), "栈内有元素");//绘制数据
    if(flag == 0)
        painter.drawText(QRect(620, 400 , 820, 100), "栈内无元素");//绘制数据
    painter.drawText(QRect(320, 200 , 320, 100), "栈顶");//绘制数据
    while (dataStruct->t->next) {
    painter.drawText(QRect(120, 200 + i * 110 , 120, 100), QString::number(dataStruct->t->data));//绘制数据
    painter.drawRect(120, 200 + i * 110, 120, 100);//绘制矩形
    i++;//改变矩形绘制位置的关键
    dataStruct->t = dataStruct->t->next;
    }
    painter.end();//绘制结束
}


void StackWidget::ComeBack()
{
    MyWidget *t = new MyWidget;
    t->show();
}
