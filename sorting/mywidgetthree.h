#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QWidget>
#include "datastruct.h"
#include "QPushButton"
#include "QLineEdit"
#include "QPainter"
class StackWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StackWidget(QWidget *parent = nullptr);
    void Look();
    int DelteNode();
    void AddN0de();
    void GetText();
    void paintEvent(QPaintEvent *event);
    void ComeBack();
    void StackEmpty();
    void DestroyStack();

    int x;//用于获取栈顶元素值
    QString xx;//未来估计不用了
    int flag;//检测栈是否为空
private:
    DataStruct *dataStruct;//建立数据结构
    QPushButton *Button1;
    QPushButton *Button2;
    QPushButton *Button3;
    QPushButton *Button4;
    QPushButton *Button5;
    QLineEdit *edit1;
    QPushButton *Button[10];



signals:

public slots:
};

#endif // TREEWIDGET_H
