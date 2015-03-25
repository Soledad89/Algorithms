#include <stdio.h>
int main(void)
{
	int a[5]= {1,2,3,4,5};
	insert_sort(a);
}

void insert_sort(int a[])
{
	for (int i = 0; 
