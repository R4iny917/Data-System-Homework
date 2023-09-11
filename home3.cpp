#include <iostream>
#include<string>
#include<algorithm>
using namespace std;
int strength[100200]; //存储冒险者力量
int id[100200];      //存储冒险者ID   
string name[100200];   //存储冒险者姓名
int adsize = 0;  //记录当前冒险者的数量
//插入冒险家
void Insert(int Id, string Name, int Strength)
{
    id[adsize] = Id;
    name[adsize] = Name;
    strength[adsize] = Strength;
    adsize++;
    //如果插入元素比原先队列最大的元素要大，则查询插入位置
    if (id[adsize - 1] < id[adsize - 2]) {
        //存储冒险家对应的ID,name，strength
        int tempid = id[adsize - 1];
        string tempname = name[adsize - 1];
        int tempstrength = strength[adsize - 1];
        int index = 0;
        for (int i = 0; i < adsize - 1; ++i) {
            //查找到位置
            if (tempid < id[i]) {
                index = i ;
                //将该位置即其后的元素全部后移一位
                for (int i = adsize - 1; i > index; --i) {
                    id[i] = id[i - 1];
                    name[i] = name[i - 1];
                    strength[i] = strength[i - 1];
                }
                //插入
                id[index] = tempid;
                name[index] = tempname;
                strength[index] = tempstrength;
                break;
            }
        }
    }
}
//删除指定冒险家ID
void Delete(int ID) {
    int temp = 0;
    for (int i = 0; i < adsize; ++i) {
        if (id[i] == ID) {
            temp = i;
            break;
        }
    }
    for (int i = temp; i < adsize - 1; ++i) {
        id[i] = id[i + 1];
        name[i] = name[i + 1];
        strength[i] = strength[i + 1];
    }
    adsize--;
}
//删除ID >= ID1 并且 ID <= ID2的冒险家
void Delete(int ID1, int ID2) {
    int* tempId = new int[adsize];
    string* tempName = new string[adsize];
    int* tempStrength = new int[adsize];
    for (int i = 0; i < adsize; ++i) {
        tempId[i] = id[i];
        tempName[i] = name[i];
        tempStrength[i] = strength[i];
    }
    int tempSize = adsize;
    adsize = 0;
    for (int i = 0; i < tempSize; ++i) {
        if (tempId[i] >= ID1 && tempId[i] <= ID2)
            continue;
        else {
            id[adsize] = tempId[i];
            name[adsize] = tempName[i];
            strength[adsize] = tempStrength[i];
            adsize++;
        }
    }
    delete[]tempId;
    delete[]tempName;
    delete[]tempStrength;
}
//查询指定ID的冒险家
void Query(int ID) {
    for (int i = 0; i < adsize; ++i)
        if (id[i] == ID) {
            printf("%d %s %d\n", id[i], name[i].c_str(), strength[i]);
            break;
        }
}
//查询指定姓名的冒险家
void Query(string Name) {
    for (int i = 0; i < adsize; ++i)
        if (name[i] == Name) {
            printf("%d %s %d\n", id[i], name[i].c_str(), strength[i]);
        }
}
//查询strength cmp(cmp为指令所给的符号，为=,!=,>=,>,<=,<) value的冒险家
void Query(int value, string cmp) {
    if (cmp == "<") {
        for (int i = 0; i < adsize; ++i) {
            if (strength[i] < value)
                printf("%d %s %d\n", id[i], name[i].c_str(), strength[i]);
        }
    }
    else if (cmp == "<=") {
        for (int i = 0; i < adsize; ++i) {
            if (strength[i] <= value)
                printf("%d %s %d\n", id[i], name[i].c_str(), strength[i]);
        }
    }
    else if (cmp == "=") {
        for (int i = 0; i < adsize; ++i) {
            if (strength[i] == value)
                printf("%d %s %d\n", id[i], name[i].c_str(), strength[i]);
        }
    }
    else if (cmp == "!=") {
        for (int i = 0; i < adsize; ++i) {
            if (strength[i] != value)
                printf("%d %s %d\n", id[i], name[i].c_str(), strength[i]);
        }
    }
    else if (cmp == ">") {
        for (int i = 0; i < adsize; ++i) {
            if (strength[i] > value)
                printf("%d %s %d\n", id[i], name[i].c_str(), strength[i]);
        }
    }
    else if (cmp == ">=") {
        for (int i = 0; i < adsize; ++i) {
            if (strength[i] >= value)
                printf("%d %s %d\n", id[i], name[i].c_str(), strength[i]);
        }
    }
}
//查询ID1<=ID<=ID2，并且strength cmp(cmp为指令所给的符号，为=,!=,>=,>,<=,<) value的冒险家
void Query(int ID1, int ID2, int value, string cmp) {
    if (cmp == "<") {
        for (int i = 0; i < adsize; ++i) {
            if (strength[i] < value && id[i] >= ID1 && id[i] <= ID2)
                printf("%d %s %d\n", id[i], name[i].c_str(), strength[i]);
        }
    }
    else if (cmp == "<=") {
        for (int i = 0; i < adsize; ++i) {
            if (strength[i] <= value && id[i] >= ID1 && id[i] <= ID2)
                printf("%d %s %d\n", id[i], name[i].c_str(), strength[i]);
        }
    }
    else if (cmp == "=") {
        for (int i = 0; i < adsize; ++i) {
            if (strength[i] == value && id[i] >= ID1 && id[i] <= ID2)
                printf("%d %s %d\n", id[i], name[i].c_str(), strength[i]);
        }
    }
    else if (cmp == "!=") {
        for (int i = 0; i < adsize; ++i) {
            if (strength[i] != value && id[i] >= ID1 && id[i] <= ID2)
                printf("%d %s %d\n", id[i], name[i].c_str(), strength[i]);
        }
    }
    else if (cmp == ">") {
        for (int i = 0; i < adsize; ++i) {
            if (strength[i] > value && id[i] >= ID1 && id[i] <= ID2)
                printf("%d %s %d\n", id[i], name[i].c_str(), strength[i]);
        }
    }
    else if (cmp == ">=") {
        for (int i = 0; i < adsize; ++i) {
            if (strength[i] >= value && id[i] >= ID1 && id[i] <= ID2)
                printf("%d %s %d\n", id[i], name[i].c_str(), strength[i]);
        }
    }
}
//收取当前指令并分析
void getCommand() {
    //收取第一个输入的英语单词
    string cmd;
    cin >> cmd;
    if (cmd == "INSERT") {
        int ID, STRENGTH;
        string NAME;
        cin >> ID >> NAME >> STRENGTH;
        Insert(ID, NAME, STRENGTH);
    }
    else if (cmd == "DELETE") {
        int ID1 = -1;
        int ID2 = -1;
        int a;
        int order = 0;
        while (cin >> a) {
            if (order == 0) {
                ID1 = a;
                ++order;
            }
            else
                ID2 = a;
            if (cin.get() == '\n')break;
        }
        if (ID2 == -1)Delete(ID1);
        else Delete(ID1, ID2);
    }
    else if (cmd == "QUERY") {
        string a[10], b;
        int count = 0;
        //获取该行输入的所有元素
        while (cin >> b)
        {
            a[count++] = b;
            if (cin.get() == '\n')break;
        }
        //count = 1,说明为查找ID
        if (count == 1) 
        {
            int x = stoi(a[0]);
            Query(x);
        }
        //输入的第一个单词为name,说明查找姓名
        else if (a[0] == "name") 
        {
            Query(a[2]);
        }
        //输入的第一个单词为strength,说明查找strength范围
        else if (a[0] == "strength")
        {
            int x = stoi(a[2]);
            Query(x, a[1]);
        }
        //若非上列所属情况，则为查找ID1<=ID<=ID2,且strength符合一定范围的冒险者
        else
        {
            int ID1 = stoi(a[0]);
            int ID2 = stoi(a[1]);
            string cmp = a[3];
            int value = stoi(a[4]);
            Query(ID1, ID2, value, cmp);
        }
    }
}


int main()
{
    int m,n;
    cin >> m >> n;
    int ID, value;
    string name;
    for (int i = 0; i < m; ++i) {     
        cin >>ID >> name >> value;
        Insert(ID, name, value);
    }
    for (int i = 0; i < n; ++i)
        getCommand();
    return 0;
}
