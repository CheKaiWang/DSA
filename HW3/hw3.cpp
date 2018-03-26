#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int m,n,flag=0,mtr[80][80],vm[80][40],vn[80][40];
void print(int cnt)
{
	for(int i=0;i<cnt;i++)
	{
		printf(mtr[i/n][i%n]==1?"#":".");
		if(i%n==n-1) printf("\n");
	}
	flag=1;
}
int check(int cnt)
{
	int a=cnt/n,b=cnt%n,count=0,test[40];
	memset(test,0,sizeof(test));
	
	for(int i=0;i<=b;i++)
	{
		if(mtr[a][i]==1) 
		{
			test[count]++;
			if(i==b && test[count]>vm[a][count]) return 0;
		}
		else if(mtr[a][i]==0 && test[count]>0)
		{
			if(test[count]!=vm[a][count]) return 0;
			count++;
		}
	}
	if(b==n-1 &&vm[a][count+1]!=0) return 0;
	if(mtr[a][b-1]==0&&n-b<vm[a][count]) return 0;
	memset(test,0,sizeof(test));
	count=0;
	for(int i=0;i<=a;i++)
	{
		if(mtr[i][b]==1) 
		{
			test[count]++;
			if(i==a && test[count]>vn[b][count]) return 0;
		}
		else if(mtr[i][b]==0 && test[count]>0)
		{
			if(test[count]!=vn[b][count]) return 0;
			count++;
		}
	}
	if(mtr[a-1][b]==0&&m-a<vn[b][count]) return 0;
	return 1;
}
void fill(int cnt)
{
	if(flag==1) return;
	if(cnt==m*n) print(cnt);
	if(cnt>=m*n) return;
	int i=cnt/n,j=cnt%n;
	mtr[i][j]=1;
	if(check(cnt))fill(cnt+1);
	if(flag==1) return;
	mtr[i][j]=0;
	if(check(cnt))fill(cnt+1);
	return;
}
int main()
{
	memset(mtr,0,sizeof(mtr));
	memset(vn,0,sizeof(vn));
	memset(vm,0,sizeof(vm));
	scanf("%d%d",&m,&n);
	for(int i=0;i<m;i++)
	{
		int j=0;
		char c;
		while(~ scanf("%d",&vm[i][j++]))
		{
			if(c=fgetc(stdin)=='\n') {j=0;break;}
		}
	}
	for(int i=0;i<n;i++)
	{
		int j=0;
		char c;
		while(~ scanf("%d",&vn[i][j++]))
		{
			if(c=fgetc(stdin)=='\n') {j=0;break;}
		}
	}
	fill(0);
	return 0;
}