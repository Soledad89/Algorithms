#include<stdio.h>
#include <stdlib.h>
#include<string.h>
int n;

bool increase(char *number);
void print(char *number);
int  main()
{
    printf("please input a number:\n");
    scanf("%d",&n);
    //we get one char more to put '\0'
    char *number = (char *)malloc(n+1);
    memset(number,'0',n);
    number[n] = '\0';
    while(!increase(number))
    {
        print(number);
    }
    getchar();
    getchar();
    return 0;
}
//let number increase 1
bool increase(char *number)
{
    int over = 0;
    int len = (int) strlen(number);
    int slen = len;
    int snum;
    char t;
    
    for(slen = len;slen > 0;slen--)
    {
        //取得时候要减去‘0’，存的时候要加上‘0’，不然会出错。上面已经讨论过了
        snum = number[slen-1] - '0' + over;
        over = 0;
        //对输入为长度1的单独处理
        if(len == 1 && snum == 9)
            return true;
        //对于长度不为1，最高位和中间位为10，才进位，为结束标志
        if(slen == 1 && snum == 10)
            return true;
        //对于最低位，为9就要进位了。
        else if(slen == len)
        {
            if(snum == 9)
            {
                over = 1;
                snum = 0;
            }
            snum++;
        }
        else
        {
            if(snum == 10)
            {
                over = 1;
                snum = 0;
            }
        }
        //over = 0;
        t = (char)snum;
        number[slen-1] = t + '0';
    }
    return false;
}

void print(char *number)
{
    int len = (int )strlen(number);
    int i = 0;
    while((int)number[i] == 0)
        i++;
    if(i == len)
        printf("0");
    for(;i<len;i++)
    {
        printf("%d",number[i] - '0');
    }
    printf("\n");
}