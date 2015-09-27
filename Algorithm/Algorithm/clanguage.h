//
//  clanguage.h
//  Algorithm
//
//  Created by 王波 on 15/9/23.
//  Copyright (c) 2015年 wangbo. All rights reserved.
//

#ifndef Algorithm_clanguage_h
#define Algorithm_clanguage_h

#include <stack>
#include <list>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


/*
 ** Look in the string s1 for the rightmost occurrence of the string
 ** s2, and return a pointer to where it begins.
 */

//strstr函数是找s1中s2第一次出现的index，也就是KMP算法的应用
char* my_strrstr( char const *s1, char const *s2 )
{
     char	*last;  //初始化一个指针变量时，只是给指针变量分配了一个空间，存储这个指针（也就是地址）
     char	*current;
    
    /*
     ** Initialize pointer for the last match we've found.
     */
    last = NULL;
    
    /*
     ** Search only if the second string is not empty.  If s2 is
     ** empty, return NULL.
     */
    if( *s2 != '\0' ){
        /*
         ** Find the first place where s2 appears in s1.
         */
        current = strstr( s1, s2 );
        
        /*
         ** Each time we find the string, save the pointer to
         ** where it begins.  Then look after the string for
         ** another occurrence.
         */
        while( current != NULL ){
            last = current;
            current = strstr( last + 1, s2 );
        }
    }
    
    /*
     ** Return pointer to the last occurrence we found.
     */
    return last;
}


int matrix[3][4];
//matrix+1指向的是矩阵的第二行的数组指针，*(matrix+1)标示了包含10个整形元素的子数组即为matrix[1]
void getMemory(char ** p, int num) {
    *p = (char *)malloc(num * sizeof(char*));
}
//上下两个函数等价
char *getMemory2(char *p, int num) {
    p = (char*)malloc(sizeof(char)*num);
    return p;
}

//这里不能只传递一个指针参数,如下，传递到函数中的只是指针p（也就是一个地址值）的拷贝
/*
 void getMemory(char *p, int num)
 {
    p = (char *) malloc(sizeof(char)*num);
 }
 */
//正确的用法是：如果传递过来的是指针，那么如果对该指针dereference的话，并改变其中的值，是完全允许的
//即：传递的是如下
void getMemory3(int *n) {
    *n = 3;                     //这是会修改n的值的，把该地址里面的值改了。
}
int getMemory_main() {
    char *str = NULL;
    getMemory(&str, 100);
    strcpy(str, "hello");
    return 0;
}



/* reverse: reverse a string */
void reverse(char s[])
{
    int c, i, j;
    for( i = 0, j = (int)strlen(s)-1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* itob(int n, char s[], int b */
void itob(int n, char s[], int b)
{
    int i, j, sign;
    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do{
        j = n % b;
        s[i++] = (j <= 9)? j + '0' : j + 'a' - 10;
    }while ((n /= b) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}


/* itoa: convert a interger to a string */
/* when the maxmin negtive number enters it craches */
void ito4(int n , char s[])
{
    int i, sign;
    
    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do {
        s[i++] = n%10 + '0';
    }while((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

/* itoa2: convert a interger into a string */
#define abs(x) ((x) < 0 ? -(x) : (x))
void itoa5(int n, char s[])
{
    int i, sign;
    sign = n;
    i = 0;
    do{
        s[i++] = abs(n % 10) + '0';
    }while((n /= 10) != 0);
    
    if(sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

/* atoi: turn a string into a insteger */
int atoi(char s[])
{
    int i, n;
    
    n = 0;
    for (i = 0; s[i] >= '0'|| s[i] <= '9'; ++i)	// isdigit(c) in ctype.h //
        n = 10 * n + (s[i] - '0');
    return n;
}

/* atoi2: turn a string into a integer, has + or -  */
int atoi2(char s[])
{
    int i, n, sign;
    
    for (i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (; isspace(s[i]); i++)
        ;
    for (n = 0; isdigit(s[i]); i++)
        n = 10 * n + (s[i] - '0');
    return sign * n;
}

/* lower: <ctype.h> has tolower(c) which acts the same */
int lower(int c)
{
    return c >= 'A' && c <= 'F' ? c - 'A' + 'a' : c;
}

/* rand: generates a random number */
unsigned long int next__ = 1;
int rand(void)
{
    next__ = next__ * 1103515245 + 12345;
    return (unsigned int)(next__/65536) % 32768;
}




/* any: */
int any(char s1[], char s2[])
{
    return 0;
    
}

/* strcat: strcat the string t to the string s */
void my_strcat(char s[], char t[])
{
    int i, j;
    i = j = 0;
    while ( s[i] != '\0')
        i ++;						// goes to the end of the string s //
    while ((s[i++] = t[j++]) != '\0')
        ;
}

/* getbits: get the unsigned x's bits from p to n */
unsigned getbits( unsigned x, int p, int n)
{
    return (x >> (p+1-n) & ~(~0 << n));
}

/* bitcount: cout the 1s of the integer x */
int bitcount(unsigned x)
{
    int b = 0;
    for (; x != 0; x >>= 1)
        if (x & 01)
            b ++;
    return b;
}


#endif
