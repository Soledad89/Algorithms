#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "algorithms.h"
#include "leetcode.h"
int N = 0;
int nCheck = 0;
int nSolu = 0;

int main( int argc, char* argv[] ) {
    
    N = 5;
    char pStr[] = "wangbo";
    Permutation(pStr);
    
    //placeQueens(N);
    //Astar_main();
    
    return 0;
    
    /*
    Print1ToMaxOfNDigits_1(4);
    
    char sch[20] = "wangbo is bob";
    ReplaceBlank(sch, 20);
    int x[] = {1, 2, 2,2, 3,4};
    countNum(x, 0, 5, 2);
    char a = 'a';
    char b = 'b';
    a = a^b;
    b = b^a;
    a = a^b;
    char ch[] = "abcdef"; //不能改为char* ch = "abcdef"，这是不可修改的，是字符串常量
    reverseString(ch);
    
    return 0;
    
    Node *head1 = NULL;
    Node *node1 = NULL,*node2 = NULL,*node3 = NULL,*node4 = NULL;
    head1 = (Node *)malloc(sizeof(Node));
    node1 = (Node *)malloc(sizeof(Node));
    node2 = (Node *)malloc(sizeof(Node));
    node3 = (Node *)malloc(sizeof(Node));
    node4 = (Node *)malloc(sizeof(Node));
    head1->data = 7;
    node1->data = 5;
    node2->data = 2;
    node3->data = 3;
    node4->data = 1;
    head1->next = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = NULL;
    
    head1 = linkedListMergeSort(head1);
    int i = 0;
    
    Node *head2 = NULL;
    Node *node5 = NULL,*node6 = NULL,*node7 = NULL,*node8 = NULL;
    head2 = (Node *)malloc(sizeof(Node));
    node5 = (Node *)malloc(sizeof(Node));
    node6 = (Node *)malloc(sizeof(Node));
    node7 = (Node *)malloc(sizeof(Node));
    node8 = (Node *)malloc(sizeof(Node));
    node5->data = 3;
    node6->data = 4;
    node7->data = 5;
    node8->data = 6;
    head2->next = node5;
    node5->next = node6;
    node6->next = node7;
    node7->next = node8;
    node8->next = NULL;
    //test:
    char* x = "abcd";
    char* y = "addcd";
    int m = LCS(x, y);
    */
    // int A[] = {1};
    //evenOddPartition(A, 6);
    return 0;
    /*
    WordDictionary wd;
    wd.addWord("abc");
    wd.addWord("a");
    wd.search(".");
    wd.search("a");
    wd.search("aa");
    wd.search("a");
    wd.search(".a");
    wd.search("a.");
    //test:
    vector<vector<int> > matrix(3);
    matrix = { {0,-2,-7,0}, {9,2,-6,2}, {-4,1,-4,1}, {-1, 8, 0, -2}};//这是横着排的，想着矩阵在内存中的存储顺序
    vector<int> col0 = matrix[0];
    vector<int> col1 = matrix[1];
    int nrow = (int) matrix.size();
    int ncol = (int) matrix[0].size();
    int ab = maxSubMatrix(matrix, nrow);
    //test:
    int i = 21;
    int j = 11;
    int xs = Add(i, j);
    
    int x = quickSqrt(100);
    int a =  INT_MIN;
    int b = -a;
    double n = quickPower(2, 5);
    
    //test:
    find_factor(10, 10);
    
    //test：
    char* s = (char*) malloc(sizeof(char) * 16);//假设整数最长是16位，每位占据一个字符
    memset(s, 0, sizeof(char) * 16);
    itoa(123131334, s);
    printf("%s", s);
    
    
    char c = firstSingleLetter(s);
    int i = '3' - '0';
    //test:
    vector<int> v = {1, 2, 3, 4, 6, 8};
    int n = findKthLargest2_1(v, 4);
    */
     //return 0;
    /*
    //test:
    vector<int> v = {1, 2, 3, 4, 6, 8};
    vector<int> w = {4, 5, 10, 1, 2, 3};
    int m;
    for (int i = 0; i < 12; i ++){
        m = bag01(v, w, i);
    }
    return 0;
    
    //test:
    string s = "ababacdadbabdacdca";
    int n = minCutNums(s);
    
    
    //test:
    
    BinaryTreeNode* b3 = new BinaryTreeNode(4, NULL, NULL);
    BinaryTreeNode* b4 = new BinaryTreeNode(7, NULL, NULL);
    BinaryTreeNode* b2 = new BinaryTreeNode(12, NULL, NULL);
    BinaryTreeNode* b1 = new BinaryTreeNode(5, b3, b4);
    BinaryTreeNode* root = new BinaryTreeNode(10, b1, b2);
    vector<int> path;
    int expectedSum = 22;
    int currentSum = 0;
    FindPath(root, expectedSum, currentSum, path);
    
    //test:
    vector<int> sc{ 2, 3, 6, 7};
    int target = 7;
    combinationSum(sc, target);
    
    //test:
    StackSuppliedMin<int>  ss;
    ss.push(3);
    ss.push(2);
    ss.push(6);
    ss.push(4);
    ss.push(1);
    ss.push(5);
    ss.pop();
    ss.pop();
    ss.pop();
    ss.push(1);
    ss.pop();
    ss.pop();
    ss.pop();
    ss.push(0);
    
    //test:
    string st = "wangbo";
    reverse(&st[0], &st[0] + st.size());
    
    //test:
    vector<int> v{2,1,5,6,2,3};
    int result = largestRectangleArea(v);
    //test:
    BSTreeNode * pRoot = NULL;
    pListIndex = NULL;
    pHead = NULL;
    addBSTreeNode(pRoot, 10);
    addBSTreeNode(pRoot, 4);
    addBSTreeNode(pRoot, 6);
    addBSTreeNode(pRoot, 8);
    addBSTreeNode(pRoot, 12);
    addBSTreeNode(pRoot, 14);
    addBSTreeNode(pRoot, 15);
    addBSTreeNode(pRoot, 16);
    ergodicBSTree(pRoot);
    
    //test: sysmmetric
    //测试：longest common prefix
    vector<string> strs = {"abdd", "abd", "abddd", "abcd"};
    string longest = longestCommonPrefix(strs);
     */
    /*
    //测试：KMP
    char* p = "wangbowan";
    char* t = "wan, bowan, wangbowawanbowangbowangwang";
    KMP_stringMatch(p, t);
    
    //测试：堆排序算法
    printf("\n");
    int arr [ 10 ] = { 91 , 8 , 6 , 82 , 15 , 18 , 7 , 46 , 29 , 12 } ;
    int i ;
    k_min ( arr , 10 , 4 ) ;
    for ( i = 0 ; i < 4 ; ++ i )
        printf ( "%d " , arr [ i ] ) ;
    
    //测试：stack conversion
    printf("\n");
    std::stack<char> stk;
    convert(stk, 15, 16);
    while (!stk.empty()) {
        printf("%c", (stk.top()));
        stk.pop();
    }
    
    //测试：Mergesort
    int n = 20; //array length
    if(1 < argc)
        n = atoi(argv[1]);
    if(n < 0) n = 0; //make sure length is non-negative
    int* A = (int*)malloc(n*sizeof(int)); //allocate an array of size n
    unsigned int seed = (unsigned int)time(NULL); //A same seed is used here for comparison between different algorithms
    double x = 2;
    double y = pow_(x, 10);
    printf("y: %lf", y);
    
    printf( "\n== mergeSort algorithm #0 ========\n" );
    randomArray( A, n, seed ); //create a randomized array using the same seed
    printf( "==>  " ); print( A, n );
    mergeSort( A, 0, n ); //sort the array
    printf( "==>  " ); print( A, n );
    int index = binsearch2(A, 10, 0, n);
    printf("index: %d\n", index);
    free(A); //release the array
 
    
    return 0;*/
}