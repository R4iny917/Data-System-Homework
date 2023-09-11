#include <iostream>
#include <assert.h>
using namespace std;
int maxHeap[10000000]; //以数组的方式实现最大堆
int minHeap[10000000]; //以数组的方式实现最小堆
unsigned long long maxHeapSize = 0; //记录最大堆的容量
unsigned long long minHeapSize = 0; //记录最小堆的容量

//最大堆下滤
void FilterDownMax(int start, int end)
{
    int i = start;
    int j = i * 2 + 1;
    int tmp = maxHeap[i];
    while (j <= end) {
        if (j + 1 <= end && maxHeap[j] < maxHeap[j + 1])
            ++j;
        if (tmp < maxHeap[j])
            maxHeap[i] = maxHeap[j];
        else
            break;
        i = j;
        j = j * 2 + 1;
    }
    maxHeap[i] = tmp;
}

//最大堆上滤
void FilterUpMax(int start)
{
    int j = start;
    int i = (start - 1) / 2;

    int tmp = maxHeap[j];
    while (j > 0) {
        if (tmp < maxHeap[i])
            break;
        else
            maxHeap[j] = maxHeap[i];

        j = i;
        i = (i - 1) / 2;
    }
    maxHeap[j] = tmp;
}
//最大堆插入元素
void InsertMax(int val)
{
    maxHeap[maxHeapSize] = val;
    FilterUpMax(maxHeapSize);
    ++maxHeapSize;
}
//最大堆移除堆顶
void RemoveMax()
{
    maxHeap[0] = maxHeap[maxHeapSize - 1];
    maxHeap[maxHeapSize - 1] = 0;
    --maxHeapSize;
    FilterDownMax(0, maxHeapSize - 1);
}
//最小堆下滤
void FilterDownMin(int start, int EndOfHeap) {
    int i = start, j = 2 * i + 1; // j 是 i 的左子女
    int temp = minHeap[i];
    while (j <= EndOfHeap) {
        if (j < EndOfHeap &&
            minHeap[j] > minHeap[j + 1]) j++; //两子女中选小者
        if (temp <= minHeap[j]) break;
        else {
            minHeap[i] = minHeap[j]; //下面的上浮
            i = j; j = 2 * j + 1; //向下滑动
        }
    }
    minHeap[i] = temp;
}
//最小堆上滤
void FilterUpMin(int start) {
    //从 start 开始,向上直到0,调整堆
    int j = start, i = (j - 1) / 2; // i 是 j 的双亲
    int temp = minHeap[j];
    while (j > 0) {
        if (minHeap[i] <= temp) break;
        else { minHeap[j] = minHeap[i]; j = i; i = (i - 1) / 2; }
    }
    minHeap[j] = temp;
}
//移除最小堆堆顶元素
void RemoveMin() {

    minHeap[0] = minHeap[minHeapSize - 1];
    minHeapSize--; //用最小元素填补
    FilterDownMin(0, minHeapSize - 1); //调整
}
//最小堆插入元素
void InsertMin(int x) {

    minHeap[minHeapSize] = x; //插在表尾
    FilterUpMin(minHeapSize); //向上调整为堆
    minHeapSize++; //堆元素增一
}


int main()
{
    int M, N;
    cin >> M >> N;
    int input;
    for (int i = 0; i < N; ++i) {
        scanf("%d", &input);
        InsertMax(input); //将输入元素存入最大堆
        int cap; //计算当前的[x/m]值大小
        if ((i + 1) % M == 0)
            cap = (i + 1) / M;
        else
            cap = (i + 1) / M + 1;
        //如果最小堆尺寸小于[x/m]，直接将最大堆堆顶元素插入最小堆，并移除最大堆堆顶元素
        if (minHeapSize < cap) {
            InsertMin(maxHeap[0]);
            RemoveMax();
        }
        //如果不小于，由于最小堆大小每轮最多加一，则最小堆尺寸一定与[x/m]相同。
        //所以在移除最大堆堆顶元素后，再将最小堆堆顶元素插入最大堆并移除最小堆堆顶元素
        else {
            InsertMin(maxHeap[0]);
            RemoveMax();
            InsertMax(minHeap[0]);
            RemoveMin();
        }
        //输出最小堆堆顶元素即为答案
        printf("%d ", minHeap[0]);
    }
}