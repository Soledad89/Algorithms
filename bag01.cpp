#include <iostream>
#include <string>
using namespace std;
int mVal, nVal;
int * pOut;
void calFun( int m, int n)
{
	if (m < 1 || n < 1 || ( n == 1 && m != 1))
		return ;

	//看是否与箱子所剩容积相等
	if ( m == n)
	{
		pOut[n] = 1;
		for ( int i = 1; i <= nVal; ++i)
		{
			if ( pOut[i] )
				cout<<i<<" ";
		}
		cout<<endl;
		pOut[n] = 0;
	}

	calFun( m, n-1);
	pOut[n] = 1;
	calFun(m - n, n-1);
	pOut[n] = 0;
}

int main( int argc, char * argv[])
{
	cout<<"m:";
	cin>>mVal;
	cout<<"n:";
	cin>>nVal;

	if ( mVal < nVal) nVal = mVal;
	pOut = new int[nVal + 1];
	memset((pOut, -1, (nVal+1)*sizeof(int));
	calFun(mVal, nVal);
	delete []pOut;
	return 0;
}

