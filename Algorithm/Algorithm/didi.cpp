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
using namespace std;

//在此输入代码




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
