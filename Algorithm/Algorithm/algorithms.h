
#ifndef Algorithm_Functions_h
#define Algorithm_Functions_h
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

using namespace std;


//结构定义
//单链表节点
struct node {
    int data;
    node* next;
    node(int e = 0): data(e) {}
};
typedef node Node;
//双向链表节点
struct ListNode {
    int data;
    ListNode* pred;
    ListNode* succ;
    ListNode() {};
    ListNode(int e = 0, ListNode* p = NULL, ListNode* s = NULL):
    data(e), pred(p), succ(s){}
};
//二叉树节点
struct BinaryTreeNode{              // a node in the binary tree
    int m_nValue;                   // value of node
    BinaryTreeNode *m_pLeft;        // left child of node
    BinaryTreeNode *m_pRight;       // right child of node
    BinaryTreeNode() {};
    BinaryTreeNode(int nv = 0, BinaryTreeNode* pl = NULL, BinaryTreeNode* pr = NULL):
    m_nValue(nv), m_pLeft(pl), m_pRight(pr) {}
};
//

namespace BST_14 {


/*
 1. 求二叉树中的节点个数
 2. 求二叉树的深度
 3. 前序遍历，中序遍历，后序遍历
 4.分层遍历二叉树（按层次从上往下，从左往右）
 5. 将二叉查找树变为有序的双向链表
 6. 求二叉树第K层的节点个数
 7. 求二叉树中叶子节点的个数
 8. 判断两棵二叉树是否结构相同
 9. 判断二叉树是不是平衡二叉树
 10. 求二叉树的镜像
 11. 求二叉树中两个节点的最低公共祖先节点
 12. 求二叉树中节点的最大距离
 13. 由前序遍历序列和中序遍历序列重建二叉树
 14.判断二叉树是不是完全二叉树
 */


/*
 1. 求二叉树中的节点个数
 递归解法：
 （1）如果二叉树为空，节点个数为0
 （2）如果二叉树不为空，二叉树节点个数 = 左子树节点个数 + 右子树节点个数 + 1
 参考代码如下：
 */

int GetNodeNum(BinaryTreeNode * pRoot)
{
    if(pRoot == NULL) // 递归出口
        return 0;
    return GetNodeNum(pRoot->m_pLeft) + GetNodeNum(pRoot->m_pRight) + 1;
}

/*
 2. 求二叉树的深度
 递归解法：
 （1）如果二叉树为空，二叉树的深度为0
 （2）如果二叉树不为空，二叉树的深度 = max(左子树深度， 右子树深度) + 1
 参考代码如下：
 */
int GetDepth(BinaryTreeNode * pRoot)
{
    if(pRoot == NULL) // 递归出口
        return 0;
    int depthLeft = GetDepth(pRoot->m_pLeft);
    int depthRight = GetDepth(pRoot->m_pRight);
    return depthLeft > depthRight ? (depthLeft + 1) : (depthRight + 1);
}
/*
 3. 前序遍历，中序遍历，后序遍历
 前序遍历递归解法：
 （1）如果二叉树为空，空操作
 （2）如果二叉树不为空，访问根节点，前序遍历左子树，前序遍历右子树
 参考代码如下：
 */
void PreOrderTraverse(BinaryTreeNode * pRoot)
{
    if(pRoot == NULL)
        return;
    Visit(pRoot); // 访问根节点
    PreOrderTraverse(pRoot->m_pLeft); // 前序遍历左子树
    PreOrderTraverse(pRoot->m_pRight); // 前序遍历右子树
}
/*
 中序遍历递归解法
 （1）如果二叉树为空，空操作。
 （2）如果二叉树不为空，中序遍历左子树，访问根节点，中序遍历右子树
 参考代码如下：
 */
void InOrderTraverse(BinaryTreeNode * pRoot)
{
    if(pRoot == NULL)
        return;
    InOrderTraverse(pRoot->m_pLeft); // 中序遍历左子树
    Visit(pRoot); // 访问根节点
    InOrderTraverse(pRoot->m_pRight); // 中序遍历右子树
}
/*
 后序遍历递归解法
 （1）如果二叉树为空，空操作
 （2）如果二叉树不为空，后序遍历左子树，后序遍历右子树，访问根节点
 参考代码如下：
 */
void PostOrderTraverse(BinaryTreeNode * pRoot)
{
    if(pRoot == NULL)
        return;
    PostOrderTraverse(pRoot->m_pLeft); // 后序遍历左子树
    PostOrderTraverse(pRoot->m_pRight); // 后序遍历右子树
    Visit(pRoot); // 访问根节点
}
/*
 4.分层遍历二叉树（按层次从上往下，从左往右）
 
 相当于广度优先搜索，使用队列实现。队列初始化，将根节点压入队列。当队列不为空，进行如下操作：弹出一个节点，访问，若左子节点或右子节点不为空，将其压入队列。
 */
void LevelTraverse(BinaryTreeNode * pRoot)
{
    if(pRoot == NULL)
        return;
    queue<BinaryTreeNode *> q;
    q.push(pRoot);
    while(!q.empty())
    {
        BinaryTreeNode * pNode = q.front();
        q.pop();
        Visit(pNode); // 访问节点
        if(pNode->m_pLeft != NULL)
            q.push(pNode->m_pLeft);
        if(pNode->m_pRight != NULL)
            q.push(pNode->m_pRight);
    }
    return;
}
/*
 5. 将二叉查找树变为有序的双向链表
 要求不能创建新节点，只调整指针。
 递归解法：
 （1）如果二叉树查找树为空，不需要转换，对应双向链表的第一个节点是NULL，最后一个节点是NULL
 （2）如果二叉查找树不为空：
 如果左子树为空，对应双向有序链表的第一个节点是根节点，左边不需要其他操作；
 如果左子树不为空，转换左子树，二叉查找树对应双向有序链表的第一个节点就是左子树转换后双向有序链表的第一个节点，同时将根节点和左子树转换后的双向有序链 表的最后一个节点连接；
 如果右子树为空，对应双向有序链表的最后一个节点是根节点，右边不需要其他操作；
 如果右子树不为空，对应双向有序链表的最后一个节点就是右子树转换后双向有序链表的最后一个节点，同时将根节点和右子树转换后的双向有序链表的第一个节点连 接。
 参考代码如下：
 */
/******************************************************************************
 参数：
 pRoot: 二叉查找树根节点指针
 pFirstNode: 转换后双向有序链表的第一个节点指针
 pLastNode: 转换后双向有序链表的最后一个节点指针
 ******************************************************************************/
void Convert(BinaryTreeNode * pRoot,
             BinaryTreeNode * & pFirstNode, BinaryTreeNode * & pLastNode)
{
    BinaryTreeNode *pFirstLeft, *pLastLeft, * pFirstRight, *pLastRight;
    if(pRoot == NULL)
    {
        pFirstNode = NULL;
        pLastNode = NULL;
        return;
    }
    
    if(pRoot->m_pLeft == NULL)
    {
        // 如果左子树为空，对应双向有序链表的第一个节点是根节点
        pFirstNode = pRoot;
    }
    else
    {
        Convert(pRoot->m_pLeft, pFirstLeft, pLastLeft);
        // 二叉查找树对应双向有序链表的第一个节点就是左子树转换后双向有序链表的第一个节点
        pFirstNode = pFirstLeft;
        // 将根节点和左子树转换后的双向有序链表的最后一个节点连接
        pRoot->m_pLeft = pLastLeft;
        pLastLeft->m_pRight = pRoot;
    }
    
    if(pRoot->m_pRight == NULL)
    {
        // 对应双向有序链表的最后一个节点是根节点
        pLastNode = pRoot;
    }
    else
    {
        Convert(pRoot->m_pRight, pFirstRight, pLastRight);
        // 对应双向有序链表的最后一个节点就是右子树转换后双向有序链表的最后一个节点
        pLastNode = pLastRight;
        // 将根节点和右子树转换后的双向有序链表的第一个节点连接
        pRoot->m_pRight = pFirstRight;
        pFirstRight->m_pLeft = pRoot;
    }
    
    return;
}
/*
 6. 求二叉树第K层的节点个数
 递归解法：
 （1）如果二叉树为空或者k<1返回0
 （2）如果二叉树不为空并且k==1，返回1
 （3）如果二叉树不为空且k>1，返回左子树中k-1层的节点个数与右子树k-1层节点个数之和
 参考代码如下：
 */
int GetNodeNumKthLevel(BinaryTreeNode * pRoot, int k)       //k也就代表了递归的深度
{
    if(pRoot == NULL || k < 1)
        return 0;
    if(k == 1)
        return 1;
    int numLeft = GetNodeNumKthLevel(pRoot->m_pLeft, k-1); // 左子树中k-1层的节点个数
    int numRight = GetNodeNumKthLevel(pRoot->m_pRight, k-1); // 右子树中k-1层的节点个数
    return (numLeft + numRight);
}
/*
 7. 求二叉树中叶子节点的个数
 递归解法：
 （1）如果二叉树为空，返回0
 （2）如果二叉树不为空且左右子树为空，返回1
 （3）如果二叉树不为空，且左右子树不同时为空，返回左子树中叶子节点个数加上右子树中叶子节点个数
 参考代码如下：

 */
int GetLeafNodeNum(BinaryTreeNode * pRoot)
{
    if(pRoot == NULL)
        return 0;
    if(pRoot->m_pLeft == NULL && pRoot->m_pRight == NULL)
        return 1;
    int numLeft = GetLeafNodeNum(pRoot->m_pLeft); // 左子树中叶节点的个数
    int numRight = GetLeafNodeNum(pRoot->m_pRight); // 右子树中叶节点的个数
    return (numLeft + numRight);
}
/*
 8. 判断两棵二叉树是否结构相同
 不考虑数据内容。结构相同意味着对应的左子树和对应的右子树都结构相同。
 递归解法：
 （1）如果两棵二叉树都为空，返回真
 （2）如果两棵二叉树一棵为空，另一棵不为空，返回假
 （3）如果两棵二叉树都不为空，如果对应的左子树和右子树都同构返回真，其他返回假
 参考代码如下
 */
bool StructureCmp(BinaryTreeNode * pRoot1, BinaryTreeNode * pRoot2)
{
    if(pRoot1 == NULL && pRoot2 == NULL) // 都为空，返回真
        return true;
    else if(pRoot1 == NULL || pRoot2 == NULL) // 有一个为空，一个不为空，返回假
        return false;
    bool resultLeft = StructureCmp(pRoot1->m_pLeft, pRoot2->m_pLeft); // 比较对应左子树
    bool resultRight = StructureCmp(pRoot1->m_pRight, pRoot2->m_pRight); // 比较对应右子树
    return (resultLeft && resultRight);
}
/*
 9. 判断二叉树是不是平衡二叉树
 递归解法：
 （1）如果二叉树为空，返回真
 （2）如果二叉树不为空，如果左子树和右子树都是AVL树并且左子树和右子树高度相差不大于1，返回真，其他返回假
 参考代码：
 */
bool IsAVL(BinaryTreeNode * pRoot, int & height)
{
    if(pRoot == NULL) // 空树，返回真
    {
        height = 0;
        return true;
    }
    int heightLeft;
    bool resultLeft = IsAVL(pRoot->m_pLeft, heightLeft);
    int heightRight;
    bool resultRight = IsAVL(pRoot->m_pRight, heightRight);
    if(resultLeft && resultRight && abs(heightLeft - heightRight) <= 1) // 左子树和右子树都是AVL，并且高度相差不大于1，返回真
    {
        height = max(heightLeft, heightRight) + 1;
        return true;
    }
    else
    {
        height = max(heightLeft, heightRight) + 1;
        return false;
    }
}
/*
 10. 求二叉树的镜像
 递归解法：
 （1）如果二叉树为空，返回空
 （2）如果二叉树不为空，求左子树和右子树的镜像，然后交换左子树和右子树
 参考代码如下
 */
BinaryTreeNode * Mirror(BinaryTreeNode * pRoot)
{
    if(pRoot == NULL) // 返回NULL
        return NULL;
    BinaryTreeNode * pLeft = Mirror(pRoot->m_pLeft); // 求左子树镜像
    BinaryTreeNode * pRight = Mirror(pRoot->m_pRight); // 求右子树镜像
    // 交换左子树和右子树
    pRoot->m_pLeft = pRight;
    pRoot->m_pRight = pLeft;
    return pRoot;
}
/*
 11. 求二叉树中两个节点的最低公共祖先节点
 递归解法：
 （1）如果两个节点分别在根节点的左子树和右子树，则返回根节点
 （2）如果两个节点都在左子树，则递归处理左子树；如果两个节点都在右子树，则递归处理右子树
 参考代码如下：
 */
bool FindNode(BinaryTreeNode * pRoot, BinaryTreeNode * pNode)
{
    if(pRoot == NULL || pNode == NULL)
        return false;
    
    if(pRoot == pNode)
        return true;
    
    bool found = FindNode(pRoot->m_pLeft, pNode);
    if(!found)
        found = FindNode(pRoot->m_pRight, pNode);
    
    return found;
}

BinaryTreeNode * GetLastCommonParent(BinaryTreeNode * pRoot,
                                     BinaryTreeNode * pNode1,
                                     BinaryTreeNode * pNode2)
{
    if(FindNode(pRoot->m_pLeft, pNode1))
    {
        if(FindNode(pRoot->m_pRight, pNode2))
            return pRoot;
        else
            return GetLastCommonParent(pRoot->m_pLeft, pNode1, pNode2);
    }
    else
    {
        if(FindNode(pRoot->m_pLeft, pNode2))
            return pRoot;
        else
            return GetLastCommonParent(pRoot->m_pRight, pNode1, pNode2);
    }
}
/*
 递归解法效率很低，有很多重复的遍历，下面看一下非递归解法。
 非递归解法：
 先求从根节点到两个节点的路径，然后再比较对应路径的节点就行，最后一个相同的节点也就是他们在二叉树中的最低公共祖先节点
 参考代码如下：
 */
bool GetNodePath(BinaryTreeNode * pRoot, BinaryTreeNode * pNode,
                 list<BinaryTreeNode *> & path)
{
    if(pRoot == pNode)
    {
        path.push_back(pRoot);
        return true;
    }
    if(pRoot == NULL)
        return false;
    path.push_back(pRoot);
    bool found = false;
    found = GetNodePath(pRoot->m_pLeft, pNode, path);
    if(!found)
        found = GetNodePath(pRoot->m_pRight, pNode, path);
    if(!found)
        path.pop_back();
    return found;
}
BinaryTreeNode * GetLastCommonParent(BinaryTreeNode * pRoot, BinaryTreeNode * pNode1, BinaryTreeNode * pNode2)
{
    if(pRoot == NULL || pNode1 == NULL || pNode2 == NULL)
        return NULL;
    list<BinaryTreeNode*> path1;
    bool bResult1 = GetNodePath(pRoot, pNode1, path1);
    list<BinaryTreeNode*> path2;
    bool bResult2 = GetNodePath(pRoot, pNode2, path2);
    if(!bResult1 || !bResult2)
        return NULL;
    BinaryTreeNode * pLast = NULL;
    list<BinaryTreeNode*>::const_iterator iter1 = path1.begin();
    list<BinaryTreeNode*>::const_iterator iter2 = path2.begin();
    while(iter1 != path1.end() && iter2 != path2.end())
    {
        if(*iter1 == *iter2)
            pLast = *iter1;
        else
            break;
        iter1++;
        iter2++;
    }
    return pLast;
}
/*
 12. 求二叉树中节点的最大距离
 即二叉树中相距最远的两个节点之间的距离。
 递归解法：
 （1）如果二叉树为空，返回0，同时记录左子树和右子树的深度，都为0
 （2）如果二叉树不为空，最大距离要么是左子树中的最大距离，要么是右子树中的最大距离，要么是左子树节点中到根节点的最大距离+右子树节点中到根节点的最大距离，同时记录左子树和右子树节点中到根节点的最大距离。
 参考代码如下：
 */
int GetMaxDistance(BinaryTreeNode * pRoot, int & maxLeft, int & maxRight)
{
    // maxLeft, 左子树中的节点距离根节点的最远距离
    // maxRight, 右子树中的节点距离根节点的最远距离
    if(pRoot == NULL)
    {
        maxLeft = 0;
        maxRight = 0;
        return 0;
    }
    int maxLL, maxLR, maxRL, maxRR;
    int maxDistLeft, maxDistRight;
    if(pRoot->m_pLeft != NULL)
    {
        maxDistLeft = GetMaxDistance(pRoot->m_pLeft, maxLL, maxLR);
        maxLeft = max(maxLL, maxLR) + 1;
    }
    else
    {
        maxDistLeft = 0;
        maxLeft = 0;
    }
    if(pRoot->m_pRight != NULL)
    {
        maxDistRight = GetMaxDistance(pRoot->m_pRight, maxRL, maxRR);
        maxRight = max(maxRL, maxRR) + 1;
    }
    else
    {
        maxDistRight = 0;
        maxRight = 0;
    }
    return max(max(maxDistLeft, maxDistRight), maxLeft+maxRight);
}
/*
 13. 由前序遍历序列和中序遍历序列重建二叉树
 二叉树前序遍历序列中，第一个元素总是树的根节点的值。中序遍历序列中，左子树的节点的值位于根节点的值的左边，右子树的节点的值位
 于根节点的值的右边。
 递归解法：
 （1）如果前序遍历为空或中序遍历为空或节点个数小于等于0，返回NULL。
 （2）创建根节点。前序遍历的第一个数据就是根节点的数据，在中序遍历中找到根节点的位置，可分别得知左子树和右子树的前序和中序遍
 历序列，重建左右子树。
 */
BinaryTreeNode * RebuildBinaryTree(int* pPreOrder, int* pInOrder, int nodeNum)
{
    if(pPreOrder == NULL || pInOrder == NULL || nodeNum <= 0)
        return NULL;
    BinaryTreeNode * pRoot = new BinaryTreeNode;
    // 前序遍历的第一个数据就是根节点数据
    pRoot->m_nValue = pPreOrder[0];
    pRoot->m_pLeft = NULL;
    pRoot->m_pRight = NULL;
    // 查找根节点在中序遍历中的位置，中序遍历中，根节点左边为左子树，右边为右子树
    int rootPositionInOrder = -1;
    for(int i = 0; i < nodeNum; i++)
        if(pInOrder[i] == pRoot->m_nValue)
        {
            rootPositionInOrder = i;
            break;
        }
    if(rootPositionInOrder == -1)
    {
        throw std::exception("Invalid input.");
    }
    // 重建左子树
    int nodeNumLeft = rootPositionInOrder;
    int * pPreOrderLeft = pPreOrder + 1;
    int * pInOrderLeft = pInOrder;
    pRoot->m_pLeft = RebuildBinaryTree(pPreOrderLeft, pInOrderLeft, nodeNumLeft);
    // 重建右子树
    int nodeNumRight = nodeNum - nodeNumLeft - 1;
    int * pPreOrderRight = pPreOrder + 1 + nodeNumLeft;
    int * pInOrderRight = pInOrder + nodeNumLeft + 1;
    pRoot->m_pRight = RebuildBinaryTree(pPreOrderRight, pInOrderRight, nodeNumRight);
    return pRoot;
}
/*
 14.判断二叉树是不是完全二叉树
 若设二叉树的深度为h，除第 h 层外，其它各层 (1～h-1) 的结点数都达到最大个数，第 h 层所有的结点都连续集中在最左边，这就是完全
 二叉树。
 有如下算法，按层次（从上到下，从左到右）遍历二叉树，当遇到一个节点的左子树为空时，则该节点右子树必须为空，且后面遍历的节点左
 右子树都必须为空，否则不是完全二叉树。
 */
bool IsCompleteBinaryTree(BinaryTreeNode * pRoot)
{
    if(pRoot == NULL)
        return false;
    queue<BinaryTreeNode *> q;
    q.push(pRoot);
    bool mustHaveNoChild = false;
    bool result = true;
    while(!q.empty())
    {
        BinaryTreeNode * pNode = q.front();
        q.pop();
        if(mustHaveNoChild) // 已经出现了有空子树的节点了，后面出现的必须为叶节点（左右子树都为空）
        {
            if(pNode->m_pLeft != NULL || pNode->m_pRight != NULL)
            {
                result = false;
                break;
            }
        }
        else
        {
            if(pNode->m_pLeft != NULL && pNode->m_pRight != NULL)
            {
                q.push(pNode->m_pLeft);
                q.push(pNode->m_pRight);
            }
            else if(pNode->m_pLeft != NULL && pNode->m_pRight == NULL)
            {
                mustHaveNoChild = true;
                q.push(pNode->m_pLeft);
            }
            else if(pNode->m_pLeft == NULL && pNode->m_pRight != NULL)
            {
                result = false;
                break;
            }
            else
            {
                mustHaveNoChild = true;
            }
        }
    }
    return result;
}

}

//smartpointer implemention
template <typename T>
class SmartPointer{
public:
    SmartPointer(T* ptr){
        ref = ptr;
        ref_count = (unsigned*)malloc(sizeof(unsigned));
        *ref_count = 1;
    }
    
    SmartPointer(SmartPointer<T> &sptr){
        ref = sptr.ref;
        ref_count = sptr.ref_count;
        ++*ref_count;
    }
    
    SmartPointer<T>& operator=(SmartPointer<T> &sptr){
        if (this != &sptr) {
            if (--*ref_count == 0){
                clear();
                cout<<"operator= clear"<<endl;
            }
            
            ref = sptr.ref;
            ref_count = sptr.ref_count;
            ++*ref_count;
        }
        return *this;
    }
    
    ~SmartPointer(){
        if (--*ref_count == 0){
            clear();
            cout<<"destructor clear"<<endl;
        }
    }
    
    T getValue() { return *ref; }
    
private:
    void clear(){
        delete ref;
        free(ref_count);
        ref = NULL; // 避免它成为迷途指针
        ref_count = NULL;
    }
    
protected:
    T *ref;
    unsigned *ref_count;
};

int main_smartpointer(){
    int *ip1 = new int();
    *ip1 = 11111;
    int *ip2 = new int();
    *ip2 = 22222;
    SmartPointer<int> sp1(ip1), sp2(ip2);
    SmartPointer<int> spa = sp1;
    sp2 = spa;
    return 0;
}



/*
 在二维平面上，有一些点，请找出经过点数最多的那条线。
 给定一个点集vector p和点集的大小n，请返回一个vector，代表经过点数最多的那条直线的斜率和截距。
 */

//这个的复杂度有点高O(N^3)，有没有可能降到O(N^2logN)，极限应该是O(N^2)
class DenseLine {
public:
    vector<double> getLine(vector<Point> p, int n) {
        // write code here
        assert(n >= 2);                     //直接假定点的个数大于等于2
        vector<double> result(2,0.0);
        int max = -1;
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                int count = 0;
                if (p[i].x == p[j].x){      //没有考虑垂直方向上的斜率
                    continue;
                }
                else{
                    double slope = (p[j].y - p[i].y) * 1.0 / (p[j].x - p[i].x);
                    double intercept = p[j].y - slope * p[j].x;
                    for (int t = 0; t < n; t++)   //其实这一步
                        if (abs(p[t].y-slope * p[t].x -intercept)<0.00001){
                            ++count;
                        }
                    
                    if (count > max){
                        max = count;
                        result[0] = slope;
                        result[1] = intercept;
                    }
                }
                
            }
        }
        return result;
    }
};

//接下来这个就是O(N2LogN)的复杂度
struct P
{
    int x;
    int y;
}point[702];

double slope(struct P a,struct P b)
{
    if(a.x==b.x)
        return 100000;
    double px=a.x-b.x;
    double py=a.y-b.y;
    return py/px;
}

int DenseLine_sortSlope()
{
    int n;
    int i,j,cnt,t,max;
    double k[702];
    while(scanf("%d",&n)!=EOF&&n)
    {
        for(i=0;i<n;i++)
            scanf("%d%d",&point[i].x, &point[i].y);
        max = -1;
        for(i = 0; i < n; i++)    //先固定一个点
        {
            t = 0;
            for(j = i+1;j < n; j++)
            {
                k[t++] = slope(point[i],point[j]);
            }
            sort(k,k+t);
            for(j=1,cnt=1; j<t; j++)        //排序之后看有哪些“相等”的。
            {
                if(fabs(k[j]-k[j-1]) < 0.00001)
                    cnt++;
                else
                    cnt = 1;
                if(cnt > max)
                    max = cnt;
            }
        }
        printf("%d\n",max+1);
    }
    return 0;
}

//上面的也太高了，最低的应该是O(N2)的复杂度，这里采用hash函数来判断是否重复
namespace line_dense {


struct point{
    double x, y;
};
class line{
public:
    double epsilon, slope, intercept;
    bool bslope;
public:
    line(){}
    line(point p, point q){
        epsilon = 0.0001;
        if(abs(p.x - q.x) > epsilon){
            slope = (p.y-q.y) / (p.x-q.x);
            intercept = p.y - slope * p.x;
            bslope = true;
        }
        else{
            bslope = false;
            intercept = p.x;
        }
    }
    int hashcode(){             //只要是看是否以前已经做过某个事或者检索过一些值，都可以用hash，只不过这里是double型的数据，这里采用了一个十分美妙的方法，转换成整数的hash
        int sl = (int)(slope * 1000);
        int in = (int)(intercept * 1000);
        return sl*1000 +  in;       //不过这个hash是否靠谱呢，会有重合的呢？
    }
    void print(){
        cout<<"y = "<<slope<<"x + "<<intercept<<endl;
    }
};

line find_best_line(point *p, int point_num){
    line bestline;
    bool first = true;
    map<int, int> mii;
    for(int i=0; i<point_num; ++i){
        for(int j=i+1; j<point_num; ++j){
            line l(p[i], p[j]);
            if(mii.find(l.hashcode()) == mii.end()){
                mii[l.hashcode()] = 0;
            }
            mii[l.hashcode()] = mii[l.hashcode()] + 1;
            if(first){              //引入额外flag来判断是否是第一个坐标点
                bestline = l;
                first = false;
            }
            else{
                if(mii[l.hashcode()] > mii[bestline.hashcode()])
                    bestline = l;
            }
        }
    }
    // int a = mii[bestline.hashcode()];
    // cout<<mii[bestline.hashcode()]<<endl;
    // cout<<(1+sqrt(1+8*a))/2<<endl;
    return bestline;
}
int main_test_line(){
    srand((unsigned)time(0));
    int graph_size = 100;
    int point_num = 500;
    point *p = new point[point_num];
    for(int i=0; i<point_num; ++i){
        p[i].x = rand()/double(RAND_MAX) * graph_size;
        p[i].y = rand()/double(RAND_MAX) * graph_size;
        //cout<<p[i].x<<" "<<p[i].y<<endl;
    }
    line l = find_best_line(p, point_num);
    l.print();
    return 0;
}


}

//与上面的类似，只不过不用hash，直接用map，将线作为key，个数作为value
namespace line_dense2 {
    
struct point{
    double x, y;
};
class line{
public:
    double epsilon, slope, intercept;
    bool bslope;
public:
    line(){}
    line(point p, point q){
        epsilon = 0.0001;
        if(abs(p.x - q.x) > epsilon){
            slope = (p.y-q.y) / (p.x-q.x);
            intercept = p.y - slope * p.x;
            bslope = true;
        }
        else{
            bslope = false;
            intercept = p.x;
        }
    }
    void print(){
        cout<<"y = "<<slope<<"x + "<<intercept<<endl;
    }
};

//map里面要求重构小于符和等于符ƒ
bool operator <(const line &l1, const line &l2){
    return l1.slope < l2.slope;
}
bool equal(double a, double b){
    return abs(a-b) < 0.0001;
}
bool operator ==(const line &l1, const line &l2){
    if(l1.bslope == l2.bslope && equal(l1.slope, l2.slope) && equal(l1.intercept, l2.intercept))
        return true;
    return false;
}
line find_best_line(point *p, int point_num){
    line bestline;
    bool first = true;
    map<line, int> line_count;
    for(int i=0; i<point_num; ++i){
        for(int j=i+1; j<point_num; ++j){
            line l(p[i], p[j]);
            if(line_count.find(l)==line_count.end())
                line_count[l] = 0;
            line_count[l] = line_count[l] + 1;
            if(first){
                bestline = l;
                first = false;
            }
            else{
                if(line_count[l] > line_count[bestline])
                    bestline = l;
            }
        }
    }
    cout<<line_count[bestline]<<endl;
    return bestline;
}
int main_test_line2(){
    srand((unsigned)time(0));
    int graph_size = 10;
    int point_num = 500;
    point *p = new point[point_num];
    for(int i=0; i<point_num; ++i){
        p[i].x = rand()/double(RAND_MAX) * graph_size;
        p[i].y = rand()/double(RAND_MAX) * graph_size;
        cout<<p[i].x<<" "<<p[i].y<<endl;
    }
    line l = find_best_line(p, point_num);
    l.print();
    return 0;
}

}
//
/*
 有一个正整数，请找出其二进制表示中1的个数相同、且大小最接近的那两个数。(一个略大，一个略小)
 */
//最接近的数

class CloseNumber {
public:
    vector<int> getCloseNumber(int x) {
        // write code here
        vector<int> v;
        int next = getNext(x);
        int prev = getPrev(x);
        v.push_back(prev);
        v.push_back(next);
        return v;
    }
private:
    int getNext(int x) {        //这个思路可以用来求permutation,也可以说这个思路得益于next_permutation
        int c0 = 0;
        int c1 = 0;
        int n = x;
        while ((n & 1) == 0 && (n!= 0)) {
            c0++;
            n >>= 1;
        }
        while ((n & 1) == 1) {
            c1++;
            n >>= 1;
        }
        if (c0 + c1 >= 31) {
            return -1;
        }
        
        x |=  (1 << (c0+c1));
        x &=  ~((1 << (c0+c1)) - 1);
        x |=  (1 << (c1-1)) - 1;
        return x;
    }
    int getPrev(int x) {
        int c1 = 0;
        int c0 = 0;
        int n = x;
        while ((n & 1) == 1) {
            c1++;
            n >>= 1;
        }
        while ((n & 1) == 0 && ( n!=0)) {
            c0++;
            n >>= 1;
        }
        if (c0 + c1 >= 31)
            return -1;
        x &= ((~0) << (c0+c1+1));
        x |= (((1 << (c1+1)) - 1) << (c0 - 1));
        return x;
    }
};



//minimum window substring
/*
 Given a string S and a string T, find the minimum window in S which will
 contain all the characters in T in complexity O(n).
 
 For example,
 S = "ADOBECODEBANC"
 T = "ABC"
 Minimum window is "BANC".
 */
//快慢指针、双指针的用法，之精髓
/*
 
 */
string minWindow(string S, string T) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int nT = T.size();
    int nS = S.size();
    
    int needToFind[256] = {0};          //记录string T中需要找到的字符串信息
    for (int i = 0; i < nT; ++i)
        ++needToFind[T[i]];
    int hasFound[256] = {0};            //目前已经找到的字符串信息
    int minBegin;
    int minEnd;
    int minWindow = nS + 1;
    int count = 0;                      //记录是否已经找到满足条件的字符串
    
    for (int begin = 0, end = 0; end < nS; ++end)
    {
        if (needToFind[S[end]] == 0)
            continue;
        char ch = S[end];
        ++hasFound[ch];
        if (hasFound[ch] <= needToFind[ch])
            ++count;                //这道题目特别有意思
        
        if (count == nT)
        {
            while (needToFind[S[begin]] == 0
                   || hasFound[S[begin]] > needToFind[S[begin]])
            {
                if (hasFound[S[begin]] > needToFind[S[begin]])
                    --hasFound[S[begin]];
                ++begin;
            }
            
            int length = end - begin + 1;
            if (length < minWindow)
            {
                minBegin = begin;
                minEnd = end;
                minWindow = length;
            }
        }
    }
    
    return minWindow <= nS ? S.substr(minBegin, minEnd-minBegin+1) : "";
}

class Solution_minWindow {
public:
    string minWindow(string S, string T) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int nT = T.size();
        int nS = S.size();
        
        int needToFind[256] = {0};
        for (int i = 0; i < nT; ++i)
            ++needToFind[T[i]];
        int hasFound[256] = {0};
        int minBegin;
        int minEnd;
        int minWindow = nS + 1;
        int count = 0;
        
        for (int begin = 0, end = 0; end < nS; ++end)
        {
            if (needToFind[S[end]] == 0)
                continue;
            char ch = S[end];
            ++hasFound[ch];
            if (hasFound[ch] <= needToFind[ch])
                ++count;
            
            if (count == nT)
            {
                while (needToFind[S[begin]] == 0
                       || hasFound[S[begin]] > needToFind[S[begin]])
                {
                    if (hasFound[S[begin]] > needToFind[S[begin]])
                        --hasFound[S[begin]];
                    ++begin;
                }
                
                int length = end - begin + 1;
                if (length < minWindow)
                {
                    minBegin = begin;
                    minEnd = end;
                    minWindow = length;
                }
            }
        }
        
        return minWindow <= nS ? S.substr(minBegin, minEnd-minBegin+1) : "";
    }
};


//
/*
 二叉搜索树建立、插入、删除、前继节点、后继节点
*/
//
namespace BST {
    

    typedef struct Node
    {
        int key;                //键值
        struct Node *left;		//左节点
        struct Node *right;     //右节点
        struct Node *father;	//父节点
        int times;              //节点出现的次数
    } Node, *pNode;

    void creatBinarySearchTree(pNode &pBSTTree, int *ptr, int len);
    void insertNode(pNode &pBSTTree, int value);
    void mallocInitNode(pNode &pInsertNode, int value);
    pNode findMinNode(pNode &pTree);
    pNode findMaxNode(pNode &pTree);
    pNode findPredecessor(pNode &pSearchNode);
    pNode findSuccessor(pNode &pSearchNode);
    void deleteNode(pNode& pdeleteNode);
    void changeFatherChildNode(pNode& pdeleteNode, pNode& pNewChildNode);

    int main_BST()
    {
        int a[] = {15,15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
        int len = sizeof(a) / sizeof(int);
        pNode pBSTTree = NULL;
        pNode pPreNode = NULL;
        pNode pSuccessor = NULL;
        
        /* 创建二叉查找树 */
        creatBinarySearchTree(pBSTTree, a, len);
        
        /* 寻找二叉查找树中的最大值 */
        cout << "最小值的节点为:" << findMinNode(pBSTTree)->key << endl;
        cout << "最大值的节点为:" << findMaxNode(pBSTTree)->key << endl;
        
        /* 寻找某个节点的前驱节点 */
        pPreNode = findPredecessor(pBSTTree->left->right);
        if (NULL != pPreNode)
        {
            cout << "该节点的前驱节点为:" << pPreNode->key << endl;
        }
        else
        {
            cout << "该节点无前驱节点" << endl;
        }
        
        /* 寻找某个节点的后继节点 */
        pSuccessor = findSuccessor(pBSTTree->left->left->left);
        if (NULL != pPreNode)
        {
            cout << "该节点的后继节点为:" << pSuccessor->key << endl;
        }
        else
        {
            cout << "该节点无后继节点" << endl;
        }
        
        /* 删除某个节点 */
        deleteNode(pBSTTree->right->right);
        deleteNode(pBSTTree->left->left);
        cout << "最小值的节点为:" << findMinNode(pBSTTree)->key << endl;
        pSuccessor = findSuccessor(pBSTTree->left->left);
        if (NULL != pPreNode)
        {
            cout << "该节点的后继节点为:" << pSuccessor->key << endl;
        }
        else
        {
            cout << "该节点无后继节点" << endl;
        }
        
        free(pBSTTree);
        pBSTTree = NULL;
        return 0;
    }

    /* 创建一个二叉查找树 */
    void creatBinarySearchTree(pNode &pBSTTree, int *ptr, int len)
    {
        for (int i = 0; i < len; i++)
        {
            insertNode(pBSTTree, *(ptr + i));
        }
    }


    /* 插入一个节点，复杂度为O(nlogn) */
    void insertNode(pNode &pBSTTree, int value)
    {
        pNode pInsertNode;
        
        /* 第一个节点，直接插入 */
        if (NULL == pBSTTree)
        {
            mallocInitNode(pInsertNode, value);
            pBSTTree = pInsertNode;
            return;
        }
        
        /* 如果键值已经存在的话，只需要times++ */
        if (value == pBSTTree->key)
        {
            pBSTTree->times++;
            return;
        }
        
        /* 如果小于本节点的值，且该节点无左孩子 */
        if ((NULL == pBSTTree->left) && (value < pBSTTree->key))
        {
            mallocInitNode(pInsertNode, value);
            pInsertNode->father = pBSTTree;
            pBSTTree->left = pInsertNode;
            return;
        }
        
        /* 如果大于本节点的值，且该节点无右孩子 */
        if ((NULL == pBSTTree->right) && (value > pBSTTree->key))
        {
            mallocInitNode(pInsertNode, value);
            pInsertNode->father = pBSTTree;
            pBSTTree->right = pInsertNode;
            return;
        }
        
        /* 如果小于本节点的值，但是该节点已经有左孩子，那么就继续递归 */
        if ((NULL != pBSTTree->left) && (value < pBSTTree->key))
        {
            insertNode(pBSTTree->left, value);
        }
        
        /* 如果大于本节点的值，但是该节点已经有右孩子，那么就继续递归 */
        if ((NULL != pBSTTree->right) && (value > pBSTTree->key))
        {
            insertNode(pBSTTree->right, value);
        }
    }

    /* 创建新节点并初始化 */
    void mallocInitNode(pNode &pInsertNode, int value)
    {
        pInsertNode = (pNode)malloc(sizeof(Node));
        pInsertNode->key = value;
        pInsertNode->father = NULL;
        pInsertNode->left = NULL;
        pInsertNode->right = NULL;
        pInsertNode->times = 1;
    }

    /* 寻找二叉树中最小的节点和最大的节点 */
    pNode findMinNode(pNode &pTree)
    {
        pNode pTemp = pTree;
        while (NULL != pTemp->left)
        {
            pTemp = pTemp->left;
        }
        return pTemp;
        
        
    }

    pNode findMaxNode(pNode &pTree)
    {
        pNode pTemp = pTree;
        while (NULL != pTemp->right)
        {
            pTemp = pTemp->right;
        }
        return pTemp;
    }

    /* 找出前驱节点 */
    pNode findPredecessor(pNode &pSearchNode)
    {
        /* 如果左子树存在的话，则返回左子树中最大的节点，即为比它小的之中的最大的节点 */
        if (NULL != pSearchNode->left)
        {
            return findMaxNode(pSearchNode->left);
        }
        
        /* 如果左子树不存在的话，则需要往上找，直到找到目标节点是目标节点父亲节点的右孩子 */
        pNode pTemp = pSearchNode;
        while(pTemp != pTemp->father->right)
        {
            pTemp = pTemp->father;
        }
        return pTemp->father;
    }

    /* 找出后继节点 */
    pNode findSuccessor(pNode &pSearchNode)
    {
        /* 如果右子树存在的话，则返回右子树中最小的节点，即为比它大的之中的最小的节点 */
        if (NULL != pSearchNode->right)
        {
            return findMinNode(pSearchNode->right);
        }
        
        /* 如果左子树不存在的话，则需要往上找，直到找到目标节点是目标节点父亲节点的左孩子 */
        pNode pTemp = pSearchNode;
        while(pTemp != pTemp->father->left)
        {
            pTemp = pTemp->father;
        }
        return pTemp->father;
    }

    void deleteNode(pNode& pdeleteNode)
    {
        /* 1.判断该节点的个数，如果节点的个数大于或等于1，则直接将该节点的个数-1 */
        if (1 < pdeleteNode->times)
        {
            pdeleteNode->times--;
            return;
        }
        /* 2.如果该节点只有一个，那么考虑删除 */
        /* 2.1 如果该节点没有孩子，则直接删除 */
        pNode pTemp = NULL;
        if ((NULL == pdeleteNode->left) && (NULL == pdeleteNode->right))
        {
            changeFatherChildNode(pdeleteNode, pTemp);
        }
        /* 2.2 如果该节点只有一个孩子，那么直接用该孩子代替该节点 */
        else if ((NULL == pdeleteNode->left) && (NULL != pdeleteNode->right))
        {
            changeFatherChildNode(pdeleteNode, pdeleteNode->right);
        }
        else if ((NULL == pdeleteNode->right) && (NULL != pdeleteNode->left))
        {
            changeFatherChildNode(pdeleteNode, pdeleteNode->left);
        }
        /* 2.3 如果该节点有两个孩子，那么考虑用该节点的前驱或者后继来代替该节点。在此，我们选择用前驱代替该节点 */
        else
        {
            pTemp = findPredecessor(pdeleteNode);
            pNode pRightChild = pdeleteNode->right;
            changeFatherChildNode(pdeleteNode, pTemp);
            pTemp->right = pRightChild;
        }
    }

    void changeFatherChildNode(pNode& pdeleteNode, pNode& pNewChildNode)
    {
        if (pdeleteNode == pdeleteNode->father->right)
        {
            pdeleteNode->father->right = pNewChildNode;			
        }
        else
        {
            pdeleteNode->father->left = pNewChildNode;
        }
    }

}//end of BST

//简洁版
namespace BST2 {
    const int maxn = 100;
    
    typedef struct BST{
        int key;
        BST *lchild, *rchild, *parent;
    }BST;
    
    BST *head, *p, node[maxn];
    int cnt;
    
    void init(){
        head = p = NULL;
        cnt = 0;
        memset(node, '\0', sizeof(node));
    }
    
    void insert(BST* &head, int x){
        if(head == NULL){
            node[cnt].key = x;
            node[cnt].parent = p;
            head = &node[cnt++];
            return;
        }
        p = head;
        if(head->key > x)
            insert(head->lchild, x);
        else
            insert(head->rchild, x);
    }
    
    void inorderTraver(BST *head){
        if(head == NULL) return;
        inorderTraver(head->lchild);
        cout<<head->key<<" ";
        inorderTraver(head->rchild);
    }
    
    BST* search(BST *head, int x){
        if(head == NULL) return NULL;
        if(head->key == x) return head;
        else if(head->key > x)
            search(head->lchild, x);
        else
            search(head->rchild, x);
    }
    
    BST* minimum(BST *head){
        if(head == NULL) return NULL;
        while(head->lchild != NULL)
            head = head->lchild;
        return head;
    }
    
    BST* maximum(BST *head){
        if(head == NULL) return NULL;
        while(head->rchild != NULL)
            head = head->rchild;
        return head;
    }
    
    BST* successor(BST *head){
        if(head->rchild != NULL)
            return minimum(head->rchild);
        BST *y = head->parent;
        while(y!=NULL && y->rchild==head){
            head = y;
            y = y->parent;
        }
        return y;
    }
    
    BST* predecessor(BST *head){
        if(head->lchild != NULL)
            return maximum(head->lchild);
        BST *y = head->parent;
        while(y!=NULL && y->lchild==head){
            head = y;
            y = y->parent;
        }
        return y;
    }
    
    void delet(BST *z){
        if(z->lchild==NULL && z->rchild==NULL){
            if(z==head) head = NULL;
            else if(z->parent->lchild == z)
                z->parent->lchild = NULL;
            else
                z->parent->rchild = NULL;
        }
        
        else if(z->lchild==NULL || z->rchild==NULL){
            if(z==head){
                if(z->lchild) head = z->lchild;
                else head = z->rchild;
                head->parent = NULL;
            }
            else{
                if(z->parent->lchild==z && z->lchild){
                    z->parent->lchild = z->lchild;
                    z->lchild->parent = z->parent;
                }
                else if(z->parent->lchild==z && z->rchild){
                    z->parent->lchild = z->rchild;
                    z->rchild->parent = z->parent;
                }
                else if(z->parent->rchild==z && z->lchild){
                    z->parent->rchild = z->lchild;
                    z->lchild->parent = z->parent;
                }
                else{
                    z->parent->rchild = z->rchild;
                    z->rchild->parent = z->parent;
                }
            }
        }
        
        else{
            BST *s = predecessor(z);
            z->key = s->key;
            if(s->parent == z)
                s->parent->lchild = s->lchild;
            else
                s->parent->rchild = s->lchild;
            if(s->lchild)
                s->lchild->parent = s->parent;
        }
    }
    int main_test_BST(){
        freopen("BST.in", "r", stdin);
        init();
        int x;
        while(cin>>x)
            insert(head, x);
        inorderTraver(head);
        cout<<endl;
        cout<<"Min: "<<(minimum(head))->key<<endl;
        cout<<"Max: "<<(maximum(head))->key<<endl;
        fclose(stdin);
        return 0;
    }
}
//


//实现hash类myhash
class myHash {          //使用开链法来
public:
    Hash(): seed_(131), size_(0) {
        memset(head_, 0, sizeof(head_));
    }
    
    void Insert(const char* str) {
        unsigned int id = hash(str);
        char *dst = (char*)node_[size_].word;
        while(*dst++ = *str++);
        node_[size_].next = head_[id];
        head_[id] = &node_[size_];
        ++size_;
    }
    
    bool Find(const char* str) {            //这要在链表里面找
        unsigned int id = hash(str);
        for(Node* p=head_[id]; p; p=p->next) {
            char* dst = (char*)p->word;
            int i = 0;
            for(; *(str+i) && *(str+i) == *(dst+i); ++i);
            if(!*(str+i) && !*(dst+i))
                return true;
        }
        return false;
    }
    
private:
    unsigned int hash(const char* str) {// BKDR Hash Function，这里可以重载一些其他的类
        unsigned int hash = 0;
        while(*str) {
            hash = hash * seed_ + (*str++);
        }
        return (hash & 0x7FFFFFFF) % kHashSize;
    }
    
private:
    unsigned int seed_;
    unsigned int size_;
    static const int kWordSize = 26 + 1;
    static const int kNodeSize = 20000;
    static const int kHashSize = 10001;
    struct Node {
        char word[kWordSize];
        Node *next;
    };
    Node node_[kNodeSize];
    Node* head_[kHashSize];
};


/*
 对于一个元素各不相同且按升序排列的有序序列，请编写一个算法，创建一棵高度最小的二叉查找树
 */
BinaryTreeNode* buildMinimalTree(vector<int> A, int start, int end) {
    if (start > end)
        return NULL;
    int mid = start + (end - start) / 2;
    BinaryTreeNode* root = new BinaryTreeNode(A[mid]);
    root->m_pLeft = buildMinimalTree(A, start, mid - 1);
    root->m_pRight = buildMinimalTree(A, mid + 1, end);
    return root;
}

BinaryTreeNode* buildMinBST(vector<int> A) {
    int length = A.size();
    if (length <= 0)
        return NULL;
    return buildMinimalTree(A, 0, length);
    
}

//Floyd最短路径算法，其是动态规划算法
//  A[i][j] = min(A[i][j], A[i][k] + A[k][j]) ( 0 <= k <= n-1)
//  只需要六行代码，三行循环，三行松弛

typedef struct
{
    char vertex[VertexNum];                      //顶点表
    int edges[VertexNum][VertexNum];            //邻接矩阵,可看做边表
    int n,e;                                    //图中当前的顶点数和边数
}   MGraph;

void Floyd(MGraph g)
{
　　int A[MAXV][MAXV];
　　int path[MAXV][MAXV];     //保存路线
　　int i,j,k,n=g.n;
　　for(i=0;i<n;i++)
    　　for(j=0;j<n;j++){
            A[i][j]= g.edges[i][j];
            path[i][j] = -1;
    }
　　for(k=0;k<n;k++)
    　　for(i=0;i<n;i++)
        　　for(j=0;j<n;j++)
                if(A[i][j]>(A[i][k]+A[k][j])) {
                    A[i][j]=A[i][k]+A[k][j];
                    path[i][j]=k;
                }
}



//problem:判断一个字符串是不是另一个字符串旋转得到的
//algorithm:
bool isSubstring(string s1, string s2){
    if(s1.find(s2) != string::npos) return true;
    else return false;
}
bool isRotation(string s1, string s2){
    if(s1.length() != s2.length() || s1.length()<=0)
        return false;
    return isSubstring(s1+s1, s2);
}

int main_isrotation(){
    string s1 = "apple";
    string s2 = "pleap";
    cout<<isRotation(s1, s2)<<endl;
    //cout<<string::npos<<endl;
    return 0;
}
/*
 Given a string, find the length of the longest substring without repeating characters. For example, the longest substring without repeating letters for "abcabcbb" is "abc", which the length is 3. For "bbbbb" the longest substring is "b", with the length of 1.
 */

int lengthOfLongestSubstring(string s) {
    int n = s.length();
    if(n<2) return n ;
    int lft = 0,rgt = 0,maxlen = 0;
    bool sign[128] = {false};
    while( rgt < n ){
        //            cout<<lft<<" "<<rgt<<" "<<maxlen<<endl;
        if(sign[s[rgt]] == false){
            sign[s[rgt]] = true;
            rgt++;
            if(maxlen < rgt - lft )
                maxlen = rgt - lft;
            continue;
        }
        sign[s[lft]] =  false;
        lft++;
    }
    return maxlen;
}



//sorted stack  stacksorted stacksort
void Qsort(stack<int> &s){
    priority_queue< int,vector<int>,greater<int> > q;
    while(!s.empty()){
        q.push(s.top());
        s.pop();
    }
    while(!q.empty()){
        s.push(q.top());
        q.pop();
    }
}

stack<int> stackSort(stack<int> s){     //这采用的是插入排序，也可以考虑使用quicksort和mergesort将需要更多的额外空间
    stack<int> t;
    while(!s.empty()){
        int data = s.top();
        s.pop();
        while(!t.empty() && data < t.top()){  //t中始终维持着排序状态，从小到大，从下到上
            s.push(t.top());
            t.pop();
        }
        t.push(data);
    }
    return t;
}

//下面这是建立一个栈，其数据从低到高由小到大排列
template<typename T>
class mystacksorted {
private:
    stack<T> s;
    
public
    void push(T t) {
        if (isempty() || t > top()) //这必须得先判断一下，看是不是有元素，没有元素的话，取top值是没有定义的
            s.push(t);
        else {
            stack<T> tmp;
            while (t < top()) {
                tmp.push(top());
                pop();
            }
            s.push(t);
            while (!tmp.empty) {
                s.push(tmp.top());
                tmp.pop();
            }
        }
            
    }
    
    T top() {
        return s.top();
    }
    
    void pop() {
        s.pop();
    }
    
    bool isempty() {
        return s.isempty();
    }
            
            
};



//用一个向量来实现三个堆栈，这里采用固定分区，当然可以灵活分区，那样就要把数组设置成环状
//problem: zeros
//algorithm;
void zero(int **a, int m, int n){
    bool row[m], col[n];
    memset(row, false, sizeof(row));
    memset(col, false, sizeof(col));
    for(int i=0; i<m; ++i)
        for(int j=0; j<n; ++j)
            if(a[i][j] == 0){
                row[i] = true;
                col[j] = true;
            }
    for(int i=0; i<m; ++i)
        for(int j=0; j<n; ++j)
            if(row[i] || col[j])
                a[i][j] = 0;
}
int main_zero()
{
    freopen("1.7.in", "r", stdin);
    
    int m, n;
    cin>>m>>n;
    
    //建立二维矩阵的方法
    int **a;
    a = new int*[m];
    for(int i=0; i<m; ++i)
        a[i] = new int[n];
    
    
    for(int i=0; i<m; ++i)
        for(int j=0; j<n; ++j)
            cin>>a[i][j];
    for(int i=0; i<m; ++i){
        for(int j=0; j<n; ++j)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
    zero(a, m, n);
    for(int i=0; i<m; ++i){
        for(int j=0; j<n; ++j)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
    fclose(stdin);
    return 0;
}
//自己建立两个二维矩阵内存分配的函数，其实可以用opencv里面的mat类也可以
int** My2DAlloc(int rows, int cols){
    int **arr = (int**)malloc(rows*sizeof(int*));
    for(int i=0; i<rows; ++i)
        arr[i] = (int*)malloc(cols*sizeof(int));
    return arr;
}
int** My2DAlloc1(int rows, int cols){
    int header = rows * sizeof(int*);
    int data = rows * cols * sizeof(int);
    int **arr = (int**)malloc(header + data);
    int *buf = (int*)(arr + rows);
    for(int i=0; i<rows; ++i)
        arr[i] = buf + i * cols;
    return arr;
}
int main_my2dAlloc(){
    int **arr = My2DAlloc1(4, 5);
    arr[2][3] = 23;
    cout<<arr[2][3]<<endl;
    return 0;
}


//problem:
/*
 请实现一种数据结构SetOfStacks，由多个栈组成，其中每个栈的大小为size，当前一个栈填满时，新建一个栈。该数据结构应支持与普通栈相同的push和pop操作。
 给定一个操作序列int[][2] ope(C++为vector<vector<int>>)，每个操作的第一个数代表操作类型，若为1，则为push操作，后一个数为应push的数字；若为2，则为pop操作，后一个数无意义。请返回一个int[][](C++为vector<vector<int>>)，为完成所有操作后的SetOfStacks，顺序应为从下到上，默认初始的SetOfStacks为空。保证数据合法。
 */
//algorithm:by wangbo
vector<vector<int> > setOfStacks(vector<vector<int> > ope, int size) {
    // write code here
    int num = ope.size();
    vector<vector<int> > vStack;
    vector<int> tmp;
    vStack.push_back(tmp);
    
    int curr = 0;
    for (int i = 0; i < num; i++)stac
    {
        if (ope[i][0] == 1){
            if (vStack[curr].size() != size)
                vStack[curr].push_back(ope[i][1]);
            else {
                tmp.clear();
                vStack.push_back(tmp);
                vStack[++curr].push_back(ope[i][1]);
            }
        }
        else {
            if (curr == 0 && vStack[curr].empty())
                return {{0}};
            if (vStack[curr].size() == 1)
            {
                vStack.pop_back();
                curr--;
            }
            else
                vStack[curr].pop_back();
        }
    }
    return  vStack;
}

const int STACK_SIZE = 100;
const int STACK_NUM = 10;
class SetOfStacks{//without popAt()
private:
    stack *st;      //类里有一个数组，存放每一个stack
    int cur;
    int capacity;
    
public:
    SetOfStacks(int capa=STACK_NUM){
        st = new stack[capa];
        cur = 0;
        capacity = capa;
    }
    ~SetOfStacks(){
        delete[] st;
    }
    void push(int val){
        if(st[cur].full()) ++cur;
        st[cur].push(val);
    }
    void pop(){
        if(st[cur].empty()) --cur;
        st[cur].pop();
    }
    int top(){
        if(st[cur].empty()) --cur;
        return st[cur].top();
    }
    bool empty(){
        if(cur==0) return st[0].empty();
        else return false;
    }
    bool full(){
        if(cur==capacity-1) return st[cur].full();
        else return false;
    }
};

//problem: 自己实现stack类，学习编写类，并实现它mystack
class stackmine{            //怎么没有赋值构造函数，stack不需要吧？？？？，但如果误操作赋值构造函数，会出问题（术语叫做：防止浅拷贝）
private:
    int *buf;
    int cur;
    int capacity;
    
public:
    stackmine(int capa = STACK_SIZE){
        buf = new int[capa];
        cur = -1;
        capacity = capa;
    }
    stackmine(){
        delete[] buf;
    }
    void push(int val){
        buf[++cur] = val;
    }
    void pop(){
        --cur;
    }
    int top(){
        return buf[cur];
    }
    bool empty(){
        return cur==-1;
    }
    bool full(){
        return cur==capacity-1;
    }
private:        //防止浅拷贝，这种方法确实防止了浅拷贝，但是如果要把一个类的实例传送到一个函数中，这又怎么办呢？
    stackmine(const stackmine& sm);    //只声明不实现
    const stackmine& operator=(const stackmine& rhis);//只声明不实现
};


//problem:  最长公共前缀,找到一串字符串的最长的公共前缀
//algorithm:
string longestCommonPrefix(vector<string>& strs) {
    if (strs.empty()) return "";    //“”才表示空串
    
    string first = strs[0];
    for (int i = 0; i < first.size(); i++)
    {
        for (int j = 1; j < strs.size(); j++)
            if (strs[j][i] != first[i])
                return first.substr(0, i);
        
    }
    return first;
}


//problem:  求字符串中最长的重复字符串longest duplicate， abcccddccc，最长为ccc
//algorithm:    后缀数组，处理字符串的利器
//后缀数组有两种方法求取：
/*
 后缀数组生成的思路：倍增算法和DC3算法
 方法一：最直接最简单的方法当然是把S的后缀都看作一些普通的字符串，按照一般字符串排序的方法对它们从小到大进行排序，即对A进行排序。最坏时间复杂度是O（n^2）。
 方法二：倍增算法(Doubling Algorithm)，它正是充分利用了各个后缀之间的联系，将构造后缀数组的最坏时间复杂度成功降至O(nlogn)。
 */
/*
 最朴素的算法是，让后缀数组之间两两比较，找出最长的公共字串(注意，这里的最长的公共字串必须是以首字符参与匹配的，如果首字母都不匹配，
 那么长度为0，eg后缀[0]和后缀[1]之间的首字母不匹配，则两者的最长公共字串长度为0)，但是时间复杂度为O(n^2).
 */
int pstrcmp(const void *p, const void *q)
{   return strcmp(*(char**)p, *(char**)q); }
int intcmp(const void *p, const void *q)    //都是这种形式，这是整数的比较
{   return *(int*)p - *(int*)q; }

int comlen(char *p, char *q)
{	int i = 0;
    while (*p && (*p++ == *q++))
        i++;
    return i;
}

bool cmpChar
#define M 1
#define MAXN 100
char c[MAXN], *a[MAXN]; //a中保存的就是字符串的后缀

int longdup_main()
{   int i, ch, n = 0, maxi = 0, maxlen = -1;
    while ((ch = getchar()) != EOF) {
        a[n] = &c[n];
        c[n++] = ch;
    }
    c[n] = 0;
    qsort(a , n, sizeof(char*), pstrcmp);//这一句gcc可以编译通过，而g++就会报错
//    sort(a, a + n, cmpChar);
    
    for (i = 0; i < n-M; i++)
        if (comlen(a[i], a[i+M]) > maxlen) {
            maxlen = comlen(a[i], a[i+M]);
            maxi = i;
        }
    printf("%.*s\n", maxlen, a[maxi]);
    return 0;
}

//problem: 编程珠玑 pearls
//algorithm: 用自己设计的hash函数来统计一个文件中每个单词的数目，当然可以用unordered_map来实现, 底层都是用的hash，也可以用map，底层用的红黑树
int wordsNum_main() {
    map<string, int> words; //也可以换成unordered_map
    map<string, int>::iterator iter;
    string t;
    while (cin >> t)
        words[t]++;
    for ( iter =words.begin(); iter != words.end(); iter++)
        cout << iter->first << " "<< iter->second << "\n";
    return 0;
}
//algorithm: 自己设计的hash函数来实现，pearls
//hashtable的数据结构就是一个包涵单向链的二维数组
namespace wordsStat {
    typedef struct wordNode *pWordNode;
    typedef struct wordNode {
        char *word;
        int count;
        pWordNode next;
    } wordNode;
    
    #define NHASH 29989
    #define MULT 31
    pWordNode bin[NHASH];   //每一个hash节点保留的是一个指针，指向一个单词节点
        //这里有一个弱点是，刚开始就要分配一个hash的数组，有时候可能并不需要这么大的hash表
    //能不能考虑刚开始分配一个小的，当元素个数与散列表的个数之比超过一定的阀值时，再重新分配
    unsigned int hash(char *p)
    {
        unsigned int h = 0;
        for ( ; *p; p++)
            h = MULT * h + *p;
        return h % NHASH;
    }
    
    #define NODEGROUP 1000      //避免多次分配，一次分配多一点的内存
    int nodesleft = 0;
    pWordNode freenode;
    
    pWordNode nmalloc()
    {
        if (nodesleft == 0) {
            freenode = (pWordNode)malloc(NODEGROUP*sizeof(node));   //采用池化技术
            nodesleft = NODEGROUP;
        }
        nodesleft--;
        return freenode++;
    }
    
    #define CHARGROUP 10000
    int charsleft = 0;
    char *freechar;
    
    char *smalloc(int n)
    {
        if (charsleft < n) {
            freechar = (char*)malloc(n+CHARGROUP);
            charsleft = n+CHARGROUP;
        }
        charsleft -= n;
        freechar += n;
        return freechar - n;
    }
    
    void incword(char *s)
    {
        pWordNode p;
        int h = hash(s);
        for (p = bin[h]; p != NULL; p = p->next)
            if (strcmp(s, p->word) == 0) {
                (p->count)++;
                return;
            }
        p = nmalloc();
        p->count = 1;
        p->word = smalloc((int)(strlen(s)+1));
        strcpy(p->word, s);
        p->next = bin[h]; //每次新插入的元素都放在链表的第一个节点前面, bin[h]里面保存的就是单链表的头指针
        bin[h] = p;
    }
    
    int wordsStat_main()
    {
        int i;
        pWordNode p;
        char buf[100];
        for (i = 0; i < NHASH; i++)
            bin[i] = NULL;
        while (scanf("%s", buf) != EOF)
            incword(buf);
        for (i = 0; i < NHASH; i++)
            for (p = bin[i]; p != NULL; p = p->next)
                printf("%s %d\n", p->word, p->count);
        return 0;
    }
}

//problem: 优先队列的实现priority_queue的实现

//algorithm: 用堆来实现，其中两个重要的siftup and siftdown函数
template<class T>
class priqueue {
private:
    int n, maxsize;
    T *x;
    void swap(int i, int j) {
        T t = x[i];
        x[i] = x[j];
        x[j] = t;
    }
    
public:
    priqueue(int m) {
        maxsize = m;
        x = new T[maxsize + 1];
        n = 0;
    }
    
    void insert(T t) {      //这里就是利用下面的siftup的方法
        int i, p;
        x[++n] = t;
        for (i = n; i > 1 && x[p=i/2] > x[i]; i = p)
            swap(p, i);
    }
    
    T extractmin(){         //这里利用下面的siftdown的方法
        int i, c;
        T t = x[1];
        x[i] = x[n--];
        for (i = 1; (c = 2*i) <= n; i = c) {
            if (c+1 <= n && x[c+1] < x[c])
                c++;
            if (x[i] <= x[c])
                break;
            swap(c, i);
        }
        return t;
    }
};
template<class T>
void heapsort(vector<T> &x) {
    int num = x.size();
    priqueue<T> pq;
    for (int i = 0; i < num; i++)
        pq.insert(x[i]);
    for (int i = 0; i < num; i++)
        x[i] = pq.extractmin();
}

namespace heapsort_ {
    
    #define MAX 200000

    void swap( int *data, int i, int j)
    {
        int temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }

    //siftup比较好理解，将每一个元素都与自己的父亲比较，如果自己的值小于父亲的值，就互换，直到到堆顶，或父亲的值小于自己的值为止。
    void siftup(int *data, int n )
    {
        int i = n;
        int p;
        while( 1 )
        {
            if ( i == 1 ) break;
            p = i/2;
            if( data[p] <= data[i]) break;
            swap( data, i, p );
            i = p;
        }
    }

    //这里的n其实意义不大，是指n之后的数据是符合要求的，n之前的数据可能不满足小根堆的要求，调整的方法也是从堆顶开始，初步向小调整
    void siftdown( int *data, int n)
    {
        int i = 1;
        int c = 0;
        while( 1 )
        {
            c = 2 * i;
            if( c > n ) break;
            //取两个孩子中较小的一个与自己作比较
            if( c + 1 <= n && data[ c + 1] < data[c] )
                c++;
            
            //如果孩子的值小于自己的值，则互换
            if( data[i] <= data[c] )
                break;
            swap( data, c, i);
            i = c;
        }
    }
    
    
    int heapsort_main()         //先从第二个元素开始对所有元素进行siftup操作，然后交换堆节点值和末尾节点值（末尾节点为子结构的最大值），然后只需要将新的根节点siftdown即可
    {
        double BegTime, EndTime;
        int data[ MAX + 1];
        int data2[ MAX + 1];
        data2[0] = 0;
        int i= 0;
        srand(5);
        for( i = 1; i <= MAX; i++ )
            data[i] = rand() % 500;
        
        memcpy( data2, data, MAX+1);
        BegTime = clock();
        
        
        //makeheap、make_heap
        for( i = 2; i <= MAX; i++ )
            siftup(data,i);
        
        //heapsort
        for( i =MAX; i >= 2; i--)
        {
            swap(data, 1, i);
            siftdown(data, i - 1 );
        }
        
        
        
        EndTime = clock();
        printf("HeapSort:%gms\n", (EndTime - BegTime) / 1000);
        
        BegTime = clock();
        sort(data2, data2 + MAX + 1);
        EndTime = clock();
        printf("sort: %gms\n", (EndTime - BegTime) / 1000);
        
        
        printf("\n");
        return 0;
    }
}

//problem: 堆排序中的两个最重要的函数siftup和siftdown
//algorithm:
// heap[0]用来存储数组中堆数据的长度，堆数据heap[1]...heap[heapLength]
// 所以数组的实际长度是heapLength+1，我们只对从数组索引为1开始的heapLength个数据进行操作
void siftUp(int* heap, int index)
{
    int heapLength = heap[0];
    
    if (index < 1 || index > heapLength)
        return;
    
    bool done = false;
    while(!done && index > 1)
    {
        if (heap[index] > heap[index / 2])
        {
            int temp = heap[index];
            heap[index] = heap[index / 2];
            heap[index / 2] = temp;
        }
        else
        {
            done = true;            //这里也可以不用引入额外变量，直接用break
        }
        
        index /= 2;
    }
}
void siftDown(int* heap, int index)
{
    int heapLength = heap[0];
    
    if (index < 1 || index * 2 > heapLength)
        return;
    
    bool done = false;
    while(!done && index * 2 <= heapLength)
    {
        index *= 2;
        
        if (index + 1 <= heapLength && heap[index + 1] > heap[index])
            index += 1;
        
        if (heap[index] > heap[index / 2])
        {
            int temp = heap[index];
            heap[index] = heap[index / 2];
            heap[index / 2] = temp;
        }
        else
        {
            done = true;
        }
    }
}

//problem: 产生m个0——n-1的随机数，不能重复random number
//algorithm: 利用一个set来保证不重复以及有序
void genSets(int m, int n){
    set<int> s;
    while (s.size() < m)
        s.insert(rand() % n);
    set<int>::iterator  iter;
    for (iter = s.begin(); iter != s.end(); iter++){
        cout << *iter << endl;
    }
}


//problem: 判断一点是否在多边形内
//algorithm: 射线交点判奇法
// 方法：求解通过该点的水平线与多边形各边的交点
// 结论：单边交点为奇数，成立!
struct point
{
    double x, y;
};

bool PtInPolygon(point p, vector<point> ptPolygon, int nCount)
{
    int nCross = 0;
    for (int i = 0; i < nCount; i++)
    {
        point p1 = ptPolygon[i];
        point p2 = ptPolygon[(i + 1) % nCount];
        // 求解 y=p.y 与 p1p2 的交
        if ( p1.y == p2.y ) // p1p2 与 y=p0.y平行
            continue;
        if ( p.y < min(p1.y, p2.y) ) // 交点在p1p2延长线上
            continue;
        if ( p.y >= max(p1.y, p2.y) ) // 交点在p1p2延长线上
            continue;
        // 求交点的 X 坐标 -----------------------------
        double x = (double)(p.y - p1.y) * (double)(p2.x - p1.x) / (double)(p2.y - p1.y) + p1.x;
        
        if ( x > p.x )
            nCross++; // 只统计单边交点
    }
        // 单边交点为偶数，点在多边形之外 ---
    return (nCross % 2 == 1);
}

//algorithm2: 向量乘积法
//A，B，C 在逆时针方向
//如果D在ABC之外，返回false，否则返回true
//注：此处依赖于A、B、C的位置关系，其位置不能调换
double Product(point A, point B, point C)
{
    return (B.x - A.x) * (C.y - A.y) - (C.x - A.x) * (B.y - A.y);
}

bool isInTriangle(point A, point B, point C, point D)
{
    if (Product(A, B, D) >= 0 && Product(B, C, D) >= 0 && Product(C, A, D) 	 >= 0)
    {
        return true;
    }
    return false;
}

//algorithm3: 7行代码解决问题
//http://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html
int pnpoly(int nvert, float *vertx, float *verty, float testx, float testy)
{
    int i, j, c = 0;
    for (i = 0, j = nvert-1; i < nvert; j = i++) {
        if ( ((verty[i]>testy) != (verty[j]>testy)) &&
            (testx < (vertx[j]-vertx[i]) * (testy-verty[i]) / (verty[j]-verty[i]) + vertx[i]) )
            c = !c;
    }
    return c;
}

//problem: lower_bound 和 upper_bound的实现,Search Insert Position of leetcode
//algorithm:
/*
 int point[10] = {1,3,7,7,9};
 int tmp = upper_bound(point, point + 5, 7) - point;
 //按从小到大，7最多能插入数组point的哪个位置
 tmp = lower_bound(point, point + 5, 7) - point;
 //按从小到大，7最少能插入数组point的哪个位置
 */
int my_lower_bound(int *array, int size, int key)
{
    int first = 0, last = size-1;
    int middle, pos = 0;       //需要用pos记录第一个大于等于key的元素位置
    
    while(first < last)
    {
        middle = (first+last)/2;
        if(array[middle] < key){      //若中位数的值小于key的值，我们要在右边子序列中查找，这时候pos可能是右边子序列的第一个
            first = middle + 1;
            pos = first;
        }
        else{
            last = middle;           //若中位数的值大于等于key，我们要在左边子序列查找，但有可能middle处就是最终位置，所以我们不移动last,
            pos = last;              //而是让first不断逼近last。
        }
    }
    return pos;
}

int searchInsert(vector<int>& nums, int target) {
    int i = 0;
    int j = nums.size() - 1;
    while (i <= j) {
        int mid = i + (j - i) / 2;
        if (nums[mid] < target)
            i = mid + 1;
        else if (nums[mid] > target)
            j = mid - 1;
        else
            return mid;
    }
//    if (j < 0)      return 0;
//    if (i > nums.size())    return nums.size();
    return i;       //直接返回i
}


int my_upper_bound(int *array, int size, int key)
{           //upper_bound返回的是最后一个大于等于val的位置，也是有一个新元素val进来时的插入位置。
    int first = 0, last = size-1;
    int middle, pos = 0;
    
    while(first < last)
    {
        middle = (first+last)/2;
        if(array[middle] > key){     //当中位数大于key时，last不动，让first不断逼近last
            last = middle;
            pos = last;
        }
        else{
            first = middle + 1;     //当中位数小于等于key时，将first递增，并记录新的位置
            pos = first;
        }
    }
    return pos;
}

//problem: 编程之美区间重合判断
/*
 1. 给定一个源区间[x,y]和N个无序的目标区间[x1,y1] [x2,y2] ... [xn,yn]，
    判断源区间[x,y]是不是在目标区间内。
 2. 给定一个窗口区域和系统界面上的N个窗口，判断这个窗口区域是否被已有的窗口覆盖。
 */
//algorithm:
struct interval{
    int low, high;
    interval(int l=0, int h=0):low(l), high(h){}

};

struct {
    bool operator()(const interval &v1, const interval &v2)
    {
        return v1.low < v2.low;
    }
} intervalLess;


int BinarySearchLower(vector<interval> arrayInterval, int len, int target)//注意咱们搜索的数为刚好小于key的那个值
{
    
    int low = 0, pos = 0;
    int high = len-1;
    while(low < high){
        int mid = (low + high)/2;
        if(arrayInterval[mid].low < target) {
            low = mid + 1;
            pos = low;
        }
        else
        {
            high = mid;
            pos = high;
        }
    }
    if (arrayInterval[pos].low > target)    //这一句特别关键，当相等时或者高出数组的最大边缘时，这时不需要减去1，只有当目标值比当前最小插入点处的元素小时，就需要往前移动一位。
        return pos-1;
    else
        return pos;        //返回结果为在哪段中
}

bool intervalCoverage(vector<interval> vIntervals, interval tInterval)
{
    bool flag = false;
    
    int n = (int)vIntervals.size();
    if (n <= 0)
        return flag;
    
    sort(vIntervals.begin(), vIntervals.end(), intervalLess);
    int cnt = 0; //合并以后的区间数
    int lastHigh = vIntervals[0].high;
    
    //合并区间
    for(int i=1; i < n; i++){
        if(lastHigh >= vIntervals[i].low && lastHigh < vIntervals[i].high)
            lastHigh = vIntervals[i].high;
        else{
            vIntervals[cnt].high = lastHigh;
            vIntervals[++cnt].low = vIntervals[i].low;
            lastHigh = vIntervals[i].high;
        }
        
    }
    vIntervals[cnt++].high = lastHigh;
    
    int sLow = BinarySearchLower(vIntervals, cnt, tInterval.low);
 
    //注意这里实现了类似于lower_bound的函数
    int sHigh = BinarySearchLower(vIntervals, cnt, tInterval.high);

    
    if(sLow == sHigh && tInterval.high <= vIntervals[sLow].high)
        //注意要判断
        flag = true;

    return flag;
}


//problem: 不用除法，求N个整数数组中N-1个整数的最大乘积
//algorithm: 统计分析规律
//我刚开始想的就是分析乘积是正还是负，但是考虑到可能产生大数，所以觉得难度就增加了，结果
//发现可以统计正负号的方法
void subarrayMultiplication(int array[], int size)
{
    int zeroNum = 0;
    int negativeNum = 0;
    int positiveNum = 0;
    int maxNegative = INT_MIN;
    int minPositive = INT_MAX;
    int zeroIndex = 0;
    int minNegative = 0;
    for(int i = 0; i < size; ++i) {
        if(array[i] == 0) {
            ++zeroNum;
            zeroIndex = i;
        }
        else if(array[i] < 0) {
            ++negativeNum;
            if(array[i] > maxNegative)
                maxNegative = array[i];
            if(array[i] < minNegative)
                minNegative = array[i];
        }
        else {
            ++positiveNum;
            if(array[i] < minPositive)
                minPositive = array[i];
        }
    }
    
    //如果数组中包含两个或者两个以上0，那么子数组的乘积肯定为0
    if(zeroNum >= 2) {
        printf("all subArray elements' product is equal to zero");
        return;
    }
    
    //如果数组中只包含一个0，那么分两个情况：
    //1.去除该0元素其余所有数的乘积为正，那么去除该0元素后所得的子数组乘积最大
    //2.去除该0元素其余所有数的乘积为负，那么子数组最大的乘积为0，子数组中必须包含0元素
    if(zeroNum == 1) {
        if(negativeNum % 2 == 0) {
            printf("the sunArray elements' indexs is except: %d\n", zeroIndex);
        }
        else {
            printf("the subArray must have the index %d of element\n", zeroIndex);
        }
        
        return;
    }
    
    //如果数组中有偶数个负数：
    //1.假定数组中存在正元素，则去掉最小正元素即可得到子数组的最大乘积
    //2.假定数组中不存在正元素，则需要去掉最小的负数，即绝对值最大的负数
    //如果数组中有奇数个负数：
    //则只需要去掉值最大的负数，及绝对值最小的负数
    if(negativeNum % 2 == 0 && positiveNum > 0) {  //需考虑没有正元素的情况
        printf("the subArray elements' indexs in except: %d\n", minPositive);
    }
    else if(negativeNum % 2 == 0 && positiveNum == 0) {
        printf("the subArray elements' indexs is except: %d\n", minNegative);
    }
    else {
        printf("the subArray elements' indexs is except: %d\n", maxNegative);
    }
    
}



//problem:求N的阶乘的末尾有多少个零，N的阶乘的二进制表示最低位1的位置
//algorithm: N的阶乘可以表示为2^x * 3^y * 5^z。零的个数即为min(x,z)，由于x肯定远大于z所以只需要求5的个数z，二进制表示最低位1即为求x
void nFactor(int N) {   //N!含有质因子为5的个数
    int ret = 0;
    for(int i = 1; i <= N; i++)
    {
        int j = i;
        while(j % 5 ==0)
        {
            ret++;
            j /= 5;
        }
    }
}
int lowestOne(int N)  //N!含有质因子为2的个数
{
    int Ret = 0;
    while(N)
    {
        N >>= 1;
        Ret += N;
    }
    return Ret;
}

//problem:
//algorithm: 用STL中的list来模拟双向链表的结构以及删除工作，只需在迭代器指向末尾节点时，将其指向的下一个节点设置为头结点即可
//
int LastRemaining_Solution1(unsigned int n, unsigned int m)
{
    if(n < 1 || m < 1)
        return -1;
    
    unsigned int i = 0;
    
    list<int> numbers;
    for(i = 0; i < n; ++ i)
        numbers.push_back(i);
    
    list<int>::iterator current = numbers.begin();
    while(numbers.size() > 1)
    {
        for(int i = 1; i < m; ++ i)
        {
            current ++;
            if(current == numbers.end())
                current = numbers.begin();
        }
        
        list<int>::iterator next = ++ current;
        if(next == numbers.end())
            next = numbers.begin();
        
        -- current;
        numbers.erase(current);
        current = next;
    }
    
    return *(current);
}

//
int LastRemaining_Solution2(unsigned int n, unsigned int m)
{
    if(n < 1 || m < 1)
        return -1;
    
    int last = 0;
    for (int i = 2; i <= n; i ++)
        last = (last + m) % i;
    
    return last;
}


//problem: 判断一个五位纸牌是不是一个顺子
//algorithm: 分别排序之后，求出0的个数以及gap的数目，判断zero的个数与gap的数目是否相等，相等则是一个顺子
int compare__(const void *arg1, const void *arg2);

bool IsContinuous(int* numbers, int length)
{
    if(numbers == NULL || length < 1)
        return false;
    
    qsort(numbers, length, sizeof(int), compare__); //其实这里可以用hash来排序，但是由于数据量比较小，优势不明显，所以采用常用的排序算法
    
    int numberOfZero = 0;
    int numberOfGap = 0;

    for(int i = 0; i < length && numbers[i] == 0; ++i)
        ++ numberOfZero;
    
    int small = numberOfZero;
    int big = small + 1;
    while(big < length)
    {
        //
        if(numbers[small] == numbers[big])  //如果有相同的元素，那么肯定不会是顺子
            return false;
        
        numberOfGap += numbers[big] - numbers[small] - 1;
        small = big;
        ++big;
    }
    
    return (numberOfGap > numberOfZero) ? false : true;
}

int compare__(const void *arg1, const void *arg2)
{
    return *(int*)arg1 - *(int*)arg2;
}


//problem: 找到数组中唯一出现一次的两个整数
//algorithm: 利用异或的结果将数组分为两个部分，怎么分组才能使一个数字在其中一组，而另一个数字在另一组，而且保证每一组中其余的元素都是配对出现的
unsigned int FindFirstBitIs1(int num);
bool IsBit1(int num, unsigned int indexBit);

void FindNumsAppearOnce(int data[], int length, int* num1, int* num2)
{
    if (data == NULL || length < 2)
        return;
    
    int resultExclusiveOR = 0;
    for (int i = 0; i < length; ++ i)
        resultExclusiveOR ^= data[i];
    
    unsigned int indexOf1 = FindFirstBitIs1(resultExclusiveOR);
    
    *num1 = *num2 = 0;
    for (int j = 0; j < length; ++ j)
    {
        if(IsBit1(data[j], indexOf1))
            *num1 ^= data[j];
        else
            *num2 ^= data[j];
    }
}

//这就是分组的策略
unsigned int FindFirstBitIs1(int num)
{
    int indexBit = 0;
    while (((num & 1) == 0) && (indexBit < 8 * sizeof(int)))
    {
        num = num >> 1;
        ++ indexBit;
    }
    
    return indexBit;
}
//
bool IsBit1(int num, unsigned int indexBit) //验证第indexBit位是否为1
{
    num = num >> indexBit;
    return (num & 1);
//    也可以是将1往左移
    /*
     bool getBit(int num, index) {检查是否为1
        return (num & (1 << index));
     }
     相应的
     int setBit(int num, index) {
        return (num | (1 <<index));
     }
     */
}


//problem:统计排序的数组中元素k的个数
//algorithm:二分查找法，求出第一个和最后一个k
int GetFirstK(int* data, int length, int k, int start, int end);
int GetLastK(int* data, int length, int k, int start, int end);

int GetNumberOfK(int* data, int length, int k)
{
    int number = 0;
    
    if(data != NULL && length > 0)
    {
        int first = GetFirstK(data, length, k, 0, length - 1);
        int last = GetLastK(data, length, k, 0, length - 1);
        
        if(first > -1 && last > -1)
            number = last - first + 1;
    }
    
    return number;
}

//
int GetFirstK(int* data, int length, int k, int start, int end)
{
    if(start > end)
        return -1;
    
    int middleIndex = (start + end) / 2;
    int middleData = data[middleIndex];
    
    if(middleData == k)
    {
        if((middleIndex > 0 && data[middleIndex - 1] != k)
           || middleIndex == 0)
            return middleIndex;
        else
            end  = middleIndex - 1;
    }
    else if(middleData > k)
        end = middleIndex - 1;
    else
        start = middleIndex + 1;
    
    return GetFirstK(data, length, k, start, end);
}

//
int GetLastK(int* data, int length, int k, int start, int end)
{
    if(start > end)
        return -1;
    
    int middleIndex = (start + end) / 2;
    int middleData = data[middleIndex];
    
    if(middleData == k)
    {
        if((middleIndex < length - 1 && data[middleIndex + 1] != k)
           || middleIndex == length - 1)
            return middleIndex;
        else
            start  = middleIndex + 1;
    }
    else if(middleData < k)
        start = middleIndex + 1;
    else
        end = middleIndex - 1;
    
    return GetLastK(data, length, k, start, end);
}



//problem: 排列，全排列
//algorithm: 递归
/*
 通过找规律，求字符串的全排列，可以看出三步：
 
 首先，求所有可能出现在第一个位置的字符，
 
 其次，把第一个字符和其后面的字符一一交换。如下图所示，分别把第一个字符a和后面的b、c等字符交换的情形。
 
 接着，固定第一个字符，求后面所有字符的排列。这个时候我们仍把后面的所有字符分成两部分：后面字符的第一个字符，以及这个字符之后的所有字符。然后把第一个字符逐一和它后面的字符交换

 */
void Permutation(char* pStr, char* pBegin);

void Permutation(char* pStr)
{
    if(pStr == NULL)
        return;
    
    Permutation1(pStr, pStr);
}

int nPermu;
void Permutation1(char* s, char* cur)//s指向整个字符串的第一个字符，cur指向当前我们做排列操作的字符串的第一个字符
{
    if(*cur == '\0')
    {   //static int nPermu = 0; //可以在这里面定义一个静态变量
        printf("%d: ", nPermu);
        printf("%s\n", s);
        nPermu++;
        return;
    }
    /*
     用123来示例下。123的全排列有123、132、213、231、312、321这六种。首先考虑213和321这二个数是如何得出的。显然这二个都是123中的1与后面两数交换得到的。然后可以将123的第二个数和每三个数交换得到132。同理可以根据213和321来得231和312。因此可以知道——全排列就是从第一个数字起每个数分别与它后面的数字交换
     */
    for(char* p = cur; *p != '\0'; ++ p)
    {
        swap(*p, *cur);
        Permutation1(s, cur + 1);
        swap(*p, *cur);
    }
}

//利用next_permutation直接列出
void Permutation2(string pStr, int length)
{
    sort(pStr.begin(), pStr.end()); //先排一个序
    
    do
    {
        cout << pStr <<endl;
    } while ( next_permutation(pStr.begin(), pStr.end()) );
}//可以自己实现next_permutation，leetcode


//通过建立一个hash来判断是不是重合
void Permutation_o(char* pStr, char* pBegin, map<string, string>& Dinstinct)
{
    if (*pBegin == '\0' )
    {
        map <string, string> :: const_iterator iter;
        string strString(pStr);
        
        if ( Dinstinct.find(strString) == Dinstinct.end() )	//不存在
        {
            cout << pStr <<endl;
            Dinstinct.insert(pair<string, string>(strString, strString));
        }
    }
    else
    {
        for (char* pCh = pBegin; *pCh!='\0'; pCh++)
        {
            swap(*pCh, *pBegin);
            Permutation_o(pStr, pBegin+1, Dinstinct);
            swap(*pCh, *pBegin);
        }
    }
}

void Permutation3(char* pStr)
{
    if (pStr==NULL)
        return;
    
    map<string, string> Dinstinct;
    Permutation_o(pStr,pStr,Dinstinct);
}

int main_permutation3(void)
{
    char str[10] ;
    cout <<"input the string: ";
    cin>> str;
    cout <<"the string's permutation lists:"<<endl;
    Permutation3(str);
    return 0;
}



//k表示当前选取到第几个数，m表示共有多少个数
void Permutation4(char* pStr,int k,int m)
{
    assert(pStr);
    
    if(k == m)
    {
        static int num = 1;  //局部静态变量，用来统计全排列的个数
        printf("第%d个排列\t%s\n",num++,pStr);
    }
    else
    {
        for(int i = k; i <= m; i++)
        {
            swap(*(pStr+k),*(pStr+i));
            Permutation4(pStr, k + 1 , m);
            swap(*(pStr+k),*(pStr+i));
        }
    }
}

int main_permutation4(void)
{
    char str[] = "abc";
    Permutation(str , 0 , strlen(str)-1);
    return 0;
}


//在[nBegin,nEnd)区间中是否有字符与下标为pEnd的字符相等
bool IsSwap(char* pBegin , char* pEnd)
{
    char *p;
    for(p = pBegin ; p < pEnd ; p++)
    {
        if(*p == *pEnd)
            return false;
    }
    return true;
}
//有重复的permutation
void PermutationD(char* pStr , char *pBegin)
{
    assert(pStr);
    
    if(*pBegin == '\0')
    {
        static int num = 1;  //局部静态变量，用来统计全排列的个数
        printf("第%d个排列\t%s\n",num++,pStr);
    }
    else
    {
        for(char *pCh = pBegin; *pCh != '\0'; pCh++)   //第pBegin个数分别与它后面的数字交换就能得到新的排列
        {
            if(IsSwap(pBegin , pCh))
            {
                swap(*pBegin , *pCh);
                Permutation(pStr , pBegin + 1);
                swap(*pBegin , *pCh);
            }
        }
    }
}

int main_permutationD(void)
{
    char str[] = "baa";
    Permutation(str , str);
    return 0;
}


//排列
void Combination(char *string ,int number,vector<char> &result);

void Combination(char *string)
{
    assert(string != NULL);
    vector<char> result;
    int i , length = strlen(string);
    for(i = 1 ; i <= length ; ++i)
        Combination(string , i ,result);
}

void Combination(char *string ,int number , vector<char> &result)
{
    assert(string != NULL);
    if(number == 0)
    {
        static int num = 1;
        printf("第%d个组合\t",num++);
        
        vector<char>::iterator iter = result.begin();
        for( ; iter != result.end() ; ++iter)
            printf("%c",*iter);
        printf("\n");
        return ;
    }
    if(*string == '\0')
        return ;
    result.push_back(*string);
    Combination(string + 1 , number - 1 , result);
    result.pop_back();
    Combination(string + 1 , number , result);
}
//用位计算的方式
vector<string> Combination2(string s ) {
    int n = s.size();
    vector<string> result;

    for (int i = 1 ; i < (1 << n); i++) {
        string tmp = "";
        for (int j = 0; j < n; j++) {
            if (i & (1 << j))
                tmp.insert(tmp.begin(), s[j]);
        }
        result.push_back(tmp);
    }
    return result;
}


int main_combination(void)
{
    char str[] = "abc";
    Combination(str);
    return 0;
}

//problem:放皇后问题
//algorithm: 回溯-分支限定
//使用试探-回溯-剪枝法的头文件，这是用迭代实现的
#define QUEEN_MAX 20
extern int nSolu;
extern int nCheck;
extern int N;

struct Queen{
    int x, y;
    Queen (int xx = 0, int yy = 0) : x(xx), y(yy) {};
    bool operator==(Queen const & q) const {
        return ( x == q.x)       //行冲突
        || (y == q.y)            //列冲突
        || ( x + y == q.x + q.y) //沿对角线冲突
        || ( x - y == q.x - q.y);//沿反对脚线冲突
    }
    bool operator!=(Queen const& q) const { return !(*this == q); }
    
};

void displayRow(Queen& q)
{
    printf("%2d: ", q.x);
    int i = 0;
    while (i++ < q.y) printf("[]");
    printf("#");
    while (i++ < N)  printf("[]");
    printf("%2d\n", q.y);
    
}
void display(std::vector<Queen>& S, int nQueen)
{
    //system("clear");
    for_each(S.rbegin(), S.rend(), displayRow);
    if ( nQueen <= S.size())
        cout << nSolu << " solution(s) found after " << nCheck << " check(s)\n";
    //getchar();
    
}

bool findQueen(std::vector<Queen> qVec, const Queen queen)
{
    vector<Queen>::iterator iterQueen;
    bool flag = true;
    
    for (iterQueen = qVec.begin(); iterQueen != qVec.end(); iterQueen++)
        if ((*iterQueen) == queen) { flag = true; break; }
    if (iterQueen == qVec.end())
        flag = false;
    return flag;
}

//这个好理解一些，整个程序是有三个部分组成，都集中于一个do/while语句中
void placeQueens(int N)
{
    std::vector<Queen> solu; //stack storing the solution
    Queen q(0, 0);// start from the original point
    clock_t c_start = clock();
    
    do {
        
        //while ((q.y < N) && findQueen(solu, q)) //通过与已有皇后的比对
        while ((q.y < N) && find(solu.begin(),solu.end(),q) != solu.end()) //这个快多了，这一个部分是最花费时间的
        {
            q.y++; nCheck++;
        }//尝试找到可摆放下一个皇后的列
        
        if (q.y < N ) { //若存在摆放的列，则
            solu.push_back(q); //摆放上当前的皇后，并
            if ( solu.size() >= N ) //若部分解已成为全局解，则通过全局变量nSolu计数
            {
                nSolu++; display(solu, N);
            }
            q.x++;                  //转入下一行
            q.y = 0;                //从0列开始，试探下一个皇后
        }
        
        
        if ( solu.size() >= N || q.y >= N ) //若已出界，则
        {
            q = solu.back();
            solu.pop_back();
            q.y++;//回溯一行，并继续试探下一列
        }//否则，试探下一行
        
    }while ( (q.x > 0) || (q.y < N)) ; //所有分支均已或穷举或剪枝之后，算法结束,q==(0,N)的时候
    
    clock_t c_end = clock();
    double timeSpended = 1000.0 * (c_end - c_start)/CLOCKS_PER_SEC;
    printf("Time Spended %f (ms)\n", timeSpended);
}


//这个更直观
class Solution_queen3 {
private:
    vector<vector<string> > res;
public:
    vector<vector<string> > solveNQueens(int n) {
        vector<string>cur(n, string(n,'.'));
        helper(cur, 0);
        return res;
    }
    void helper(vector<string> &cur, int row)
    {
        if(row == cur.size())
        {
            res.push_back(cur);
            return;
        }
        for(int col = 0; col < cur.size(); col++)
            if(isValid(cur, row, col))
            {
                cur[row][col] = 'Q';
                helper(cur, row+1);
                cur[row][col] = '.';
            }
    }
    
    //判断在cur[row][col]位置放一个皇后，是否是合法的状态
    //已经保证了每行一个皇后，只需要判断列是否合法以及对角线是否合法。
    bool isValid(vector<string> &cur, int row, int col)
    {
        //列
        for(int i = 0; i < row; i++)
            if(cur[i][col] == 'Q')return false;
        //右对角线(只需要判断对角线上半部分，因为后面的行还没有开始放置)
        for(int i = row-1, j=col-1; i >= 0 && j >= 0; i--,j--)
            if(cur[i][j] == 'Q')return false;
        //左对角线(只需要判断对角线上半部分，因为后面的行还没有开始放置)
        for(int i = row-1, j=col+1; i >= 0 && j < cur.size(); i--,j++)
            if(cur[i][j] == 'Q')return false;
        return true;
    }
};


//这个更简单快速
class Solution_queen {
private:
    vector<vector<string> > res;
public:
    vector<vector<string> > solveNQueens(int n) {
        vector<int> state(n, -1);       //都初始化为-1
        helper(state, 0);
        return res;
    }
    
    void helper(vector<int> &state, int row)
    {//放置第row行的皇后
        int n = state.size();
        if(row == n)
        {
            vector<string> tmpres(n, string(n,'.'));
            for(int i = 0; i < n; i++)
                tmpres[i][state[i]] = 'Q';
            res.push_back(tmpres);
            return;
        }
        for(int col = 0; col < n; col++)
            if(isValid(state, row, col))
            {
                state[row] = col;
                helper(state, row+1);
                state[row] = -1;    //回溯
            }
    }
    
    //判断在row行col列位置放一个皇后，是否是合法的状态
    //已经保证了每行一个皇后，只需要判断列是否合法以及对角线是否合法。
    bool isValid(vector<int> &state, int row, int col)
    {
        for(int i = 0; i < row; i++)//只需要判断row前面的行，因为后面的行还没有放置
            if(state[i] == col || abs(row - i) == abs(col - state[i]))
                return false;
        return true;
    }
};

//迭代版
class Solution_queen2 { //迭代版
private:
    vector<vector<string> > res;
public:
    vector<vector<string> > solveNQueens(int n) {
        vector<int> state(n, -1);
        for(int row = 0, col; ;)
        {
            for(col = state[row] + 1; col < n; col++)//从上一次放置的位置后面开始放置
            {
                if(isValid(state, row, col))
                {
                    state[row] = col;
                    if(row == n-1)//找到了一个解,继续试探下一列
                    {
                        vector<string>tmpres(n, string(n,'.'));
                        for(int i = 0; i < n; i++)
                            tmpres[i][state[i]] = 'Q';
                        res.push_back(tmpres);
                    }
                    else {row++; break;}//当前状态合法，去放置下一行的皇后
                }
            }
            if(col == n)//当前行的所有位置都尝试过，回溯到上一行
            {
                if(row == 0)break;//所有状态尝试完毕，退出
                state[row] = -1;//回溯前清除当前行的状态
                row--;
            }
        }
        return res;
    }
    
    //判断在row行col列位置放一个皇后，是否是合法的状态
    //已经保证了每行一个皇后，只需要判断列是否合法以及对角线是否合法。
    bool isValid(vector<int> &state, int row, int col)
    {
        for(int i = 0; i < row; i++)//只需要判断row前面的行，因为后面的行还没有放置
            if(state[i] == col || abs(row - i) == abs(col - state[i]))
                return false;
        return true;
    }
};


//problem: knight moves
//algorithm: Astar A星算法 A* 主要利用A*算法和BFS算法
struct knight{
    int x,y,step;
    int g,h,f;                                      // f = g + h
    bool operator < (const knight & k) const{      //重载比较运算符
        return f > k.f;
    }
};
knight k;
bool visited[8][8];         //访问标记(关闭列表)
int xs,ys,xt,yt,ans;                               //起点(x1,y1),终点(x2,y2),最少移动次数ans
int dirs[8][2]={{-2,-1},{-2,1},{2,-1},{2,1},{-1,-2},{-1,2},{1,-2},{1,2}};//8个移动方向
priority_queue<knight> priQueue;//最小优先级队列(开启列表)

bool in(const knight & a){                         //判断knight是否在棋盘内
    if(a.x < 0 || a.y < 0 || a.x >= 8  || a.y >= 8)
        return false;
    return true;
}
int Heuristic(const knight &a){                    //manhattan估价函数
    return (abs(a.x-xt) + abs(a.y-yt)) * 10;
}
void Astar(){             //A*算法
    knight current, next;
    while(!priQueue.empty()){
        current = priQueue.top(), priQueue.pop(), visited[current.x][current.y] = true;
        if(current.x == xt && current.y == yt){                 //算法终止条件
            ans = current.step;
            break;
        }
        for(int i = 0; i < 8; i++){ //这里与下面的暴力搜索不一样，这是启发式的
            next.x = current.x+dirs[i][0];
            next.y = current.y+dirs[i][1];
            if(in(next) && !visited[next.x][next.y]){    //依次判断八个位置的属性是否满足要求，再压入队列中
                next.g = current.g + 23;             //23表示根号5乘以10再取其ceil
                next.h = Heuristic(next);
                next.f = next.g + next.h;
                next.step = current.step + 1;
                priQueue.push(next);
            }
        }
    }
}
int Astar_main(){   //测试
    char line[6];
    while(fgets(line, 7, stdin)){
        xs=line[0]-'a',ys=line[1]-'1',xt=line[3]-'a',yt=line[4]-'1';
        memset(visited,false,sizeof(visited));
        k.x=xs,k.y=ys,k.g=k.step=0,k.h=Heuristic(k),k.f=k.g+k.h;
        while(!priQueue.empty()) priQueue.pop();
        priQueue.push(k);
        Astar();
        printf("To get from %c%c to %c%c takes %d knight moves.\n",line[0],line[1],line[3],line[4],ans);
    }
    return 0;
}


//algorithm2: BFS，广度优先搜索，
//也可以是深度优先搜索，只需要把其中的队列改为堆栈就是深度优先搜索
//如果改为优先队列，那就是启发式搜索，类似Astar算法
int n,sx,sy,ex,ey;
int accessed[305][305];
int direction[8][2] = {-1,-2,-2,-1,-2,1,-1,2,1,-2,2,-1,2,1,1,2};
struct grid
{
    int x,y,step;       //每个点维护了到起始点的距离
};

int check(int x,int y)
{
    if(x<0 || x>=n || y<0 || y>=n)
        return 1;
    return accessed[x][y];
}

void bfs()
{
    memset(accessed, 0, sizeof(accessed));
    grid current,next;
    queue<grid> Q;  //深度优先搜索
    current.x = sx;
    current.y = sy;
    current.step = 0;
    accessed[sx][sy] = 1;
    Q.push(current);
    while(!Q.empty())
    {
        current = Q.front();
        Q.pop();
        if(current.x == ex && current.y == ey)
        {
            printf("%d\n",current.step);
            return;
        }
        for(int i = 0;i<8;i++)
        {
            next = current;
            next.x = current.x+direction[i][0];
            next.y = current.y+direction[i][1];
            if(check(next.x,next.y))
                continue;
            next.step = current.step+1;
            accessed[next.x][next.y] = 1;
            Q.push(next);
        }
    }
}

int bfs_main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d%d%d",&n,&sx,&sy,&ex,&ey);
        bfs();
    }
    
    return 0;
}

//algorithm3: 双向BFS算法 BBFS、BiBFS
namespace Bi_Directional_BFS {
    

char ss[3];
char ee[3];
typedef struct node
{
    int x;
    int y;
    int steps;
}node;
int d[8][2]={{-2,1},{-2,-1},{-1,-2},{-1,2},{2,-1},{2,1},{1,-2},{1,2}};
int visited[8][8];
int color[8][8];//区分当前位置是哪个队列查找过了
node s;
node e;
int in(node n)
{
    if(n.x<0||n.y<0||n.x>7||n.y>7)
        return 0;
    return 1;
}
int bfs()
{
    queue<node>qf;         //我发现如果把qf和qb放在外面的话，节省的时间挺惊人的，耗时16MS
    queue<node>qb;
    memset(visited,0,sizeof(visited));
    memset(color,0,sizeof(color));
    qf.push(s);
    qb.push(e);
    visited[s.x][s.y]=0;
    visited[e.x][e.y]=1;
    color[s.x][s.y]=1;//着色
    color[e.x][e.y]=2;
    while(!qf.empty() || !qb.empty())
    {
        if(!qf.empty())
        {
            node st = qf.front();
            qf.pop();
            for(int i=0; i<8; ++i)
            {
                node t;
                t.x = st.x + d[i][0];
                t.y = st.y + d[i][1];
                if(in(t))
                {
                    if(color[t.x][t.y] == 0){
                        visited[t.x][t.y] = visited[st.x][st.y]+1;
                        color[t.x][t.y]=1;
                        qf.push(t);
                    }
                    else if(color[t.x][t.y]==2){
                        return visited[st.x][st.y]+visited[t.x][t.y];
                    }
                }
            }
            
        }
        if(!qb.empty())
        {
            node st=qb.front();
            qb.pop();
            for(int i=0;i<8;++i)
            {
                node t;
                t.x=st.x+d[i][0];
                t.y=st.y+d[i][1];
                if(in(t))
                {
                    if(color[t.x][t.y]==0){
                        visited[t.x][t.y]=visited[st.x][st.y]+1;
                        color[t.x][t.y]=2;
                        qb.push(t);
                    }
                    else if(color[t.x][t.y]==1){
                        return visited[st.x][st.y]+visited[t.x][t.y];
                    }
                }
            }
        }
    }
}
int main_BBFS(int argc, char *argv[])
{
    // freopen("in.txt","r",stdin);
    while(scanf("%s %s",ss,ee)==2)
    {
        s.x=ss[0]-'a';
        s.y=ss[1]-'1';
        e.x=ee[0]-'a';
        e.y=ee[1]-'1';
        s.steps=0;
        e.steps=1;
        if(s.x==e.x && s.y==e.y)
            printf("To get from %s to %s takes 0 knight moves.\n",ss,ee);
        else
            printf("To get from %s to %s takes %d knight moves.\n",ss,ee,bfs());
    }
    return 0;
}

}


//problem: 八数码问题，九宫格问题
//algorithm: 深度优先或者Astar/A*/A star.


//problem:环形打印出一个矩阵
//algorithm:画图来理清思路
/*
 Spiral Matrix
Given an integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.

For example,
Given n = 3,

You should return the following matrix:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
 ]
*/

vector<vector<int>> generateMatrix(int n) {
    vector<vector<int> > matrix(n, vector<int>(n,0));
    int begin = 0;
    int end = n - 1;
    int num = 1;
    while (begin < end) {
        for (int i = begin; i < end; i++)   matrix[begin][i] = num++;
        for (int i = begin; i < end; i++)   matrix[i][end] = num++;
        for (int i = end; i > begin; i--)   matrix[end][i] = num++;
        for (int i = end; i > begin; i--)   matrix[i][begin] = num++;
        begin++;
        end--;
    }
    if (begin == end) {
        matrix[begin][end] = num;
    }
    return matrix;
}


//problem: 求一棵树的镜像
//algorithm: 变相考察树的遍历
void MirrorRecursively(BinaryTreeNode *pNode)
{
    if(pNode == NULL)
        return;
    
    BinaryTreeNode *pTemp = pNode->m_pLeft;
    pNode->m_pLeft = pNode->m_pRight;
    pNode->m_pRight = pTemp;
    
    if(pNode->m_pLeft)
        MirrorRecursively(pNode->m_pLeft);
    
    if(pNode->m_pRight)
        MirrorRecursively(pNode->m_pRight);
}

void MirrorIteratively(BinaryTreeNode* pRoot)
{
    if(pRoot == NULL)
        return;
    
    std::stack<BinaryTreeNode*> stackTreeNode;
    stackTreeNode.push(pRoot);
    
    while(stackTreeNode.size() > 0)
    {
        BinaryTreeNode *pNode = stackTreeNode.top();
        stackTreeNode.pop();
        
        BinaryTreeNode *pTemp = pNode->m_pLeft;
        pNode->m_pLeft = pNode->m_pRight;
        pNode->m_pRight = pTemp;
        
        if(pNode->m_pLeft)
            stackTreeNode.push(pNode->m_pLeft);
        
        if(pNode->m_pRight)
            stackTreeNode.push(pNode->m_pRight);
    }
}



//problem:树的子结构
//algorithm: 递归调用，考察树的遍历，注意边界条件
bool HasSubtreeCore(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2);
bool DoesTree1HaveTree2(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2);
bool HasSubtree(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
    bool result = false;
    
    if(pRoot1 != NULL && pRoot2 != NULL)                //一边遍历一边判断
    {
        if(pRoot1->m_nValue == pRoot2->m_nValue)
            result = DoesTree1HaveTree2(pRoot1, pRoot2); //这就相当于树遍历中的VISIT函数
        if(!result)
            result = HasSubtree(pRoot1->m_pLeft, pRoot2);
        if(!result)
            result = HasSubtree(pRoot1->m_pRight, pRoot2);
    }
    
    return result;
}

bool DoesTree1HaveTree2(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
    if(pRoot2 == NULL) //这三个递归的退出判断特别重要，前后顺序也很重要
        return true;
    
    if(pRoot1 == NULL)
        return false;
    
    if(pRoot1->m_nValue != pRoot2->m_nValue)
        return false;
    
    return DoesTree1HaveTree2(pRoot1->m_pLeft, pRoot2->m_pLeft) &&
    DoesTree1HaveTree2(pRoot1->m_pRight, pRoot2->m_pRight);
}


//problem: 定位到链表中倒数第k个节点
//algorithm:主要考虑鲁棒性，当头结点为空时、k为零时、k大于链表的长度时
node* FindKthToTail(node* pListHead, unsigned int k)
{
    if(pListHead == NULL || k == 0) // 如果k==0,那么由于k的类型是unsigned int则k-1将变成很大的正整数
        return NULL;
    
    node *pAhead = pListHead;
    node *pBehind = NULL;
    
    for(unsigned int i = 0; i < k - 1; ++ i)
    {
        if(pAhead->next != NULL)  //
            pAhead = pAhead->next;
        else
        {
            return NULL;
        }
    }
    
    pBehind = pListHead;
    while(pAhead->next != NULL)
    {
        pAhead = pAhead->next;
        pBehind = pBehind->next;
    }
    
    return pBehind;
}
//下面的递归解法都有O(n)的复杂度
//algorithm1: 采用递归的方式来求，只打印元素的值
int FindKthToTail2(node* head, int i, int k ) {
    if (head == nullptr)
        return 0;
    int i = FindKthToTail(head->next, k);
    if (i == k)
        cout << head.data << endl;
    return i;
}
//algorithm2: 采用递归来实现，返回元素的指针，这里就要用到引用
node* FindKthToTail3(node* head, int k, int &i){
    if (head == NULL )
        return NULL;
    node *nd = FindKthToTail(head->next, k, i);
    i++;
    if (i == k)
        return head;
    else
        return nd;
}


//problem:
//algorithm:
int MinInOrder(int* numbers, int index1, int index2);

int Min(int* numbers, int length)
{
    if(numbers == NULL || length <= 0)
        return -1;
    
    int index1 = 0;
    int index2 = length - 1;
    int indexMid = index1; //初始化
    while(numbers[index1] >= numbers[index2])
    {
        // index1指向第一个递增数组最后一个元素
        // index2指向第二个递增数组最前一个元素
        if(index2 - index1 == 1)
        {
            indexMid = index2;
            break;
        }
        
        //如果下标index1\index2\indexmid指向的数字都相等时，只能用顺序查找的了
        indexMid = (index1 + index2) / 2;
        if(numbers[index1] == numbers[index2]
           && numbers[indexMid] == numbers[index1])
            return MinInOrder(numbers, index1, index2);
        
        // 缩小查找范围
        if(numbers[indexMid] >= numbers[index1])
            index1 = indexMid;
        else if(numbers[indexMid] <= numbers[index2])
            index2 = indexMid;
    }
    
    return numbers[indexMid];
}

int MinInOrder(int* numbers, int index1, int index2)
{
    int result = numbers[index1];
    for(int i = index1 + 1; i <= index2; ++i)
    {
        if(result > numbers[i])
            result = numbers[i];
    }
    
    return result;
}


//problem: 利用两个栈实现队列的功能myQueue
//algorithm: stack1用于入栈，stack2用于弹出，当stack2为空时，将stack1中的所有元素压入stack2中
template <typename T> class myQueueWithStack
{
public:
    myQueueWithStack(void);
    ~myQueueWithStack(void);
    
    void enqueue(const T& node);
    
    T dequeue();
    
private:
    stack<T> stack1;
    stack<T> stack2;
};

template<typename T>
void myQueueWithStack<T>::enqueue(const T& element)
{
    stack1.push(element);
}

template<typename T>
T myQueueWithStack<T>::dequeue()
{
    if(stack2.size()<= 0)
    {
        while(stack1.size()>0)
        {
            T& data = stack1.top();
            stack1.pop();
            stack2.push(data);
        }
    }
    
    if(stack2.size() == 0)  //这时stack1里面也没有元素
        return INT_MIN;
    
    T head = stack2.top();
    stack2.pop();
    
    return head;
}


//problem: 知道先序排列的数组和中序排列的数组，重构/重建原二叉搜索树rebuild, buildtree.
//algorithm: 递归
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    template<typename Iter>
    TreeNode* make(Iter pFirst , Iter pLast , Iter iFirst , Iter iLast) {
        if(pFirst == pLast) return nullptr;
        if(iFirst == iLast) return nullptr;
        int val = *pFirst;
        auto iRoot = find(iFirst , iLast , val);
        TreeNode* root = new TreeNode(*iRoot);
        int leftSize = iRoot - iFirst;
        root -> left = make(pFirst+1 , pFirst+leftSize+1 , iFirst , iRoot);
        root -> right = make(pFirst+leftSize+1 , pLast , iRoot + 1 , iLast);
        return root;
    }
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        int size = inorder.size();
        if(size == 0) return nullptr;
        return make(preorder.begin() , preorder.end() , inorder.begin() , inorder.end());
    }
};



//编程之美上面的源代码
// 定义树的长度。为了后序调用实现的简单，我们直接用宏定义了树节点的总数
#define TREELEN 6
struct NODE
{
    NODE* pLeft;		// 左节点
    NODE* pRight;		// 右节点
    char chValue;		// 节点值
};

void ReBuild(char* pPreOrder,		//前序遍历结果
             char* pInOrder,			//中序遍历结果
             int nTreeLen,			//树长度
             NODE** pRoot)			//根节点
{
    
    //检查边界条件
    if(pPreOrder == NULL || pInOrder == NULL)
    {
        return;
    }
    
    // 获得前序遍历的第一个节点
    NODE* pTemp = new NODE;
    pTemp -> chValue = *pPreOrder;
    pTemp -> pLeft = NULL;
    pTemp -> pRight = NULL;
    
    // 如果节点为空，把当前节点复制到根节点
    if(*pRoot == NULL)
    {
        *pRoot = pTemp;
    }
    
    // 如果当前树长度为1，那么已经是最后一个节点
    if(nTreeLen == 1)
    {
        return;
    }
    
    // 寻找子树长度
    char* pOrgInOrder = pInOrder;
    char* pLeftEnd = pInOrder;
    int nTempLen = 0;
    
    // 找到左子树的结尾
    while(*pPreOrder != *pLeftEnd)
    {
        if(pPreOrder == NULL || pLeftEnd == NULL)
        {
            return;
        }
        
        nTempLen++;
        
        // 记录临时长度，以免溢出
        if(nTempLen > nTreeLen)
        {
            break;
        }
        
        pLeftEnd++;
    }
    
    // 寻找左子树长度
    int nLeftLen = 0;
    nLeftLen = (int)(pLeftEnd - pOrgInOrder);
    
    // 寻找右子树长度
    int nRightLen = 0;
    nRightLen = nTreeLen - nLeftLen - 1;
    
    // 重建左子树
    if(nLeftLen > 0)
    {
        ReBuild(pPreOrder + 1, pInOrder, nLeftLen, &((*pRoot) -> pLeft));
    }
    
    // 重建右子树
    if(nRightLen > 0)
    {
        ReBuild(pPreOrder + nLeftLen + 1, pInOrder + nLeftLen + 1,
                nRightLen, &((*pRoot) -> pRight)); 
    }
    
}

// 示例的调用代码
void rebuild_main(int argc, char* argv[])
{
    char szPreOrder[TREELEN]={'a', 'b', 'd', 'c', 'e', 'f'};
    char szInOrder[TREELEN]={'d', 'b', 'a', 'e', 'c', 'f'};
    
    NODE* pRoot = NULL;
    ReBuild(szPreOrder, szInOrder, TREELEN, &pRoot);
}


//problem:替换字符串中的空格为其他的字符
//algorithm:从后往前，依次移位，但是首先得确定最终替换后的字符的长度是多少
void ReplaceBlank(char string[], int length)///*length为字符串的最大值*/
{
    if(string == NULL && length <= 0)
        return;
    
    /*originalLength为字符串实际长度*/
    int originalLength = 0;
    int numberOfBlank = 0;
    int i = 0;
    while(string[i] != '\0')
    {
        ++ originalLength;
        
        if(string[i] == ' ')
            ++ numberOfBlank;
        
        ++ i;
    }
    
    /*newLength为空格被替换之后的新长度*/
    int newLength = originalLength + numberOfBlank * 2; //这有一个问题，没有加上末尾的'\0'下面的replace2和replace3才是对的
    if(newLength > length)
        return;
    
    int indexOfOriginal = originalLength - 1;
    int indexOfNew = newLength - 1;
    while(indexOfOriginal >= 0 &&  indexOfOriginal < indexOfNew)
    {
        if(string[indexOfOriginal] == ' ')
        {
            string[indexOfNew --] = '0';
            string[indexOfNew --] = '2';
            string[indexOfNew --] = '%';
        }
        else
        {
            string[indexOfNew --] = string[indexOfOriginal];
        }
        
        -- indexOfOriginal;
    }
}

char* replace2(char *c){
    if(c == NULL) return NULL;
    int len = strlen(c);
    if(len == 0) return NULL;
    int cnt = 0;
    for(int i=0; i<len; ++i)
    {
        if(c[i] == ' ')
            ++cnt;
    }
    char *cc = new char[len+2*cnt+1];   //这是重新建立了一个可以容纳连接到一起的数组
    int p = 0;
    for(int i=0; i<len; ++i)
    {
        if(c[i] == ' ')
        {
            cc[p] = '%';
            cc[p+1] = '2';
            cc[p+2] = '0';
            p += 3;
        }
        else
        {
            cc[p] = c[i];
            ++p;
        }
    }
    cc[p] = '\0';
    return cc;
}

void replace3(char *c){
    if(c == NULL) return;
    int len = strlen(c);
    if(len == 0) return;
    int cnt = 0;
    for(int i=0; i<len; ++i)
    {
        if(c[i] == ' ')
            ++cnt;
    }
    int p = len + 2*cnt;
    c[p--] = '\0';//the space must be allocated first.
    for(int i=len-1; i>=0; --i)
    {
        if(c[i] == ' ')
        {
            c[p] = '0';
            c[p-1] = '2';
            c[p-2] = '%';
            p -= 3;
        }
        else
        {
            c[p] = c[i];
            --p;
        }
    }
}




//problem: 二维数组中查找特定的数值 search matrix
//algorithm: 首先选举右上角的元素与target进行比较，如果大于target则该列被剔除
//如果小于target则该行被剔除，这样每一步都会缩小查找空间young matrix
//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
bool Find(int* matrix, int rows, int columns, int number)
{
    bool found = false;
    
    if(matrix != NULL && rows > 0 && columns > 0)
    {
        int row = 0;
        int column = columns - 1;
        while(row < rows && column >=0)
        {
            if(matrix[row * columns + column] == number)
            {
                found = true;
                break;
            }
            else if(matrix[row * columns + column] > number)
                -- column;
            else
                ++ row;
        }
    }
    
    return found;
}
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    
    int m = matrix.size();
    int n = matrix[0].size();
    int row = 0, col = n - 1;
    while ( row <= m-1 && col >= 0) {
        if (matrix[row][col] > target)
            col--;
        else if (matrix[row][col] < target)
            row++;
        else
            return true;
        
    }
    return false;
    
}

#define ROW 4
#define COL 4

bool YoungMatrix(int array[][COL], int Key){
    int i = 0, j = COL - 1;
    int var = array[i][j];
    while (true){
        if (var == Key)
            return true;
        else if (var < Key && i < ROW - 1)
            var = array[++i][j];
        else if (var > Key && j > 0)
            var = array[i][--j];
        else
            return false;
    }
}

/*测试用例
int matrix[][4] =
    {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
    FIND((int*)matrix, 4, 4, 7);
 */

//problem: count the specific number of given array
//algorithm: recursion
int counttarget;
void countNum(int a[],int start,int finish, int target){
    int middle=(start+finish)/2;
    if(start>finish)
        return ;
    if(a[middle]==target){
        counttarget++;
        countNum(a,start,middle-1, target);
        countNum(a,middle+1,finish, target);
        //cout<<"get here"<<middle<<endl
    }else if(a[middle]>target){
        countNum(a,start,middle-1, target);
    }else
    {
        countNum(a,middle+1,finish, target);
    }
}

//algorithm2: 迭代法，参考STL中的equal_range的实现
//然后两个相减
int getUpper(int arr[], int size, int key){//获取某个元素最后出现位
    int low = 0, high = size - 1;
    //其实是一个递归迭代
    while(low < high){
        int mid = (low + high + 1) / 2;
        if(arr[mid] <= key)
            //当要查找的值比中位数大于等于时，把查找的低位限制为mid
            low = mid;
        else
            //当要找的值比 中位数小时，，把查找的高位限制为mid-1
            high = mid - 1;
    }
    //    返回最后出现位置
    return low;
}
int getLower(int arr[], int size, int key){//获取某个元素第一次出现位置
    int low = 0, high = size - 1;
    while(low < high){
        int mid = (low + high) / 2;
        //当要找的值比中位数小于等于时，，把查找的高位限制为mid+1
        if(arr[mid] >= key)
            high = mid;
        else
            //当要找的值比 中位数大时，，把查找的低位限制为mid+1
            low = mid + 1;
    }
    //返回第一次出现位置
    return low;
}

//problem: memmove，对基本函数的了解
//algorithm: 注意memcpy和memmove的区别
void * my_memmove(void *destaddr, const void *sourceaddr, unsigned length)
{
    char *dest = (char*)destaddr;
    const char *source = (char*)sourceaddr;
    if (source < dest)
    /* Moving from low mem to hi mem; start at end.  */
        for (source += length, dest += length; length; --length)
            *--dest = *--source;
    else if (source != dest)
    /* Moving from hi mem to low mem; start at beginning.  */
        for (; length; --length)
            *dest++ = *source++;
                    
    return destaddr;
}

char* mymemmove(char *dst, const char* src, int cnt)
{
    assert(dst != NULL && src != NULL); //一定要有assert
    
    char *ret = dst;
    
    if (dst >= src && dst <= src+cnt-1) //内存重叠，从高地址开始复制
    {       //  srt.......dst.......src+cnt-1......dst+cnt-1
        dst = dst+cnt-1;
        src = src+cnt-1;
        while (cnt--)
            *dst-- = *src--;
    }
    else    //正常情况，从低地址开始复制
    {
        while (cnt--)
            *dst++ = *src++;
    }
    
    return ret;
}

char* mystrcpy(char *dst,const char *src)   //[1]
{
    assert(dst != NULL && src != NULL);    //[2]
    
    char *ret = dst;  //[3]         返回dst的原始值使函数能够支持链式表达式
    
    while ((*dst++ = *src++) != '\0'); //[4]
    
    return ret;
}

int mystrlen( const char *str ) //输入参数const
{
    　assert( str != NULL ); //断言字符串地址非0
    　int len = 0;
    　while( (*str++) != '\0' ) len++;
    　return len;
}

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
//最高效的肯定是KMP（看毛片算法）
void makeNext(const char str[],int next[])
//“部分匹配值”就是”前缀”和”后缀”的最长的共有元素的长度（不是倒过来）
{
    int m = strlen(str);
    next[0] = 0;
    int i = 0;      //两个指针一前一后
    for (int j = 1; j < m; ++j)
    {
        while(i > 0 && str[j] != str[i])
            i = next[i-1];      //就这一步不好理解
        if (str[j] == str[i])
        {
            i++;
        }
        next[j] = i;
    }
}

int kmp(const char text[], const char str[], int next[])
{
    int i = 0;
    int n = strlen(text);
    int m = strlen(str);
    makeNext(str, next);
    
    for (int j = 0; j < n; ++j )
    {          //移动位数 = 已匹配的字符数 – 对应的部分匹配值(已匹配字符最后一位的匹配值)
        while(i > 0 && text[j] != str[i])
            i = next[i-1];
        if (text[j] == str[i])
        {
            i++;
        }
        if (i == m)
        {
            printf("Pattern occurs with shift:%d\n",(j-m+1));
        }
    }
}




//problem: linkedlist sort mergelist listmerge
//algorithm: use merge sort to sort a linked list, with no extra space used

Node * merge2(Node * p1, Node * p2);
Node * mergeSort2(Node * p, int len);
int getLen(Node* head);

Node * linkedListMergeSort(Node * pHead) {
    int len = getLen(pHead);
    return mergeSort2(pHead, len);
}
int getLen(Node* head){
    int i = 0;
    while (head){
        head = head->next;
        i++;
    }
    return i;
}
Node * mergeSort2(Node * p, int len) {
    if (len == 1) { p->next = NULL; return p; }
    Node * pmid = p;
    for (int i=0; i<len/2; i++) {
        pmid = pmid->next; }
    Node * p1 = mergeSort2(p, len/2);
    Node * p2 = mergeSort2(pmid, len - len/2);
    return merge2(p1, p2);
}
//链表合并
Node *mergeListNonRecursively(Node *head1,Node *head2)
{
    if(head1 == NULL) //鲁棒性测试必须先行
        return head2;
    if(head2 == NULL)
        return head1;
    
    Node *p1 = NULL;
    Node *p2 = NULL;
    Node *head = NULL;
    
    //找出两个链表中第一个结点较小的结点，head记录较小结点的头结点
    if(head1->data < head2->data){
        head = head1;
        p1 = head1->next;
        p2 = head2;
    }
    else{
        head = head2;
        p2 = head2->next;
        p1 = head1;
    }
    
    Node *pcur = head;
    
    //在两个链表中遍历比较，将值较小的结点链接到pcur结点后
    while(p1 != NULL && p2 != NULL){
        if(p1->data <= p2->data){
            pcur->next = p1;
            pcur = p1;
            p1 = p1->next;
        }
        else
        {
            pcur->next = p2;
            pcur = p2;
            p2 = p2->next;
        }
    }
    //将p1或p2剩余的结点链到pcur之后，完成整个合并的过程
    if(p1 != NULL)
        pcur->next = p1;
    if(p2 != NULL)
        pcur->next = p2;
    
    return head;
}


//再用递归实现链表的merge
Node * mergelistRecursively(Node *head1, Node *head2)
{
    if(head1 == NULL)
        return head2;
    if(head2 == NULL)
        return head1;
    Node *head = NULL;
    if(head1->data < head2->data)
    {
        head = head1;
        head->next = Merge3(head1->next, head2);
    }
    else
    {
        head = head2;
        head->next = Merge3(head1, head2->next);
    }
    return head;
}

class Solution_merge2Lists {
public:
    
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == NULL)
            return l2;
        if (l2 == NULL)
            return l1;
        if (l1 == NULL && l2 == NULL)
            return NULL;
        
        ListNode dummy(-1);
        ListNode* head = &dummy;
        ListNode* p = l1, *q = l2;
        while (p != NULL || q != NULL){
            int val1 = (p == NULL) ? INT_MAX : p->val;
            int val2 = (q == NULL) ? INT_MAX : q->val;
            if (val1 < val2) {
                head->next = p;
                p = p->next;
            }
            else
            {
                head->next = q;
                q = q->next;
            }
            head = head->next;
            
        }
        return dummy.next;
    }
};

class Solution_mergeKlists {
public:
    bool operator< (ListNode* b) {
        return this->val > b->val;
    }
    
    ListNode* mergeKLists(vector<ListNode*> lists) {
        if (lists.size() == 0)
            return NULL;
        priority_queue<ListNode*> pq;
        for (int i = 0; i < lists.size(); i++) {
            if (lists[i] != NULL)
                pq.push(lists[i]);
        }
        ListNode* head = new ListNode(-1);
        head->next = NULL;
        ListNode* p = head;
        while (!pq.empty()) {
            auto tmp = pq.top();
            p->next = tmp;
            p = p->next;
            pq.pop();
            if (tmp->next != NULL)
                pq.push(tmp->next);
        }
        return head->next;
        delete head;
    }
};

//merge sorted list
void mergeSortedList(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    
    int i = m - 1;
    int j = n - 1;
    int k = m + n - 1;
    while (i >= 0 && j >= 0) {
        nums1[k--] = (nums1[i] >= nums2[j]) ? nums1[i--] : nums2[j--];
    }
    while (j >= 0)
        nums1[k--] = nums2[j--];
}



//problem: lowest common ancestor (LCA)
//algorithm:

//情况1：节点只有左指针、右指针，没有parent指针，root已知，不是二叉搜索树
TreeNode* lowestCommonAncestor(TreeNode* root , TreeNode* a , TreeNode* b)
{
    if(root == NULL)
        return NULL;
    if(root == a || root == b)
        return root;
    
    TreeNode* left =  lowestCommonAncestor(root->left , a , b);
    TreeNode* right = lowestCommonAncestor(root->right , a , b);
    
    if(left && right)
        return root;
    return left ? left : right;
    
}
//情况2：节点有左指针、右指针、还有parent指针，可以知道两个点肯定有交点
//可以转化为求两条链相交的最近点
//这里再提供一个思路
/*
 给定两个单链表(head1, head2),检测两个链表是否有交点,如果有返回第一个交点。
 如果 head1==head2,那么显然相交,直接返回 head1。
 否则,分别从 head1,head2 开始遍历两个链表获得其长度 len1 与 len2,
 假设 len1>=len2,那么指针 p1 由 head1 开始向后移动 len1-len2 步,指针 p2=head2,
 下面 p1、p2 每次向后前进一步并比较 p1、p2 是否相等,如果相等即返回该结点,
 否则说明两个链表没有交点。
 */

//情况3： 二叉树是个二叉查找树，且root和两个节点的值(a, b)已知
TreeNode* lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q) {
    int min, max;
    min = (p->val < q->val) ? p->val : q->val;
    max = (p->val < q->val) ? q->val : p->val;
    while(root) {
        if (root->val >= min && root->val <= max)
            return root;
        if (root->val < min)
            root = root->right;
        else
            root = root->left;
    }
    return NULL;
}



//problem: 把数组排成最小的数
//algorithm: 重新定义比较函数
/*
 字符串的比较函数需要重新定义，不是比较a和b，而是比较ab与 ba。如果ab < ba，则a < b；
 如果ab > ba，则a > b；如果ab = ba，则a = b。比较函数的定义是本解决方案的关键。
 为什么不能直接比较ab和ba的大小呢，因为把他们拼起来可能会超出int的表达范围，所以这是
 一个隐形的大数问题
 */
struct comparestr  //仿函数
{
    bool operator() (const string &src1, const string &src2)
    {
        string s1 = src1 + src2;
        string s2 = src2 + src1;
        return s1 < s2;   //升序排列，如果改为s1 > s2则为逆序排列
    }
};
//函数功能 ： 把数组排成最小的数
//函数参数 ： pArray为数组,num为数组元素个数
void ComArrayMin(int *pArray, int num){
    string *pStrArray = new string[num];
    for(int i=0; i<num; i++)
    {
        stringstream stream;
        stream<<pArray[i];
        stream>>pStrArray[i];
    }
    
    sort(pStrArray, pStrArray + num, comparestr()); //字符串数组排序

}
//剑指offer上的解答
const int g_MaxNumberLength = 10;

char* g_StrCombine1 = new char[g_MaxNumberLength * 2 + 1];
char* g_StrCombine2 = new char[g_MaxNumberLength * 2 + 1];

int compare(const void* strNumber1, const void* strNumber2);
void PrintMinNumber(int* numbers, int length)
{
    if(numbers == NULL || length <= 0)
        return;
    
    char** strNumbers = (char**)(new int[length]);
    for(int i = 0; i < length; ++i)
    {
        strNumbers[i] = new char[g_MaxNumberLength + 1];
        sprintf(strNumbers[i], "%d", numbers[i]);
    }
    
    qsort(strNumbers, length, sizeof(char*), compare);
    
    for(int i = 0; i < length; ++i)
        printf("%s", strNumbers[i]);
    printf("\n");
    
    for(int i = 0; i < length; ++i)
        delete[] strNumbers[i];
    delete[] strNumbers;
}
int compare(const void* strNumber1, const void* strNumber2)
{
    // [strNumber1][strNumber2]
    strcpy(g_StrCombine1, *(const char**)strNumber1);
    strcat(g_StrCombine1, *(const char**)strNumber2);
    
    // [strNumber2][strNumber1]
    strcpy(g_StrCombine2, *(const char**)strNumber2);
    strcat(g_StrCombine2, *(const char**)strNumber1);
    
    return strcmp(g_StrCombine1, g_StrCombine2);
}

//problem: 用递归法颠倒一个栈, stackreverse
//algorithm: recursion

// Add an element to the bottom of a stack:
template<typename T> void AddToStackBottom(stack<T>& stack, T t)
{
    if(stack.empty())
    {
        stack.push(t);
    }
    else
    {
        T top = stack.top();
        stack.pop();
        AddToStackBottom(stack, t);
        stack.push(top);
    }
}

// Reverse a stack recursively in three steps:
// 1. Pop the top element
// 2. Reverse the remaining stack
// 3. Add the top element to the bottom of the remaining stack
template<typename T> void ReverseStack(stack<T>& stack)
{
    if(!stack.empty())
    {
        T top = stack.top();
        stack.pop();
        ReverseStack(stack);
        AddToStackBottom(stack, top);
    }
}


//problem: split a interger
//algorithm: recursion递归调用
/*
 基本整数划分问题是将一个正整数n拆成一组数连加并等于n的形式，
 且这组数中的最大加数不大于m
 */
int integerSplit(int n, int m)
{
    if(n < 1 || m < 1) return 0;
    if(n == 1 || m == 1) return 1;
    if(n < m)
        return integerSplit(n, n);
    else if(n == m)
        return integerSplit(n, m - 1) + 1;
    else
        return integerSplit(n, m - 1) + integerSplit((n - m), m);
}
//problem: delete some specific chars in a string
//algorithm: hash + fast/slow pointers
void deleteChars(char* s, char* d){
    char * pTemp = d;
    char * pFast = s, *pSlow = s;
    int hashTable[256];
    memset(hashTable, 0, 256*sizeof(int));
    while ('\0' != *pTemp)
    {
        hashTable[*pTemp] = 1;
        pTemp++;
    }
    
    while ('\0' != *pFast)
    {
        if(!hashTable[*pFast])
        {
            *pSlow = *pFast;
            pSlow++;
        }
        ++pFast;
    }
    *pSlow = '\0';
    
}
//algorithm: 原始的方法
/* squeese: delete the string c in s */
void squeese(char s[], char c[])
{
    int i, j, k;
    
    for ( i = k = 0; s[i] != '\0'; i++)
    {
        for ( j = 0; c[j] != '\0' && s[i] != c[j]; j++)
            ;
        if ( c[j] == '\0')
            s[k++] = s[i];
    }
    s[k] = '\0';
    
}


//problem: 给定链表的头指针和一个结点指针，在O(1)时间删除该结点
//algorithm:
/*删除之前，我们需要需要把给定的结点的下一个结点的数据拷贝到给定的结点中。
 此时，时间复杂度为O(1)。如果删除的结点位于链表的尾部，没有下一个结点，仍然需要从链表
 的头结点开始，顺便遍历得到给定结点的前序结点，并完成删除操作。这个时候时间复杂度是O(n)。
 假设链表总共有n个结点，我们的算法在n-1总情况下时间复杂度是O(1)，
 只有当给定的结点处于链表末尾的时候，时间复杂度为O(n)。
 那么平均时间复杂度[(n-1)*O(1)+O(n)]/n，仍然为O(1)。
 */
//a->b->c->d..   //现在，给定了结点b，即要删除b
//a->c->d..
void DeleteNode(node* pListHead, node* pToBeDeleted)
{
    if(pToBeDeleted->next != NULL)   //要删除的结点b不是尾结点
    {
        //把b的下一个结点c先保存起来
        node* pNext = pToBeDeleted->next;   //pNext指着c
        
        pToBeDeleted->data = pNext->data;   //保存起来的c的值赋给b的值
        pToBeDeleted->next = pNext->next;   //d的值赋给c
        
        //最后，删除c。
        delete pNext;
        pNext = NULL;
    }
    else
    {
        //如果b是尾结点，找头结点，只能依次遍历 找b结点了
        node* pNode = pListHead;
        while(pNode->next != pToBeDeleted)
        {
            pNode = pNode->next;
        }
        //删除c。
        pNode->next = NULL;
        delete pToBeDeleted;
        pToBeDeleted = NULL;
    }
}


//problem:
/*
1. 看到这道题后，第一反应是从头到尾输出比较简单。于是很自然地想到把链表中链接结点的指针反转过来，改变链表的方向。然后就可以从头到尾输出了。反转链表的算法详见此微软100题系列第24题。
2.接下来的想法是从头到尾遍历链表，每经过一个结点的时候，把该结点放到一个栈中。当遍历完整个链表
 后，再从栈顶开始输出结点的值，此时输出的结点的顺序已经反转过来了。该方法需要维护一个额外的栈，
 现起来比较麻烦。
3. 既然想到了栈来实现这个函数，而递归本质上就是一个栈结构。于是很自然的又想到了用递归来实现。要实现反过来输出链表，我们每访问到一个结点的时候，先递归输出它后面的结点，再输出该结点自身，这样链表的输出结果就反过来了
 */
void PrintListReversingly_Iteratively(node* pHead){
    std::stack<node*> nodes; //直接把指针压入栈中，免得压数据费时费空间
    node* pNode = pHead;
    while(pNode != NULL)
    {
        nodes.push(pNode);
        pNode = pNode->next;
    }
    
    while(!nodes.empty())
    {
        pNode = nodes.top();
        printf("%d\t", pNode->data);
        nodes.pop();
    }
}
//其实当链表特别长时，应该采用栈，这样可以避免可能发生栈溢出
void PrintListReversingly(node* pListHead)
{
    if(pListHead != NULL){
        if (pListHead->next != NULL){
            PrintListReversingly(pListHead->next);
        }
        printf("%d", pListHead->data);
    }
}
//以上思路用来求字符串的长度
int getLen(char *str){
    if (*str == '\0')
        return 0;
    return getLen(str + 1) + 1;
}

//
//problem： 将数组中奇数都放在数组的前面，偶数都放在数组的后面
//algorithm: 类似于quicksort的partition，以下建立一个模板，可以把数组分成满足不同标准的函数指针
void evenOddPartition(int A[], int n) { //这里就没有pivot的概念了不需要
    if (n == 0 || n == 1)
        return;
    int i = 0, j = n - 1;
    while (i < j) {
        while ((i < j) && ((A[i] & 1) == 1)) //判断一个数字是不是偶数并没有用%运算符而是用&。理由是通常情况下位运算符比%要快一些；
                i++;
        while ((i < j) && ((A[j] & 1) == 0))
                j--;
        if (i < j)  //最好还是再加上一个判断
            swap(A[i], A[j]);
        i++;
        j--;
    }
}
/*
 Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.
 
 Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.
 */
//这也是用了partition的思想，用三个指针，只需要扫描一次就能将0-2的一串指数进行排序，如果是二进制的话就变成了partition，需要两个指针

//快排其实有两种不同的思路，一种思路是两个指针都是从头开始往后扫描，而另一种思路是一个指针往后扫，一个指针往前扫。
void sortColors(int A[], int n) {
    int i = -1;
    int j = -1;
    int k = -1;
    for(int p = 0; p < n; p ++)
    {
        //根据第i个数字，挪动0~i-1串。
        if(A[p] == 0)
        {
            A[++k] = 2;    //2往后挪
            A[++j] = 1;    //1往后挪
            A[++i] = 0;    //0往后挪
        }
        else if(A[p] == 1)
        {
            A[++k] = 2;
            A[++j] = 1;
        }
        else
            A[++k] = 2;
    }
    
}


//algorithm: 利用函数指针，提高扩展性，只要是把
void Reorder(int *pData, unsigned int length, bool (*func)(int));
bool isEven(int n);

void ReorderOddEven_2(int *pData, unsigned int length)
{
    Reorder(pData, length, isEven); //利用函数指针
}

void Reorder(int *pData, unsigned int length, bool (*func)(int))
{
    if(pData == NULL || length == 0)
        return;
    
    int *pBegin = pData;
    int *pEnd = pData + length - 1;
    
    while(pBegin < pEnd)
    {
        // 满足标准
        while(pBegin < pEnd && !func(*pBegin))
            pBegin ++;
        
        // 不满足标准
        while(pBegin < pEnd && func(*pEnd))
            pEnd --;
        
        if(pBegin < pEnd) //swap(*pBegin, *pEnd);加一层判断更保险
        {
            int temp = *pBegin;
            *pBegin = *pEnd;
            *pEnd = temp;
        }
    }
}

bool isEven(int n)
{
    return (n & 1) == 0;
}


//problem: find consecutive sequence whose sum equals to n
//algorithm: recursive，思想和2sum中前后指针的思想一致，都是若大于sum，则small变化（这里是small加，因为求得是small到big之间的连加），若小于sum，则big加
void PrintContinuousSequence(int small, int big);
// Find continuous sequence, whose sum is n
void FindContinuousSequence(int n)
{
    if(n < 3)
        return;
    
    int small = 1;
    int big = 2;
    int middle = (1 + n) / 2;
    int sum = small + big;
    while(small < middle)
    {
        // we are lucky and find the sequence
        if(sum == n)
            PrintContinuousSequence(small, big);
        // if the current sum is greater than n,
        // move small forward
        while(sum > n)
        {
            sum -= small;   //避免了重新计算之和，只需减掉小端值就可以了
            small ++;
            // we are lucky and find the sequence
            if(sum == n)
                PrintContinuousSequence(small, big);
        }
        // move big forward
        big ++;
        sum += big;   //只需加上大端值就可以了
    }
}
// Print continuous sequence between small and big
void PrintContinuousSequence(int small, int big)
{
    for(int i = small; i <= big; ++ i)
        printf("%d ", i);
    printf("/n");
}

//problem: use a trie to search for
//algorithm:

class TrieNode {
public:
    bool isWord;
    TrieNode* hash[26];
    char c;
    TrieNode(){}
    TrieNode(char c_) {
        c = c_;
        isWord = false;
        for (int i = 0; i < 26; i ++) {
            hash[i] = NULL;
        }
    }
};

class WordDictionary {
public:
    WordDictionary() {
        root = new TrieNode;
        for (int i = 0; i < 26; i ++) {
            root->hash[i] = NULL;
        }
    }

    // Adds a word into the data structure.
    void addWord(string word) {
        TrieNode* p = root;
        for (int i = 0; i < word.size(); i ++)
        {
            char tmp = word[i];
            if (p->hash[tmp-'a'] == NULL) {
                TrieNode* tnew = new TrieNode(tmp);
                p->hash[tmp-'a'] = tnew;
            }
            p = p->hash[tmp-'a'];
        }
        p->isWord = true;
    }
    
    // Returns if the word is in the data structure. A word could
    // contain the dot character '.' to represent any one letter.
    bool search(string word) {
        return search(word, 0, (int)word.size(), root);
    }
    
    bool search(string word, int pos, int n, TrieNode* cur) {
        if (cur == NULL)
            return false;
        if (pos == n)
            return cur->isWord;
        if (word[pos] == '.') {
            for (int i = 0; i < 26; i++) {
                if (cur->hash[i] && search(word, pos+1, n, cur->hash[i]))
                    return true;
            }
        }else {
            if (cur->hash[word[pos] - 'a'] && search(word, pos+1, n, cur->hash[word[pos] - 'a']))
                return true;
        }
        return false;
    }
    
private:
    TrieNode* root;
    
};

//problem: implement a trie
//algorithm:
/*
 这题实质是实现一颗多叉树（分支因子26）的插入和查找操作。定义每个TrieNode保存char c，保存一个HashMap用于储存所有的孩子节点，key是对应的字符，value是孩子节点，定义flag hasWord来标记这个node上是否存在word。对于插入操作，直接从上向下分层扫描树，如果没有对应字符节点存在就新建节点，如果有就去相应路径向下探察。对于查询操作，前缀树的定义可以保证当我们从前向后扫描字符串时候，每一个字符都可以从上到下对应前缀树的每一层，所以扫描过程中如果有任何一个字符不存在于当前层中，就可以立刻停止查找返回null，也就是不存在这样的word或者前缀，否则继续从对应的分支向下探察。时间复杂度是O（L），L是树的高度，也就是最长word的长度，空间复杂度26^L，每一层分支因子26，有L层
 */
class TrieNode2 {
public:
    TrieNode2 *next[26];
    bool isString;
    // Initialize your data structure here.
    TrieNode2() {
        for(int i = 0; i < 26; i++)
            next[i] = NULL;
        isString = false;
    }
};

class Trie2 {
public:
    Trie2() {
        root = new TrieNode2();
        
    }
    //这会有严重的错误，没有析构函数，整棵树没有析构函数，下一个实现将实现析构的函数
    
    // Inserts a word into the trie.
    void insert(string s) {
        TrieNode2 *p = root;
        for(int i = 0; i < s.size(); i++){
            if(p->next[s[i]-'a'] == NULL){
                p->next[s[i]-'a'] = new TrieNode2();
            }
            p = p->next[s[i]-'a'];
        }
        p->isString = true;
    }
    
    // Returns if the word is in the trie.
    bool search(string key) {
        TrieNode2 *p = root;
        for(int i = 0; i < key.size(); i++){
            if(p == NULL) return false;
            p = p->next[key[i]-'a'];
        }
        if(p == NULL || p->isString == false) return false;
        return true;
        
    }
    
    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode2 *p = root;
        for(int i = 0; i <= prefix.size(); i++){
            if(p == NULL) return false;
            p = p->next[prefix[i]-'a'];
        }
        return true;
    }
    
private:
    TrieNode2* root;
};
// Your Trie object will be instantiated and called as such:
// Trie trie = new Trie();
// trie.insert("somestring");
// trie.search("key");

//以上实现的trie树没有考虑树的析构问题，但这里还有两个问题，复制拷贝函数和赋值构造函数都需要重载，不然调用的是编译器自动给trie2类加上的
namespace trie2 {
    

const int MaxBranchNum = 26;//如果区分大小写，可以扩展到52

/*定义trie树结点*/
class TrieNode
{
public:
    char* word; //节点表示的单词
    int count;  //单词出现的次数
    TrieNode* nextBranch[MaxBranchNum];//指向26个字符节点的指针
public:
    TrieNode() : word(NULL),count(0)
    {
        memset(nextBranch,NULL,sizeof(TrieNode*) * MaxBranchNum);
    }
};

/*定义类Trie*/
class Trie
{
public:
    Trie();
    ~Trie();
    void Insert(const char* str);//插入字符串str
    bool Search(const char* str,int& count);//查找字符串str，并返回出现的次数
    bool Remove(const char* str);//删除字符串str
    void PrintALL();//打印trie树中所有的结点
    void PrintPre(const char* str);//打印以str为前缀的单词
private:
    TrieNode* pRoot;
private:
    void Destory(TrieNode* pRoot);
    void Print(TrieNode* pRoot);
};

#endif //_TRIE_

Trie::Trie()
{
    pRoot = new TrieNode();//注意字典树的根不存放字符
}

Trie::~Trie()
{
    Destory(pRoot); //这个特别特别重要，不是有三原则嘛？这里还有一个问题，怎么防治浅拷贝
}

/*插入一个单词*/
void Trie::Insert(const char* str)
{
    assert(NULL != str);
    int index;
    TrieNode* pLoc = pRoot;
    for (int i = 0;str[i];i++)
    {
        index = str[i] - 'a';//如果区分大小写，可以扩展
        
        if(index < 0 || index > MaxBranchNum)//不执行插入
        {
            return;
        }
        
        if (NULL == pLoc->nextBranch[index])//该单词的前缀不存在，要生成该结点
        {
            pLoc->nextBranch[index] = new TrieNode();
        }
        pLoc = pLoc->nextBranch[index];
    }
    if (NULL != pLoc->word)//单词已经出现过
    {
        pLoc->count++;
        return;
    }
    else    //单词没有出现过，应该插入单词
    {
        pLoc->count++;
        pLoc->word = new char[strlen(str) + 1];
        assert(NULL != pLoc->word);
        strcpy(pLoc->word,str);
    }
}

/*查找一个单词，如果存在该单词，则返回其出现次数*/
bool Trie::Search(const char* str,int& count)
{
    assert(str != NULL);
    int i = 0;
    int index = -1;;
    TrieNode* pLoc = pRoot;
    while(pLoc && *str)
    {
        index = *str - 'a';//如果区分大小写，可以扩展
        
        if(index < 0 || index > MaxBranchNum)//不是一个单词，不执行插入
        {
            return false;
        }
        
        pLoc = pLoc->nextBranch[index];
        str++;
    }
    if (pLoc && pLoc->word)//条件成立，找到该单词
    {
        count = pLoc->count;
        return true;
    }
    return false;
}

bool Trie::Remove(const char* str)
{
    assert(NULL != str);
    int index = -1;;
    TrieNode* pLoc = pRoot;
    while(pLoc && *str)
    {
        index = *str - 'a';//如果区分大小写，可以扩展
        
        if(index < 0 || index > MaxBranchNum)//不是一个单词，不执行插入
        {
            return false;
        }
        
        pLoc = pLoc->nextBranch[index];
        str++;
    }
    if (pLoc && pLoc-> word)//条件成立，找到该单词
    {
        delete[] pLoc->word;
        pLoc->word = NULL;
        return true;
    }
    return false;
}

void Trie::PrintALL()
{
    Print(pRoot);
}

void Trie::PrintPre(const char* str)
{
    assert(str != NULL);
    int i = 0;
    int index = -1;;
    TrieNode* pLoc = pRoot;
    while(pLoc && *str)
    {
        index = *str - 'a';//如果区分大小写，可以扩展
        
        if(index < 0 || index > MaxBranchNum)//不是一个单词，不执行插入
        {
            return;
        }
        
        pLoc = pLoc->nextBranch[index];
        str++;
    }
    if (pLoc)//条件成立，找到该单词
    {
        Print(pLoc);
    }
}

/*按照字典顺序输出以pRoot为根的所有的单词*/
void Trie::Print(TrieNode* pRoot)
{
    if (NULL == pRoot)
    {
        return;
    }
    //输出单词
    if (NULL != pRoot->word)
    {
        cout<<pRoot->word<<" "<<pRoot->count<<endl;
    }
    //递归处理分支
    for (int i = 0;i < MaxBranchNum;i++)
    {
        Print(pRoot->nextBranch[i]);
    }
}

/*销毁trie树*/
void Trie::Destory(TrieNode* pRoot)
{
    if (NULL == pRoot)
    {
        return;
    }
    for (int i = 0;i < MaxBranchNum;i++)
    {
        Destory(pRoot->nextBranch[i]);
    }
    //销毁单词占得空间
    if (NULL != pRoot->word)
    {
        delete []pRoot->word;
        pRoot->word = NULL;
    }
    delete pRoot;//销毁结点
    pRoot = NULL;
}

int main_trie()
{
    Trie t;
    string str;
    int count = -1;
    ifstream in("word.txt");
    //把单词输入字典树
    while(in >> str)
    {
        transform(str.begin(),str.end(),str.begin(),tolower);//大写变小写
        t.Insert(str.c_str());
    }
    //查找
    bool isFind = t.Search("the",count);
    if (isFind)
    {
        cout<<"存在the,出现次数："<<count<<endl;
    }
    else
    {
        cout<<"不存在the!"<<endl;
    }
    //输出
    t.PrintALL();
    //删除
    bool isDel = t.Remove("the");
    if (isDel)
    {
        cout<<"删除成功!"<<endl;
    }
    else
    {
        cout<<"删除失败!"<<endl;
    }
    //输出以w开头的单词
    t.PrintPre("w");
    cout<<endl;
    system("pause");
}

}//end of trie

//利用trie来统计词频

//功能：统计一段英文的单词频率(文章以空格分隔，没有标点)
//思路：trie节点保存单词频率，然后通过DFS按字典序输出词频
//时空复杂度: O(n*len)(len为单词平均长度)
//copyright@yansha 2011.10.25
//updated@July 2011.10.26
//程序尚不完善，有很多地方还需改进。
#define num_of_letters 26
#define max_word_length 20

// 定义trie树节点
struct Trie
{
    int count;
    Trie *next[num_of_letters];
};

// 定义根节点
Trie *root = NULL;

/**
 * 建立trie树，同时保存单词频率
 */
void create_trie(char *word)
{
    int len = strlen(word);
    Trie *cur = root, *node;
    int pos = 0;
    
    // 深度为单词长度
    for(int i = 0; i < len; ++i)
    {
        // 将字母范围映射到0-25之间
        pos = word[i] - 'a';
        
        // 如果当前字母没有对应的trie树节点则建立，否则处理下一个字母
        if(cur->next[pos] == NULL)   //1、这里应该有个查找过程
        {
            node = (Trie *)malloc(sizeof(Trie));
            node->count = 0;
            
            // 初始化next节点
            for(int j = 0; j < num_of_letters; ++j)
                node->next[j] = NULL;
            
            // 开始处理下一个字母
            cur->next[pos] = node;
        }
        cur = cur->next[pos];
    }
    // 单词频率加1
    cur->count++;
}

/**
 * 大写字母转化成小写字母
 */
void upper_to_lower(char *word, int len)
{
    for (int i = 0; i < len; ++i)
    {
        if(word[i] >= 'A' && word[i] <= 'Z')
            word[i] += 32;              //大写字母的ascll码在前
    }
}

/**
 * 处理输入
 */
void process_input()
{
    char word[max_word_length];
    
    // 打开统计文件(注意保持文件名一致)
    FILE *fp_passage = fopen("passage.txt", "r");
    assert(fp_passage);
    
    // 循环处理单词
    while (fscanf(fp_passage, "%s", word) != EOF)
    {
        int len = strlen(word);
        if (len > 0)
            upper_to_lower(word, len);
        create_trie(word);
    }
    fclose(fp_passage);
}

/**
 * 深度优先遍历
 */
void trie_dfs(Trie *p, char *queue)
{
    for(int i = 0; i < num_of_letters; ++i)
    {
        if(p->next[i] != NULL)
        {
            // 定义队列头结点
            char *head = queue;
            
            // 在末尾增加一个字母
            while (*queue != '\0')
                queue++;
            *queue = (char)(i + 'a');
            queue = head;
            
            // 在控制台打印单词及其频率
            if (p->next[i]->count > 0)
                printf("%s\t%d\n", queue, p->next[i]->count);
            
            trie_dfs(p->next[i], queue);
            
            // 在末尾去掉一个字母
            head = queue;
            while (*(queue+1) != '\0')
                queue++;
            *queue = '\0';
            queue = head;
        }
    }
}
int main_trie()
{
    // 初始化trie树根节点
    root = (Trie *)malloc(sizeof(Trie));
    for(int j = 0; j < num_of_letters; ++j)
        root->next[j] = NULL;
    
    // 处理输入
    process_input();
    
    // 分配一个保存单词中间结果的队列
    char *queue = (char*) calloc(max_word_length, sizeof(char));
    
    // 通过DFS打印结果
    trie_dfs(root, queue);
    system("pause");
    return 0;
}



//问题：在从1到n的正数中1出现的次数，编程之美
//题目：输入一个整数n，求从1到n这n个整数的十进制表示中1出现的次数。
//算法：
//最简单的，每次判断整数的个位数字是不是1。如果这个数字大于10，除以10之后再判断个位数字是不是1
int num1s(int n)
{
    int count = 0;//统计变量
    int factor = 1;//分解因子
    int lower = 0;//当前处理位的所有低位
    int higher = 0;//当前处理位的所有高位
    int curr =0;//当前处理位
    
    while(n/factor != 0)
    {
        lower = n - n/factor*factor;//求得低位
        curr = (n/factor)%10;//求当前位
        higher = n/(factor*10);//求高位
        
        switch(curr)
        {
            case 0:
                count += higher * factor;
                break;
            case 1:
                count += higher * factor + lower + 1;
                break;
            default:
                count += (higher+1)*factor;
        }
        
        factor *= 10;
    }
    
    return count;
}


//问题：栈混洗
//算法：利用辅助栈，将效率降低到O(n)
bool IsPossiblePopOrder(const int* pPush, const int* pPop, int nLength)
{
    bool bPossible = false;
    
    if(!pPush || !pPop || nLength <= 0)
        return bPossible;
    
    const int *pNextPush = pPush;
    const int *pNextPop = pPop;
    
    // ancillary stack
    std::stack<int> stackData;
    
    // check every integers in pPop
    while(pNextPop - pPop < nLength)
    {
        while(stackData.empty() || stackData.top() != *pNextPop){

            if (pNextPush - pPush == nLength)
                break;
            stackData.push(*pNextPush);
            pNextPush ++;

        }
        
        if(stackData.top() != *pNextPop)
            break;
        
        // Check the next integer in pPop
        stackData.pop();
        pNextPop ++;
    }
    
    if(stackData.empty() && pNextPop - pPop == nLength)
        bPossible = true;
    
    return bPossible;
}
//这是用数组的形式来处理的，以上使用指针，本质上没有区别
bool isPopSeries(int push[], int pop[], int n) {
    bool bPossible = false;
    stack<int> helper;
    int i1 = 0, i2 = 0;
    while (i2 < n) {
        while (helper.empty() || helper.top() != pop[i2]) {
            if (i1 < n)
                helper.push(push[i1++]);
            else
                break;
            
            if (!helper.empty() && helper.top() == pop[i2]) {
                helper.pop(); i2++; }
        }
    }
    if (helper.empty() && i2 == n)
        bPossible = true;
    return bPossible;
}
//算法2：利用栈混洗的充要条件，算法复杂度是O(n^2)
/*
 充要条件(Knuth):
 A permutation is a stack permutation iff 
 it does NOT involve the permutation 312:
 对于任意i < j,不含模式{ ..., j+1, ..., i, ..., j, ...}
 */


//问题：其实也叫hanmming_weight
/*
题目：输入一个整数，求该整数的二进制表达中有多少个1。
例如输入10，由于其二进制表示为1010，有两个1，因此输出2。
一个很基本的想法是，我们先判断整数的最右边一位是不是1。
接着把整数右移一位，原来处于右边第二位的数字现在被移到第一位了，
再判断是不是1。这样每次移动一位，直到这个整数变成0为止。
现在的问题变成怎样判断一个整数的最右边一位是不是1了。
很简单，如果它和整数1作与运算。由于1除了最右边一位以外，其他所有位都为0。
因此如果与运算的结果为1，表示整数的最右边一位是1，否则是0。得到的代码如下：
*/
//算法：
///////////////////////////////////////////////////////////////////////
// Get how many 1s in an integer's binary expression
///////////////////////////////////////////////////////////////////////
int NumberOf1_Solution1(int i)
{
    int count = 0;
    while(i)
    {
        if(i & 1)
            count ++;
        
        i = i >> 1;
    }
    
    return count;
}

//算法2：解决以上算法的bug
/*
这个思路当输入i是正数时没有问题，但当输入的i是一个负数时，
不但不能得到正确的1的个数，还将导致死循环。
以负数0x80000000为例，右移一位的时候，并不是简单地把最高位的1移到第二位变成0x40000000，
而是0xC0000000。这是因为移位前是个负数，仍然要保证移位后是个负数，因此移位后的最高位会设为1。
如果一直做右移运算，最终这个数字就会变成0xFFFFFFFF而陷入死循环。
为了避免死循环，我们可以不右移输入的数字i。
首先i和1做与运算，判断i的最低位是不是为1。
接着把1左移一位得到2，再和i做与运算，就能判断i的次高位是不是1……
这样反复左移，每次都能判断i的其中一位是不是1。基于此，我们得到如下代码：
*/
int NumberOf1_Solution2(int i){
    int count = 0;
    unsigned int flag = 1;
    while(flag){
        if(i & flag)
            count ++;
        
        flag = flag << 1;
    }
    
    return count;
}
//算法3：把一个整数减去1再与原来的整数做位与运算得到的是把整数的二进制表示中最右边一个1变成0
 int NumberOf1_Solution3(int i){
     int count = 0;
     while (i){
         ++ count;
         i = (i - 1) & i;
     }
     return count;
 }
//扩展：如何用一个语句判断一个整数是不是二的整数次幂？
//PS：n&(n-1)==0;//二进制数只有一位位1，则该数是2的整数次幂.
//扩展2：判断两个整数，计算改变m的二进制表示中多少为才能得到n

inline int changeNbits(int m, int n) {
    return NumberOf1_Solution3(m ^ n);
}

//算法4：wikipedia
int NumberOf1_Solution_Wikipedia(int n) //分治法
{
    n = (n&0x55555555) + ((n>>1)&0x55555555);
    n = (n&0x33333333) + ((n>>2)&0x33333333);
    n = (n&0x0f0f0f0f) + ((n>>4)&0x0f0f0f0f);
    n = (n&0x00ff00ff) + ((n>>8)&0x00ff00ff);
    n = (n&0x0000ffff) + ((n>>16)&0x0000ffff);
    return n;
}


//问题：
/*
写一个函数,它的原形是int continumax(char *outputstr,char *intputstr)
功能：
在字符串中找出连续最长的数字串，并把这个串的长度返回，
并把这个最长数字串付给其中一个函数参数outputstr所指内存。
例如："abcd12345ed125ss123456789"的首地址传给intputstr后，函数将返回9，
outputstr所指的值为123456789
*/
//leeyunce
//算法：跟在序列中求最小值差不多
int continumax(char *outputstr, char *intputstr)
{
    int i, maxlen = 0;
    char * maxstr = 0;
    
    while (true)
    {
        while (intputstr && (*intputstr<'0' || *intputstr>'9'))
            //skip all non-digit characters
        {
            intputstr++;
        }
        
        if (!intputstr) break;
        
        int count = 0;
        char * tempstr = intputstr;
        while (intputstr && (*intputstr >= '0' && *intputstr <= '9'))
            //OK, these characters are digits
        {
            count++;
            intputstr++;
        }
        
        if (count > maxlen)
        {
            maxlen = count;
            maxstr = tempstr;
        }
    }
    
    for (i=0; i<maxlen; i++)
    {
        outputstr[i] = maxstr[i];
    }
    
    outputstr[i] = '\0';
    
    return maxlen;
}


//问题：剑指offer，不用加减乘除做加法
//算法：用位计算（add2和add3递归改迭代的方式）
int Add2(int a, int b){
    if(b == 0)
        return a;
    int sum = a ^ b; // 各位相加，不计进位
    int carry = (a & b) << 1; // 记下进位
    return Add2(sum, carry); // 求sum和carry的和
}
int Add3(int a, int b){
    while(b != 0){      //迭代该递归的典型案例
        int sum = a ^ b;
        int carry = (a & b) << 1;
        a = sum;
        b = carry;
    }
    return a;
}

//用加法做乘除法
//想一想用只用加法怎么实现乘除还有减法，注意减法不能乘以-1，这道题在现实中肯定遇不到，但是可以锻炼人的逻辑思维能力
//不用判断语句，做比较

class Max {
public:
    int getMax(int a, int b) {
        // write code here
        int c = a - b;              //这里有一个缺陷是没有检验这里是不是有可能溢出
        int k = (c >> 31 & 0x01) ^ 1;
        int q = k ^ 1;
        return a * k +  b * q;
    }
};


//问题：输入两个整数 m 和 n，从数列1，2，3.......n 中 随意取几个数,
//使其和等于 m ,要求将其中所有的可能组合列出来
//算法：0/1背包问题的思路
list<int> list1;//需要维护一个全局的链表，不能用栈，因为这里需要遍历其元素
void find_factor(int sum, int n)
{
    // 递归出口
    if(n <= 0 || sum <= 0)
        return;
    
    // 输出找到的结果
    if(sum == n)
    {
        // 反转list
        list1.reverse();
        for(list<int>::iterator iter = list1.begin(); iter != list1.end(); iter++)
            cout << *iter << " + ";
        cout << n << endl;
        list1.reverse();
    }
    
    list1.push_front(n);      //典型的01背包问题
    find_factor(sum-n, n-1);   //放n，n-1个数填满sum-n
    list1.pop_front();
    find_factor(sum, n-1);     //不放n，n-1个数填满sum
}


//问题：将整数n转换为字符串并保存到s中
//算法：itoa
void itoa(int n, char s[]) {
    int i, sign;
    if ( (sign = n) < 0)
        n = -n; //这里可能会出现bug,不能处理最大的负数
    i = 0;
    do {
        s[i++] = n%10 + '0';
    }while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s, s+strlen(s));
}
void itoa2(int n, char s[]) {
    int i, sign;
    sign = n; //此处
    i = 0;
    do {
        s[i++] = abs ( n % 10 )+ '0'; //此处
    }while ((n /= 10) != 0); //此处
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s, s+strlen(s));
}
//算法2：处理以上算法的bug，不能处理最大的负数

//问题：将字符串转换为整数保存在s中，这种方法可以用来处理大整数，将大整数存储在字符串中
//算法：atoi，标准库里面的函数，一般用于将函数的参数（字符串）转换为整数
int  myatoi(char s[]) {
    int num = (int) strlen(s);
    if (num == 0) return 0;
    int sign = 1;
    int i, sum = 0;
    if (s[0] == '-') {
        sign = -1;
        i++;
    }else if (s[0] == '+')
        i++;
    
    for (; i < num; i++) {
        if (!isdigit(s[i])) {
            printf("Invalid numbers");
            exit(-1);
        }
        sum = sum * 10 + (s[i] - '0');
        // overflow
        if(sum > std::numeric_limits<int>::max())
        {
            sum = 0;
            return 0;
        }
    }
    return sum * sign;
}

int my_atoi(const char * a) {       //有一个问题是没有考虑溢出
    
    if (*a == '+')
        return atoi(a+1);
    else if (*a=='-')
        return - atoi(a+1);
    
    const char *p = a;
    int c = 0;
    while (*p >= '0' && *p <= '9') {
        c = c*10 + (*p - '0'); }
    return c;
}

double my_atof(char s[])
{
    double val, power;
    int i, sign;
    
    for ( i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-' ? -1 : 1);
    if ( s[i] == '-' || s[i] == '+')
        i++;
    
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');    //提取整数部分
    if ( s[i] == '.')
        i++;
    
    for ( power = 1.0; isdigit(s[i]); i++)  //提取小数部分
    {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;                      //记录小数的位数，方便之后移位
    }
    
    return sign * val / power;
}

//problem:
/* htoi: convert hexadecimal string to integer */
/*eg 0X0811ABc3 */
#define YES  1
#define NO   0

int htoi(char s[])
{
    int hexdigit = 0, i, index, n;
    
    i = 0;
    if (s[i] == '0')
    {
        ++i;
        if (s[i] == 'x' || s[i] == 'X')
            ++i;
    }
    
    n = 0;
    index = YES;
    for ( ; index == YES; ++i)
    {
        if (s[i] >= '0' && s[i] <= '9')
            hexdigit = s[i] - '0';
        else if (s[i] >= 'a' && s[i] <= 'f')
            hexdigit = s[i] - 'a' + 10;
        else if (s[i] >= 'A' && s[i] <= 'F')
            hexdigit = s[i] - 'A' + 10;
        else
            index = NO;
        if (index == YES)
            n = 16 * n + hexdigit;
    }
    return n;
}

//July、2010、10/22。
enum Status {kValid = 0, kInvalid};
int g_nStatus = kValid;
int StrToInt(const char* str)
{
    g_nStatus = kInvalid;
    long long num = 0;
    
    if(str != NULL)
    {
        const char* digit = str;
        
        // the first char in the string maybe '+' or '-'
        bool minus = false;
        if(*digit == '+')
            digit ++;
        else if(*digit == '-')
        {
            digit ++;
            minus = true;
        }
        
        // the remaining chars in the string
        while (*digit != '\0')
        {
            if (isdigit(*digit))
            {
                num = num * 10 + (*digit - '0');
                
                // overflow
                if(num > std::numeric_limits<int>::max())
                {
                    num = 0;
                    break;
                }
                
                digit ++;
            }
            // if the char is not a digit, invalid input
            else
            {
                num = 0;
                break;
            }
        }
        
        if(*digit == '\0')
        {
            g_nStatus = kValid;
            if(minus)
                num = 0 - num;
        }
    }
    return static_cast<int>(num);
}

//问题：快速计算裴波那契数列
//算法：这个可以用来实现fibollic数列的logn算法，并且利用quickPower的思想
void multiply(int A[], int B[], int* _r);
void powerMatrix(int A[], int n, int* _r);
int f(int n) {
    int A[4] = {1,1,1,0};
    int result[4];
    powerMatrix(A, n, result);
    return result[0];
}

void multiply(int A[], int B[], int* _r) {
    _r[0] = A[0]*B[0] + A[1]*B[2];
    _r[1] = A[0]*B[1] + A[1]*B[3];
    _r[2] = A[2]*B[0] + A[3]*B[2];
    _r[3] = A[2]*B[1] + A[3]*B[3];
}

void powerMatrix(int A[], int n, int* _r) {
    if (n==1) { memcpy(A, _r, 4*sizeof(int)); return; }
    int tmp[4];
    powerMatrix(A, n>>1, _r);
    multiply(_r, _r, tmp);
    if ((n & 1) == 1) {
        multiply(tmp, A, _r);
    } else {
        memcpy(_r, tmp, 4*sizeof(int));
    }
}

//一般做法：fib
int fibllic(int n)  {
    int a = 7;      //初始值都可以自己确定
    int b = 11;
    
    if (n == 1) return a;
    if (n == 2) return b;
    
    for (int i = 2; i < n; i++) {
        b = a + b;
        a = b - a;
    }
    return b;
}

int fibllic(int n, int n0, int n1)  {
    int a = n0;      //初始值都可以自己确定
    int b = n1;
    
    if (n == 0) return a;
    if (n == 1) return b;
    
    for (int i = 1; i < n; i++) {
        b = a + b;
        a = b - a;
    }
    return b;
}


//问题：n个人围成一圈，顺序排号。从第一个人开始报数（从1到3报数），
//凡报到3的人退出圈子，问最后留下的是原来第几号的那个人?
//算法：
int LastRemaining_Solution2(int n, unsigned int m)
{
    // invalid input
    if(n <= 0 || m < 0)
        return -1;
    
    // if there are only one integer in the circle initially,
    // of course the last remaining one is 0
    int lastinteger = 0;
    
    // find the last remaining one in the circle with n integers
    for (int i = 2; i <= n; i ++)
        lastinteger = (lastinteger + m) % i;
    
    return lastinteger;
}
//问题：题目：在一个字符串中找到第一个只出现一次的字符。
//如输入abaccdeff，则输出b。
//算法：hash函数
char firstSingleLetter(char* s) { //其实就是hash的思想
    int f[26] = {0};    //如果在原始字符串中还有其他的字符，得用ASCII码作为hash键值的表
    for (int i = 0; i < strlen(s); i ++)
        f[s[i] - 'a']++;
    for (int i = 0; i < strlen(s); i++) {
        int index = s[i] - 'a';
        if (f[index] == 1 )
            return s[i];
    }
    return ' ';
}
//algorithm: 利用bitset
bool CompareString(string long_str, string short_str)   //字符串包含
{
    bitset<26> flag;    //利用bitset类
    for(int i=0; i<long_str.size(); ++i)
    {
        // flag.set(n)置第n位为1
        flag.set(long_str[i]-'A');
    }
    for(int i=0; i<short_str.size(); ++i)
    {
        // flag.test(n)判断第n位是否为1
        if(!flag.test(short_str[i]-'A'))
            return false;
    }
    return true;
}

//算法2：hash映射，使用ASCII键值
char FirstNotRepeatingChar(char* pString)
{
    if(!pString)
        return 0;
    
    const int tableSize = 256;
    unsigned int hashTable[tableSize];
    memset(hashTable, 0, sizeof(hashTable));
    //for(unsigned int i = 0; i < tableSize; ++ i)
    //    hashTable[i] = 0;
    
    char* pHashKey = pString;
    while(*(pHashKey) != '\0')
        hashTable[*(pHashKey++)] ++;
    
    pHashKey = pString;
    while(*pHashKey != '\0')
    {
        if(hashTable[*pHashKey] == 1)
            return *pHashKey;
        
        pHashKey++;
    }
    
    return *pHashKey;
}

//problem: 变位词的判断
//algorithm: 先对字符串排序，然后判断两个字符串是否相等

bool wordsReorder(string s1, string s2)
{
    sort(s1.begin(), s1.end());
    //sort(&s1[0], &s1[0] + s1.size());
    sort(s2.begin(), s2.end());
    return s1 < s2;
}

//problem: 找出特定单词的所有变位词的集合
//algorithm: 先得到每个单词的标示（也就是其排序之后的字符串），然后按照标示进行排序
/*
 *  map是C++中的关联容器，map会自动排序，unordered_map不会自动排序，根据不同的需求选择
 *   按关键字有序
 *   关键字不可重复
 */

/*
 *对每个单词排序
 *排序后字符串作为关键字，原单词作为值
 *存入map中
 */
map<string, string> word;   //由于key是字符串，所以不需要自己定义比较函数，如果关键字是自己定义的类的话就要自己重载比较函数
void sign_sort(const char* dic)
{
    ifstream in(dic);
    if(!in)
    {
        cout << "Couldn't open file: " + string(dic) << endl;
        return;
    }
    
    string aword;
    string asign;
    while(in >> aword)
    {
        asign = aword;
        sort(asign.begin(), asign.end());
        word[asign] += aword + " "; //这个特别巧妙，将同一个key的value值都连接起来
    } 
    in.close(); 
}

void wordsExchange(vector<string> &vWords, map<string, string> &mWords) {
    int n = (int) vWords.size();
    for (int i = 0; i < n ; i++) {
        string value = vWords[i];
        string key = value;             //key保存的是变位词，value是原始的单词
        sort(key.begin(), key.end(), charCompare);
        mWords[key] += value + ' ';
    }
}

//问题：二叉树的层次遍历算法
//算法：利用队列进行迭代
void BinaryTreeLevelTraverse(BinaryTreeNode* root) {
    if (!root)  return;
    queue<BinaryTreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        BinaryTreeNode* pFront = q.front();
        printf("%d", pFront->m_nValue);
        q.pop();
        if (!root->m_pLeft)
            q.push(root->m_pLeft);
        if (!root->m_pRight)
            q.push(root->m_pRight);
    }
}
//也可以用deque
struct BTreeNode // a node in the binary tree
{
    int         m_nValue; // value of node
    BTreeNode  *m_pLeft;  // left child of node
    BTreeNode  *m_pRight; // right child of node
};
void PrintFromTopToBottom(BTreeNode *pTreeRoot)
{
    if(!pTreeRoot)
        return;
    
    // get a empty queue
    deque<BTreeNode *> dequeTreeNode;
    
    // insert the root at the tail of queue
    dequeTreeNode.push_back(pTreeRoot);
    
    while(!dequeTreeNode.empty())
    {
        // get a node from the head of queue
        BTreeNode *pNode = dequeTreeNode.front();
        dequeTreeNode.pop_front();
        
        // print the node
        cout << pNode->m_nValue << ' ';
        
        // print its left child sub-tree if it has
        if(pNode->m_pLeft)
            dequeTreeNode.push_back(pNode->m_pLeft);
        // print its right child sub-tree if it has
        if(pNode->m_pRight)
            dequeTreeNode.push_back(pNode->m_pRight);
    }
}
//也可以用数组
void PrintNodeByLevel(BTreeNode* root)
{
    if(root == NULL)
        return;
    vector<BTreeNode*> vec;		//这里我们使用STL 中的vector来代替数组，可利用
    //到其动态扩展的属性
    vec.push_back(root);
    int cur = 0;
    int last = 1;
    while(cur < vec.size())
    {
        last = (int)vec.size();		//新的一行访问开始，重新定位last于当前行最后
								//一个节点的下一个位置
        while(cur < last)
        {
            cout << vec[cur] -> m_nValue << " ";		//访问节点
            if(!vec[cur] -> m_pLeft)		//当前访问节点的左节点不为空则压入
                vec.push_back(vec[cur] -> m_pLeft);
            if(!vec[cur] -> m_pRight)		//当前访问节点的右节点不为空则压入，
                //注意左右节点的访问顺序不能颠倒
                vec.push_back(vec[cur] -> m_pRight);
            cur++;
        }
        cout << endl;		//当cur == last,说明该层访问结束，输出换行符
    }
}


//算法2：
/*我们知道树是图的一种特殊退化形式。
同时如果对图的深度优先遍历和广度优先遍历有比较深刻的理解，

将不难看出这种遍历方式实际上是一种广度优先遍历。
因此这道题的本质是在二元树上实现广度优先遍历。
*/

//问题：reverse a tree，构成他的镜像mirror，左右对称
//算法：分治递归
void Reversetree(BinaryTreeNode *root)
{
    if(!root)
        return;
    BinaryTreeNode *p;
    
    p = root->m_pLeft;
    root->m_pLeft = root->m_pRight;
    root->m_pRight = p;
    
    if(root->m_pLeft)
        Reversetree(root->m_pLeft);
    if(root->m_pRight)
        Reversetree(root->m_pRight);
}
//算法2：递归改迭代，利用一个栈
/*
由于递归的本质是编译器生成了一个函数调用的栈，
因此用循环来完成同样任务时最简单的办法就是用一个辅助栈来模拟递归。
首先我们把树的头结点放入栈中。
在循环中，只要栈不为空，弹出栈的栈顶结点，交换它的左右子树。
如果它有左子树，把它的左子树压入栈中；
如果它有右子树，把它的右子树压入栈中。
这样在下次循环中就能交换它儿子结点的左右子树了。
*/


//problem: 二叉搜索树的后序遍历验证
//algorithm: 递归调用
bool VerifySquenceOfBST(int sequence[], int length)
{
    if(sequence == NULL || length <= 0)
        return false;
    
    int root = sequence[length - 1];
    
    // 在二叉搜索树中，左子树节点小于根节点
    int i = 0;
    for(; i < length - 1; ++ i)
    {
        if(sequence[i] > root)  //找到partition的点
            break;
    }
    
    // 右子树节点大于根节点
    int j = i;
    for(; j < length - 1; ++ j)
    {
        if(sequence[j] < root)
            return false;
    }
    
    // 判断左子树是不是二叉树
    bool left = true;
    if(i > 0)
        left = VerifySquenceOfBST(sequence, i);
    
    // 判断右子树是不是二叉树
    bool right = true;
    if(i < length - 1)
        right = VerifySquenceOfBST(sequence + i, length - i - 1);
    
    return (left && right);
}


//判断一个二叉树是不是BST
//algorithm1: 每一个根节点保存一个最大值和一个最小值min/max法
bool isBSThelper(BinaryTreeNode* root, int min, int max) {
    if (root == NULL)
        return true;
    int t = root->m_value;
    if (t > max || t < min)
        return false;
    return isBSThelper(root->m_pLeft, min, t - 1) && isBSThelper(root->m_pLeft, t + 1, max);
}
bool isBST(BinaryTreeNode* root){
    return isBSThelper(root, INT_MIN, INT_MAX);
}

//采用中序遍历将节点的值保存到一个数组中，然后判断数组是不是满足递增的条件
static int index = 0;
void copyBST(BinaryTreeNode* root, int array[]) {
    if (root == NULL)
        return;
    copyBST(root->left, array);
    array[index] = root->m_value;
    index++;
    copyBST(root->right, array);
}
bool checkBST(BinaryTreeNode* root) {
    int* array = new int[index + 1];
    copyBST(root, array);
    for (int i = 1; i < index; i++) {
        if (array[i] <= array[i-1])
            return false;
    }
    return true;
}
//可以看出上面保存的数组其实没有必要，只需要比较后一个元素与前一个元素的大小关系
static int last_printed = INT_MIN;  //使用全局变量
bool checkBST2(BinaryTreeNode* root) {
    if (root == NULL)
        return true;
    if (!checkBST2(root->m_pLeft))
        return false;
    
    if (root->m_value <= last_printed)
        return false;
    last_printed = root->m_value;
    
    
    if (!checkBST2(root->m_pRight))
        return false;
    return true;
}

//也可以使用静态变量prev来保持前驱节点很巧妙
bool isBST(struct BinaryTreeNode* root)
{
    static struct BinaryTreeNode* prev = NULL;  //使用局部变量
    
    // traverse the tree in inorder fashion and keep track of prev node
    if(root == NULL)
        return true;
    
    if(!isBST(root->m_pLeft))
        return false;
    
    // Allows only distinct valued nodes
    if(prev != NULL && root->m_value <= prev->m_value)
        return false;
    
    prev = root;
    
    return isBST(root->m_pRight);

    
}
/*
 Given a Binary Tree where each node has following structure, write a function to populate next pointer for all nodes. The next pointer for every node should be set to point to inorder successor.
 */
// An implementation that doesn't use static variable
// A wrapper over populateNextRecur
void populateNext(struct node *root)
{
    // The first visited node will be the rightmost node
    // next of the rightmost node will be NULL
    struct node *next = NULL;
    
    populateNextRecur(root, &next);
}

/* Set next of all descendents of p by traversing them in reverse Inorder */
void populateNextRecur(struct BinaryTreeNode* p, struct BinaryTreeNode **next_ref)
{
    if (p)
    {
        // First set the next pointer in right subtree
        populateNextRecur(p->m_pRight, next_ref);
        
        // Set the next as previously visited node in reverse Inorder
        p->next = *next_ref;
        
        // Change the prev for subsequent node
        *next_ref = p;
        
        // Finally, set the next pointer in right subtree
        populateNextRecur(p->m_pLeft, next_ref);
    }
}





struct ListNode__ {
    int m_value;
    ListNode__* leftch;
    ListNode__* rightch;
};
void Reversetree2(ListNode__ *phead)
{
    if(!phead)
        return;
    
    stack<ListNode__*> stacklist;
    stacklist.push(phead);         //首先把树的头结点放入栈中。
    
    while(!stacklist.empty())
        //在循环中，只要栈不为空，弹出栈的栈顶结点，交换它的左右子树
    {
        ListNode__* pnode=stacklist.top();
        stacklist.pop();
        
        ListNode__* ptemp;
        ptemp = pnode->leftch;
        pnode->leftch = pnode->rightch;
        pnode->rightch = ptemp;
        
        if(pnode->leftch)
            stacklist.push(pnode->leftch);   //若有左子树，把它的左子树压入栈中
        if(pnode->rightch)
            stacklist.push(pnode->rightch);  //若有右子树，把它的右子树压入栈中
    }
}


//问题：已经排好序，求和为固定值的两个数字
//算法：两边往中间扫描
bool findTwoNumbers(int data[], unsigned int length, int sum, int& num1, int& num2) {
    bool found = false;
    if (length < 1) return found;
    int i = 0, j = length-1;
    while (i < j) {
        int curSum = data[i] + data[j];
        if (curSum == sum) {
            num1 = data[i];
            num2 = data[j];
            found = true;
            break;
        }else if (curSum > sum)
            j--;
        else
            i++;
    }
    return found;
}

//问题：单项链表，倒数第k个节点
//算法：注意对错误输入的处理
node* listSearch(node* head, int k) {
    int i = 0;
    node* p = head, *q = head;
    while (!p && i < k) {
        p = p->next;
        i++;
    }
    if (i < k) return NULL;
    while (!p) {
        q = q->next;
        p = p->next;
    }
    return q;
    
}

//问题：求二叉树中节点的最大距离...
//算法：dynanmic programming
// 数据结构定义
struct NODE_
{
    NODE_* pLeft;            // 左子树
    NODE_* pRight;          // 右子树
    int nMaxLeft;          // 左子树中的最长距离
    int nMaxRight;         // 右子树中的最长距离
    char chValue;        // 该节点的值
};
int nMaxLen;
// 寻找树中最长的两段距离
void FindMaxLen(NODE_* pRoot)
{
    // 遍历到叶子节点，返回
    if(pRoot == NULL){
        return;
    }
    
    // 如果左子树为空，那么该节点的左边最长距离为0
    if(pRoot -> pLeft == NULL){
        pRoot -> nMaxLeft = 0;
    }
    
    // 如果右子树为空，那么该节点的右边最长距离为0
    if(pRoot -> pRight == NULL){
        pRoot -> nMaxRight = 0;
    }
    
    // 如果左子树不为空，递归寻找左子树最长距离
    if(pRoot -> pLeft != NULL){
        FindMaxLen(pRoot -> pLeft);
    }
    
    // 如果右子树不为空，递归寻找右子树最长距离
    if(pRoot -> pRight != NULL){
        FindMaxLen(pRoot -> pRight);
    }
    
    // 计算左子树最长节点距离
    if(pRoot -> pLeft != NULL){
        int nTempMax = 0;
        if(pRoot -> pLeft -> nMaxLeft > pRoot -> pLeft -> nMaxRight){
            nTempMax = pRoot -> pLeft -> nMaxLeft;
        }
        else{
            nTempMax = pRoot -> pLeft -> nMaxRight;
        }
        pRoot -> nMaxLeft = nTempMax + 1;
    }
    
    // 计算右子树最长节点距离
    if(pRoot -> pRight != NULL){
        int nTempMax = 0;
        if(pRoot -> pRight -> nMaxLeft > pRoot -> pRight -> nMaxRight){
            nTempMax = pRoot -> pRight -> nMaxLeft;
        }
        else{
            nTempMax = pRoot -> pRight -> nMaxRight;
        }
        pRoot -> nMaxRight = nTempMax + 1;
    }
    
    // 更新最长距离
    if(pRoot -> nMaxLeft + pRoot -> nMaxRight > nMaxLen){
        nMaxLen = pRoot -> nMaxLeft + pRoot -> nMaxRight;
    }
}//很明显，思路完全一样，但书上给的这段代码更规范

//algorithm2: use divide-conquer.
/*
 * return the depth of the tree,getdepth
 */
struct Tree {
    Tree* left;
    Tree* right;
};

//简介版
int TreeDepth(BinaryTreeNode* pRoot)
{
    if(pRoot == NULL)
        return 0;
    
    int nLeft = TreeDepth(pRoot->m_pLeft);
    int nRight = TreeDepth(pRoot->m_pRight);
    
    return max(nLeft, nRight) + 1;
}

/*
 * return the max distance of the tree
 */
int get_max_distance(Tree *tree) {
    if (tree == NULL)
        return false;
    int distance = TreeDepth(tree->left) + TreeDepth(tree->right);
        
    // compare the value with it's sub trees
    int l_distance = get_max_distance(tree->left);
    int r_distance = get_max_distance(tree->right);
    
    return max(distance, max(l_distance, r_distance));
}

//problem: 判断一个二叉树是不是平衡二叉树
//algorithm: 后序遍历
//该算法的缺点是：每一个节点都遍历了多次

bool IsBalanced_Solution1(BinaryTreeNode* pRoot)
{
    if(pRoot == NULL)
        return true;
    
    int left = TreeDepth(pRoot->m_pLeft); //会多次计算同一个节点的深度
    int right = TreeDepth(pRoot->m_pRight);
    if (abs(left - right) > 1)
        return false;
    
    return IsBalanced_Solution1(pRoot->m_pLeft)
    && IsBalanced_Solution1(pRoot->m_pRight);
}

//algorithm2: 上述方法虽然简单，但是遍历了多次节点，可以考虑后序遍历，每一个节点
//用一个变量记录树的高度，然后该节点是否满足平衡二叉树的节点条件
class Solution_isbalanced {
public:
    bool isBalanced(TreeNode* root) {
        if (root == NULL)
            return true;
        int depth = 0;
        return isBalanced(root, depth);
    }
    
private:
    bool isBalanced(TreeNode* root, int& depth) {
        if (root == NULL) {
            depth = 0;
            return true;
        }
        int left, right;
        bool bl = isBalanced(root->left, left);
        bool br = isBalanced(root->right, right);
        if ( bl && br ) {
            if (abs(left - right) <= 1) {
                depth = max(left, right) + 1;
                return true;
            }
        }
        return false;
    }
};

//在不同的递归层，通过引用来传递参数，或阶段性胜利
class Balance {
public:
    bool isBalance(TreeNode* root) {
        int depth = 0;
        return isBalanced(root, depth);
    }
    
private:
    bool isBalanced(TreeNode* root, int& depth) {
        if (root == NULL) {
            depth = 0;
            return true;
        }
        
        int left, right;
        bool lb, rb;
        lb = isBalanced(root->left, left);
        rb = isBalanced(root->right, right);
        if (lb && rb) {
            if (left - right <= 1 && left - right >= -1) {
                depth = (left > right) ? left + 1 : right + 1;
                return true;
            }
        }
        return false;
    }
};


//问题：判断整数序列是不是二叉查找树的后序遍历结果
//算法：其实就是二叉查找树后序遍历的基本算法
bool verifySquenceOfBST(int squence[], int length)
{
    if(squence == NULL || length <= 0)
        return false;
    
    // root of a BST is at the end of post order traversal squence
    int root = squence[length - 1];
    
    // the nodes in left sub-tree are less than the root
    int i = 0;
    for(; i < length - 1; ++ i)
    {
        if(squence[i] > root)
            break;
    }
    
    // the nodes in the right sub-tree are greater than the root
    int j = i;
    for(; j < length - 1; ++ j)
    {
        if(squence[j] < root)
            return false;
    }
    
    // verify whether the left sub-tree is a BST
    bool left = true;
    if(i > 0)
        left = verifySquenceOfBST(squence, i);
    
    // verify whether the right sub-tree is a BST
    bool right = true;
    if(i < length - 1)
        right = verifySquenceOfBST(squence + i, length - i - 1);
    
    return (left && right);
}


//问题：reverse a list
//算法：使用三个额外指针，可以改用两个额外指针
node *reverseList(node *head)
{
    if (head == NULL)
        return NULL;
    node *p,*q,*r;
    p = head;
    q = p->next;
    while(q != NULL)
    {
        r = q->next;
        q->next = p;
        p = q;
        q = r;
    }
    head->next = NULL;
    head = p;
    return head;
}
node *reverseList2(node *head)
{
    if (head == NULL)
        return NULL;
    node *q,*r;
    q = head->next;
    head->next = NULL;
    
    while(q != NULL)
    {
        r = q->next;
        q->next = head;
        head = q;
        q = r;
    }

    return head;
}



/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) {
 *         val = x;
 *         next = null;
 *     }
 * }
 */
public class Solution_reverseKGroup{
    public ListNode reverseKGroup(ListNode head, int k) {
        if(head == null || head.next == null || k < 2) return head;
        ListNode fakeHead = new ListNode(-1);
        fakeHead.next = head;
        ListNode pre = fakeHead;
        ListNode cur = head;
        int i = 0;
        while(cur != null){
            i++;
            cur = cur.next;
            if(i % k == 0){
                pre = reverseLinkedList(pre, cur);
                if(i == k){
                    head = pre;
                }
                int temp = k;
                while(temp > 1){
                    pre = pre.next;
                    temp--;
                }
            }
        }
        return head;
    }
    
    //reverse nodes between beginNode and endNode(exclusively)
    //return the first node in the reversed part
    private static ListNode reverseLinkedList(ListNode beginNode, ListNode endNode) {
        // TODO Auto-generated method stub
        ListNode head = beginNode.next;
        ListNode dummy = head;//use dummy to maintain the new head
        ListNode pre = head;
        ListNode cur = pre.next;
        ListNode after = cur.next;
        while(cur != endNode){
            pre.next = after;
            cur.next = dummy;
            dummy = cur;
            cur = pre.next;
            if(cur == null) break;
            after = cur.next;
        }
        beginNode.next = dummy;//!after reverse, beginNode should also before the first Node, endNode should also before the last node
        return dummy;
    }
}
//problem: usr insertion sort to sort a single linked list
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
namespace insertionSortList {
    struct ListNode {
             int val;
             ListNode *next;
             ListNode(int x) : val(x), next(NULL) {}
        };
    
    class Solution_insertionSortList {
    public:
        ListNode *insertionSortList(ListNode *head) {
            if (head == nullptr) return head;
            
            ListNode* curr = head -> next;
            head -> next = nullptr;
            
            while(curr != nullptr){
                ListNode* tmpHead = head;
                ListNode* prev = nullptr;
                //这个刚开始设为空很重要，通过判断这个变量是否改变来判断时候在头结点处插入节点
                ListNode* next = curr -> next;
                while(tmpHead != nullptr && tmpHead -> val <= curr -> val)
                {
                    prev = tmpHead;
                    tmpHead = tmpHead -> next;
                }
                
                if(prev != nullptr){
                    //insert
                    if(prev -> next){
                        curr -> next = prev -> next;
                        prev -> next = curr;
                    }else
                    {
                        prev -> next = curr;
                        curr -> next = nullptr;
                    }
                }else{
                    curr -> next = head;
                    head = curr;
                }
                
                curr = next;
            }
            return head;
        }
        
    };

}

/*
 Given a list, rotate the list to the right by k places, where k is non-negative.
 
 For example:
 Given 1->2->3->4->5->NULL and k = 2,
 return 4->5->1->2->3->NULL.
 */


node* rotateRight(node* head, int k) {
    if (head == NULL)
        return NULL;
    if (head->next == NULL)
        return head;
    node* tail = head;
    node* p = head;
    int len = 0;
    while (p != NULL) {
        len++;
        tail = p;
        p = p -> next;
    }
    k = k % len;
    p = head;
    for (int i = 0 ; i < len - k - 1; i++) {
        p = p->next;
    }
    tail -> next = head;
    head = p->next;
    p->next = NULL;
    return head;
}

//问题：给出俩个单向链表的头指针，比如h1，h2，判断这俩个链表是否相交。交点
//算法：
/*
 1.首先假定链表不带环
 那么，我们只要判断俩个链表的尾指针是否相等。
 相等，则链表相交；否则，链表不相交。
 2.如果链表带环，
 那判断一链表上俩指针相遇的那个节点，在不在另一条链表上。
 如果在，则相交，如果不在，则不相交。
 
 所以，事实上，这个问题就转化成了：
 1.先判断带不带环
 2.如果都不带环，就判断尾节点是否相等
 3.如果都带环，判断一链表上俩指针相遇的那个节点，在不在另一条链表上。
 如果在，则相交，如果不在，则不相交。
 */

//判断一个单项链表是否存在环，快慢指针，双指针都是解决问题的好办法
bool checkCircle(const node* head)
{
    if(head==NULL)                  //首先检查这个
        return false;
    const node *low = head, *fast = head->next;
    while(fast && fast->next)
    {
        low = low->next;
        fast = fast->next->next;
        if(low == fast) return true;
    }
    return false;
}

//判断一个单项链表的环的位置
node* FindLoopPort(node *head)
{
    node *slow = head, *fast = head;
    while ( fast && fast->next )
    {
        slow = slow->next;
        fast = fast->next->next;
        if ( slow == fast ) break;
    }
    if (fast == NULL || fast->next == NULL)
        return NULL;
    slow = head;
    while (slow != fast)
    {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

//下面这种算法有bug
bool connectionList(const node* h1, const node* h2) {
    if (h1 == NULL || h2 == NULL)           //首先检查这个
        return false;
    if (!checkCircle(h1) && !checkCircle(h2)) { //都没环
        while (h1->next != NULL) h1 = h1->next;
        while (h2->next != NULL) h2 = h2->next;
        if (h1 == h2)
            return true;
        
    }else {
        while (h1 != h2 && h1 != NULL && h2 != NULL) {
            /*若都有环，但是不相交，这里是死循环*/
            /*
             所以，判断带环的链表，相不相交，只能这样：
             如果都带环，判断一链表上俩指针相遇的那个节点，在不在另一条链表上。
             如果在，则相交，如果不在，则不相交
             */
            h1 = h1->next;
            if (h2->next)
                h2 = h2->next->next;
            else
                h2 = h2->next;
        }
        if (h1 == h2 && h1 && h2)
            return true;
        
    }
    return false;
}

//algorithm3: 先遍历得到两条链表的长度信息，先让长度更长的移动一段距离，再同时开始运动
//algorithm4:
unsigned int GetListLength(ListNode* pHead);

ListNode* FindFirstCommonNode( ListNode *pHead1, ListNode *pHead2)
{
    //
    unsigned int nLength1 = GetListLength(pHead1);
    unsigned int nLength2 = GetListLength(pHead2);
    int nLengthDif = nLength1 - nLength2;
    
    ListNode* pListHeadLong = pHead1;
    ListNode* pListHeadShort = pHead2;
    if(nLength2 > nLength1)
    {
        pListHeadLong = pHead2;
        pListHeadShort = pHead1;
        nLengthDif = nLength2 - nLength1;
    }
    
    //
    for(int i = 0; i < nLengthDif; ++ i)
        pListHeadLong = pListHeadLong->succ;
    
    while((pListHeadLong != NULL) &&
          (pListHeadShort != NULL) &&
          (pListHeadLong != pListHeadShort))
    {
        pListHeadLong = pListHeadLong->succ;
        pListHeadShort = pListHeadShort->succ;
    }
    
    return pListHeadLong; //这步还是比较巧妙，不需要判断是不是到达末尾了
}

unsigned int GetListLength(ListNode* pHead)     //代码复用的体现
{
    unsigned int nLength = 0;
    ListNode* pNode = pHead;
    while(pNode != NULL)
    {
        ++ nLength;
        pNode = pNode->succ;
    }
    
    return nLength;
}




//问题：在二叉树中找出和为某一值的所有路径(树）
//算法：与Leetcode combination sum I的类似，使用回溯剪枝法，利用堆栈和深度优先搜索策略
/*
 当访问到某一结点时，把该结点添加到路径上，并累加当前结点的值。
 如果当前结点为叶结点并且当前路径的和刚好等于输入的整数，则当前的路径符合要求，我们把它打印出来
 
 如果当前结点不是叶结点，则继续访问它的子结点。当前结点访问结束后，递归函数将自动回到父结点。
 因此我们在函数退出之前要在路径上删除当前结点并减去当前结点的值，
 以确保返回父结点时路径刚好是根结点到父结点的路径。
 
 我们不难看出保存路径的数据结构实际上是一个栈结构，因为路径要与递归调用状态一致，
 而递归调用本质就是一个压栈和出栈的过程。
 */
//递归1
void FindPath_(
              BinaryTreeNode*   pTreeNode,    // a node of binary tree
              int               expectedSum,  // the expected sum
              int&              currentSum,   // the sum of path
              vector<int>&      path         // a path from root to current node
){
    if(!pTreeNode)
        return;
    
    currentSum += pTreeNode->m_nValue;
    path.push_back(pTreeNode->m_nValue);
    //这里没有采用stack而是采用vector原因在于我们要遍历栈中的元素，而栈不提供迭代器的功能
    
    // if the node is a leaf, and the sum is same as pre-defined,
    // the path is what we want. print the path
    bool isLeaf = (!pTreeNode->m_pLeft && !pTreeNode->m_pRight);
    if(currentSum == expectedSum && isLeaf)
    {
        std::vector<int>::iterator iter = path.begin();
        for(; iter != path.end(); ++ iter)
            std::cout << *iter << '\t';
        std::cout << std::endl;
    }
    
    // if the node is not a leaf, goto its children
    if(pTreeNode->m_pLeft)
        FindPath_(pTreeNode->m_pLeft, expectedSum, currentSum, path);
    if(pTreeNode->m_pRight)
        FindPath_(pTreeNode->m_pRight, expectedSum, currentSum, path);
    
    // when we finish visiting a node and return to its parent node,
    // we should delete this node from the path and
    // minus the node's value from the current sum
    currentSum -= pTreeNode->m_nValue;
    path.pop_back();
}

//递归2， 剑指offer
void FindPath(BinaryTreeNode* pRoot, int expectedSum, std::vector<int>& path, int& currentSum);

void FindPath(BinaryTreeNode* pRoot, int expectedSum)
{
    if(pRoot == NULL)
        return;
    
    std::vector<int> path;
    int currentSum = 0;
    FindPath(pRoot, expectedSum, path, currentSum);
}

void FindPath
(
 BinaryTreeNode*   pRoot,
 int               expectedSum,
 std::vector<int>& path,
 int&              currentSum
 )
{
    currentSum += pRoot->m_nValue;
    path.push_back(pRoot->m_nValue);

    bool isLeaf = pRoot->m_pLeft == NULL && pRoot->m_pRight == NULL;
    if(currentSum == expectedSum && isLeaf)
        //找到了满足条件的方案，打印出来，这其实与遍历的思想完全一致，相当于VISIT函数
    {
        printf("A path is found: ");
        std::vector<int>::iterator iter = path.begin();
        for(; iter != path.end(); ++ iter)
            printf("%d\t", *iter);
        
        printf("\n");
    }
    
    if(pRoot->m_pLeft != NULL)
        FindPath(pRoot->m_pLeft, expectedSum, path, currentSum);
    if(pRoot->m_pRight != NULL)
        FindPath(pRoot->m_pRight, expectedSum, path, currentSum);
    
    //在返回父节点之前，在路径上删除当前节点，并在currentSum中减去当前节点的值
    currentSum -= pRoot->m_nValue;
    path.pop_back();
}


//题目：求子数组的最大和
/*
输入一个整形数组，数组里有正数也有负数。
数组中连续的一个或多个整数组成一个子数组，每个子数组都有一个和。
求所有子数组的和的最大值。要求时间复杂度为O(n)。
*/
//算法：
/*
 解释下：
 例如输入的数组为1, -2, 3, 10, -4, 7, 2, -5，
 那么最大的子数组为     3, 10, -4, 7, 2，
 因此输出为该子数组的和18
 
 所有的东西都在以下俩行，
 即：
 b  ：  0  1  -1  3  13   9  16  18  7
 sum：  0  1   1  3  13  13  16  18  18
 
 其实算法很简单，当前面的几个数，加起来后，b<0后，
 把b重新赋值，置为下一个元素，b=a[i]。
 当b>sum，则更新sum=b;
 若b<sum，则sum保持原值，不更新
 */
int maxSubArray(int* a, int n)
{
    int sum = 0;
    int b = 0;
    
    for(int i = 0; i < n; i++)
    {
        if(b < 0)
            b = a[i];
        else
            b += a[i];
        if(sum < b)
            sum = b;
    }
    return sum;
}
//算法：动态规划
int maxSubArray2(int A[], int n) {
    int result = INT_MIN, f = 0;
    for (int i = 0; i < n; i++) {
        f = max(f + A[i], A[i]);
        result = max(result, f);
    }
    return result;
}


//problem: obstain the maximum sum of the sub-matrix
//algorithm: dynanmic programming, 2D DP，下面这段代码是错的，但是思想是对的，利用积分图
//int maxSubMatrix(vector<vector<int> >& matrix) {
//    int N = (int)matrix.size();
//    int M = (int)matrix[0].size();
//    int PS[N+1][M+1];
//    for (int i = 0; i <= N; i++){
//        PS[i][0] = 0;
//    }
//    for (int j = 0; j <= M; j++){
//        PS[0][j] = 0;
//    }
//    int tmp = 0;
//    for (int i = 1; i <= N; i++) {
//        for (int j = 1; j <= M; j++) {
//            tmp  = PS[i-1][j] + PS[i][j-1] - PS[i-1][j-1] + matrix[i-1][j-1];
//            PS[i][j] = max(max(tmp, PS[i-1][j]), max(PS[i-1][j-1], PS[i][j-1]));
//        }
//    }
//    return PS[N][M];
//    
//}
//algorithm2: 这下面的才是对的，利用maxSubArray

int maxSubMatrix(vector<vector<int> > a, int n){
    
    int max_sum = INT_MIN;
    int * b = new int [n];
    int rowLast = 0;
    int colLast = 0;
    for(int j = 0;j < n;j++)
    {
        for(int i = 0; i < n; i++)
            b[i]= 0;
        for(int i = j; i < n; i++) {
            for(int k = 0;k < n;k++)
                b[k] += a[k][i]; //换成行相加，效率更高，缓存友好
            //其实这还能优化，用一个三维的数组来记录中间值，可以避免重复的运算
            int sum = maxSubArray(b,n);
            if(sum > max_sum) {
                max_sum = sum;
                rowLast = j;
                colLast = i;
            }
        }
    }
    delete []b;
    return max_sum;
}


//问题：设计包含min函数的栈，定义栈的数据结构，要求添加一个min函数，能够得到栈的最小元素。
//要求函数min、push以及pop的时间复杂度都是O(1)。
//算法：借助一个辅助栈来保存最小值stackmin、minstack
template<typename T>
class StackSuppliedMin{
public:
    vector<T> datas;
    vector<size_t> s; //借助一个辅助栈,保存的是最小值的index
    
    void push(T data){
        datas.push_back(data);
        if (s.empty() || data < datas[s.back()])
            s.push_back(datas.size()-1);
    }
    
    void pop(){
        assert(!datas.empty());     //这步还是没有判断
        if (datas.back() == datas[s.back()])
            s.pop_back();
        datas.pop_back();
    }
    
    T min(){
        assert(!datas.empty() && !s.empty());//这步也没有判断，真是作死
        return datas[s.back()];
    }
    
    void display();
};


//算法2：上面的存储空间为O(n)，是不是可以在堆栈中元素添加一个额外的数据项
typedef struct nodeMinStackMinStack{
    int val, min;
}nodeMinStack;

class StackWithMin{
public:
    StackWithMin(int size=1000){
        buf = new nodeMinStack[size];
        buf[0].min = MAX_INT;
        cur = 0;
    }
    ~StackWithMin(){
        delete[] buf;
    }
    void push(int val){
        buf[++cur].val = val;
        if(val<buf[cur-1].min) buf[cur].min = val;
        else buf[cur].min = buf[cur-1].min;
    }
    void pop(){
        --cur;
    }
    int top(){
        return buf[cur].val;
    }
    bool empty(){
        return cur==0;
    }
    int min(){
        return buf[cur].min;
    }
    
private:
    nodeMinStack *buf;
    int cur;
};

//算法3：在另一个栈中直接存储最小值，但是这个的复杂度与上面算法2的一样，能不能降低空间复杂大，特别是当栈底的元素恰好最小时
class minStack {
public:
    stack<int> s1;
    stack<int> s2;
    
    void push(int x){
        s1.push(x);
        if (s2.empty() && s2.top() >= x)
            s2.push(x);
    }
    
    void pop() {
        assert(!s1.empty());
        if (s1.top() == s2.top())
            s2.pop();
        s1.pop();
    }
    
    int getMin(){
        assert(!s2.empty());
        return s2.top();
    }
};



//problem: 将上面的最小值栈推广到最大值队列
//algorithm: 用两个栈可以实现一个队列，而其中的一个栈是上述的最大栈（最小的类似），所以最大的队列包含了底层4个基本栈
template<typename T>
class MaxStack {
public:
    void Push(const T& value) {
        data_.push(value);
        if (max_element_.empty()) {
            max_element_.push(value);
        } else if (value >= max_element_.top()) {
            max_element_.push(value);
        }
    }
    T Top() {
        return data_.top();
    }
    void Pop() {
        if (data_.top() == max_element_.top()) {
            max_element_.pop();
        }
        data_.pop();
    }
    bool Empty() {
        return data_.empty();
    }
    T Max() {
        if (!max_element_.empty()) {
            return max_element_.top();
        }
        return -1;
    }
private:
    std::stack<T> data_;
    std::stack<T> max_element_;
};

template<typename T>
class MaxQueue {
public:
    void Push(const T& value) {
        push_stack_.Push(value);
    }
    T Front() {
        if (pop_stack_.empty()) {
            while (!push_stack_.Empty()) {
                pop_stack_.Push(push_stack_.Top());
                push_stack_.Pop();
            }
        }
        return pop_stack_.Top();
    }
    void Pop() {
        if (pop_stack_.Empty()) {
            while (!push_stack_.Empty()) {
                pop_stack_.Push(push_stack_.Top());
                push_stack_.Pop();
            }
        }
        pop_stack_.Pop();
    }
    bool IsEmpty() {
        return push_stack_.Empty() && pop_stack_.Empty();
    }
    T Max() {
        if (!push_stack_.Empty() && !pop_stack_.Empty()) {
            return push_stack_.Max() > pop_stack_.Max() ? push_stack_.Max() : pop_stack_.Max();
        } else if (push_stack_.Empty() && !pop_stack_.Empty()) {
            return pop_stack_.Max();
        } else if (!push_stack_.Empty() && pop_stack_.Empty()) {
            return push_stack_.Max();
        } else {
            //      throw RUNTIME_ERROR;
        }
        return -1;
    }
private:
    MaxStack<T> push_stack_;
    MaxStack<T> pop_stack_;
};
void maxqueue_main() {
    MaxQueue<int> max_queue;
    max_queue.Push(1);
    max_queue.Push(2);
    max_queue.Push(6);
    max_queue.Push(4);
    max_queue.Push(5);
    max_queue.Push(2);
    printf("max %d\n", max_queue.Max());
    max_queue.Pop();
    printf("max %d\n", max_queue.Max());
    max_queue.Pop();
    printf("max %d\n", max_queue.Max());
    max_queue.Pop();
    printf("max %d\n", max_queue.Max());
    max_queue.Pop();
    printf("max %d\n", max_queue.Max());
    max_queue.Pop();
    printf("max %d\n", max_queue.Max());
}


//问题：把二元查找树转变成排序的双向链表
//算法：中序递归
struct BSTtreenode
{
    int m_nValue; // value of node
    BSTtreenode *m_pLeft; // left child of node
    BSTtreenode *m_pRight; // right child of node
    BSTtreenode(int mv = 0, BSTtreenode* ml = NULL, BSTtreenode* mr = NULL): m_nValue(mv), m_pLeft(ml), m_pRight(mr) {}
};

typedef BSTtreenode DoubleList;
DoubleList * pHead;
DoubleList * pLastNodeInlist; //始终指向双向链表的最后一个节点

void convertToDoubleList(BSTtreenode * pCurrent);
// 创建二元查找树
void addBSTreeNode(BSTtreenode * & pCurrent, int value)
{
    if (NULL == pCurrent)
    {
        BSTtreenode * pBSTree = new BSTtreenode();
        pBSTree->m_pLeft = NULL;
        pBSTree->m_pRight = NULL;
        pBSTree->m_nValue = value;
        pCurrent = pBSTree;
        
    }
    else
    {
        if ((pCurrent->m_nValue) > value)
        {
            addBSTreeNode(pCurrent->m_pLeft, value);
        }
        else if ((pCurrent->m_nValue) < value)
        {
            addBSTreeNode(pCurrent->m_pRight, value);
        }
        else
        {
            //cout<<"重复加入节点"<<endl;
        }
    }
}

// 遍历二元查找树  中序
void inorderBSTree(BSTtreenode * pCurrent)
{
    if (NULL == pCurrent){
        return;
    }
    if (NULL != pCurrent->m_pLeft){
        inorderBSTree(pCurrent->m_pLeft);
    }
    // 节点接到链表尾部，假设之前访问过的结点已经调整为一个双向链表，且最后一个元素是
    // 已链接元素的最大值，那么只需要将当前结点连接至双向链表的最后一个结点即可
    
    convertToDoubleList(pCurrent);
    
    // 右子树为空
    if (NULL != pCurrent->m_pRight){
        inorderBSTree(pCurrent->m_pRight);
    }
}

// 二叉树转换成list
void  convertToDoubleList(BSTtreenode * pCurrent)
{
    
    pCurrent->m_pLeft = pLastNodeInlist; //使当前结点的左指针指向双向链表中最后一个结点
    if (NULL != pLastNodeInlist) //使双向链表中最后一个结点的右指针指向当前ƒ结点
    {
        pLastNodeInlist->m_pRight = pCurrent;
    }
    else //若最后一个元素不存在，此时双向链表尚未建立，因此将当前结点设为双向链表头结点
    {
        pHead = pCurrent;
    }
    pLastNodeInlist = pCurrent; //将当前结点设为双向链表中最后一个结点
    cout<<pCurrent->m_nValue<<endl;
}

//单向排序链表转换为二叉排序树
BSTtreenode* genBST(int start, int end, vector<BSTtreenode*> &treeNodes);
BSTtreenode *sortedListToBST(node *head)
{
    vector<BSTtreenode*> treeNodes;
    while (head != NULL)
    {
        BSTtreenode *p = new BSTtreenode(head->data);
        treeNodes.push_back(p);
        head = head->next;
    }
    return genBST(0, (int)treeNodes.size() - 1, treeNodes);
}

BSTtreenode* genBST(int start, int end, vector<BSTtreenode*> &treeNodes)
{
    if (start == end) return treeNodes[start];
    else if (start+1 == end)
    {
        treeNodes[start]->m_pRight = treeNodes[end];
        return treeNodes[start];
    }
    
    int mid = (start+end)/2;
    BSTtreenode* root = treeNodes[mid];
    root->m_pLeft = genBST(start, mid-1, treeNodes);
    root->m_pRight = genBST(mid+1, end, treeNodes);
    return root;
}

/*
 
 Flatten Binary Tree to Linked List
 Given a binary tree, flatten it to a linked list in-place.
 
 For example,
 Given
 
     1
    / \
   2   5
  / \   \
 3   4   6
 The flattened tree should look like:
 1
  \
   2
    \
     3
      \
       4
        \
         5
          \
           6

 */
//拉伸
void flatten(TreeNode* root) {
    if (NULL == root)
        return;
    flatten(root->left);
    flatten(root->right);
    if (NULL == root->left) return;
    //三方进行合并,将左子树所形成的链表插入到root和root->right之间
    TreeNode* p = root->left;
    while(p->right)
        p = p->right;
    p->right = root->right;
    root->right = root->left;
    root->left = NULL;
}

//迭代版


//问题：给定两个串a和b，问b是否是a的子串的变位词。例如输入a = hello, b = lel, lle,
//ello都是true,但是b = elo是false
//算法：划窗+字符种类差(动态的窗口调整)

bool f(string a,string b)
{
    vector<int> num(25,0);
    int nonZero = 0;
    for(int i=0;i<b.size();++i)
    {
        if(++num[b[i]-'a']==1)
            ++nonZero;
    }
    for(int i=0;i<b.size();++i)
    {
        int c = a[i] - 'a';
        --num[c];
        if(num[c]==0)       --nonZero;
        else if(num[c]==-1) ++nonZero;
    }
    if(nonZero == 0)        return true;
    //旧窗口a[i-b.size()..i-1]
    //新窗口a[i-b.size()+1..i]
    for(int i = b.size(); i < a.size(); ++i)      //这种最好由后往前
    {
        //删除a[i-b.size()]
        int c = a[i-b.size()]-'a';
        ++num[c];
        if(num[c]==0)       --nonZero;
        else if(num[c]==1)  ++nonZero;
        //添加a[i]
        c=a[i]-'a';
        --num[c];
        if(num[c]==0)       --nonZero;
        else if(num[c]==-1) ++nonZero;
        if(nonZero==0)      return true;
    }
    return false;
}



//问题：bitmap的使用
//算法：
/*简述bitmap的原理：(以字符串是否包含为例)
 int dictionary = 0; 用来保存32个bit;
 
 setbit:
    for x in string1:
        dictionary = dictionary | 0x01 << x - 'a';
 getbit:
    for x in string2:
        if dictionary != dictionary | 0x01 << x - 'a';
            break;
        else
            YES;
 */
#define BYTESIZE 8  //定义每个Byte中有8个Bit位
void SetBit(char *p, int posi)
{
    for(int i = 0; i < posi/BYTESIZE; i++)
    {
        p++;
    }
    
    *p = *p|(0x01 << (posi%BYTESIZE));//将该Bit位赋值1
    return;
}

void BitMapSortDemo(int* data, int n, int maxElement)
{
    //为了简单起见，我们不考虑负数
    
    const int BufferLen = maxElement / 8 + 1;
    //BufferLen这个值是根据待排序的数据中最大值确
    //待排序中的最大值是14，因此只需要2个Bytes(16个Bit)
    char *pBuffer = new char[BufferLen];
    
    //要将所有的Bit位置为0，否则结果不可预知。
    memset(pBuffer,0,BufferLen);
    for(int i = 0; i < n; i++)    //
    {
        //首先将相应Bit位上置为1
        SetBit(pBuffer,data[i]);
    }
    
    //输出排序结果
    for(int i=0; i < BufferLen; i++)    //每次处理一个字节(Byte)
    {
        for(int j=0; j< BYTESIZE;j++)   //处理该字节中的每个Bit位
        {
            //判断该位上是否是1，进行输出，这里的判断比较笨。
            //首先得到该第j位的掩码（0x01＜＜j），将内存区中的
            //位和此掩码作与操作。最后判断掩码是否和处理后的
            //结果相同
            if((*pBuffer&(0x01 << j)) == (0x01<<j))
            {
                printf("%d ",i*BYTESIZE + j);
            }
        }
        pBuffer++;
    }
}
//下面建立一个类来实现bitmap

class Bitmap{
public:
    Bitmap(int size = 32){
        bits = new int[size/32 + 1];
    }
    ~Bitmap(){
        delete[] bits;
    }
    bool get(int pos){// true if bit is 1, else: false
        return (bits[pos/32] & (1<<(pos&0x1f))) != 0;
    }
    void set(int pos){
        bits[pos/32] |= (1<<(pos&0x1f));
    }
private:
    int *bits;
};

void print_duplicates(int a[], int n, int bitsize){
    Bitmap bm(bitsize);
    for(int i=0; i<n; ++i){
        if(bm.get(a[i]-1)) // bitmap starts at 0, number starts at 1
            cout<<a[i]<<endl;
        else
            bm.set(a[i]-1);
    }
}
int main_Bitmap(){
    int a[] = {
        1,2,3,4,5,32000,7,8,9,10,11,1,2,13,15,16,32000,11,5,8
    };
    print_duplicates(a, 20, 32000);
    return 0;
}


//问题：建立Trie树
//算法：用于匹配，统计等
namespace trie {
    
    #define MAX 26//字符集大小
    typedef struct TrieNode
    {
        int nCount;//记录该字符出现次数
        struct TrieNode* next[MAX];
    }TrieNode;

    TrieNode Memory[1000000];
    int allocp=0;

    /*初始化*/
    void InitTrieRoot(TrieNode* *pRoot)
    {
        *pRoot=NULL;
    }

    /*创建新结点*/
    TrieNode* CreateTrieNode()
    {
        int i;
        TrieNode *p;
        p = &Memory[allocp++];
        p->nCount=1;
        for(i=0;i<MAX;i++)
        {
            p->next[i]=NULL;
        }
        return p;
    }

    /*插入*/
    void InsertTrie(TrieNode* *pRoot,char *s)
    {
        int i,k;
        TrieNode *p;
        if(!(p = *pRoot))
        {
            p = *pRoot = CreateTrieNode();
        }
        i=0;
        while(s[i])
        {
            k = s[i++] - 'a';//确定branch
            if(p->next[k]) p->next[k]->nCount++;
            else p->next[k] = CreateTrieNode();
            p = p->next[k];
        }
    }

    //查找
    int SearchTrie(TrieNode* *pRoot,char *s)
    {
        TrieNode *p;
        int i,k;
        if(!(p = *pRoot))
        {
            return 0;
        }
        i=0;
        while(s[i])
        {
            k = s[i++]-'a';
            if(p->next[k] == NULL) return 0;
            p=p->next[k];
        }
        return p->nCount;
    }

}

//问题：归并向量的中位数
//算法：充分利用向量的有序性
//中位数算法蛮力版：效率低，仅适用于max(n1, n2)较小的情况
//子向量S1[lo1, lo1 + n1)和S2[lo2, lo2 + n2)分别有序，数据项可能重复
int trivialMedian ( vector<int>& S1, int lo1, int n1, vector<int>& S2, int lo2, int n2 ) {
    int hi1 = lo1 + n1, hi2 = lo2 + n2;
    vector<int> S; //将两个有序子向量归并为一个有序向量
    while ( ( lo1 < hi1 ) && ( lo2 < hi2 ) ) {
        while ( ( lo1 < hi1 ) && S1[lo1] <= S2[lo2] ) S.push_back ( S1[lo1 ++] );
        while ( ( lo2 < hi2 ) && S2[lo2] <= S1[lo1] ) S.push_back ( S2[lo2 ++] );
    }
    while ( lo1 < hi1 )
        S.push_back ( S1[lo1 ++] );
    while ( lo2 < hi2 )
        S.push_back ( S1[lo2 ++] );
    return S[ ( n1 + n2 ) / 2]; //直接返回归并向量的中位数
}
//归并长度等长的向量
int median( vector<int>& S1, int lo1, vector<int>& S2, int lo2, int n ) { //中位数算法（高效版）

    if ( n < 3 )
        return trivialMedian ( S1, lo1, n, S2, lo2, n ); //递归基，当元素数目较少时，可以采用蛮力法
    int mi1 = lo1 + n / 2, mi2 = lo2 + ( n - 1 ) / 2; //长度（接近）减半
    if ( S1[mi1] < S2[mi2] )
        return median ( S1, mi1, S2, lo2, n + lo1 - mi1 ); //取S1右半、S2左半
    else if ( S1[mi1] > S2[mi2] )
        return median ( S1, lo1, S2, mi2, n + lo2 - mi2 ); //取S1左半、S2右半
    else
        return S1[mi1];
}
//归并长度不等长的向量，复杂度：log(min(n1, n2))
int median ( vector<int>& S1, int lo1, int n1, vector<int>& S2, int lo2, int n2 ) { //中位数算法
    if ( n1 > n2 ) return median ( S2, lo2, n2, S1, lo1, n1 ); //确保n1 <= n2
    if ( n2 < 6 ) //递归基：1 <= n1 <= n2 <= 5
        return trivialMedian ( S1, lo1, n1, S2, lo2, n2 );
    ///////////////////////////////////////////////////////////////////////
    //                lo1            lo1 + n1/2      lo1 + n1 - 1
    //                 |                 |                 |
    //                 X >>>>>>>>>>>>>>> X >>>>>>>>>>>>>>> X
    // Y .. trimmed .. Y >>>>>>>>>>>>>>> Y >>>>>>>>>>>>>>> Y .. trimmed .. Y
    // |               |                 |                 |               |
    // lo2     lo2 + (n2-n1)/2       lo2 + n2/2     lo2 + (n2+n1)/2    lo2 + n2 -1
    ///////////////////////////////////////////////////////////////////////
    if ( 2 * n1 < n2 ) //若两个向量的长度相差悬殊，则长者（S2）的两翼可直接截除
        return median ( S1, lo1, n1, S2, lo2 + ( n2 - n1 - 1 ) / 2, n1 + 2 - ( n2 - n1 ) % 2 );
    ///////////////////////////////////////////////////////////////////////
    //    lo1                  lo1 + n1/2              lo1 + n1 - 1
    //     |                       |                       |
    //     X >>>>>>>>>>>>>>>>>>>>> X >>>>>>>>>>>>>>>>>>>>> X
    //                             |
    //                            m1
    ///////////////////////////////////////////////////////////////////////
    //                            mi2b
    //                             |
    // lo2 + n2 - 1         lo2 + n2 - 1 - n1/2
    //     |                       |
    //     Y <<<<<<<<<<<<<<<<<<<<< Y ...
    //                                .
    //                               .
    //                              .
    //                             .
    //                            .
    //                           .
    //                          .
    //                         ... Y <<<<<<<<<<<<<<<<<<<<< Y
    //                             |                       |
    //                       lo2 + (n1-1)/2               lo2
    //                             |
    //                            mi2a
    ///////////////////////////////////////////////////////////////////////
    int mi1  = lo1 + n1 / 2;
    int mi2a = lo2 + ( n1 - 1 ) / 2;
    int mi2b = lo2 + n2 - 1 - n1 / 2;
    if ( S1[mi1] > S2[mi2b] ) //取S1左半、S2右半
        return median ( S1, lo1, n1 / 2 + 1, S2, mi2a, n2 - ( n1 - 1 ) / 2 );
    else if ( S1[mi1] < S2[mi2a] ) //取S1右半、S2左半
        return median ( S1, mi1, ( n1 + 1 ) / 2, S2, lo2, n2 - n1 / 2 );
    else //S1保留，S2左右同时缩短
        return median ( S1, lo1, n1, S2, mi2a, n2 - ( n1 - 1 ) / 2 * 2 );
}

//问题：在无序向量中，若有一半以上的元素同为m, 则称之为主流数（majority）
//算法1：减而治之
int majEleCandidate ( vector<int> A );
bool majEleCheck ( vector<int> A, int maj );

bool majority ( vector<int> A, int& maj ) { //众数查找算法：T可比较可判等
    maj = majEleCandidate ( A ); //必要性：选出候选者maj
    return majEleCheck ( A, maj ); //充分性：验证maj是否的确当选
}
int majEleCandidate ( vector<int> A ) { //选出具备必要条件的众数候选者
    int maj = 0; //众数候选者
    // 线性扫描：借助计数器c，记录maj与其它元素的数量差额
    for ( int c = 0, i = 0; i < A.size(); i++ )
        if ( 0 == c ) { //每当c归零，都意味着此时的前缀P可以剪除
            maj = A[i]; c = 1; //众数候选者改为新的当前元素
        } else //否则
            maj == A[i] ? c++ : c--; //相应地更新差额计数器
    return maj; //至此，原向量的众数若存在，则只能是maj —— 尽管反之不然
}
bool majEleCheck ( vector<int> A, int maj ) { //验证候选者是否确为众数
    int occurrence = 0; //maj在A[]中出现的次数
    for ( int i = 0; i < A.size(); i++ ) //逐一遍历A[]的各个元素
        if ( A[i] == maj ) occurrence++; //每遇到一次maj，均更新计数器
    return 2 * occurrence > A.size(); //根据最终的计数值，即可判断是否的确当选
}

//algorithm2: 只需要判断中位数是不是众数即可。两步：找到中位数，判断中位数是不是众数
bool g_bInputInvalid = false;

bool CheckInvalidArray(int* numbers, int length)
{
    g_bInputInvalid = false;
    if(numbers == NULL && length <= 0)
        g_bInputInvalid = true;
    
    return g_bInputInvalid;
}

bool CheckMoreThanHalf(int* numbers, int length, int number)
{
    int times = 0;
    for(int i = 0; i < length; ++i)
    {
        if(numbers[i] == number)
            times++;
    }
    
    bool isMoreThanHalf = true;
    if(times * 2 <= length)
    {
        g_bInputInvalid = true;
        isMoreThanHalf = false;
    }
    
    return isMoreThanHalf;
}

int partition ( int* A, int lo, int hi ) ;
int MoreThanHalfNum_Solution1(int* numbers, int length)  //直接判断中位数n/2满不满足条件即可
{
    if(CheckInvalidArray(numbers, length))
        return 0;
    
    int middle = length >> 1;
    int start = 0;
    int end = length - 1;
    int index = partition(numbers, start, end);
    
    
    while(index != middle)          //这与快排就不一样了
    {
        if(index > middle)
        {
            end = index - 1;
            index = partition(numbers, start, end);
        }
        else
        {
            start = index + 1;
            index = partition(numbers, start, end);
        }
    }
    
    
    
    int result = numbers[middle];
    if(!CheckMoreThanHalf(numbers, length, result))
        result = 0;
    
    return result;
}

//还有一种比较巧妙的方法
//a代表数组，length代表数组长度，median/majority
int FindOneNumber(int* a, int length)   //这个的前提是一定存在众数
{
    int candidate = a[0];
    int nTimes = 1;
    for (int i = 1; i < length; i++)
    {
        if (nTimes == 0)
        {
            candidate = a[i];
            nTimes = 1;
        }
        else
        {
            if (candidate == a[i])
                nTimes++;
            else
                nTimes--;
        }
    }
    return candidate;
}


//如果是要经常得到一组数组的中位数的话(数据是不断变化的,这种应用场景很普遍)，以上的方法的都不是增量的，建立最大最小堆来随时列举中位数
/*
 可以用最大堆和最小堆来解答这个问题：
 1.假设当前的中位数为m，其中最大堆维护的是<=m的数字序列，最小堆维护的是>=m的数字序列，但是两个堆都不包含m
 2.当新的数字到达时，比如为a，将a与m进行比较，若a<=m 则将其加入到最大堆中，否则将其加入到最小堆中
 3.如果此时最小堆和最大堆的元素个数的差值>=2 ，则将m加入到元素个数少的堆中，然后从元素个数多的堆将根节点赋值到m，最后重建两个最大堆和最小堆，返回到2
 */
namespace median_max-minHeap {  //min-max heap

class Median{
private:
    priority_queue<int,vector<int>,less<int> > max_heap;//左边的数
    priority_queue<int,vector<int>,greater<int> > min_heap;//右边的数
    
public:
    void Insert(int v);
    int GetValue();
};

void Median::Insert(int v){
    if(max_heap.empty() && min_heap.empty())
        max_heap.push(v);
    // max_heap不为空，则往max_heap插入数据，
    // 往min_heap插入数据的话可能导致较小的数放到右边的堆
    else if(!max_heap.empty() && min_heap.empty())
        max_heap.push(v);
    else if(max_heap.empty() && !min_heap.empty())
        min_heap.push(v);
    else{
        if(v < max_heap.top())
            max_heap.push(v);
        else
            min_heap.push(v);
    }
    //调整，保证两个堆的元素数量差别不大于1
    //不要用hmax_heap.size()-min_heap.size()>1
    //因为size返回的是unsigned类型，当左边相减得到一个负数时，本来为false
    //但会被转为一个大的正数，结果为true，出问题
    while(max_heap.size() > min_heap.size()+1){
        int data = max_heap.top();
        min_heap.push(data);
        max_heap.pop();
    }
    while(min_heap.size() > max_heap.size()+1){
        int data = min_heap.top();
        max_heap.push(data);
        min_heap.pop();
    }
}

int Median::GetValue(){//中位数为int，由于有除法，也可改为float
    if(max_heap.empty() && min_heap.empty())
        return (1<<31); //都为空时，返回int最小值
    if(max_heap.size() == min_heap.size())
        return (max_heap.top()+min_heap.top()) / 2;
    else if(max_heap.size() > min_heap.size())
        return max_heap.top();
    else
        return min_heap.top();
}

int main_median(){
    srand((unsigned)time(0));
    Median md;
    // vector<int> vi;
    // int num = rand() % 30; //数量是30以内的随机数
    // for(int i=0; i<num; ++i){
    //     int data = rand() % 100; //元素是100内的数
    //     vi.push_back(data);
    //     md.Insert(data);
    // }
    // sort(vi.begin(), vi.end());
    // for(int i=0; i<num; ++i)
    //     cout<<vi.at(i)<<" "; //排序的序列
    md.Insert(3);
    md.Insert(1);
    md.Insert(2);
    cout<<endl<<md.GetValue()<<endl; //中位数
    return 0;
}

}

//问题：排序
//算法：quicksort
//Quicksort is typically over twice as fast as merge sort
//Quicksort behaves well even with caching and virtual memory

int partition_2 ( int* A, int lo, int hi ) { //版本A：基本形式
    swap ( A[lo], A[lo + rand() % ( hi - lo) ] ); //任选一个元素与首元素交换
    int pivot = A[lo]; //以首元素为候选轴点——经以上交换，等效于随机选取
    while ( lo < hi ) { //从向量的两端交替地向中间扫描
        while ( ( lo < hi ) && ( pivot <= A[hi] ) ) //在不小于pivot的前提下
            hi--;           //向左拓展右端子向量
        A[lo] = A[hi]; //小于pivot者归入左侧子序列
        while ( ( lo < hi ) && ( A[lo] <= pivot ) ) //在不大于pivot的前提下
            lo++;           //向右拓展左端子向量
        A[hi] = A[lo]; //大于pivot者归入右侧子序列
    }                   //assert: lo == hi
    A[lo] = pivot; //将备份的轴点记录置于前、后子向量之间
    return lo; //返回轴点的秩
}

//这一版本是按照算法导论的伪代码写的，太经典了
int partition(int* A, int left, int right) {
    int pivot = A[left];    //swap(A[left], A[left + rand() % (right - left)]);
    int i = left;
    for (int j = left + 1; j <= right; j++)
        if (A[j] <= pivot)
            swap(A[++i], A[j]);
    swap(A[left], A[i]);
    return i;
}
void quickSort (int* A, int lo, int hi ) {
    if ( lo < hi ) {
        int mi = partition( A, lo, hi);
        quickSort ( A, lo, mi - 1 );
        quickSort ( A, mi + 1, hi );
    }
}

//这里的partition新建了节点
ListNode* partitionList(ListNode* pHead, int x)
{
    // write code here, listpartition
    if(pHead==nullptr)
        return nullptr;
    ListNode *pNode = pHead;
    ListNode *small = new ListNode(0);
    ListNode *big = new ListNode(0);
    ListNode *ptr1 = small;
    ListNode *ptr2 = big;
    while(pNode)
    {
        if(pNode->val < x)
        {
            ptr1->next = pNode;
            ptr1 = ptr1->next;
            ptr1->next = nullptr;
        }
        else
        {
            ptr2->next = pNode;
            ptr2 = ptr2->next;
            ptr2->next = nullptr;
        }
        
        pNode = pNode->next;
    }
    
    ptr1->next = big->next;
    return small->next;
}

//问题：串匹配算法
//算法1：brute force
int stringMatch(char* P, char* T){
    size_t n = strlen(T), i = 0; //文本串长度
    size_t m = strlen(P), j = 0; //模式串长度
    while ( j < m && i < n) {
        if (T[i] == P[j])
        {   i ++; j--; }
        else
        {   i -= j - 1; j = 0; }
    }
    return (int)(i - j);
}

//算法2：brute force
int stringMatch2(char* P, char* T){
    size_t n = strlen(T), i = 0;
    size_t m = strlen(P), j = 0;
    while ( j < m && i < n) {
        if (T[i + j] == P[j])
            j++;
        else
        {   i ++; j = 0; }
    }
    return (int)(i - j);
}

//算法3：KMP
int* buildNext(char* P);
int KMP_stringMatch ( char* P, char* T ) {  //KMP算法
    int* next = buildNext ( P ); //构造next表
    int n = ( int ) strlen ( T ), i = 0; //文本串指针
    int m = ( int ) strlen ( P ), j = 0; //模式串指针
    while ( j < m  && i < n ) //自左向右逐个比对字符
        if ( 0 > j || T[i] == P[j] ) //若匹配，或P已移出最左侧（两个判断的次序不可交换）
        { i ++;  j ++; } //则转到下一字符
        else //否则
            j = next[j]; //模式串右移（注意：文本串不用回退）
    delete [] next; //释放next表
    return i - j;
}

int* buildNext ( char* P ) { //构造模式串P的next表
    size_t m = strlen ( P ), j = 0; //“主”串指针
    int* N = new int[m]; //next表
    int t = N[0] = -1; //模式串指针
    while ( j < m - 1 )
        if ( 0 > t || P[j] == P[t] ) { //匹配
            j ++; t ++;
            N[j] = t; //此句可改进...
        } else //失配
            t = N[t];
    return N;
}




//写成模板、标准类的形式
template <typename T>
class StackWithMin {
public:
    StackWithMin(void) {}
    virtual ~StackWithMin(void) {}
    
    T& top(void);
    const T& top(void) const;
    
    void push(const T& value);
    void pop(void);
    
    const T& min(void) const;
    
    bool empty() const;
    size_t size() const;
    
private:
    std::stack<T>   m_data;     //
    std::stack<T>   m_min;      //
};

template <typename T> void StackWithMin<T>::push(const T& value)
{
    //
    m_data.push(value);
    
    if(m_min.size() == 0 || value < m_min.top())
        m_min.push(value);
    else
        m_min.push(m_min.top());
}

template <typename T> void StackWithMin<T>::pop()
{
    assert(m_data.size() > 0 && m_min.size() > 0);
    
    m_data.pop();
    m_min.pop();
}


template <typename T> const T& StackWithMin<T>::min() const
{
    assert(m_data.size() > 0 && m_min.size() > 0);
    
    return m_min.top();
}

template <typename T> T& StackWithMin<T>::top()
{
    return m_data.top();
}

template <typename T> const T& StackWithMin<T>::top() const
{
    return m_data.top();
}

template <typename T> bool StackWithMin<T>::empty() const
{
    return m_data.empty();
}

template <typename T> size_t StackWithMin<T>::size() const
{
    return m_data.size();
}


//问题：使用两个堆栈来实现队列
//算法：一个负责入队，一个负责出队
class DoubleStack2Queue {
public:
    stack<int> s1;
    stack<int> s2;
    int push(int x)
    {
        s1.push(x);
        return x;
    }
    
    void pop()
    {
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        s2.pop();
    }

};


//问题：找出一个大小为n的数组里面最大的k个数
//算法1：建立一个大小为k的堆，复杂度为O(k + (n-k)logk)~O(nlogk)
#define PARENT(i) (i)/2
#define LEFT(i) 2*(i)+1
#define RIGHT(i) 2*(i+1)

void swap ( int * a , int * b )
{
    int tmp;
    tmp = * a;
    * a = * b ;
    * b = tmp;
}

void max_heapify ( int * arr , int index , int len )
{
    int l = LEFT ( index ) ;
    int r = RIGHT ( index ) ;
    int largest ;
    if ( l < len && arr [ l ] > arr [ index ] )
        largest = l ;
    else
        largest = index ;
    if ( r < len && arr [ r ] > arr [ largest ] )
        largest = r ;
    if ( largest != index ) { //将最大元素提升，并递归
        swap ( & arr [ largest ] , & arr [ index ] ) ;
        max_heapify ( arr , largest , len ) ;
    }
}

void build_maxheap ( int * arr , int len )
{
    int i ;
    if ( arr == NULL || len <= 1 )
        return ;
    for ( i = len / 2 + 1 ; i >= 0 ; -- i )
        max_heapify ( arr , i , len ) ;
}

void k_min ( int * arr , int len , int k )
{
    int i ;
    build_maxheap ( arr , k ) ;
    for ( i = k ; i < len ; i ++ )
    {
        if ( arr [ i ] < arr [ 0 ] )
        {
            arr [ 0 ] = arr [ i ] ;
            max_heapify ( arr , 0 , k ) ;
        }
    }
}

//堆排序
void heap_sort(int *arr,int len)
{
    int i;
    if(arr==NULL || len<=1)
        return;
    build_maxheap(arr,len);
    
    for(i=len-1;i>=1;--i){
        swap(&arr[0],&arr[i]);
        max_heapify(arr,0,--len);
    }
}

//算法2：运用类似快速排序的Partition规则快速选择出最小的k各元素
int k_big ( int arr [ ] , int low , int high , int k )
{
    int pivot    = arr [ low ] ;
    int high_tmp = high ;
    int low_tmp = low ;
    
    while ( low < high ) {
        //从右向左查找，直到找到第一个小于枢纽元素为止
        while ( low < high && arr [ high ] >= pivot )
        {
            -- high ;
        }
        arr [ low ] = arr [ high ] ;        //这里把第一个数抠出来了
        //从左向右查找，直到找到第一个大于枢纽元素为止
        while ( low < high && arr [ low ] <= pivot )
        {
            ++ low ;
        }
        arr [ high ] = arr [ low ] ;
    }
    arr [ low ] = pivot ;
    
    /*这个也可以

    int i = low, j = low+1, x = arr[low];
    for (j = low + 1; j <= high-low; j++)
        if (arr[j] <= x)
            swap(arr[i++], arr[j]);
    swap(arr[low], arr[i]);
    */
    if ( low == k - 1 )
    {
        return arr [ low ] ;
    } else if ( low > k - 1 )
    {
        return k_big ( arr , low_tmp , low - 1 , k ) ;
    } else
    {
        return k_big ( arr , low + 1 , high_tmp , k - low ) ;
    }
}

//算法3：算法2的迭代版本，很好理解
void quickSelect ( vector<int> & A, int k ) {       //基于快速划分的k选取算法
    for ( int lo = 0, hi = (int)A.size() - 1; lo < hi; ) {
        int i = lo, j = hi;
        int pivot = A[lo];
        while ( i < j ) {                           //O(hi - lo + 1) = O(n)
            while ( ( i < j ) && ( pivot <= A[j] ) ) j--; A[i] = A[j];
            while ( ( i < j ) && ( A[i] <= pivot ) ) i++; A[j] = A[i];
        }                                           //assert: i == j
        A[i] = pivot;
        if ( k <= i ) hi = i - 1;
        if ( i <= k ) lo = i + 1;
    } //A[k] is now a pivot
}



//问题：最大间隙问题
//算法：采用桶结构

#define MAXINT INT_MAX
#define MININT INT_MIN
typedef struct _bucket
{
    int min, max;
} Bucket;

int maxGap(int *a, int n)
{
    int max = MININT, min = MAXINT, i;
    double bucketLen;
    for(i = 0; i < n; ++i)
    {
        if(a[i] > max) max = a[i];
        if(a[i] < min) min = a[i];
    }
    bucketLen = (max-min) * 1.0 / (n-1);
    Bucket *bucket = new Bucket[n-1];
    for(i = 0; i < n-1; ++i)
    {
        bucket[i].max = MININT;
        bucket[i].min = MAXINT;
        
    }
    bucket[0].max = min; bucket[0].min = min;
    bucket[n-2].max = max; bucket[n-2].min = max;
    for(i = 0; i < n; ++i)
    {
        int index;
        if(a[i] != min && a[i] != max)
        {
            index = (a[i]-min) * 1.0 / bucketLen;
            if(bucket[index].max < a[i]) bucket[index].max = a[i];
            if(bucket[index].min > a[i]) bucket[index].min = a[i];
        }
    }
    int low = -1, high = -1, maxGap = 0, curGap, pre = 0;
    for(i = 1; i < n-1; ++i)
    {
        if(bucket[i].max != MININT)
        {
            curGap = bucket[i].min - bucket[pre].max;
            if(curGap > maxGap)
            {
                maxGap = curGap;
                low = bucket[pre].max, high = bucket[i].min;
            }
            pre = i;
        }
    }
    printf("the maximum gap is %d, between %d and %d!\n", maxGap, low, high);
    return maxGap;
}


//问题：判断两个序列是否可以组成一个入栈一个出栈序列
//算法：模拟堆栈即可，如果当前要出栈的元素敲好在栈顶，则必须出栈，否则就入栈
bool isPossible(vector<int> &in, vector<int> &out)
{
    stack<int> s;
    for (int i = 0, j = 0; j < out.size(); ++j) {
        while (s.empty() || s.top() != !out[j]) {
            if (i >= in.size())
                return  false;
            s.push(in[i++]);
        }
        s.pop();
    }
    return true;
}


//问题：统计整数二进制展开中数位1的总数
//算法：复杂度为logn
int countOnes ( unsigned int n ) {
    int ones = 0; //计数器复位
    while ( 0 < n ) { //在n缩减至0之前，反复地
        ones += ( 1 & n ); //检查最低位，若为1则计数
        n >>= 1; //右移一位
    }
    return ones; //返回计数
} //等效于glibc的内置函数int __builtin_popcount (unsigned int n)

//算法：O(ones)正比于数位1的总数
int countOnes1 ( unsigned int n ) { //
    int ones = 0; //计数器复位
    while ( 0 < n ) { //在n缩减至0之前，反复地
        ones++; //计数（至少有一位为1）
        n &= n - 1; //清除当前最靠右的1
    }
    return ones; //返回计数
} //等效于glibc的内置函数int __builtin_popcount (unsigned int n)

//problem: 翻转比特，bitreverse
uint32_t reverseBits(uint32_t n) {
    uint32_t res = 0;
    for (int i = 0; i < 32; ++i) {
        if (n & 1 == 1) {
            res = (res << 1) + 1;
            n = n >> 1;
        } else {
            res = res << 1;
            n = (n >> 1);
        }
    }
    return res;
}

uint32_t reverseBits2(uint32_t n) {
    uint32_t m=0;
    for(int i=0;i<32;i++){
        m<<=1;
        m = m|(n & 1);
        n>>=1;
    }
    return m;
}
//问题：求最大公约数
//算法：辗转相除法
int gcd1(int a, int b)
{
    while (true) {
        if (0 == a) return b;
        if (0 == b) return a;
        if (a > b)         a %= b;
        else               b %= a;
    }
}
//上述除法的计算需要很多的时钟周期，改为减法
int gcd2(int x, int y)
{
    if(x < y)
        return gcd2(y, x);
    if(y == 0)
        return x;
    else
        return gcd2(x - y, y);
}

//problem: 最小公倍数
//algorithm: 通过最大公约数来求最小公倍数
int gcd_3(int m, int n) {
    return m / gcd1(m, n) * n;
}


//减法造成递归的深度加深，能不能融合gcd1和gcd2,采用
inline bool IsEven(int x) {
    return (x & 1) == 0;
}
int gcd3(int x, int y)
{
    if(x < y)
        return gcd3(y, x);
    if(y == 0)
        return x;
    else
    {
        if(IsEven(x))
        {
            if(IsEven(y))
                return (gcd3(x >> 1, y >> 1) << 1);
            else
                return gcd3(x >> 1, y);
        }
        else
        {
            if(IsEven(y))
                return gcd3(x, y >> 1);
            else
                return gcd3(y, x - y);
        }
    }
}

//count the primes;
int countPrimes(int n) {
    bool* isPrime = new bool[n];
    for (int i = 0; i < n; i++) {
        //这个使用memset(isPrime, true, n * sizeof(bool))快多了
        isPrime[i] = true;
    }
    for (int i = 2; i*i < n; i++) {
        if (!isPrime[i])
            continue;
        for (int j = i*i; j < n; j += i) { //消除i的整数倍元素
            isPrime[j] = false;
        }
    }
    
    int count = 0;
    for (int i = 2; i < n; i++) {
        if(isPrime[i]) count++;
    }
    return count;
    
}
/*
 Given an array of n integers where n > 1, nums, return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].
 
 Solve it without division and in O(n).
 
 For example, given [1,2,3,4], return [24,12,8,6].
 
 Follow up:
 Could you solve it with constant space complexity? (Note: The output array does not count as extra space for the purpose of space complexity analysis.)
 
 题意：
 
 　　给定一个数组，对于数组中每一个元素i，求ret[i] = nums[0]*nums[1]...*nums[i-1]*nums[i+1]*...*nums[len-1]。不能用除法，要求时间复杂度O(n).
 
 思路：
 
 　　先由左到右的顺序求每个元素左边乘积（ret[i] = nums[0]*nums[1]...*nums[i-1]），在其结果上由右到左求每个元素右边乘积（ret[i] = ret[i]*nums[i+1]*...*nums[len-1]）即可，其中nums[0]*nums[1]...*nums[i-1]以及nums[i+1]*...*nums[len-1]都可由常量连乘得到。
 */
class Solution_productExceptSelf {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        
        int len = (int)nums.size(), temp;
        vector<int> ret(len, 1);
        
        temp = 1;
        for(int i = 1; i < len; i++)
        {
            temp *= nums[i - 1];
            ret[i] *= temp;
        }
        
        temp = 1;
        for(int i = len - 2; i >= 0; i--)
        {
            temp *= nums[i + 1];
            ret[i] *= temp;
        }
        
        return ret;
    }
};



//问题：判断多个括号是否匹配
//算法：利用压栈、出栈操作来匹配
bool paren(const char exp[])
{
    std::stack<char> s;
    int i = 0;
    while (exp[i++]) {
        if ('(' == exp[i]) {
            s.push(exp[i]);
        }else if (s.empty() )
            return false;
        else
            s.pop();
    }
    return s.empty();
}

void convert(std::stack<char> &stk, int n, int base)
{
    static char digit[] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        'A', 'B', 'C', 'D', 'E', 'F'
    };
    while (n > 0) {
        stk.push(digit[n%base]);
        n /= base;
    }
}


//问题： 快速排序
//算法： 桶排序
#define CAPACITY 10
struct barrel {
    int node[CAPACITY];
    int count;/* the num of node */
};
extern void quick_sort(int a[], int p, int q);/* not necessary */
void bucket_sort(int data[], int size)
{
    int max, min, num, pos;
    int i, j, k;
    struct barrel *pBarrel;
    
    max = min = data[0];
    for (i = 1; i < size; i++) {
        if (data[i] > max) {
            max = data[i];
        } else if (data[i] < min) {
            min = data[i];
        }
    }
    num = (max - min + 1) / 10 + 1;
    
    pBarrel = (struct barrel*)malloc(sizeof(struct barrel) * num);
    memset(pBarrel, 0, sizeof(struct barrel) * num);
    
    /* put data[i] into barrel which it belong to */
    for (i = 0; i < size; i++) {
        k = (data[i] - min + 1) / 10;/* calculate the index of data[i] in barrel */
        (pBarrel + k)->node[(pBarrel + k)->count] = data[i];
        (pBarrel + k)->count++;
    }
    
    pos = 0;
    for (i = 0; i < num; i++) {
        struct barrel* tmp = pBarrel + i;
        sort(tmp->node, tmp->node + tmp->count );/* sort node in every barrel */
        
        for (j = 0; j < (pBarrel+i)->count; j++) {
            data[pos++] = (pBarrel+i)->node[j];
        }
    }
    free(pBarrel);
}

//问题：排序问题
//算法：冒泡排序
void bubblesort(int A[], int n)
{
    while(n--)
    {
        for(int i = 0; i < n; i++)
            if(A[i] > A[i+1]) {
                std::swap(A[i], A[i+1]);
            }
    }
}

//问题: sort
//算法: merge sort
void merge(int a[], int lo, int mid, int hi)
{
    int *A = a + lo;
    //A array 的值会复制到B array中，然后merge B array and C array into the start of A.s
    int lb = mid - lo; //the length of B array
    int *B = (int*)malloc(lb * sizeof(int));
    for (int i = 0; i < lb; i++)
        B[i] = A[i];
    
    int lc = hi - mid;//length of C array
    int *C = a + mid;
    int i = 0, j = 0, k = 0; //A---i, B---j, C---k
    while (j < lb && k < lc) {
        while (j < lb && B[j] <= C[k]) A[i++] = B[j++];
        while (k < lc && C[k] <= B[j]) A[i++] = C[k++];
    }
    while ( j < lb ) A[i++] = B[j++];
    free(B);
}

void mergeSort(int A[], int lo, int hi)
{
    if (lo < hi) {
        
        int mid = (lo + hi)>>1;
        mergeSort(A, lo, mid);
        mergeSort(A, mid+1, hi);
        merge(A, lo, mid, hi);
    }
}

//算法：shellsort
void ShellSort(int a[], int n){
    int gap, i, j, temp;
    for (gap = n/2; gap >= 1; gap = gap/2){
        for (i = gap; i < n; i++) {
            temp = a[i];
            for (j = i; (j >= gap) && (a[j - gap] > temp); j = j-gap){
                a[j] = a[j - gap];
            }
            a[j] = temp;
        }
    }
}

//algorithm: counting sort
#define SIZE 65453  //计数排序的一个缺点就是必须先知道数列的最大值，比如对一串字母序列进行排序
void countingSort(int A[], int B[], int n){
    int C[SIZE];
    memset(C, 0, sizeof(int)*SIZE);
    
    for (int i = 0; i < n; i++)
        C[A[i]]++;
    
    for (int i = 0; i < SIZE; i++)
        C[i] = C[i] + C[i-1];
    
    for (int i = n-1; i >= 0; i--)  //从数组的末尾往开头扫描，依次处理
    {
        B[C[A[i]]] = A[i];
        C[A[i]] = C[A[i]] - 1;
    }
}


//问题: binsearch
//算法: binary search

//两种写法的差异如下：search1和search2
int search1(int array[], int n, int v)  //左闭右闭
{
    int left, right, middle;
    
    left = 0, right = n - 1;    ///差别1,多了三处
    
    while (left <= right)       //差别2
    {
        middle = (left + right) / 2;
        if (array[middle] > v){
            right = middle - 1; //差别3
        }
        else if (array[middle] < v){
            left = middle + 1;
        }
        else{
            return middle;
        }
    }
    
    return -1;
}

int search2(int array[], int n, int v)  //左闭右开
{
    int left, right, middle;
    
    left = 0, right = n;   ///差别1
    
    while (left < right)    //差别2
    {
        middle = left + (right - left) / 2;
        
        if (array[middle] > v)
        {
            right = middle; //差别3
        }
        else if (array[middle] < v)
        {
            left = middle + 1;
        }
        else
        {
            return middle;
        }
    }
    
    return -1;
}


//变形：find peak element eg: 1 2 3 2 1        //如果最大值有重复怎么办
int findPeakElement(const vector<int> &num) {
    int left = 0;
    int right = num.size()-1;
    while(left <= right){
        if(left == right)           //这里有一个结束条件，注意
            return left;
        int mid = (left+right)/2;
        if(num[mid] < num[mid+1])   //将中间值与右边的值进行比较
            left = mid+1;
        else
            right = mid;
    }
}
//以上的findPeakelement变形为：given a list of elements arranged in ascending and then descending order(e.g. 1,3,5,7,6,4,2), write a function to determine if a target number in in this list.

//不适用递归，如果存在返回数组位置，不存在则返回-1
int binSearch3(int arry[],int len,int value)
{
    //如果传入的数组为空或者数组长度<=0那么就返回-1。防御性编程
    if(arry == NULL||len<=0)
        return -1;
    
    int start = 0;
    int end = len-1;
    
    while(start<=end)//判断清是否有=
    {
        int mid = start + (end-start)/2;
        if(arry[mid] == value)
            return mid;
        else if(value < arry[mid])
            end = mid - 1;        //这里的减一与判断条件中的等号一一对应，这里有减号，前面就要有等号，比如1，2，3，4要找1，因为/符号是向下取整
        else
            start = mid + 1;
    }
    return -1;
    
}

int BinarySearchRecursion(int arry[],int &value,int &start,int &end)
{
    if(start>end)
        return -1;
    
    int mid=start+(end-start)/2;
    if(arry[mid]==value)
        return mid;
    else if(value<arry[mid])
    {
        end = mid - 1;
        return BinarySearchRecursion(arry,value,start,end);
    }
    else
    {
        start = mid + 1;
        return BinarySearchRecursion(arry,value,start,end);
    }
}

int BinarySearchRecursion(int arry[],int &len,int &value)
{
    //如果传入的数组为空或者数组长度<=0那么就返回-1。防御性编程
    if(arry==NULL||len<=0)
        return -1;
    int start=0;
    int end=len-1;
    return  BinarySearchRecursion(arry,value,start,end);
}

void binSearch_main()
{
    int arry[]={1,2,3,4,5,6,7,8};
    int len=sizeof(arry)/sizeof(int);
    int especteNum1=4;
    int especteNum2=9;
    int index=binSearch3(arry,len,especteNum1);
    cout<<"index:"<<index<<endl;
    
    int index2=BinarySearchRecursion(arry,len,especteNum2);
    cout<<"index2:"<<index2<<endl;

}

//problem: shifted Binary Search 3, 4, 5, 6, 7, 8, 1, 2
//algorithm: recursion
int shiftedBinsearch(int a[], int x, int low, int high) {
    
    if (low > high) return -1;
    int mid = low + (high-low)/2;
    
    if (a[mid] == x)
        return mid;
    else if (a[low] < x && x <= a[mid])
        return shiftedBinsearch(a, x, mid + 1, high);
    else
        return shiftedBinsearch(a, x, low, mid - 1);
    return -1;
}
//algorithm2: nonrecursion，这与上面的二分查找类似，边界条件都差不多，只是需要再次判断
int binsearch_rotated(vector<int>& nums, int target) {
    int n = nums.size();
    assert(n > 0);
    int left = 0;
    int right  = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target)
            return mid;
        if (nums[mid] >= nums[left])  {      //左半部分有序，注意这里都要用到等号
            if (target >= nums[left] && target < nums[mid])
                right = mid - 1;
            else
                left  = mid + 1;
        }
        else {                              //总有一半有序
            if (target > nums[mid] && target <= nums[right])
                left = mid + 1;
            else
                right = mid - 1;
        }
    }
    return -1;
    
}


//问题：去除一个数组中相同的值
//算法：将与前一个元素不同的元素直接放在数组的开端处的指针叠加
int uniquefy(int A[], int n)
{
    int i = 0, j = 0;
    while (++j < n)
        if (A[i] != A[j])
            A[++i] = A[j];
    return i+1; //返回元素的个数
}

int disordered(int A[], int n)
{
    int num = 0;
    for (int i = 0; i < n; i++)
        num += (A[i-1] > A[i]);
    return num;
}

//问题：快速计算幂指数
//算法：分解指数n
inline bool doubleEqual(double x, double t) {
    return ( x - t ) < 0.000000001 && ( x - t ) > - 0.000000001;
}
double quickPower(double x, int n) //这个在leetcode上面会超时
{
    //没检查边界条件和错误输入
    //有三种错误处理方式：返回值、全局变量和异常
    if (doubleEqual(x, 0.0) && n < 0)
        return 0.0;
    
    if (n < 0)
        return 1.0 / quickPower(x, -n);
    double result = 1;
    while (0 < n) {
        if (n & 1)  result *= x;
        n >>= 1;
        x *= x;
    }
    return result;
    
}
//算法2：分治法，与mergesort思路完全一样
double quickPower3(double x, int n) {
    if (n == 0) return 1.0;
    double result = 1.0;
    double tmp = quickPower3(x, n/2);
    if ( n % 2 == 0)
        return tmp * tmp;
    else
        return x * tmp * tmp;
}
double quickPower2(double x, int n) {
    if (n < 0)
        return 1.0 / quickPower2(x, -n); //这个不能处理n取最大负数的情况，会有bug，与itoa类似,
                                        //只是这里，但是潜在隐患存在: (-INT_MIN) == INT_MIN
    else
        return quickPower3(x, n);
}

//问题：implement sqrt
//算法：二分查找
int quickSqrt(int x) {
    if (x < 2) return x;
    int left = 1, right = x / 2; //right没必要再往上搜索了
    int last_mid = 0;
    while (left <= right) {
        const int mid = left + (right-left)/2;
        if (x / mid > mid) {//不要用x > mid * mid会溢出
            left = mid + 1;
            last_mid = mid;    //这是找整数。。。。。下面的newton法才能找到
        }else if (x / mid < mid) {
            right = mid - 1;
        }else
            return mid;
    }
    return last_mid;
}
//算法：牛顿法
//X(n+1)=[X(n)+p/Xn]/2
double NewTon_sqrt(double n) {
    double k = 1.0;
    while(abs(k*k-n) > 1e-9) {
        k = (k+n/k)/2;          //精髓：X(n+1)=[X(n)+p/Xn]/2
    }
    return k;
}



//problem: 不用额外的变量颠倒一个字符串
//algorithm: 利用位运算
void reverseString(char* str){  //如果是char* str = "adnafn"，这是不能修改的，出错。可以改为传入为字符数组
    for(int i = 0,j = (int) strlen(str) - 1; i < j; i++, j--){
        str[i] = str[i] ^ str[j];
        str[j] = str[j] ^ str[i];
        str[i] = str[i] ^ str[j];
    }
}

void reverse(int* A, int lo, int hi)
//迭代版，一般用迭代版，以上的递归版效率较低
{
    while (lo < hi)
        std::swap(A[lo++], A[hi--]);
}
void shiftRight(int* A, int n, int k)
{
    k %= n;
    std::reverse(A,A+k);
    std::reverse(A+k, A+n);
    std::reverse(A, A+n);
}


//problem: 复制复杂链表结构
//algorithm：在原始链表上面clone再分离
struct ComplexListNode
{
    int                 m_nValue;
    ComplexListNode*    m_pNext;
    ComplexListNode*    m_pSibling;
};
//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//  |       |      /|\             /|\
//  --------+--------               |
//          -------------------------
void CloneNodes(ComplexListNode* pHead);
void ConnectSiblingNodes(ComplexListNode* pHead);
ComplexListNode* ReconnectNodes(ComplexListNode* pHead);

ComplexListNode* Clone(ComplexListNode* pHead)
{
    CloneNodes(pHead);
    ConnectSiblingNodes(pHead);
    return ReconnectNodes(pHead);
}

void CloneNodes(ComplexListNode* pHead)
{
    ComplexListNode* pNode = pHead;
    while(pNode != NULL)
    {
        ComplexListNode* pCloned = new ComplexListNode();
        pCloned->m_nValue = pNode->m_nValue;
        pCloned->m_pNext = pNode->m_pNext;
        pCloned->m_pSibling = NULL;
        
        pNode->m_pNext = pCloned;
        
        pNode = pCloned->m_pNext;
    }
}

void ConnectSiblingNodes(ComplexListNode* pHead)
{
    ComplexListNode* pNode = pHead;
    while(pNode != NULL)
    {
        ComplexListNode* pCloned = pNode->m_pNext;
        if(pNode->m_pSibling != NULL)
        {
            pCloned->m_pSibling = pNode->m_pSibling->m_pNext;
        }
        
        pNode = pCloned->m_pNext;
    }
}

ComplexListNode* ReconnectNodes(ComplexListNode* pHead)
{
    ComplexListNode* pNode = pHead;
    ComplexListNode* pClonedHead = NULL;
    ComplexListNode* pClonedNode = NULL;
    
    if(pNode != NULL)
    {
        pClonedHead = pClonedNode = pNode->m_pNext;
        pNode->m_pNext = pClonedNode->m_pNext;
        pNode = pNode->m_pNext;
    }
    
    while(pNode != NULL)
    {
        pClonedNode->m_pNext = pNode->m_pNext;
        pClonedNode = pClonedNode->m_pNext;
        
        pNode->m_pNext = pClonedNode->m_pNext;
        pNode = pNode->m_pNext;
    }
    
    return pClonedHead;
}

//
//problem: 只用一个变量来解决中国象棋将帅问题
//algorithm: 利用位运算，
#define HALF_BITS_LENGTH 4
// 这个值是记忆存储单元长度的一半，在这道题里是4bit
#define FULLMASK 255
// 这个数字表示一个全部bit的mask，在二进制表示中，它是11111111。
#define LMASK (FULLMASK << HALF_BITS_LENGTH)
// 这个宏表示左bits的mask，在二进制表示中，它是11110000。
#define RMASK (FULLMASK >> HALF_BITS_LENGTH)
// 这个数字表示右bits的mask，在二进制表示中，它表示00001111。
#define RSET(b, n) (b = ((LMASK & b) ^ n))
// 这个宏，将b的右边设置成n
#define LSET(b, n)  (b = ((RMASK & b) ^ (n << HALF_BITS_LENGTH)))
// 这个宏，将b的左边设置成n
#define RGET(b) (RMASK & b)
// 这个宏得到b的右边的值
#define LGET(b) ((LMASK & b) >> HALF_BITS_LENGTH)
// 这个宏得到b的左边的值
#define GRIDW 3
// 这个数字表示将帅移动范围的行宽度。

int general_main()
{
    unsigned char b;
    for(LSET(b, 1); LGET(b) <= GRIDW * GRIDW; LSET(b, (LGET(b) + 1)))
        for(RSET(b, 1); RGET(b) <= GRIDW * GRIDW; RSET(b, (RGET(b) + 1)))
            if(LGET(b) % GRIDW != RGET(b) % GRIDW)
                printf("A = %d, B = %d\n", LGET(b), RGET(b));
    
    return 0;
}

//algorithm2:
struct {
    unsigned char a:4;
    unsigned char b:4;
}i;
void general_main2(){
    for (i.a = 1; i.a<9; i.a++)
        for (i.b = 1; i.b<9; i.b++)
            if (i.a % 3 == i.b % 3)
                printf("A = %d, B = %d\n", i.a, i.b);
}

void shuffle ( int A[], int n ) { //将A[0, n)随机打乱
    while ( 1 < n )
        swap ( A[rand() % n], A[--n] );
}

void printLastKLines(ifstream &fin, int k){
    string line[k];
    int lines = 0;
    string tmp;
    while(getline(fin, tmp)){
        line[lines%k] = tmp;
        ++lines;
    }
    int start, cnt;
    if(lines < k){
        start = 0;
        cnt = lines;
    }
    else{
        start = lines%k;
        cnt = k;
    }
    for(int i=0; i<cnt; ++i)
        cout<<line[(start+i)%k]<<endl;
}

/*
 计算字符串表达式的值，表达式中只含有(,),+,-,空格和非负整数。例如：
 　　“1 + 1” = 2
 　　” 2-1 + 2 ” = 3
 　　“(1+(4+5+2)-3)+(6+8)” = 23
 */
//basic caculator
/*
 两个栈：
 
 一个存放操作数，每次进栈要注意，如果操作符栈顶元素为'+'/'-'，则需要立即计算。
 
 一个存放操作符（包括括号），每次出现')'时，不断进行出栈计算再进栈，直到弹出'('，说明当前括号内计算完毕。
 */
class Solution_caculator {
public:
    int calculate(string s) {
        stack<int> num; //两个栈，一个用来存储操作符，一个用来存储操作数
        stack<int> op;
        int i = 0;
        while(i < s.size())
        {
            while(i < s.size() && s[i] == ' ')
                i ++;
            if(i == s.size())
                break;
            if(s[i] == '+' || s[i] == '-' || s[i] == '(')
            {
                op.push(s[i]);
                i++;
            }
            else if(s[i] == ')')
            {
                while(op.top() != '(')
                {// calculation within parentheses
                    int n2 = num.top();
                    num.pop();
                    int n1 = num.top();
                    num.pop();
                    if(op.top() == '+')
                        num.push(n1 + n2);
                    else
                        num.push(n1 - n2);
                    op.pop();
                }
                op.pop();
                while(!op.empty() && op.top() != '(')
                {
                    int n2 = num.top();
                    num.pop();
                    int n1 = num.top();
                    num.pop();
                    if(op.top() == '+')
                        num.push(n1 + n2);
                    else
                        num.push(n1 - n2);
                    op.pop();
                }
                i ++;
            }
            else    //操作数时
            {
                int n = 0;
                while(i < s.size() && s[i] >= '0' && s[i] <= '9')
                {
                    n = n*10 + (s[i]-'0');
                    i ++;
                }
                num.push(n);
                while(!op.empty() && op.top() != '(')
                {
                    int n2 = num.top();
                    num.pop();
                    int n1 = num.top();
                    num.pop();
                    if(op.top() == '+')
                        num.push(n1 + n2);
                    else
                        num.push(n1 - n2);
                    op.pop();
                }
            }
        }
        return num.top();
    }
};


int GetNum(string poststr,int *i)
{
    int tmp =0;
    while(poststr[(*i)] >= ‘0‘ && poststr[(*i)] <= ‘9‘)
    {
        tmp = tmp*10 + ( poststr[(*i)] - ‘0‘);
        (*i) ++;
    }
    return tmp;
}

bool isBigEndian() {
    int x = 1;
    char* y = &x;
    return 1 == *y;
}

void hanoi(int n, char src, char bri, char dst){
    //第一个参数表示移动多少个第二个参数中的盘子
    if(n == 1){
        cout<<"Move disk "<<n<<" from "<<src<<" to "<<dst<<endl;
    }
    else{
        hanoi(n-1, src, dst, bri);
        cout<<"Move disk "<<n<<" from "<<src<<" to "<<dst<<endl;
        hanoi(n-1, bri, src, dst);
    }
}
int main_hanoi() {
    int n;
    scanf("%d", &n);
    printf("%d\n", (1 << n) - 1); /* 总次数 */
    hanoi(n, 'A', 'B', 'C');
    return 0;
}

//以下用递归来实现，每次要记录盘的状态

struct op{
    int begin, end;
    char src, bri, dst;
    op(){
        
    }
    op(int pbegin, int pend, int psrc, int pbri, int pdst):begin(pbegin), end(pend), src(psrc), bri(pbri), dst(pdst){
        
    }
};

void hanoi(int n, char src, char bri, char dst){
    stack<op> st;
    op tmp;
    st.push(op(1, n, src, bri, dst));
    while(!st.empty()){
        tmp = st.top();
        st.pop();
        if(tmp.begin != tmp.end){
            st.push(op(tmp.begin, tmp.end-1, tmp.bri, tmp.src, tmp.dst));
            st.push(op(tmp.end, tmp.end, tmp.src, tmp.bri, tmp.dst));
            st.push(op(tmp.begin, tmp.end-1, tmp.src, tmp.dst, tmp.bri));
        }
        else{
            cout<<"Move disk "<<tmp.begin<<" from "<<tmp.src<<" to "<<tmp.dst<<endl;
        }
        
    }
}


#endif
