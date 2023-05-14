#ifndef MYWIDGETTWO_H
#define MYWIDGETTWO_H

#include <QWidget>
#include "QPushButton"
#include "QLabel"
class MywidgetTwo : public QWidget
{
    Q_OBJECT//公有的
public:



public:
    MywidgetTwo(QWidget *parent = nullptr);
    ~MywidgetTwo();//使用信号与操必须有的东西



    //新增部分
    int length;//length为新定义
    int *data;
    int cur1,cur2,cur3;
    int flag;//用何种方法颜色进行标记
    int flagT;//用何种方法颜色进行标记
    int flagC;//代码标识符
    void ComeBack();
    QString total;//用于统计排列的每趟结果
    void Wirte(int *data,int length);//写入MywidgetTwo数据
    void Read();//向表格写入数据
    void printTable();//打印表格
    void deal_Color(int cur1,int cur2,int cur3);
    void paintEvent(QPaintEvent *);
    void dealSimple();

private:

    QFont font2;//字体设置
    QPushButton *button1;//开始排序按钮
    QPushButton *button2;//关闭按钮
    QPushButton *button3;//返回按钮
    QLabel *label1;

public slots:



};

#endif // MYWIDGETTWO_H
