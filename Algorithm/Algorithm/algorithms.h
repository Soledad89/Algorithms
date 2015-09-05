//
//  Functions.h
//  Algorithm
//
//  Created by 王波 on 15/8/20.
//  Copyright (c) 2015年 wangbo. All rights reserved.
//

#ifndef Algorithm_Functions_h
#define Algorithm_Functions_h
#include <stack>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


//结构定义
struct ListNode {
    int data;
    ListNode* pred;
    ListNode* succ;
    ListNode() {};
    ListNode(int e = 0, ListNode* p = NULL, ListNode* s = NULL):
    data(e), pred(p), succ(s){}
};
//ListNode* header;
//ListNode* trailer;


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

void BitMapSortDemo(int* num)
{
    //为了简单起见，我们不考虑负数
    

    const int BufferLen = 2;      //BufferLen这个值是根据待排序的数据中最大值确
    //待排序中的最大值是14，因此只需要2个Bytes(16个Bit)
    char *pBuffer = new char[BufferLen];
    
    //要将所有的Bit位置为0，否则结果不可预知。
    memset(pBuffer,0,BufferLen);
    for(int i = 0; i < 9; i++)
    {
        //首先将相应Bit位上置为1
        SetBit(pBuffer,num[i]);
    }
    
    //输出排序结果
    for(int i=0; i < BufferLen; i++)//每次处理一个字节(Byte)
    {
        for(int j=0; j< BYTESIZE;j++)//处理该字节中的每个Bit位
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
//算法：减而治之
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


//问题：排序
//算法：quicksort
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

#define MAXINT (1<<31)-1
#define MININT 1<<31
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
int gcdEU(int a, int b)
{
    while (true) {
        if (0 == a) return b;
        if (0 == b) return a;
        if (a > b)         a %= b;
        else               b %= a;
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

//问题: binsearch lower bound
//算法: binary search
int binsearch_lowerbound(int A[], const int x, int lo, int hi){
    while (lo < hi) {
        int mid = (lo + hi)>>1;
        (x < A[mid]) ? mid = hi : lo = mid + 1;
    }
    return lo;
}
int binsearch2(int A[], const int x, int lo, int hi)
{
    while (1 < hi - lo) {
        int mid = (lo + hi) >> 1;
        (x < A[mid])? hi = mid : lo = mid;
    }
    return (x == A[lo]) ? lo : -1;
}
int binsearch(int A[], const int x, int lo, int hi)
{
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        if (x < A[mid])
            hi = mid;
        else if (A[mid] < x)
            lo = mid + 1;
        else
            return mid;
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

double pow_(double x, int n)
{
    double result = 1;
    double tmp = x;
    while (0 < n) {
        if (n & 1)
            result *= tmp;
        n >>= 1;
        tmp *= tmp;
    }
    return result;
    
}

/*
 void reverse(int* A, int lo, int hi) //递归版，recursive
 {
 if(lo < hi)
 {
 std::swap(A[lo], A[hi]);
 reverse(A, lo+1, hi-1)
 }
 }
 */
void reverse(int* A, int lo, int hi) //迭代版，一般用迭代版，以上的递归版效率较低
{
    while (lo < hi)
        std::swap(A[lo++], A[hi--]);
}

void shift(int* A, int n, int k)
{
    k %= n;
    std::reverse(A,A+k);
    std::reverse(A+k, A+n);
    std::reverse(A, A+n);
}

void shuffle( int A[], int n ) {
    while ( 1 < n )
        std::swap ( A[rand() % n], A[--n] );
}

void shuffle( int A[], int lo, int hi )
{  shuffle ( A + lo, hi - lo );  }

void randomArray( int A[], int n, int seed ) {
    srand(seed);
    for ( int i = 0; i < n; i++ )
        A[i] = i;
    shuffle ( A, 0, n / 3 );
    shuffle ( A, 2 * n / 3, n );
}

void print( int A[], int n, int lo, int hi ) {
    bool sorted = true;
    for( int i = 1; i < n; i++ )
        if ( A[i-1] > A[i] )
            sorted = false;
    printf( sorted ? "S: " : " : " );
    for( int i = 0; i < lo; i++ ) printf ( "   ." );
    for( int i = lo; i < hi; i++ ) printf ( "%4d", A[i] );
    for( int i = hi; i < n; i++ ) printf ( "   ." );
    printf ( "\n" );
}

void print( int A[], int n )
{
    print( A, n, 0, n );
}


#endif
