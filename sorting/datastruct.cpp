#include "datastruct.h"
#include "QDebug"
#include<iostream>
#include<QPoint>
#include<QLine>
#include"QQueue"
DataStruct::DataStruct()
{
    S = new LNode;//作为全局变量
    t = new LNode;
    root = new Tree('a');//此处root是全局变量
    R = new Tree;
    treeNum = 0;

    typedef struct TNode{
        Tree *data;
        TNode *next;
    };

    typedef struct Queue{
        TNode *front,*rear;
    };


    //Tag = new int[100];//树的染色标签

}

void DataStruct::InitialStack()//栈的初始化
{
    S->data = 5;
    S->next = NULL;//头结点
}

//入栈操作
void DataStruct::AddNode(int data)
{
    LNode *r = new LNode;//创建新结点
    r->data = data;//将新结点存储新入栈的数据元素
    r->next = S;//建立新结点与栈的连接
    S = r;//将栈顶指针指向该新结点
}

//查看栈内存在元素
void DataStruct::Look()
{
    LNode *r = S;//复制根节点信息
    qDebug()<<"栈内元素为:";
    if (r->next == NULL)//如果栈内无元素
        qDebug()<<"栈内元素为空";

    while (r->next)
    {
        qDebug()<<r->data;//打印当前结点值
        r = r->next;//将指针移动到下一个结点
    }
    qDebug()<<"\n\n";

}

//查看栈是否为空
bool DataStruct::StackEmpty()
{
    if (S->next)//如果栈顶指针指向对象存在则栈不为空
        return false;//不为空则返回false值
    else return true;
}

//销毁栈
bool DataStruct::DestroyStack()
{
    S->next = nullptr;//将栈顶的指针置空
}


//获取栈的高度信息
int DataStruct::GetLength()
{
    int length = 0;//初始化长度信息
    LNode *r = S;
    if (r->next == NULL)//栈为空则长度为0
    {
        qDebug()<<"栈内元素为空";
        return 0;
    }
    while (r->next) {//栈顶指针指向元素存在则长度加1
        length++;
        r = r->next;
    }
    return length;//返回栈的长度信息

}

//移除栈顶元素
int DataStruct::DeleteNode()
{
    if(S->next != NULL)//如果栈顶元素存在则进行移除操作
    {
        int x = S->data;//取出栈顶元素值
        S = S->next;//将栈顶指针指向下一个元素
        return x;//返回栈顶元素值
    }
    else return -1;
}


//先序序列建立树
//原理：利用键盘输入的参数str构建先序序列，从而根据先序递归完成树的建立；
void DataStruct::CreateBinTree(QString &str, Tree *&Node,int &i)
{

    if(str[i]!='#')//说明不是空节点
    {
        Node=new Tree(str[i]);
        treeNum++;//统计结点数量
        i++;
        this->CreateBinTree(str,Node->left,i);//递归左子树
        this->CreateBinTree(str,Node->right,i);//递归右子树
    }
    else
    {
        i++;
        Node=nullptr;
    }

}


//层次遍历
void DataStruct::LevelOrder()
{
    QQueue<Tree *>Q;         //调用队列
    Tree *p=root;
    Q.enqueue(root);
    while(!Q.isEmpty())
    {
        p=Q.dequeue();
        levelstr.append(p->data);
        if(p->left!=nullptr)
            Q.enqueue(p->left);
        if(p->right!=nullptr)
            Q.enqueue(p->right);
    }
}


//前序遍历
//原理：利用递归的方法进行先序遍历
void DataStruct::preOrder(Tree *&Node,int &tag)
{

    if(Node!=nullptr)//结点不能为空
    {
        Node->tag = tag;//统计结点的遍历顺序
        tag++;
        prestr.append(Node->data);//将该结点的值添加存储起来
        preOrder(Node->left,tag);//遍历左子树
        preOrder(Node->right,tag);//遍历右子树
    }
}
//中序遍历
//原理：利用递归的方法进行中序遍历
void DataStruct::inOrder(Tree *&Node,int &tag)
{
    if(Node!=nullptr)//结点不能为空
    {
        inOrder(Node->left,tag);//遍历左子树
        Node->tag = tag;//统计结点的遍历顺序
        tag++;
        instr.append(Node->data);//将该结点的值存储起来
        inOrder(Node->right,tag);//遍历右子树
    }

}

//后序遍历
//原理：利用递归的方法进行后序遍历
void DataStruct::postOrder(Tree *Node,int &tag)
{
    if(Node!=nullptr)//结点不能为空
    {
        postOrder(Node->left,tag);//遍历左子树
        postOrder(Node->right,tag);//遍历右子树
        Node->tag = tag;//统计结点的遍历顺序
        tag++;
        poststr.append(Node->data);//将该结点的值存储起来
    }
}



//为结点设置相应的坐标,以及相邻结点的线段设立坐标
//原理：利用队列为每个结点进行层次遍历，从而为每个结点设立对应坐标
void DataStruct::setMyPoints()
{
    int i=0;
    Mypoints=new QPoint[treeNum];//为结点的坐标存储动态分配空间
    My_lines=new QLine[treeNum-1];//为直线的坐标存储动态分配空间
    QQueue<Tree *>Q;//调用队列
    Tree *p=root;
    root->setpoint(QPoint(500,300));//为根节点设置坐标
    Q.enqueue(root);//结点入队
    Mypoints[i]=root->point;

    //通过层次遍历，完成各个坐标的匹配
    while(!Q.isEmpty())
    {
        p=Q.dequeue();//结点出队
        if(p->left!=nullptr)//左孩子设立坐标属性值和对应线段属性值
        {
            i++;
            int h=height(p);
            p->left->setpoint(p->point-QPoint(45*h,-100));//设立结点坐标
            Mypoints[i]=p->left->point;//存储坐标
            My_lines[i-1].setP1(p->point+QPoint(0,25));//设立线段坐标
            My_lines[i-1].setP2(p->left->point-QPoint(0,25));//存储坐标
            Q.enqueue(p->left);//左孩子入队
        }

        if(p->right!=nullptr)//右孩子设立坐标属性值和对应线段属性值
        {
            i++;
            int h=height(p);
            p->right->setpoint(p->point+QPoint(45*h,100));//设立结点所在坐标
            Mypoints[i]=p->right->point;//保存右孩子坐标
            My_lines[i-1].setP1(p->point+QPoint(0,25));//设立线段坐标
            My_lines[i-1].setP2(p->right->point-QPoint(0,25));//存储坐标
            Q.enqueue(p->right);//右孩子入队
            h--;
        }

    }
}

//存储每个结点通过先序遍历（中序遍历、后序遍历）的遍历顺序
//原理：利用层次遍历的方法遍历每个结点，从而访问他们的tag标签，存储它们的遍历顺序
void DataStruct::dealTag()
{
    Tag = new int[treeNum];//为存储tag标签分配空间
    int i=0;
    R=root;
    Q2.enqueue(root);//根结点入队
    Tag[i] = root->tag;
    //通过层次遍历，完成各个坐标的匹配
    while(!Q2.isEmpty())
    {
        R=Q2.dequeue();//结点出队
        if(R->left!=nullptr)//存储左孩子结点的tag
        {
            i++;
            Tag[i] = R->left->tag;
            Q2.enqueue(R->left);//左孩子入队
        }

        if(R->right!=nullptr)//存储右孩子结点的tag
        {
            i++;
            Tag[i] = R->right->tag;
            Q2.enqueue(R->right);//右孩子入队
        }

    }
}
//为每个结点寻找左右子树
//原理：利用层次遍历遍历每个结点，从而访问他们的左右孩子，并将左右孩子存储下来，通过如此的方法便为每个结点寻找到了左右孩子
void DataStruct::SetLRtree()
{
    QQueue<Tree *>Q;         //调用队列
    int i=0;
    CRoot = new QChar[treeNum];//树的根结点存储
    LTree = new QChar[treeNum];//树的左子树存储
    RTree = new QChar[treeNum];//树的右子树存储
    R=root;
    Q.enqueue(root);//根结点入队
    if(root)
    CRoot[i] = root->data;
    if(root->right)
    RTree[i] = root->right->data;
    if(root->left)
    LTree[i] = root->left->data;

    while(!Q.isEmpty())
    {
        R=Q.dequeue();//结点出队
        if(R->left!=nullptr)//为左孩子结点存储对应属性值
        {
            i++;
            CRoot[i] = R->left->data;//左子树存储
            if(R->left->right)
            RTree[i] = R->left->right->data;
            if(R->left->left)
            LTree[i] = R->left->left->data;
            Q.enqueue(R->left);//左孩子入队
        }

        if(R->right!=nullptr)//为右孩子结点存储对应属性值
        {
            i++;
            CRoot[i] = R->right->data;//右子树存储
            if(R->right->right)
            RTree[i] = R->right->right->data;
            if(R->right->left)
            LTree[i] = R->right->left->data;
            Q.enqueue(R->right);//右孩子入队
        }

    }
}



int DataStruct::height(Tree *Node)
{
      if(Node==nullptr)
          return 0;
      else
      {
          int i=height(Node->left);
          int j=height(Node->right);
          return (i<j)? j+1:i+1;
      }
}

//获得前序、中序、后、层次遍历的字符串
QString DataStruct::getPreStr()
{
   return prestr;
}

QString DataStruct::getInStr()
{
   return instr;
}

QString DataStruct::getPostStr()
{
   return poststr;
}

QString DataStruct::getLevelStr()
{
   return levelstr;
}


QPoint *DataStruct::getPoints()
{
    return Mypoints;
}

QLine *DataStruct::getLines()
{
    return My_lines;
}



//返回节点个数
int DataStruct::size()
{
    return treeNum;
}
