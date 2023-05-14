#include "mywidgettwo.h"
#include "mywidget.h"
#include "ui_mywidget.h"
#include "QPushButton"
#include "QGridLayout"
#include "widget.h"
#include <QDebug>
#include "QLabel"
#include <string>
#include "QPainter"   //只有调用painter才能使用painter
#include"QTimer"
MywidgetTwo::MywidgetTwo(QWidget *parent)://标准格式
    QWidget(parent)
{
    flag = 1;
    cur1 = cur2 = flagT = -1;
    flagC = 7;
    setGeometry(300,300,1300,1100);
   //设置主窗口图标
    setWindowIcon(QIcon("://image/pig.jpg"));

    setWindowTitle("算法图形化解析软件设计与实现");//设置程序标题



    label1 = new QLabel(this);
    label1->setGeometry(10,10,1000,1000);//文本框大小
    label1->setStyleSheet("QLabel{font:15px;color:red;background-color:rgb(f9,f9,f9);}");//文本格式
    total = QString("本轮排序的结果是:\n");
    //total = QString::number(11);//转化数字的方法

    //label1->clear();//清理文本内容
//    for(int i = 0 ; i < length; i++)
//    {
//        total = total.append(QString::number(data[i]));
//        total = total.append(",");
//    }

    label1->setText(total);
}

MywidgetTwo::~MywidgetTwo()//必须部分
{

}

void MywidgetTwo::Wirte(int *data,int length)//写入数据
{
    this->data = data;
    this->length = length;
}

void MywidgetTwo::Read()//读出数据
{
      for(int i = 0 ; i < length; i++)
      {
          total = total.append(QString::number(data[i]));
          total = total.append(",");
//          qDebug()<<data[i];
      }
      total = total.append("\n");
}

void MywidgetTwo::printTable()//打印排序结果
{
    label1->setText(total);//发挥作用了
    this->show();

}

void MywidgetTwo::deal_Color(int cur1,int cur2,int cur3)
{
    this->cur1 = cur1;
    this->cur2 = cur2;
    flagT = cur3;
    repaint();
}


//重构的绘图事件
void MywidgetTwo::paintEvent(QPaintEvent *)
{

    QPainter painter(this);

    QFont font;//设置字体，下面设置字体属性
    QPen pen(Qt::SolidLine);
    pen.setWidth(5);//设置笔的宽度
    pen.setColor(Qt::green);//设置笔的颜色
    painter.setPen(pen);//确认笔的状态
    font.setPointSize(25);
    font.setItalic(true);
    painter.setFont(font);
    for(int i = 0;i < length;i++)
    {
        if((cur1 == i || cur2 == i) &&flagT == 1)
        {
            pen.setColor(Qt::red);//设置笔的颜色
            painter.setPen(pen);//确认笔的状态
        }
        else if((cur1 == i || cur2 == i) &&flagT == 0)
        {
            pen.setColor(Qt::blue);//设置笔的颜色
            painter.setPen(pen);//确认笔的状态
        }
        painter.drawText(QRect(120 + i * 60, 200 , 50, 50), QString::number(data[i]));//绘制数据
        painter.drawRect(120 + i * 60, 200 , 50, 50);//绘制矩形
        pen.setColor(Qt::green);//设置笔的颜色
        painter.setPen(pen);//确认笔的状态
    }
    if(flagC == 1)//直接插入排序
    {
        pen.setColor(Qt::black);//设置笔的颜色
        painter.setPen(pen);//确认笔的状态
        font.setPointSize(10);
        painter.setFont(font);
        painter.drawText(QRect(420 , 300 , 800, 500), QString("void InsertSort(int array[], int size) {").append("\n\t").append("for (int i = 1; i < size; i++) {        // 第 1 个数肯定是有序的，从第 2 个数开始遍历，依次插入有序序列").append("\n\t").append("int temp = array[i];   // 取出第 i 个数，和前 i-1 个数比较后，插入合适位置").append("\n\t").append("int j    = i - 1;   // 因为前 i-1 个数都是从小到大的有序序列，所以只要当前比较的数 (array[j]) 比 temp 大，就把这个数后移一位").append("\n\t").append("while (j >= 0 && array[j] > temp) { // 当 j < 0 或 array[j] < temp(array[i]) 时终止").append("\n\t\t").append("array[j + 1] = array[j];        // 将大于 temp(array[i]) 的数据后移").append("\n\t\t").append("j--;}    // 向前比较").append("\n").append("array[j + 1] = temp;     // array[i]插入到正确的位置上"));//绘制数据
    }

    if(flagC == 2)//冒泡排序
    {
        pen.setColor(Qt::black);//设置笔的颜色
        painter.setPen(pen);//确认笔的状态
        font.setPointSize(10);
        painter.setFont(font);
        painter.drawText(QRect(420 , 300 , 800, 500),QString("void BubbleSort( int data[], int n )").append("\n\t").append("int i, j, k, t;").append("\n\t").append("for( i = 1; i <= n-1; i++ )").append("\n\t").append("{").append("\n\t\t").append("if( data[j+1] < data[j] )").append("\n\t\t\t").append("t         = data[j+1];").append("\n\t\t\t").append("data[j+1] = data[j];").append("\n\t\t\t").append("data[j]   = t;").append("\n").append("}").append("\n").append("}").append("\n}").append("\n}"));
    }
    if(flagC == 3)//堆排序
    {
        pen.setColor(Qt::black);//设置笔的颜色
        painter.setPen(pen);//确认笔的状态
        font.setPointSize(10);
        painter.setFont(font);
        painter.drawText(QRect(420 , 300 , 800, 500),QString("void maxheap_sort(int a[], int start,int end) {").append("\n	int c = start; // 当前（current）节点的位置").append("\n	int L = 2 * c + 1; // 左（Left）孩子的位置").append("\n	int tmp = a[c]; // 当前（current）节点的大小").append("\n	for (; L <= end; c = L, L = 2 * L + 1) {").append("\n		// “L”是左孩子，“L+1”是右孩子").append("\n		if (L < end && a[L] < a[L + 1]) {").append("\n			L++; // 左右两个孩子中选择较大者，即m_heap[L+1]").append("\n		}").append("\n		if (tmp >= a[L]) {").append("\n			break; // 调整结束").append("\n		}").append("\n		eLse {// 交换值").append("\n			a[c] = a[L];").append("\n			a[L] = tmp;").append("\n		}").append("\n	}").append("}"));
        painter.drawText(QRect(1120 , 300 , 800, 500),QString("void heap_sort_asc(int a[], int n) {").append("\n	int i;").append("\nfor (i = n / 2 - 1; i >= 0; i--) {").append("\n// 从（n/2-1）--> 0 逐次遍历。遍历之后，得到的数组实际上是一个（最大）二叉堆").append("\n	for (i = n / 2 - 1; i >= 0; i--) {").append("\n		maxheap_sort(a, i, n - 1);").append("\n	}").append("\n	// 从最后一个元素开始对序列进行调整，不断地缩小调整的范围直到第一个元素").append("\n	for (i = n - 1; i > 0; i--) {").append("\n		// 交换a[0]和a[i]。交换后，a[i]是a[0..i]中最大的。").append("\n		swap(&a[0], &a[i]);").append("\n		// 调整a[0..i-1]，使得a[0..i-1]仍然是一个最大堆。").append("\n		// 即，保证a[i-1]是a[0..i-1]中的最大值。").append("\n		maxheap_sort(a, 0, i - 1);").append("\n	}").append("\n}"));
    }
    if(flagC == 4)//直接选择排序
    {
        pen.setColor(Qt::black);//设置笔的颜色
        painter.setPen(pen);//确认笔的状态
        font.setPointSize(10);
        painter.setFont(font);
        painter.drawText(QRect(420 , 300 , 800, 500),QString("void SeletedSont(int a[],int n)").append("\n{").append("\n	int i,j,kmin,t;").append("\n	for(i=0;i<n-1;i++)").append("\n	{").append("\n		kmin=i;").append("\n		for(j=i+1;j<n;j++)").append("\n		{").append("\n			if(a[j]<a[kmin])  kmin=j;").append("\n		}").append("\n			if(i-kmin){").append("\n				t=a[i];").append("\n				a[i]=a[kmin];").append("\n				a[kmin]=t;").append("\n							}").append("\n	}").append("\n}"));
    }
    if(flagC == 5)//归并排序
    {
        pen.setColor(Qt::black);//设置笔的颜色
        painter.setPen(pen);//确认笔的状态
        font.setPointSize(10);
        painter.setFont(font);
        painter.drawText(QRect(420 , 300 , 800, 500),QString("void merge(int a[], int start, int mid, int end) {").append("\n	int* tmp = (int*)malloc((end - start + 1) * sizeof(int));").append("\n	// tmp是汇总2个有序区间的临时区域。").append("\n	int i = start; // 第一个有序区的索引").append("\n	int j = mid + 1; // 第二个有序区的索引").append("\n	int k = 0; // 临时区域的索引").append("\n	while (i <= mid && j <= end) {").append("\n		if (a[i] <= a[j]) {").append("\n			tmp[k++] = a[i++];").append("\n		}").append("\n		else {").append("\n			tmp[k++] = a[j++];").append("\n		}").append("\n	}").append("\n	while (i <= mid) {").append("\n		tmp[k++] = a[i++];").append("\n	}").append("\n	while (j <= end) {").append("\n		tmp[k++] = a[j++]; // 将两个有序区间合并").append("\n	}").append("\n	// 排序后的元素，全部都整合到数组a中").append("\n	for (i = 0; i < k; i++) {").append("\n		a[start + i] = tmp[i];").append("\n	}").append("\n	free(tmp);").append("\n	tmp = NULL;").append("\n}").append("\n}"));
        painter.drawText(QRect(1120 , 300 , 800, 500),QString("void merge_sort_up_to_down(int a[], int start, int end) {").append("\n	if (a == NULL || start >= end) {").append("\n		return;").append("\n	int mid = (end + start) / 2;").append("\n	merge_sort_up_to_down(a, start, mid); // 递归排序a[start..mid]").append("\n	merge_sort_up_to_down(a, mid + 1, end); // 递归排序a[mid..end]").append("\n	// a[start..mid]和a[mid..end]是两个有序空间").append("\n	// 将它们排序成一个有序空间a[start..end]").append("\n	merge(a, start, mid, end);").append("\n}"));
    }
    if(flagC == 6)//基数排序
    {
        pen.setColor(Qt::black);//设置笔的颜色
        painter.setPen(pen);//确认笔的状态
        font.setPointSize(10);
        painter.setFont(font);
        painter.drawText(QRect(420 , 300 , 800, 500),QString("int max = data[0];      //寻找最大值，由此得知所需的位数").append("\nfor(int i = 1 ; i < length; i++){").append("\n        if(data[i] > max)").append("\n            max = data[i];").append("\n    }").append("\n    //以个、十、百....的位的数目来遍历").append("\n    for (int exp = 1; max/exp > 0; exp *= 10) {").append("\n        int output[length];").append("\n        int count[10] = {0};").append("\n        for(int i = 0; i < length; i++){//得到每个位数上的数字的个数").append("\n        for(int i = 1; i < 10; i++){").append("\n            count[(data[i]/exp)%10]++;  //例如在{1,2,11,13,4}个位为一的有2个，个位为2的有1，...").append("\n        }").append("\n        //然后将所得到的所有位数进行累加求和，方便判断是在output[]的那个位子上").append("\n        for(int i = 1; i < 10; i++){").append("\n            count[i] += count[i - 1];").append("\n        }").append("\n        for(int i = length -1; i >= 0; i--){").append("\n            output[count[(data[i]/exp)%10] - 1]= data[i];").append("\n            count[(data[i]/exp)%10] --;").append("\n        }").append("\n        for(int i = 0; i < length; i++){").append("\n            data[i] = output[i];    //将此趟排序好的数据赋值回去").append("\n        }"));
    }

    if(flagC == 7)//快速排序
    {
        pen.setColor(Qt::black);//设置笔的颜色
        painter.setPen(pen);//确认笔的状态
        font.setPointSize(10);
        painter.setFont(font);
        painter.drawText(QRect(420 , 300 , 800, 400),QString("int partition(int a[], int low, int high)  //计算基准点，分割为左右两个数组").append("\n{").append("\n    int point = a[low];//基准点等于第一个元素").append("\n      while(low<high)").append("\n      {").append("\n          while(low<high && a[high]>=point)//控制high指针比较并左移").append("\n          {").append("\n                 high--;").append("\n          } ").append("\n         swap(a,low,high);").append("\n}").append("         while(low<high && a[low]<=point)//控制low指针比较并右移").append("\n          {").append("\n                low++;").append("\n          }").append("\n          swap(a,low,high);").append("\n      }").append("\n    return low;//返回基准点位置").append("\n}"));
        painter.drawText(QRect(1120 , 300 , 800, 400),QString("void quicksort(int a[], int low, int high)  //low:起始位置 high:末尾位置").append("\n{").append("\n    if(low<high){").append("\n        int point = partition(a,low,high);//计算基准点").append("\n        quicksort(a,low,point-1);  //对基准点的左边进行排序").append("\n        quicksort(a,point+1,high);//对基准点的右边进行排序").append("\n    }").append("\n}"));
    }
    if(flagC == 8)//希尔排序
    {
        pen.setColor(Qt::black);//设置笔的颜色
        painter.setPen(pen);//确认笔的状态
        font.setPointSize(10);
        painter.setFont(font);
        painter.drawText(QRect(420 , 300 , 800, 400),QString("void ShellSort(int* arr, int size)").append("\n{").append("\n    int gap = size;").append("\n    while (gap > 1)").append("\n    {").append("\n        gap = gap / 3 + 1;	//调整希尔增量").append("\n        int i = 0;").append("\n        for (i = 0; i < size - gap; i++)	//从0遍历到size-gap-1").append("\n        {").append("\n            int end = i;").append("\n            int temp = arr[end + gap];").append("\n            while (end >= 0)").append("\n            {").append("\n                if (arr[end] > temp)").append("\n                {").append("\n                    arr[end + gap] = arr[end];").append("\n                    end -= gap;").append("\n                }").append("\n                else").append("\n                {").append("\n                    break;").append("\n                }").append("\n            }").append("\n            arr[end + gap] = temp;	//以 end+gap 作为插入位置").append("\n        }").append("\n    }").append("\n}"));
        painter.drawText(QRect(420 , 300 , 800, 400),QString(""));
    }
}

void MywidgetTwo::dealSimple()
{
    repaint();
}




