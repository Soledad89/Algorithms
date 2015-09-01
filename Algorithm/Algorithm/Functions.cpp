//
//  Functions.cpp
//  Algorithm
//
//  Created by 王波 on 15/8/20.
//  Copyright (c) 2015年 wangbo. All rights reserved.
//
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <stack>
#include "Functions.h"

int countOnes ( unsigned int n ) { //统计整数二进制展开中数位1的总数：O(logn)
    int ones = 0; //计数器复位
    while ( 0 < n ) { //在n缩减至0之前，反复地
        ones += ( 1 & n ); //检查最低位，若为1则计数
        n >>= 1; //右移一位
    }
    return ones; //返回计数
} //等效于glibc的内置函数int __builtin_popcount (unsigned int n)

int countOnes1 ( unsigned int n ) { //统计整数二进制展开中数位1的总数：O(ones)正比于数位1的总数
    int ones = 0; //计数器复位
    while ( 0 < n ) { //在n缩减至0之前，反复地
        ones++; //计数（至少有一位为1）
        n &= n - 1; //清除当前最靠右的1
    }
    return ones; //返回计数
} //等效于glibc的内置函数int __builtin_popcount (unsigned int n)



int gcdEU(int a, int b)
{
    while (true) {
        if (0 == a) return b;
        if (0 == b) return a;
        if (a > b)         a %= b;
        else               b %= a;
    }
}

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

void merge(int a[], int lo, int mid, int hi)
{
    int *A = a + lo;
    int lb = mid - lo; //B array的长度
    int *B = (int*)malloc(lb * sizeof(int));
    for (int i = 0; i < lb; i++)
        B[i] = A[i];
    
    int lc = hi - mid;//length of B array
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
    int num = hi - lo;
    if (num == 0 || num == 1)
        return;
    int mid = (lo + hi)>>1;
    mergeSort(A, lo, mid);
    mergeSort(A, mid, hi);
    merge(A, lo, mid, hi);
}

int binsearch_lowerbound(int A[], const int x, int lo, int hi){
    while (lo < hi) {
        int mid = (lo + hi)>>1;
        (x < A[mid]) ? mid = hi : lo = mid + 1;
    }
    return lo;
}
int binsearch2(int A[], const int x, int lo, int hi)
{
    while (1 < hi - lo) {
        int mid = (lo + hi) >> 1;
        (x < A[mid])? hi = mid : lo = mid;
    }
    return (x == A[lo]) ? lo : -1;
}
int binsearch(int A[], const int x, int lo, int hi)
{
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        if (x < A[mid])
            hi = mid;
        else if (A[mid] < x)
            lo = mid + 1;
        else
            return mid;
    }
    return -1;
}

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

double pow_(double x, int n)
{
    double result = 1;
    double tmp = x;
    while (0 < n) {
        if (n & 1)
            result *= tmp;
        n >>= 1;
        tmp *= tmp;
    }
    return result;
    
}

/*
 void reverse(int* A, int lo, int hi) //递归版，recursive
 {
 if(lo < hi)
 {
 std::swap(A[lo], A[hi]);
 reverse(A, lo+1, hi-1)
 }
 }
 */
void reverse(int* A, int lo, int hi) //迭代版，一般用迭代版，以上的递归版效率较低
{
    while (lo < hi)
        std::swap(A[lo++], A[hi--]);
}

void shift(int* A, int n, int k)
{
    k %= n;
    std::reverse(A,A+k);
    std::reverse(A+k, A+n);
    std::reverse(A, A+n);
}

void shuffle( int A[], int n ) {
    while ( 1 < n )
        std::swap ( A[rand() % n], A[--n] );
}

void shuffle( int A[], int lo, int hi )
{  shuffle ( A + lo, hi - lo );  }

void randomArray( int A[], int n, int seed ) {
    srand(seed);
    for ( int i = 0; i < n; i++ )
        A[i] = i;
    shuffle ( A, 0, n / 3 );
    shuffle ( A, 2 * n / 3, n );
}

void print( int A[], int n, int lo, int hi ) {
    bool sorted = true;
    for( int i = 1; i < n; i++ )
        if ( A[i-1] > A[i] )
            sorted = false;
    printf( sorted ? "S: " : " : " );
    for( int i = 0; i < lo; i++ ) printf ( "   ." );
    for( int i = lo; i < hi; i++ ) printf ( "%4d", A[i] );
    for( int i = hi; i < n; i++ ) printf ( "   ." );
    printf ( "\n" );
}

void print( int A[], int n )
{
    print( A, n, 0, n );
}