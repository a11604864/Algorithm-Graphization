#ifndef MAINWINDOWTH_H
#define MAINWINDOWTH_H

#include"QPushButton"
#include <QWidget>

class mainWindowTH : public QWidget
{
    Q_OBJECT
public:
    explicit mainWindowTH(QWidget *parent = nullptr);

private:
    QPushButton *button1;//开始排序按钮
    QPushButton *button2;//关闭按钮
    QPushButton *button3;//返回按钮
    QFont font2;//字体设置

    void ComeBack();

signals:

public slots:
    void click_quick();
    void click_bubble();


};

#endif // MAINWINDOWTH_H
