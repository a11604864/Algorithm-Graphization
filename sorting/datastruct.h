#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include<iostream>
#include "QPoint"
#include "QChar"
#include "QString"
#include "QLine"
#include "QQueue"

using namespace std;

class DataStruct
{
public:
    DataStruct();

    //栈的数据结构
    typedef struct LNode{
        int data;//结点的数据元素
        LNode *next;//下个结点的位置信息
    }*node;
    LNode *S;//定义到类里面所共享
    LNode *t;
    void InitialStack();
    void AddNode(int data);
    void Look();
    int DeleteNode();
    int GetLength();
    void LevelOrder();
    bool StackEmpty();
    bool DestroyStack();

    //树的数据结构
    typedef struct Tree
    {
        QChar data;//数据元素
        Tree *left,*right;//左孩子、右孩子
        QPoint point;//结点的坐标
        int tag = -1;//标志位

        //树的初始化
        Tree(QChar data,QPoint point=QPoint(0,0),Tree *left=NULL,Tree *right=NULL)
        {
            this->data=data;
            this->left=left;
            this->right=right;
            this->point=point;
        }
        Tree(){;}

        //修改坐标的值
       void setpoint(QPoint p)
       {
             point=p;
       }


    }*tree;
    Tree *R;//借助结点
    Tree *root;
    QQueue<Tree *>Q2;

    void CreateBinTree(QString &str, Tree *&Node,int &i);
    void preOrder(Tree *&Node,int &tag);
    void inOrder(Tree *&Node,int &tag);
    void postOrder(Tree *Node,int &tag);
    void setMyPoints();
    void SetLRtree();
    int height(Tree *Node);
    QString getPreStr();//获取先序字符串
    QString getInStr();//获取中序字符串
    QString getPostStr();//获取后序字符串
    QString getLevelStr();
    QPoint *getPoints();
    QLine *getLines();
    int size();

    QString prestr;
    QString instr;
    QString poststr;
    QString levelstr;
    int treeNum; //统计树中结点数
    QPoint *Mypoints;       //树各个结点坐标的集合
    QLine *My_lines;        //线的条数
    QChar *CRoot;
    QChar *LTree;//存储左子树
    QChar *RTree;//存储右子树


    int *Tag;
    void dealTag();
};

#endif // DATASTRUCT_H
