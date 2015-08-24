//
//  Functions.h
//  Algorithm
//
//  Created by 王波 on 15/8/20.
//  Copyright (c) 2015年 wangbo. All rights reserved.
//

#ifndef Algorithm_Functions_h
#define Algorithm_Functions_h
#include <stack>
struct ListNode {
    int data;
    ListNode* pred;
    ListNode* succ;
    ListNode() {};
    ListNode(int e = 0, ListNode* p = NULL, ListNode* s = NULL):
    data(e), pred(p), succ(s){}
};
//ListNode* header;
//ListNode* trailer;
void convert(std::stack<char> &stk, int n, int base);
void bubblesort(int A[], int n);
void merge(int a[], int lo, int mid, int hi);
void mergeSort(int A[], int lo, int hi);
int binsearch(int A[], const int x, int lo, int hi);
int binsearch2(int A[], const int x, int lo, int hi);
double pow_(double x, int n);
void reverse(int* A, int lo, int hi);
void shift(int* A, int n, int k);
void shuffle( int A[], int n );
void shuffle( int A[], int lo, int hi );
void randomArray( int A[], int n, int seed );
void print( int A[], int n, int lo, int hi );
void print( int A[], int n );

#endif
