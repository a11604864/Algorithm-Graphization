#include "bubble.h"
#include<QDebug>
#include<QTime>
#include<iostream>
#include"QTimer"
#include"QEventLoop"
#include"QCoreApplication"
#include <QElapsedTimer>
Bubble::Bubble(int l, int m, int mD, int *data, QObject *parent) : QObject(parent)
{
    qsrand(static_cast<uint>(QTime::currentTime().msec())); //初始化随机种子
    length = l;
    max = m;
    mDelay = mD;
    this->data = data;
    rand();
}


//产生整体序列构成自然数的无规则序列
//原理：利用随机数，逐一生成范围元素并且通过筛查的方式反正重复
void Bubble::rand()
{


    if(data == nullptr)
        throw "数据不合理";
    bool flag[length];//设定标记位防止重复存储
    for(int i = 0; i < length; i++)
        flag[i] = false;
    for(int i = 0; i < length ; i++){
        while(1){
            int r = qrand()%max + 1;//数据随机产生的出处
            if(flag[r-1] == false){
                data[i] = r;
                flag[r-1]= true;
                break;
            }
        }
    }

}



//冒泡排序开始
void Bubble::goBubble()
{
    QTime qtime;//新增部分
    qtime.start();//计时开始
    QElapsedTimer t;
    bubbleSignal3();
    bubbleSignal2();//激活打印表格的槽函数
    t.start();
    while(t.elapsed()<1000);//时间延迟
    bool flag = false;  //供判断是否已经完成
    for(int i = 1; i < length && !flag; i ++){
        flag = true;
        for(int j = 0; j < length-i; j++){
            if(data[j] > data[j+1]){
                int t = data[j];
                data[j] = data[j+1];
                data[j+1] = t;
                flag = false;
            }
            t.start();
            while(t.elapsed()<1000);//时间延迟
            bubbleSignal(j);//提示重新绘制图形的提示器
            bubbleSignal4(j,j+1,1);
            QThread::msleep(static_cast<unsigned int>(mDelay));
        }
        bubbleSignal3();//激活写入函数
    }

    //保证图形最后能顺利完整的遍历完成
    for(int i = 0; i < length; i++){
        bubbleSignal(i);//发送当前需要调整颜色的位置
        QThread::msleep(static_cast<unsigned int>(mDelay));
    }
    qDebug()<<"程序的运行时间为："<<qtime.elapsed()/1000.0<<"s";//打印花费时间

}



//直接插入排序开始
//原理：每趟排序都能确定一个由若干元素组成的有序序列
void Bubble::goInsertion()
{
    QElapsedTimer t;//实现代码暂停的关键部分
    QTime qtime;//新增部分
    qtime.start();//计时开始
    bubbleSignal3();//激活更新数据的槽函数
    bubbleSignal2();//激活打印表格的槽函数
    t.start();
    while(t.elapsed()<1000);//时间延迟

    //直接插入排序
    for (int i = 1; i < length;i++) {
        int j ;
        if(data[i] < data[i - 1]){
            int temp = data[i];
            for (j = i - 1;j>= 0&&temp < data[j];j--) {
                data[j+1] = data[j];//将元素右移
                bubbleSignal(j);//激活柱状图的颜色标签的槽函数
                t.start();
                while(t.elapsed()<1000);//时间延迟
                QThread::msleep(static_cast<unsigned int>(mDelay));
            }          
            data[j + 1] = temp;//确定该元素在有序的序列的位置
            bubbleSignal4(j + 1,i,1);
            t.start();
            while(t.elapsed()<500);//时间延迟
            bubbleSignal4(-1,i,0);
            t.start();
            while(t.elapsed()<1000);//时间延迟
            bubbleSignal(j);//激活柱状图的颜色标签的槽函数
            bubbleSignal3();//激活写入函数
            QThread::msleep(static_cast<unsigned int>(mDelay));
        }
    }

    for(int i = 0; i < length; i++){
        bubbleSignal(i);
        QThread::msleep(static_cast<unsigned int>(mDelay));
    }
    qDebug()<<"程序的运行时间为："<<qtime.elapsed()/1000.0<<"s";//打印花费时间
    bubbleSignal2();//激活打印表格的槽函数
}
//直接插入排序结束





//堆排序开始
//堆排序采用的顺序存储的建堆方式
//原理：将待排序的记录构造成一个大顶堆（或小顶堆），
//然后依次将堆顶元素取出，放到有序序列的末尾，再重新调整堆，使其满足堆的性质。
void Bubble::goHeap()
{
    qDebug()<<"初始序列分别为：";
    for(int i = 0;i < length;i++)
    qDebug()<<"第"<<i + 1<<"个数据是"<<data[i];
    bubbleSignal3();//写入函数
    QElapsedTimer t;
    bubbleSignal2();//激活打印表格的槽函数
    t.start();
    while(t.elapsed()<1000);//时间延迟
    QTime qtime;//新增部分
    qtime.start();//计时开始
    // 初始化堆
    // length / 2 - 1是二叉树中最后一个非叶子结点的序号
    for (int i = length / 2 -1; i >= 0; i--)//向前调整
    {
        heapAdjust(i,length);
        cur = i;//标志位
        bubbleSignal(i);
        QThread::msleep(static_cast<unsigned int>(mDelay));
    }
    // 交换堆顶元素和最后一个元素
    for (int i = length-1; i >= 0; i--)
    {
        int temp;//暂存元素
        bubbleSignal3();//激活写入函数
        bubbleSignal4(-1,0,1);//用蓝色标注大根堆堆顶元素
        t.start();
        while(t.elapsed()<1000);//时间延迟
        temp = data[i];
        data[i] = data[0];
        data[0] = temp;
        bubbleSignal3();//激活写入函数
        bubbleSignal4(i,-1,0);
        t.start();
        while(t.elapsed()<1000);//时间延迟
        heapAdjust(0,i);//再次调整为大根堆
        bubbleSignal(i);
        QThread::msleep(static_cast<unsigned int>(mDelay));
    }
    for(int i = 0; i < length;i++){
        bubbleSignal(i);
        QThread::msleep(static_cast<unsigned int>(mDelay));
    }
    qDebug()<<"程序的运行时间为："<<qtime.elapsed()/1000.0<<"s";//打印花费时间
    bubbleSignal2();//激活打印表格的槽函数
}


//重新构建大顶堆
void Bubble::heapAdjust(int i, int len)
{
    int temp = data[i];
    for(int j = 2*i+1;j <len; j=j*2+1){
        if(j < len-1 && data[j] < data[j + 1]){
            ++j;
        }
        if(temp >= data[j])
            break;
        data[i] = data[j];
        i = j;
        bubbleSignal(i);
        QThread::msleep(static_cast<unsigned int>(mDelay));
    }
    data[i] = temp;
}
//堆排序结束





//希尔排序
//原理：希尔排序的基本思想是将待排序的记录按照一定的间隔进行分组，
//对每个分组使用插入排序算法进行排序，然后逐步缩小间隔，再对分组进行排序，直到间隔为1
void Bubble::goShell()
{
    QElapsedTimer t;//实现代码暂停的关键部分
    bubbleSignal3();//激活更新数据的槽函数
    bubbleSignal2();//激活打印表格的槽函数
    t.start();
    while(t.elapsed()<1000);//时间延迟
    int increasement = length;
    int i, j, k;
    QTime qtime;//新增部分
    qtime.start();//计时开始
    do
    {
        // 确定分组的增量
        increasement = increasement / 3 + 1;
        for (i = 0; i < increasement; i++)
        {
            for (j = i + increasement; j < length; j += increasement)//在同一增量的不同序列下完成一趟排序
            {
                bubbleSignal4(j + increasement,j,1);//激活数字序列的颜色标签槽函数
                if (data[j] < data[j - increasement])
                {
                    int temp = data[j];
                    for (k = j - increasement; k >= 0 && temp < data[k]; k -= increasement)//在同一增量完成有序化排序
                    {
                        data[k + increasement] = data[k];
                        bubbleSignal(k);
                        QThread::msleep(static_cast<unsigned int>(mDelay));
                    }
                    data[k + increasement] = temp;

                }                
                t.start();
                while(t.elapsed()<1000);//时间延迟
            }
        }
        bubbleSignal3();//激活更新数据的槽函数
    } while (increasement > 1);

    for(int i = 0; i < length;i++){
        bubbleSignal(i);
        QThread::msleep(static_cast<unsigned int>(mDelay));
    }
    qDebug()<<"程序的运行时间为："<<qtime.elapsed()/1000.0<<"s";//打印花费时间
    bubbleSignal2();//激活打印表格的槽函数
}



//简单选择排序
//原理：每次将该序列的最小元素放到序列的前面，重复上述操作直到序列有序
void Bubble::goChoice()
{
    QElapsedTimer t;//实现代码暂停的关键部分
    bubbleSignal3();
    bubbleSignal2();//激活打印表格的槽函数
    QTime qtime;//新增部分
    qtime.start();//计时开始
    for (int i = 0;i < length; i++) {   //先进行整体循环遍历
        int index = i;                  //当前比较的位子
        for (int j = i+1;j < length; j++) {
            if(data[index] > data[j]){  //在余下的数找到其最小的数
                index = j;
                bubbleSignal(j);
                QThread::msleep(static_cast<unsigned int>(mDelay));
            }
        }
        if(index == i)  //没有找到，即表示当前数是余下数的最小数
            continue;
        else {          //找到，即将当前位子的数与找到的数进行交换
            int temp = data[index];//交换元素的位置
            data[index] = data[i];
            data[i] = temp;
            bubbleSignal4(index,i,1);//标注选中元素以及插入位置
            t.start();
            while(t.elapsed()<1000);//时间延迟

        }
        bubbleSignal(i);//激活柱状图颜色标签的槽函数
        bubbleSignal3();//激活写入函数
        QThread::msleep(static_cast<unsigned int>(mDelay));
    }

    for(int i = 0; i < length;i++){
        bubbleSignal(i);
        QThread::msleep(static_cast<unsigned int>(mDelay));
    }
    qDebug()<<"程序的运行时间为："<<qtime.elapsed()/1000.0<<"s";//打印花费时间
    bubbleSignal2();//激活打印表格的槽函数
}





/*举个栗子 有数据 12，9，11，13，5，7
 * 先进行递归将数组分为长度尽可能相等的两部分
 *      第一次递归    第二次递归  第三次递归
 *      12，9，11 -->  12,9           经过mergeSort递归到底
 *                          --> 9,12  在merge中进行排序
 *                     11            返回上一层递归中，向右递归到底
 *                          --> 9,11,12     在merge中进行排序
 *      13，5，7 --->  13,5 --> 5,13 --> 5,7,13   同理上
 *      -->5,7,9,11,12,13           得到最终排序
 *  最终会在动画看到先是排好一个小山峰（9，11，12）然后紧接着又排好一个小山峰（5,7,13）
 *  然后俩个小山峰进行在merge中进行归并就得出了大山峰（5,7,9,11,12,13）
 */


//归并排序
//原理：归并排序的基本思想是将待排序的记录分成若干个子序列，
//每个子序列都是有序的，然后将这些子序列合并成一个大的有序序列，最终完成整个序列的排序。
void Bubble::goMerge()
{
    QTime qtime;//新增部分
    QElapsedTimer t;//代码暂停的关键部分
    bubbleSignal3();//激活更新数据的槽函数
    bubbleSignal2();//激活打印表格的槽函数
    t.start();
    while(t.elapsed()<1000);//时间延迟
    bubbleSignal4(-1,-1,-1);//取消闪烁
    qtime.start();//计时开始
    mergeSort(0,length-1);

    for(int i = 0; i < length;i++){
        bubbleSignal(i);
        QThread::msleep(static_cast<unsigned int>(mDelay));
    }
    bubbleSignal2();//激活打印表格的槽函数
    qDebug()<<"程序的运行时间为："<<qtime.elapsed()/1000.0<<"s";//打印花费时间
}
//将数组分为尽可能相等的俩个部分
void Bubble::mergeSort(int l, int r)
{
    if(l < r){
        int m = l + (r-l)/2;
        mergeSort(l,m);//通过递归手段逐一划分子序列
        mergeSort(m+1,r);
        merge(l,m,r);//将两个子序列有序化
    }
}
//对于俩个子序列进行整个有序化处理
void Bubble::merge(int l, int m, int r)
{
    QElapsedTimer t;
    int n1 = m-l+1;
    int n2 = r - m;
    int L[n1],R[n2];
    for(int i = 0; i < n1; i++){
        L[i] = data[l+i];       //存数组l到m之间的数据
    }
    for(int i = 0; i < n2; i++){
        R[i] = data[m + 1 + i]; //存数组m+1到r之间的数据
    }
    int k = l,i = 0, j = 0;
    while(i < n1 && j < n2){    //将两个部分在一个新的数组中合并并且排序
        if(L[i] <= R[j]){
            data[k] = L[i];
            i++;
        }
        else{
            data[k] = R[j];
            j++;
        }
        k++;
        bubbleSignal(k);//激活柱状图的颜色标签槽函数
        QThread::msleep(static_cast<unsigned int>(mDelay));
    }
    while(i < n1){              //将L中剩余的值放入data中
        data[k] = L[i];
        i ++;
        k ++;
        bubbleSignal(k);

        QThread::msleep(static_cast<unsigned int>(mDelay));
    }
    while(j < n2){
        data[k] = R[j];         //将R中剩余的值放入data中
        j ++;
        k ++;
        bubbleSignal(k);//激活柱状图的颜色标签槽函数

        QThread::msleep(static_cast<unsigned int>(mDelay));
    }
    bubbleSignal4(0,length - 1,1);
    t.start();
    while(t.elapsed()<3000);//时间延迟
    bubbleSignal4(-1,-1,-1);//激活柱状图的颜色标签槽函数
    bubbleSignal3();//激活写入函数,没有打印全是归并排序的弊端
}
//归并排序结束





//桶排序（考虑删除）
void Bubble::goBucket()
{
    int max = data[0];
    for(int i = 1 ;i < length; i ++){
        if(data[i] > max)
            max = data[i];
    }
    max ++;                         //加一是为了防止数组越界
    QVector<int> b[10];             //假设放十个桶，这个可以自定义
    for (int i = 0; i < length; i++) {
        int bi = 10*data[i]/max;
        b[bi].push_back(data[i]);   //然后将数据以10为间隔放置数据
    }

    int c = 0,len =0;   //c用来表示新放入数组的位子，len表示经历各个桶的累长度
    for(int i = 0; i < 10; i ++){   //将data的数据进行重新放入，方便动图观看
        for(int j = 0; j < b[i].size(); j++){
            data[c++] = b[i].at(j);
        }
    }
    c = 0;
    for(int i = 0; i < 10; i ++){
        //这里本想使用sort库来实现各个桶内的排序方便偷个懒的
        //可是那样就不好动图表现了，就用了直接插入排序来代替了，好像也不是很好看
        //std::sort(b[i].begin(),b[i].end());
        for(int j = 1+len; j < b[i].size()+len; j++){
            //直接插入排序
            int k;
            if(data[j] < data[j - 1]){
                int temp = data[j];
                for (k = j - 1;k>= len&&temp < data[k];k--) {
                    data[k+1] = data[k];
                    bubbleSignal(k);
                    QThread::msleep(static_cast<unsigned int>(mDelay));
                }
                data[k+1] = temp;
//                bubbleSignal(k + len);
//                QThread::msleep(static_cast<unsigned int>(mDelay));
            }
        }
        len += b[i].size();
    }
    for(int i = 0; i < length;i++){
        bubbleSignal(i);
        QThread::msleep(static_cast<unsigned int>(mDelay));
    }
}




//快速排序
//原理：基本思想是选取一个基准元素，将待排序的记录分成两部分，一部分记录的关键字比基准元素小，
//另一部分记录的关键字比基准元素大，然后对这两部分记录分别进行排序，最终将整个序列排序。
void Bubble::goQuick()
{
    bubbleSignal3();//激活更新数据的槽函数
    QElapsedTimer s;//代码暂停的关键部分
    bubbleSignal2();//激活打印表格的槽函数
    s.start();
    while(s.elapsed()<3000);//时间延迟
    QTime qtime;//新增部分
    qtime.start();//计时开始
    quickSort(0,length-1);//进行快排

    for(int i = 0; i < length;i++){
        bubbleSignal(i);
        QThread::msleep(static_cast<unsigned int>(mDelay));
    }
    bubbleSignal2();//激活打印表格的槽函数
    qDebug()<<"程序的运行时间为："<<qtime.elapsed()/1000.0<<"s";//打印花费时间
}

void Bubble::quickSort(int l, int r)//快速排序
{
    if(l < r){
        int mid = quickQartition(l,r);//得到分割数，完成后mid元素大于左侧元素小于右侧元素
        quickSort(l,mid);       //再次进行快排
        quickSort(mid+1,r);     //递归完成快速排序

    }
}
//将数组的最左边的数据为分割数，将比分割数大的数放在分割数的右边，小的放在左边
//返回分割数最后所在的位子
int Bubble::quickQartition(int l, int r)
{
    QElapsedTimer s;
    int t = data[l];    //t为分割数
    bubbleSignal4(l,-1,1);//枢轴元素闪红
    s.start();
    while(s.elapsed()<2000);//时间延迟
    bubbleSignal4(-1,-1,1);//取消闪红
    while(l < r){
        while(l < r && data[r] >= t)//如果最右边的数大于分割数，则寻次右边的数进行比较
            r --;
        quickSwap(l,r); //如果分割数比右边的数要大，则将俩者交换位子
        s.start();
        while(s.elapsed()<1000);//时间延迟
        bubbleSignal5();
        while(l < r && data[l] <= t)//同上
            l ++;
        quickSwap(l,r);
        s.start();
        bubbleSignal5();
        while(s.elapsed()<1000);//时间延迟
    }
    bubbleSignal3();//激活更新数据的槽函数
    bubbleSignal4(l,-1,0);//激活序列颜色标签的槽函数
    s.start();
    while(s.elapsed()<2000);//时间延迟
    bubbleSignal4(-1,-1,-1);//取消闪红
    return l;
}

void Bubble::quickSwap(int one, int two)//交换元素的函数
{
    int temp = data[one];
    data[one] = data[two];
    data[two] = temp;
    bubbleSignal(one);
    //趟数太多
    QThread::msleep(static_cast<unsigned int>(mDelay));
}
//快速排序结束



//基数排序
//原理：的基本思想是将待排序的记录按照位数从低到高依次排序，每次排完一位后，再根据下一位进行排序，直到所有位都排完为止。
void Bubble::goRadix()
{
    QTime qtime;//新增部分
    qtime.start();//计时开始
    int max = data[0];//寻找最大值，由此得知所需的位数
    for(int i = 1 ; i < length; i++){
        if(data[i] > max)
            max = data[i];
    }
    //以个、十、百....的位的数目来遍历
    for (int exp = 1; max/exp > 0; exp *= 10) {
        int output[length];
        int count[10] = {0};
        for(int i = 0; i < length; i++){//得到每个位数上的数字的个数
            count[(data[i]/exp)%10]++;  //例如在{1,2,11,13,4}个位为一的有2个，个位为2的有1，...
        }
        //然后将所得到的所有位数进行累加求和，方便判断是在output[]的那个位子上
        for(int i = 1; i < 10; i++){
            count[i] += count[i - 1];
        }
        for(int i = length -1; i >= 0; i--){
            output[count[(data[i]/exp)%10] - 1]= data[i];
            count[(data[i]/exp)%10] --;
            bubbleSignal(i);
            QThread::msleep(static_cast<unsigned int>(mDelay));
        }

        for(int i = 0; i < length; i++){
            data[i] = output[i];//将此趟排序好的数据赋值回去
            bubbleSignal(i);//激活柱状图的颜色标签的槽函数
            bubbleSignal3();//激活更新数据的槽函数
            QThread::msleep(static_cast<unsigned int>(mDelay));
        }
        bubbleSignal3();//激活更新数据的槽函数

    }
    bubbleSignal2();//激活打印表格的槽函数
    qDebug()<<"程序的运行时间为："<<qtime.elapsed()/1000.0<<"s";//打印花费时间
}
//基数排序结束







//执行排序所需要调用的函数
 void Bubble::run_bubble()
{
     rand();
     goBubble();
}
void Bubble::run_bucket()
{
    rand();
    goBucket();

}
void Bubble::run_heap()
{
    rand();
    goHeap();

}
void Bubble::run_insertion()
{
    rand();
    goInsertion();
}
void Bubble::run_shell()
{
    rand();
    goShell();

}
void Bubble::run_quick()
{
    rand();
    goQuick();

}
void Bubble::run_radix()
{
    rand();
    goQuick();

}
void Bubble::run_merge()
{
    rand();
    goMerge();
}
void Bubble::run_choice()
{
    rand();
    goChoice();
}




