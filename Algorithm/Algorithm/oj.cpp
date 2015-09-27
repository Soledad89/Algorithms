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
#include <queue>
#include <exception>
#include <assert.h>
#include <math.h>
#include <string.h>

using namespace std;

//一般做法：fib
int fibllic(int n)  {
    int a = 7;      //初始值都可以自己确定
    int b = 11;
    
    if (n == 0) return a;
    if (n == 1) return b;
    
    for (int i = 1; i < n; i++) {
        b = a + b;
        a = b - a;
    }
    return b;
}
/*
 Problem Description
 There are another kind of Fibonacci numbers: F(0) = 7, F(1) = 11, F(n) = F(n-1) + F(n-2) (n>=2).
 Input
 Input consists of a sequence of lines, each containing an integer n. (n < 1,000,000).
 Output
 Print the word "yes" if 3 divide evenly into F(n).
 Print the word "no" if not.
 */
 
int main()  {
    int tmp;
    
    while (cin >> tmp) {
        tmp = fibllic(tmp);
        if (tmp % 3 == 0)
            cout << "yes"<<endl;
        else
            cout << "no" << endl;
    }
    return 0;
    
}

int main11()
{
    int n,c;
    while(scanf("%d",&n)!=EOF)
    {
        c = n%8;
        if(c==2||c==6) printf("yes\n");
        else printf("no\n");
    }
    return 0;
}

/*
 求小公倍数
 */

int gcdwangbo(int m, int n) {
    if ( 0 == m)    return n;
    if ( 0 == n)    return m;
    if (m > n)
        return gcdwangbo(m % n, n);
    else
        return gcdwangbo(m, n % m);
}
int main10() {
    int m, n;
    while (cin >> m >> n) {
        cout << n / gcdwangbo(m,n) * m  <<endl;
    }
    return 0;
}


/*
 
 */

int main9() {
    string str;
    while (cin >> str) {
        int pos = 0;
        vector<int> result;
        int size = (int)str.size();
        for(int i = 0; i < size; i++)
        {
            pos = (int)str.find('5',i);
            if(pos < size)
            {
                string s = str.substr(i,pos-i);
                int si = atoi(s.c_str());           //将字符串转化为整数
                result.push_back(si);
                i = pos;
            }
        }
        sort(result.begin(), result.end());
        for (vector<int>::iterator iter = result.begin(); iter != result.end(); iter++)
            cout << *iter << ' ';
    }
    return 0;
}

#include<stdio.h>
#define mm 10000
int main7()
{
    int  p[mm],i,j,k,n;
    char a[mm];
    while(1)
    {
        i=0;n=0,k=0;
        while((a[i]=getchar())!='\n'&&a[i]!=EOF)
            i++;
        if(a[i]==EOF) break;
        for(j=0;j<i;j++)  	                     //p[n]分为后的各个数
            if(a[j]!='5')
                k=k*10+a[j]-'0';
            else if(a[j+1]!='5')
            {
                p[n]=k;
                k=0;
                n++;
            }
        if(a[i-1]!='5')
        {
            p[n]=k;
            n=n+1;
        }
        for(j=0;j<n;j++)       //排序
            for(i=0;i<n-j-1;i++)
                if(p[i]>p[i+1])
                {
                    k=p[i];
                    p[i]=p[i+1];
                    p[i+1]=k;
                }
        /*if(a[0]!='5')
         printf("%d ",p[0]);
         for(j=1;j<n-1;j++)
         printf("%d ",p[j]);
         printf("%d\n",p[n-1]);
         */
        if(a[0]!='5') j=0;
        else j=1;
        printf("%d",p[j++]);
        for(;j<n;j++)
            printf(" %d",p[j]);
        printf("\n");
    }
    return 0;
    
}


/*
 求若干数的最小公倍数
 */
int gcd1(int a, int b)
{
    while (true) {
        if (0 == a) return b;
        if (0 == b) return a;
        if (a > b)         a %= b;
        else               b %= a;
    }
}

int gcd3(int m, int n )
{
    return m / gcd1(m, n) * n;
}


int main5() {
    int num;
    cin >> num;
    for (int i = 0; i < num; i++) {
        int size;
        cin >> size;
        int partialGcd = 1;
        
        int x;
        for (int j = 0; j < size; j++) {
            cin >> x;
            partialGcd = gcd3(partialGcd, x);
        }
        cout << partialGcd << endl;
    }
    return 0;
}




/*
 对学生进行排队,按照成绩、学号、姓名
 */

#define BUFFER 256
struct student {
    string number;
    string name;
    int score;
    student(string n, string nm, int s) : number(n), name(nm), score(s) {}
};

bool compare1(student &s1, student &s2) {
    string str1 = s1.number;
    string str2 = s2.number;
    return str1 < str2;
        
}
bool compare2(student &s1, student &s2) {
    string str1 = s1.name;
    string str2 = s2.name;
    if (str1 < str2)
        return true;
    else if (str1 > str2)
        return false;
    else
        return s1.number < s2.number;
}

bool compare3(student & s1, student &s2) {
    if (s1.score < s2.score)
        return true;
    else if (s1.score > s2.score)
        return false;
    else
        return s1.number < s2.number;
}
int main4() {
    int n, c;
    int caseIndex = 0;
    string number;
    string name;
    int score;
    
    while ( cin >> n >> c ) {
        if (n == 0)
            break;
        
        caseIndex ++;

        vector<student> vStudent;
        for (int i = 0; i < n ; i++) {
            cin >> number >> name >> score;
            vStudent.push_back(student(number, name, score));
        }
        switch (c) {
            case 1:
                sort(vStudent.begin(), vStudent.end(),compare1);
                break;
            case 2:
                sort(vStudent.begin(), vStudent.end(),compare2);
                break;
            case 3:
                sort(vStudent.begin(), vStudent.end(),compare3);
                break;
            default:
                break;
        }
        
        cout << "Case " << caseIndex << ':' <<endl;
        vector<student>::iterator iter;
        for (iter = vStudent.begin(); iter != vStudent.end(); iter++)
        {
            cout << iter->number << ' ' << iter->name <<' ' << iter->score <<endl;
            
        }
        
        
        
    }
    return 0;
}

/*
 求若干点集的最小包含矩阵
 */

int main3() {
    int x, y;
    int xmin = 232, xmax = -232, ymin = 232, ymax = -232;
    bool flag = false;
    while (cin >> x >> y) {
        if (x == 0 && y == 0 && flag == true)
            break;
        
        if (x == 0 && y == 0) {
            cout << xmin <<' ' << ymin<< ' ' << xmax<< ' ' << ymax << endl;
            xmin = 232, xmax = -232, ymin = 232, ymax = -232;
            flag = true;
            continue;
        }
        

        if (x < xmin)
            xmin = x;
        if (x > xmax)
            xmax = x;
        if (y < ymin)
            ymin = y;
        if (y > ymax)
            ymax = y;
        
        flag = false;
    }
    return 0;
}

/*
 统计若干字符在特定字符串中出现的频率
 */
int main2() {
    int m;
    char str1[6];
    memset(str1, '0', sizeof(char)*5);
    char str2[81];
    
    int hashtable[BUFFER];

    while (gets(str1)) { //gets()可以读入一整行，以\n结束
        if (str1[0] == '#') //输入的第一个字符是‘#’时结束
            break;
        
        memset(hashtable, 0, sizeof(int) * BUFFER);
        memset(str2, '0', sizeof(char)*80);
        gets(str2);
        m = (int)strlen(str2);
        for (int i = 0; i < m; i++) {
            hashtable[str2[i]]++;
        }
        
        int n = (int)strlen(str1);
        for (int j = 0; j < n; j++) {
            cout << str1[j] << ' ' << hashtable[str1[j]] <<endl;
        }
        
        
    }
    return 0;
}

/*
 求最长子串，其和为0
 */
int main1() {
    vector<int> vec;
    int tmp;
    while (cin >> tmp) {
        vec.push_back(tmp);
    }
    
    int num = (int)vec.size();
    vector<int> sum;
    sum.push_back(0);
    int parsum = 0;
    for (int i = 0; i < num; i++) {
        sum.push_back(parsum + vec[i]);
        parsum = parsum + vec[i];
    }
    
    int start = 0, end = 0, result = 0, max = -1;
    for (int i = 0; i < num+1; i++) {
        int tmp = sum[i];
        int j = num;
        while (i < j) {
            if (tmp == sum[j]) {
 
                result = j - i + 1;
                if (result > max) {
                    max = result;
                    start = i;
                    end = j;
                }
            }
            j--;
        }
    }
    for (int k = start; k < end; k++)
        cout << vec[k] << ' ';
    return 0;
}


void function1(int m, int n) {
    
}

int main_() {
    int num;
    cin >> num;
    for (int i = 0; i < num; i ++) {
        int size;
        cin >> size;
        
        vector<int> vec(size);
        int tmp;
        for (int j = 0; j < size; j++) {
            cin >> tmp;
            vec[j] = tmp;
        }
        
        int m = 0, n = 0;
        function1(m, n);
        
        vector<int> result(3, 1);
        cout << "Case: " << i << '\n' << result[0] <<' ' << result[1] << endl;
    }
    /*
     int a[7]={1,2,3,4,5,6,7};
     vector<int> ivector(a,a+7);//vector的赋值并不可以像数组一样方便的用花括号方便的完成赋值，这里借用了数组来初始化这个vector，初始化方
     //式vector<elementType> intvec(begin,end);这样可以用起来看上去还是比较习惯的。
     */
    return 0;
}

int main__() {
    int start, end;
    while (cin >> start >> end) {
        int cur;
        vector<int> vec;
        vec.reserve(20);
        for (cur = start; cur <= end; cur++) {
            int sum1, sum2, sum3;
            int old = cur;
            sum1 = pow(old / 100, 3);
            old = old % 100;
            sum2 = pow(old / 10, 3);
            old = old % 10;
            sum3 = pow(old, 3);
            if (cur == (sum1 + sum2 + sum3)) {
                vec.push_back(cur);
            }
        }
        int num = (int)vec.size();
        if (num == 0) {
            cout << "no"<< endl;
            continue;}
        for (int i = 0; i < num; i++) {
            if (i != num-1)
                cout << vec[i] << ' ';
            else
                cout << vec[i] << endl;
        }
    }
    return 0;
}

int main___() {
    int n, m;
    vector<int> a = {1,2,3};
    while (cin >> n >> m) {
        float sum = n;
        float old = n;
        for (int i = 1; i < m; i++) {
            float tmp = sqrt(old);
            sum = sum + tmp;
            old = tmp;
        }
        printf("%.2f", sum);
    }
    return 0;
}

int main______() {
    //vector<int> a = {1,2,3};
    
    string str;
    while (cin >> str){
        cout << "Case: " << str << endl;
    }
    return 0;
}
