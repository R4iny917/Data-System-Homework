#include<iostream>
using namespace std;
//存储输入时的每条边的起点，终点和权值
struct temp {
	int start; int end;
	long long time;
};
//构造Edge来存储边
struct Edge {
	int to, next, v;
} a[300000];
int visit[300000];//判断该城市是否被访问
int N;//城市数量
//链式前向星的辅助数组和数值
int h[300000];
int cnt;

//链式前向星初始化
void add(int x, int y, int z) {
	a[++cnt].to = y;
	a[cnt].next = h[x];
	a[cnt].v = z;
	h[x] = cnt;
}
struct Pair {
	long long time;
	int src;
};
//用pair初始化最小堆，使得每个堆元素中分别存储城市编号和相隔时间
Pair minHeap[300000];
//记录最小堆大小
int minHeapSize = 0;
//最小堆上滤（基于time大小，下同）
void FilterDown(int start, int EndOfHeap) {
	int i = start, j = 2 * i + 1; // j 是 i 的左子女
	Pair temp = minHeap[i];
	while (j <= EndOfHeap) {
		if (j < EndOfHeap &&
			minHeap[j].time > minHeap[j + 1].time) j++; //两子女中选小者
		if (temp.time <= minHeap[j].time) break;
		else {
			minHeap[i] = minHeap[j]; //下面的上浮
			i = j; j = 2 * j + 1; //向下滑动
		}
	}
	minHeap[i] = temp;
}
//最小堆下滤
void FilterUp(int start) {
	//从 start 开始,向上直到0,调整堆
	int j = start, i = (j - 1) / 2; // i 是 j 的双亲
	Pair temp = minHeap[j];
	while (j > 0) {
		if (minHeap[i].time <= temp.time) break;
		else { minHeap[j] = minHeap[i]; j = i; i = (i - 1) / 2; }
	}
	minHeap[j] = temp;
}
//移除最小堆堆顶元素
void Remove() {

	// x = minHeap[0]; //最小元素出队列
	minHeap[0] = minHeap[minHeapSize - 1];
	minHeapSize--; //用最小元素填补
	FilterDown(0, minHeapSize - 1); //调整
}
//插入最小堆
void Insert(int time, int src) {

	minHeap[minHeapSize].time = time;
	minHeap[minHeapSize].src = src;//插在表尾
	FilterUp(minHeapSize); //向上调整为堆
	minHeapSize++; //堆元素增一
}
//dijkstra算法
void dij(int src, long long* dijk) {
	for (int i = 0; i < N; i++) {
		//初始化当前的dijk数组和visit数组
		dijk[i] = 1e18;
		visit[i] = 0;
	}
	dijk[src] = 0;//初始点到当前点距离为0
	Insert(0, src);//将当前点插入最小堆
	while (minHeapSize != 0) {
		int x = minHeap[0].src; //取出最小堆堆顶的src
		Remove();//移除最小堆堆顶元素
		if (visit[x]) continue;//如果当前src访问过,继续下一轮循环
		visit[x] = 1;//当前结点被访问过
		for (int i = h[x]; i; i = a[i].next)//遍历与当前结点相连的边
			//如果该节点被访问过，并且经过该点而到达最终点的权值总和小于原来的权值
			//则更改到达最终点的权值，并将其保存到最小堆中
			if (visit[x] && dijk[x] + a[i].v < dijk[a[i].to]) {
				dijk[a[i].to] = dijk[x] + a[i].v;
				Insert(dijk[a[i].to], a[i].to);
			}

	}
}

long long dijk[3][300000];//分别对应src1,src2,dest到各点的最短距离
int main() {
	int m, n, src1, src2, dest;
	cin >> m >> n >> src1 >> src2 >> dest;
	N = m;
	temp* tmp = new temp[n];
	for (int i = 0; i < n; ++i)
		cin >> tmp[i].start >> tmp[i].end >> tmp[i].time;	
	//存储邻接表
	for (int i = 0; i < n; ++i)
		add(tmp[i].start, tmp[i].end, tmp[i].time);	
	// 得出src1, src2到各点的最短距离
	dij(src1, dijk[0]); dij(src2, dijk[1]);	
	//清零辅助数组和数值
	for (int i = 0; i < m; i++) h[i] = 0;
	cnt = 0;	
	//存储逆邻接表
	for (int i = 0; i < n; ++i) 
		add(tmp[i].end, tmp[i].start, tmp[i].time);	
	//得出dest到各点的最短距离
	dij(dest, dijk[2]);
	long long ans = 1e18;	
	//遍历所有节点得出最小值
	for (int i = 0; i < m; i++) 
		ans = min(ans, dijk[0][i] + dijk[1][i] + dijk[2][i]);	
	//输出答案
	if (ans == 1e18) cout << -1;
	else cout << ans;
}