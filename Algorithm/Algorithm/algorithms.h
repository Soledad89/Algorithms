
#ifndef Algorithm_Functions_h
#define Algorithm_Functions_h
#include <stack>
#include <list>
#include <assert.h>
#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <bitset>
#include <map>
#include <queue>
#include <exception>
#include <assert.h>

using namespace std;


//结构定义
//单链表节点
struct node {
    int data;
    node* next;
    node(int e = 0): data(e) {}
};
typedef node Node;
//双向链表节点
struct ListNode {
    int data;
    ListNode* pred;
    ListNode* succ;
    ListNode() {};
    ListNode(int e = 0, ListNode* p = NULL, ListNode* s = NULL):
    data(e), pred(p), succ(s){}
};
//二叉树节点
struct BinaryTreeNode{              // a node in the binary tree
    int m_nValue;                   // value of node
    BinaryTreeNode *m_pLeft;        // left child of node
    BinaryTreeNode *m_pRight;       // right child of node
    BinaryTreeNode() {};
    BinaryTreeNode(int nv = 0, BinaryTreeNode* pl = NULL, BinaryTreeNode* rl = NULL):
    m_nValue(nv), m_pLeft(pl), m_pRight(rl) {}
};

//problem: 判断一点是否在多边形内
//algorithm: 射线交点判奇法
// 方法：求解通过该点的水平线与多边形各边的交点
// 结论：单边交点为奇数，成立!
struct point
{
    double x, y;
};

bool PtInPolygon(point p, vector<point> ptPolygon, int nCount)
{
    int nCross = 0;
    for (int i = 0; i < nCount; i++)
    {
        point p1 = ptPolygon[i];
        point p2 = ptPolygon[(i + 1) % nCount];
        // 求解 y=p.y 与 p1p2 的交
        if ( p1.y == p2.y ) // p1p2 与 y=p0.y平行
            continue;
        if ( p.y < min(p1.y, p2.y) ) // 交点在p1p2延长线上
            continue;
        if ( p.y >= max(p1.y, p2.y) ) // 交点在p1p2延长线上
            continue;
        // 求交点的 X 坐标 -----------------------------
        double x = (double)(p.y - p1.y) * (double)(p2.x - p1.x) / (double)(p2.y - p1.y) + p1.x;
        
        if ( x > p.x )
            nCross++; // 只统计单边交点
    }
        // 单边交点为偶数，点在多边形之外 ---
    return (nCross % 2 == 1);
}

//algorithm2: 向量乘积法
//A，B，C 在逆时针方向
//如果D在ABC之外，返回false，否则返回true
//注：此处依赖于A、B、C的位置关系，其位置不能调换
double Product(point A, point B, point C)
{
    return (B.x - A.x) * (C.y - A.y) - (C.x - A.x) * (B.y - A.y);
}

bool isInTriangle(point A, point B, point C, point D)
{
    if (Product(A, B, D) >= 0 && Product(B, C, D) >= 0 && Product(C, A, D) 	 >= 0)
    {
        return true;
    }
    return false;
}

//algorithm3: 7行代码解决问题
//http://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html
int pnpoly(int nvert, float *vertx, float *verty, float testx, float testy)
{
    int i, j, c = 0;
    for (i = 0, j = nvert-1; i < nvert; j = i++) {
        if ( ((verty[i]>testy) != (verty[j]>testy)) &&
            (testx < (vertx[j]-vertx[i]) * (testy-verty[i]) / (verty[j]-verty[i]) + vertx[i]) )
            c = !c;
    }
    return c;
}

//problem: lower_bound 和 upper_bound的实现
//algorithm:
/*
 int point[10] = {1,3,7,7,9};
 int tmp = upper_bound(point, point + 5, 7) - point;
 //按从小到大，7最多能插入数组point的哪个位置
 tmp = lower_bound(point, point + 5, 7) - point;
 //按从小到大，7最少能插入数组point的哪个位置
 */
int my_lower_bound(int *array, int size, int key)
{
    int first = 0, last = size-1;
    int middle, pos = 0;       //需要用pos记录第一个大于等于key的元素位置
    
    while(first < last)
    {
        middle = (first+last)/2;
        if(array[middle] < key){      //若中位数的值小于key的值，我们要在右边子序列中查找，这时候pos可能是右边子序列的第一个
            first = middle + 1;
            pos = first;
        }
        else{
            last = middle;           //若中位数的值大于等于key，我们要在左边子序列查找，但有可能middle处就是最终位置，所以我们不移动last,
            pos = last;              //而是让first不断逼近last。
        }
    }
    return pos;
}
int my_upper_bound(int *array, int size, int key)
{           //upper_bound返回的是最后一个大于等于val的位置，也是有一个新元素val进来时的插入位置。
    int first = 0, last = size-1;
    int middle, pos = 0;
    
    while(first < last)
    {
        middle = (first+last)/2;
        if(array[middle] > key){     //当中位数大于key时，last不动，让first不断逼近last
            last = middle;
            pos = last;
        }
        else{
            first = middle + 1;     //当中位数小于等于key时，将first递增，并记录新的位置
            pos = first;
        }
    }
    return pos;
}

//problem: 编程之美区间重合判断
/*
 1. 给定一个源区间[x,y]和N个无序的目标区间[x1,y1] [x2,y2] ... [xn,yn]，
    判断源区间[x,y]是不是在目标区间内。
 2. 给定一个窗口区域和系统界面上的N个窗口，判断这个窗口区域是否被已有的窗口覆盖。
 */
//algorithm:
struct interval{
    int low, high;
    interval(int l=0, int h=0):low(l), high(h){}

};

struct {
    bool operator()(const interval &v1, const interval &v2)
    {
        return v1.low < v2.low;
    }
} intervalLess;


int BinarySearchLower(vector<interval> arrayInterval, int len, int target)//注意咱们搜索的数为刚好小于key的那个值
{
    
    int low = 0, pos = 0;
    int high = len-1;
    while(low < high){
        int mid = (low + high)/2;
        if(arrayInterval[mid].low < target) {
            low = mid + 1;
            pos = low;
        }
        else
        {
            high = mid;
            pos = high;
        }
    }
    if (arrayInterval[pos].low > target)    //这一句特别关键，当相等时或者高出数组的最大边缘时，这时不需要减去1，只有当目标值比当前最小插入点处的元素小时，就需要往前移动一位。
        return pos-1;
    else
        return pos;        //返回结果为在哪段中
}

bool intervalCoverage(vector<interval> vIntervals, interval tInterval)
{
    bool flag = false;
    
    int n = (int)vIntervals.size();
    if (n <= 0)
        return flag;
    
    sort(vIntervals.begin(), vIntervals.end(), intervalLess);
    int cnt = 0; //合并以后的区间数
    int lastHigh = vIntervals[0].high;
    
    //合并区间
    for(int i=1; i < n; i++){
        if(lastHigh >= vIntervals[i].low && lastHigh < vIntervals[i].high)
            lastHigh = vIntervals[i].high;
        else{
            vIntervals[cnt].high = lastHigh;
            vIntervals[++cnt].low = vIntervals[i].low;
            lastHigh = vIntervals[i].high;
        }
        
    }
    vIntervals[cnt++].high = lastHigh;
    
    int sLow = BinarySearchLower(vIntervals, cnt, tInterval.low);
 
    //注意这里实现了类似于lower_bound的函数
    int sHigh = BinarySearchLower(vIntervals, cnt, tInterval.high);

    
    if(sLow == sHigh && tInterval.high <= vIntervals[sLow].high)
        //注意要判断
        flag = true;

    return flag;
}


//problem: 不用除法，求N个整数数组中N-1个整数的最大乘积
//algorithm: 统计分析规律
//我刚开始想的就是分析乘积是正还是负，但是考虑到可能产生大数，所以觉得难度就增加了，结果
//发现可以统计正负号的方法
void subarrayMultiplication(int array[], int size)
{
    int zeroNum = 0;
    int negativeNum = 0;
    int positiveNum = 0;
    int maxNegative = INT_MIN;
    int minPositive = INT_MAX;
    int zeroIndex = 0;
    int minNegative = 0;
    for(int i = 0; i < size; ++i) {
        if(array[i] == 0) {
            ++zeroNum;
            zeroIndex = i;
        }
        else if(array[i] < 0) {
            ++negativeNum;
            if(array[i] > maxNegative)
                maxNegative = array[i];
            if(array[i] < minNegative)
                minNegative = array[i];
        }
        else {
            ++positiveNum;
            if(array[i] < minPositive)
                minPositive = array[i];
        }
    }
    
    //如果数组中包含两个或者两个以上0，那么子数组的乘积肯定为0
    if(zeroNum >= 2) {
        printf("all subArray elements' product is equal to zero");
        return;
    }
    
    //如果数组中只包含一个0，那么分两个情况：
    //1.去除该0元素其余所有数的乘积为正，那么去除该0元素后所得的子数组乘积最大
    //2.去除该0元素其余所有数的乘积为负，那么子数组最大的乘积为0，子数组中必须包含0元素
    if(zeroNum == 1) {
        if(negativeNum % 2 == 0) {
            printf("the sunArray elements' indexs is except: %d\n", zeroIndex);
        }
        else {
            printf("the subArray must have the index %d of element\n", zeroIndex);
        }
        
        return;
    }
    
    //如果数组中有偶数个负数：
    //1.假定数组中存在正元素，则去掉最小正元素即可得到子数组的最大乘积
    //2.假定数组中不存在正元素，则需要去掉最小的负数，即绝对值最大的负数
    //如果数组中有奇数个负数：
    //则只需要去掉值最大的负数，及绝对值最小的负数
    if(negativeNum % 2 == 0 && positiveNum > 0) {  //需考虑没有正元素的情况
        printf("the subArray elements' indexs in except: %d\n", minPositive);
    }
    else if(negativeNum % 2 == 0 && positiveNum == 0) {
        printf("the subArray elements' indexs is except: %d\n", minNegative);
    }
    else {
        printf("the subArray elements' indexs is except: %d\n", maxNegative);
    }
    
}



//problem:求N的阶乘的末尾有多少个零，N的阶乘的二进制表示最低位1的位置
//algorithm: N的阶乘可以表示为2^x * 3^y * 5^z。零的个数即为min(x,z)，由于x肯定远大于z所以只需要求5的个数z，二进制表示最低位1即为求x
void nFactor(int N) {   //N!含有质因子为5的个数
    int ret = 0;
    for(int i = 1; i <= N; i++)
    {
        int j = i;
        while(j % 5 ==0)
        {
            ret++;
            j /= 5;
        }
    }
}
int lowestOne(int N)  //N!含有质因子为2的个数
{
    int Ret = 0;
    while(N)
    {
        N >>= 1;
        Ret += N;
    }
    return Ret;
}

//problem:
//algorithm: 用STL中的list来模拟双向链表的结构以及删除工作，只需在迭代器指向末尾节点时，将其指向的下一个节点设置为头结点即可
//
int LastRemaining_Solution1(unsigned int n, unsigned int m)
{
    if(n < 1 || m < 1)
        return -1;
    
    unsigned int i = 0;
    
    list<int> numbers;
    for(i = 0; i < n; ++ i)
        numbers.push_back(i);
    
    list<int>::iterator current = numbers.begin();
    while(numbers.size() > 1)
    {
        for(int i = 1; i < m; ++ i)
        {
            current ++;
            if(current == numbers.end())
                current = numbers.begin();
        }
        
        list<int>::iterator next = ++ current;
        if(next == numbers.end())
            next = numbers.begin();
        
        -- current;
        numbers.erase(current);
        current = next;
    }
    
    return *(current);
}

//
int LastRemaining_Solution2(unsigned int n, unsigned int m)
{
    if(n < 1 || m < 1)
        return -1;
    
    int last = 0;
    for (int i = 2; i <= n; i ++)
        last = (last + m) % i;
    
    return last;
}


//problem: 判断一个五位纸牌是不是一个顺子
//algorithm: 分别排序之后，求出0的个数以及gap的数目，判断zero的个数与gap的数目是否相等，相等则是一个顺子
int compare__(const void *arg1, const void *arg2);

bool IsContinuous(int* numbers, int length)
{
    if(numbers == NULL || length < 1)
        return false;
    
    qsort(numbers, length, sizeof(int), compare__); //其实这里可以用hash来排序，但是由于数据量比较小，优势不明显，所以采用常用的排序算法
    
    int numberOfZero = 0;
    int numberOfGap = 0;

    for(int i = 0; i < length && numbers[i] == 0; ++i)
        ++ numberOfZero;
    
    int small = numberOfZero;
    int big = small + 1;
    while(big < length)
    {
        //
        if(numbers[small] == numbers[big])  //如果有相同的元素，那么肯定不会是顺子
            return false;
        
        numberOfGap += numbers[big] - numbers[small] - 1;
        small = big;
        ++big;
    }
    
    return (numberOfGap > numberOfZero) ? false : true;
}

int compare__(const void *arg1, const void *arg2)
{
    return *(int*)arg1 - *(int*)arg2;
}


//problem: 找到数组中唯一出现一次的两个整数
//algorithm: 利用异或的结果将数组分为两个部分，怎么分组才能使一个数字在其中一组，而另一个数字在另一组，而且保证每一组中其余的元素都是配对出现的
unsigned int FindFirstBitIs1(int num);
bool IsBit1(int num, unsigned int indexBit);

void FindNumsAppearOnce(int data[], int length, int* num1, int* num2)
{
    if (data == NULL || length < 2)
        return;
    
    int resultExclusiveOR = 0;
    for (int i = 0; i < length; ++ i)
        resultExclusiveOR ^= data[i];
    
    unsigned int indexOf1 = FindFirstBitIs1(resultExclusiveOR);
    
    *num1 = *num2 = 0;
    for (int j = 0; j < length; ++ j)
    {
        if(IsBit1(data[j], indexOf1))
            *num1 ^= data[j];
        else
            *num2 ^= data[j];
    }
}

//这就是分组的策略
unsigned int FindFirstBitIs1(int num)
{
    int indexBit = 0;
    while (((num & 1) == 0) && (indexBit < 8 * sizeof(int)))
    {
        num = num >> 1;
        ++ indexBit;
    }
    
    return indexBit;
}
//
bool IsBit1(int num, unsigned int indexBit) //验证第indexBit位是否为1
{
    num = num >> indexBit;
    return (num & 1);
}


//problem:统计排序的数组中元素k的个数
//algorithm:二分查找法，求出第一个和最后一个k
int GetFirstK(int* data, int length, int k, int start, int end);
int GetLastK(int* data, int length, int k, int start, int end);

int GetNumberOfK(int* data, int length, int k)
{
    int number = 0;
    
    if(data != NULL && length > 0)
    {
        int first = GetFirstK(data, length, k, 0, length - 1);
        int last = GetLastK(data, length, k, 0, length - 1);
        
        if(first > -1 && last > -1)
            number = last - first + 1;
    }
    
    return number;
}

//
int GetFirstK(int* data, int length, int k, int start, int end)
{
    if(start > end)
        return -1;
    
    int middleIndex = (start + end) / 2;
    int middleData = data[middleIndex];
    
    if(middleData == k)
    {
        if((middleIndex > 0 && data[middleIndex - 1] != k)
           || middleIndex == 0)
            return middleIndex;
        else
            end  = middleIndex - 1;
    }
    else if(middleData > k)
        end = middleIndex - 1;
    else
        start = middleIndex + 1;
    
    return GetFirstK(data, length, k, start, end);
}

//
int GetLastK(int* data, int length, int k, int start, int end)
{
    if(start > end)
        return -1;
    
    int middleIndex = (start + end) / 2;
    int middleData = data[middleIndex];
    
    if(middleData == k)
    {
        if((middleIndex < length - 1 && data[middleIndex + 1] != k)
           || middleIndex == length - 1)
            return middleIndex;
        else
            start  = middleIndex + 1;
    }
    else if(middleData < k)
        start = middleIndex + 1;
    else
        end = middleIndex - 1;
    
    return GetLastK(data, length, k, start, end);
}



//problem: 排列
//algorithm: 递归
void Permutation(char* pStr, char* pBegin);

void Permutation(char* pStr)
{
    if(pStr == NULL)
        return;
    
    Permutation(pStr, pStr);
}

int nPermu;
void Permutation(char* pStr, char* pBegin)//pStr指向整个字符串的第一个字符，pBegin指向当前我们做排列操作的字符串的第一个字符
{
    if(*pBegin == '\0')
    {
        printf("%d: ", nPermu);
        printf("%s\n", pStr);
        nPermu++;
    }
    else
    {
        for(char* pCh = pBegin; *pCh != '\0'; ++ pCh)
            //每一次递归，从pBegin向后扫描每一个字符，在交换pBegin和pCh之后，再对pBegin后面的字符串递归的排列操作
        {
            char temp = *pCh;
            *pCh = *pBegin;
            *pBegin = temp;
            
            Permutation(pStr, pBegin + 1);
            
            //temp = *pCh;
            //*pCh = *pBegin;
            //*pBegin = temp;
        }
    }
}


//problem:放皇后问题
//algorithm: 回溯-分支限定
//使用试探-回溯-剪枝法的头文件
#define QUEEN_MAX 20
extern int nSolu;
extern int nCheck;
extern int N;

struct Queen{
    int x, y;
    Queen (int xx = 0, int yy = 0) : x(xx), y(yy) {};
    bool operator==(Queen const & q) const {
        return ( x == q.x)       //行冲突
        || (y == q.y)            //列冲突
        || ( x + y == q.x + q.y) //沿对角线冲突
        || ( x - y == q.x - q.y);//沿反对脚线冲突
    }
    bool operator!=(Queen const& q) const { return !(*this == q); }
    
};

void displayRow(Queen& q)
{
    printf("%2d: ", q.x);
    int i = 0;
    while (i++ < q.y) printf("[]");
    printf("#");
    while (i++ < N)  printf("[]");
    printf("%2d\n", q.y);
    
}
void display(std::vector<Queen>& S, int nQueen)
{
    //system("clear");
    for_each(S.rbegin(), S.rend(), displayRow);
    if ( nQueen <= S.size())
        cout << nSolu << " solution(s) found after " << nCheck << " check(s)\n";
    //getchar();
    
}

bool findQueen(std::vector<Queen> qVec, const Queen queen)
{
    vector<Queen>::iterator iterQueen;
    bool flag = true;
    
    for (iterQueen = qVec.begin(); iterQueen != qVec.end(); iterQueen++)
        if ((*iterQueen) == queen) { flag = true; break; }
    if (iterQueen == qVec.end())
        flag = false;
    return flag;
}

//这个好理解一些，整个程序是有三个部分组成，都集中于一个do/while语句中
void placeQueens(int N)
{
    std::vector<Queen> solu; //stack storing the solution
    Queen q(0, 0);// start from the original point
    clock_t c_start = clock();
    
    do {
        
        //while ((q.y < N) && findQueen(solu, q)) //通过与已有皇后的比对
        while ((q.y < N) && find(solu.begin(),solu.end(),q) != solu.end()) //这个快多了，这一个部分是最花费时间的
        {
            q.y++; nCheck++;
        }//尝试找到可摆放下一个皇后的列
        
        if (q.y < N ) { //若存在摆放的列，则
            solu.push_back(q); //摆放上当前的皇后，并
            if ( solu.size() >= N ) //若部分解已成为全局解，则通过全局变量nSolu计数
            {
                nSolu++; display(solu, N);
            }
            q.x++;                  //转入下一行
            q.y = 0;                //从0列开始，试探下一个皇后
        }
        
        
        if ( solu.size() >= N || q.y >= N ) //若已出界，则
        {
            q = solu.back();
            solu.pop_back();
            q.y++;//回溯一行，并继续试探下一列
        }//否则，试探下一行
        
    }while ( (q.x > 0) || (q.y < N)) ; //所有分支均已或穷举或剪枝之后，算法结束,q==(0,N)的时候
    
    clock_t c_end = clock();
    double timeSpended = 1000.0 * (c_end - c_start)/CLOCKS_PER_SEC;
    printf("Time Spended %f (ms)\n", timeSpended);
}

//problem: knight moves
//algorithm: Astar A星算法 A* 主要利用A*算法和BFS算法
struct knight{
    int x,y,step;
    int g,h,f;                                      // f = g + h
    bool operator < (const knight & k) const{      //重载比较运算符
        return f > k.f;
    }
};
knight k;
bool visited[8][8];         //访问标记(关闭列表)
int xs,ys,xt,yt,ans;                               //起点(x1,y1),终点(x2,y2),最少移动次数ans
int dirs[8][2]={{-2,-1},{-2,1},{2,-1},{2,1},{-1,-2},{-1,2},{1,-2},{1,2}};//8个移动方向
priority_queue<knight> priQueue;//最小优先级队列(开启列表)

bool in(const knight & a){                         //判断knight是否在棋盘内
    if(a.x < 0 || a.y < 0 || a.x >= 8  || a.y >= 8)
        return false;
    return true;
}
int Heuristic(const knight &a){                    //manhattan估价函数
    return (abs(a.x-xt) + abs(a.y-yt)) * 10;
}
void Astar(){             //A*算法
    knight current, next;
    while(!priQueue.empty()){
        current = priQueue.top(), priQueue.pop(), visited[current.x][current.y] = true;
        if(current.x == xt && current.y == yt){                 //算法终止条件
            ans = current.step;
            break;
        }
        for(int i = 0; i < 8; i++){ //这里与下面的暴力搜索不一样，这是启发式的
            next.x = current.x+dirs[i][0];
            next.y = current.y+dirs[i][1];
            if(in(next) && !visited[next.x][next.y]){    //依次判断八个位置的属性是否满足要求，再压入队列中
                next.g = current.g + 23;             //23表示根号5乘以10再取其ceil
                next.h = Heuristic(next);
                next.f = next.g + next.h;
                next.step = current.step + 1;
                priQueue.push(next);
            }
        }
    }
}
int Astar_main(){   //测试
    char line[6];
    while(fgets(line, 7, stdin)){
        xs=line[0]-'a',ys=line[1]-'1',xt=line[3]-'a',yt=line[4]-'1';
        memset(visited,false,sizeof(visited));
        k.x=xs,k.y=ys,k.g=k.step=0,k.h=Heuristic(k),k.f=k.g+k.h;
        while(!priQueue.empty()) priQueue.pop();
        priQueue.push(k);
        Astar();
        printf("To get from %c%c to %c%c takes %d knight moves.\n",line[0],line[1],line[3],line[4],ans);
    }
    return 0;
}


//algorithm2: BFS，广度优先搜索，
//也可以是广度优先搜索，只需要把其中的队列改为堆栈就是深度优先搜索
//如果改为优先队列，那就是启发式搜索，类似Astar算法
int n,sx,sy,ex,ey;
int accessed[305][305];
int direction[8][2] = {-1,-2,-2,-1,-2,1,-1,2,1,-2,2,-1,2,1,1,2};
struct grid
{
    int x,y,step;
};

int check(int x,int y)
{
    if(x<0 || x>=n || y<0 || y>=n)
        return 1;
    return accessed[x][y];
}

void bfs()
{
    memset(accessed, 0, sizeof(accessed));
    grid current,next;
    queue<grid> Q;  //深度优先搜索
    current.x = sx;
    current.y = sy;
    current.step = 0;
    accessed[sx][sy] = 1;
    Q.push(current);
    while(!Q.empty())
    {
        current = Q.front();
        Q.pop();
        if(current.x == ex && current.y == ey)
        {
            printf("%d\n",current.step);
            return;
        }
        for(int i = 0;i<8;i++)
        {
            next = current;
            next.x = current.x+direction[i][0];
            next.y = current.y+direction[i][1];
            if(check(next.x,next.y))
                continue;
            next.step = current.step+1;
            accessed[next.x][next.y] = 1;
            Q.push(next);
        }
    }
}

int bfs_main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d%d%d",&n,&sx,&sy,&ex,&ey);
        bfs();
    }
    
    return 0;
}


//problem: 八数码问题，九宫格问题
//algorithm: 深度优先或者Astar/A*/A star.


//problem:环形打印出一个矩阵
//algorithm:画图来理清思路
void PrintMatrixInCircle(int** numbers, int columns, int rows, int start);
void printNumber(int number);

void PrintMatrixClockwisely(int** numbers, int columns, int rows)
{
    if(numbers == NULL || columns <= 0 || rows <= 0)
        return;
    
    int start = 0;
    
    while(columns > start * 2 && rows > start * 2)
    {
        PrintMatrixInCircle(numbers, columns, rows, start);
        
        ++start;
    }
}

void PrintMatrixInCircle(int** numbers, int columns, int rows, int start)
{
    int endX = columns - 1 - start;
    int endY = rows - 1 - start;
    
    // 从左到右打印第一行
    for(int i = start; i <= endX; ++i)
    {
        int number = numbers[start][i];
        printNumber(number);
    }
    
    // 从上到下打印一列
    if(start < endY)
    {
        for(int i = start + 1; i <= endY; ++i)
        {
            int number = numbers[i][endX];
            printNumber(number);
        }
    }
    
    // 从右到左打印一行
    if(start < endX && start < endY)
    {
        for(int i = endX - 1; i >= start; --i)
        {
            int number = numbers[endY][i];
            printNumber(number);
        }
    }
    
    // 从下到上打印一列
    if(start < endX && start < endY - 1)
    {
        for(int i = endY - 1; i >= start + 1; --i)
        {
            int number = numbers[i][start];
            printNumber(number);
        }
    }
}

void printNumber(int number)
{
    printf("%d\t", number);
}



//problem: 求一棵树的镜像
//algorithm: 变相考察树的遍历
void MirrorRecursively(BinaryTreeNode *pNode)
{
    if(pNode == NULL)
        return;
    
    BinaryTreeNode *pTemp = pNode->m_pLeft;
    pNode->m_pLeft = pNode->m_pRight;
    pNode->m_pRight = pTemp;
    
    if(pNode->m_pLeft)
        MirrorRecursively(pNode->m_pLeft);
    
    if(pNode->m_pRight)
        MirrorRecursively(pNode->m_pRight);
}

void MirrorIteratively(BinaryTreeNode* pRoot)
{
    if(pRoot == NULL)
        return;
    
    std::stack<BinaryTreeNode*> stackTreeNode;
    stackTreeNode.push(pRoot);
    
    while(stackTreeNode.size() > 0)
    {
        BinaryTreeNode *pNode = stackTreeNode.top();
        stackTreeNode.pop();
        
        BinaryTreeNode *pTemp = pNode->m_pLeft;
        pNode->m_pLeft = pNode->m_pRight;
        pNode->m_pRight = pTemp;
        
        if(pNode->m_pLeft)
            stackTreeNode.push(pNode->m_pLeft);
        
        if(pNode->m_pRight)
            stackTreeNode.push(pNode->m_pRight);
    }
}



//problem:树的子结构
//algorithm: 递归调用，考察树的遍历，注意边界条件
bool HasSubtreeCore(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2);
bool DoesTree1HaveTree2(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2);
bool HasSubtree(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
    bool result = false;
    
    if(pRoot1 != NULL && pRoot2 != NULL)                //一边遍历一边判断
    {
        if(pRoot1->m_nValue == pRoot2->m_nValue)
            result = DoesTree1HaveTree2(pRoot1, pRoot2); //这就相当于树遍历中的VISIT函数
        if(!result)
            result = HasSubtree(pRoot1->m_pLeft, pRoot2);
        if(!result)
            result = HasSubtree(pRoot1->m_pRight, pRoot2);
    }
    
    return result;
}

bool DoesTree1HaveTree2(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
    if(pRoot2 == NULL) //这三个递归的退出判断特别重要，前后顺序也很重要
        return true;
    
    if(pRoot1 == NULL)
        return false;
    
    if(pRoot1->m_nValue != pRoot2->m_nValue)
        return false;
    
    return DoesTree1HaveTree2(pRoot1->m_pLeft, pRoot2->m_pLeft) &&
    DoesTree1HaveTree2(pRoot1->m_pRight, pRoot2->m_pRight);
}


//problem: 定位到链表中倒数第k个节点
//algorithm:主要考虑鲁棒性，当头结点为空时、k为零时、k大于链表的长度时
node* FindKthToTail(node* pListHead, unsigned int k)
{
    if(pListHead == NULL || k == 0) // 如果k==0,那么由于k的类型是unsigned int则k-1将变成很大的正整数
        return NULL;
    
    node *pAhead = pListHead;
    node *pBehind = NULL;
    
    for(unsigned int i = 0; i < k - 1; ++ i)
    {
        if(pAhead->next != NULL)  //
            pAhead = pAhead->next;
        else
        {
            return NULL;
        }
    }
    
    pBehind = pListHead;
    while(pAhead->next != NULL)
    {
        pAhead = pAhead->next;
        pBehind = pBehind->next;
    }
    
    return pBehind;
}

//problem:
//algorithm:
int MinInOrder(int* numbers, int index1, int index2);

int Min(int* numbers, int length)
{
    if(numbers == NULL || length <= 0)
        return -1;
    
    int index1 = 0;
    int index2 = length - 1;
    int indexMid = index1; //初始化
    while(numbers[index1] >= numbers[index2])
    {
        // index1指向第一个递增数组最后一个元素
        // index2指向第二个递增数组最前一个元素
        if(index2 - index1 == 1)
        {
            indexMid = index2;
            break;
        }
        
        //如果下标index1\index2\indexmid指向的数字都相等时，只能用顺序查找的了
        indexMid = (index1 + index2) / 2;
        if(numbers[index1] == numbers[index2]
           && numbers[indexMid] == numbers[index1])
            return MinInOrder(numbers, index1, index2);
        
        // 缩小查找范围
        if(numbers[indexMid] >= numbers[index1])
            index1 = indexMid;
        else if(numbers[indexMid] <= numbers[index2])
            index2 = indexMid;
    }
    
    return numbers[indexMid];
}

int MinInOrder(int* numbers, int index1, int index2)
{
    int result = numbers[index1];
    for(int i = index1 + 1; i <= index2; ++i)
    {
        if(result > numbers[i])
            result = numbers[i];
    }
    
    return result;
}


//problem: 利用两个栈实现队列的功能
//algorithm: stack1用于入栈，stack2用于弹出，当stack2为空时，将stack1中的所有元素压入stack2中
template <typename T> class CQueue
{
public:
    CQueue(void);
    ~CQueue(void);
    
    void appendTail(const T& node);
    
    T deleteHead();
    
private:
    stack<T> stack1;
    stack<T> stack2;
};

template<typename T> void CQueue<T>::appendTail(const T& element)
{
    stack1.push(element);
}

template<typename T> T CQueue<T>::deleteHead()
{
    if(stack2.size()<= 0)
    {
        while(stack1.size()>0)
        {
            T& data = stack1.top();
            stack1.pop();
            stack2.push(data);
        }
    }
    
    if(stack2.size() == 0)
        return INT_MIN;
    
    T head = stack2.top();
    stack2.pop();
    
    return head;
}


//problem: 知道先序排列的数组和中序排列的数组，重构/重建原二叉搜索树rebuild
//algorithm: 递归
BinaryTreeNode* rebuild(int* startPreorder, int* endPreorder, int* startInorder, int* endInorder);

BinaryTreeNode* Construct(int* preorder, int* inorder, int length)
{
    if(preorder == NULL || inorder == NULL || length <= 0)
        return NULL;
    
    return rebuild(preorder, preorder + length - 1,
                         inorder, inorder + length - 1);
}

BinaryTreeNode* rebuild( int* startPreorder, int* endPreorder,
                               int* startInorder, int* endInorder)
{
    // 前序遍历的第一个节点是根节点的值
    int rootValue = startPreorder[0];
    BinaryTreeNode* root = (BinaryTreeNode*) malloc(sizeof(BinaryTreeNode));
    root->m_nValue = rootValue;
    root->m_pLeft = root->m_pRight = NULL;
    
    if(startPreorder == endPreorder)
    {
        if(startInorder == endInorder && *startPreorder == *startInorder)
            return root;
        else
            //throw std::exception("Invalid input.");这是微软的。。。
            return NULL;
    }
    
    // 在中序遍历中找到根节点的值
    int* rootInorder = startInorder;
    while(rootInorder <= endInorder && *rootInorder != rootValue)
        ++ rootInorder;
    
    if(rootInorder == endInorder && *rootInorder != rootValue)
        //throw std::exception("Invalid input.");
        return NULL;
    
    int leftLength = (int) (rootInorder - startInorder);
    int* leftPreorderEnd = startPreorder + leftLength;
    if(leftLength > 0)
    {
        // 构建左子树
        root->m_pLeft = rebuild(startPreorder + 1, leftPreorderEnd,
                                      startInorder, rootInorder - 1);
    }
    if(leftLength < endPreorder - startPreorder)
    {
        // 构建右子树
        root->m_pRight = rebuild(leftPreorderEnd + 1, endPreorder,
                                       rootInorder + 1, endInorder);
    }
    
    return root;
}

//编程之美上面的源代码
// 定义树的长度。为了后序调用实现的简单，我们直接用宏定义了树节点的总数
#define TREELEN 6
struct NODE
{
    NODE* pLeft;		// 左节点
    NODE* pRight;		// 右节点
    char chValue;		// 节点值
};

void ReBuild(char* pPreOrder,		//前序遍历结果
             char* pInOrder,			//中序遍历结果
             int nTreeLen,			//树长度
             NODE** pRoot)			//根节点
{
    
    //检查边界条件
    if(pPreOrder == NULL || pInOrder == NULL)
    {
        return;
    }
    
    // 获得前序遍历的第一个节点
    NODE* pTemp = new NODE;
    pTemp -> chValue = *pPreOrder;
    pTemp -> pLeft = NULL;
    pTemp -> pRight = NULL;
    
    // 如果节点为空，把当前节点复制到根节点
    if(*pRoot == NULL)
    {
        *pRoot = pTemp;
    }
    
    // 如果当前树长度为1，那么已经是最后一个节点
    if(nTreeLen == 1)
    {
        return;
    }
    
    // 寻找子树长度
    char* pOrgInOrder = pInOrder;
    char* pLeftEnd = pInOrder;
    int nTempLen = 0;
    
    // 找到左子树的结尾
    while(*pPreOrder != *pLeftEnd)
    {
        if(pPreOrder == NULL || pLeftEnd == NULL)
        {
            return;
        }
        
        nTempLen++;
        
        // 记录临时长度，以免溢出
        if(nTempLen > nTreeLen)
        {
            break;
        }
        
        pLeftEnd++;
    }
    
    // 寻找左子树长度
    int nLeftLen = 0;
    nLeftLen = (int)(pLeftEnd - pOrgInOrder);
    
    // 寻找右子树长度
    int nRightLen = 0;
    nRightLen = nTreeLen - nLeftLen - 1;
    
    // 重建左子树
    if(nLeftLen > 0)
    {
        ReBuild(pPreOrder + 1, pInOrder, nLeftLen, &((*pRoot) -> pLeft));
    }
    
    // 重建右子树
    if(nRightLen > 0)
    {
        ReBuild(pPreOrder + nLeftLen + 1, pInOrder + nLeftLen + 1,
                nRightLen, &((*pRoot) -> pRight)); 
    }
    
}

// 示例的调用代码
void rebuild_main(int argc, char* argv[])
{
    char szPreOrder[TREELEN]={'a', 'b', 'd', 'c', 'e', 'f'};
    char szInOrder[TREELEN]={'d', 'b', 'a', 'e', 'c', 'f'};
    
    NODE* pRoot = NULL;
    ReBuild(szPreOrder, szInOrder, TREELEN, &pRoot);
}


//problem:替换字符串中的空格为其他的字符
//algorithm:从后往前，依次移位，但是首先得确定最终替换后的字符的长度是多少
void ReplaceBlank(char string[], int length)///*length为字符串的最大值*/
{
    if(string == NULL && length <= 0)
        return;
    
    /*originalLength为字符串实际长度*/
    int originalLength = 0;
    int numberOfBlank = 0;
    int i = 0;
    while(string[i] != '\0')
    {
        ++ originalLength;
        
        if(string[i] == ' ')
            ++ numberOfBlank;
        
        ++ i;
    }
    
    /*newLength为空格被替换之后的新长度*/
    int newLength = originalLength + numberOfBlank * 2;
    if(newLength > length)
        return;
    
    int indexOfOriginal = originalLength - 1;
    int indexOfNew = newLength - 1;
    while(indexOfOriginal >= 0 && indexOfNew > indexOfOriginal)
    {
        if(string[indexOfOriginal] == ' ')
        {
            string[indexOfNew --] = '0';
            string[indexOfNew --] = '2';
            string[indexOfNew --] = '%';
        }
        else
        {
            string[indexOfNew --] = string[indexOfOriginal];
        }
        
        -- indexOfOriginal;
    }
}



//problem: 二维数组中查找特定的数值
//algorithm: 首先选举右上角的元素与target进行比较，如果大于target则该列被剔除
//如果小于target则该行被剔除，这样每一步都会缩小查找空间
//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
bool Find(int* matrix, int rows, int columns, int number)
{
    bool found = false;
    
    if(matrix != NULL && rows > 0 && columns > 0)
    {
        int row = 0;
        int column = columns - 1;
        while(row < rows && column >=0)
        {
            if(matrix[row * columns + column] == number)
            {
                found = true;
                break;
            }
            else if(matrix[row * columns + column] > number)
                -- column;
            else
                ++ row;
        }
    }
    
    return found;
}
/*测试用例
int matrix[][4] = 
    {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
    FIND((int*)matrix, 4, 4, 7);
 */

//problem: count the specific number of given array
//algorithm: recursion
int counttarget;
void countNum(int a[],int start,int finish, int target){
    int middle=(start+finish)/2;
    if(start>finish)
        return ;
    if(a[middle]==target){
        counttarget++;
        countNum(a,start,middle-1, target);
        countNum(a,middle+1,finish, target);
        //cout<<"get here"<<middle<<endl
    }else if(a[middle]>target){
        countNum(a,start,middle-1, target);
    }else
    {
        countNum(a,middle+1,finish, target);
    }
}

//algorithm2: 迭代法，参考STL中的equal_range的实现
//然后两个相减
int getUpper(int arr[], int size, int key){//获取某个元素最后出现位
    int low = 0, high = size - 1;
    //其实是一个递归迭代
    while(low < high){
        int mid = (low + high + 1) / 2;
        if(arr[mid] <= key)
            //当要查找的值比中位数大于等于时，把查找的低位限制为mid
            low = mid;
        else
            //当要找的值比 中位数小时，，把查找的高位限制为mid-1
            high = mid - 1;
    }
    //    返回最后出现位置
    return low;
}
int getLower(int arr[], int size, int key){//获取某个元素第一次出现位置
    int low = 0, high = size - 1;
    while(low < high){
        int mid = (low + high) / 2;
        //当要找的值比中位数小于等于时，，把查找的高位限制为mid+1
        if(arr[mid] >= key)
            high = mid;
        else
            //当要找的值比 中位数大时，，把查找的低位限制为mid+1
            low = mid + 1;
    }
    //返回第一次出现位置
    return low;
}

//problem: memmove
//algorithm: 注意memcpy和memmove的区别
void * mymemmove(void *destaddr, const void *sourceaddr, unsigned length)
{
    char *dest = (char*)destaddr;
    const char *source = (char*)sourceaddr;
    if (source < dest)
    /* Moving from low mem to hi mem; start at end.  */
        for (source += length, dest += length; length; --length)
            *--dest = *--source;
    else if (source != dest)
    /* Moving from hi mem to low mem; start at beginning.  */
        for (; length; --length)
            *dest++ = *source++;
                    
    return destaddr;
}
int my_atoi(const char * a) {
    
    if (*a == '+')
        return atoi(a+1);
    else if (*a=='-')
        return - atoi(a+1);
    
    const char *p = a;
    int c = 0;
    while (*p >= '0' && *p <= '9') {
        c = c*10 + (*p - '0'); }
    return c;
}

//problem: linkedlist sort
//algorithm: use merge sort to sort a linked list, with no extra space used

Node * merge2(Node * p1, Node * p2);
Node * mergeSort2(Node * p, int len);
int getLen(Node* head);

Node * linkedListMergeSort(Node * pHead) {
    int len = getLen(pHead);
    return mergeSort2(pHead, len);
}
int getLen(Node* head){
    int i = 0;
    while (head){
        head = head->next;
        i++;
    }
    return i;
}
Node * mergeSort2(Node * p, int len) {
    if (len == 1) { p->next = NULL; return p; }
    Node * pmid = p;
    for (int i=0; i<len/2; i++) {
        pmid = pmid->next; }
    Node * p1 = mergeSort2(p, len/2);
    Node * p2 = mergeSort2(pmid, len - len/2);
    return merge2(p1, p2);
}
//链表合并
Node *merge2(Node *head1,Node *head2)
{
    if(head1 == NULL) //鲁棒性测试必须先行
        return head2;
    if(head2 == NULL)
        return head1;
    
    Node *p1 = NULL;
    Node *p2 = NULL;
    Node *head = NULL;
    
    //找出两个链表中第一个结点较小的结点，head记录较小结点的头结点
    if(head1->data < head2->data){
        head = head1;
        p1 = head1->next;
        p2 = head2;
    }
    else{
        head = head2;
        p2 = head2->next;
        p1 = head1;
    }
    
    Node *pcur = head;
    
    //在两个链表中遍历比较，将值较小的结点链接到pcur结点后
    while(p1 != NULL && p2 != NULL){
        if(p1->data <= p2->data){
            pcur->next = p1;
            pcur = p1;
            p1 = p1->next;
        }
        else
        {
            pcur->next = p2;
            pcur = p2;
            p2 = p2->next;
        }
    }
    //将p1或p2剩余的结点链到pcur之后，完成整个合并的过程
    if(p1 != NULL)
        pcur->next = p1;
    if(p2 != NULL)
        pcur->next = p2;
    
    return head;
}


//再用递归实现链表的merge
Node * Merge3(Node *head1, Node *head2)
{
    if(head1 == NULL)
        return head2;
    if(head2 == NULL)
        return head1;
    Node *head = NULL;
    if(head1->data < head2->data)
    {
        head = head1;
        head->next = Merge3(head1->next, head2);
    }
    else
    {
        head = head2;
        head->next = Merge3(head1, head2->next);
    }
    return head;
}


//problem: lowest common ancestor
//algorithm:

//情况1：节点只有左指针、右指针，没有parent指针，root已知
BinaryTreeNode* findLowestCommonAncestor(BinaryTreeNode* root , BinaryTreeNode* a , BinaryTreeNode* b)
{
    if(root == NULL)
        return NULL;
    if(root == a || root == b)
        return root;
    
    BinaryTreeNode* left =
        findLowestCommonAncestor(root->m_pLeft , a , b);
    BinaryTreeNode* right =
        findLowestCommonAncestor(root->m_pRight , a , b);
    
    if(left && right)
        return root;
    return left ? left : right;
}
//情况2：节点有左指针、右指针、还有parent指针，可以知道两个点肯定有交点
//可以转化为求两条链相交的最近点
//这里再提供一个思路
/*
 给定两个单链表(head1, head2),检测两个链表是否有交点,如果有返回第一个交点。
 如果 head1==head2,那么显然相交,直接返回 head1。
 否则,分别从 head1,head2 开始遍历两个链表获得其长度 len1 与 len2,
 假设 len1>=len2,那么指针 p1 由 head1 开始向后移动 len1-len2 步,指针 p2=head2,
 下面 p1、p2 每次向后前进一步并比较 p1、p2 是否相等,如果相等即返回该结点,
 否则说明两个链表没有交点。
 */

//情况3： 二叉树是个二叉查找树，且root和两个节点的值(a, b)已知
BinaryTreeNode* findLowestCommonAncestor3(BinaryTreeNode* root , BinaryTreeNode* a , BinaryTreeNode* b)
{
    int min, max;
    if(a->m_nValue < b->m_nValue)
        min = a->m_nValue , max = b->m_nValue;
    else
        min = b->m_nValue , max = a->m_nValue;
    while(root)
    {
        if(root->m_nValue >= min && root->m_nValue <= max)
            return root;
        else if(root->m_nValue < min && root->m_nValue < max)
            root = root->m_pRight;
        else
            root = root->m_pLeft;
    }
    return NULL;
}



//problem: 把数组排成最小的数
//algorithm: 重新定义比较函数
/*
 字符串的比较函数需要重新定义，不是比较a和b，而是比较ab与 ba。如果ab < ba，则a < b；
 如果ab > ba，则a > b；如果ab = ba，则a = b。比较函数的定义是本解决方案的关键。
 为什么不能直接比较ab和ba的大小呢，因为把他们拼起来可能会超出int的表达范围，所以这是
 一个隐形的大数问题
 */
struct comparestr  //仿函数
{
    bool operator() (const string &src1, const string &src2)
    {
        string s1 = src1 + src2;
        string s2 = src2 + src1;
        return s1 < s2;   //升序排列，如果改为s1 > s2则为逆序排列
    }
};
//函数功能 ： 把数组排成最小的数
//函数参数 ： pArray为数组,num为数组元素个数
void ComArrayMin(int *pArray, int num){
    string *pStrArray = new string[num];
    for(int i=0; i<num; i++)
    {
        stringstream stream;
        stream<<pArray[i];
        stream>>pStrArray[i];
    }
    
    sort(pStrArray, pStrArray + num, comparestr()); //字符串数组排序

}
//剑指offer上的解答
const int g_MaxNumberLength = 10;

char* g_StrCombine1 = new char[g_MaxNumberLength * 2 + 1];
char* g_StrCombine2 = new char[g_MaxNumberLength * 2 + 1];

int compare(const void* strNumber1, const void* strNumber2);
void PrintMinNumber(int* numbers, int length)
{
    if(numbers == NULL || length <= 0)
        return;
    
    char** strNumbers = (char**)(new int[length]);
    for(int i = 0; i < length; ++i)
    {
        strNumbers[i] = new char[g_MaxNumberLength + 1];
        sprintf(strNumbers[i], "%d", numbers[i]);
    }
    
    qsort(strNumbers, length, sizeof(char*), compare);
    
    for(int i = 0; i < length; ++i)
        printf("%s", strNumbers[i]);
    printf("\n");
    
    for(int i = 0; i < length; ++i)
        delete[] strNumbers[i];
    delete[] strNumbers;
}
int compare(const void* strNumber1, const void* strNumber2)
{
    // [strNumber1][strNumber2]
    strcpy(g_StrCombine1, *(const char**)strNumber1);
    strcat(g_StrCombine1, *(const char**)strNumber2);
    
    // [strNumber2][strNumber1]
    strcpy(g_StrCombine2, *(const char**)strNumber2);
    strcat(g_StrCombine2, *(const char**)strNumber1);
    
    return strcmp(g_StrCombine1, g_StrCombine2);
}

//problem: 用递归法颠倒一个栈
//algorithm: recursion

// Add an element to the bottom of a stack:
template<typename T> void AddToStackBottom(stack<T>& stack, T t)
{
    if(stack.empty())
    {
        stack.push(t);
    }
    else
    {
        T top = stack.top();
        stack.pop();
        AddToStackBottom(stack, t);
        stack.push(top);
    }
}

// Reverse a stack recursively in three steps:
// 1. Pop the top element
// 2. Reverse the remaining stack
// 3. Add the top element to the bottom of the remaining stack
template<typename T> void ReverseStack(stack<T>& stack)
{
    if(!stack.empty())
    {
        T top = stack.top();
        stack.pop();
        ReverseStack(stack);
        AddToStackBottom(stack, top);
    }
}


//problem: split a interger
//algorithm: recursion递归调用
/*
 基本整数划分问题是将一个正整数n拆成一组数连加并等于n的形式，
 且这组数中的最大加数不大于m
 */
int integerSplit(int n, int m)
{
    if(n < 1 || m < 1) return 0;
    if(n == 1 || m == 1) return 1;
    if(n < m)
        return integerSplit(n, n);
    else if(n == m)
        return integerSplit(n, m - 1) + 1;
    else
        return integerSplit(n, m - 1) + integerSplit((n - m), m);
}
//problem: delete some specific chars in a string
//algorithm: hash + fast/slow pointers
void deleteChars(char* s, char* d){
    char * pTemp = d;
    char * pFast = s, *pSlow = s;
    int hashTable[256];
    memset(hashTable, 0, 256*sizeof(int));
    while ('\0' != *pTemp)
    {
        hashTable[*pTemp] = 1;
        pTemp++;
    }
    
    while ('\0' != *pFast)
    {
        if(!hashTable[*pFast])
        {
            *pSlow = *pFast;
            pSlow++;
        }
        ++pFast;
    }
    *pSlow = '\0';
    
}
//problem: 给定链表的头指针和一个结点指针，在O(1)时间删除该结点
//algorithm:
/*删除之前，我们需要需要把给定的结点的下一个结点的数据拷贝到给定的结点中。
 此时，时间复杂度为O(1)。如果删除的结点位于链表的尾部，没有下一个结点，仍然需要从链表
 的头结点开始，顺便遍历得到给定结点的前序结点，并完成删除操作。这个时候时间复杂度是O(n)。
 假设链表总共有n个结点，我们的算法在n-1总情况下时间复杂度是O(1)，
 只有当给定的结点处于链表末尾的时候，时间复杂度为O(n)。
 那么平均时间复杂度[(n-1)*O(1)+O(n)]/n，仍然为O(1)。
 */
//a->b->c->d..   //现在，给定了结点b，即要删除b
//a->c->d..
void DeleteNode(node* pListHead, node* pToBeDeleted)
{
    if(pToBeDeleted->next != NULL)   //要删除的结点b不是尾结点
    {
        //把b的下一个结点c先保存起来
        node* pNext = pToBeDeleted->next;   //pNext指着c
        
        pToBeDeleted->data = pNext->data;   //保存起来的c的值赋给b的值
        pToBeDeleted->next = pNext->next;   //d的值赋给c
        
        //最后，删除c。
        delete pNext;
        pNext = NULL;
    }
    else
    {
        //如果b是尾结点，找头结点，只能依次遍历 找b结点了
        node* pNode = pListHead;
        while(pNode->next != pToBeDeleted)
        {
            pNode = pNode->next;
        }
        //删除c。
        pNode->next = NULL;
        delete pToBeDeleted;
        pToBeDeleted = NULL;
    }
}


//problem:
/*
1. 看到这道题后，第一反应是从头到尾输出比较简单。于是很自然地想到把链表中链接结点的指针反转过来，改变链表的方向。然后就可以从头到尾输出了。反转链表的算法详见此微软100题系列第24题。
2.接下来的想法是从头到尾遍历链表，每经过一个结点的时候，把该结点放到一个栈中。当遍历完整个链表
 后，再从栈顶开始输出结点的值，此时输出的结点的顺序已经反转过来了。该方法需要维护一个额外的栈，
 现起来比较麻烦。
3. 既然想到了栈来实现这个函数，而递归本质上就是一个栈结构。于是很自然的又想到了用递归来实现。要实现反过来输出链表，我们每访问到一个结点的时候，先递归输出它后面的结点，再输出该结点自身，这样链表的输出结果就反过来了
 */
void PrintListReversingly_Iteratively(node* pHead){
    std::stack<node*> nodes; //直接把指针压入栈中，免得压数据费时费空间
    node* pNode = pHead;
    while(pNode != NULL)
    {
        nodes.push(pNode);
        pNode = pNode->next;
    }
    
    while(!nodes.empty())
    {
        pNode = nodes.top();
        printf("%d\t", pNode->data);
        nodes.pop();
    }
}
//其实当链表特别长时，应该采用栈，这样可以避免可能发生栈溢出
void PrintListReversingly(node* pListHead)
{
    if(pListHead != NULL){
        if (pListHead->next != NULL){
            PrintListReversingly(pListHead->next);
        }
        printf("%d", pListHead->data);
    }
}
//以上思路用来求字符串的长度
int getLen(char *str){
    if (*str == '\0')
        return 0;
    return getLen(str + 1) + 1;
}

//
//problem： 将数组中奇数都放在数组的前面，偶数都放在数组的后面
//algorithm: 类似于quicksort的partition，以下建立一个模板，可以把数组分成满足不同标准的函数指针
void evenOddPartition(int A[], int n) {
    if (n == 0 || n == 1)
        return;
    int i = 0, j = n - 1;
    while (i < j) {
        while ((i < j) && ((A[i] & 1) == 1)) //判断一个数字是不是偶数并没有用%运算符而是用&。理由是通常情况下位运算符比%要快一些；
                i++;
        while ((i < j) && ((A[j] & 1) == 0))
                j--;
        if (i < j)  //最好还是再加上一个判断
            swap(A[i], A[j]);
        i++;
        j--;
    }
}
//algorithm: 利用函数指针，提高扩展性，只要是把
void Reorder(int *pData, unsigned int length, bool (*func)(int));
bool isEven(int n);

void ReorderOddEven_2(int *pData, unsigned int length)
{
    Reorder(pData, length, isEven); //利用函数指针
}

void Reorder(int *pData, unsigned int length, bool (*func)(int))
{
    if(pData == NULL || length == 0)
        return;
    
    int *pBegin = pData;
    int *pEnd = pData + length - 1;
    
    while(pBegin < pEnd)
    {
        // 满足标准
        while(pBegin < pEnd && !func(*pBegin))
            pBegin ++;
        
        // 不满足标准
        while(pBegin < pEnd && func(*pEnd))
            pEnd --;
        
        if(pBegin < pEnd) //swap(*pBegin, *pEnd);加一层判断更保险
        {
            int temp = *pBegin;
            *pBegin = *pEnd;
            *pEnd = temp;
        }
    }
}

bool isEven(int n)
{
    return (n & 1) == 0;
}


//problem: find consecutive sequence whose sum equals to n
//algorithm: recursive，思想和2sum中前后指针的思想一致，都是若大于sum，则small变化（这里是small加，因为求得是small到big之间的连加），若小于sum，则big加
void PrintContinuousSequence(int small, int big);
// Find continuous sequence, whose sum is n
void FindContinuousSequence(int n)
{
    if(n < 3)
        return;
    
    int small = 1;
    int big = 2;
    int middle = (1 + n) / 2;
    int sum = small + big;
    while(small < middle)
    {
        // we are lucky and find the sequence
        if(sum == n)
            PrintContinuousSequence(small, big);
        // if the current sum is greater than n,
        // move small forward
        while(sum > n)
        {
            sum -= small;   //避免了重新计算之和，只需减掉小端值就可以了
            small ++;
            // we are lucky and find the sequence
            if(sum == n)
                PrintContinuousSequence(small, big);
        }
        // move big forward
        big ++;
        sum += big;   //只需加上大端值就可以了
    }
}
// Print continuous sequence between small and big
void PrintContinuousSequence(int small, int big)
{
    for(int i = small; i <= big; ++ i)
        printf("%d ", i);
    printf("/n");
}

//problem: use a trie to search for
//algorithm:

class TrieNode {
public:
    bool isWord;
    TrieNode* hash[26];
    char c;
    TrieNode(){}
    TrieNode(char c_) {
        c = c_;
        isWord = false;
        for (int i = 0; i < 26; i ++) {
            hash[i] = NULL;
        }
    }
};

class WordDictionary {
public:
    WordDictionary() {
        root = new TrieNode;
        for (int i = 0; i < 26; i ++) {
            root->hash[i] = NULL;
        }
    }

    
    // Adds a word into the data structure.
    void addWord(string word) {
        TrieNode* p = root;
        for (int i = 0; i < word.size(); i ++)
        {
            char tmp = word[i];
            if (p->hash[tmp-'a'] == NULL) {
                TrieNode* tnew = new TrieNode(tmp);
                p->hash[tmp-'a'] = tnew;
            }
            p = p->hash[tmp-'a'];
        }
        p->isWord = true;
    }
    
    // Returns if the word is in the data structure. A word could
    // contain the dot character '.' to represent any one letter.
    bool search(string word) {
        return search(word, 0, (int)word.size(), root);
    }
    
    bool search(string word, int pos, int n, TrieNode* cur) {
        if (cur == NULL)
            return false;
        if (pos == n)
            return cur->isWord;
        if (word[pos] == '.') {
            for (int i = 0; i < 26; i++) {
                if (cur->hash[i] && search(word, pos+1, n, cur->hash[i]))
                    return true;
            }
        }else {
            if (cur->hash[word[pos] - 'a'] && search(word, pos+1, n, cur->hash[word[pos] - 'a']))
                return true;
        }
        return false;
    }
    
private:
    TrieNode* root;
    
};

//problem: implement a trie
//algorithm:
/*
 这题实质是实现一颗多叉树（分支因子26）的插入和查找操作。定义每个TrieNode保存char c，保存一个HashMap用于储存所有的孩子节点，key是对应的字符，value是孩子节点，定义flag hasWord来标记这个node上是否存在word。对于插入操作，直接从上向下分层扫描树，如果没有对应字符节点存在就新建节点，如果有就去相应路径向下探察。对于查询操作，前缀树的定义可以保证当我们从前向后扫描字符串时候，每一个字符都可以从上到下对应前缀树的每一层，所以扫描过程中如果有任何一个字符不存在于当前层中，就可以立刻停止查找返回null，也就是不存在这样的word或者前缀，否则继续从对应的分支向下探察。时间复杂度是O（L），L是树的高度，也就是最长word的长度，空间复杂度26^L，每一层分支因子26，有L层
 */
class TrieNode2 {
public:
    TrieNode2 *next[26];
    bool isString;
    // Initialize your data structure here.
    TrieNode2() {
        for(int i = 0; i < 26; i++)
            next[i] = NULL;
        isString = false;
    }
};

class Trie {
public:
    Trie() {
        root = new TrieNode2();
        
    }
    
    // Inserts a word into the trie.
    void insert(string s) {
        TrieNode2 *p = root;
        for(int i = 0; i < s.size(); i++){
            if(p->next[s[i]-'a'] == NULL){
                p->next[s[i]-'a'] = new TrieNode2();
            }
            p = p->next[s[i]-'a'];
        }
        p->isString = true;
    }
    
    // Returns if the word is in the trie.
    bool search(string key) {
        TrieNode2 *p = root;
        for(int i = 0; i < key.size(); i++){
            if(p == NULL) return false;
            p = p->next[key[i]-'a'];
        }
        if(p == NULL || p->isString == false) return false;
        return true;
        
    }
    
    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode2 *p = root;
        for(int i = 0; i <= prefix.size(); i++){
            if(p == NULL) return false;
            p = p->next[prefix[i]-'a'];
        }
        return true;
    }
    
private:
    TrieNode2* root;
};

// Your Trie object will be instantiated and called as such:
// Trie trie = new Trie();
// trie.insert("somestring");
// trie.search("key");


//问题：在从1到n的正数中1出现的次数，编程之美
//题目：输入一个整数n，求从1到n这n个整数的十进制表示中1出现的次数。
//算法：
//最简单的，每次判断整数的个位数字是不是1。如果这个数字大于10，除以10之后再判断个位数字是不是1
int num1s(int n)
{
    int count = 0;//统计变量
    int factor = 1;//分解因子
    int lower = 0;//当前处理位的所有低位
    int higher = 0;//当前处理位的所有高位
    int curr =0;//当前处理位
    
    while(n/factor != 0)
    {
        lower = n - n/factor*factor;//求得低位
        curr = (n/factor)%10;//求当前位
        higher = n/(factor*10);//求高位
        
        switch(curr)
        {
            case 0:
                count += higher * factor;
                break;
            case 1:
                count += higher * factor + lower + 1;
                break;
            default:
                count += (higher+1)*factor;
        }
        
        factor *= 10;
    }
    
    return count;
}


//问题：栈混洗
//算法：利用辅助栈，将效率降低到O(n)
bool IsPossiblePopOrder(const int* pPush, const int* pPop, int nLength)
{
    bool bPossible = false;
    
    if(!pPush || !pPop || nLength <= 0)
        return bPossible;
    
    const int *pNextPush = pPush;
    const int *pNextPop = pPop;
    
    // ancillary stack
    std::stack<int> stackData;
    
    // check every integers in pPop
    while(pNextPop - pPop < nLength)
    {
        while(stackData.empty() || stackData.top() != *pNextPop){

            if (pNextPush - pPush == nLength)
                break;
            stackData.push(*pNextPush);
            pNextPush ++;

        }
        
        if(stackData.top() != *pNextPop)
            break;
        
        // Check the next integer in pPop
        stackData.pop();
        pNextPop ++;
    }
    
    if(stackData.empty() && pNextPop - pPop == nLength)
        bPossible = true;
    
    return bPossible;
}
//这是用数组的形式来处理的，以上使用指针，本质上没有区别
bool isPopSeries(int push[], int pop[], int n) {
    bool bPossible = false;
    stack<int> helper;
    int i1 = 0, i2 = 0;
    while (i2 < n) {
        while (helper.empty() || helper.top() != pop[i2]) {
            if (i1 < n)
                helper.push(push[i1++]);
            else
                break;
            
            if (!helper.empty() && helper.top() == pop[i2]) {
                helper.pop(); i2++; }
        }
    }
    if (helper.empty() && i2 == n)
        bPossible = true;
    return bPossible;
}
//算法2：利用栈混洗的充要条件，算法复杂度是O(n^2)
/*
 充要条件(Knuth):
 A permutation is a stack permutation iff 
 it does NOT involve the permutation 312:
 对于任意i < j,不含模式{ ..., j+1, ..., i, ..., j, ...}
 */


//问题：其实也叫hanmming_weight
/*
题目：输入一个整数，求该整数的二进制表达中有多少个1。
例如输入10，由于其二进制表示为1010，有两个1，因此输出2。
一个很基本的想法是，我们先判断整数的最右边一位是不是1。
接着把整数右移一位，原来处于右边第二位的数字现在被移到第一位了，
再判断是不是1。这样每次移动一位，直到这个整数变成0为止。
现在的问题变成怎样判断一个整数的最右边一位是不是1了。
很简单，如果它和整数1作与运算。由于1除了最右边一位以外，其他所有位都为0。
因此如果与运算的结果为1，表示整数的最右边一位是1，否则是0。得到的代码如下：
*/
//算法：
///////////////////////////////////////////////////////////////////////
// Get how many 1s in an integer's binary expression
///////////////////////////////////////////////////////////////////////
int NumberOf1_Solution1(int i)
{
    int count = 0;
    while(i)
    {
        if(i & 1)
            count ++;
        
        i = i >> 1;
    }
    
    return count;
}

//算法2：解决以上算法的bug
/*
这个思路当输入i是正数时没有问题，但当输入的i是一个负数时，
不但不能得到正确的1的个数，还将导致死循环。
以负数0x80000000为例，右移一位的时候，并不是简单地把最高位的1移到第二位变成0x40000000，
而是0xC0000000。这是因为移位前是个负数，仍然要保证移位后是个负数，因此移位后的最高位会设为1。
如果一直做右移运算，最终这个数字就会变成0xFFFFFFFF而陷入死循环。
为了避免死循环，我们可以不右移输入的数字i。
首先i和1做与运算，判断i的最低位是不是为1。
接着把1左移一位得到2，再和i做与运算，就能判断i的次高位是不是1……
这样反复左移，每次都能判断i的其中一位是不是1。基于此，我们得到如下代码：
*/
int NumberOf1_Solution2(int i){
    int count = 0;
    unsigned int flag = 1;
    while(flag){
        if(i & flag)
            count ++;
        
        flag = flag << 1;
    }
    
    return count;
}
//算法3：把一个整数减去1再与原来的整数做位与运算得到的是把整数的二进制表示中最右边一个1变成0
 int NumberOf1_Solution3(int i){
     int count = 0;
     while (i){
         ++ count;
         i = (i - 1) & i;
     }
     return count;
 }
//扩展：如何用一个语句判断一个整数是不是二的整数次幂？
//PS：n&(n-1)==0;//二进制数只有一位位1，则该数是2的整数次幂.
//扩展2：判断两个整数，计算改变m的二进制表示中多少为才能得到n

inline int changeNbits(int m, int n) {
    return NumberOf1_Solution3(m ^ n);
}

//算法4：wikipedia
int NumberOf1_Solution_Wikipedia(int n) //分治法
{
    n = (n&0x55555555) + ((n>>1)&0x55555555);
    n = (n&0x33333333) + ((n>>2)&0x33333333);
    n = (n&0x0f0f0f0f) + ((n>>4)&0x0f0f0f0f);
    n = (n&0x00ff00ff) + ((n>>8)&0x00ff00ff);
    n = (n&0x0000ffff) + ((n>>16)&0x0000ffff);
    return n;
}


//问题：
/*
写一个函数,它的原形是int continumax(char *outputstr,char *intputstr)
功能：
在字符串中找出连续最长的数字串，并把这个串的长度返回，
并把这个最长数字串付给其中一个函数参数outputstr所指内存。
例如："abcd12345ed125ss123456789"的首地址传给intputstr后，函数将返回9，
outputstr所指的值为123456789
*/
//leeyunce
//算法：跟在序列中求最小值差不多
int continumax(char *outputstr, char *intputstr)
{
    int i, maxlen = 0;
    char * maxstr = 0;
    
    while (true)
    {
        while (intputstr && (*intputstr<'0' || *intputstr>'9'))
            //skip all non-digit characters
        {
            intputstr++;
        }
        
        if (!intputstr) break;
        
        int count = 0;
        char * tempstr = intputstr;
        while (intputstr && (*intputstr >= '0' && *intputstr <= '9'))
            //OK, these characters are digits
        {
            count++;
            intputstr++;
        }
        
        if (count > maxlen)
        {
            maxlen = count;
            maxstr = tempstr;
        }
    }
    
    for (i=0; i<maxlen; i++)
    {
        outputstr[i] = maxstr[i];
    }
    
    outputstr[i] = '\0';
    
    return maxlen;
}


//问题：剑指offer，不用加减乘除做加法
//算法：用位计算
int Add(int num1, int num2)
{
    int sum, carry;
    do
    {
        sum = num1 ^ num2;          //这是不考虑进位情况下的结果
        carry = (num1 & num2) << 1; //向左移动一位表明了进位的性质
        
        num1 = sum;
        num2 = carry;
    }
    while(num2 != 0);
    
    return num1;
}


//问题：输入两个整数 m 和 n，从数列1，2，3.......n 中 随意取几个数,
//使其和等于 m ,要求将其中所有的可能组合列出来
//算法：0/1背包问题的思路
list<int> list1;//需要维护一个全局的链表，不能用栈，因为这里需要遍历其元素
void find_factor(int sum, int n)
{
    // 递归出口
    if(n <= 0 || sum <= 0)
        return;
    
    // 输出找到的结果
    if(sum == n)
    {
        // 反转list
        list1.reverse();
        for(list<int>::iterator iter = list1.begin(); iter != list1.end(); iter++)
            cout << *iter << " + ";
        cout << n << endl;
        list1.reverse();
    }
    
    list1.push_front(n);      //典型的01背包问题
    find_factor(sum-n, n-1);   //放n，n-1个数填满sum-n
    list1.pop_front();
    find_factor(sum, n-1);     //不放n，n-1个数填满sum
}


//问题：将整数n转换为字符串并保存到s中
//算法：itoa
void itoa(int n, char s[]) {
    int i, sign;
    if ( (sign = n) < 0)
        n = -n; //这里可能会出现bug,不能处理最大的负数
    i = 0;
    do {
        s[i++] = n%10 + '0';
    }while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s, s+strlen(s));
}
void itoa2(int n, char s[]) {
    int i, sign;
    sign = n; //此处
    i = 0;
    do {
        s[i++] = abs ( n % 10 )+ '0'; //此处
    }while ((n /= 10) != 0); //此处
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s, s+strlen(s));
}
//算法2：处理以上算法的bug，不能处理最大的负数

//问题：将字符串转换为整数保存在s中，这种方法可以用来处理大整数，将大整数存储在字符串中
//算法：atoi，标准库里面的函数，一般用于将函数的参数（字符串）转换为整数
int  myatoi(char s[]) {
    int num = (int) strlen(s);
    if (num == 0) return 0;
    int sign = 1;
    int i, sum = 0;
    if (s[0] == '-') {
        sign = -1;
        i++;
    }else if (s[0] == '+')
        i++;
    
    for (; i < num; i++) {
        if (!isdigit(s[i])) {
            printf("Invalid numbers");
            exit(-1);
        }
        sum = sum * 10 + (s[i] - '0');
        // overflow
        if(sum > std::numeric_limits<int>::max())
        {
            sum = 0;
            return 0;
        }
    }
    return sum * sign;
}
//July、2010、10/22。
enum Status {kValid = 0, kInvalid};
int g_nStatus = kValid;
int StrToInt(const char* str)
{
    g_nStatus = kInvalid;
    long long num = 0;
    
    if(str != NULL)
    {
        const char* digit = str;
        
        // the first char in the string maybe '+' or '-'
        bool minus = false;
        if(*digit == '+')
            digit ++;
        else if(*digit == '-')
        {
            digit ++;
            minus = true;
        }
        
        // the remaining chars in the string
        while (*digit != '\0')
        {
            if (isdigit(*digit))
            {
                num = num * 10 + (*digit - '0');
                
                // overflow
                if(num > std::numeric_limits<int>::max())
                {
                    num = 0;
                    break;
                }
                
                digit ++;
            }
            // if the char is not a digit, invalid input
            else
            {
                num = 0;
                break;
            }
        }
        
        if(*digit == '\0')
        {
            g_nStatus = kValid;
            if(minus)
                num = 0 - num;
        }
    }
    return static_cast<int>(num);
}

//问题：快速计算裴波那契数列
//算法：这个可以用来实现fibollic数列的logn算法，并且利用quickPower的思想
void multiply(int A[], int B[], int* _r);
void powerMatrix(int A[], int n, int* _r);
int f(int n) {
    int A[4] = {1,1,1,0};
    int result[4];
    powerMatrix(A, n, result);
    return result[0];
}

void multiply(int A[], int B[], int* _r) {
    _r[0] = A[0]*B[0] + A[1]*B[2];
    _r[1] = A[0]*B[1] + A[1]*B[3];
    _r[2] = A[2]*B[0] + A[3]*B[2];
    _r[3] = A[2]*B[1] + A[3]*B[3];
}

void powerMatrix(int A[], int n, int* _r) {
    if (n==1) { memcpy(A, _r, 4*sizeof(int)); return; }
    int tmp[4];
    powerMatrix(A, n>>1, _r);
    multiply(_r, _r, tmp);
    if ((n & 1) == 1) {
        multiply(tmp, A, _r);
    } else {
        memcpy(_r, tmp, 4*sizeof(int));
    }
}

//问题：n个人围成一圈，顺序排号。从第一个人开始报数（从1到3报数），
//凡报到3的人退出圈子，问最后留下的是原来第几号的那个人?
//算法：
int LastRemaining_Solution2(int n, unsigned int m)
{
    // invalid input
    if(n <= 0 || m < 0)
        return -1;
    
    // if there are only one integer in the circle initially,
    // of course the last remaining one is 0
    int lastinteger = 0;
    
    // find the last remaining one in the circle with n integers
    for (int i = 2; i <= n; i ++)
        lastinteger = (lastinteger + m) % i;
    
    return lastinteger;
}
//问题：题目：在一个字符串中找到第一个只出现一次的字符。
//如输入abaccdeff，则输出b。
//算法：hash函数
char firstSingleLetter(char* s) { //其实就是hash的思想
    int f[26] = {0};    //如果在原始字符串中还有其他的字符，得用ASCII码作为hash键值的表
    for (int i = 0; i < strlen(s); i ++)
        f[s[i] - 'a']++;
    for (int i = 0; i < strlen(s); i++) {
        int index = s[i] - 'a';
        if (f[index] == 1 )
            return s[i];
    }
    return ' ';
}
//algorithm: 利用bitset
bool CompareString(string long_str, string short_str)   //字符串包含
{
    bitset<26> flag;    //利用bitset类
    for(int i=0; i<long_str.size(); ++i)
    {
        // flag.set(n)置第n位为1
        flag.set(long_str[i]-'A');
    }
    for(int i=0; i<short_str.size(); ++i)
    {
        // flag.test(n)判断第n位是否为1
        if(!flag.test(short_str[i]-'A'))
            return false;
    }
    return true;
}

//算法2：hash映射，使用ASCII键值
char FirstNotRepeatingChar(char* pString)
{
    if(!pString)
        return 0;
    
    const int tableSize = 256;
    unsigned int hashTable[tableSize];
    memset(hashTable, 0, sizeof(hashTable));
    //for(unsigned int i = 0; i < tableSize; ++ i)
    //    hashTable[i] = 0;
    
    char* pHashKey = pString;
    while(*(pHashKey) != '\0')
        hashTable[*(pHashKey++)] ++;
    
    pHashKey = pString;
    while(*pHashKey != '\0')
    {
        if(hashTable[*pHashKey] == 1)
            return *pHashKey;
        
        pHashKey++;
    }
    
    return *pHashKey;
}

//problem: 变位词的判断
//algorithm: 先对字符串排序，然后判断两个字符串是否相等
// 自定义序函数（二元谓词）
bool charCompare(char i, char j)
{
    return i > j;
}
bool wordsReorder(string s1, string s2)
{
    // 采用泛型算法对s1,s2排序，sort()采用的是快速排序算法
    sort(s1.begin(), s1.end(), charCompare);
    sort(s2.begin(), s2.end(), charCompare);
    if(!s1.compare(s2)) // 相等返回0
        return true;
    else
        return false;
}
//problem: 找出特定单词的所有变位词的集合
//algorithm: 先得到每个单词的标示（也就是其排序之后的字符串），然后按照标示进行排序
/*
 *  map是C++中的关联容器，map会自动排序，unordered_map不会自动排序，根据不同的需求选择
 *   按关键字有序
 *   关键字不可重复
 */
map<string, string> word;

/* 自定义比较函数（用于排序） */
bool myfunction(char i, char j)
{
    return i < j;
}

/*
 *对每个单词排序
 *排序后字符串作为关键字，原单词作为值
 *存入map中
 */
void sign_sort(const char* dic)
{
    // 文件流
    ifstream in(dic);
    if(!in)
    {
        cout << "Couldn't open file: " + string(dic) << endl;
        return;
    }
    
    string aword;
    string asign;
    while(in >> aword)
    {
        asign = aword;
        sort(asign.begin(), asign.end(), myfunction);
        // 若标识不存在，创建一个新map元素，若存在，加在值后面
        word[asign] += aword + " ";
    } 
    in.close(); 
}

void wordsExchange(vector<string> &vWords, map<string, string> &mWords) {
    int n = (int) vWords.size();
    for (int i = 0; i < n ; i++) {
        string value = vWords[i];
        string key = value;             //key保存的是变位词，value是原始的单词
        sort(key.begin(), key.end(), charCompare);
        mWords[key] += value + ' ';
    }
}

//问题：二叉树的层次遍历算法
//算法：利用队列进行迭代
void BinaryTreeLevelTraverse(BinaryTreeNode* root) {
    if (!root)  return;
    queue<BinaryTreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        BinaryTreeNode* pFront = q.front();
        printf("%d", pFront->m_nValue);
        q.pop();
        if (!root->m_pLeft)
            q.push(root->m_pLeft);
        if (!root->m_pRight)
            q.push(root->m_pRight);
    }
}
//也可以用deque
struct BTreeNode // a node in the binary tree
{
    int         m_nValue; // value of node
    BTreeNode  *m_pLeft;  // left child of node
    BTreeNode  *m_pRight; // right child of node
};
void PrintFromTopToBottom(BTreeNode *pTreeRoot)
{
    if(!pTreeRoot)
        return;
    
    // get a empty queue
    deque<BTreeNode *> dequeTreeNode;
    
    // insert the root at the tail of queue
    dequeTreeNode.push_back(pTreeRoot);
    
    while(!dequeTreeNode.empty())
    {
        // get a node from the head of queue
        BTreeNode *pNode = dequeTreeNode.front();
        dequeTreeNode.pop_front();
        
        // print the node
        cout << pNode->m_nValue << ' ';
        
        // print its left child sub-tree if it has
        if(pNode->m_pLeft)
            dequeTreeNode.push_back(pNode->m_pLeft);
        // print its right child sub-tree if it has
        if(pNode->m_pRight)
            dequeTreeNode.push_back(pNode->m_pRight);
    }
}
//也可以用数组
void PrintNodeByLevel(BTreeNode* root)
{
    if(root == NULL)
        return;
    vector<BTreeNode*> vec;		//这里我们使用STL 中的vector来代替数组，可利用
    //到其动态扩展的属性
    vec.push_back(root);
    int cur = 0;
    int last = 1;
    while(cur < vec.size())
    {
        last = (int)vec.size();		//新的一行访问开始，重新定位last于当前行最后
								//一个节点的下一个位置
        while(cur < last)
        {
            cout << vec[cur] -> m_nValue << " ";		//访问节点
            if(!vec[cur] -> m_pLeft)		//当前访问节点的左节点不为空则压入
                vec.push_back(vec[cur] -> m_pLeft);
            if(!vec[cur] -> m_pRight)		//当前访问节点的右节点不为空则压入，
                //注意左右节点的访问顺序不能颠倒
                vec.push_back(vec[cur] -> m_pRight);
            cur++;
        }
        cout << endl;		//当cur == last,说明该层访问结束，输出换行符
    }
}


//算法2：
/*我们知道树是图的一种特殊退化形式。
同时如果对图的深度优先遍历和广度优先遍历有比较深刻的理解，

将不难看出这种遍历方式实际上是一种广度优先遍历。
因此这道题的本质是在二元树上实现广度优先遍历。
*/

//问题：reverse a tree，构成他的镜像mirror，左右对称
//算法：分治递归
void Reversetree(BinaryTreeNode *root)
{
    if(!root)
        return;
    BinaryTreeNode *p;
    
    p = root->m_pLeft;
    root->m_pLeft = root->m_pRight;
    root->m_pRight = p;
    
    if(root->m_pLeft)
        Reversetree(root->m_pLeft);
    if(root->m_pRight)
        Reversetree(root->m_pRight);
}
//算法2：递归改迭代，利用一个栈
/*
由于递归的本质是编译器生成了一个函数调用的栈，
因此用循环来完成同样任务时最简单的办法就是用一个辅助栈来模拟递归。
首先我们把树的头结点放入栈中。
在循环中，只要栈不为空，弹出栈的栈顶结点，交换它的左右子树。
如果它有左子树，把它的左子树压入栈中；
如果它有右子树，把它的右子树压入栈中。
这样在下次循环中就能交换它儿子结点的左右子树了。
*/


//problem: 二叉搜索树的后序遍历验证
//algorithm: 递归调用
bool VerifySquenceOfBST(int sequence[], int length)
{
    if(sequence == NULL || length <= 0)
        return false;
    
    int root = sequence[length - 1];
    
    // 在二叉搜索树中，左子树节点小于根节点
    int i = 0;
    for(; i < length - 1; ++ i)
    {
        if(sequence[i] > root)  //找到partition的点
            break;
    }
    
    // 右子树节点大于根节点
    int j = i;
    for(; j < length - 1; ++ j)
    {
        if(sequence[j] < root)
            return false;
    }
    
    // 判断左子树是不是二叉树
    bool left = true;
    if(i > 0)
        left = VerifySquenceOfBST(sequence, i);
    
    // 判断右子树是不是二叉树
    bool right = true;
    if(i < length - 1)
        right = VerifySquenceOfBST(sequence + i, length - i - 1);
    
    return (left && right);
}


struct ListNode__ {
    int m_value;
    ListNode__* leftch;
    ListNode__* rightch;
};
void Reversetree2(ListNode__ *phead)
{
    if(!phead)
        return;
    
    stack<ListNode__*> stacklist;
    stacklist.push(phead);         //首先把树的头结点放入栈中。
    
    while(stacklist.size())
        //在循环中，只要栈不为空，弹出栈的栈顶结点，交换它的左右子树
    {
        ListNode__* pnode=stacklist.top();
        stacklist.pop();
        
        ListNode__* ptemp;
        ptemp = pnode->leftch;
        pnode->leftch = pnode->rightch;
        pnode->rightch = ptemp;
        
        if(pnode->leftch)
            stacklist.push(pnode->leftch);   //若有左子树，把它的左子树压入栈中
        if(pnode->rightch)
            stacklist.push(pnode->rightch);  //若有右子树，把它的右子树压入栈中
    }
}


//问题：已经排好序，求和为固定值的两个数字
//算法：两边往中间扫描
bool findTwoNumbers(int data[], unsigned int length, int sum, int& num1, int& num2) {
    bool found = false;
    if (length < 1) return found;
    int i = 0, j = length-1;
    while (i < j) {
        int curSum = data[i] + data[j];
        if (curSum == sum) {
            num1 = data[i];
            num2 = data[j];
            found = true;
            break;
        }else if (curSum > sum)
            j--;
        else
            i++;
    }
    return found;
}

//问题：单项链表，倒数第k个节点
//算法：注意对错误输入的处理
node* listSearch(node* head, int k) {
    int i = 0;
    node* p = head, *q = head;
    while (!p && i < k) {
        p = p->next;
        i++;
    }
    if (i < k) return NULL;
    while (!p) {
        q = q->next;
        p = p->next;
    }
    return q;
    
}

//问题：求二叉树中节点的最大距离...
//算法：dynanmic programming
// 数据结构定义
struct NODE_
{
    NODE_* pLeft;            // 左子树
    NODE_* pRight;          // 右子树
    int nMaxLeft;          // 左子树中的最长距离
    int nMaxRight;         // 右子树中的最长距离
    char chValue;        // 该节点的值
};
int nMaxLen;
// 寻找树中最长的两段距离
void FindMaxLen(NODE_* pRoot)
{
    // 遍历到叶子节点，返回
    if(pRoot == NULL){
        return;
    }
    
    // 如果左子树为空，那么该节点的左边最长距离为0
    if(pRoot -> pLeft == NULL){
        pRoot -> nMaxLeft = 0;
    }
    
    // 如果右子树为空，那么该节点的右边最长距离为0
    if(pRoot -> pRight == NULL){
        pRoot -> nMaxRight = 0;
    }
    
    // 如果左子树不为空，递归寻找左子树最长距离
    if(pRoot -> pLeft != NULL){
        FindMaxLen(pRoot -> pLeft);
    }
    
    // 如果右子树不为空，递归寻找右子树最长距离
    if(pRoot -> pRight != NULL){
        FindMaxLen(pRoot -> pRight);
    }
    
    // 计算左子树最长节点距离
    if(pRoot -> pLeft != NULL){
        int nTempMax = 0;
        if(pRoot -> pLeft -> nMaxLeft > pRoot -> pLeft -> nMaxRight){
            nTempMax = pRoot -> pLeft -> nMaxLeft;
        }
        else{
            nTempMax = pRoot -> pLeft -> nMaxRight;
        }
        pRoot -> nMaxLeft = nTempMax + 1;
    }
    
    // 计算右子树最长节点距离
    if(pRoot -> pRight != NULL){
        int nTempMax = 0;
        if(pRoot -> pRight -> nMaxLeft > pRoot -> pRight -> nMaxRight){
            nTempMax = pRoot -> pRight -> nMaxLeft;
        }
        else{
            nTempMax = pRoot -> pRight -> nMaxRight;
        }
        pRoot -> nMaxRight = nTempMax + 1;
    }
    
    // 更新最长距离
    if(pRoot -> nMaxLeft + pRoot -> nMaxRight > nMaxLen){
        nMaxLen = pRoot -> nMaxLeft + pRoot -> nMaxRight;
    }
}//很明显，思路完全一样，但书上给的这段代码更规范

//algorithm2: use divide-conquer.
/*
 * return the depth of the tree
 */
struct Tree {
    Tree* left;
    Tree* right;
};
int get_depth(Tree *tree) {
    int depth = 0;
    if ( tree ) {
        int a = get_depth(tree->left);
        int b = get_depth(tree->right);
        depth = ( a > b ) ? a : b;
        depth++;
    }
    return depth;
}
//简介版
int TreeDepth(BinaryTreeNode* pRoot)
{
    if(pRoot == NULL)
        return 0;
    
    int nLeft = TreeDepth(pRoot->m_pLeft);
    int nRight = TreeDepth(pRoot->m_pRight);
    
    return (nLeft > nRight) ? (nLeft + 1) : (nRight + 1);
}

/*
 * return the max distance of the tree
 */
int get_max_distance(Tree *tree) {
    int distance = 0;
    if ( tree ) {
        // get the max distance connected to the current node
        distance = get_depth(tree->left) + get_depth(tree->right);
        
        // compare the value with it's sub trees
        int l_distance = get_max_distance(tree->left);
        int r_distance = get_max_distance(tree->right);
        distance = ( l_distance > distance ) ? l_distance : distance;
        distance = ( r_distance > distance ) ? r_distance : distance;
    }
    return distance;
}

//problem: 判断一个二叉树是不是平衡二叉树
//algorithm: 后序遍历
//该算法的缺点是：每一个节点都遍历了多次
int TreeDepth_(BinaryTreeNode* pRoot)
{
    if(pRoot == NULL)
        return 0;
    
    int nLeft = TreeDepth_(pRoot->m_pLeft);
    int nRight = TreeDepth_(pRoot->m_pRight);
    
    return (nLeft > nRight) ? (nLeft + 1) : (nRight + 1);
}

bool IsBalanced_Solution1(BinaryTreeNode* pRoot)
{
    if(pRoot == NULL)
        return true;
    
    int left = TreeDepth_(pRoot->m_pLeft); //会多次计算同一个节点的深度
    int right = TreeDepth_(pRoot->m_pRight);
    int diff = left - right;
    if(diff > 1 || diff < -1)
        return false;
    
    return IsBalanced_Solution1(pRoot->m_pLeft)
    && IsBalanced_Solution1(pRoot->m_pRight);
}

//algorithm2: 上述方法虽然简单，但是遍历了多次节点，可以考虑后序遍历，每一个节点
//用一个变量记录树的高度，然后该节点是否满足平衡二叉树的节点条件
bool IsBalanced(BinaryTreeNode* pRoot, int* pDepth);

bool IsBalanced_Solution2(BinaryTreeNode* pRoot)
{
    int depth = 0;
    return IsBalanced(pRoot, &depth);
}

bool IsBalanced(BinaryTreeNode* pRoot, int* pDepth)
{
    if(pRoot == NULL)
    {
        *pDepth = 0;
        return true;
    }
    
    int left, right;
    if(IsBalanced(pRoot->m_pLeft, &left)
       && IsBalanced(pRoot->m_pRight, &right))
    {
        int diff = left - right;
        if(diff <= 1 && diff >= -1)
        {
            *pDepth = 1 + (left > right ? left : right);
            return true;
        }
    }
    
    return false;
}



//问题：判断整数序列是不是二叉查找树的后序遍历结果
//算法：其实就是二叉查找树后序遍历的基本算法
bool verifySquenceOfBST(int squence[], int length)
{
    if(squence == NULL || length <= 0)
        return false;
    
    // root of a BST is at the end of post order traversal squence
    int root = squence[length - 1];
    
    // the nodes in left sub-tree are less than the root
    int i = 0;
    for(; i < length - 1; ++ i)
    {
        if(squence[i] > root)
            break;
    }
    
    // the nodes in the right sub-tree are greater than the root
    int j = i;
    for(; j < length - 1; ++ j)
    {
        if(squence[j] < root)
            return false;
    }
    
    // verify whether the left sub-tree is a BST
    bool left = true;
    if(i > 0)
        left = verifySquenceOfBST(squence, i);
    
    // verify whether the right sub-tree is a BST
    bool right = true;
    if(i < length - 1)
        right = verifySquenceOfBST(squence + i, length - i - 1);
    
    return (left && right);
}


//问题：reverse a list
//算法：使用三个额外指针，可以改用两个额外指针
node *reverseList(node *head)
{
    if (head == NULL)
        return NULL;
    node *p,*q,*r;
    p = head;
    q = p->next;
    while(q != NULL)
    {
        r = q->next;
        q->next = p;
        p = q;
        q = r;
    }
    head->next = NULL;
    head = p;
    return head;
}
node *reverseList2(node *head)
{
    if (head == NULL)
        return NULL;
    node *q,*r;
    q = head->next;
    head->next = NULL;
    
    while(q != NULL)
    {
        r = q->next;
        q->next = head;
        head = q;
        q = r;
    }

    return head;
}


//问题：给出俩个单向链表的头指针，比如h1，h2，判断这俩个链表是否相交。交点
//算法：
/*
 1.首先假定链表不带环
 那么，我们只要判断俩个链表的尾指针是否相等。
 相等，则链表相交；否则，链表不相交。
 2.如果链表带环，
 那判断一链表上俩指针相遇的那个节点，在不在另一条链表上。
 如果在，则相交，如果不在，则不相交。
 
 所以，事实上，这个问题就转化成了：
 1.先判断带不带环
 2.如果都不带环，就判断尾节点是否相等
 3.如果都带环，判断一链表上俩指针相遇的那个节点，在不在另一条链表上。
 如果在，则相交，如果不在，则不相交。
 */

//判断一个单项链表是否存在环，快慢指针，双指针都是解决问题的好办法
bool checkCircle(const node* head)
{
    if(head==NULL)                  //首先检查这个
        return false;
    const node *low = head, *fast = head->next;
    while(fast && fast->next)
    {
        low = low->next;
        fast = fast->next->next;
        if(low == fast) return true;
    }
    return false;
}

//判断一个单项链表的环的位置
node* FindLoopPort(node *head)
{
    node *slow = head, *fast = head;
    while ( fast && fast->next )
    {
        slow = slow->next;
        fast = fast->next->next;
        if ( slow == fast ) break;
    }
    if (fast == NULL || fast->next == NULL)
        return NULL;
    slow = head;
    while (slow != fast)
    {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

//下面这种算法有bug
bool connectionList(const node* h1, const node* h2) {
    if (h1 == NULL || h2 == NULL)           //首先检查这个
        return false;
    if (!checkCircle(h1) && !checkCircle(h2)) { //都没环
        while (h1->next != NULL) h1 = h1->next;
        while (h2->next != NULL) h2 = h2->next;
        if (h1 == h2)
            return true;
        
    }else {
        while (h1 != h2 && h1 != NULL && h2 != NULL) {
            /*若都有环，但是不相交，这里是死循环*/
            /*
             所以，判断带环的链表，相不相交，只能这样：
             如果都带环，判断一链表上俩指针相遇的那个节点，在不在另一条链表上。
             如果在，则相交，如果不在，则不相交
             */
            h1 = h1->next;
            if (h2->next)
                h2 = h2->next->next;
            else
                h2 = h2->next;
        }
        if (h1 == h2 && h1 && h2)
            return true;
        
    }
    return false;
}

//algorithm3: 先遍历得到两条链表的长度信息，先让长度更长的移动一段距离，再同时开始运动
//algorithm4:
unsigned int GetListLength(ListNode* pHead);

ListNode* FindFirstCommonNode( ListNode *pHead1, ListNode *pHead2)
{
    //
    unsigned int nLength1 = GetListLength(pHead1);
    unsigned int nLength2 = GetListLength(pHead2);
    int nLengthDif = nLength1 - nLength2;
    
    ListNode* pListHeadLong = pHead1;
    ListNode* pListHeadShort = pHead2;
    if(nLength2 > nLength1)
    {
        pListHeadLong = pHead2;
        pListHeadShort = pHead1;
        nLengthDif = nLength2 - nLength1;
    }
    
    //
    for(int i = 0; i < nLengthDif; ++ i)
        pListHeadLong = pListHeadLong->succ;
    
    while((pListHeadLong != NULL) &&
          (pListHeadShort != NULL) &&
          (pListHeadLong != pListHeadShort))
    {
        pListHeadLong = pListHeadLong->succ;
        pListHeadShort = pListHeadShort->succ;
    }
    
    
    ListNode* pFisrtCommonNode = pListHeadLong;
    
    return pFisrtCommonNode;
}

unsigned int GetListLength(ListNode* pHead)
{
    unsigned int nLength = 0;
    ListNode* pNode = pHead;
    while(pNode != NULL)
    {
        ++ nLength;
        pNode = pNode->succ;
    }
    
    return nLength;
}




//问题：在二叉树中找出和为某一值的所有路径(树）
//算法：与Leetcode combination sum I的类似，使用回溯剪枝法，利用堆栈和深度优先搜索策略
/*
 当访问到某一结点时，把该结点添加到路径上，并累加当前结点的值。
 如果当前结点为叶结点并且当前路径的和刚好等于输入的整数，则当前的路径符合要求，我们把它打印出来
 
 如果当前结点不是叶结点，则继续访问它的子结点。当前结点访问结束后，递归函数将自动回到父结点。
 因此我们在函数退出之前要在路径上删除当前结点并减去当前结点的值，
 以确保返回父结点时路径刚好是根结点到父结点的路径。
 
 我们不难看出保存路径的数据结构实际上是一个栈结构，因为路径要与递归调用状态一致，
 而递归调用本质就是一个压栈和出栈的过程。
 */
//递归1
void FindPath_(
              BinaryTreeNode*   pTreeNode,    // a node of binary tree
              int               expectedSum,  // the expected sum
              int&              currentSum,   // the sum of path
              vector<int>&      path         // a path from root to current node
){
    if(!pTreeNode)
        return;
    
    currentSum += pTreeNode->m_nValue;
    path.push_back(pTreeNode->m_nValue);
    //这里没有采用stack而是采用vector原因在于我们要遍历栈中的元素，而栈不提供迭代器的功能
    
    // if the node is a leaf, and the sum is same as pre-defined,
    // the path is what we want. print the path
    bool isLeaf = (!pTreeNode->m_pLeft && !pTreeNode->m_pRight);
    if(currentSum == expectedSum && isLeaf)
    {
        std::vector<int>::iterator iter = path.begin();
        for(; iter != path.end(); ++ iter)
            std::cout << *iter << '\t';
        std::cout << std::endl;
    }
    
    // if the node is not a leaf, goto its children
    if(pTreeNode->m_pLeft)
        FindPath_(pTreeNode->m_pLeft, expectedSum, currentSum, path);
    if(pTreeNode->m_pRight)
        FindPath_(pTreeNode->m_pRight, expectedSum, currentSum, path);
    
    // when we finish visiting a node and return to its parent node,
    // we should delete this node from the path and
    // minus the node's value from the current sum
    currentSum -= pTreeNode->m_nValue;
    path.pop_back();
}

//递归2， 剑指offer
void FindPath(BinaryTreeNode* pRoot, int expectedSum, std::vector<int>& path, int& currentSum);

void FindPath(BinaryTreeNode* pRoot, int expectedSum)
{
    if(pRoot == NULL)
        return;
    
    std::vector<int> path;
    int currentSum = 0;
    FindPath(pRoot, expectedSum, path, currentSum);
}

void FindPath
(
 BinaryTreeNode*   pRoot,
 int               expectedSum,
 std::vector<int>& path,
 int&              currentSum
 )
{
    currentSum += pRoot->m_nValue;
    path.push_back(pRoot->m_nValue);

    bool isLeaf = pRoot->m_pLeft == NULL && pRoot->m_pRight == NULL;
    if(currentSum == expectedSum && isLeaf)
        //找到了满足条件的方案，打印出来，这其实与遍历的思想完全一致，相当于VISIT函数
    {
        printf("A path is found: ");
        std::vector<int>::iterator iter = path.begin();
        for(; iter != path.end(); ++ iter)
            printf("%d\t", *iter);
        
        printf("\n");
    }
    
    if(pRoot->m_pLeft != NULL)
        FindPath(pRoot->m_pLeft, expectedSum, path, currentSum);
    if(pRoot->m_pRight != NULL)
        FindPath(pRoot->m_pRight, expectedSum, path, currentSum);
    
    //在返回父节点之前，在路径上删除当前节点，并在currentSum中减去当前节点的值
    currentSum -= pRoot->m_nValue;
    path.pop_back();
}


//题目：求子数组的最大和
/*
输入一个整形数组，数组里有正数也有负数。
数组中连续的一个或多个整数组成一个子数组，每个子数组都有一个和。
求所有子数组的和的最大值。要求时间复杂度为O(n)。
*/
//算法：
/*
 解释下：
 例如输入的数组为1, -2, 3, 10, -4, 7, 2, -5，
 那么最大的子数组为     3, 10, -4, 7, 2，
 因此输出为该子数组的和18
 
 所有的东西都在以下俩行，
 即：
 b  ：  0  1  -1  3  13   9  16  18  7
 sum：  0  1   1  3  13  13  16  18  18
 
 其实算法很简单，当前面的几个数，加起来后，b<0后，
 把b重新赋值，置为下一个元素，b=a[i]。
 当b>sum，则更新sum=b;
 若b<sum，则sum保持原值，不更新
 */
int maxSubArray(int* a, int n)
{
    int sum = 0;
    int b = 0;
    
    for(int i = 0; i < n; i++)
    {
        if(b < 0)
            b = a[i];
        else
            b += a[i];
        if(sum < b)
            sum = b;
    }
    return sum;
}
//算法：动态规划
int maxSubArray2(int A[], int n) {
    int result = INT_MIN, f = 0;
    for (int i = 0; i < n; i++) {
        f = max(f + A[i], A[i]);
        result = max(result, f);
    }
    return result;
}


//problem: obstain the maximum sum of the sub-matrix
//algorithm: dynanmic programming, 2D DP，下面这段代码是错的，但是思想是对的，利用积分图
//int maxSubMatrix(vector<vector<int> >& matrix) {
//    int N = (int)matrix.size();
//    int M = (int)matrix[0].size();
//    int PS[N+1][M+1];
//    for (int i = 0; i <= N; i++){
//        PS[i][0] = 0;
//    }
//    for (int j = 0; j <= M; j++){
//        PS[0][j] = 0;
//    }
//    int tmp = 0;
//    for (int i = 1; i <= N; i++) {
//        for (int j = 1; j <= M; j++) {
//            tmp  = PS[i-1][j] + PS[i][j-1] - PS[i-1][j-1] + matrix[i-1][j-1];
//            PS[i][j] = max(max(tmp, PS[i-1][j]), max(PS[i-1][j-1], PS[i][j-1]));
//        }
//    }
//    return PS[N][M];
//    
//}
//algorithm2: 这下面的才是对的，利用maxSubArray

int maxSubMatrix(vector<vector<int> > a, int n){
    
    int max_sum = INT_MIN;
    int * b = new int [n];
    int rowLast = 0;
    int colLast = 0;
    for(int j = 0;j < n;j++)
    {
        for(int i = 0; i < n; i++)
            b[i]= 0;
        for(int i = j; i < n; i++) {
            for(int k = 0;k < n;k++)
                b[k] += a[k][i]; //换成行相加，效率更高，缓存友好
            //其实这还能优化，用一个三维的数组来记录中间值，可以避免重复的运算
            int sum = maxSubArray(b,n);
            if(sum > max_sum) {
                max_sum = sum;
                rowLast = j;
                colLast = i;
            }
        }
    }
    delete []b;
    return max_sum;
}
//问题：设计包含min函数的栈，定义栈的数据结构，要求添加一个min函数，能够得到栈的最小元素。
//要求函数min、push以及pop的时间复杂度都是O(1)。
//算法：借助一个辅助栈来保存最小值
template<typename T>
class StackSuppliedMin{
public:
    vector<T> datas;
    vector<size_t> minIndexStack; //借助一个辅助栈,保存的是最小值的index
    
    void push(T data){
        datas.push_back(data);
        if (minIndexStack.empty() || data < datas[minIndexStack.back()])
            minIndexStack.push_back(datas.size()-1);
    }
    
    void pop(){
        assert(!datas.empty());
        if (datas.back() == datas[minIndexStack.back()])
            minIndexStack.pop_back();
        datas.pop_back();
    }
    
    T min(){
        assert(!datas.empty() && !minIndexStack.empty());
        return datas[minIndexStack.back()];
    }
    
    void display();
};
//算法2：在另一个栈中直接存储最小值
class MinStack {
public:
    void push(int x) {
        p.push_back(x);
        if (q.size() == 0 || x < q.back() ) //这句判断很重要
            q.push_back(x);
        else q.push_back(q.back());
    }
    
    void pop() {
        p.pop_back();
        q.pop_back();
    }
    
    int top() {
        return p.back();
    }
    
    int getMin() {
        return q.back();
    }
private:
    vector<int> p;
    vector<int> q;
};

//problem: 将上面的最小值栈推广到最大值队列
//algorithm: 用两个栈可以实现一个队列，而其中的一个栈是上述的最大栈（最小的类似），所以最大的队列包含了底层4个基本栈
template<typename T>
class MaxStack {
public:
    void Push(const T& value) {
        data_.push(value);
        if (max_element_.empty()) {
            max_element_.push(value);
        } else if (value >= max_element_.top()) {
            max_element_.push(value);
        }
    }
    T Top() {
        return data_.top();
    }
    void Pop() {
        if (data_.top() == max_element_.top()) {
            max_element_.pop();
        }
        data_.pop();
    }
    bool Empty() {
        return data_.empty();
    }
    T Max() {
        if (!max_element_.empty()) {
            return max_element_.top();
        }
        return -1;
    }
private:
    std::stack<T> data_;
    std::stack<T> max_element_;
};

template<typename T>
class MaxQueue {
public:
    void Push(const T& value) {
        push_stack_.Push(value);
    }
    T Front() {
        if (pop_stack_.empty()) {
            while (!push_stack_.Empty()) {
                pop_stack_.Push(push_stack_.Top());
                push_stack_.Pop();
            }
        }
        return pop_stack_.Top();
    }
    void Pop() {
        if (pop_stack_.Empty()) {
            while (!push_stack_.Empty()) {
                pop_stack_.Push(push_stack_.Top());
                push_stack_.Pop();
            }
        }
        pop_stack_.Pop();
    }
    bool IsEmpty() {
        return push_stack_.Empty() && pop_stack_.Empty();
    }
    T Max() {
        if (!push_stack_.Empty() && !pop_stack_.Empty()) {
            return push_stack_.Max() > pop_stack_.Max() ? push_stack_.Max() : pop_stack_.Max();
        } else if (push_stack_.Empty() && !pop_stack_.Empty()) {
            return pop_stack_.Max();
        } else if (!push_stack_.Empty() && pop_stack_.Empty()) {
            return push_stack_.Max();
        } else {
            //      throw RUNTIME_ERROR;
        }
        return -1;
    }
private:
    MaxStack<T> push_stack_;
    MaxStack<T> pop_stack_;
};
void maxqueue_main() {
    MaxQueue<int> max_queue;
    max_queue.Push(1);
    max_queue.Push(2);
    max_queue.Push(6);
    max_queue.Push(4);
    max_queue.Push(5);
    max_queue.Push(2);
    printf("max %d\n", max_queue.Max());
    max_queue.Pop();
    printf("max %d\n", max_queue.Max());
    max_queue.Pop();
    printf("max %d\n", max_queue.Max());
    max_queue.Pop();
    printf("max %d\n", max_queue.Max());
    max_queue.Pop();
    printf("max %d\n", max_queue.Max());
    max_queue.Pop();
    printf("max %d\n", max_queue.Max());
}


//问题：把二元查找树转变成排序的双向链表
//算法：中序递归
struct BSTreeNode
{
    int m_nValue; // value of node
    BSTreeNode *m_pLeft; // left child of node
    BSTreeNode *m_pRight; // right child of node
};

typedef BSTreeNode DoubleList;
DoubleList * pHead;
DoubleList * pLastNodeInlist; //始终指向双向链表的最后一个节点

void convertToDoubleList(BSTreeNode * pCurrent);
// 创建二元查找树
void addBSTreeNode(BSTreeNode * & pCurrent, int value)
{
    if (NULL == pCurrent)
    {
        BSTreeNode * pBSTree = new BSTreeNode();
        pBSTree->m_pLeft = NULL;
        pBSTree->m_pRight = NULL;
        pBSTree->m_nValue = value;
        pCurrent = pBSTree;
        
    }
    else
    {
        if ((pCurrent->m_nValue) > value)
        {
            addBSTreeNode(pCurrent->m_pLeft, value);
        }
        else if ((pCurrent->m_nValue) < value)
        {
            addBSTreeNode(pCurrent->m_pRight, value);
        }
        else
        {
            //cout<<"重复加入节点"<<endl;
        }
    }
}

// 遍历二元查找树  中序
void inorderBSTree(BSTreeNode * pCurrent)
{
    if (NULL == pCurrent){
        return;
    }
    if (NULL != pCurrent->m_pLeft){
        inorderBSTree(pCurrent->m_pLeft);
    }
    // 节点接到链表尾部，假设之前访问过的结点已经调整为一个双向链表，且最后一个元素是
    // 已链接元素的最大值，那么只需要将当前结点连接至双向链表的最后一个结点即可
    
    convertToDoubleList(pCurrent);
    
    // 右子树为空
    if (NULL != pCurrent->m_pRight){
        inorderBSTree(pCurrent->m_pRight);
    }
}

// 二叉树转换成list
void  convertToDoubleList(BSTreeNode * pCurrent)
{
    
    pCurrent->m_pLeft = pLastNodeInlist; //使当前结点的左指针指向双向链表中最后一个结点
    if (NULL != pLastNodeInlist) ////使双向链表中最后一个结点的右指针指向当前ƒ结点
    {
        pLastNodeInlist->m_pRight = pCurrent;
    }
    else //若最后一个元素不存在，此时双向链表尚未建立，因此将当前结点设为双向链表头结点
    {
        pHead = pCurrent;
    }
    pLastNodeInlist = pCurrent; //将当前结点设为双向链表中最后一个结点
    cout<<pCurrent->m_nValue<<endl;
}


//问题：给定两个串a和b，问b是否是a的子串的变位词。例如输入a = hello, b = lel, lle,
//ello都是true,但是b = elo是false
//算法：划窗+字符种类差
int anagramMatch(char* t, char* p){
    int num[26] = {0};
    int nonZero = 0;
    int lenp = (int)strlen(p);
    int lent = (int)strlen(t);
    
    for (int i = 0; i < lenp; i++){
        if (++num[p[i] - 'a'] == 1) ++nonZero;
    }
    
    int i, k = 0;
    for (; k < lent-lenp; k ++){
        for (i = k; i < lenp+k; i ++){
            int c = t[i] - 'a';
            --num[c];
            if (num[c] == 0)    --nonZero;
            if (num[c] == -1)   ++nonZero;
        }
        if (nonZero==0)     return k;
    }
    return -1;
}



//问题：bitmap的使用
//算法：
/*简述bitmap的原理：(以字符串是否包含为例)
 int dictionary = 0; 用来保存32个bit;
 
 setbit:
    for x in string1:
        dictionary = dictionary | 0x01 << x - 'a';
 getbit:
    for x in string2:
        if dictionary != dictionary | 0x01 << x - 'a';
            break;
        else
            YES;
 */
#define BYTESIZE 8  //定义每个Byte中有8个Bit位
void SetBit(char *p, int posi)
{
    for(int i = 0; i < posi/BYTESIZE; i++)
    {
        p++;
    }
    
    *p = *p|(0x01 << (posi%BYTESIZE));//将该Bit位赋值1
    return;
}

void BitMapSortDemo(int* data, int n, int maxElement)
{
    //为了简单起见，我们不考虑负数
    
    const int BufferLen = maxElement / 8 + 1;
    //BufferLen这个值是根据待排序的数据中最大值确
    //待排序中的最大值是14，因此只需要2个Bytes(16个Bit)
    char *pBuffer = new char[BufferLen];
    
    //要将所有的Bit位置为0，否则结果不可预知。
    memset(pBuffer,0,BufferLen);
    for(int i = 0; i < n; i++)    //
    {
        //首先将相应Bit位上置为1
        SetBit(pBuffer,data[i]);
    }
    
    //输出排序结果
    for(int i=0; i < BufferLen; i++)    //每次处理一个字节(Byte)
    {
        for(int j=0; j< BYTESIZE;j++)   //处理该字节中的每个Bit位
        {
            //判断该位上是否是1，进行输出，这里的判断比较笨。
            //首先得到该第j位的掩码（0x01＜＜j），将内存区中的
            //位和此掩码作与操作。最后判断掩码是否和处理后的
            //结果相同
            if((*pBuffer&(0x01 << j)) == (0x01<<j))
            {
                printf("%d ",i*BYTESIZE + j);
            }
        }
        pBuffer++;
    }
}



//问题：建立Trie树
//算法：用于匹配，统计等
namespace trie {
    
    #define MAX 26//字符集大小
    typedef struct TrieNode
    {
        int nCount;//记录该字符出现次数
        struct TrieNode* next[MAX];
    }TrieNode;

    TrieNode Memory[1000000];
    int allocp=0;

    /*初始化*/
    void InitTrieRoot(TrieNode* *pRoot)
    {
        *pRoot=NULL;
    }

    /*创建新结点*/
    TrieNode* CreateTrieNode()
    {
        int i;
        TrieNode *p;
        p = &Memory[allocp++];
        p->nCount=1;
        for(i=0;i<MAX;i++)
        {
            p->next[i]=NULL;
        }
        return p;
    }

    /*插入*/
    void InsertTrie(TrieNode* *pRoot,char *s)
    {
        int i,k;
        TrieNode *p;
        if(!(p = *pRoot))
        {
            p = *pRoot = CreateTrieNode();
        }
        i=0;
        while(s[i])
        {
            k = s[i++] - 'a';//确定branch
            if(p->next[k]) p->next[k]->nCount++;
            else p->next[k] = CreateTrieNode();
            p = p->next[k];
        }
    }

    //查找
    int SearchTrie(TrieNode* *pRoot,char *s)
    {
        TrieNode *p;
        int i,k;
        if(!(p = *pRoot))
        {
            return 0;
        }
        i=0;
        while(s[i])
        {
            k = s[i++]-'a';
            if(p->next[k] == NULL) return 0;
            p=p->next[k];
        }
        return p->nCount;
    }

}

//问题：归并向量的中位数
//算法：充分利用向量的有序性
//中位数算法蛮力版：效率低，仅适用于max(n1, n2)较小的情况
//子向量S1[lo1, lo1 + n1)和S2[lo2, lo2 + n2)分别有序，数据项可能重复
int trivialMedian ( vector<int>& S1, int lo1, int n1, vector<int>& S2, int lo2, int n2 ) {
    int hi1 = lo1 + n1, hi2 = lo2 + n2;
    vector<int> S; //将两个有序子向量归并为一个有序向量
    while ( ( lo1 < hi1 ) && ( lo2 < hi2 ) ) {
        while ( ( lo1 < hi1 ) && S1[lo1] <= S2[lo2] ) S.push_back ( S1[lo1 ++] );
        while ( ( lo2 < hi2 ) && S2[lo2] <= S1[lo1] ) S.push_back ( S2[lo2 ++] );
    }
    while ( lo1 < hi1 )
        S.push_back ( S1[lo1 ++] );
    while ( lo2 < hi2 )
        S.push_back ( S1[lo2 ++] );
    return S[ ( n1 + n2 ) / 2]; //直接返回归并向量的中位数
}
//归并长度等长的向量
int median( vector<int>& S1, int lo1, vector<int>& S2, int lo2, int n ) { //中位数算法（高效版）

    if ( n < 3 )
        return trivialMedian ( S1, lo1, n, S2, lo2, n ); //递归基，当元素数目较少时，可以采用蛮力法
    int mi1 = lo1 + n / 2, mi2 = lo2 + ( n - 1 ) / 2; //长度（接近）减半
    if ( S1[mi1] < S2[mi2] )
        return median ( S1, mi1, S2, lo2, n + lo1 - mi1 ); //取S1右半、S2左半
    else if ( S1[mi1] > S2[mi2] )
        return median ( S1, lo1, S2, mi2, n + lo2 - mi2 ); //取S1左半、S2右半
    else
        return S1[mi1];
}
//归并长度不等长的向量，复杂度：log(min(n1, n2))
int median ( vector<int>& S1, int lo1, int n1, vector<int>& S2, int lo2, int n2 ) { //中位数算法
    if ( n1 > n2 ) return median ( S2, lo2, n2, S1, lo1, n1 ); //确保n1 <= n2
    if ( n2 < 6 ) //递归基：1 <= n1 <= n2 <= 5
        return trivialMedian ( S1, lo1, n1, S2, lo2, n2 );
    ///////////////////////////////////////////////////////////////////////
    //                lo1            lo1 + n1/2      lo1 + n1 - 1
    //                 |                 |                 |
    //                 X >>>>>>>>>>>>>>> X >>>>>>>>>>>>>>> X
    // Y .. trimmed .. Y >>>>>>>>>>>>>>> Y >>>>>>>>>>>>>>> Y .. trimmed .. Y
    // |               |                 |                 |               |
    // lo2     lo2 + (n2-n1)/2       lo2 + n2/2     lo2 + (n2+n1)/2    lo2 + n2 -1
    ///////////////////////////////////////////////////////////////////////
    if ( 2 * n1 < n2 ) //若两个向量的长度相差悬殊，则长者（S2）的两翼可直接截除
        return median ( S1, lo1, n1, S2, lo2 + ( n2 - n1 - 1 ) / 2, n1 + 2 - ( n2 - n1 ) % 2 );
    ///////////////////////////////////////////////////////////////////////
    //    lo1                  lo1 + n1/2              lo1 + n1 - 1
    //     |                       |                       |
    //     X >>>>>>>>>>>>>>>>>>>>> X >>>>>>>>>>>>>>>>>>>>> X
    //                             |
    //                            m1
    ///////////////////////////////////////////////////////////////////////
    //                            mi2b
    //                             |
    // lo2 + n2 - 1         lo2 + n2 - 1 - n1/2
    //     |                       |
    //     Y <<<<<<<<<<<<<<<<<<<<< Y ...
    //                                .
    //                               .
    //                              .
    //                             .
    //                            .
    //                           .
    //                          .
    //                         ... Y <<<<<<<<<<<<<<<<<<<<< Y
    //                             |                       |
    //                       lo2 + (n1-1)/2               lo2
    //                             |
    //                            mi2a
    ///////////////////////////////////////////////////////////////////////
    int mi1  = lo1 + n1 / 2;
    int mi2a = lo2 + ( n1 - 1 ) / 2;
    int mi2b = lo2 + n2 - 1 - n1 / 2;
    if ( S1[mi1] > S2[mi2b] ) //取S1左半、S2右半
        return median ( S1, lo1, n1 / 2 + 1, S2, mi2a, n2 - ( n1 - 1 ) / 2 );
    else if ( S1[mi1] < S2[mi2a] ) //取S1右半、S2左半
        return median ( S1, mi1, ( n1 + 1 ) / 2, S2, lo2, n2 - n1 / 2 );
    else //S1保留，S2左右同时缩短
        return median ( S1, lo1, n1, S2, mi2a, n2 - ( n1 - 1 ) / 2 * 2 );
}

//问题：在无序向量中，若有一半以上的元素同为m, 则称之为主流数（majority）
//算法1：减而治之
int majEleCandidate ( vector<int> A );
bool majEleCheck ( vector<int> A, int maj );

bool majority ( vector<int> A, int& maj ) { //众数查找算法：T可比较可判等
    maj = majEleCandidate ( A ); //必要性：选出候选者maj
    return majEleCheck ( A, maj ); //充分性：验证maj是否的确当选
}
int majEleCandidate ( vector<int> A ) { //选出具备必要条件的众数候选者
    int maj = 0; //众数候选者
    // 线性扫描：借助计数器c，记录maj与其它元素的数量差额
    for ( int c = 0, i = 0; i < A.size(); i++ )
        if ( 0 == c ) { //每当c归零，都意味着此时的前缀P可以剪除
            maj = A[i]; c = 1; //众数候选者改为新的当前元素
        } else //否则
            maj == A[i] ? c++ : c--; //相应地更新差额计数器
    return maj; //至此，原向量的众数若存在，则只能是maj —— 尽管反之不然
}
bool majEleCheck ( vector<int> A, int maj ) { //验证候选者是否确为众数
    int occurrence = 0; //maj在A[]中出现的次数
    for ( int i = 0; i < A.size(); i++ ) //逐一遍历A[]的各个元素
        if ( A[i] == maj ) occurrence++; //每遇到一次maj，均更新计数器
    return 2 * occurrence > A.size(); //根据最终的计数值，即可判断是否的确当选
}

//algorithm2: 只需要判断中位数是不是众数即可。两步：找到中位数，判断中位数是不是众数
bool g_bInputInvalid = false;

bool CheckInvalidArray(int* numbers, int length)
{
    g_bInputInvalid = false;
    if(numbers == NULL && length <= 0)
        g_bInputInvalid = true;
    
    return g_bInputInvalid;
}

bool CheckMoreThanHalf(int* numbers, int length, int number)
{
    int times = 0;
    for(int i = 0; i < length; ++i)
    {
        if(numbers[i] == number)
            times++;
    }
    
    bool isMoreThanHalf = true;
    if(times * 2 <= length)
    {
        g_bInputInvalid = true;
        isMoreThanHalf = false;
    }
    
    return isMoreThanHalf;
}

int partition ( int* _elem, int lo, int hi ) ;
int MoreThanHalfNum_Solution1(int* numbers, int length)  //直接判断中位数n/2满不满足条件即可
{
    if(CheckInvalidArray(numbers, length))
        return 0;
    
    int middle = length >> 1;
    int start = 0;
    int end = length - 1;
    int index = partition(numbers, start, end);
    while(index != middle)
    {
        if(index > middle)
        {
            end = index - 1;
            index = partition(numbers, start, end);
        }
        else
        {
            start = index + 1;
            index = partition(numbers, start, end);
        }
    }
    
    int result = numbers[middle];
    if(!CheckMoreThanHalf(numbers, length, result))
        result = 0;
    
    return result;
}




//问题：排序
//算法：quicksort
//Quicksort is typically over twice as fast as merge sort
//Quicksort behaves well even with caching and virtual memory

int partition ( int* _elem, int lo, int hi ) { //版本A：基本形式
    swap ( _elem[lo], _elem[lo + rand() % ( hi - lo + 1 ) ] ); //任选一个元素与首元素交换
    int pivot = _elem[lo]; //以首元素为候选轴点——经以上交换，等效于随机选取
    while ( lo < hi ) { //从向量的两端交替地向中间扫描
        while ( ( lo < hi ) && ( pivot <= _elem[hi] ) ) //在不小于pivot的前提下
            hi--;           //向左拓展右端子向量
        _elem[lo] = _elem[hi]; //小于pivot者归入左侧子序列
        while ( ( lo < hi ) && ( _elem[lo] <= pivot ) ) //在不大于pivot的前提下
            lo++;           //向右拓展左端子向量
        _elem[hi] = _elem[lo]; //大于pivot者归入右侧子序列
    }                   //assert: lo == hi
    _elem[lo] = pivot; //将备份的轴点记录置于前、后子向量之间
    return lo; //返回轴点的秩
}

void quickSort ( int* _elem, int lo, int hi ) { //0 <= lo < hi <= size
    if ( hi - lo < 2 ) return;              //单元素区间自然有序，否则...
    int mi = partition ( _elem, lo, hi - 1 ); //在[lo, hi - 1]内构造轴点
    quickSort ( _elem, lo, mi );                       //对前缀递归排序
    quickSort ( _elem, mi + 1, hi );                   //对后缀递归排序
}

//问题：串匹配算法
//算法1：brute force
int stringMatch(char* P, char* T){
    size_t n = strlen(T), i = 0; //文本串长度
    size_t m = strlen(P), j = 0; //模式串长度
    while ( j < m && i < n) {
        if (T[i] == P[j])
        {   i ++; j--; }
        else
        {   i -= j - 1; j = 0; }
    }
    return (int)(i - j);
}

//算法2：brute force
int stringMatch2(char* P, char* T){
    size_t n = strlen(T), i = 0;
    size_t m = strlen(P), j = 0;
    while ( j < m && i < n) {
        if (T[i + j] == P[j])
            j++;
        else
        {   i ++; j = 0; }
    }
    return (int)(i - j);
}

//算法3：KMP
int* buildNext(char* P);
int KMP_stringMatch ( char* P, char* T ) {  //KMP算法
    int* next = buildNext ( P ); //构造next表
    int n = ( int ) strlen ( T ), i = 0; //文本串指针
    int m = ( int ) strlen ( P ), j = 0; //模式串指针
    while ( j < m  && i < n ) //自左向右逐个比对字符
        if ( 0 > j || T[i] == P[j] ) //若匹配，或P已移出最左侧（两个判断的次序不可交换）
        { i ++;  j ++; } //则转到下一字符
        else //否则
            j = next[j]; //模式串右移（注意：文本串不用回退）
    delete [] next; //释放next表
    return i - j;
}

int* buildNext ( char* P ) { //构造模式串P的next表
    size_t m = strlen ( P ), j = 0; //“主”串指针
    int* N = new int[m]; //next表
    int t = N[0] = -1; //模式串指针
    while ( j < m - 1 )
        if ( 0 > t || P[j] == P[t] ) { //匹配
            j ++; t ++;
            N[j] = t; //此句可改进...
        } else //失配
            t = N[t];
    return N;
}


//问题：支持查找最小元素的堆栈getMin
//算法：使用两个堆栈,S1维护原来的值，S2维护最小值，它们元素个数一样多
class minStack {
public:
    stack<int> s1;
    stack<int> s2;
    
    void push(int x){
        s1.push(x);
        if (s2.empty() && s2.top() >= x)
            s2.push(x);
    }
    
    void pop() {
        if (s1.top() == s2.top())
            s2.pop();
        s1.pop();
    }
    
    int getMin(){
        return s2.top();
    }
};

//写成模板、标准类的形式
template <typename T>
class StackWithMin {
public:
    StackWithMin(void) {}
    virtual ~StackWithMin(void) {}
    
    T& top(void);
    const T& top(void) const;
    
    void push(const T& value);
    void pop(void);
    
    const T& min(void) const;
    
    bool empty() const;
    size_t size() const;
    
private:
    std::stack<T>   m_data;     //
    std::stack<T>   m_min;      //
};

template <typename T> void StackWithMin<T>::push(const T& value)
{
    //
    m_data.push(value);
    
    if(m_min.size() == 0 || value < m_min.top())
        m_min.push(value);
    else
        m_min.push(m_min.top());
}

template <typename T> void StackWithMin<T>::pop()
{
    assert(m_data.size() > 0 && m_min.size() > 0);
    
    m_data.pop();
    m_min.pop();
}


template <typename T> const T& StackWithMin<T>::min() const
{
    assert(m_data.size() > 0 && m_min.size() > 0);
    
    return m_min.top();
}

template <typename T> T& StackWithMin<T>::top()
{
    return m_data.top();
}

template <typename T> const T& StackWithMin<T>::top() const
{
    return m_data.top();
}

template <typename T> bool StackWithMin<T>::empty() const
{
    return m_data.empty();
}

template <typename T> size_t StackWithMin<T>::size() const
{
    return m_data.size();
}




//问题：使用两个堆栈来实现队列
//算法：一个负责入队，一个负责出队
class DoubleStack2Queue {
public:
    stack<int> s1;
    stack<int> s2;
    int push(int x)
    {
        s1.push(x);
        return x;
    }
    
    void pop()
    {
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        s2.pop();
    }

};


//问题：找出一个大小为n的数组里面最大的k个数
//算法1：建立一个大小为k的堆，复杂度为O(k + (n-k)logk)~O(nlogk)
#define PARENT(i) (i)/2
#define LEFT(i) 2*(i)+1
#define RIGHT(i) 2*(i+1)

void swap ( int * a , int * b )
{
    int tmp;
    tmp = * a;
    * a = * b ;
    * b = tmp;
}

void max_heapify ( int * arr , int index , int len )
{
    int l = LEFT ( index ) ;
    int r = RIGHT ( index ) ;
    int largest ;
    if ( l < len && arr [ l ] > arr [ index ] )
        largest = l ;
    else
        largest = index ;
    if ( r < len && arr [ r ] > arr [ largest ] )
        largest = r ;
    if ( largest != index ) { //将最大元素提升，并递归
        swap ( & arr [ largest ] , & arr [ index ] ) ;
        max_heapify ( arr , largest , len ) ;
    }
}

void build_maxheap ( int * arr , int len )
{
    int i ;
    if ( arr == NULL || len <= 1 )
        return ;
    for ( i = len / 2 + 1 ; i >= 0 ; -- i )
        max_heapify ( arr , i , len ) ;
}

void k_min ( int * arr , int len , int k )
{
    int i ;
    build_maxheap ( arr , k ) ;
    for ( i = k ; i < len ; i ++ )
    {
        if ( arr [ i ] < arr [ 0 ] )
        {
            arr [ 0 ] = arr [ i ] ;
            max_heapify ( arr , 0 , k ) ;
        }
    }
}
//堆排序
void heap_sort(int *arr,int len)
{
    int i;
    if(arr==NULL || len<=1)
        return;
    build_maxheap(arr,len);
    
    for(i=len-1;i>=1;--i){
        swap(&arr[0],&arr[i]);
        max_heapify(arr,0,--len);
    }
}

//算法2：运用类似快速排序的Partition规则快速选择出最小的k各元素
int k_big ( int arr [ ] , int low , int high , int k )
{
    int pivot    = arr [ low ] ;
    int high_tmp = high ;
    int low_tmp = low ;
    while ( low < high ) {
        //从右向左查找，直到找到第一个小于枢纽元素为止
        while ( low < high && arr [ high ] >= pivot )
        {
            -- high ;
        }
        arr [ low ] = arr [ high ] ;
        //从左向右查找，直到找到第一个大于枢纽元素为止
        while ( low < high && arr [ low ] <= pivot )
        {
            ++ low ;
        }
        arr [ high ] = arr [ low ] ;
    }
    arr [ low ] = pivot ;
    
    if ( low == k - 1 )
    {
        return arr [ low ] ;
    } else if ( low > k - 1 )
    {
        return k_big ( arr , low_tmp , low - 1 , k ) ;
    } else
    {
        return k_big ( arr , low + 1 , high_tmp , k ) ;
    }
}

//算法3：算法2的迭代版本，很好理解
void quickSelect ( vector<int> & A, int k ) {       //基于快速划分的k选取算法
    for ( int lo = 0, hi = (int)A.size() - 1; lo < hi; ) {
        int i = lo, j = hi;
        int pivot = A[lo];
        while ( i < j ) {                           //O(hi - lo + 1) = O(n)
            while ( ( i < j ) && ( pivot <= A[j] ) ) j--; A[i] = A[j];
            while ( ( i < j ) && ( A[i] <= pivot ) ) i++; A[j] = A[i];
        }                                           //assert: i == j
        A[i] = pivot;
        if ( k <= i ) hi = i - 1;
        if ( i <= k ) lo = i + 1;
    } //A[k] is now a pivot
}



//问题：最大间隙问题
//算法：采用桶结构

#define MAXINT INT_MAX
#define MININT INT_MIN
typedef struct _bucket
{
    int min, max;
} Bucket;

int maxGap(int *a, int n)
{
    int max = MININT, min = MAXINT, i;
    double bucketLen;
    for(i = 0; i < n; ++i)
    {
        if(a[i] > max) max = a[i];
        if(a[i] < min) min = a[i];
    }
    bucketLen = (max-min) * 1.0 / (n-1);
    Bucket *bucket = new Bucket[n-1];
    for(i = 0; i < n-1; ++i)
    {
        bucket[i].max = MININT;
        bucket[i].min = MAXINT;
        
    }
    bucket[0].max = min; bucket[0].min = min;
    bucket[n-2].max = max; bucket[n-2].min = max;
    for(i = 0; i < n; ++i)
    {
        int index;
        if(a[i] != min && a[i] != max)
        {
            index = (a[i]-min) * 1.0 / bucketLen;
            if(bucket[index].max < a[i]) bucket[index].max = a[i];
            if(bucket[index].min > a[i]) bucket[index].min = a[i];
        }
    }
    int low = -1, high = -1, maxGap = 0, curGap, pre = 0;
    for(i = 1; i < n-1; ++i)
    {
        if(bucket[i].max != MININT)
        {
            curGap = bucket[i].min - bucket[pre].max;
            if(curGap > maxGap)
            {
                maxGap = curGap;
                low = bucket[pre].max, high = bucket[i].min;
            }
            pre = i;
        }
    }
    printf("the maximum gap is %d, between %d and %d!\n", maxGap, low, high);
    return maxGap;
}


//问题：判断两个序列是否可以组成一个入栈一个出栈序列
//算法：模拟堆栈即可，如果当前要出栈的元素敲好在栈顶，则必须出栈，否则就入栈
bool isPossible(vector<int> &in, vector<int> &out)
{
    stack<int> s;
    for (int i = 0, j = 0; j < out.size(); ++j) {
        while (s.empty() || s.top() != !out[j]) {
            if (i >= in.size())
                return  false;
            s.push(in[i++]);
        }
        s.pop();
    }
    return true;
}


//问题：统计整数二进制展开中数位1的总数
//算法：复杂度为logn
int countOnes ( unsigned int n ) {
    int ones = 0; //计数器复位
    while ( 0 < n ) { //在n缩减至0之前，反复地
        ones += ( 1 & n ); //检查最低位，若为1则计数
        n >>= 1; //右移一位
    }
    return ones; //返回计数
} //等效于glibc的内置函数int __builtin_popcount (unsigned int n)

//算法：O(ones)正比于数位1的总数
int countOnes1 ( unsigned int n ) { //
    int ones = 0; //计数器复位
    while ( 0 < n ) { //在n缩减至0之前，反复地
        ones++; //计数（至少有一位为1）
        n &= n - 1; //清除当前最靠右的1
    }
    return ones; //返回计数
} //等效于glibc的内置函数int __builtin_popcount (unsigned int n)


//问题：求最大公约数
//算法：辗转相除法
int gcd1(int a, int b)
{
    while (true) {
        if (0 == a) return b;
        if (0 == b) return a;
        if (a > b)         a %= b;
        else               b %= a;
    }
}
//上述除法的计算需要很多的时钟周期，改为减法
int gcd2(int x, int y)
{
    if(x < y)
        return gcd2(y, x);
    if(y == 0)
        return x;
    else
        return gcd2(x - y, y);
}
//减法造成递归的深度加深，能不能融合gcd1和gcd2,采用
inline bool IsEven(int x) {
    return (x & 1) == 0;
}
int gcd3(int x, int y)
{
    if(x < y)
        return gcd3(y, x);
    if(y == 0)
        return x;
    else
    {
        if(IsEven(x))
        {
            if(IsEven(y))
                return (gcd3(x >> 1, y >> 1) << 1);
            else
                return gcd3(x >> 1, y);
        }
        else
        {
            if(IsEven(y))
                return gcd3(x, y >> 1);
            else
                return gcd3(y, x - y);
        }
    }
}

//问题：判断多个括号是否匹配
//算法：利用压栈、出栈操作来匹配
bool paren(const char exp[])
{
    std::stack<char> s;
    int i = 0;
    while (exp[i++]) {
        if ('(' == exp[i]) {
            s.push(exp[i]);
        }else if (s.empty() )
            return false;
        else
            s.pop();
    }
    return s.empty();
}

void convert(std::stack<char> &stk, int n, int base)
{
    static char digit[] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        'A', 'B', 'C', 'D', 'E', 'F'
    };
    while (n > 0) {
        stk.push(digit[n%base]);
        n /= base;
    }
}


//问题： 快速排序
//算法： 桶排序
#define CAPACITY 10
struct barrel {
    int node[CAPACITY];
    int count;/* the num of node */
};
extern void quick_sort(int a[], int p, int q);/* not necessary */
void bucket_sort(int data[], int size)
{
    int max, min, num, pos;
    int i, j, k;
    struct barrel *pBarrel;
    
    max = min = data[0];
    for (i = 1; i < size; i++) {
        if (data[i] > max) {
            max = data[i];
        } else if (data[i] < min) {
            min = data[i];
        }
    }
    num = (max - min + 1) / 10 + 1;
    
    pBarrel = (struct barrel*)malloc(sizeof(struct barrel) * num);
    memset(pBarrel, 0, sizeof(struct barrel) * num);
    
    /* put data[i] into barrel which it belong to */
    for (i = 0; i < size; i++) {
        k = (data[i] - min + 1) / 10;/* calculate the index of data[i] in barrel */
        (pBarrel + k)->node[(pBarrel + k)->count] = data[i];
        (pBarrel + k)->count++;
    }
    
    pos = 0;
    for (i = 0; i < num; i++) {
        struct barrel* tmp = pBarrel + i;
        sort(tmp->node, tmp->node + tmp->count );/* sort node in every barrel */
        
        for (j = 0; j < (pBarrel+i)->count; j++) {
            data[pos++] = (pBarrel+i)->node[j];
        }
    }
    free(pBarrel);
}

//问题：排序问题
//算法：冒泡排序
void bubblesort(int A[], int n)
{
    while(n--)
    {
        for(int i = 0; i < n; i++)
            if(A[i] > A[i+1]) {
                std::swap(A[i], A[i+1]);
            }
    }
}

//问题: sort
//算法: merge sort
void merge(int a[], int lo, int mid, int hi)
{
    int *A = a + lo;
    int lb = mid - lo; //B array的长度
    int *B = (int*)malloc(lb * sizeof(int));
    for (int i = 0; i < lb; i++)
        B[i] = A[i];
    
    int lc = hi - mid;//length of B array
    int *C = a + mid;
    int i = 0, j = 0, k = 0; //A---i, B---j, C---k
    while (j < lb && k < lc) {
        while (j < lb && B[j] <= C[k]) A[i++] = B[j++];
        while (k < lc && C[k] <= B[j]) A[i++] = C[k++];
    }
    while ( j < lb ) A[i++] = B[j++];
    free(B);
}

void mergeSort(int A[], int lo, int hi)
{
    int num = hi - lo;
    if (num == 0 || num == 1)
        return;
    int mid = (lo + hi)>>1;
    mergeSort(A, lo, mid);
    mergeSort(A, mid, hi);
    merge(A, lo, mid, hi);
}

//算法：shellsort
void ShellSort(int a[], int n){
    int gap, i, j, temp;
    for (gap = n/2; gap >= 1; gap = gap/2){
        for (i = gap; i < n; i++) {
            temp = a[i];
            for (j = i; (j >= gap) && (a[j - gap] > temp); j = j-gap){
                a[j] = a[j - gap];
            }
            a[j] = temp;
        }
    }
}

//algorithm: counting sort
#define SIZE 65453  //计数排序的一个缺点就是必须先知道数列的最大值，比如对一串字母序列进行排序
void countingSort(int A[], int B[], int n){
    int C[SIZE];
    memset(C, 0, sizeof(int)*SIZE);
    for (int i = 0; i < n; i++)
        C[A[i]]++;
    
    for (int i = 0; i < SIZE; i++)
        C[i] = C[i] + C[i-1];
    
    for (int i = n-1; i >= 0; i--)  //从数组的末尾往开头扫描，依次处理
    {
        B[C[A[i]]] = A[i];
        C[A[i]] = C[A[i]] - 1;
    }
}


//问题: binsearch
//算法: binary search

//两种写法的差异如下：search1和search2
int search1(int array[], int n, int v)  //左闭右闭
{
    int left, right, middle;
    
    left = 0, right = n - 1;    ///差别1
    
    while (left <= right)       //差别2
    {
        middle = (left + right) / 2;
        if (array[middle] > v){
            right = middle - 1; //差别3
        }
        else if (array[middle] < v){
            left = middle + 1;
        }
        else{
            return middle;
        }
    }
    
    return -1;
}

int search2(int array[], int n, int v)  //左闭右开
{
    int left, right, middle;
    
    left = 0, right = n;   ///差别1
    
    while (left < right)    //差别2
    {
        middle = left + (right - left) / 2;
        
        if (array[middle] > v)
        {
            right = middle; //差别3
        }
        else if (array[middle] < v)
        {
            left = middle + 1;
        }
        else
        {
            return middle;
        }
    }
    
    return -1;
}



//不适用递归，如果存在返回数组位置，不存在则返回-1
int binSearch3(int arry[],int len,int value)
{
    //如果传入的数组为空或者数组长度<=0那么就返回-1。防御性编程
    if(arry == NULL||len<=0)
        return -1;
    
    int start = 0;
    int end = len-1;
    
    while(start<=end)//判断清是否有=
    {
        int mid = start + (end-start)/2;
        if(arry[mid] == value)
            return mid;
        else if(value < arry[mid])
            end = mid - 1;        //这里的减一与判断条件中的等号一一对应，这里有减号，前面就要有等号，比如1，2，3，4要找1，因为/符号是向下取整
        else
            start = mid + 1;
    }
    return -1;
    
}

int BinarySearchRecursion(int arry[],int &value,int &start,int &end)
{
    if(start>end)
        return -1;
    
    int mid=start+(end-start)/2;
    if(arry[mid]==value)
        return mid;
    else if(value<arry[mid])
    {
        end = mid - 1;
        return BinarySearchRecursion(arry,value,start,end);
    }
    else
    {
        start = mid + 1;
        return BinarySearchRecursion(arry,value,start,end);
    }
}

int BinarySearchRecursion(int arry[],int &len,int &value)
{
    //如果传入的数组为空或者数组长度<=0那么就返回-1。防御性编程
    if(arry==NULL||len<=0)
        return -1;
    int start=0;
    int end=len-1;
    return  BinarySearchRecursion(arry,value,start,end);
}

void binSearch_main()
{
    int arry[]={1,2,3,4,5,6,7,8};
    int len=sizeof(arry)/sizeof(int);
    int especteNum1=4;
    int especteNum2=9;
    int index=binSearch3(arry,len,especteNum1);
    cout<<"index:"<<index<<endl;
    
    int index2=BinarySearchRecursion(arry,len,especteNum2);
    cout<<"index2:"<<index2<<endl;

}

//problem: shifted Binary Search 3, 4, 5, 6, 7, 8, 1, 2
//algorithm: recursion
int shiftedBinsearch(int a[], int x, int low, int high) {
    
    if (low > high) return -1;
    int mid = low + (high-low)/2;
    
    if (a[mid] == x)
        return mid;
    else if (a[low] < x && x <= a[mid])
        return shiftedBinsearch(a, x, mid + 1, high);
    else
        return shiftedBinsearch(a, x, low, mid - 1);
    return -1;
}
//algorithm2: nonrecursion，这与上面的二分查找类似
int bsearch_rotate(int a[], int n, int t)
{
    int low = 0, high = n-1;
    while (low <= high) {
        int mid = low + (high-low) / 2;
        if (t == a[mid])
            return mid;
        if (a[mid] >= a[low]) { //数组左半有序
            if (t >= a[low] && t < a[mid])
                high = mid - 1;
            else
                low = mid + 1;
        } else {       //数组右半段有序
            if (t > a[mid] && t <= a[high])
                low = mid + 1;
            else
                high = mid - 1;
        }
    }
    return -1;
}


//问题：去除一个数组中相同的值
//算法：将与前一个元素不同的元素直接放在数组的开端处的指针叠加
int uniquefy(int A[], int n)
{
    int i = 0, j = 0;
    while (++j < n)
        if (A[i] != A[j])
            A[++i] = A[j];
    return i+1; //返回元素的个数
}

int disordered(int A[], int n)
{
    int num = 0;
    for (int i = 0; i < n; i++)
        num += (A[i-1] > A[i]);
    return num;
}

//问题：快速计算幂指数
//算法：分解指数n
inline bool doubleEqual(double x, double t) {
    return ( x - t ) < 0.000000001 && ( x - t ) > - 0.000000001;
}
double quickPower(double x, int n) //这个在leetcode上面会超时
{
    //没检查边界条件和错误输入
    //有三种错误处理方式：返回值、全局变量和异常
    if (doubleEqual(x, 0.0) && n < 0)
        return 0.0;
    
    if (n < 0)
        return 1.0 / quickPower(x, -n);
    double result = 1;
    while (0 < n) {
        if (n & 1)  result *= x;
        n >>= 1;
        x *= x;
    }
    return result;
    
}
//算法2：分治法，与mergesort思路完全一样
double quickPower3(double x, int n) {
    if (n == 0) return 1.0;
    double result = 1.0;
    double tmp = quickPower3(x, n/2);
    if ( n % 2 == 0)
        return tmp * tmp;
    else
        return x * tmp * tmp;
}
double quickPower2(double x, int n) {
    if (n < 0)
        return 1.0 / quickPower2(x, -n); //这个不能处理n取最大负数的情况，会有bug，与itoa类似,
                                        //只是这里，但是潜在隐患存在: (-INT_MIN) == INT_MIN
    else
        return quickPower3(x, n);
}

//问题：implement sqrt
//算法：二分查找
int quickSqrt(int x) {
    if (x < 2) return x;
    int left = 1, right = x / 2; //right没必要再往上搜索了
    int last_mid = 0;
    while (left <= right) {
        const int mid = left + (right-left)/2;
        if (x / mid > mid) {//不要用x > mid * mid会溢出
            left = mid + 1;
            last_mid = mid;
        }else if (x / mid < mid) {
            right = mid - 1;
        }else
            return mid;
    }
    return last_mid;
}

//problem: 不用额外的变量颠倒一个字符串
//algorithm: 利用位运算
void reverseString(char* str){  //如果是char* str = "adnafn"，这是不能修改的，出错。可以改为传入为字符数组
    for(int i = 0,j = (int) strlen(str) - 1; i < j; i++, j--){
        str[i] = str[i] ^ str[j];
        str[j] = str[j] ^ str[i];
        str[i] = str[i] ^ str[j];
    }
}

void reverse(int* A, int lo, int hi)
//迭代版，一般用迭代版，以上的递归版效率较低
{
    while (lo < hi)
        std::swap(A[lo++], A[hi--]);
}
void shiftRight(int* A, int n, int k)
{
    k %= n;
    std::reverse(A,A+k);
    std::reverse(A+k, A+n);
    std::reverse(A, A+n);
}


//problem: 复制复杂链表结构
//algorithm：在原始链表上面clone再分离
struct ComplexListNode
{
    int                 m_nValue;
    ComplexListNode*    m_pNext;
    ComplexListNode*    m_pSibling;
};
//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//  |       |      /|\             /|\
//  --------+--------               |
//          -------------------------
void CloneNodes(ComplexListNode* pHead);
void ConnectSiblingNodes(ComplexListNode* pHead);
ComplexListNode* ReconnectNodes(ComplexListNode* pHead);

ComplexListNode* Clone(ComplexListNode* pHead)
{
    CloneNodes(pHead);
    ConnectSiblingNodes(pHead);
    return ReconnectNodes(pHead);
}

void CloneNodes(ComplexListNode* pHead)
{
    ComplexListNode* pNode = pHead;
    while(pNode != NULL)
    {
        ComplexListNode* pCloned = new ComplexListNode();
        pCloned->m_nValue = pNode->m_nValue;
        pCloned->m_pNext = pNode->m_pNext;
        pCloned->m_pSibling = NULL;
        
        pNode->m_pNext = pCloned;
        
        pNode = pCloned->m_pNext;
    }
}

void ConnectSiblingNodes(ComplexListNode* pHead)
{
    ComplexListNode* pNode = pHead;
    while(pNode != NULL)
    {
        ComplexListNode* pCloned = pNode->m_pNext;
        if(pNode->m_pSibling != NULL)
        {
            pCloned->m_pSibling = pNode->m_pSibling->m_pNext;
        }
        
        pNode = pCloned->m_pNext;
    }
}

ComplexListNode* ReconnectNodes(ComplexListNode* pHead)
{
    ComplexListNode* pNode = pHead;
    ComplexListNode* pClonedHead = NULL;
    ComplexListNode* pClonedNode = NULL;
    
    if(pNode != NULL)
    {
        pClonedHead = pClonedNode = pNode->m_pNext;
        pNode->m_pNext = pClonedNode->m_pNext;
        pNode = pNode->m_pNext;
    }
    
    while(pNode != NULL)
    {
        pClonedNode->m_pNext = pNode->m_pNext;
        pClonedNode = pClonedNode->m_pNext;
        
        pNode->m_pNext = pClonedNode->m_pNext;
        pNode = pNode->m_pNext;
    }
    
    return pClonedHead;
}

//
//problem: 只用一个变量来解决中国象棋将帅问题
//algorithm: 利用位运算，
#define HALF_BITS_LENGTH 4
// 这个值是记忆存储单元长度的一半，在这道题里是4bit
#define FULLMASK 255
// 这个数字表示一个全部bit的mask，在二进制表示中，它是11111111。
#define LMASK (FULLMASK << HALF_BITS_LENGTH)
// 这个宏表示左bits的mask，在二进制表示中，它是11110000。
#define RMASK (FULLMASK >> HALF_BITS_LENGTH)
// 这个数字表示右bits的mask，在二进制表示中，它表示00001111。
#define RSET(b, n) (b = ((LMASK & b) ^ n))
// 这个宏，将b的右边设置成n
#define LSET(b, n)  (b = ((RMASK & b) ^ (n << HALF_BITS_LENGTH)))
// 这个宏，将b的左边设置成n
#define RGET(b) (RMASK & b)
// 这个宏得到b的右边的值
#define LGET(b) ((LMASK & b) >> HALF_BITS_LENGTH)
// 这个宏得到b的左边的值
#define GRIDW 3
// 这个数字表示将帅移动范围的行宽度。

int general_main()
{
    unsigned char b;
    for(LSET(b, 1); LGET(b) <= GRIDW * GRIDW; LSET(b, (LGET(b) + 1)))
        for(RSET(b, 1); RGET(b) <= GRIDW * GRIDW; RSET(b, (RGET(b) + 1)))
            if(LGET(b) % GRIDW != RGET(b) % GRIDW)
                printf("A = %d, B = %d\n", LGET(b), RGET(b));
    
    return 0;
}

//algorithm2:
struct {
    unsigned char a:4;
    unsigned char b:4;
}i;
void general_main2(){
    for (i.a = 1; i.a<9; i.a++)
        for (i.b = 1; i.b<9; i.b++)
            if (i.a % 3 == i.b % 3)
                printf("A = %d, B = %d\n", i.a, i.b);
}




#endif
