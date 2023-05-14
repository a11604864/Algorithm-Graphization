#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "QPushButton"
#include <QWidget>

class mainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit mainWindow(QWidget *parent = nullptr);

private:
    QPushButton *button1;//开始排序按钮
    QPushButton *button2;//关闭按钮
    QPushButton *button3;//返回按钮
    QFont font2;//字体设置


    void ComeBack();


signals:

public slots:
    void click_merge();
    void click_heap();
    void click_radix();
    void click_choice();
};

#endif // MAINWINDOW_H
