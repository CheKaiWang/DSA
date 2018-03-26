#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

typedef struct{
	int UserID;
	int ItemID;
	int Result;
	int Time;
}Data;

bool cmpU(const Data &a,const Data &b)
{
	if(a.UserID!=b.UserID) return a.UserID<b.UserID;
	if(a.ItemID!=b.ItemID) return a.ItemID<b.ItemID;
	return a.Time<b.Time;
}
bool cmpI(const Data &a,const Data &b)
{
	if(a.ItemID!=b.ItemID) return a.ItemID<b.ItemID;
	if(a.UserID!=b.UserID) return a.UserID<b.UserID;
	return a.Time<b.Time;
}
bool cmp(const int &a,const int &b)
{
	return a<b;
}
int main()
{
	int n;
	vector<Data> dataU,dataI;
	Data temp,ttmp;
	FILE *f=fopen("/tmp2/KDDCUP2012/track1/rec_log_train.txt","r");
		
	while(fscanf(f,"%d%d%d%d",&temp.UserID,&temp.ItemID,&temp.Result,&temp.Time)==4)
	{	
		if(temp.UserID==ttmp.UserID && temp.ItemID==ttmp.ItemID && temp.Result==ttmp.Result && temp.Time==ttmp.Time) continue;
		dataU.push_back(temp);
		dataI.push_back(temp);
		ttmp.UserID=temp.UserID;ttmp.ItemID=temp.ItemID;ttmp.Result=temp.Result;ttmp.Time=temp.Time;
	}
	fclose(f);
	sort(dataU.begin(),dataU.end(),cmpU);
	sort(dataI.begin(),dataI.end(),cmpI);
	
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		char str[32],c;
		scanf("%s",str);
		
		if(!strcmp(str,"accept"))
		{
			int u,i,t;
			scanf("%d%d%d",&u,&i,&t);
			vector<Data>::iterator low;
			low=lower_bound (dataU.begin(),dataU.end(),(Data){u,i,1,t},cmpU);
			if(low->ItemID==i&&low->UserID==u&&low->Time==t) printf("%d\n",low->Result);
			else printf("0\n");
		}
		
		else if(!strcmp(str,"items"))
		{
			int u1,u2,store=0;
			scanf("%d%d",&u1,&u2);
			vector<int> Is;
			vector<Data>::iterator user1,user2;
			user1=lower_bound (dataU.begin(),dataU.end(),(Data){u1,0,0,0},cmpU);
			user2=lower_bound (dataU.begin(),dataU.end(),(Data){u2,0,0,0},cmpU);
			if(user1->UserID!=u1 ||user2->UserID!=u2) printf("EMPTY\n");
			else
			{
				while(user1->UserID==u1 && user2->UserID==u2 && user1!=dataU.end() && user2!=dataU.end())
				{
					if(user1->ItemID>user2->ItemID) user2++;
					else if(user1->ItemID<user2->ItemID) user1++;
					else 
					{
						if(user1->ItemID!=store)
						{
							store=user1->ItemID;
							Is.push_back(store);
						}
						user1++; user2++;
					}

				}
				if(Is.begin()==Is.end()) printf("EMPTY\n");
				else
				{
					for(vector<int>::iterator it=Is.begin();it!=Is.end();it++)
						printf("%d\n",*it);
				}
			}
		}

		else if(!strcmp(str,"users"))
		{
			int i1,i2,t1,t2,store=0;
			scanf("%d%d%d%d",&i1,&i2,&t1,&t2);
			std::vector<int> Us;
			vector<Data>::iterator item1,item2;
			item1=lower_bound (dataI.begin(),dataI.end(),(Data){0,i1,0,0},cmpI);
			item2=lower_bound (dataI.begin(),dataI.end(),(Data){0,i2,0,0},cmpI);
			if(item1->ItemID!=i1 || item2->ItemID!=i2) printf("EMPTY\n");
			else
			{
				while(item1->ItemID==i1 && item2->ItemID==i2 && item1!=dataI.end() && item2!=dataI.end())
				{
					if(item1->UserID>item2->UserID) item2++;
					else if(item1->UserID<item2->UserID) item1++;
					else 
					{
						if(item1->Time>t2 || item1->Time<t1) item1++;
						else if(item2->Time>t2 || item2->Time<t1) item2++;
						else
						{
							if(item1->UserID!=store)
							{
								store=item1->UserID;
								Us.push_back(store);
							}
							item1++; item2++;
						}
					}

				}
				if(Us.begin()==Us.end()) printf("EMPTY\n");
				else
				{
					for(vector<int>::iterator it=Us.begin();it!=Us.end();it++)
						printf("%d\n",*it);
				}
			}
		}

		else if(!strcmp(str,"ratio"))
		{
			int i,threshold,counta=0,counttimes=0,countusers=0,tempuser=0,acornot=0;
			scanf("%d%d",&i,&threshold);
			for(vector<Data>::iterator it=dataU.begin();it!=dataU.end();it++)
			{	

				if(it->UserID==tempuser) counttimes++;
				else if(it->UserID!=tempuser && counttimes>threshold)
				{	
					if(acornot==1) counta++;
					tempuser=it->UserID;
					countusers++;
					counttimes=1;
					acornot=0;
				}
				else if(it->UserID!=tempuser && counttimes<=threshold)
				{
					tempuser=it->UserID;
					counttimes=1;
					acornot=0;
				}
				if(it->ItemID==i && it->Result==1) acornot=1;
				if(it==dataU.end()-1 && counttimes>threshold)
				{
					if(acornot==1) counta++;
					countusers++;
				}
			}
			printf("%d/%d\n",counta,countusers);
		}

		else if(!strcmp(str,"findtime_item"))
		{
			int i,scan;
			vector<int> Us,Ts;
			scanf("%d",&i);
			while(~ scanf("%s",str))
			{
				sscanf(str,"%d",&scan);
				Us.push_back(scan);
				if(c=fgetc(stdin)=='\n') break;
			}
			scan=0;
			sort(Us.begin(),Us.end(),cmp);
			vector<Data>::iterator item=lower_bound(dataI.begin(),dataI.end(),(Data){0,i,0,0},cmpI);
			for(vector<Data>::iterator it=item;it->ItemID==i;it++)
				for(vector<int>::iterator it2=Us.begin();it2!=Us.end();it2++)
					if(it->UserID==*it2 && scan!=it->UserID)
					{
						scan=it->UserID;
						for(vector<Data>::iterator t=it;t->UserID==scan;t++)
							Ts.push_back(t->Time);
						break;
				
					}
			sort(Ts.begin(),Ts.end(),cmp);
			scan=0;
			if(Ts.begin()==Ts.end()) printf("EMPTY\n");
			else
			{
				for(vector<int>::iterator it=Ts.begin();it!=Ts.end();it++)
					if(*it!=scan)
					{
						printf("%d\n",*it);
						scan=*it;
					}
			}		
		}
	}
	return 0;
}