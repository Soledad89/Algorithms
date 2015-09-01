#include <stdio.h>
int foo(int);
void bar(int);

int main()
{
	int a;
	char *s = "hello, bob\n";
	printf("%s\n", &s[7]);
	a = 5;
	foo(a);
	return 0;
}

int foo(int n)
{
	int b ;
	b = n; 
	b *= 2;
	bar(b);
	return b;
}

void bar(int n)
{
	printf("Hi, I am Bar");
}

