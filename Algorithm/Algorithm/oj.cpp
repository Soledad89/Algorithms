#include <stack>
#include <list>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <bitset>
#include <map>
#include <set>
#include <unordered_set>
#include <queue>
#include <exception>
#include <assert.h>
#include <math.h>
#include <string.h>
//#include "algorithms.h"
using namespace std;

void Permutation(char* pStr, char* pBegin);

void Permutation(char* pStr)
{
    if(pStr == NULL)
        return;
    
    Permutation(pStr, pStr);
}

int nPermu;
void Permutation(char* s, char* cur)//pStr指向整个字符串的第一个字符，pBegin指向当前我们做排列操作的字符串的第一个字符
{
    if(*cur == '\0')
    {   //static int nPermu = 0; //可以在这里面定义一个静态变量
        printf("%d: ", nPermu);
        printf("%s\n", s);
        nPermu++;
    }
    else
    {
        for(char* p = cur; *p != '\0'; ++ p)
            //每一次递归，从pBegin向后扫描每一个字符，在交换pBegin和pCh之后，再对pBegin后面的字符串递归的排列操作
        {
            char temp = *p;
            *p = *cur;
            *cur = temp;
            
            Permutation(s, cur + 1);
            
            temp = *p;
            *p = *cur;
            *cur = temp;
        }
    }
}

int main(void)
{
    std::string s = "aba";
    std::sort(s.begin(), s.end());
    do {
        std::cout << s << '\n';
    } while(std::next_permutation(s.begin(), s.end()));
    
    char ss[] = "abcd";
    Permutation(ss);
    int a = 12344;
    string atr = to_string(a);
    /* to_string把参数当做是数字来处理
     std::string to_string( int value );

     std::string to_string( long value );

     std::string to_string( long long value );

     std::string to_string( unsigned value );

     std::string to_string( unsigned long value );

     std::string to_string( unsigned long long value );

     std::string to_string( float value );

     std::string to_string( double value );

     std::string to_string( long double value );
     */
    string str1 = "";
    char c = '0' + 2;
    
    char str[] = "abc";

    return 0;
}

//int main() {
//    //main_hanoi();
//    string str("wangbo");
//    sort(str.begin(), str.end());
//    
//    std::vector<int> vec;
//    // VS2008下
//    vec.push_back(1111);
//    vec.push_back(2222);
//    int *pVec = &vec[0];
//    vec.clear();                //clear并不会把容器里面的内容都释放掉，swap才会把容器里面的内容释放掉
//    /*
//     vector的内存不会自动释放的，clear后仍然占用那块内存
//     找一本合格的关于C++标准库的书，会有很详细的介绍
//     
//     C++11提供了shrink_to_fit方法显式释放内存，如果你一定要释放内存，在clear或者erase后进行shrink操作
//    */
//    std::cout<<vec.capacity()<<std::endl;// 2
//    
//    if( vec.capacity() > 0 )
//    {
//        std::cout<<*pVec<<std::endl; //1111
//        std::cout<<*(pVec+1)<<std::endl;//2222
//    }
//    return 0;
//}


/*
void rotateMatrix(vector<vector<int> > &matrix) {
    reverse(matrix.begin(), matrix.end());
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = i + 1; j < matrix[i].size(); ++j)
            swap(matrix[i][j], matrix[j][i]);
    }
}

bool matrixequal(vector<vector<int> > matrix1, vector<vector<int> > matrix2, int N) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++ )
            if (matrix1[i][j] != matrix2[i][j])
                return false;
    return true;
}

bool rotate(vector<vector<int> > matrix, int N) {
    if (N % 2 == 1) {
        
    }
    return false;
}

int main(){
    string str1 = "wangbo";
    int count = 12;
    string str2 = str1 + to_string(count);
    
    int num;
    cin >> num;
    while (num--) {
        int N;
        cin >> N;
        bool flag = false;
        vector<vector<int> > matrix1(N, vector<int>(N,0));
        vector<vector<int> > matrix2(N, vector<int>(N,0));
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                cin >> matrix1[i][j];
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                cin >> matrix2[i][j];
        
        for (int i = 0; i < 4; i++) {
            rotateMatrix(matrix1);
            if (matrixequal(matrix1, matrix2, N)) {
                cout << "Yes" << endl;
                flag = true;
                break;
            }
        }
        if (!flag)
            cout << "No" << endl;
    }
    return 0;
    
}
*/
//
//
//int main24() {
//    int num;
//    cin >> num;
//    int* a = new int[num];
//    for (int i = 0; i < num; i++ ) {
//        cin >> a[i];
//    }
//    return 0;
//    
//}
//
//int main23() {
//    float x0, y0, r;
//    
//    while (cin >> x0 >> y0 >> r ) {
//        int resultx = 0, resulty = 0;
//    int xmax = (int)(x0 + r), xmin = (int)(x0 - r), ymax = (int)(y0 + r), ymin = (int) (y0 - r);
//    int max = 0;
//    for (int i = xmin; i <= xmax; i++) {
//        for (int j = ymin; j <= ymax; j++) {
//            float distance = (i - x0)*(i - x0) + (j - y0)*(j - y0);
//            if (distance > r * r)
//                continue;
//            if (distance > max) {
//                max = distance;
//                resultx = i;
//                resulty = j;
//            }
//            else if (abs(distance - max) <= 10e-7) {
//                if (i > resultx) {
//                    resultx = i;
//                    resulty = j;
//                }else if (i == resultx) {
//                    if (j > resulty)
//                        resulty = j;
//                }
//            }
//            
//        }
//    }
//    cout << resultx << ' ' << resulty << endl;
//    }
//    return 0;
//}
//
//
//
//
//int partition(int* A, int left, int right) {
//    int pivot = A[left];        //swap(A[left], A[left + rand() % (right - left)]);
//    int i = left;
//    for (int j = left + 1; j <= right; j++)
//        if (A[j] <= pivot)
//            swap(A[++i], A[j]);
//    swap(A[left], A[i]);
//    return i;
//}
//void quickSort (int* A, int lo, int hi ) {
//    if ( lo < hi ) {
//        int mi = partition( A, lo, hi);
//        quickSort ( A, lo, mi - 1 );
//        quickSort ( A, mi + 1, hi );
//    }
//}
//
//int main22() {
//    int A[] = {4, 3, 6, 3, 7, 5, 8, 1};
//    quickSort(A , 0, sizeof(A) / sizeof(int) - 1);
//    for (int i = 0; i < sizeof(A) / sizeof(int); i++)
//        cout << A[i] <<endl;
//    return 0;
//}
//    
//    
//template<typename T>
//class mystack {
//private:
//    stack<T> s;
//    
//public:
//    void Push(T t) {
//        if (Isempty() || t > Top())
//            s.push(t);
//        else {
//            stack<T> tmp;
//            while (!s.empty() && t < s.top()) {
//                tmp.push(s.top());
//                s.pop();
//            }
//            s.push(t);
//            while (!tmp.empty()) {
//                s.push(tmp.top());
//                tmp.pop();
//            }
//        }
//        
//    }
//    
//    T Top() {
//        return s.top();
//    }
//    
//    void Pop() {
//        s.pop();
//    }
//    
//    bool Isempty() {
//        return s.empty();
//    }
//    
//    
//};
//
//int main21() {
//    mystack<int>  ms;
//    ms.Push(1);
//    ms.Push(2);
//    ms.Push(3);
//    ms.Push(0);
//    cout<<ms.Top()<<endl;
//    ms.Pop();
//    ms.Push(8);
//    ms.Push(9);
//    ms.Push(5);
//    ms.Pop();
//    ms.Pop();
//    ms.Pop();
//    cout<<ms.Top()<<endl;
//    return 0;
//}
//
//
//
//
//
//
//int lds(int A[], int n){
//    int *f = new int[n];
//    int len = 1;
//    for(int i=0; i<n; ++i){
//        f[i] = 1;
//        for(int j=0; j<i; ++j)
//            if(A[j] > A[i] && f[j]+1>f[i])
//                f[i] = f[j] + 1;
//        if(f[i]>len)
//            len = f[i];
//    }
//    delete[] f;
//    return len;
//}
//
//
//int main20() {
//    int m, n;
//    cin >> m;
//    while (m--) {
//        cin >> n;
//        int* height = new int[n];
//        for (int i = 0; i < n; i++) {
//            cin >> height[i];
//        }
//        cout << lds(height, n) << endl;
//    }
//    return 0;
//}
//
//
//
//
//
//string zipString(string iniString) {
//    // write code here
//    char c = iniString[0];
//    int num = (int)iniString.size();
//    int count = 1;
//    string result;
//    char str[4];
//    for (int i = 1; i < num; i++) {
//        if (iniString[i] == c)
//            count++;
//        else {
//            result += c + to_string(count);
//            c = iniString[i];
//            count = 1;
//            
//        }
//
//    }
//    result += c + to_string(count);
//    
//    return result.size() >= num ? iniString : result;
//    
//    
//}
//
//int main18() {
//
//    string s = "bob";
//    string result = zipString(s);
//    
//    return 0;
//}
//
///*
//int main16() {
//    vector<vector<int> > matrix1 = {{1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15},{16,17,18,19,20},{21,22,23,24,25}};
//    vector<vector<int> > matrix = {{1,1}};
//
//    vector<int> tmp = {1, 2, 3, 4};
//    int m = lower_bound(tmp.begin(), tmp.end(), 1) - tmp.begin();
//    vector<vector<int> > matrix3 = {{1, 4}, {2, 5}};
//    bool b = searchMatrix(matrix1, 19);
//
//    return 0;
//}
//
//*/
//
//
/////////////
//int longestConsecutive2(vector<int>& nums) {
//    int n = (int)nums.size();
//    if ( n == 0 || n == 1)
//        return n;
//    unordered_set<int>  setnum;
//    setnum.insert(nums.begin(), nums.end());
//    
////    for (int i = 0; i < n; i++) {
////        setnum.insert(nums[i]);
////    }
//    
//    int max = 0;
//    int count;
//    for (int i = 0; i < n; i++) {
//        count = 1;
//        int curincrease = nums[i] + 1;
//        while(setnum.find(curincrease) != setnum.end()) {
//            count++;
//            setnum.erase(curincrease);
//            curincrease++;
//            
//        }
//        
//        int curdecrease = nums[i] - 1;
//        while (setnum.find(curdecrease) != setnum.end()) {
//            count++;
//            setnum.erase(curdecrease);
//            curdecrease--;
//            
//        }
//        
//        if (count > max)
//            max = count;
//    }
//    return max;
//}
//
//int longestConsecutive(vector<int>& nums) {
//    int n = nums.size();
//    if ( n == 0 || n == 1)
//        return n;
//    sort(nums.begin(), nums.end());
//    int max = 0;
//    int cur = 1;
//    for (int i = 1; i < n; i++) {
//        if ( nums[i] == nums[i-1]) {
//            if ( i == n - 1 && cur > max)
//                max = cur;
//            continue;
//        }
//        
//        if (nums[i] == nums[i - 1] + 1 ) {
//            cur++;
//            if (i == n-1 && cur > max)
//                max = cur;
//        } else
//        {
//            if ( cur > max) {
//                max = cur;
//            }
//            cur = 1;
//        }
//    }
//    return max;
//}
//
//int main13() {
//    vector<char> s = {'a', 'b'};
//    vector<vector<char> > vv;
//    vv.push_back(s);
//    s = {'c','d'};
//    vv.push_back(s);
//    
//    string str = "cab";
//    vector<string> vString;
//    vString.push_back(str);
//    
//    //findWords(vv, vString);
//    
//    vector<int> nums = {9,1,-3,2,4,8,3,-1,6,-2,-4,7};
//    int m = longestConsecutive2(nums);
//    return 0;
//}
//
//
//
///*
// Problem Description
// The highest building in our city has only one elevator. A request list is made up with N positive numbers. The numbers denote at which floors the elevator will stop, in specified order. It costs 6 seconds to move the elevator up one floor, and 4 seconds to move down one floor. The elevator will stay for 5 seconds at each stop.
// 
// For a given request list, you are to compute the total time spent to fulfill the requests on the list. The elevator is on the 0th floor at the beginning and does not have to return to the ground floor when the requests are fulfilled.
// Input
// There are multiple test cases. Each case contains a positive integer N, followed by N positive numbers. All the numbers in the input are less than 100. A test case with N = 0 denotes the end of input. This test case is not to be processed.
// Output
// Print the total time on a single line for each test case.
// Sample Input
// 1 2
// 3 2 3 1
// 0
// */
//
//int main12() {
//    int up = 6;
//    int down = 4;
//    int wait = 5;
//    int num = 0;
//
//    int prev;       //initial pos
//    int cur;
//    int sum;        //sum time
//    while (cin >> num) {
//        prev = 0; cur =0; sum = 0;
//        if (num == 0) break;
//        while (num--) {
//            cin >> cur;
//            if (cur > prev) {
//                sum += (cur - prev) * up + wait;
//                prev = cur;
//            }
//            else if (cur < prev){
//                sum += (prev - prev) * down + wait;
//                prev = cur;
//            }
//        }
//        cout << sum << endl;
//    }
//    return 0;
//}
///*
// Problem Description : right most digit
// Given a positive integer N, you should output the most right digit of N^N.
// Input
// The input contains several test cases. The first line of the input is a single integer T which is the number of test cases. T test cases follow.
// Each test case contains a single positive integer N(1<=N<=1,000,000,000).
// Output
// For each test case, you should output the rightmost digit of N^N.
// Sample Input
// 2
// 3
// 4
// Sample Output
// 7
// 6
// 
// Hint
// 
// In the first case, 3 * 3 * 3 = 27, so the rightmost digit is 7.
// In the second case, 4 * 4 * 4 * 4 = 256, so the rightmost digit is 6.
// */
//
//int main_rightmostdigit()
//{
//    int n;
//    cin>>n;
//    while (n--)
//    {
//        int m;
//        cin>>m;
//        int a[10][5]={      //如99^99 可转化为求99个9相乘后最低位是什么，而同一个数连乘结果是具有周期性的，周期不大于10,这里是5
//            {0,0,0,0,0},
//            {1,1,1,1,1},
//            {6,2,4,8,6},
//            {1,3,9,7,1},
//            {6,4,6,4,6},
//            {5,5,5,5,5},
//            {6,6,6,6,6},
//            {1,7,9,3,1},
//            {6,8,4,2,6},
//            {1,9,1,9,1}};
//        cout<<a[m%10][m%4]<<endl;
//    }
//    return 0;
//}
//
////更简洁
//int main_oj_rightmostdigit()
//{
//    int n; int s,a,b,num;
//    scanf("%d",&n);
//    while(n--)
//    {
//        
//        scanf("%d",&num);
//        a=num%10;
//        b=num%4;
//        if(b==0)
//            b=4;
//        printf("%d\n",(int)pow((double)a,b)%10);
//    }
//    return 0;
//}
//
//
//
//
////一般做法：fib
//
///*
// Problem Description
// There are another kind of Fibonacci numbers: F(0) = 7, F(1) = 11, F(n) = F(n-1) + F(n-2) (n>=2).
// Input
// Input consists of a sequence of lines, each containing an integer n. (n < 1,000,000).
// Output
// Print the word "yes" if 3 divide evenly into F(n).
// Print the word "no" if not.
// */
//
//int fibllic1(int n)  {
//    int a = 7;      //初始值都可以自己确定
//    int b = 11;
//    
//    if (n == 0) return a;
//    if (n == 1) return b;
//    
//    for (int i = 1; i < n; i++) {
//        b = a + b;
//        a = b - a;
//    }
//    return b;
//}
//
//int main_wangbo()  {
//    int tmp;
//    
//    while (cin >> tmp) {
//        tmp = fibllic1(tmp);
//        if (tmp % 3 == 0)
//            cout << "yes"<<endl;
//        else
//            cout << "no" << endl;
//    }
//    return 0;
//    
//}
//
///*
// 首先你要知道这个公式 (a+b)%c=(a%c+b%c)%c
// 然后 从F(0)=7 F(1)=11开始 我们只要看每一个数对3取余的结果就好了
// 设G(X) = F(X)%3
// 那么就有 G(0)=1,G(1)=2 G(N)=(G(N-1)+G(N-2))%3  //取余肯定有重复的
// 然后把前面几项你就会看到规律 1 2 0 2 2 1 0 1 1 2 0 2 2 ……
// 所以是以8为周期的 然后第3项和第7项为0 所以就有了你给的代码啦
// */
//int main_oj()
//{
//    int n,c;
//    while(scanf("%d",&n)!=EOF)
//    {
//        c = n%8;
//        if(c==2||c==6) printf("yes\n");
//        else printf("no\n");
//    }
//    return 0;
//}
//
///*
// 求小公倍数
// */
//
//int gcdwangbo(int m, int n) {
//    if ( 0 == m)    return n;
//    if ( 0 == n)    return m;
//    if (m > n)
//        return gcdwangbo(m % n, n);
//    else
//        return gcdwangbo(m, n % m);
//}
//int main10() {
//    int m, n;
//    while (cin >> m >> n) {
//        cout << n / gcdwangbo(m,n) * m  <<endl;
//    }
//    return 0;
//}
//
//
///*
// 
// */
//
//int main9() {
//    string str;
//    while (cin >> str) {
//        int pos = 0;
//        vector<int> result;
//        int size = (int)str.size();
//        for(int i = 0; i < size; i++)
//        {
//            pos = (int)str.find('5',i);
//            if(pos < size)
//            {
//                string s = str.substr(i,pos-i);
//                int si = atoi(s.c_str());           //将字符串转化为整数,将整数转化为字符串可以用to_string
//                result.push_back(si);
//                i = pos;
//            }
//        }
//        sort(result.begin(), result.end());
//        for (vector<int>::iterator iter = result.begin(); iter != result.end(); iter++)
//            cout << *iter << ' ';
//    }
//    return 0;
//}
//
//#include<stdio.h>
//#define mm 10000
//int main7()
//{
//    int  p[mm],i,j,k,n;
//    char a[mm];
//    while(1)
//    {
//        i=0;n=0,k=0;
//        while((a[i]=getchar())!='\n'&&a[i]!=EOF)
//            i++;
//        if(a[i]==EOF) break;
//        for(j=0;j<i;j++)  	                     //p[n]分为后的各个数
//            if(a[j]!='5')
//                k=k*10+a[j]-'0';
//            else if(a[j+1]!='5')
//            {
//                p[n]=k;
//                k=0;
//                n++;
//            }
//        if(a[i-1]!='5')
//        {
//            p[n]=k;
//            n=n+1;
//        }
//        for(j=0;j<n;j++)       //排序
//            for(i=0;i<n-j-1;i++)
//                if(p[i]>p[i+1])
//                {
//                    k=p[i];
//                    p[i]=p[i+1];
//                    p[i+1]=k;
//                }
//        /*if(a[0]!='5')
//         printf("%d ",p[0]);
//         for(j=1;j<n-1;j++)
//         printf("%d ",p[j]);
//         printf("%d\n",p[n-1]);
//         */
//        if(a[0]!='5') j=0;
//        else j=1;
//        printf("%d",p[j++]);
//        for(;j<n;j++)
//            printf(" %d",p[j]);
//        printf("\n");
//    }
//    return 0;
//    
//}
//
//
///*
// 求若干数的最小公倍数
// */
//int gcd12(int a, int b)
//{
//    while (true) {
//        if (0 == a) return b;
//        if (0 == b) return a;
//        if (a > b)         a %= b;
//        else               b %= a;
//    }
//}
//
//int gcd32(int m, int n )
//{
//    return m / gcd12(m, n) * n;
//}
//
//
//int main5() {
//    int num;
//    cin >> num;
//    for (int i = 0; i < num; i++) {
//        int size;
//        cin >> size;
//        int partialGcd = 1;
//        
//        int x;
//        for (int j = 0; j < size; j++) {
//            cin >> x;
//            partialGcd = gcd32(partialGcd, x);
//        }
//        cout << partialGcd << endl;
//    }
//    return 0;
//}
//
//
//
//
///*
// 对学生进行排队,按照成绩、学号、姓名
// */
//
//#define BUFFER 256
//struct student {
//    string number;
//    string name;
//    int score;
//    student(string n, string nm, int s) : number(n), name(nm), score(s) {}
//};
//
//bool compare1(student &s1, student &s2) {
//    string str1 = s1.number;
//    string str2 = s2.number;
//    return str1 < str2;
//        
//}
//bool compare2(student &s1, student &s2) {
//    string str1 = s1.name;
//    string str2 = s2.name;
//    if (str1 < str2)
//        return true;
//    else if (str1 > str2)
//        return false;
//    else
//        return s1.number < s2.number;
//}
//
//bool compare3(student & s1, student & s2) {
//    if (s1.score < s2.score)
//        return true;
//    else if (s1.score > s2.score)
//        return false;
//    else
//        return s1.number < s2.number;
//}
//int main4() {
//    int n, c;
//    int caseIndex = 0;
//    string number;
//    string name;
//    int score;
//    
//    while ( cin >> n >> c ) {
//        if (n == 0)
//            break;
//        
//        caseIndex ++;
//
//        vector<student> vStudent;
//        for (int i = 0; i < n ; i++) {
//            cin >> number >> name >> score;
//            vStudent.push_back(student(number, name, score));
//        }
//        switch (c) {
//            case 1:
//                sort(vStudent.begin(), vStudent.end(),compare1);
//                break;
//            case 2:
//                sort(vStudent.begin(), vStudent.end(),compare2);
//                break;
//            case 3:
//                sort(vStudent.begin(), vStudent.end(),compare3);
//                break;
//            default:
//                break;
//        }
//        
//        cout << "Case " << caseIndex << ':' <<endl;
//        vector<student>::iterator iter;
//        for (iter = vStudent.begin(); iter != vStudent.end(); iter++)
//        {
//            cout << iter->number << ' ' << iter->name <<' ' << iter->score <<endl;
//            
//        }
//        
//        
//        
//    }
//    return 0;
//}
//
///*
// 求若干点集的最小包含矩阵
// */
//
//int main3() {
//    int x, y;
//    int xmin = 232, xmax = -232, ymin = 232, ymax = -232;
//    bool flag = false;
//    while (cin >> x >> y) {
//        if (x == 0 && y == 0 && flag == true)
//            break;
//        
//        if (x == 0 && y == 0) {
//            cout << xmin <<' ' << ymin<< ' ' << xmax<< ' ' << ymax << endl;
//            xmin = 232, xmax = -232, ymin = 232, ymax = -232;
//            flag = true;
//            continue;
//        }
//        
//
//        if (x < xmin)
//            xmin = x;
//        if (x > xmax)
//            xmax = x;
//        if (y < ymin)
//            ymin = y;
//        if (y > ymax)
//            ymax = y;
//        
//        flag = false;
//    }
//    return 0;
//}
//
///*
// 统计若干字符在特定字符串中出现的频率
// */
//int main2() {
//    int m;
//    char str1[6];
//    memset(str1, '0', sizeof(char)*5);
//    char str2[81];
//    
//    int hashtable[BUFFER];
//
//    while (gets(str1)) { //gets()可以读入一整行，以\n结束
//        if (str1[0] == '#') //输入的第一个字符是‘#’时结束
//            break;
//        
//        memset(hashtable, 0, sizeof(int) * BUFFER);
//        memset(str2, '0', sizeof(char)*80);
//        gets(str2);
//        m = (int)strlen(str2);
//        for (int i = 0; i < m; i++) {
//            hashtable[str2[i]]++;
//        }
//        
//        int n = (int)strlen(str1);
//        for (int j = 0; j < n; j++) {
//            cout << str1[j] << ' ' << hashtable[str1[j]] <<endl;
//        }
//        
//        
//    }
//    return 0;
//}
//
///*
// 求最长子串，其和为0
// */
//int main1() {
//    vector<int> vec;
//    int tmp;
//    while (cin >> tmp) {
//        vec.push_back(tmp);
//    }
//    
//    int num = (int)vec.size();
//    vector<int> sum;
//    sum.push_back(0);
//    int parsum = 0;
//    for (int i = 0; i < num; i++) {
//        sum.push_back(parsum + vec[i]);
//        parsum = parsum + vec[i];
//    }
//    
//    int start = 0, end = 0, result = 0, max = -1;
//    for (int i = 0; i < num+1; i++) {
//        int tmp = sum[i];
//        int j = num;
//        while (i < j) {
//            if (tmp == sum[j]) {
// 
//                result = j - i + 1;
//                if (result > max) {
//                    max = result;
//                    start = i;
//                    end = j;
//                }
//            }
//            j--;
//        }
//    }
//    for (int k = start; k < end; k++)
//        cout << vec[k] << ' ';
//    return 0;
//}
//
//
//void function1(int m, int n) {
//    
//}
//
//int main_() {
//    int num;
//    cin >> num;
//    for (int i = 0; i < num; i ++) {
//        int size;
//        cin >> size;
//        
//        vector<int> vec(size);
//        int tmp;
//        for (int j = 0; j < size; j++) {
//            cin >> tmp;
//            vec[j] = tmp;
//        }
//        
//        int m = 0, n = 0;
//        function1(m, n);
//        
//        vector<int> result(3, 1);
//        cout << "Case: " << i << '\n' << result[0] <<' ' << result[1] << endl;
//    }
//    /*
//     int a[7]={1,2,3,4,5,6,7};
//     vector<int> ivector(a,a+7);//vector的赋值并不可以像数组一样方便的用花括号方便的完成赋值，这里借用了数组来初始化这个vector，初始化方
//     //式vector<elementType> intvec(begin,end);这样可以用起来看上去还是比较习惯的。
//     */
//    return 0;
//}
//
//int main__() {
//    int start, end;
//    while (cin >> start >> end) {
//        int cur;
//        vector<int> vec;
//        vec.reserve(20);
//        for (cur = start; cur <= end; cur++) {
//            int sum1, sum2, sum3;
//            int old = cur;
//            sum1 = pow(old / 100, 3);
//            old = old % 100;
//            sum2 = pow(old / 10, 3);
//            old = old % 10;
//            sum3 = pow(old, 3);
//            if (cur == (sum1 + sum2 + sum3)) {
//                vec.push_back(cur);
//            }
//        }
//        int num = (int)vec.size();
//        if (num == 0) {
//            cout << "no"<< endl;
//            continue;}
//        for (int i = 0; i < num; i++) {
//            if (i != num-1)
//                cout << vec[i] << ' ';
//            else
//                cout << vec[i] << endl;
//        }
//    }
//    return 0;
//}
//
//int main___() {
//    int n, m;
//    vector<int> a = {1,2,3};
//    while (cin >> n >> m) {
//        float sum = n;
//        float old = n;
//        for (int i = 1; i < m; i++) {
//            float tmp = sqrt(old);
//            sum = sum + tmp;
//            old = tmp;
//        }
//        printf("%.2f", sum);
//    }
//    return 0;
//}
//
//int main______() {
//    //vector<int> a = {1,2,3};
//    
//    string str;
//    while (cin >> str){
//        cout << "Case: " << str << endl;
//    }
//    return 0;
//}
