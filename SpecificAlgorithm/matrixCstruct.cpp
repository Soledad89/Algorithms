#include<cstdio>
#include<iostream>
#include<cstring>
#define maxn 5

using namespace std;

const int mod = 10000;
int n,q;
struct Mat
{
  int mp[maxn][maxn];
  bool operator = (Mat a)
  {
    for(int i=0;i<n;i++)
    {
      for(int j=0;j<n;j++)
        mp[i][j] = a.mp[i][j];
    }
  }
};
Mat operator *(Mat a,Mat b)
{
  Mat c;
  memset(c.mp,0,sizeof(c.mp));
  for(int k=0;k<n;k++)
  {
    for(int i=0;i<n;i++)
    {
      if(a.mp[i][k]<=0) continue;
      for(int j=0;j<n;j++)
      {
        if(b.mp[k][j]<=0) continue;
        c.mp[i][j] = c.mp[i][j]+(a.mp[i][k]*b.mp[k][j])%mod;
        if(c.mp[i][j]>mod) c.mp[i][j]-=mod;
      }
    }
  }
  return c;
}
Mat operator ^(Mat a,int k)
{
  Mat c;
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
      c.mp[i][j] = (i==j);
  }
  while(k)
  {
    if(k&1)
      c = c*a;
    a =a*a;
    k>>=1;
  }
  return c;
}
int main()
{
  while(scanf("%d",&q)!=EOF)
  {
    if(q == -1) break;
    Mat x;
    x.mp[0][0] = 0;
    x.mp[0][1] = 1;
    x.mp[1][0] = 1;
    x.mp[1][1] = 1;
    Mat y;
    y.mp[0][0] = 0;
    y.mp[1][0] = 1;
    Mat z;
    n = 2;
    if(!q)
    {
      printf("0\n");
      continue;
    }
    z = x^(q-1);
    Mat tmp = z*y;
    printf("%d\n",tmp.mp[1][0]%10000);
  }
  return 0;
}