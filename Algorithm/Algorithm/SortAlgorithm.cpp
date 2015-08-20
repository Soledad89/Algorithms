//
//  SortAlgorithm.cpp
//  Algorithm
//
//  Created by 王波 on 15/8/20.
//  Copyright (c) 2015年 wangbo. All rights reserved.
//
#include <algorithm>

void bubblesort(int A[], int n)
{
    while ( n-- )
    {
        for (int i = 0; i < n; i++)
            if ( A[i] > A[i+1]) {
                std::swap ( A[i], A[i+1]);
            }
    }
}