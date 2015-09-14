//
//  hihocoder.cpp
//  Algorithm
//
//  Created by 王波 on 15/9/13.
//  Copyright (c) 2015年 wangbo. All rights reserved.
//

#include <stdio.h>
#include <math.h>
//#include <map>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
float distance(vector<float> &a, vector<float> b);
void kthIndex(vector<float>& v, vector<int>& index, int k);

int main() {
    int k, n, mtrain, mtest;
    cin >> k >> n >> mtrain >> mtest;
    vector<vector<float> > trainMatrix;
    trainMatrix.reserve(mtrain);
    char* label = (char*)malloc(sizeof(char) * mtrain);
    memset(label, 0, sizeof(char)*mtrain);
    
    for (int i = 0; i < mtrain; i++) {
        vector<float> vtmp;
        vtmp.reserve(n);
        float f;
        char s;
        for (int j = 0; j < n; j++) {
            cin >> f;
            vtmp.push_back(f);
        }
        cin >> s;
        trainMatrix.push_back(vtmp);
        label[i] = s;
    }

    vector<vector<float> > testMatrix;
    testMatrix.reserve(mtest);
    for (int i = 0; i < mtest; i++) {
        vector<float> vtmp;
        vtmp.reserve(n);
        float f;
        for (int j = 0; j < n; j++){
            cin >> f;
            vtmp.push_back(f);
        }
        testMatrix.push_back(vtmp);
    }
    
    for (int i = 0; i < mtest; i++) {
        vector<float> vDistance;
        vDistance.reserve(mtrain);
        for (int j = 0; j < mtrain; j++) {
            vDistance.push_back(distance(testMatrix[i], trainMatrix[j]));
        }
        vector<int> index;
        index.reserve(k);
        kthIndex(vDistance, index, k);
        int alpha[4] = {0};
        for (int i = 0; i < k; i++) {
            alpha[label[index[i]] - 'A']++;
        }
        int in, max = -1;
        for (int i = 0; i < 4; i++) {
            if (alpha[i] > max) {
                max = alpha[i];
                in = i;
            }
                
        }
        cout << i + 'A'<< endl;
        
    }
    return 0;
            
}

float distance(vector<float> &a, vector<float> b) {
    int num = (int)a.size();
    float sum = 0;
    for (int i = 0; i < num; i++) {
        sum += pow(a[i] - b[i], 2);
    }
    return sqrt(sum);
}

struct compare  //仿函数
{
    bool operator() (const pair<float, int> &src1, const pair<float, int> &src2)
    {
        return src1.first < src2.first;   //升序排列，如果改为s1 > s2则为逆序排列
    }
};

void kthIndex(vector<float>& v, vector<int>& index, int k){
    vector<pair<float, int> > m;
    for (int i = 0; i < v.size(); i++) {
        m.push_back(make_pair(v[i], i));
    }
    sort(m.begin(), m.end(), compare());
    for (int i = 0; i < k; i++)
        index.push_back(m[i].second);
}

