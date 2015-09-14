//
//  bitmap.cpp
//  Algorithm
//
//  Created by 王波 on 15/9/14.
//  Copyright (c) 2015年 wangbo. All rights reserved.
//
#include <iostream>
#include <cstdio>
using namespace std;


int main(){
    
    freopen("./data.txt", "r", stdin);
    int int_len = sizeof(int) * 8;
    int bucket_num = 0xFFFFFFFF / int_len;
    int* bit = new int[bucket_num];
    int v;
    while(scanf("%d", &v) != EOF){
        bit[v/int_len] |= 1<<(v%int_len);
    }
    bool found = false;
    for(int i=0; i<bucket_num; ++i){
        for(int j=0; j<int_len; ++j){
            if((bit[i] & (1<<j)) == 0){
                cout<<i*int_len + j<<endl;
                found = true;
                break;
            }
            
        }
        if(found) break;
    }
    
    delete[] bit;
    fclose(stdin);
    return 0;
}
