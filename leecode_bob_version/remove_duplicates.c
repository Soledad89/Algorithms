#include <stdio.h>
#include <stdlib.h>
#define MAXMUM 1000
int remove_duplicates(int a[], int num);

int main(int arc, char *argv[])
{
	if (arc == 1){	
		printf("please input the numbers");
		return 0;
	}
	
	int num = atoi(argv[1]);
	int a[MAXMUM];
	int i; 
	
	printf("please input %d numbers\n", num);
	
	for (i = 0; i < num;  i++)
	{
		printf("please input the %d number\n", i);
		scanf("%d", &a[i]);
	}
	printf("the original numbers: ");
	for (i = 0; i < num; i++)
		printf("%d ", a[i]);

	int n = remove_duplicates(a, num);
	printf("\nthe moved numbers: ");
	for (i = 0; i < n; i++)
		printf("%d ", a[i]);
	return 0;
}

int remove_duplicates(int a[], int num)
{
	if (num == 0) return 0;
	int i, index = 0;
	for (i = 1; i < num; i++)
		if (a[index] != a[i])
			a[++index] = a[i];
	return index+1;
}



