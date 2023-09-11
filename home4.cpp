#include<iostream>
using namespace std;
#define maxN 200000  //定义数组尺寸
#define mod 199999;  //哈希mod值
int Vout[maxN][600]; //经过哈希处理的结点的邻接表
int sizeVout[maxN];  //经过哈希处理的结点出度
int Vin[maxN][600];  //经过哈希处理的结点的逆邻接表
int sizeVin[maxN];   //经过哈希处理的结点的入度
bool vis[maxN];      //判断哈希处理的结点是否被访问过
int rPath2[maxN][8]; //反向存储两层路径
int rPath2Size[maxN];//存储结点对应路径的size
int vis1[maxN];      //标记反向距离不超过3的所有结点
int vis2[maxN];      //标记走两步可到达head的结点
int answer = 0;      //答案
int Hash[maxN];      //hash表
//哈希值写入
int writeHash(int x) {
    int tempX = x % mod;
    while (Hash[tempX] != -1 && Hash[tempX] != x) {
        ++tempX;
        if (tempX == 199999)
            tempX = 0;
    }
    Hash[tempX] = x;
    return tempX;
}
//哈希值读取
int getHash(int x) {
    int tempX = x % mod;
    while (Hash[tempX] != x) {
        ++tempX;
    }
    return tempX;
}
//以逆邻接表来求得rPath2和vis2
void rdfs3(int head, int cur, int depth)
{
    //求得cur对应的Hash值，并使得该hashCur已被访问
    int hashCur = getHash(cur);
    vis[hashCur] = true;
    //遍历hashCur的入边
    for (int i = 0; i < sizeVin[hashCur]; ++i)
    {
        //求得入边点并将之进行Hash处理
        int ver = Vin[hashCur][i];       
        int hashVer = getHash(ver);
        //如果访问过或者当前值小于head值，此放弃此轮循环
        if (ver < head || vis[hashVer]) continue;
        //将当前head值保存到vis1[hashVer]中，表示该节点可以到达head
        vis1[hashVer] = head;
        //如果深度为2则深入处理
        if (depth == 2)
        {
            //如果vis2[hashVer]保存的不是head结点，则将rPath2[hash]清零
            if (vis2[hashVer] != head)
            {
                for (int i = 0; i < rPath2Size[hashVer]; ++i)
                    rPath2[hashVer][i] = 0;
                rPath2Size[hashVer] = 0;
            }
            //令vis2[hashVer] = head，并将当前的cur存储到hashVer所对应的rPath2路径中
            vis2[hashVer] = head;
            rPath2[hashVer][rPath2Size[hashVer]] = cur;
            rPath2Size[hashVer]++;
        }
        //若深度小于3，则继续搜索
        if (depth < 3)
            rdfs3(head, ver, depth + 1);
    }
    //回溯，置vis[hashCur]为未访问的状态
    vis[hashCur] = false;
}
//以邻接表进行搜索
void dfs5(int head, int cur, int depth)
{
    //将Cur值进行hash处理
    int hashCur = getHash(cur);
    vis[hashCur] = true;
    //遍历hashCur所有的出边
    for (int i = 0; i < sizeVout[hashCur]; ++i)
    {
        //获取当前的出边结点并将之进行hash处理
        int ver = Vout[hashCur][i];
        int hashVer = getHash(ver);
        //如果访问过或者当前值小于head值，此放弃此轮循环
        if (ver < head || vis[hashVer]) continue;
        //若深度大于3，且此时不能访问到head，则放弃此轮循环
        if (depth > 3 && vis1[hashVer] != head) continue; 
        // 环的判定条件: ver结点走两步可到达head
        if (vis2[hashVer] == head)
        {   //遍历hashVer对应的rPath
            for (int j = 0; j < rPath2Size[hashVer]; ++j)
            {
                //得到hashVer路径上所经过的点，并将之进行hash处理
                //若已经访问，则放弃此轮循环，若非，则答案加一
                int temp = rPath2[hashVer][j];
                int hashTemp = getHash(temp);
                if (vis[hashTemp]) continue;
                ++answer;
            }
        }
        if (depth < 5)   // 继续搜索
            dfs5(head, ver, depth + 1);
    }
    vis[hashCur] = false;
}

struct EDGE {
    int start;
    int end;
};

int main()
{
    int m;
    scanf("%d", &m);
    EDGE* edge = new EDGE[m];
    for (int i = 0; i < m; ++i)
        scanf("%d%d", &edge[i].start, &edge[i].end);
    for (int i = 0; i < maxN; ++i)
        Hash[i] = -1;
    //保存邻接表和逆邻接表
    for (int i = 0; i < m; ++i) {
        int tempStart = writeHash(edge[i].start);
        int tempEnd = writeHash(edge[i].end);
        Vout[tempStart][sizeVout[tempStart]] = edge[i].end;
        Vin[tempEnd][sizeVin[tempEnd]] = edge[i].start;
        ++sizeVout[tempStart];
        ++sizeVin[tempEnd];
    }
    for (int i = 0; i < maxN; ++i)
    {
        if (sizeVout[i] && sizeVin[i])  // 只有出入度不为0的结点才会构成环
        {
            rdfs3(Hash[i], Hash[i], 1);
            dfs5(Hash[i], Hash[i], 1);
        }
    }
    cout << answer;
}
