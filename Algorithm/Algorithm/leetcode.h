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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


//problem: preorder\inordrer\postordre tree traveral recursive and non-recursive
//algorithm: as follows
void visit(TreeNode* node) {
    printf("%d -> ", node->val);
}
void preorderRecursive(TreeNode * node)
{
    if (node == NULL) return;
    visit(node);
    preorderRecursive(node->left);
    preorderRecursive(node->right);
}
void inorderRecursive(TreeNode* node) {
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

void preorderNonrecursive(TreeNode * node) {
    stack<TreeNode *> s;
    s.push(node);
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
            cur = cur->right; //这与书上的异曲同工之妙
        }
    }
}
//algorithm:dsa
void inorderNonrecursive2(TreeNode* node){
    stack<TreeNode*> s;
    TreeNode* cur = node;
    while (true) {
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

void traverseLevel(TreeNode* node) {
    queue<TreeNode*> q;
    TreeNode* cur;
    q.push(cur);
    while (!q.empty()) {
        cur = q.front(); q.pop();
        visit(cur);
        if (!cur->left)     q.push(cur->left);
        if (!cur->right)    q.push(cur->right);
    }
}


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
    priority_queue<int> pq;
    for (auto n : nums)
        pq.push(n);
    for (int i = 1; i < k; i++)
        pq.pop();
    
    return pq.top();
}

//算法3：分治法，利用quick sort的思想
int partition(vector<int> &nums,int begin,int end);

int findKthLargest3(vector<int>& nums, int k)

{
    
    int pivot=nums[0];
    
    int left=0;
    
    int right = (int)nums.size()-1;
    
    while(true) {
        
        int pos = partition(nums,left,right);
        
        if(pos == k-1)
            
            return nums[pos];
        
        if(pos<k-1)
            left = pos+1;
        else
            right = pos-1;
        
    }
    
}

int partition(vector<int> &nums,int begin,int end)

{
    
    int left=begin+1;
    
    int right=end;
    
    while(left<=right) {
        
        if(nums[left]<nums[begin]&&nums[right]>nums[begin])
            
            swap(nums[left],nums[right]);
        
        if(nums[left]>=nums[begin]) 
            
            left++; 
        
        if(nums[right]<=nums[begin]) 
            
            right--;
        
    } 
    
    swap(nums[begin],nums[right]); return right; 
    
}

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
//问题：Edit Distance
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

//问题：longest increasing subsequence(LIS)
//算法：动态规划，复杂度为O(n2)
int lis(int A[], int n){
    int *f = new int[n];
    int len = 1;
    for(int i=0; i<n; ++i){
        f[i] = 1;
        for(int j=0; j<i; ++j)
            if(A[j]<=A[i] && f[j]+1>f[i])
                f[i] = f[j] + 1;
        if(f[i]>len)
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
//算法2：动态规划+滚动数组，只需O(n)的空间//这个存在bug????
int minPathS(vector<vector<int> > & grid) {
    int m = (int) grid.size();
    int n = grid[0].size();
    int f[n];
    f[0] = 0;
    fill(f, f+n, INT_MAX); //初始值都设为INT_MAX, 因为后面用到的是min函数
    for (int i = 0; i < m ; i++) {
        f[0] += grid[i][0];
        for (int j = 1; j < n; j++) {
            f[j] = min(f[j-1], f[j]) + grid[i][j];
        }
    }
    return f[n-1];
}
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
void dfs(vector<int>& nums, int gap, int start, vector<int>& intermediate,
         vector<vector<int> >& result);
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<vector<int> > result;
    vector<int> intermediate;
    dfs(candidates, target, 0, intermediate, result);
    return result;
}
void dfs(vector<int>& nums, int gap, int start, vector<int>& intermediate,
vector<vector<int> >& result) {
    if (gap == 0) {
        result.push_back(intermediate);
        return;
    }
    for (int i = start; i < nums.size(); i++) {
        if (gap < nums[i])  return; //prunning
        intermediate.push_back(nums[i]);
        dfs(nums, gap - nums[i], i, intermediate, result);
        intermediate.pop_back();
    }
}

//问题：reverse a sentence of words
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
//算法2：以上算法并不高效
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

//问题：最大间隙问题Maximum gap
//算法：采用桶结构
int maximumGap(vector<int>& nums) {
    if(nums.empty() || nums.size() == 1)
        return 0;
    int n = (int) nums.size();
    int minAll = *min_element(nums.begin(), nums.end());
    int maxAll = *max_element(nums.begin(), nums.end());
    double gap = ((double)(maxAll - minAll)) / (n - 1);
    
    // compute min and max element for each bucket
    vector<int> minV(n-1, INT_MAX);
    vector<int> maxV(n-1, INT_MIN);
    for(int i = 0; i < n; i ++)
    {
        if(nums[i] != maxAll)
        {// the bktId of maxAll will fall out of bucket range
            int bktId = (int)((nums[i]-minAll)/gap);
            minV[bktId] = min(minV[bktId], nums[i]);
            maxV[bktId] = max(maxV[bktId], nums[i]);
        }
    }
    int ret = 0;
    int curMax = maxV[0];
    for(int i = 1; i < n-1; i ++)
    {
        if(minV[i] != INT_MAX)
        {
            ret = max(ret, minV[i]-curMax);
            curMax = maxV[i];
        }
    }
    ret = max(ret, maxAll-curMax);
    return ret;
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

//问题：Largest Rectangle in Histogram
//算法：利用堆栈来维护一个递增栈, 栈内存储的是高度递增的下标,使用一个栈的O(n)解法，代码非常简洁，栈内存储的是高度递增的下标。对于每一个直方图高度，分两种情况。1：当栈空或者当前高度大于栈顶下标所指示的高度时，当前下标入栈。否则，2：当前栈顶出栈，并且用这个下标所指示的高度计算面积。而这个方法为什么只需要一个栈呢？因为当第二种情况时，for循环的循环下标回退，也就让下一次for循环比较当前高度与新的栈顶下标所指示的高度，注意此时的栈顶已经改变由于之前的出栈。
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
string longestCommonPrefix(vector<string>& strs) {
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
