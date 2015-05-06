#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"

int main(int arc, char *argv[])
{
    int i;

    int num = 10;
    int A[MAXMUM] = {1,2,3,4,4,4,4,7,7,8};
    for (i = 0; i < num; i++)
        printf("%d  ", A[i]);
    printf("\n");

    int num_new;
    //num_new = remove_duplicates(A, num);
    num_new = remove_duplicates3(A, num);


    for (i = 0; i < num_new; i++)
        printf("%d  ",A[i]);
    printf("\n");

    return 0;
}



