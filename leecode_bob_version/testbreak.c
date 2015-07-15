#include <stdio.h>

int main()
{
	int i;
	for (i = 0; i < 5; i++)
		if ( i == 4)
			break;/*after break occurs, no other program will be executed*/

	printf("%d\n", i);
	return 0;
}

