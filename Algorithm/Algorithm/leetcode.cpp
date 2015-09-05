//
//  leetcode.cpp
//  Algorithm
//
//  Created by 王波 on 15/9/5.
//  Copyright (c) 2015年 wangbo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <string>
#include <queue>
#include <iostream>

using namespace std;


//问题：2sum
//算法：利用hash_map，可以获得O(1)的search
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> mapping;
    vector<int> result;
    for (int i = 0; i < nums.size();  i++){
        mapping[nums[i]] = i;
    }
    for (int i = 0; i < nums.size(); i ++){
        const int gap = target - nums[i];
        if (mapping.find(gap) != mapping.end() && mapping[gap] > i) {
            result.push_back(i+1);
            result.push_back(mapping[gap] + 1);
            break;
        }
    }
    return result;
}

//问题：next permutation
//算法：如下
/*
1. 找到最后一个严格升序的首位 (a[i] < a[i + 1]), 定义为x
    (A) = a[0..x – 1]  (B) = a[x + 1..n -1]
2. 找到y > x,  a[y] > a[x]，且a[y]最小
    一定存在，因为x + 1就是一个候选
    a[x]后面的数都是降序，所以从后往前找到第一个大于a[x]的位置就是y了
    可以二分找到y，但不影响总体时间复杂度
3. 交换a[x], a[y]
4. 对(x + 1)位后进行逆转
    交换后a[x + 1..n -1]仍然是降序(不升)
    逆转等于排序
 */
void nextPermutation(vector<int>& nums) {
    int n = (int)nums.size();
    int x;
    for (x = n - 2; (x >= 0) && (nums[x] >= nums[x+1]); --x);
    if (x < 0) {
        reverse(nums.begin(), nums.end());
        return;
    }
    int y;
    for (y = n-1; nums[y] <= nums[x]; --y);
    swap(nums[x], nums[y]);
    reverse(nums.begin() + x + 1, nums.end());
    
}
