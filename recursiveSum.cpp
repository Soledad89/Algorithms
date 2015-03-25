#include <iostream>
using namespace std;
int sum;
int store[10];
void Output()
{
	for (int i = 9; i>=0; --i)
	{
		cout<<store[i]<<" ";
	}
	cout<<endl;
	++sum;
}

void Comput(int score, int num)
{
	if (score < 0 || score > (num+1)*10)
		return;
	if (num == 0)
	{
		store[num] = score;
		Output();
		return;
	}

	for (int i = 0; i<=10; ++i)
	{
		store[num] = i;
		Comput(score - i, num - 1);
	}
}

int main(int argc, char * argv[])
{
	Comput(90,9);
	cout<<"总数："<<sum<<endl;
	return 0;
}


