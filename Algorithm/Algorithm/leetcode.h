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
#include "algorithms.h"

using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//边界条件、特殊输入（NULL指针、空字符串）、错误处理


/*
 果然是郑老师的检查下水道，注意与二分法比较像，但是要处理边界条件
 */
bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int i = 1;
        int j = n;
        while (i < j) {
            int mid = i + (j - i) / 2;
            if (isBadVersion(mid))
                j = mid;
            else
                i = mid + 1;
        }
        return j;
    }
};


/*
 Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.
 
 For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13, return 2 because 13 = 4 + 9.
 */

//Perfect Squares,总共有以下两种方法dp, bfs当然还有数学方法，见有道笔记

//DP
class Solution {
public:
    int numSquares(int n) {
        if (n == 0) return 0;
        
        vector<int> dp(n+1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j * j <= i; ++j) {
                dp[i] = min(dp[i], 1 + dp[i - j*j]);
            }
        }
        
        return dp[n];
    }
};

//BFS
class Solution
{
public:
    int numSquares(int n)
    {
        if (n <= 0)
        {
            return 0;
        }
        
        // perfectSquares contain all perfect square numbers which
        // are smaller than or equal to n.
        vector<int> perfectSquares;
        // cntPerfectSquares[i - 1] = the least number of perfect
        // square numbers which sum to i.
        vector<int> cntPerfectSquares(n);
        
        // Get all the perfect square numbers which are smaller than
        // or equal to n.
        for (int i = 1; i*i <= n; i++)
        {
            perfectSquares.push_back(i*i);
            cntPerfectSquares[i*i - 1] = 1;
        }
        
        // If n is a perfect square number, return 1 immediately.
        if (perfectSquares.back() == n)
        {
            return 1;
        }
        
        // Consider a graph which consists of number 0, 1,...,n as
        // its nodes. Node j is connected to node i via an edge if
        // and only if either j = i + (a perfect square number) or
        // i = j + (a perfect square number). Starting from node 0,
        // do the breadth-first search. If we reach node n at step
        // m, then the least number of perfect square numbers which
        // sum to n is m. Here since we have already obtained the
        // perfect square numbers, we have actually finished the
        // search at step 1.
        queue<int> searchQ;
        for (auto& i : perfectSquares)
        {
            searchQ.push(i);
        }
        
        int currCntPerfectSquares = 1;
        while (!searchQ.empty())
        {
            currCntPerfectSquares++;
            
            int searchQSize = searchQ.size();
            for (int i = 0; i < searchQSize; i++)
            {
                int tmp = searchQ.front();
                // Check the neighbors of node tmp which are the sum
                // of tmp and a perfect square number.
                for (auto& j : perfectSquares)
                {
                    if (tmp + j == n)
                    {
                        // We have reached node n.
                        return currCntPerfectSquares;
                    }
                    else if ((tmp + j < n) && (cntPerfectSquares[tmp + j - 1] == 0))
                    {
                        // If cntPerfectSquares[tmp + j - 1] > 0, this is not
                        // the first time that we visit this node and we should
                        // skip the node (tmp + j).
                        cntPerfectSquares[tmp + j - 1] = currCntPerfectSquares;
                        searchQ.push(tmp + j);
                    }
                    else if (tmp + j > n)
                    {
                        // We don't need to consider the nodes which are greater ]
                        // than n.
                        break;
                    }
                }
                
                searchQ.pop();
            }
        }
        
        return 0;
    }
};

/*
 Given a string that contains only digits 0-9 and a target value, return all possibilities to add operators +, -, or * between the digits so they evaluate to the target value.
 
 Examples:
 
 "123", 6 -> ["1+2+3", "1*2*3"]
 "232", 8 -> ["2*3+2", "2+3*2"]
 "00", 0 -> ["0+0", "0-0", "0*0"]
 "3456237490", 9191 -> []
 */

/*
 我们需要两个变量diff和curNum，一个用来记录将要变化的值，另一个是当前运算后的值，而且它们都需要用long long型的，因为字符串转为int型很容易溢出，所以我们用长整型。对于加和减，diff就是即将要加上的数和即将要减去的数的负值，而对于乘来说稍有些复杂，此时的diff应该是上一次的变化的diff乘以即将要乘上的数，有点不好理解，那我们来举个例子，比如2+3*2，即将要运算到乘以2的时候，上次循环的curNum = 5, diff = 3, 而如果我们要算这个乘2的时候，新的变化值diff应为3*2=6，而我们要把之前+3操作的结果去掉，再加上新的diff，即(5-3)+6=8，即为新表达式2+3*2的值，有点难理解，大家自己一步一步推算吧。
 

 */

class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> res;
        dfs(num, target, 0, 0, "", res);
        return res;
    }
    void dfs(string num, int target, long long diff, long long curNum, string out, vector<string> &res) {
        if (num.size() == 0 && curNum == target) {
            res.push_back(out);
        }
        for (int i = 1; i <= num.size(); ++i) {
            string cur = num.substr(0, i);
            if (cur.size() > 1 && cur[0] == '0') return;
            string next = num.substr(i);
            if (out.size() > 0) {
                dfs(next, target, stoll(cur), curNum + stoll(cur), out + "+" + cur, res);
                dfs(next, target, -stoll(cur), curNum - stoll(cur), out + "-" + cur, res);
                dfs(next, target, diff * stoll(cur), (curNum - diff) + diff * stoll(cur), out + "*" + cur, res);
            } else {
                dfs(next, target, stoll(cur), stoll(cur), cur, res);
            }
        }
    }
};


//
/*
 题目大意是给你一个迭代器的接口，接口支持两个方法，next(), hasNext(),next()返回下一个元素，指针后移一位，hasNext返回是否还有下一个元素，要求在这个接口上做一层封装，使得支持peek()方法，即获取下一个元素但是不移动指针。
 
 
 
 题目本身并没有什么难度，增加一个cache缓存一下next()返回值作为peek()的返回值，并标记这个元素已经在缓存里就可以了。
 
 题目有个容易出错的地方是新的peekingIterator需要从iterator类继承，然而父类已经有next()方法了，所以在子类直接用next()得到的是子类的next()，要调用题目给的接口需要加上域操作符iterator::next()，另外编译类时，从上往下编译声明，之后再编译函数体，这个顺序在这里也得以体现。事实证明这些东西没写过还是很容易出错的- -！
 */

// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.
class Iterator {
    struct Data;
    Data* data;
public:
    Iterator(const vector<int>& nums);
    Iterator(const Iterator& iter);
    virtual ~Iterator();
    // Returns the next element in the iteration.
    int next();
    // Returns true if the iteration has more elements.
    bool hasNext() const;
};


class PeekingIterator : public Iterator {
public:
    int cache;
    bool hasPeeked;
    
    PeekingIterator(const vector<int>& nums) : Iterator(nums) {
        // Initialize any member here.
        // **DO NOT** save a copy of nums and manipulate it directly.
        // You should only use the Iterator interface methods.
        hasPeeked = false;
    }
    
    // Returns the next element in the iteration without advancing the iterator.
    int peek() {
        if (!hasPeeked) {
            hasPeeked = true;
            return cache = Iterator::next();
        } else {
            return cache;
        }
    }
    
    // hasNext() and next() should behave the same as in the Iterator interface.
    // Override them if needed.
    int next() {
        if (hasPeeked) {
            hasPeeked = false;
            return cache;
        } else {
            return Iterator::next();
        }
    }
    
    bool hasNext() const {
        if (hasPeeked) {
            return true;
        } else {
            return Iterator::hasNext();
        }
    }
};

//设计BST的迭代器
class BSTIterator {
private:
    stack<TreeNode*> sta;
public:
    BSTIterator(TreeNode *root) {
        while(!sta.empty())
            sta.pop();
        while(root) {//初始化时，栈里保存从根节点到最左边叶子的节点，栈顶是整颗树的最小值
            sta.push(root);
            root = root->left;
        }
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !sta.empty();
    }
    
    /** @return the next smallest number */
    int next() {
        TreeNode *tmp = sta.top();
        sta.pop();
        int ret = tmp->val;
        tmp = tmp->right;//开始保存当前弹出栈的节点的右子树，还是先压入右儿子的所有左儿子！
        while(tmp) {
            sta.push(tmp);
            tmp = tmp->left;
        }
        return ret;
    }
};


class BSTIterator {
private:
    stack<TreeNode*> s;
public:
    BSTIterator(TreeNode *root) {
        while (root != NULL) {
            s.push(root);
            root = root -> left;
        }
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !s.empty();
    }
    
    /** @return the next smallest number */
    int next() {
        if (!hasNext()) {
            return INT_MIN; //Error
        }
        int res = s.top() -> val;
        TreeNode* node = s.top();
        s.pop();
        if (node -> right != NULL) {
            node = node -> right;
            s.push(node);
            while (node -> left != NULL) {
                node = node -> left;
                s.push(node);
            }
        }
        return res;
    }
};


/*
 game of life
 */
// Game of Life
/*
 状态: 前一位表示下一代的状态,后一位表示当前的状态
 00: 死->死
 10: 死->活
 01: 活->死
 11: 活->活
 */
class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int dir[][2] = {{1,-1}, {1,0},{1,1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1}};
        int m = board.size();
        int n = board[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int cnt = 0;
                for (int k = 0; k < 8; k++) {
                    int x = dir[k][0] + i;
                    int y = dir[k][1] + j;
                    if (x < 0 || x >= m || y < 0 || y >= n) {
                        continue;
                    }
                    if (board[x][y] & 1)    cnt++;
                }
                //dead
                if (board[i][j] == 0) {
                    if (cnt == 3)
                        board[i][j] = 2;    //2: 10
                }
                //live
                else {
                    if (cnt < 2 || cnt > 3)
                        board[i][j] = 1;    //1: 01
                    else
                        board[i][j] = 3;    //3: 11
                }
            }
        }
        
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n;j++)
                board[i][j] >>= 1;
        
    }
    
};


/*trapping rain water containing
 Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.
 
 For example,
 Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.
 */
/*
 观察下就可以发现被水填满后的形状是先升后降的塔形，因此，先遍历一遍找到塔顶，然后分别从两边开始，往塔顶所在位置遍历，水位只会增高不会减小，且一直和最近遇到的最大高度持平，这样知道了实时水位，就可以边遍历边计算面积。
 */
class Solution {
public:
    //双指针法, 主要运用了container with most water 的思想
    int trap3(vector<int>& height) {
        int n = height.size(), l = 0, r = n - 1, water = 0, minHeight = 0;
        while (l < r) {
            while (l < r && height[l] <= minHeight)
                water += minHeight - height[l++];
            while (r > l && height[r] <= minHeight)
                water += minHeight - height[r--];
            minHeight = min(height[l], height[r]);
        }
        return water;
    }
    
    int trap2(vector<int>& height) {
        int n = height.size();
        int* max_right = new int[n]();  //这是记录每一个trap左右两边最高的柱子
        int* max_left  = new int[n]();
        for (int i = 1; i < n; i++) {
            max_left[i] = max(max_left[i-1], height[i-1]);
            max_right[n - i - 1] = max(max_right[n-i], height[n-i]);
        }
        
        int sum = 0;
        for (int i = 0; i < n; i++) {
            int h = min(max_left[i], max_right[i]);
            if (h > height[i])
                sum += h - height[i];
        }
        delete[] max_right;
        delete[] max_left;
        return sum;
    }
    
    int trap(vector<int>& A) {
        int n = A.size();
        int maxIndex = 0; //将数组分为两个部分
        for (int i = 0; i < n; i++)
            if (A[i] > A[maxIndex])
                maxIndex = i;
        int water = 0;
        for (int i = 0, peak = 0; i < maxIndex; i++) {
            if (A[i] > peak)    peak = A[i];
            else
                water += peak - A[i];
        }
        
        for (int i = n - 1, top = 0; i > maxIndex; i--) {
            if (A[i] > top)    top = A[i];
            else
                water += top - A[i];
        }
        return water;
    }
    
    /*
     Container With Most Water
     */
    int maxArea(vector<int> &height) {
        
        int n = height.size();
        int maxArea = 0;
        int i = 0, j = n-1;
        while(i<j){
            int temp = (j - i)*(height[i]>height[j]?height[j]:height[i]);
            if(height[i] < height[j])   //这种更新的方式
                i++;
            else
                j--;
            maxArea = max(maxArea, temp);
        }
        return maxArea;
    }
    
};
//问题：Largest Rectangle in Histogram
//算法：利用堆栈来维护一个递增栈, 栈内存储的是高度递增的下标,使用一个栈的O(n)解法，代码非常简洁，栈内存储的是高度递增的下标。对于每一个直方图高度，分两种情况。1：当栈空或者当前高度大于栈顶下标所指示的高度时，当前下标入栈。否则，2：当前栈顶出栈，并且用这个下标所指示的高度计算面积。而这个方法为什么只需要一个栈呢？因为当第二种情况时，for循环的循环下标回退，也就让下一次for循环比较当前高度与新的栈顶下标所指示的高度，注意此时的栈顶已经改变由于之前的出栈。
/*
 由于出栈的这些元素高度都是递增的，我们可以求出这些立柱中所围成的最大矩形。更妙的是，由于这些被弹出的立柱处于“波峰”之上(比如弹出i 到 i+k，那么所有这些立柱的高度都高于 i-1和 i+k+1的高度)，因此，如果我们使用之前所提的“左右延伸找立柱”的思路解，以这些立柱的高度作为整个矩形的高度时，左右延伸出的矩形所包含的立柱不会超出这段“波峰”，因为波峰外的立柱高度都比他们低。“波峰图”其实就是求解最大矩形的“孤岛”，它不会干扰到外部。
 */
int largestRectangleArea(vector<int> &height) {
    if(height.size() == 0) return 0;
    stack<int> st;
    int result = 0;
    height.push_back(0);
    int leftarea = 0, rightarea = 0;
    for(int i = 0; i < height.size(); ++i){
        while(!st.empty() && height[st.top()] > height[i]){
            int tmp = st.top();
            st.pop();
            leftarea = (st.empty() ? tmp + 1 : tmp - st.top()) * height[tmp]; //以tmp为高度，tmp所在柱以及向左延伸出来的矩形面积
            rightarea = (i - tmp - 1) * height[tmp]; //以tmp为高度，向右边延伸出来的矩形面积
            result = max(result, leftarea + rightarea);
        }
        st.push(i);
    }
    return result;
}
//算法2：遍历，暴力算法
int largestRectangleArea2(vector<int> &height) {
    if(height.size() == 0) return 0;
    int max = 0;
    for(int i = 0; i < height.size(); ++i){
        int mid = i;
        int area = 0;
        for(;mid >= 0 && height[mid] >= height[i]; area += height[i], --mid);
        for(mid = i+1 ;mid < height.size() && height[mid] >= height[i]; area += height[i], ++mid);
        if(max < area) max = area;
    }
    return max;
}

/*
 Given a positive integer, return its corresponding column title as appear in an Excel sheet.
 
 For example:
 
 1 -> A
 2 -> B
 3 -> C
 ...
 26 -> Z
 27 -> AA
 28 -> AB
 */
class Solution{
public:
    string convertToTitle(int n) {
        string str = "";
        while (n) {
            str.insert(str.begin(), (n-1) % 26 + 'A');
            n =  (n-1) / 26;
        }
        return str;
    }
    
    string convertToTitle2(int n) {
        string ret = "";
        while(n)
        {
            ret = (char)((n-1)%26+'A') + ret;
            n = (n-1)/26;
        }
        return ret;
    }
    
    int titleToNumber(string s) {
        int n = s.size();
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum = sum * 26 +  (s[i] - 'A' + 1) ;
        }
        return sum;
    }
};


/*
 Implement regular expression matching with support for '.' and '*'.
 
 '.' Matches any single character.
 '*' Matches zero or more of the preceding element.
 
 The matching should cover the entire input string (not partial).
 
 The function prototype should be:
 bool isMatch(const char *s, const char *p)
 
 Some examples:
 isMatch("aa","a") → false
 isMatch("aa","aa") → true
 isMatch("aaa","aa") → false
 isMatch("aa", "a*") → true
 isMatch("aa", ".*") → true
 isMatch("ab", ".*") → true
 isMatch("aab", "c*a*b") → true
 */
/*
 状态转移方程如下：
 dp[i][j] =
 c1. p[j+1] != '*'时   if s[i] == p[j]  dp[i][j] = dp[i+1][j+1]
                        else dp[i][j] = false
 c2 p[j+1] == '*'时  (这个情况下，要扩展 *, dp[i][j] 从拓展的情况下，选择一个是真的结果）
 if( s[i] ==  p[j] || p[j] == '.' && (*s) != 0)  当s[i] 和 p[j] 一样的时候，例如 aba, a*b这个时候，i = 0, j = 0, 自然可以匹配a a
 如果p[j] == .  因为他可以匹配任何字符，所以和相等关系有基本一样的方式。
 并且每一步匹配都要递增 i 的值，如果有成立的，则返回true，否则到匹配终了，返回通配符匹配完成后的结果。
 */
class Solution_IsMatch {
    
    bool isMatch(const char *s, const char *p){
        if (*p == '\0') return *s == '\0';
        //next char is not '*', then must current characters
        if (*(p+1) != '*'){
            if (*p == *s || (*p == '.'&& *s != '\0')){
                return isMatch(s + 1, p + 1);
            }else { //next char is '*'
                while (*p == *s || (*p == '.' && *s != '\0')){
                    if (isMatch(s, p+2))
                        return true;
                    s++;
                }
                return isMatch(s, p+2);
            }
        }
    }
    
    bool isMatch_iterate(const char *s, const char *p){
        bool star = false;
        const char *str, *ptr;
        for (str = s, ptr = p; *str != '\0'; str++, ptr++){
            switch (*ptr){
                case '?':
                    break;
                case '*':
                    star = true;
                    s = str, p = ptr;
                    while (*p == '*')
                        p++;        //skip continuous '*'
                    if (*p == '\0')
                        return true;
                    str = s - 1;
                    ptr = p - 1;
                    break;
                default:
                    if (*str != *ptr){
                        //如果前面没有‘*’，则匹配不成功
                        if (!star)
                            return false;
                        s++;
                        str = s- 1;
                        ptr = p -1;
                    }
            }
        }
        while (*ptr == '*')
            ptr++;
        return (*ptr == '\0');
    }
};


class Solution_happyNumber {
public:
    bool isHappy(int n) {
        if (n < 1)  return false;
        if (n == 1) return true;
        
        unordered_set<int> showedNums;      //hash save the world
        showedNums.insert(n);
        
        while(true){
            int s = 0;
            while(n) {            //这个是对整数进行分解的方法
                s += (n % 10) * (n % 10);
                n = n / 10;
            }
            
            if (s == 1)
                return true;
            else if (showedNums.find(s) != showedNums.end())
                return false;
            n = s;
            showedNums.insert(s);
        }
    }
};

/*
 Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.
 
 Example 1:
 
 11110
 11010
 11000
 00000
 Answer: 1
 
 Example 2:
 
 11000
 11000
 00100
 00011
 Answer: 3
 */
class Solution_Numberofislands {
public:
    int numIslands(vector<vector<char>>& grid) {
        int count = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == '1') {
                    dfs(grid, i, j);
                    count++;
                }
            }
        }
        return count;
    }
    
    void dfs(vector<vector<char> >&grid , int i , int j){
        if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size()) {
            return
        }
        
        if (grid[i][j] == '1') {
            grid[i][j] = 'X';
            dfs(grid, i+1, j);
            dfs(grid, i-1, j);
            dfs(grid, i, j-1);
            dfs(grid, i, j+1);
        }
    }
    
};


//single number
class Solution_singleNumber {
    
    int singleNumber2(int A[], int n){
        int x = 0;
        for (size_t i = 0; i < n; i++)
            x ^= A[i];
        return x;
    }


    int singleNumber3(int A[], int n){
        const int W = sizeof(int) * 8;
        int count[W];
        fill_n(&count[0], W, 0);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < W; j++){
                count[j] += (A[i] >> j) & 1;
                count[j] %= 3;
            }
        }
        
        int result = 0;
        for(int i = 0; i < W; i++)
            result += (count[i] << i);
        
        return result;
    }

    //通用的方法用一个32位的数组，唯一一个只出现1次的，其余都是k次
    int singleNumberK(vector<int>& s, int k )
    {
        vector<int> t(32,0);////Made a array contain 32 elements.
        int sz = s.size();
        int i, j, n;
        for (i = 0; i < sz; ++i)
        {
            n = s[i];
            for (j = 31; j >= 0; --j)   //只要这里的顺序与下面的相同即可
            {
                t[j] += n & 1;//Find the last digit.
                n >>= 1;
                if (!n)
                    break;
            }
        }
        int res = 0;
        for (j = 31; j >= 0; --j)
        {
            n = t[j] % k;       //"3" represents k times.
            if (n)
                res += 1 << (31 - j);
        }
        return res;
    }
    
    //Given an array of numbers nums, in which exactly two elements appear only once and all the other elements appear exactly twice.
    vector<int> singleNumber_2single(vector<int>& nums) {
        int n = nums.size();
        vector<int> result;
        if (n == 0)
            return result;
        int ac = nums[0];
        for (int i = 1; i < n; i++) {
            ac ^= nums[i];
        }
        int index = 0;
        while((ac & 1) == 0) {
            index++;
            ac >>= 1;
        }
        
        int n1 = 0;
        int n2 = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] & (1 << index))
                n1 ^= nums[i];
            else
                n2 ^= nums[i];
        }
        return vector<int>{n1, n2};
    }
    
    //简洁版
    vector<int> singleNumber_2single2(vector<int>& nums) {
        int s = 0;  // the result of a xor b;
        for (auto item : nums) s ^= item;
        int lastBit = (s & (s - 1)) ^ s;  // the last bit that a diffs b
        //int lastBit = s & ( ~ ( s - 1));
        int intA = 0, intB = 0;
        for (auto item : nums) {
            if (item & lastBit) intA = intA ^ item;
            else intB = intB ^ item;
        }
        return vector<int>{intA, intB};
    }
    

};

/*
 Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of all numbers in this range, inclusive.
 
 For example, given the range [5, 7], you should return 4.
 
 
 
 直接计算肯定会超时。
 
 可以举几个例子来看看(都用二进制来表示)。
 
 m=001, n=111, 最终结果是000，
 
 m=11001, n=11110, 最终结果是11000，最左边11***是[m,n]区间的每个数都一样的
 
 m=10100, n=10111, 最终结果是10100   最左边101**是[m,n]区间的每个数都一样的
 
 可以看到我们只需要观察m和n这两个数字就可以得到结果，只需要知道他们最左边不变的部分，组合右边全0，就是最终的结果。
 
 所以我们来顶一个全1的mask，用来标记左边有多少位置是不变的。mask中右边0的部分代表的是[m,n]中会发生变化的部分，也就是说最终结果的这部分肯定也是0， 每次通过mask=mask<<1来更新， 当 m&mask == n& mask的时候，判断结束，
 
 最终的结果就是 m&mask 或者 n& mask
 */
class Solution_rangeBitwiseAnd {
public:
    int rangeBitwiseAnd(int m, int n) {
        int mask = ~0;      // all 1 sequence
        while (mask != 0)
        {
            if ((m & mask) == (n & mask)) //to test the unchanged part of the left-side
            {
                break;
            }
            mask <<= 1;             // the 0 in the mask indicate the changed part, which will be 0 in the result
        }
        return m & mask;
    }
    
    public int rangeBitwiseAnd2(int m, int n) {
        int i=0;
        while(m!=n){
            m>>=1;
            n>>=1;
            i++;
        }
        return m<<i;
    }
}

    int rangeBitwiseAnd3(int m, int n) { //最简单直观，方便理解
        while (m < n)   {
            n = n & (n - 1);
        }
        return n;
    }
};


/*
 Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.
 
 Note:
 You may assume k is always valid, 1 ≤ k ≤ BST's total elements.
 
 Follow up:
 What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?
 
 Hint:
 
 Try to utilize the property of a BST.
 What if you could modify the BST node's structure?
 The optimal runtime complexity is O(height of BST).
 */
class Solution_kthSmallest {
public:
    int kthSmallest(TreeNode* root, int k) {
        if (root == NULL)
            return 0;
        int rootRank = getNodesNum(root->left) + 1;
        if (rootRank == k)
            return root->val;
        else if (rootRank > k)
            return kthSmallest(root->left, k);
        else
            return kthSmallest(root->right, k - rootRank);
    }
private:
    
    int getNodesNum(TreeNode * root) {  //计算树的节点数目
        if (root == NULL)
            return 0;
        return getNodesNum(root->left) + getNodesNum(root->right) + 1;
    }
};
//algorithm: 以上的解法遍历了多次节点，浪费，可以不用求左子树的节点数目

/*
 Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
 
 For example,
 Given [100, 4, 200, 1, 3, 2],
 The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.
 
 Your algorithm should run in O(n) complexity.
 */

//复杂度为O(nlogn)
int longestConsecutive(vector<int>& nums) {
    int n = nums.size();
    if ( n == 0 || n == 1)
        return n;
    sort(nums.begin(), nums.end());         //排序之后再做
    int max = 0;
    int cur = 1;
    for (int i = 1; i < n; i++) {
        if ( nums[i] == nums[i-1]) {
            if ( i == n - 1 && cur > max)
                max = cur;
            continue;
        }
        
        if (nums[i] == nums[i - 1] + 1 ) {
            cur++;
            if (i == n-1 && cur > max)
                max = cur;
        } else
        {
            if ( cur > max) {
                max = cur;
            }
            cur = 1;
        }
    }
    return max;
}
//复杂度为O(n);

int longestConsecutive2(vector<int>& nums) {
    int n = (int)nums.size();
    if ( n == 0 || n == 1)
        return n;
    unordered_set<int>  setnum;
    //由于有查找的步骤，因此考虑使用set，如果用map的话，其底层结构是红黑树，所以复杂度也是O(nlogn)
    setnum.insert(nums.begin(), nums.end());
    
    //    for (int i = 0; i < n; i++) {
    //        setnum.insert(nums[i]);
    //    }
    
    int max = 0;
    int count;
    for (int i = 0; i < n; i++) {
        count = 1;
        int curincrease = nums[i] + 1;
        while(setnum.find(curincrease) != setnum.end()) {
            count++;
            setnum.erase(curincrease);
            curincrease++;
            
        }
        
        int curdecrease = nums[i] - 1;
        while (setnum.find(curdecrease) != setnum.end()) {
            count++;
            setnum.erase(curdecrease);
            curdecrease--;
            
        }
        
        if (count > max)
            max = count;
    }
    return max;
}


/*
 Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.
 
 For example:
 
 Given "aacecaaa", return "aaacecaaa".
 
 Given "abcd", return "dcbabcd".
 */
string shortestPalindrome(string s) {
    if (s == "")
        return "";
    string s_r = reverse(s.begin(), s.end());
    
}

//problem:实现LRU cache
//algorithm: 采用hashmap（也就是unordered_map）和list

class LRUCache{
private:
    struct CacheNode
    {
        int key;
        int value;
    };
    
    int maxSize ;
    list<CacheNode> cacheList;      //STL中的list就是双链表实现
    unordered_map<int, list<CacheNode>::iterator > mp;
    //这个用map开销是236ms,用unordered_map的开销是156ms，看来unordered_map的效率确实高
public:
    LRUCache(int capacity) {
        maxSize = capacity;
    }
    
    int get(int key) {
        unordered_map<int, list<CacheNode>::iterator >::iterator it = mp.find(key);
        if(it == mp.end())      //没有命中
        {
            return -1;
        }
        else  //在cache中命中了
        {
            list<CacheNode>::iterator listIt = mp[key];
            CacheNode newNode;
            newNode.key = key;
            newNode.value = listIt->value;
            cacheList.erase(listIt);               //先删除命中的节点
            cacheList.push_front(newNode);   //将命中的节点放到链表头部
            mp[key] = cacheList.begin();
        }
        return cacheList.begin()->value;
    }
    
    void set(int key, int value) {
        unordered_map<int, list<CacheNode>::iterator >::iterator it = mp.find(key);
        if(it == mp.end())   //没有命中
        {
            if(cacheList.size() == maxSize)  //cache满了
            {
                mp.erase(cacheList.back().key);
                cacheList.pop_back();
            }
            CacheNode newNode;
            newNode.key = key;
            newNode.value = value;
            cacheList.push_front(newNode);
            mp[key] = cacheList.begin();
        }
        else  //命中
        {
            list<CacheNode>::iterator listIt = mp[key];
            cacheList.erase(listIt);               //先删除命中的节点
            CacheNode newNode;
            newNode.key = key;
            newNode.value = value;
            cacheList.push_front(newNode);   //将命中的节点放到链表头部
            mp[key] = cacheList.begin();
        }
    }
};

//接下来我们讲一下BFS和DFS的应用，一个典型的例子
namespace BFS_DFS {
    
    
#define MAX 100
typedef struct
{
    int edges[MAX][MAX];    //邻接矩阵
    int n;                  //顶点数
    int e;                  //边数
}MGraph;

bool visited[MAX];          //标记顶点是否被访问过

void creatMGraph(MGraph &G)    //用引用作参数
{
    int i,j;
    int s,t;                 //存储顶点编号
    int v;                   //存储边的权值
    for(i=0;i<G.n;i++)       //初始化
    {
        for(j=0;j<G.n;j++)
        {
            G.edges[i][j]=0;
        }
        visited[i]=false;
    }
    for(i=0;i<G.e;i++)      //对矩阵相邻的边赋权值
    {
        scanf("%d %d %d",&s,&t,&v);   //输入边的顶点编号以及权值
        G.edges[s][t]=v;
    }
}

void DFS(MGraph G,int v)      //深度优先搜索
{
    int i;
    printf("%d ",v);          //访问结点v
    visited[v]=true;
    for(i=0;i<G.n;i++)       //访问与v相邻的未被访问过的结点
    {
        if(G.edges[v][i]!=0 && visited[i]==false)
        {
            DFS(G,i);           /////////////
        }
    }
}

void DFS_nonRecursive(MGraph G,int v)   //非递归实现
{
    stack<int> s;
   
    visited[v] = true;
    s.push(v);
    
    while(!s.empty())
    {
        int i = s.top();          //取栈顶顶点
        s.pop();
        /////////////////VISITED
        printf("%d ", i);
        /////////////////VISITED
       
        for(int j=0;j<G.n;j++)  //访问与顶点i相邻的顶点
        {
            if(G.edges[i][j] != 0 && visited[j]==false)
            {
                visited[j]=true;
                s.push(j);           //访问完后入栈

            }
        }

    }
}

void BFS_nonRecursive(MGraph G,int v)      //广度优先搜索
{
    queue<int> Q;             //STL模板中的queue
    visited[v] = true;
    Q.push(v);
    while(!Q.empty())
    {
        int i = Q.front();         //取队首顶点
        Q.pop();
        
        printf("%d ", i);
        
        for(int j=0;j<G.n;j++)   //广度遍历
        {
            if(G.edges[i][j]!=0&&visited[j]==false)
            {
                visited[j]=true;
                Q.push(j);
            }
        }
    }
}

int main_BFSDFS(void)
{
    int n,e;    //建立的图的顶点数和边数
    while(scanf("%d %d",&n,&e)==2&&n>0)
    {
        MGraph G;
        G.n=n;
        G.e=e;
        creatMGraph(G);
        DFS_nonRecursive(G,0);
        printf("\n");
        //    DFS1(G,0);
        //    printf("\n");
        //    BFS(G,0);
        //    printf("\n");
    }
    return 0;
}

}

//DFS标准模板，也就这几个步骤
 /**
 * dfs模板
 * input 输入数据指针
 * path 当前路径，也是中间结果
 * result 存放最终结果
 * cur or gap 标记当前位置或距离目标的距离
 * return 路径长度，如果是求路径本身，则不需要返回长度
 **/

/*
void dfs(type &input, type &path, type &result, int cur or gap) {
    if (数据非法) return 0;			//终止条件
    if (cur == input.size()) {			//收敛条件
        // if (gap == 0) {
        将path放入result;
    }
    
    if (可以剪枝)	return;
    for (…) 	{					//执行所有可能的扩展动作
        执行动作，修改path;
        dfs(input, path, result, cur++ or gap—);
        恢复path;
    }
}
*/




//problem:对于一个有向图，请实现一个算法，找出两点之间是否存在一条路径。
/*
 题目
 
 给定一个有向图，设计算法判断两结点间是否存在路径。
 
 解答
 
 根据题意，给定一个有向图和起点终点，判断从起点开始，是否存在一条路径可以到达终点。 考查的就是图的遍历，从起点开始遍历该图，如果能访问到终点， 则说明起点与终点间存在路径。稍微修改一下遍历算法即可。
 
 代码如下(在BFS基础上稍微修改)：
 */

struct UndirectedGraphNode {
    int label;
    vector<struct UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {}
};

class Path {
public:
    bool checkPath(UndirectedGraphNode* a, UndirectedGraphNode* b) {
        //map<UndirectedGraphNode*, bool> visited;//记录是否已经访问过
        return atob(a,b) || atob(b,a);
    }
     
    bool atob(UndirectedGraphNode* a, UndirectedGraphNode* b){//广度优先搜索
        map<UndirectedGraphNode*, bool> flag;
        queue<UndirectedGraphNode*> q;//队列保存节点
        
        q.push(a);//入列
        flag[a] = true;//标记访问
        
        while(!q.empty()){
            UndirectedGraphNode* curr = q.front();
            q.pop();//出列
            ////这就是广度遍历的VISIT
            if (curr == b)
                return true;
            //////////////////
            for(unsigned int i = 0; i < curr->neighbors.size(); ++i){
                if(!flag[curr->neighbors[i]]) {
                    q.push(curr->neighbors[i]);
                    flag[curr->neighbors[i]] = true;    //push进去之后就意味着已经访问了
                }   
            }
        }
        return false;//找不到
    }
};

namespace bfs_path_exit {

    const int maxn = 100;
    bool g[maxn][maxn], visited[maxn];      //要有一个标记是否visited
    int n;
    queue<int> q;

    void init(){
        memset(g, false, sizeof(g));
        memset(visited, false, sizeof(visited));
    }
    bool route(int src, int dst){
        q.push(src);
        visited[src] = true;
        while(!q.empty()){
            int t = q.front();
            q.pop();
            if(t == dst) 
                return true;
            
            for(int i=0; i<n; ++i)
                if(g[t][i] && !visited[i]){
                    q.push(i);
                    visited[i] = true;
                }
        }
        return false;
    }
    int main_bfs_pathExit(){
        freopen("4.2.in", "r", stdin);  

        init();
        int m, u, v;
        cin>>n>>m;
        for(int i=0; i<m; ++i){
            cin>>u>>v;
            g[u][v] = true;
        }
        cout<<route(1, 6)<<endl;
        fclose(stdin);
        return 0;
    }

}

//word ladder I
/*
Given two words (start and end), and a dictionary, find the length of shortest transformation sequence from start to end, such that:

Only one letter can be changed at a time
Each intermediate word must exist in the dictionary
*/
//bfs




//problem: letter combinations
//algorithm: dfs
class Solution {

public:
    vector<string> letterCombinations(const string &digits) {
        if (digits.empty()) return vector<string>();
        vector<string>  result;
        dfs(digits, 0, "", result);
        return result;
    }
private:
    const vector<string> keyboard = { " ", "", "abc", "def", "ghi", "jkl","mno","pqrs", "tuv", "wxyz" };

    void dfs(const string &digits, size_t cur, string path, vector<string> &result) {
        if (cur == digits.size()) {
            result.push_back(path);
            return;
        }
        
        for (auto c : keyboard[digits[cur] - '0']) {
            dfs(digits, cur+1, path+c, result);
        }
    }
    
    
    //利用迭代
    vector<string> letterCombinations(string digits) {
        vector<string> result;
        if(digits.empty()) return vector<string>();
        static const vector<string> v = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        result.push_back("");   // add a seed for the initial case
        for(int i = 0 ; i < digits.size(); ++i) {
            int num = digits[i]-'0';
            if(num < 0 || num > 9) break;
            const string& candidate = v[num];
            if(candidate.empty()) continue;
            vector<string> tmp;
            for(int j = 0 ; j < candidate.size() ; ++j) {
                for(int k = 0 ; k < result.size() ; ++k) {
                    tmp.push_back(result[k] + candidate[j]);
                }
            }
            result.swap(tmp);
        }
        return result;
    }

};
//problem: word search
//algorithm: dfs;
/*
 abcds
 dfafa
 fafaf
 */
//从中判断是否包含abcaf等
//dfs一般都包含四个步骤：done, find, forward, backtracking, 再结合trie树可以降低复杂度
bool dfs_wordSearch(const vector<vector<char> > &board, const string &word, 
    int index, int x, int y, vector<vector<bool> > &visited) {
    
    //done
    if (index == word.size())
        return true;    //收敛条件
    
    //find
    if (x < 0 || y < 0 || x >= board.size() || y >= board[0].size() || visited[x][y])
        return false;   //越界，终止条件
    if (board[x][y] != word[index])
        return false;   //不相等，剪枝
    
    //forward
    visited[x][y] = true;
    bool ret = dfs_wordSearch(board, word, index+1, x-1, y, visited) || //上
               dfs_wordSearch(board, word, index+1, x+1, y, visited) || //下
               dfs_wordSearch(board, word, index+1, x, y-1, visited) || //左
               dfs_wordSearch(board, word, index+1, x, y+1, visited);   //右
    
    //backtracking
    visited[x][y] = false;  //回溯，保护现场
    return ret;
}



bool wordSearch(vector<vector<char> > &board, string word) {
    const int m = (int)board.size();
    const int n = (int)board[0].size();
    
    vector<vector<bool> > visited(m, vector<bool>(n, false));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            if (dfs_wordSearch(board, word, 0, i, j, visited))  //从每一个board blank出发
                return true;
    }
    return false;
}


bool dfs(vector<vector<char> > &board, vector<vector<bool> > visited, string str, int current, int target, int x, int y);
vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    int m = board.size();
    int n = board[0].size();
    int nw = words.size();
    vector<string> result;
    vector<vector<bool> > visited(m, vector<bool>(n, false));
    int current = 0;
    for (int i = 0; i < nw; i++) {
        string str = words[i];
        int target = str.size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (dfs(board, visited, str, current, target, i, j))
                    result.push_back(str);
            }
        }
    }
    return result;
}

bool dfs(vector<vector<char> > &board, vector<vector<bool> > visited, string str, int current, int target, int x, int y)
{
    bool result = false;
    if (current == target)
        return true;
    if (x < 0 || y < 0 || x >= board.size() || y >= board[0].size() || visited[x][y] )
        return false;
    
    if (str[current] == board[x][y]) {
        visited[x][y] = true;
        result = dfs(board, visited, str, current + 1, target, x - 1, y) ||
        dfs(board, visited, str, current + 1, target, x + 1, y) ||
        dfs(board, visited, str, current + 1, target, x, y - 1) ||
        dfs(board, visited, str, current + 1, target, x, y + 1);
        visited[x][y] = false;
    }
    return result;
}

//采用高效的Trie
class Solution_wordSearch {
public:
    struct TriNode {
        TriNode *ch[26];
        bool isWord;
        TriNode() : isWord(false) {
            for (auto &a : ch) a = NULL;
        }
    } *root;
    
    void insert(string word) {
        TriNode *p = root;
        for (auto &a : word) {
            int i = a - 'a';
            if (p->ch[i] == NULL) p->ch[i] = new TriNode();
            p = p->ch[i];
        }
        p->isWord = true;
    }
    
    bool isPrefix(string word) {
        TriNode *p = root;
        for (auto &a : word) {
            int i = a - 'a';
            if (p->ch[i] == NULL) return false;
            p = p->ch[i];
        }
        return true;
    }
    
    bool isWord(string word) {
        TriNode *p = root;
        for (auto &a : word) {
            int i = a - 'a';
            if (p->ch[i] == NULL) return false;
            p = p->ch[i];
        }
        return p->isWord;
    }
    
    Solution_wordSearch() {
        root = new TriNode();
    }
    
    bool isValid(vector<vector<char>> &board, vector<vector<bool>> &visit, int x, int y) {
        int m = board.size(), n = board[0].size();
        if (x < 0 || x >= m || y < 0 || y >= n || visit[x][y]) return false;
        return true;
    }
    
    bool dfs(vector<vector<char>> &board, vector<vector<bool>> &visit, set<string> &st, string &s, int x, int y) {
        int dx[4] = {1, 0, -1, 0};
        int dy[4] = {0, 1, 0, -1};
        visit[x][y] = true;
        int xx, yy;
        for (int i = 0; i < 4; ++i) {
            xx = x + dx[i]; yy = y + dy[i];
            if (isValid(board, visit, xx, yy)) {
                s.push_back(board[xx][yy]);
                if (isWord(s)) st.insert(s);
                if (isPrefix(s)) dfs(board, visit, st, s, xx, yy);
                s.pop_back();
            }
        }
        visit[x][y] = false;
    }
    
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> res;
        if (board.empty() || board[0].empty() || words.empty()) return res;
        for (auto &word : words) insert(word);
        int m = board.size(), n = board[0].size();
        vector<vector<bool>> visit(m, vector<bool>(n, false));
        string s;
        set<string> st;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                s.push_back(board[i][j]);
                if (isWord(s)) st.insert(s);
                if (isPrefix(s)) dfs(board, visit, st, s, i, j);
                s.pop_back();
            }
        }
        for (auto &word : st) res.push_back(word);
        return res;
    }
};


//problem: subsets
//algorithm: dfs
/*
 原数组中每一个元素在子集中有两种状态：要么存在、要么不存在。这样构造子集的过程中每个元素就有两种选择方法：选择、不选择，因此可以构造一颗二叉树来表示所有的选择状态：二叉树中的第i+1层第0层无节点表示子集中加入或不加入第i个元素，左子树表示加入，右子树表示不加入。所有叶节点即为所求子集。因此可以采用DFS的递归思想求得所有叶节点。
 */
//S为原数组，temp为当前子集，level为原数组中的元素下标亦为二叉树的层数，result为所求子集集合
void subsets(vector<int> &S,vector<int> temp,int level,vector<vector<int> > &result)
{
    //如果是叶子节点则加入到result中
    if(level == S.size())
    {
        result.push_back(temp);
        return;
    }
    //对于非叶子节点，不将当前元素加入到temp中
    subsets(S,temp,level + 1,result);
    //将元素加入到temp中
    temp.push_back(S[level]);
    subsets(S,temp,level + 1,result);
}

//algorithm2: 位运算
/*
 求子集问题就是求组合问题。数组中的n个数可以用n个二进制位表示，当某一位为1表示选择对应的数，为0表示不选择对应的数
 */
vector<vector<int> > subsets2(vector<int> &S,int n)
{
    //n个数有0~max-1即2^n中组合，1<<n表示2^n
    int max = 1<<n;
    vector<vector<int> >result;
    for(int i = 0;i < max;i++)
    {
        vector<int> temp;
        int idx = 0;
        int j = i;
        while(j > 0)
        {
            //判断最后一位是否为1，若为1则将对应数加入到当前组合中
            if(j&1)
            {
                temp.push_back(S[idx]);
            }
            idx++;
            //判断了这一位是否为1后要右移
            j = j>>1;
        }
        //判断完了一种组合，加入到结果集中
        result.push_back(temp);
    }
    return result;
}



//problem: valid sudoku
//algorithm:
bool check(char ch, bool used[9]) {
    if (ch == '.') return true;
    if (used[ch-'1']) return false;
    used[ch-'1'] = true;
    
    return true;
}
bool isValidSudoku(const vector<vector<char> > &board){
    bool used[9];
    for (int i = 0; i < 9; i++){
        fill(used, used + 9, false);
        
        for (int j = 0; j < 9; j++) //检测每一行
            if (!check(board[i][j], used))
                return false;
        
        fill(used, used + 9, false);
        
        for (int j = 0; j < 9; j++) //检测每一列
            if (!check(board[j][i], used))
                return false;
    }
    
    for (int r = 0; r < 3; r++)//检测9个小格子
        for (int c = 0; c < 3; c++) {
            fill(used, used + 9, false);
            
            for (int i = r*3; i < r * 3 + 3; i++)
                for (int j = c*3; j < c * 3 + 3; j++)
                    if (!check(board[i][j], used))
                        return false;
            
        }
    
    return true;
}

//problem: sudoku solver/ sudoku puzzle
//algorithm: 深度优先搜索DFS，回溯
/*
 思路：（借助网上的讨论）因为题目输入保证有且只有一个解，所以试探每一个格子的时候，
 只需要考虑当前行、列、矩形框满足条件，满足就进入下一个格子试探，不满足回溯。
 注意判断一个格子落入哪个矩形框的设计
 */
bool isValidSudoku(vector<vector<char> > &board,int x,int y){
    for(int j=0;j<9;j++)                        //当前行
        if(j != y && board[x][j] == board[x][y])
            return false;
    
    for(int i=0;i<9;i++)
        if(i != x && board[i][y] == board[x][y])//当前列
            return false;
    
    int gridRow = x/3 * 3, gridCol = y/3 * 3;   //当前小框
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(gridRow + i != x && gridCol + j != y
               && board[gridRow + i][gridCol + j] == board[x][y])
                return false;
    return true;
}

bool solveSudokuSingle(vector<vector<char> > &board){
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            if(board[i][j] == '.'){
                for(int k=1;k<=9;k++){
                    board[i][j] = '0' + k;          //从最小的添加起
                    if(isValidSudoku(board,i,j) && solveSudokuSingle(board))
                        return true;
                    if ( k == 9)                   //如果不满足
                        board[i][j] = '.';      //则回溯，重要的是要重新将这一位清零
                }
                return false;
            }
    return true;
}

void solveSudoku(vector<vector<char> > &board) {
    solveSudokuSingle(board);
}



//problem: twosum
//algorithm: 利用hash，直接用STL提供unordered_map中的hash内核
vector<int> twoSum(vector<int> &num, int target)
{
    unordered_map<int, int> mapping;
    vector<int> result;
    for (int i = 0; i < num.size(); i++)
    {
        mapping[num[i]] = i;
    }
    
    for (int i = 0; i < num.size(); i++)
    {
        const int gap = target - num[i];
        if (mapping.find(gap) != mapping.end() && mapping[gap] > i)
        {
            result.push_back(i + 1);
            result.push_back(mapping[gap] + 1);
            break;
        }
    }
    
    return result;
}
//algorithm2: 利用双指针，前提是已经排序的数组
bool FindNumbersWithSum(int data[], int length, int sum,
                        int* num1, int* num2)
{
    bool found = false;
    if(length < 1 || num1 == NULL || num2 == NULL)
        return found;
    
    int ahead = length - 1;
    int behind = 0;
    
    while(ahead > behind)
    {
        long long curSum = data[ahead] + data[behind];
        
        if(curSum == sum)
        {
            *num1 = data[behind];
            *num2 = data[ahead];
            found = true;
            break;
        }
        else if(curSum > sum)
            ahead --;
        else
            behind ++;
    }
    
    return found;
}


//problem: 3sum, sum3==target
//algorithm: double pointer
vector<vector<int> > threeSum(vector<int> & num, const int target)
{
    vector<vector<int> > result;
    if (num.size() < 3) return result;
    sort(num.begin(), num.end());
    
    auto last = num.end();
    for (auto i = num.begin(); i < last - 2; ++i)
    {
        auto j = i + 1;
        if (i > num.begin() && *i == *(i-1)) continue;  //跳过重复的元素
        auto k = last - 1;
        while (j < k)
        {
            if (*i + *j + *k < target)
            {
                ++j;
                while ( *j == *(j - 1) && j < k ) ++j;
            }
            else if ( *i + *j + *k > target)
            {
                --k;
                while (*k == *(k + 1) && j < k) --k;
            }
            else
            {
                result.push_back({*i, *j, *k});
                ++j;
                --k;
                while ( *j == *(j - 1) && *k == *(k + 1) && j < k) ++j;
            }
        }
    }
    return result;
}
//problem: 有时候不能找到精确的3sum，可以找近似的3sum
//algorithm: 双指针夹逼，找之和与target之差最小的组合

int threeSumClosest(vector<int> &num, int target)
{
    int result = 0;
    int min_gap = INT_MAX;
    sort(num.begin(), num.end());
    for (auto a = num.begin(); a != prev(num.end(), 2); ++a)
    {
        auto b = next(a);
        auto c = prev(num.end());
        
        while (b < c)
        {
            const int sum = *a + *b + *c;
            const int gap = abs(sum - target);
            
            if (gap < min_gap)
            {
                result = sum;
                min_gap = gap;
            }
            
            if (sum < target) ++b;
            else              --c;
        }
    }
    return result;
}



//problem: reimplement strstr
//algorithm: the most efficient algorithm is KMP, but you must make sure you can
//do it right, in interview, brutal force is the one.
int MystrStr(char* haystack, char* needle){
    if ( needle == NULL) return 0;
    
    const char* p1;
    const char* p2;
    const char* p1_advance = haystack;
    
    for (p2 = &needle[1]; *p2; ++p2){
        p1_advance++;  //向前移动短字符串的长度
    }
    
    for (p1 = haystack; *p1_advance; p1_advance++){
        char* p1_old = (char*) p1;
        p2 = needle;
        while (*p1 && *p2 && *p1 == *p2){
            p1++;
            p2++;
        }
        
        if( p2 == NULL) return (int) (p1_old-haystack); //注意返回的是在haystack中的索引
        p1 = p1_old + 1;
    }
    return -1;
}

int myStrStr_(char *string, char *substring) {
    if (substring == NULL || string == NULL)
        return -1;
    int len1 = (int) strlen(string);
    int len2 = (int) strlen(substring);
    if (len1 < len2)
        return -1;
    for (int i = 0; i <= len1 - len2; i++) {
        int j = 0;
        for (; j < len2; j++){
            if (string[i + j] != substring[j])
                break;
        }
        if (j == len2)
            return i;
    }
    return -1;
}


//problem: preorder\inordrer\postordre tree traveral recursive and non-recursive
//algorithm: as follows树的遍历，树遍历
void visit(TreeNode* node) {                //这个VISIT不简单
    printf("%d -> ", node->val);
}
void preorderRecursive(TreeNode * node)
{
    if (node == NULL) return;
    visit(node);
    preorderRecursive(node->left);
    preorderRecursive(node->right);
}
void inorderRecursive(TreeNode* node) {         //这个相当于按照元素的大小由小到大的顺序访问
    if (node == NULL) return ;
    inorderRecursive(node->left);
    visit(node);
    inorderRecursive(node->right);
}
void postorderRecursive(TreeNode* node) {
    if (node == NULL) return ;
    postorderRecursive(node->left);
    postorderRecursive(node->right);
    visit(node);
}

void preorderNonrecursive(TreeNode * node) {    //树的前序遍历就是图的深度优先遍历
    stack<TreeNode *> s;
    s.push(node);   //preorder 还是先压入栈的好
    while (!s.empty())
    {
        TreeNode * cur = s.top(); s.pop();
        visit(cur);
        if (cur->right!=NULL)
            s.push(cur->right);
        if (cur->left!=NULL)
            s.push(cur->left);
    }
}
void inorderNonrecursive(TreeNode * node)
{
    stack<TreeNode *> s;
    TreeNode * cur = node;
    while (!s.empty() || cur != NULL) {
        if (cur != NULL) {
            s.push(cur);
            cur = cur->left;
        } else {
            cur = s.top(); s.pop();
            visit(cur);
            cur = cur->right;
        }
    }
}

void inorderNonrecursive2(TreeNode* node){
    stack<TreeNode*> s;
    TreeNode* cur = node;
    while (true) {  //inorder才喜欢这样来做
        while (cur) {
            s.push(cur);
            cur = cur->left; //从根节点出发沿左分支下行,直到最深的节点
        }
        if (s.empty()) break;
        cur = s.top(); s.pop();
        visit(cur);
        cur = cur->right;
        
    }
}

void postorderNonrecursive(TreeNode * node) {
    //the node first traversed is the node last visited
    stack<TreeNode *> sTraverse, sVisit;
    sTraverse.push(node);
    while (!sTraverse.empty())
    {
        TreeNode * p = sTraverse.top(); sTraverse.pop();
        sVisit.push(p);
        if (p->left != NULL) sTraverse.push(p->left);
        if (p->right != NULL) sTraverse.push(p->right);
    }
    while (!sVisit.empty()) {
        visit(sVisit.top());
        sVisit.pop();
    }
}

void traverseLevel(TreeNode* node) {            //树的层次遍历就相当于图的广度遍历
    queue<TreeNode*> q;
    TreeNode* cur;
    q.push(cur);
    while (!q.empty()) {
        cur = q.front(); q.pop();
        visit(cur);
        if (!cur->left)
            q.push(cur->left);
        if (!cur->right)
            q.push(cur->right);
    }
}
//下面一个算法是层次遍历的一个变种
/*
 Binary Tree Zigzag Level Order Traversal
 Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).
 
 For example:
 Given binary tree {3,9,20,#,#,15,7},
     3
    / \
   9  20
     /  \
    15   7
 return its zigzag level order traversal as:
 [
 [3],
 [20,9],
 [15,7]
 ]
 */
//但本质还是一样的，主要是要设置一个标志来表明是从左往右还是从右往左
class Solution_zigzagLevelOrder {       //递归版
public:
    vector<vector<int> > zigzagLevelOrder(TreeNode* root) {
        assert(root != NULL);
        vector<vector<int> > result;
        traverse(root, 1, result, true);
        return result;
    }
    void traverse(TreeNode* root, int level, vector<vector<int> > &result, bool left_to_right) {
        if (!root)  return;
        if (level > result.size());
        result.push_back(vector<int>());
        if (left_to_right)
            result[level-1].push_back(root->val);
        else
            result[level-1].insert(result[level-1].begin(), root->val);
        
        traverse(root->left, level+1, result, !left_to_right);
        traverse(root->right, level+1, result, !left_to_right);
    }
};


class Solution_zigzagLevelOrder3 {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if(root == nullptr)
            return ans;
        stack<TreeNode*> currentLevel, nextLevel;   //用两个栈，存储连续两层的节点
        TreeNode *p = root;
        currentLevel.push(p);
        vector<int> levelArray;
        int levelFlag = 0;              //even : left to right , odd : right to left
        while(!currentLevel.empty()) {
            while(!currentLevel.empty()) {
                p = currentLevel.top();
                currentLevel.pop();
                levelArray.push_back(p->val);
                if(levelFlag & 1) {     //odd，根据奇偶性来判断先push左子树还是右子树
                    if(p->right)
                        nextLevel.push(p->right);
                    if(p->left)
                        nextLevel.push(p->left);
                }else {
                    if(p->left)
                        nextLevel.push(p->left);
                    if(p->right)
                        nextLevel.push(p->right);
                }
            }
            ans.push_back(levelArray);
            levelArray.clear();
            swap(nextLevel, currentLevel);
            levelFlag++;
        }
        return ans;
    }
};

class Solution_zigzagLevelOrder4{
public:
    vector<vector<int> > zigzagLevelOrder(TreeNode *root)
    {
        vector<vector<int> > vvi;
        
        if(root == NULL)
            return vvi;
        
        queue<TreeNode *> q;            //还是利用队列，层次遍历的
        q.push(root);
        bool zigzag = false;
        while(!q.empty())
        {
            vector<int> vi;
            for(int i = 0, n = q.size(); i < n; ++ i)   //使用队列，利用size得到每一排的个数
            {
                TreeNode *temp = q.front();
                q.pop();
                if(temp -> left)
                    q.push(temp -> left);
                if(temp -> right)
                    q.push(temp -> right);
                vi.push_back(temp -> val);
            }
            if(zigzag)
                reverse(vi.begin(), vi.end());
            vvi.push_back(vi);
            zigzag = !zigzag;
        }
        
        return vvi;
    }
    
    /*
     Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.
     
     For example:
     Given the following binary tree,
        1            <---
      /   \
     2     3         <---
      \     \
       5     4       <---
     You should return [1, 3, 4].
     */
    //这个也是层次遍历的一个变种
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        if (NULL == root)   return res;
        queue<TreeNode*> q;
        q.push(root);
        while(true) {
            int n = q.size();
            for (int i = 0; i < n; i++) {
                TreeNode* tmp = q.front(); q.pop();
                if (tmp->left)  q.push(tmp->left);
                if (tmp->right) q.push(tmp->right);
                if ( i == n-1)  res.push_back(tmp->val);
            }
            if (q.empty())  break;
        }
        return res;
    }
};



//问题：rotate a image with O(1)
//算法：先将每一列颠倒，再沿着主对角线交换
/*
 * clockwise rotate
 * first reverse up to down, then swap the symmetry
 * 1 2 3     7 8 9     7 4 1
 * 4 5 6  => 4 5 6  => 8 5 2
 * 7 8 9     1 2 3     9 6 3
 */
void rotateMatrix(vector<vector<int> > &matrix) {
    reverse(matrix.begin(), matrix.end());
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = i + 1; j < matrix[i].size(); ++j)
            swap(matrix[i][j], matrix[j][i]);
    }
}
//算法2:先沿着副对角线翻转一次，再沿着水平中线翻转一次
void rotateMatrix2(vector<vector<int> > &matrix) {
    const int n = (int)matrix.size();
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - i; ++j)
            swap(matrix[i][j], matrix[n-1-j][n-1-i]);
    for (int i = 0; i < n/2; ++i)
        for (int j = 0; j < n; ++j)
            swap(matrix[i][j], matrix[n-1-i][j]);
}

//setZeros
//以下算法的复杂度为O(m+n)，可不可能有const space
void setMatrixZeros(vector<vector<int> > &matrix)
{
    const size_t m = matrix.size();
    const size_t n = matrix[0].size();
    vector<bool> row(m, false);
    vectro<bool> col(n, false);
    
    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < n; ++j)
            if (matrix[i][j] == 0)
                row[i] = col[j] = true;
    }
    
    for (size_t i = 0; i < m ; ++i)
        if (row[i])
            fill(&matrix[i][0], &matrix[i][0] + n, 0);
    
    for (size_t j = 0; j < n; ++j)
        if (col[j]){
            for (size_t i = 0; i < m; ++i)
                matrix[i][j] = 0;
        }
}

//利用矩阵的第一行和第一列来作为辅助空间使用。不用开辟新的存储空间
//要点：首先要记录第一行和第一列是不是有零
void setZeroes(vector<vector<int> > &matrix) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int row = matrix.size();
    if(row == 0) return;
    int col = matrix[0].size();
    if(col == 0) return;
    
    bool firstrowiszero = false;
    bool firstcoliszero = false;
    for(int j = 0; j < col; ++j)
        if(matrix[0][j] == 0){
            firstrowiszero = true;
            break;
        }
    for(int i = 0; i < row; ++i)
        if(matrix[i][0] == 0){
            firstcoliszero = true;
            break;
        }
    
    for(int i = 1; i < row; ++i)
        for(int j = 1; j < col; ++j){
            if(matrix[i][j] == 0) {
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }
        }
    
    for(int i = 1; i < row; ++i)
        for(int j = 1; j < col; ++j)
            if(matrix[i][0] == 0 || matrix[0][j] == 0)
                matrix[i][j] = 0;
    
    if(firstrowiszero){
        for(int j = 0; j < col; ++j)
            matrix[0][j] = 0;
    }
    if(firstcoliszero){
        for(int i = 0; i < row; ++i)
            matrix[i][0] = 0;
    }
}




//问题：剑指offer,Divide Two Integers Divide two integers without using multiplication, division and mod operator.
//算法：位运算,加，减（不断减去被除数,这样比较慢，可以每次将被除数翻倍
int divide(int dividend, int divisor) {
    //当dividend = INT_MAX时，-dividend会溢出，所以用long long
    long long a = dividend >= 0 ? dividend : -(long long) dividend;
    long long b = divisor >= 0 ? divisor : -(long long) divisor;
    long long result = 0;
    while (a >= b) {
        long long c = b;
        for (int i =  0; a >= c; ++i) {
            a -= c ;
            result += (1 << i);
            c <<= 1;
        }
    }
    result =  ((dividend^divisor) >> 31) ? (-result) : (result);
    if (result > INT_MAX)
        return INT_MAX;
    return (int) result;
}


//问题：kth largest element
//算法：建立一个大小为k的最小堆
/*
 使用数组中的前k个数构成一个最小堆，然后从第k+1个数开始遍历数组，
 如果遍历的数组元素小于堆顶元素，舍弃掉，如果遍历的数组元素大于堆顶元素，将堆顶元素出堆，
 然后将大于堆顶元素的数组中的元素插入堆中，再次形成堆
 */

//对比：基于partition的思想的速度更快，但是其需要修改原数组，而且其需要一次性将所有数据都读入内存
//不适合于大数据量的情况，而基于红黑树或堆的思想不需要修改原始数组，而且可以从辅助存储空间（磁盘）中
//每次读入一个数字，根据GetLeastNumbers的方式判断是不是要放入容器leastNumbers中，这种思路只要求
//内存能够容纳leastNumbers即可。

int findKthLargest(vector<int>& nums, int k){
    
    make_heap(nums.begin(), nums.begin()+k, greater<int>());//这个建立的是最小堆
    //make_heap默认为最大堆less<int>, Constructs a max heap in the range [first, last)，
    //根节点最大
    
    for(int i = k; i<nums.size();i++) {
        
        int top = nums.front();
        
        if(nums[i] > top) {
            
            pop_heap(nums.begin(),nums.begin()+k,greater<int>());
            
            nums[k-1] = nums[i];
            
            push_heap(nums.begin(),nums.begin()+k,greater<int>()); 
            
        } 
        
    } 
    
    return nums.front();
}
//算法2：使用最大堆也可以求解，就是将整个数组中的元素构成一个最大堆，这时堆顶元素是最大的，
//连续将堆顶元素弹出k-1次后堆顶元素就是第k大的数了
int findKthLargest2(vector<int>& nums, int k)

{
    
    make_heap(nums.begin(), nums.end());
    
    for (int i=1; i<k; i++){
        
        pop_heap(nums.begin(), nums.end());
        
        nums.pop_back();
        
    } 
    
    return nums[0]; 
    
}
//算法2.1：建立一个优先排序队列
int findKthLargest2_1(vector<int>& nums, int k) {
    priority_queue<int> pq; //优先队列就是用heap来实现的
    for (auto n : nums)
        pq.push(n);
    for (int i = 1; i < k; i++)
        pq.pop();
    
    return pq.top();
}
//算法2.2: 建立一个红黑树（可以利用STL里面的set或multiset）
typedef multiset<int, greater<int> >            intSet; //允许重复
typedef multiset<int, greater<int> >::iterator  setIterator;

void GetLeastNumbers_Solution(const vector<int>& data, intSet& leastNumbers, int k)
{
    leastNumbers.clear();
    
    if(k < 1 || data.size() < k)
        return;
    
    vector<int>::const_iterator iter = data.begin();
    for(; iter != data.end(); ++ iter)
    {
        if((leastNumbers.size()) < k)
            leastNumbers.insert(*iter);
        
        else
        {
            setIterator iterGreatest = leastNumbers.begin();
            
            if(*iter < *(leastNumbers.begin()))
            {
                leastNumbers.erase(iterGreatest); //擦除最大值
                leastNumbers.insert(*iter);
            }
        }
    }
}

//算法3：分治法，利用quick sort的思想partition
class Solution_findKthLargest {     //这个比直接用priority_queue效率高多了
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        assert(k > 0 && k <= n);
        if (n == 0)
            return -1;
        int i = 0;
        int j = n - 1;
        while (i <= j) {
            int p = partition(nums, i, j);
            if (p == k - 1)
                return nums[p];
            if (p < k - 1)
                i = p + 1;
            else
                j = p - 1;
        }
    }
    int partition(vector<int>& nums, int left, int right) {
        int pivot = nums[left];
        int i = left;
        for (int j = left + 1; j <= right; j++)
            if (nums[j] >= pivot)
                swap(nums[++i], nums[j]);   //swap的妙用啊，太妙了妙妙妙
        swap(nums[left], nums[i]);
        return i;
    }
};

//问题：Decode ways
//算法：与climing Stairs类似
int numDecodings(const string& s) {
    if (s.empty() || s[0] == '0') return 0;
    int prev = 0;
    int cur = 1;
    //长度为n的字符串，有n+1个阶梯
    for (int i = 1; i <= s.size(); ++i) {
        if (s[i-1] == '0')  cur = 0;
        if (i < 2 || !(s[i-2] == '1' || (s[i-2] == '2' && s[i-1] <= '6')))
            //f(i) = f(i-1) + f(i-2) 但是f(i-1)和f(i-2)会受到很多限制
            //cur代表f(i-1),pre代表f(i-2)
            prev = 0;
        
        int tmp = cur;
        cur = prev + cur;
        prev = tmp;
    }
    return cur;
}
//问题：Climing stairs
//算法：其实是一个动态规划问题，按照原始的动态规划的基本框架，解法如下，空间复杂度为O(n)
#define MAXN  1000
int climbStairs(int n) {
    int f[MAXN];
    memset(f, 1, n+1);
    
    for (int i = 2; i <= n; i++)
        f[i] = f[i-1] + f[i-2];
    return f[n];
}
//算法2：想到第i个值并不需要i-3及以前的值，所以可以将空间复杂度下降到O(1),也就是迭代版
int climbStairs2(int n) {
    int prev, cur;
    prev = 0;
    cur = 1;
    for (int i = 1; i <= n; ++i){
        int tmp = cur;
        cur += prev;
        prev = tmp;
    }
    return cur;
}
//问题：Edit Distance 与hamming distance相似
//算法：二维动态规划，空间复杂度是O(n*m)
int minDistance(string word1, string word2) {
    const int n = (int) word1.size();
    const int m = (int) word2.size();
    //长度为n的字符串，有n+1个隔板
    int f[n+1][m+1];
    for (int i = 0; i <= n; i ++)
        f[i][0] = i;
    for (int j = 0; j <= m; j++)
        f[0][j] = j;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (word1[i-1] == word2[j-1])
                f[i][j] = f[i-1][j-1];
            else {
                int mn = min(f[i-1][j], f[i][j-1]);
                f[i][j] = 1 + min(f[i-1][j-1], mn);
                
            }
            
        }
    }
    return f[n][m];
    
}
//算法2：二维动态规划+滚动数组，时间复杂度O(n*m)，空间复杂度O(n)
int minDistance2(string word1, string word2) {
    if (word1.length() < word2.length())
        return minDistance2(word2, word1);
    
    int f[word2.length() + 1];
    int upper_left = 0; //额外用一个变量记录f[i-1][j-1]
    for (int i = 0; i <= word2.length(); ++i)
        f[i] = i;
    
    for (int i = 1; i <= word1.size(); ++i) {
        upper_left = f[0];
        f[0] = i;
        for (int j = 1; j <= word2.size(); ++j) {
            int upper = f[j];
            if (word1[i-1] == word2[j-1])
                f[j] = upper_left;
            else
                f[j] = 1 + min(upper_left, min(f[j], f[j-1]));
            
            upper_left = upper;
        }
    }
    return f[word2.length()];
    
}
//hamming distance
int hamming_distance(unsigned x, unsigned y)
{
    int dist = 0;
    unsigned  val = x ^ y;
    
    // Count the number of bits set
    while (val != 0)
    {
        // A bit is set, so increment the count and clear the bit
        dist++;
        val &= val - 1;
    }
    
    // Return the number of differing bits
    return dist;
}

//DP。。。DP。。。DP。。。DP。。。go ahead!!!!!!!!!!!!!
//problem: longest common subsequence(LCS)
//algorithm: dynanmic programming.
int LCS(char* x, char* y) {
    int m = (int)strlen(x);
    int n = (int)strlen(y);
    
    int c[m+1][n+1];
    for (int i = 0; i <= m; i++)
        c[i][0] = 0;
    for (int i = 0; i <= n; i++)
        c[0][i] = 0;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
        {
            if (x[i] == y[j])
                c[i][j] = c[i-1][j-1] + 1;
            else
                c[i][j] = max(c[i-1][j], c[i][j-1]);
            
        }
    return c[m][n];
}

//problem: longest common substring(LCS)
//algorithm: 总共有三种方法，暴力搜索、动态规划、后缀树
//dp
int LCS_dp(char * x, char * y)
{
    int xlen = (int)strlen(x);
    int ylen = (int)strlen(y);
    int maxlen = 0, maxindex = 0;
    int dp[xlen][ylen]; //dp[i][j]表示 以x[i]和y[j]结尾的最长公共子串的长度
    for (int i = 0; i < xlen; i++){
        if (x[i] == y[0])
            dp[i][0] = 1;
        else
            dp[i][0] = 0;
    }
    for (int j = 0; j < ylen; j++) {
        if (x[0] == y[j])
            dp[0][j] = 1;
        else
            dp[0][j] = 0;
    }
    for(int i = 1; i < xlen; ++i)
    {
        for(int j = 1; j < ylen; ++j)
        {
            if(x[i] == y[j]){
                dp[i][j] = dp[i-1][j-1] + 1;
            }else
                dp[i][j] = 0;
            
            if(dp[i][j] > maxlen)
            {
                maxlen = dp[i][j];
                maxindex = i + 1 - maxlen;
            }
        }
    }
    return maxlen;
}
//另一种实现方法
int LongestCommonSubstring(const char * strA, const char * strB)
{
    char * LCS = NULL;
    const size_t LengthA = strlen(strA);
    const size_t LengthB = strlen(strB);
    size_t LCSLength = 0;
    unsigned int PositionX = 0;
    unsigned int PositionY = 0;
    
    int i, j;
    int Matrix[LengthA + 1][LengthB + 1];;
    
    for(i = 0; i < LengthA+1 ; ++i)
    {
        for(j = 0; j < LengthB+1 ; ++j)
        {
            Matrix[i][j] = 0;
        }
    }
    
    for(i = 0; i < LengthA+1; ++i)
    {
        for(j = 0; j < LengthB+1; ++j)
        {
            if(strA[i] == strB[j])
            {
                if((i == 0)||(j == 0))
                    Matrix[i][j] = 1;
                else
                    Matrix[i][j] = Matrix[i - 1][j - 1] + 1;
            }
            if(Matrix[i][j] > LCSLength)
            {
                LCSLength = Matrix[i][j];
                PositionX = i;
                PositionY = j;
            }
        }
    }
    return (int) LCSLength;
}


//问题：longest increasing subsequence(LIS)
//算法：动态规划，复杂度为O(n2)
//F[i]表示从1到i这一段中以i结尾的最长上升子序列的长度
//f[i] = max(f[j] + 1, 1), j < i && A[j] <= A[i]    //有一个1是有可能A[i]比前面所有的元素都小，只能自成一个最长上升子序列
int lis(int A[], int n){
    int *f = new int[n];
    int len = 1;
    for(int i=0; i<n; ++i){
        f[i] = 1;       //默认肯定都为1
        for(int j=0; j<i; ++j)
            if(A[j] <= A[i] && f[j]+1 > f[i])
                f[i] = f[j] + 1;
        if(f[i] > len)
            len = f[i];
    }
    delete[] f;
    return len;
}
//算法2：贪心算法+二分查找
int bsearch(int c[],int n,int a)
{
    
    int l = 1, r = n;
    int mid = 0;
    while(l<=r)
    {
        mid = (l+r)/2;
        if( a > c[mid] && a <= c[mid+1] )
            break; // >&&<= 换为: >= && <
        else if( a < c[mid] )
            r = mid-1;
        else l = mid+1;
    }
    return mid+1;
}

template<class T>
int LIS2(T a[], int n)
{
    int i, j, size = 1;
    T *c=new T[n+1];
    int *dp=new int[n+1];
    c[1] = a[1]; dp[1] = 1;
    
    for(i=2;i<=n;++i)
    {
        if( a[i] <= c[1] ) j = 1;// <= 换为: <
        else if( a[i] >c[size] )
            j=++size;   // > 换为: >=
        else
            j = bsearch(c, size, a[i]);
        c[j] = a[i]; dp[i] = j;
    }
    return size;
    
}

//问题：0/1背包问题
//算法：动态规划
#define MAXN 100
#define MAXC 1000
int d[MAXN][MAXC];
int bag01(vector<int> V, vector<int> W, int C) { //C表示最大重量，V表示价值，W表示重量
    if (C == 0) return 0;
    int n = (int) V.size();
//    vector<vector<int> > d(n+1);
//    for (int i = 0; i <= n; i ++) {
//        d[i].assign(C, 0);
//    }//这样会出问题，提示过度释放
    for (int i = 0; i <= n; ++i){
        for (int j=0; j<=C; ++j){
            d[i][j] = i ==0 ? 0 : d[i-1][j];
            if (i > 0 && j >= W[i-1])
                d[i][j] = max(d[i-1][j-W[i-1]]+V[i-1], d[i-1][j]);
        }
    }
    //打印出
    printf("%d\n", d[n][C]);
    
    //输出打印方案，这与动态系统的基本框架很像
    int j = C;
    int y[n];//这叫动态数组，早期的C标准不支持，现在支持了，只是大小定下来之后就不能再变了
    int* x = (int*) malloc(sizeof(int) * n);
    memset(x, 0, sizeof(int) * n);
    for(int i = n; i>0; --i){
        if(d[i][j] > d[i-1][j]){
            x[i-1] = 1;
            j = j - W[i-1];
        }
    }
    
    for(int i=0; i<n; ++i)
        printf("%d ", x[i]);
    printf("\n");
    delete [] x;
    
    return d[n][C];
}

//问题：Minimum Path Sum
//算法：二维动态规划, 占用空间O(n2)
int minPathSum(vector<vector<int> > & grid) {
    if (grid.size() == 0)   return 0;
    int m = (int) grid.size();
    int n = (int) grid[0].size();
    
    int f[m][n];
    f[0][0] = grid[0][0];
    for (int i = 1; i < m; i++) {
        f[i][0] = f[i-1][0] + grid[i][0];
    }
    
    for (int i = 1; i < n; i++) {
        f[0][i] = f[0][i - 1] + grid[0][i];
    }
    
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            f[i][j] = min(f[i-1][j], f[i][j-1]) + grid[i][j];
        }
    }
    return f[m-1][n-1];
}
//算法2：动态规划+滚动数组，只需O(n)的空间
int minPathSum2(vector<vector<int> > &grid) {
    int m = grid.size(), n = grid[0].size();
    vector<int> dp(n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0) {
                if (j == 0) {
                    dp[j] = grid[i][j];
                }
                else {
                    dp[j] = dp[j-1] + grid[i][j];
                }
            }
            else if (j == 0) {
                dp[j] = dp[j] + grid[i][j];
            }
            else
                dp[j] = min(dp[j-1], dp[j]) + grid[i][j];
        }
        
    }
    
    return dp[n-1];
}

//算法3：Unique Paths, 没有了权重，看有多少条路径可以从start点，只能向下的向前走，通到finish点
class Solution {
    
public:
    int uniquePaths(vector<vector<int> >&grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int> > dp(m, vector<int>(n, 1));
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                    dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }
    
    //滚动数组+动态规划
    int uniquePaths(vector<vector<int> >&grid) {
        int m = grid.size(), n = grid[0].size();
        vector<int> dp(n, 0);
        dp[0] = 1;
        for(int i = 0; i < m; i++ ) {
            for (int j = 1; j < n; j++) {
                dp[j] = dp[j-1] + dp[j];
            }
        }
        return dp[n-1];
    }

    int uniquePathsWithObstacles(vector<vector<int> >&grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int> > dp(m+1, vector<int>(n+1, 0));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == 1 && j == 1) {
                    if (grid[0][0]) return 0;
                    dp[1][1] = 1;
                    continue;
                }
                if (!grid[i-1][j-1])
                    dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        return dp[m][n];
    }
    
    //动态规划+滚动数组
    int uniquePathsWithObstacles(vector<vector<int> >&grid) {
        int m = grid.size(), n = grid[0].size();
        vector<int> dp(n,0);
        if (grid[0][0] || grid[m-1][n-1]) return 0;
        dp[0] = 1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j])
                    dp[j] = 0;
                else {
                    if (j > 0)  //这个条件还是要满足
                        dp[j] = dp[j-1]+ dp[j];
                }
            }
        }
        return dp[n-1];
    }
};

//问题：Triangle 路径求最小和（ 动态规划问题）
//算法：动态规划，用了O(n2)的空间
int minimumTotal(vector<vector<int> > &triangle) {

    if(triangle.size() == 0)
        return 0;
    int n = (int) triangle.size();
    vector<vector<int> > dp(n+1);
    for(int i = 0; i <= n; ++i)
        dp[i].assign(n+1, INT_MAX);
    
    dp[1][1] = triangle[0][0];
    for(int i = 2; i <= n; ++i)
    {
        for(int j = 1; j <= i; ++j)
        {
            dp[i][j] = min(dp[i-1][j-1], dp[i-1][j]) + triangle[i-1][j-1];
        }
    }
    //output
    int ans = INT_MAX;
    for(int j = 1; j <= n; ++j)
        ans = min(dp[n][j], ans);
    return ans;
}
//算法：动态规划，只用了O(n)的额外空间
int minimumTotal2(vector<vector<int> > &triangle) {
    
    if (triangle.size() == 0)
        return 0;
    
    vector<int> f(triangle[triangle.size()-1].size());
    
    f[0] = triangle[0][0];
    for(int i = 1; i < triangle.size(); i++)
        for(int j = (int)triangle[i].size() - 1; j >= 0; j--)
            if (j == 0)
                f[j] = f[j] + triangle[i][j];
            else if (j == triangle[i].size() - 1)
                f[j] = f[j-1] + triangle[i][j];
            else
                f[j] = min(f[j-1], f[j]) + triangle[i][j];
    
    int ret = INT_MAX;
    for(int i = 0; i < f.size(); i++)
        ret = min(ret, f[i]);
    
    return ret;
}
//算法：动态规划，使用空间O(1),从低往高
int minimumTotal3(vector<vector<int> >& triangle) {
    for (int i = (int) triangle.size() - 2; i >= 0; --i)
        for (int j = 0; j < i + 1; ++j)
            triangle[i][j] += min(triangle[i+1][j], triangle[i+1][j+1]);
    return triangle[0][0];
}

//问题： Palindrome Partitioning II
//算法： 动态规划
int minCutNums(string s) {
    const int n = (int) s.size();
    int f[n+1];
    bool p[n][n];
    fill_n(&p[0][0], n*n, false);
    for (int i = 0; i <= n; i++)
        f[i] = n - 1 - i;   //最后一个f[n] = -1
    for (int i = n-1; i >=0; i--) {
        for (int j = i; j < n; j++) {
            if (s[i] == s[j] && (j - i < 2 || p[i+1][j-1])) {
                p[i][j] = true;
                f[i] = min(f[i], f[j+1] + 1);
            }
        }
    }
    return f[0];
}

/*
 Interleaving String:
 
 
 Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.
 
 For example,
 Given:
 s1 = "aabcc",
 s2 = "dbbca",
 
 When s3 = "aadbbcbcac", return true.
 When s3 = "aadbbbaccc", return false.
 
 试了下跟归并一样的贪心思路，果然是不行的，比如 s1= "aa", s2="ab", s3="aaba" 贪心就不行，因为在s1[i] ,s2[j] 都和s3中字母相等的时候，你不知道应该用哪一个。
 那就老老实实DP吧，下面空间还可以优化成O(n)的。
 */
//刚开始我也是用了贪心，但是发现贪心会出现问题，所以改为动态规划了
/*
 设状态 f[i][j]，表示 s1[0,i-1] 和 s2[0,j-1]，匹配 s3[0, i+j-1]。如果 s1 的最后一个字符等于 s3 的最后一个字符，则 f[i][j]=f[i-1][j]；如果 s2 的最后一个字符等于 s3 的最后一个字符，则 f[i][j]=f[i][j-1]。
 因此状态转移方程如下：
 f[i][j] = 
           (s1[i - 1] == s3 [i + j - 1] && f[i - 1][j])
        || (s2[j - 1] == s3 [i + j - 1] && f[i][j - 1]);
 */
//二维动态规划，画一个矩阵就可以理解了
class Solution_Interleaving {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.size();
        int n = s2.size();
        if(m+n != s3.size())
            return false;
        vector<vector<bool> > path(m+1, vector<bool>(n+1, false));
        for(int i = 0; i < m+1; i ++)
        {
            for(int j = 0; j < n+1; j ++)
            {
                if(i == 0 && j == 0)
                    // start
                    path[i][j] = true;
                else if(i == 0)
                    path[i][j] = path[i][j-1] & (s2[j-1]==s3[j-1]);
                else if(j == 0)
                    path[i][j] = path[i-1][j] & (s1[i-1]==s3[i-1]);
                else
                    path[i][j] = (path[i][j-1] & (s2[j-1]==s3[i+j-1])) || (path[i-1][j] & (s1[i-1]==s3[i+j-1]));
            }
        }
        return path[m][n];
    }
};

//滚动数组，只需要O(n)的空间复杂度
bool isInterleave(string s1, string s2, string s3) {
    int m = s1.size();
    int n = s2.size();
    if(m+n != s3.size())
        return false;
    if (s1.size() < s2.size())
        return isInterleave(s2, s1, s3);
    vector<bool>  path(n+1, false);         //选短了那一个
    for(int i = 0; i < m+1; i ++)
    {
        for(int j = 0; j < n+1; j ++)
        {
            if(i == 0 && j == 0)
                // start
                path[i][j] = true;
            else if(i == 0)
                path[i][j] = path[i][j-1] & (s2[j-1]==s3[j-1]);
            else if(j == 0)
                path[i][j] = path[i-1][j] & (s1[i-1]==s3[i-1]);
            else
                path[i][j] = (path[i][j-1] & (s2[j-1]==s3[i+j-1])) || (path[i-1][j] & (s1[i-1]==s3[i+j-1]));
        }
    }
    return path[m][n];
}

/*
 Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.
 
 For example:
 
 Given "aacecaaa", return "aaacecaaa".
 
 Given "abcd", return "dcbabcd"
 */
string shortestPalindrome(string s)  {
    string str = s;
    reverse(str.begin(), str.end());
    
    int i, k;
    int l = (int)s.length();
    for (i = l; i >= 0; i-- ) {
        string tmps1 = s.substr(0, i);
        string tmps2 = str.substr(l - i);
        if (tmps1.compare(tmps2) == 0)
            break;
    }
    return str.substr(0,l - i) + s;
    
}

//判断一个string 是不是palindrome
bool isPalindrome(string s) {
    int n = s.size();
    if (n == 0 || n == 1) return true;
    int i = 0, j = n - 1;
    while (i <= j) {
        if (isalnum(s[i]) && isalnum(s[j]))
            //if (s[i] == s[j] || tolower(s[i]) == tolower(s[j]) ) {
            if (s[i] == s[j] || abs(s[i] - s[j]) == 32) {
                i++;
                j--;
                continue;
            }
            else
                return false;
        if (!isalnum(s[i]))
            i++;
        if (!isalnum(s[j]))
            j--;
        
    }
    return true;
    
}

/*
 最长回文子串 longest palindrome substring
 */
class Solution {
public:
    string longestPalindrome2(string s) {    //600ms
        int n = s.size(), ss = 0, tt = 0;
        int max = -1;
        bool flag[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i >= j)
                    flag[i][j] = true;
                else
                    flag[i][j] = false;
            }
        }
        
        for (int j = 1; j < n; j++) {
            for (int i = 0; i < j; i++) {
                if (s[i] == s[j]) {
                    flag[i][j] = flag[i+1][j-1];
                    if (flag[i][j] && j - i + 1 >= max) {
                        max = j - i + 1;
                        ss = i;
                        tt = j;
                    }
                }
                else
                    flag[i][j] = false;
            }
        }
        
        return s.substr(ss, max);
    }
    
    //这是从中间开始搜素
    std::string longestPalindrome(std::string s) {//8ms
        if (s.size() < 2)
            return s;
        int len = s.size(), max_left = 0, max_len = 1, left, right;
        for (int start = 0; start < len && len - start > max_len / 2;) {
            left = right = start;
            while (right < len - 1 && s[right + 1] == s[right]) //跳过重复的字符
                ++right;
            start = right + 1;
            while (right < len - 1 && left > 0 && s[right + 1] == s[left - 1]) {
                ++right;
                --left;
            }
            if (max_len < right - left + 1) {
                max_left = left;
                max_len = right - left + 1;
            }
        }
        return s.substr(max_left, max_len);
    }
};


//用KMP方法
/*
 求字符串s的翻转s_rev
 将两个字符串进行拼接：{s}#{s_rev}
 找出新字符串中最长公共前缀后缀长度comLen
 s_rev.substring(0, s.length() - comLen)就是在原字符串头部插入的子串部分
 */
string shortestPalindrome2(string s) {
    string r = s;
    reverse(r.begin(), r.end());
    string t = s + "#" + r;
    vector<int> p(t.size(), 0);
    for (int i = 1; i < t.size(); ++i) {
        int j = p[i - 1];
        while (j > 0 && t[i] != t[j]) j = p[j - 1];
        p[i] = (j += t[i] == t[j]);
    }
    return r.substr(0, s.size() - p[t.size() - 1]) + s;
}


//这空间复杂度为O(n)
bool isPalindromeList(ListNode* pHead) {
    // write code here
    if(pHead == NULL)
        return true;
    stack<int> ss;
    ListNode* p = pHead;
    ListNode* q = pHead;
    ss.push(p->val);
    while(q->next != NULL && q->next->next != NULL)
    {
        p = p->next;
        ss.push(p->val);
        q = q->next->next;
    }
    if(q->next == NULL) //长度为奇数
        ss.pop();
    p = p->next;
    while(!ss.empty())
    {
        if(ss.top() != p->val)
            break;
        p = p->next;
        ss.pop();
    }
    if(ss.empty())
        return true;
    else
        return false;
}
};

bool isPalindromeList2(ListNode* pHead) {
    // write code here
    if (pHead == NULL)
        return false;
    vector<int> vList;
    while (pHead) {
        vList.push_back(pHead->val);
        pHead = pHead->next;
    }
    int num = vList.size();
    int i = 0, j = num - 1;
    while(i < j) {
        if (vList[i++] != vList[j--])
            return false;
    }
    return true;
}

//这的空间复杂度是O(1)
/*
 Given a singly linked list, determine if it is a palindrome.
 
 Follow up:
 Could you do it in O(n) time and O(1) space?
 
 判断一个链表的所有元素是否为回文，本身没什么难度，但是O(1)的空间复杂度就麻烦点了：将链表分裂为两个等长的链表，然后逆序其中一个，最后逐个比较两个链表的每个元素，如果全部相等就是Palindrome lsit，但是需要考虑链表长度为奇数的情况。
 */

/*
 1. 获取链表的中点,使用龟兔算法的方法，两个指针，一个遍历速度是另外一个的两倍，找到中点
 2. 然后反转链表的后半部分
 3. 对比链表的前后两个部分是否一样
 4. 最后将原链表的后半部分反转恢复原来的链表(恢复作案现场)
 */
bool isPalindrome3(ListNode* head) {
    if (head == nullptr) {
        return true; // IMHO this should be false but is true in leetcode oj
    }
    if (head->next == nullptr) {
        return true;
    }
    // get the len of the list, 链表奇数或者偶数节点需要判断（如果为奇数那么就删除最后的栈顶）。
    int len = 0;
    for (auto ptr = head; ptr != nullptr; ptr = ptr->next) {
        len++;
    }
    // get the header of another half of the list
    //这下面也可以用快慢指针，指向链表的中间节点，同样也要考虑奇偶性
    int nl = len / 2;
    auto ptr = head;
    for (int i = 0; i != nl; ++i) {
        ptr = ptr->next;
    }
    if (len % 2 != 0) { //
        ptr = ptr->next;
    }
    // reverse another half
    ListNode* pre = nullptr;
    auto cur = ptr;
    while (cur != nullptr) {
        auto post = cur->next;
        cur->next = pre;
        pre = cur;
        cur = post;
    }
    ptr = pre;
    
    // compare two half list
    for (int i = 0; i != nl; ++i) {
        if (ptr->val != head->val) {
            return false;
        }
        ptr = ptr->next;
        head = head->next;
    }
    return true;
}

//利用快慢指针找到中间元素，然后将后半链表reverse，依次比较
class Solution_palin {
public:
    bool isPalindrome(ListNode* head) {
        if (head == NULL || head->next == NULL)
            return true;
        ListNode* p = head;
        ListNode* q = head;
        while(q != NULL && q->next!= NULL) {//快慢指针的判断条件容易出错，注意不能只单独判断q->next是否为空，如果q本身就为空的话，会runtime error
            p = p->next;
            q = q->next->next;
        }
        ListNode* mid = (q == NULL) ? p : p->next;
        ListNode* mid_reverse = reverseList(mid);
        ListNode* r = mid_reverse;
        while (r != NULL) {
            if (r->val != head->val)
                return false;
            r = r->next;
            head = head ->next;
        }
        //reverseList(mid_reverse);
        return true;
    }
    
private:
    ListNode* reverseList(ListNode* head) {
        if (head == NULL)
            return NULL;
        ListNode * p = head;
        ListNode * q = head->next;
        p->next = NULL;
        while (q != NULL) {
            p = q;
            q = p->next;
            p->next = head;
            head = p;
        }
        return head;
    }
};


//问题：Integer to English Words
//算法：先处理999以内的数，再大的数就可以类推
string convertHundred(int num);

string numberToWords(int num) {
    string res = convertHundred(num % 1000);
    vector<string> v = {"Thousand", "Million", "Billion"};
    for (int i = 0; i < 3; ++i) {
        num /= 1000;
        res = num % 1000 ? convertHundred(num % 1000) + " " + v[i] + " " + res : res;
    }
    while (res.back() == ' ') res.pop_back();
    return res.empty() ? "Zero" : res;
}

string convertHundred(int num) {
    vector<string> v1 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    vector<string> v2 = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    string res;
    int a = num / 100, b = num % 100, c = num % 10;
    res = b < 20 ? v1[b] : v2[b / 10] + (c ? " " + v1[c] : "");
    if (a > 0) res = v1[a] + " Hundred" + (b ? " " + res : "");
    return res;
}

//问题：判断一个完全二叉树的节点个数
//算法：递归调用，动态规划问题
int countNodes(TreeNode* root) {
    if (NULL == root)   return 0;
    
    int leftHeight = 1;
    int rightHeight = 1;
    TreeNode *p = root->left;
    while (p != NULL){
        leftHeight++;
        p = p->left;
    }
    
    p = root->right;
    while (p != NULL){
        rightHeight++;
        p = p->right;
    }
    
    if (leftHeight == rightHeight)  return (1 << leftHeight) - 1;
    
    return countNodes(root->left) + countNodes(root->right) + 1;
}

//问题：Combination Sum
//算法：利用回溯剪枝法，使用DFS深度优先搜索策略
class Solution_combinationSum {
public:
    vector<vector<int>> combinationSum(vector<int>& v, int target) {
        sort(v.begin(), v.end());
        vector<vector<int> > result;
        vector<int> cur;
        dfs(v, target, 0, cur, result);
        return result;
    }
    
    void dfs(vector<int>& v, int gap, int start, vector<int> & cur, vector<vector<int> > &result) {
        if (gap == 0) {
            result.push_back(cur);
            return;
        }
        for (int i = start; i < v.size(); i++) {
            if (gap < v[i])
                return;
            cur.push_back(v[i]);
            dfs(v, gap - v[i], i, cur, result);
            cur.pop_back();
        }
    }
    
};

//问题：Combination Sum2
//算法：利用回溯剪枝，注意防止重复
class Solution_combinationSum2 {
public:

    vector<vector<int>> combinationSum2(vector<int>& v, int target) {
        sort(v.begin(), v.end());
        vector<vector<int> > result;
        vector<int> cur;
        dfs(v, target, 0, cur, result);
        return result;
    }
    
    void dfs(vector<int>& v, int gap, int start, vector<int> & cur, vector<vector<int> > &result) {
        if (gap == 0) {
            result.push_back(cur);
            return;
        }
        for (int i = start; i < v.size(); i++) {
            if (gap < v[i])
                return;
            cur.push_back(v[i]);
            dfs(v, gap - v[i], i + 1, cur, result);     //与上面的差别
            cur.pop_back();
            while (i < v.size() - 1 && v[i] == v[i+1])  //与上面的差别
                i++;
        }
    }
};

//问题：reverse sentence of words
//算法：利用两个栈，一个用于存放单词，一个用于存放句子
void reverseWords(string &s) {
    stack<int> word;
    stack<int> sentence;
    int i = 0;
    
    while(i <= s.size()){
        if(i == s.size() || s[i] == ' '){
            if(!word.empty()){
                if(!sentence.empty()){
                    sentence.push(' ');
                }
                while(!word.empty()){
                    sentence.push(word.top());
                    word.pop();
                }
            }
        } else{
            word.push(s[i]);
        }
        i++;
    };
    
    s.clear();
    while(!sentence.empty()){
        s.push_back(sentence.top());
        sentence.pop();
    };
}
//算法2：以上算法并不高效，需要额外的空间
void reverseWords2(string & s)
{
    
    string ss;
    int i = (int) s.length()-1;
    while(i>=0)
    {
        while(i>=0&&s[i] == ' ')
        {
            i --;
        }
        if(i<0) break;
        if(ss.length()!=0)
            ss.push_back(' ');
        string temp ;
        for(;i>=0&&s[i]!=' ';i--)
            temp.push_back(s[i]);
        reverse(temp.begin(),temp.end());
        ss.append(temp);
    }
    s=ss;
}
//algorithm3: swordoffer标准答案
void reverseString(char *pBegin, char *pEnd)
{
    if(pBegin == NULL || pEnd == NULL)
        return;
    
    while(pBegin < pEnd)
    {
        char temp = *pBegin;
        *pBegin = *pEnd;
        *pEnd = temp;
        
        pBegin ++, pEnd --;
    }
}

char* ReverseSentence(char *pData)
{
    if(pData == NULL)
        return NULL;
    
    char *pBegin = pData;
    
    char *pEnd = pData;
    while(*pEnd != '\0')
        pEnd ++;
    pEnd--;
    
    reverseString(pBegin, pEnd);
    
    pBegin = pEnd = pData;
    while(*pBegin != '\0')
    {
        if(*pBegin == ' ')
        {
            pBegin ++;
            pEnd ++;
        }
        else if(*pEnd == ' ' || *pEnd == '\0')
        {
            reverseString(pBegin, --pEnd);
            pBegin = ++pEnd;
        }
        else
        {
            pEnd ++;
        }
    }
    
    return pData;
}
//左旋转一个字符串
char* LeftRotateString(char* pStr, int n)
{
    if(pStr != NULL)
    {
        int nLength = static_cast<int>(strlen(pStr));
        if(nLength > 0 && n > 0 && n < nLength)         //边界检测和错误输入处理
        {
            char* pFirstStart = pStr;
            char* pFirstEnd = pStr + n - 1;
            char* pSecondStart = pStr + n;
            char* pSecondEnd = pStr + nLength - 1;
            
            reverseString(pFirstStart, pFirstEnd);
            reverseString(pSecondStart, pSecondEnd);
            reverseString(pFirstStart, pSecondEnd);
        }
    }
    
    return pStr;
}


//问题：最大间隙问题Maximum gap
/*
 给定一个未排序的数组，找到该数组在排序形式下，连续两个数字相减得到差的最大值。 尽可能找到一个满足线性的时间和空间复杂度的方法。 如果数组中元素个数少于2个，则返回0。 给定假设：数组中所有的元素都是非负的整数，4字节。
 */
//算法：采用桶结构
int maximumGap(vector<int>& nums) {
    int n = nums.size();
    if (n == 0 || n == 1)
        return 0;
    int minElement = INT_MAX;
    int maxElement = INT_MIN;
    for (int i = 0; i < n; i ++) {
        minElement = min(minElement, nums[i]);
        maxElement = max(maxElement, nums[i]);
    }
    
    vector<int> minVec(n-1, INT_MAX);
    vector<int> maxVec(n-1, INT_MIN);
    if (maxElement == minElement)
        return 0;
    double gap = (maxElement - minElement) / (1.0 * (n - 1));
    for (int i = 0; i < n; i++) {
        if (nums[i] != maxElement) {
            int index = (int)(nums[i] - minElement) / gap;
            minVec[index] = min(minVec[index], nums[i]);
            maxVec[index] = max(maxVec[index], nums[i]);
        }
    }
    int maximumGap = -1;
    int curMax = maxVec[0];
    for (int i = 1; i < n-1; i++) {
        if (minVec[i] != INT_MAX) {
            maximumGap = max(maximumGap, minVec[i] - curMax);
            curMax = maxVec[i];
        }
    }
    
    return max(maximumGap, maxElement - curMax);
    
    
}


//问题：word break
//算法：使用动态规划，列出转移方程，注意初始化的设定，动态规划两个方面：1. 初始化；2. 动态转移方程
bool wordBreak(string s, unordered_set<string>& wordDict) {
    vector<bool> f(s.size()+1, false);
    f[0] = true;
    for (int i = 1; i <= s.size(); ++i) {
        for (int j = i - 1; j >= 0; --j) {
            if (f[j] && wordDict.find(s.substr(j, i - j)) != wordDict.end()) {
                f[i] = true;
                break;
            }
        }
    }
    return f[s.size()];
}

//问题：word break II
/*
Given a string s and a dictionary of words dict, add spaces in s to construct a sentence where each word is a valid dictionary word.

Return all such possible sentences.

For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"].
*/
//算法：使用动态规划，除了使用word break的代码之外，还需要一种数据结构来记录分词的位置
void gen_path(const string &s, const vector<vector<bool> > &prev, int cur, vector<string> &path,
              vector<string> &result){
    //DFS遍历树，生成路径
    if (cur == 0) {
        string tmp;
        for (auto iter = path.crbegin(); iter != path.crend(); ++iter)
            tmp += *iter + " ";
        tmp.erase(tmp.end() - 1);
        result.push_back(tmp);
    }
    for (int i = 0; i < s.size(); ++i) {
        if (prev[cur][i]) {
            path.push_back(s.substr(i, cur - i));
            gen_path(s, prev, i , path, result);
            path.pop_back();
        }
    }
}

vector<string> wordBreak2(string s, unordered_set<string>& wordDict) {
    vector<bool> f(s.size()+1, false);
    vector<vector<bool> > prev(s.length()+1, vector<bool>(s.length())); //记录分词的位置
    //prev[i][j]为true表示s[j,i)是一个合法单词,可以从j处切开
    
    f[0] = true;
    for (int i = 1; i <= s.size(); ++i) {
        for (int j = i - 1; j >= 0; --j) {
            if (f[j] && wordDict.find(s.substr(j, i - j)) != wordDict.end()) {
                f[i] = true;
                prev[i][j] = true;
            }
        }
    }
    
    vector<string> result;
    vector<string> path;
    gen_path(s, prev, (int)s.length(), path, result);
    return result;
}


/*
 Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing all ones and return its area
 */
class Solution_maximalRectangle {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = (int)matrix.size();
        if (m == 0)
            return 0;
        int n = (int)matrix[0].size();
        int max = -1;
        for (int i = 0; i < m; i++) {
            int* arr = new int[n];
            for (int k = 0; k < n; k++) {
                arr[k] = 0;
            }
            
            for (int j = i; j < m; j++) {
                for (int k = 0; k < n; k++) {
                    arr[k] += matrix[j][k] - '0';
                }
                int maxsum = maximalArray(arr, n, j - i + 1) * (j - i + 1);
                if (maxsum > max)
                    max = maxsum;
            }
        }
        return max;
    }
    
private:
    int maximalArray(int a[], int  n, int target) {
        if (n == 0)
            return -1;
        
        int max = 0;
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] == target)
                count++;
            else {
                if (count > max)
                    max = count;
                count = 0;
            }
        }
        return count > max ? count : max;
        
    }
};

/*
 Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.
 
 For example,
 Given nums = [0, 1, 3] return 2.
 
 Note:
 Your algorithm should run in linear runtime complexity. Could you implement it using only constant extra space complexity?
 */
class Solution_missingNumber {
public:
    int missingNumber(vector<int>& nums) {  //这种方法比直接求和更好，但是极端情况下也有可能溢出
        int n = nums.size();
        assert(n > 0);
        int sum = 0;
        for (int i= 0; i < n; i++) {
            sum += nums[i] - i;
        }
        int result = n - sum;
        return result;
    }
    int missingNumber1(vector<int>& nums) {
        int n = nums.size();
        int x = nums[0] ^ 0;
        for (int i = 1; i < n; i++){
            x ^= nums[i] ^ i;           //不可能溢出
        }
        x ^= n;
        return x;
    }
};

/*
 [Leetcode] Maximal Rectangle
 Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing all ones and return its area.
 
 给定一个矩阵中，只有0和1，求出这个矩阵的一个最大的子矩阵，其中只包含1.
 
 例如
 
 01101
 
 11010
 
 01110
 
 11110
 
 11111
 
 00000
 
 其实这个问题可以转化为Largest Rectangle in Histogram，先将上面的矩阵转化为：
 
 01101
 
 12010
 
 03110
 
 14210
 
 25321
 
 00000
 
 然后对每一行求直方图的最大面积。
 */
class Solution_maximalRectangle2 {
public:
    int maxArea(vector<int> &line) {
        if (line.size() < 1) return 0;
        stack<int> S;
        line.push_back(0);
        int sum = 0;
        for (int i = 0; i < line.size(); i++) {
            if (S.empty() || line[i] > line[S.top()]) S.push(i);
            else {
                int tmp = S.top();
                S.pop();
                sum = max(sum, line[tmp]*(S.empty()? i : i-S.top()-1));
                i--;
            }
        }
        return sum;
    }
    
    int maximalRectangle(vector<vector<char> > &matrix) {
        if (matrix.size() < 1) return 0;
        int n = matrix.size();
        if (n == 0) return 0;
        int m = matrix[0].size();
        if (m == 0) return 0;
        vector<vector<int> > lines(n, vector<int>(m, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i == 0) {
                    lines[i][j] = ((matrix[i][j] == '1') ? 1 : 0);
                } else {
                    lines[i][j] += ((matrix[i][j] == '1') ? lines[i-1][j] + 1 : 0);
                }
            }
        }
        int maxRec = 0, tmpRec;
        for (int i = 0; i < n; ++i) {
            tmpRec = maxArea(lines[i]);
            maxRec = (maxRec > tmpRec) ? maxRec : tmpRec;
        }
        return maxRec;
    }
};



//问题：Symmetric tree
//算法：递归或利用栈的迭代
bool isSymmetric(TreeNode* left, TreeNode* right);
bool isSymmetric(TreeNode* root) {
    return root ? isSymmetric(root->left, root->right) : true;
}

bool isSymmetric(TreeNode* left, TreeNode* right) {
    if (!left && !right)    return true;
    if (!left || !right)    return false;
    return left->val == right->val
    && isSymmetric(left->left, right->right)
    && isSymmetric(left->right, right->left);
}

//算法：迭代版
bool isSymmetric2(TreeNode* root) {
    if (!root) return true;
    stack<TreeNode*> s;
    s.push(root->left);
    s.push(root->right);
    
    while (!s.empty()) {
        TreeNode* p = s.top(); s.pop();
        TreeNode* q = s.top(); s.pop();
        if (!p && !q)   continue;
        if (!p || !q)   return false;
        if (p->val != q->val)   return false;
        s.push(p->left);
        s.push(q->right);
        
        s.push(p->right);
        s.push(q->left);
    }
    return true;
}

//问题：longest common prefix
//算法：
string longestCommonPrefix_(vector<string>& strs) {
    if (strs.empty()) return "";
    
    string first = strs[0];
    for (int i = 0; i < first.size(); i++)
    {
        for (int j = 1; j < strs.size(); j++)
            if (strs[j][i] != first[i])
                return first.substr(0, i);
        
    }
    return first;
}

//问题：2sum
//算法：利用hash_map，可以获得O(1)的search
vector<int> twoSum_(vector<int>& nums, int target) {
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

//问题：next_permutation
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
    int y;                                  //x右边大于nums[x]的最小值
    for (y = n-1; nums[y] <= nums[x]; --y);
    swap(nums[x], nums[y]);
    reverse(nums.begin() + x + 1, nums.end());
    
}

//problem: add two binary string, string加法，字符串加法，下面有一个字符串乘法
//Given two binary strings, return their sum (also a binary string)
//algorithm: 下面的打印大数，将下面的2改为10就可以用来对string进行大数加法
string addBinaryString(string a, string b){
    string result;
    int al = a.size();
    int bl = b.size();
    
    const size_t n = al > bl ? al: bl;
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    
    int carry = 0;
    for (size_t i = 0; i < n; i++){
        const int ai = i < al ? a[i] - '0' : 0;
        const int bi = i < bl ? b[i] - '0' : 0;
        const int val = (ai + bi + carry) % 2;
        carry = (ai + bi + carry) / 2;
        result.insert(result.begin(), val+'0');//这一步不能用+吗？string的+不能加字符？？？？？？？？？
    }
    
    if (carry == 1){
        result.insert(result.begin(), '1');
    }
    
    return result;
}

//problem: 打印出n位的数,用字符数组来解决大数问题，也可以用字符串类string来表示并计算大数
//algorithm: 这也是个大数问题
void PrintNumber(char* number);//关键问题在于前面的零不要打印出来
bool Increment(char* number); //加一，最关键的问题是判断什么时候加到了最大值

void Print1ToMaxOfNDigits_1(int n)
{
    if(n <= 0)
        return;
    
    char *number = new char[n + 1];
    memset(number, '0', n);  //刚开始在所有的位上都初始化为‘0’
    number[n] = '\0';
    
    while(!Increment(number))
    {
        PrintNumber(number);
    }
    
    delete []number;
}

bool Increment(char* number)
{
    bool isOverflow = false;
    int carry = 0;
    int nLength = (int)strlen(number);
    
    for(int i = nLength - 1; i >= 0; i --)
    {
        int nSum = number[i] - '0' + carry;
        if(i == nLength - 1)
            nSum ++;
        
        if(nSum >= 10)
        {
            if(i == 0)
                isOverflow = true;
            else
            {
                nSum -= 10;
                carry = 1;
                number[i] = '0' + nSum;
            }
        }
        else
        {
            number[i] = '0' + nSum;
            break;
        }
    }
    
    return isOverflow;
}

void PrintNumber(char* number)
{
    bool isBeginning0 = true;
    int nLength = (int)strlen(number);
    
    for(int i = 0; i < nLength; ++ i)
    {
        if(isBeginning0 && number[i] != '0')
            isBeginning0 = false;
        
        if(!isBeginning0)
        {
            printf("%c", number[i]);
        }
    }
    
    printf("\n");
}

//大数加法和大数乘法


//
/*
 有一个介于0和1之间的实数，类型为double，返回它的二进制表示。如果该数字无法精确地用32位以内的二进制表示，返回“Error”。
 给定一个double num，表示0到1的实数，请返回一个string，代表该数的二进制表示或者“Error”。
 */
string print_binary(string val){
    int pos = val.find('.', 0);
    int intpart = atoi(val.substr(0, pos).c_str());
    double decpart = atof(val.substr(pos, val.length()-pos).c_str());
    string intstr = "", decstr = "";
    while(intpart > 0){
        if(intpart&1) intstr = "1" + intstr;
        else intstr = "0" + intstr;
        intpart >>= 1;
    }
    while(decpart > 0){
        if(decstr.length() > 32) return "ERROR";
        decpart *= 2;
        if(decpart >= 1){
            decstr += "1";
            decpart -= 1;
        }
        else
            decstr += "0";
    }
    return intstr + "." + decstr;
}

void print_binary(int x){       //这个太easy了
    string s = "";
    for(int i=0; i<32 && x!=0; ++i, x >>= 1){
        if(x&1) s = "1" + s;
        else s = "0" + s;
    }
    cout<<s<<endl;
}




//problem: 大数的乘法，保存在两个string中
//algorithm： 乘法的运算法则
string strMultiply(string num1, string num2) {
    
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());
    
    if (("0" == num1) || ("0" == num2)) {
        return "0";
    }
    
    string result = "";

    int flag = 0, steps = 0;
    
    for (int i = 0; i < num1.length(); ++i) {
        int position = steps;
        
        for (int j = 0; j < num2.length(); ++j) {
            int v = (num1[i] - '0') * (num2[j] - '0') + flag;
            
            if (position < result.length()) {
                v += result[position] - '0';
                result[position] = (v % 10) + '0';
            }
            else {
                result.append(1, (v % 10) + '0');
            }
            
            flag = v / 10;
            ++position;
        }
        
        if (flag > 0) {
            result.append(1, flag + '0');
        }
        
        flag = 0;
        ++steps;
    }
    
    reverse(result.begin(), result.end());
    
    return result;
}


//problem: add digits
//algorithm:
int addDigits(int num)
{
    return 1 + (num-1) % 9;
}


//位的奇偶互换
/*用10101010也就是0xaa来提取奇数位
 */
int swapOddEvenBits(int x) {
    return ((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1); //这是32位的
}
//problem: 这题与add binary string 类似，都是用字符串、数组、链表来保存整数或二进制数，
//用来进行计算
//这样就可以计算特别大的数的和，整数不能表示，只能用字符串或者链表表示

/* addlist listadd
 You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
 
 Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 Output: 7 -> 0 -> 8
 */


node *addlist(node *l1, node *l2){
    node dummy(-1);
    int carry = 0;
    node *prev = &dummy;
    
    node *pa = l1, *pb = l2;
    while( pa != NULL || pb != NULL) {
        const int ai = pa == NULL ? 0: pa->data;
        const int bi = pb == NULL ? 0: pb->data;
        const int value = (ai + bi + carry) % 10;
        carry = (ai + bi + carry) / 10;
        prev->next = new node(value);
        
        pa = pa == NULL ? NULL : pa->next;
        pb = pb == NULL ? NULL : pb->next;
        prev = prev->next;
    }
    
    if (carry > 0)
        prev->next = new node(carry);
    return dummy.next;
}

//链式加法
ListNode* plusAB(ListNode* a, ListNode* b) {
    // write code here
    if (a == NULL || b == NULL)
        return NULL;
    
    ListNode* head = new ListNode(-1);
    ListNode* curr = head;
    
    int carry = 0;
    while(a || b) {
        int num1 = (a != NULL ? a->val : 0);
        int num2 = (b != NULL ? b->val : 0);
        int sum = (num1 + num2 + carry) % 10;
        carry = (num1 + num2 + carry) / 10;
        ListNode* c = new ListNode(sum);
        curr->next = c;
        if (a != NULL)
            a = a->next;
        if (b != NULL)
            b = b->next;
        curr = curr->next;
    }
    if (carry == 1) {
        ListNode* end = new ListNode(carry);
        curr->next = end;
    }
    
    
    return head->next;
}

/*
 r如果是顺序存储怎么办????????????，两条链表的数目不相等，还可以在结尾添加零元素节点来解决问题
 */
//problem: String to Integer (atoi)
//algorithm: 考虑各种情况，这个细节题，却是特别重要
int myAtoi(char* str) {
    int num = 0;
    int sign = 1;
    const int n = (int)strlen(str);
    int i = 0;
    
    while (isspace(str[i]) && i < n)
        i++;
    
    if (str[i] == '+'){
        i++;
    }else if (str[i] == '-'){
        sign = -1;
        i++;
    }
    
    for (; i < n; i++){
        //	if (str[i] < '0' || str[i] > '9')
        if (!isdigit(str[i]))
            break;
        //怎么判断整数溢出，这是一个方法
        if (num > INT_MAX/10 || (num == INT_MAX / 10 && (str[i] - '0') > INT_MAX % 10))
            return sign == -1 ? INT_MIN: INT_MAX;
        num = num * 10 + str[i] - '0';
    }
    
    return num*sign;
    
}

class Solution {
public:
    int reverse(int x) {
        bool flag = false;
        if (x == INT_MIN)
            return 0;
        if (x < 0) {
            x = abs(x);
            flag = true;
        }
        int sum = 0;
        while (x) {
            if (sum > INT_MAX / 10 || (sum == INT_MAX && (x > INT_MAX % 10)))
                return 0;
            sum = sum * 10 + x % 10;
            x /= 10;
        }
        if (flag) {
            return -sum;
        }else
            return sum;
    }
    
    //其实把它转换成long就可以了
    int reverse(int x) {
        if (x == 0) {
            return x;
        }
        int neg = (x > 0) ? 1 : -1;
        long sum = 0;
        long tmp = abs((long)x);
        while (tmp) {
            sum = sum * 10 + tmp % 10;
            tmp /= 10;
        }
        return (sum > INT_MAX) ? 0 : sum * neg;
    }
};

/*
 Reverse digits of an integer.
 
 Example1: x = 123, return 321
 Example2: x = -123, return -321
 */

//以上得判断一个整数是否溢出
/*
 无符号整数没有溢出， 溢出是有符号数的专利
 检查 cpu 的状态标志寄存器中的溢出标志位
 1. 无符号整数溢出很好判断, x + y < x 就表示溢出了.
 */
//有符号整形a和b,如何判断a+b是否溢出
int ifo_add(int a,int b) {
    __asm {
        mov eax,a
        add eax,b
        jo  overflowed
        xor eax,eax
        jmp no_overflowed
    overflowed:
        mov eax,1
    no_overflowed:
    }
}
int main_test() {
    int a,b;
    
    a=          1;b= 2;printf("%11d+(%2d) %d\n",a,b,ifo_add(a,b));
    a=         -1;b=-2;printf("%11d+(%2d) %d\n",a,b,ifo_add(a,b));
    a= 2147483647;b= 1;printf("%11d+(%2d) %d\n",a,b,ifo_add(a,b));
    a=-2147483647;b=-1;printf("%11d+(%2d) %d\n",a,b,ifo_add(a,b));
    a=-2147483647;b=-2;printf("%11d+(%2d) %d\n",a,b,ifo_add(a,b));
}
//          1+( 2)


//problem: gas station, 保证解唯一，这个很重要
//algorithm:
/*
 O(N)的解法是,设置两个变量,判断当前的指针的有效性;则判断整个数组是否有解,有就返回通过得到的下标,
 没有则返回 -1
 */
int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
{
    int total = 0;
    int j = -1;
    
    for (int i = 0, sum = 0; i < gas.size(); ++i){
        sum += gas[i] - cost[i];
        total += gas[i] - cost[i];
        if (sum < 0) {
            j = i;
            sum = 0;
        }
    }
    return total >= 0 ? j + 1 : -1;
}

//problem: candy given
//algorithm: 贪心算法那
/*
 先从左到右扫描一遍，使得右边比左边得分高的小朋友糖果数比左边多。
 再从右到左扫描一遍，使得左边比右边得分高的小朋友糖果数比右边多。
 */
int candy(vector<int> &ratings) {
    vector<int> candy(ratings.size(), 1);
    int height = 1;
    for (int i = 1; i < ratings.size(); i++) {
        if (ratings[i] > ratings[i - 1]) {
            candy[i] = max(++height, candy[i]);
        } else {
            height = 1;
        }
    }
    height = 1;
    for (int i = ratings.size() - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1]) {
            candy[i] = max(++height, candy[i]);
        } else {
            height = 1;
        }
    }
    int ans = 0;
    for (int i = 0; i < ratings.size(); i++) {
        ans += candy[i];
    }
    return ans;
}

//problem:
//algorithm:

class removeNodes {

public:
    int removeElementsOfArray(vector<int>& nums, int val) {
        int n = nums.size();
        if (0 == n) return 0;
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] != val)
                nums[j++] = nums[i];
        }
        return j;
    }
    
    ListNode* removeElementsOfList(ListNode* head, int val) {
        if (NULL == head)   return NULL;
        ListNode dummy(-1); //利用好dummy法
        dummy.next = head;
        ListNode* pre = &dummy;
        ListNode* cur = head;
        while( cur != NULL) {
            if (cur->val == val) {  //这里没有将满足要求的节点的内存释放，可以加上一个delete
                cur = cur->next;
                pre->next = cur;
            }else {
                pre = cur;
                cur = cur->next;
            }
        }
        return dummy.next;
    }
    
    ListNode* removeDuplicatesFromSortedList(ListNode * head)
    {
        ListNode* pre = head;
        if (head == nullptr)
            return nullptr;
        ListNode* cur;
            //双指针法
        for (cur = pre->next; cur != nullptr; cur = cur->next)
        {
            if (cur->val == pre->val){
                pre->next = cur->next;
                delete cur;
            }
            else
                pre = cur;
        }
        return head;
    }

    ListNode* removeDuplicatesFromLists2(ListNode* head)
    {
        if (head->next == nullptr)
            return head;
        ListNode dummy(INT_MIN);//头节点
        dummy.next = head;
        ListNode *prev = &dummy, *cur = head;
        while(cur != nullptr){
            bool duplicated = false;
            while (cur->next!=nullptr && cur->val == cur->next->val){
                duplicated = true;
                ListNode *temp = cur;
                cur = cur->next;
                delete temp;
            }
            if (duplicated){//删除重复的最后一个元素
                ListNode* temp = cur;
                cur = cur->next;
                delete temp;
                continue;
            }
            prev->next = cur;
            prev = prev->next;
            cur = cur->next;
        }
        prev->next = cur;
        return dummy.next;
    }



    ListNode* removeNthFromList(ListNode* head, int n)// 只扫描了一次
    {
        ListNode dummy(-1);
        dummy.next = head;
        
        ListNode* p = &dummy;
        ListNode* q = &dummy;
        
        for (int i = 0; i < n; i++)
            q = q->next;
        
        while (q->next)
        {
            q = q->next;
            p = p->next;
        }
        
        ListNode* tmp;
        tmp = p->next;
        p->next = p->next->next;
        delete tmp;
        return dummy.next;
    }

    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if (n <= 2)
            return n;
        bool flag = false;
        int i = 0, j;
        for (j = 1; j < n; j++){
            if (nums[j] != nums[i]) {
                nums[++i] = nums[j];
                flag = false;
            }
            else if (nums[j] == nums[i] && !flag) {
                nums[++i] = nums[j];
                flag = !flag;
            }
        }
        return i+1;
    }

    int remove_duplicates2(int a[], int num)
    {
        if (num == 0) return 0;
        int i, flag = 0, index = 0;
        for (i = 1; i < num; i++)
            if (a[index] != a[i])
                a[++index] = a[i];
            else{
                if (a[i] == a[i+1])
                    i++;
                else
                    a[++index] = a[i];
            }
        
        return index+1;
    }
    
    /*
     The main idea is the same with problem Linked List Cycle II,https://leetcode.com/problems/linked-list-cycle-ii/. Use two pointers the fast and the slow. The fast one goes forward two steps each time, while the slow one goes only step each time. They must meet the same item when slow==fast. In fact, they meet in a circle, the duplicate number must be the entry point of the circle when visiting the array from nums[0]. Next we just need to find the entry point. We use a point(we can use the fast one before) to visit form begining with one step each time, do the same job to slow. When fast==slow, they meet at the entry point of the circle. The easy understood code is as follows.
     */
    
    int findDuplicate3(vector<int>& nums)
    {
        if (nums.size() > 1)
        {
            int slow = nums[0];     //这个的局限是只能处理1-n之间的数，如果是0-n-1这个方法就不行，因为如果nums[0] = 0那么就是死循环。
            int fast = nums[nums[0]];
            while (slow != fast)
            {
                slow = nums[slow];
                fast = nums[nums[fast]];
            }
            
            fast = 0;
            while (fast != slow)
            {
                fast = nums[fast];
                slow = nums[slow];
            }
            return slow;
        }
        return -1;
    }
    //更加通用的方法
    /*
     题目要求我们不能改变原数组，即不能给原数组排序，又不能用多余空间，那么哈希表神马的也就不用考虑了，又说时间小于O(n2)，也就不能用brute force的方法，那我们也就只能考虑用二分搜索法了，我们在区别[1, n]中搜索，首先求出中点mid，然后遍历整个数组，统计所有小于等于mid的数的个数，如果个数大于mid，则说明重复值在[mid+1, n]之间，反之，重复值应在[1, mid-1]之间，然后依次类推，知道搜索完成，此时的low就是我们要求的重复值
     */
    int findDuplicate(vector<int>& nums) {
        int low = 1, high = nums.size() - 1;
        while (low <= high) {
            int mid = low + (high - low) * 0.5;
            int cnt = 0;
            for (auto a : nums) {
                if (a <= mid) ++cnt;
            }
            if (cnt <= mid) low = mid + 1;
            else high = mid - 1;
        }
        return low;
    }
    
    
    int firstMissingPositive(vector<int>& A) {
        int n = A.size();
        int i = 0, j;
        while (i < n)
        {
            if (A[i] != i + 1 && A[i] > 0 && A[i] <= n && A[i] != A[A[i]-1])
                swap(A[i], A[A[i]-1]);
            else i++;
        }
        
        for (j = 0; j < n; j++)
            if (A[j] != j + 1)
                return j + 1;
        return n + 1;
        
    }
    

};

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        return set<int>(nums.begin(), nums.end()).size() < nums.size();
    }
    
    //利用hash
    bool containsDuplicate(vector<int>& nums) {
        if (nums.size() == 0)   return false;
        unordered_set<int> s;
        s.insert(nums[0]);
        for (int i = 1 ; i < nums.size(); i++) {
            if (s.find(nums[i]) != s.end())
                return true;
            else
                s.insert(nums[i]);
        }
        return false;
    }
    
    //利用map
    bool containsDuplicate(vector<int>& nums) {
        if (nums.empty())  return false;
        unordered_map<int,int> mp;
        for (int i : nums) {
            if (++mp[i] > 1) {
                return true;
            }
        }
        return false;
    }
    
    /*
     Given an array of integers and an integer k, find out whether there are 
     two distinct indices i and j in the array such that nums[i] = nums[j] and 
     the difference between i and j is at most k.
     */
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 0) return false;
        unordered_map<int, int> hashmap;
        for (int i = 0; i < n; i++) {
            if (hashmap.find(nums[i]) != hashmap.end() && i - hashmap[nums[i]] <= k)
                return true;
            else
                hashmap[nums[i]] = i;   //这里不用insert，直接这样就可以了
        }
        return false;
    }
    
    /*
     Given an array of integers, find out whether there are two distinct indices i and j in the array such that the difference between nums[i] and nums[j] is at most t and the difference between i and j is at most k.
     */
    //这个如果逐一遍历-t~t的话，复杂度太高了
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if (k < 1 || t < 0 || nums.size() < 2)
            return false;
        multiset<int> box;              //这个说白了就是利用BST的特性
        for(int i = 0; i < nums.size() - 1; ) {
            box.insert(nums[i++]);
            set<int>::iterator it = box.lower_bound(nums[i]-t); //说白了是利用了BST的特性
            
            if(it != box.end()) {
                if(abs(*it - nums[i]) > t)
                    return true;
            }
            
            if(i >= k) {            //维护一个k大小的窗
                box.erase(nums[i - k]);
            }
        }
        return false;
    }
    
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        set<int> window; // set is ordered automatically
        for (int i = 0; i < nums.size(); i++) {
            if (i > k)
                window.erase(nums[i-k-1]);// the set contains nums i j at most k
            // -t <= x - nums[i] <= t;
            auto pos = window.lower_bound(nums[i] - t); // x >= nums[i] - t
            if (pos != window.end() && *pos - nums[i] <= t) // x <= nums[i] + t
                return true;
            window.insert(nums[i]);
        }
        return false;
    }
};



//----------------------------------------------------------------


/*










void connet(TreeLinkNode *root, TreeLinkNode *sibling){
    if (root = NULL)
        return ;
    else
        root->next = sibling;
    
    connet(root->left , root->right);
    if (sibling)
        connet(root->right, sibling->left);
    else
        connet(root->right, NULL);
}

int evalRPN(vector<string> &tokens){
    stack<string> s;
    for (auto token: tokens){
        if (!is_operator(token))
            s.push(token);
        else {
            int y = stoi(s.top());
            s.pop();
            int x = stoi(s.top());
            s.pop();
            if (token[0] == '+')	x += y;
            else if (token[0] == '-')	x -= y;
            else if (token[0] == '*')	x *= y;
            else						x /= y;
            s.push(to_string(x));
        }
    }
    return stoi(s.top());
}

bool is_operator(const string *op){
    return op.size() == 1 && string("+-/*").find(op) != string::npos;
}

unsigned int binary_to_gray(unsigned int n)
{
    return n ^ (n >> 1);
}


vector<int> grayCode(int n)
{
    vector<int> result;
    const size_t size = 1 << n;
    result.reserve(size);
    for (size_t i = 0; i < size; ++i)
        result.push_back(binary_to_gray(i));
    return result;
}






bool isPalindrome(string s){
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    auto left = s.begin(), right = prev(s.end());
    while(left < right){
        if (!::isalnum(*left))
            ++left;
        else if (!::isalnum(*right))
            --right;
        else if (*left != *right)
            return false;
        else {
            left++;
            right--;
        }
        
    }
    return true;
}


int lengthOfLastWord(const char *s)
{
    int len = 0;
    while (*s){
        if (*s++ != ' ')
            ++len;
        else if (*s && *s != ' ')
            len = 0;
    }
    return len;
}


ListNode* listDetectCycle(ListNode* head){
    ListNode* slow = head, *fast = head;
    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast){
            ListNode * slow2 = head;
            while (slow2 != slow){
                slow2 = slow2->next;
                slow = slow->next;
            }
            return slow2;
        }
    }
    return NULL;
}




string longestCommonPrefix(vector<string> &strs){
    if (strs.empty()) return "";
    
    for (int idx = 0; idx < strs[0].size(); ++idx){
        for (int i = 1; i < strs.size(); ++i){
            if (strs[i][idx] != strs[0][idx])
                return strs[0].substr(0,idx);
        }
    }
    return strs[0];
}


int longestConsecutive(const vector<int> &num)
{
    unordered_map<int, bool> used;
    int longest = 0;
    for (auto i : num)
    {
        if (used[i]) continue;
        int length = 0;
        used[i] = true;
        for (int j = i + 1; used.find(j) != used.end(); ++j)
        {
            used[j] = true;
            ++length;
        }
        
        for (int j = i - 1; used.find(j) != used.end(); --j)
        {
            used[j] = true;
            ++length;
        }
        longest = max(longest, length);
    }
    return longest;
}


int longestValidParentheses(string s)
{
    int max_len = 0, last = -1;
    stack<int> lefts;
    
    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] == '(')
            lefts.push(i);
        else {
            if (lefts.empty())
                last = i;
            else {
                lefts.pop();
                if (lefts.empty())
                    max_len = max(max_len, i-last);
                else
                    max_len = max(max_len, i-lefts.top());
            }
        }
    }
    return max_len;
}

void mergeSortedArray(int A[], int m, int B[], int n){
    int ia = m - 1, ib = n - 1, icur = m + n - 1;
    while (ia >= 0 && ib >= 0){
        A[icur--] = A[ia] >= B[ib] ? A[ia--] : B[ib--];
    }BTreeNode
    
    while (ib >= 0){
        A[icur--] = B[ib--];
    }
}

ListNode *mergeTwoLists(ListNode *l1, ListNode *l2){
    if (l1 == NULL) return l2;
    if (l2 == NULL) return l1;
    
    ListNode dummy(-1);
    ListNode *p = &dummy;
    for (; l1 != NULL && l2 != NULL; p = p -> next){
        if (l1->val > l2->val){
            p->next = l2;
            ls = l2->next;
        }else{
            p->next = l1;
            l1 = l1->next;
        }
    }
    p->next = l1 != NULL ? l1 : l2;
    return dummy.next;
}


int minimumDepthofBinaryTree(const TreeNode *root, bool hasbrother){
    if (!root) return hasbrother ? INT_MAX : 0;
    
    return 1 + min(minimumDepthofBinaryTree(root->left, root->right != NULL),
                   minimumDepthofBinaryTree(root->right, root->left != NULL));
}

int maxDepthOfBinaryTree(TreeNode* root){
    if (root == NULL) return 0;
    
    return max(maxDepthOfBinaryTree(root->left), maxDepthOfBinaryTree(root->right)) + 1;
}

char* myStrStr(const char* haystack, const char* needle){
    if (*needle == NULL) return (char*)haystack;
    
    const char* p1;
    const char* p2;
    const char* p1_advance = haystack;
    
    for (p2 = &needle[1]; *p2; ++p2){
        p1_advance++;
    }
    
    for (p1 = haystack; *p1_advance; p1_advance++){
        char* p1_old = (char*) p1;
        p2 = needle;
        while (*p1 && *p2 && *p1 == *p2){
            p1++;
            p2++;
        }
        
        if(*p2 == NULL) return p1_old;
        p1 = p1_old + 1;
    }
    return NULL;
}


ListNode* partitionList(ListNode* Head, int x)
{
    ListNode left_dummy(-1);
    ListNode right_dummy(-1);
    
    auto left_cur = &left_dummy;
    auto right_cur = &right_dummy;
    
    for (ListNode *cur = Head; cur; cur = cur->next)
    {
        if (cur->val < x){
            left_cur->next = cur;
            left_cur = cur;
        }
        else{
            right_cur->next = cur;
            right_cur = cur;
        }
        left_cur->next = right_dummy.next;
        right_cur->next = nullptr;
    }
}



void pathSum(TreeNode* root , int gap, vector<int> &cur,
             vector<vector<int> > &result){
    if (root == NULL) return ;
    
    cur.push_back(root->val);
    
    if (root->left == NULL && root->right == NULL) {
        if (gap == root->val)
            result.push_back(cur);
    }
    pathSum(root->left, gap - root->val, cur, result);
    pathSum(root->right, gap - root->val, cur, result);
    
    cur.pop_back();
}


vector<int> preorderTraversal(TreeNode *root){
    vector<int> result;
    const TreeNode *p;
    stack<const TreeNode *> s;
    
    p = root;
    if (p != NULL) s.push(p);
    
    while (!s.empty()) {
        p = s.top();
        s.pop();
        result.push_back(p->val);
        
        if ( p->right != NULL) s.push(p->right);
        if ( p->left != NULL) s.push(p->left);
    }
    return result;
}


 
//找到中间节点，把后半节链表reverse，然后合并成一个大的链表, reverselist listreverse
ListNode* reverse(ListNode* head);
void reorderList(ListNode* head){
    if (head == NULL || head->next == NULL)
        return;
    ListNode* slow = head;
    ListNode* fast = head;
    ListNode* prev = NULL;
    while (fast && fast->next){
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    
    prev->next = NULL;
    slow = reverse(slow);
    ListNode* cur = head;
    while (cur->next){
        ListNode* tmp = cur->next;
        cur->next = slow;
        slow = slow->next;
        cur->next->next = tmp;
        cur = tmp;
    }
    cur->next = slow;
}

ListNode* reverse(ListNode* head){
    if (head == NULL || head->next == NULL)
        return head;
    
    ListNode* prev = head;
    ListNode* tmp = head->next;
    ListNode* cur = tmp->next;
    head->next = NULL;
    while(cur->next){
        tmp->next = prev;
        prev = tmp;
        tmp = cur;
        cur = cur->next;
    }
    tmp->next = prev;
    cur->next = tmp;;
    return cur;
}



ListNode *reverseLinkedList2(ListNode *head, int m, int n)
{
    ListNode dummy(-1);
    dummy.next = head;
    
    ListNode *prev = &dummy;
    for (int i = 0; i < m - 1; ++i)
        prev = prev -> next;
    ListNode* const head2 = prev;
    
    prev = head2->next;
    ListNode *cur = prev->next;
    for (int i = m; i < n; i++){
        prev->next = cur->next;
        cur->next = head2->next;
        head2->next = cur;
        cur = prev->next;
    }
    return dummy.next;
}




void rotateImage(vector<vector<int> > & matrix)
{
    const int n = matrix.size();
    
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n-1; ++j)
            swap(matrix[i][j], matrix[n - 1 - j][n - 1 - i]);
    }
    
    for (int i = 0; i < n/2; ++i)
        for (int j = 0; j < n; ++j)
            swap(matrix[i][j], matrix[n-1-i][j]);
}



ListNode* rotateRightList(ListNode *head, int k){
    if (head == NULL || k == 0)
        return head;
    
    int len = 1;
    ListNode* p = head;
    while (p->next){
        len++;
        p = p->next;
    }
    
    k = len - k % len;
    p->next = head;
    for (int step = 0; step < k; step++)
        p = p->next;
    
    head = p->next;
    p->next = NULL;
    return head;
}


 
 






int sumNumbers(TreeNode *root, int sum) {
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return sum * 10 + root->val;
    
    return sumNumbers(root->left, sum * 10 + root->val) +
    sumNumbers(root->right, sum * 10 + root->val);
}


ListNode* swapNodesInList(ListNode* head){
    if (!head || !head->next)
        return head;
    ListNode dummy(-1);
    dummy.next = head;
    ListNode* prev = &dummy;
    ListNode* cur = prev->next;
    ListNode* next = cur->next;
    while(next)
    {
        prev->next = next;
        cur->next = next->next;
        next->next = cur;
        
        prev = cur;
        cur = cur->next;
        next = cur ? cur->next : NULL;
    }
    return dummy.next;
}







int trappingRainWater(int A[], int n)
{
    int *max_left = new int[n]();
    int *max_right = new int[n]();
    
    for (int i = 1; i < n ; i++)
    {
        max_left[i] = max(max_left[i-1], A[i-1]);
        max_right[n - i - 1] = max(max_right[n - i], A[n - i]);
    }
    int sum = 0;
    for (int i = 0; i < n; i++){
        int height = min(max_left[i], max_right[i]);
        if (height > A[i])  sum += height - A[i];
    }
    
    delete[] max_left;
    delete[] max_right;
    return sum;
}


int trappingRainWater2(int a[], int n)
{
    int max = 0;
    for (int i = 0; i < n; i++){
        if (A[i] > A[max]) max = i;
    }
    
    int water = 0;
    for (int i = 0, peak = 0; i < max; i++){
        if (A[i] > peak) peak = A[i];
        else
            water += peak - A[i];
    }
    
    for (int i = n - 1, top = 0; i > max; i--){
        if (A[i] > top) top = A[i];
        else
            water += = top - A[i];
    }
    
    return water;
}






                
                
                
                
int removeElement(int A[], int n, int target)
    {
        int index = 0;
        int i;
        for (i = 0; i < n; ++i)
        {
            if (A[i] != elem) 
                A[index++] = A[i];
        }
        return index;
    }
                
                
                int remove_duplicates(int a[], int num)
    {
        if (num == 0) return 0;
        int i, index = 0;
        for (i = 1; i < num; i++)
            if (a[index] != a[i])
                a[++index] = a[i];
        return index+1;
    }
                

 
 
                
                int remove_duplicates3(int a[], int num)
    {
        if (num < 3) return num;
        int i, index = 2;
        for (i = 2; i < num; i++)
            if (a[i] != a[index-2])
                a[index++] = a[i];
        return index;
    }
                
                
                
                int search_in_rotated_sorted_array(int x, int A[], int num)
    {
        int first = 0, last = num;
        while (first != last)
        {
            const int mid = first + (last - first) / 2;
            if (A[mid] == x)
                return mid;
            if (A[first] <= A[mid])
            {
                if (A[first] <= x && x < A[mid])
                    last = mid;
                else
                    first = mid + 1;
            }
            else
            {
                if (A[mid] < x && x <= A[last - 1])
                    first = mid - 1;
                else
                    last = mid;
            }
        }
        return -1;
        
    }
*/
        

//problem:
//algorithm:


//problem:
//algorithm:


//problem:
//algorithm:



//problem:
//algorithm:



//problem:
//algorithm:



//problem:
//algorithm:



//problem:
//algorithm:

