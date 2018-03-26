#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
vector<float> p,q;
float D[1024][128];
bool B[1024][128];
float d(int i,int j)
{
	if(i==0 && j==0) return abs(p[i]-q[j]);
	else if(j==0) return d(i-1,j) + abs(p[i]-q[j]);
	if(B[i][j]==1) return D[i][j];
	if(i<j) return 7122;
	else
	{
		if(d(i-1,j)!=d(i-1,j-1)) D[i][j]=((d(i-1,j)<d(i-1,j-1))? d(i-1,j) : d(i-1,j-1)) + abs(p[i]-q[j]);
		else D[i][j]=d(i-1,j-1) + abs(p[i]-q[j]);
		B[i][j]=1;
		return D[i][j];
	}
}
void go(int i,int j)
{
	int P[1024],n=0;
	for(int k=i;k>0 && j>0;k--)
	{
		if(D[k-1][j]>=D[k-1][j-1])
		{
			P[n++]=k;
			j--;
		}
	}
	printf("0 ");
	for(int i=n-1;i>=0;i--) printf("%d ",P[i]);
}
int main()
{
	int m,n,t;
	float tmp,min=666666;
	memset(B,sizeof(B),0);
	memset(D,sizeof(D),0);
	scanf("%d",&m);
	for(int i=0;i<m;i++)
	{
		scanf("%f",&tmp);
		p.push_back(tmp);
	}
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%f",&tmp);
		q.push_back(tmp);
	}
	for(int i=0;i<n;i++)
	{
		if(d(m-1,i) < min)
		{
			min=d(m-1,i);
			t=i;
		}
	}
	printf("%f\n",min);
	go(m-1,t);
	return 0;
}