//
//  hihocoder2.cpp
//  Algorithm
//
//  Created by 王波 on 15/9/13.
//  Copyright (c) 2015年 wangbo. All rights reserved.
//

#include <stdio.h>
#include <math.h>
//#include <map>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
#define NUM 1000
void count(vector<int> x, int num, int k, int* c);

int main() {
    int v, m, t;
    //cin >> v >> m >> t;
    string st;
    getline(cin, st);
    
    string st1, st2, st3;
    cin >> st1 >> st2 >> st3;
    int data[3 * NUM];
    int n, size = 0;
    while (cin >> n) {
        data[size++] = n;
    }
    int fchatnum[NUM];
    int cchatnum[NUM];
    int remark[NUM];
    for (int i = 0; i < size; i++){
        if (i%3 == 0)
            fchatnum[i/3] = data[i];
        else if (i%3 == 1)
            cchatnum[i/3] = data[i];
        else
            remark[i/3] = data[i];
    }
    
    //问题1
    vector<int> index1;
    vector<int> index2;
    index1.reserve(NUM);
    index2.reserve(NUM);
    for (int i = 0 ; i < NUM; i++) {
        if (remark[i] == 1)
            index1.push_back(i);
        if (remark[i] == 2)
            index2.push_back(i);
    }
    float p_index1 = index1.size() * 1.0 / NUM;
    float p_index2 = index2.size() * 1.0 / NUM;
    printf("%.3f\n", p_index2);
    
    //问题3
    int index1_X9 = 0;
    int index1_Y9 = 0;
    int n_index1 = (int) index1.size();
    for (vector<int>::iterator iter = index1.begin(); iter != index1.end(); iter++ ) {
        if (fchatnum[*iter] == 9)
            index1_X9++;
        if (cchatnum[*iter] == 9)
            index1_Y9++;
    }
    
    int index2_X9 = 0;
    int index2_Y9 = 0;
    int n_index2 = (int) index2.size();
    for (vector<int>::iterator iter = index2.begin(); iter != index2.end(); iter++ ) {
        if (fchatnum[*iter] == 9)
            index2_X9++;
        if (cchatnum[*iter] == 9)
            index2_Y9++;
    }
    
    //问题2
    
    int num_index2 = (int)index2.size();
    vector<int> fchatnum2;
    fchatnum2.reserve(num_index2);
    for (int i = 0; i < num_index2; i++ )
        fchatnum2.push_back(fchatnum[index2[i]]);
    
    int countFchatnum[11] = {0};
    count(fchatnum2, num_index2, 10, countFchatnum);
    
    for (int i = 1; i < 10; i++) {
        printf("%.3f,", countFchatnum[i] * 1.0 / num_index2);
    }
    printf("%.3f\n", countFchatnum[10] * 1.0 / num_index2);
    
    
    
    
    //问题3
    float pratio1 = p_index1 * index1_X9 / (1.0 * index1.size()) * index1_Y9 / (1.0 * index1.size());
    
    float pratio2 = p_index2 * index2_X9 / (1.0 * index2.size()) * index2_Y9 / (1.0 * index2.size());
    
    printf("%.3f\n", pratio2/(pratio1+pratio2));
    return 0;
    
    
}

void count(vector<int> x, int num, int k, int* c) {
    for (int i = 0; i < num; i ++) {
        c[x[i]]++;
    }
}