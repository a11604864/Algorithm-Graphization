#ifndef MYWIDGETFOUR_H
#define MYWIDGETFOUR_H

#include <QWidget>
#include "datastruct.h"
#include "QPushButton"
#include "QPainter"
#include "qLineEdit.h"

class MywidgetFour : public QWidget
{
    Q_OBJECT
public:
    explicit MywidgetFour(QWidget *parent = nullptr);
    DataStruct *datastruct;
    QString A;//传输建立树的遍历结果
    int flag = 0;//树是否建立的标志位
    int flagT = 0;//是否进行染色的判断标准
    int Tag = -1;//painter函数的颜色标签
    void paintEvent(QPaintEvent *);
    void BuildPre();
    void InputStr();
    void dealTag();
    void AddTag();
    void BuildTree();
    void BuildIn();
    void BuildPo();
    void ComeBack();

private:
    QPushButton *Button1;
    QPushButton *Button2;
    QPushButton *Button3;
    QLineEdit *edit1;
    QPushButton *Button4;
    QPushButton *Button5;

signals:

public slots:
};

#endif // MYWIDGETFOUR_H
