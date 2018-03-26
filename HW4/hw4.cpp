#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef struct{
	int bID,cID,act,prc,cnt;
}data;
vector<data> buy,sell;
vector<int> check;
bool cmpbuy(const data& a,const data& b)
{
	if(a.prc!=b.prc) return a.prc<b.prc;
	return a.bID>b.bID;
}
bool cmpsell(const data& a,const data& b)
{
	if(a.prc!=b.prc) return a.prc>b.prc;
	return a.bID>b.bID;
}
int main()
{
	int op=0;
	data tmp;
	while(scanf("%d%d%d%d%d",&tmp.bID,&tmp.cID,&tmp.act,&tmp.prc,&tmp.cnt)==5)
	{
		check.push_back(0);
		if(tmp.act==0 && tmp.cnt!=0)
		{
			buy.push_back(tmp);
			push_heap(buy.begin(),buy.end(),cmpbuy);			
		}
		else if(tmp.act==1 && tmp.cnt!=0)
		{
			sell.push_back(tmp);
			push_heap(sell.begin(),sell.end(),cmpsell);
		}
		else if(tmp.act==2)
		{
			check[tmp.prc]=1;
		}
		while( sell.size()>0 && buy.size()>0)
		{
			while(check[buy.front().bID]==1 && buy.size()!=0)
			{
				pop_heap(buy.begin(),buy.end(),cmpbuy);
				buy.pop_back();
			}
			while(check[sell.front().bID]==1 && sell.size()!=0)
			{
				pop_heap(sell.begin(),sell.end(),cmpsell);
				sell.pop_back();
			}
			if(sell.front().prc>buy.front().prc ||sell.size()==0 ||buy.size()==0) break;
			if(sell.front().cnt>buy.front().cnt)
			{
				printf("%d\t%d\t%d\t%d\t%d\n",op,buy.front().cID,sell.front().cID,sell.front().prc,buy.front().cnt);
				sell.front().cnt -= buy.front().cnt;
				pop_heap(buy.begin(),buy.end(),cmpbuy);
				buy.pop_back();
				op++;
			}
			else if(sell.front().cnt<buy.front().cnt)
			{
				printf("%d\t%d\t%d\t%d\t%d\n",op,buy.front().cID,sell.front().cID,sell.front().prc,sell.front().cnt);
				buy.front().cnt -= sell.front().cnt;
				pop_heap(sell.begin(),sell.end(),cmpsell);
				sell.pop_back();
				op++;
			}
			else
			{
				printf("%d\t%d\t%d\t%d\t%d\n",op,buy.front().cID,sell.front().cID,sell.front().prc,buy.front().cnt);
				pop_heap(buy.begin(),buy.end(),cmpbuy);
				buy.pop_back();
				pop_heap(sell.begin(),sell.end(),cmpsell);
				sell.pop_back();
				op++;
			}
		}
	}
	return 0;
}