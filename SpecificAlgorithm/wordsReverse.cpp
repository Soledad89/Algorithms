/*
题目描述：翻转句子中单词的顺序，但单词内字符的顺序不变。句子中单词以空格符隔开。
为简单起见，标点符号和普通字母一样处理。如："I am a student."翻转成"student. a am I"。
 
常见面试题
*/
 
#include<iostream>
#include<vector>
#include<assert.h>
#include<cstring>
using namespace std;
 
void swap(char &a, char &b)
{
    char tmp = b;
    b = a;
    a = tmp;
}
 
void swap_str(char* str, int start, int end)
{
    assert(str!=NULL && start <= end);
    int low = start;
    int high = end;
 
    //整个句子按字符翻转
    while (low < high)
    {
        swap(str[low], str[high]);
        low++;
        high--;
    }
 
}
 
//方法一：依次读入句子中的每个单词，并将它们放入一个栈中。然后再将单词出栈。
//时间复杂度：O(n)，空间复杂度:O(n)；
 
//方法二：首先将整个句子按字符翻转，然后再将其中每个单词的字符旋转。
//时间复杂度：O(n)，空间复杂度:O(1)；
void reverse_word(char str[])
{
    int len = strlen(str);
 
    //翻转整个句子
    swap_str(str, 0, len-1);
 
    int s = 0;
    int e = 0;
    //翻转每个单词
    for (int i=0; i<len; i++)
    {
        e = i;
        if (str[e] == ' ')
        {
            //str[e]为空格，所以范围是[s,e-1].
            swap_str(str, s, e-1);
            s = e + 1;
        }
    }
}
 
int main()
{
    char str[] = "I am a student.";
    reverse_word(str);
    cout<<str<<endl;
    return 0;
}